#include <erc/maker/src_file_generator.h>

#include <fstream>
#include <sstream>

#include <zlib.h>

namespace erc {
  namespace maker {

    inline const char * named_boolean_str( const bool value )
    {
      static const char * true_str{"true"};
      static const char * false_str{"false"};
      return value ? true_str : false_str;
    }

    // ---- ---- ---- ----

    std::ostream & operator <<( std::ostream & os, const file_property & fp )
    {
      using std::endl;
      os << "{\"" << fp.filename << "\", \"" << fp.extension << "\", " << fp.size << "}";
    }

    std::ostream & operator <<( std::ostream & os, const embedded_data_property & edp )
    {
      using std::endl;
      os << "  {" << endl
         << "    " << edp.file << "," << endl
         << "    " << edp.size << ", " << named_boolean_str( edp.compressed ) << ", " << named_boolean_str( edp.raw_data ) << endl
         << "  }";
    }

    std::ostream & operator <<( std::ostream & os, const embedded_file & ef )
    {
      using std::endl;
      os << "{" << endl
         << "  \"" << ef.path << "\"," << endl
         << "  " << ef.property << "," << endl
         << "  data" << endl
         << "}";
    }

    // ---- ---- ---- ----

    std::string compress_string( const std::string & str,
                                 int compressionlevel = Z_BEST_COMPRESSION )
    {
      z_stream zs;                        // z_stream is zlib's control structure
      memset( &zs, 0, sizeof( zs ) );

      if ( deflateInit( &zs, compressionlevel ) != Z_OK )
        throw( std::runtime_error( "deflateInit failed while compressing." ) );

      zs.next_in = ( Bytef * )str.data();
      zs.avail_in = str.size();           // set the z_stream's input

      int ret;
      char outbuffer[32768];
      std::string outstring;

      // retrieve the compressed bytes blockwise
      do
      {
        zs.next_out = reinterpret_cast<Bytef *>( outbuffer );
        zs.avail_out = sizeof( outbuffer );

        ret = deflate( &zs, Z_FINISH );

        if ( outstring.size() < zs.total_out )
        {
          // append the block to the output string
          outstring.append( outbuffer,
                            zs.total_out - outstring.size() );
        }
      }
      while ( ret == Z_OK );

      deflateEnd( &zs );

      if ( ret != Z_STREAM_END )          // an error occurred that was not EOF
      {
        std::ostringstream oss;
        oss << "Exception during zlib compression: (" << ret << ") " << zs.msg;
        throw ( std::runtime_error( oss.str() ) );
      }

      return outstring;
    }


    // ---- ---- ---- ----

    void data_block_writer( std::ostream & os, const std::string & data )
    {
      //
      using std::endl;

      //
      constexpr size_t return_mod_limit( 40 );
      const size_t size( data.size() );

      //
      os << "static const unsigned char data[" << size << "] =" << endl
         << "{" << endl;

      //
      for ( size_t i( 0 ), return_mod_count( 0 ); i < size; ++i, ++return_mod_count )
      {
        os << "0x" << short( data[i] ) << ",";
        if ( return_mod_limit == return_mod_count )
        {
          os << endl;
          return_mod_count = 0;
        }
      }

      //
      os << "};" << endl
         << endl;
    }

    // ---- ---- ---- ----

    src_file_generator::src_file_generator( const file_property_found & _valid_input_file, const std::string _generated_embedded_file_unique_identifier, const std::string _output_src_file ) :
      valid_input_file( std::move( _valid_input_file ) ),
      generated_embedded_file_unique_identifier( std::move( _generated_embedded_file_unique_identifier ) ),
      output_src_file( std::move( _output_src_file ) )
    {

      //
      using std::endl;

      try
      {
        //
        std::ifstream input( valid_input_file.path, std::fstream::in | std::fstream::binary );
        if ( !input )
          throw std::string( "invalid <input_file> " + valid_input_file.path );

        //
        std::ofstream output( output_src_file, std::fstream::out | std::fstream::trunc );
        if ( !output )
          throw std::string( "can't write <output_file> at " + output_src_file );

        //
        output << "/**" << endl
               << "* @brief Generated file for EmbeddedResource lib" << endl
               << "* @note Original file can be found at" << endl
               << "*       " << valid_input_file.path << endl
               << "*/" << endl
               << endl;

        //
        const std::string input_content( ( std::istreambuf_iterator<char>( input ) ),
                                         ( std::istreambuf_iterator<char>() ) );

        //
        size_t packing_size( 0 );

        //
        if ( valid_input_file.file.compress )
        {
          const std::string input_compressed_content( compress_string( input_content ) );
          data_block_writer( output, input_compressed_content );
          packing_size = input_compressed_content.size();
        }
        else
        {
          data_block_writer( output, input_content );
          packing_size = input_content.size();
        }

        //
        embedded_file ef
        {
          valid_input_file.file.path,
          {
            valid_input_file.property,
            packing_size,
            valid_input_file.file.compress,
            true /**< raw data */
          },
          nullptr /**< not important here */
        };

        //
        output << "#include \"./embedded_file.h\"" << endl
               << "const erc::embedded_file erc::generated_embedded_files::" << generated_embedded_file_unique_identifier << endl
               << ef << ";" << endl
               << endl;

      }
      catch ( const std::string & s )
      {
        throw std::runtime_error( "[embedded_rc::maker::src_file_generator] " + s );
      }


    }

  }
}
