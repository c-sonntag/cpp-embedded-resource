#include <erc/maker/src_generator.h>

#include <fstream>
#include <sstream>

#define ZLIB_CONST 1
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
      return os;
    }

    std::ostream & operator <<( std::ostream & os, const embedded_data_property & edp )
    {
      using std::endl;
      os << "  {" << endl
         << "    " << edp.file << "," << endl
         << "    " << edp.size << ", " << named_boolean_str( edp.compressed ) << ", " << named_boolean_str( edp.raw_data ) << endl
         << "  }";
      return os;
    }

    std::ostream & operator <<( std::ostream & os, const embedded_file & ef )
    {
      using std::endl;
      os << "{" << endl
         << "  \"" << ef.path << "\"," << endl
         << ef.property << "," << endl
         << "  data" << endl
         << "}";
      return os;
    }

    // ---- ---- ---- ----

    std::string compress_string( const std::string & str,
                                 int compressionlevel = Z_BEST_COMPRESSION )
    {
      z_stream zs;                        // z_stream is zlib's control structure
      memset( &zs, 0, sizeof( zs ) );

      if ( deflateInit( &zs, compressionlevel ) != Z_OK )
        throw( std::runtime_error( "deflateInit failed while compressing." ) );

      zs.next_in = reinterpret_cast<const Bytef *>( str.data() );
      zs.avail_in = static_cast<uInt>( str.size() );         // set the z_stream's input

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
      constexpr uint8_t return_mod_limit( 15 );

      //
      const size_t size( data.size() );

      //
      os << "static const unsigned char data[" << size << "] =" << endl
         << "{" << endl;

      //
      const std::ios_base::fmtflags original_os_flags( os.flags() );
      os << std::hex;

      //
      uint8_t return_mod_count( 0 );
      for ( const char c : data )
      {
        if ( return_mod_limit == return_mod_count )
        {
          os << endl;
          return_mod_count = 0;
        }

        os << "0x" << static_cast<unsigned short>( static_cast<unsigned char>( c ) ) << ",";

        ++return_mod_count;
      }

      //
      if ( return_mod_count != 0 )
        os << endl;

      //
      os.flags( original_os_flags );

      //
      os << "};" << endl
         << endl;

    }

    // ---- ---- ---- ----

    void src_generator::generate_file( const src_file_identifier & file_id, const std::string & output_src_file )
    {

      //
      using std::endl;

      try
      {
        //
        std::ifstream input( file_id.valid_input_file.path, std::ifstream::in | std::ifstream::binary );
        if ( !input )
          throw std::string( "invalid <input_file> " + file_id.valid_input_file.path );

        //
        std::ofstream output( output_src_file, std::ofstream::out | std::ofstream::trunc );
        if ( !output )
          throw std::string( "can't write <output_src_file> at " + output_src_file );

        //
        output << "/**" << endl
               << "* @brief Generated file for EmbeddedResource lib" << endl
               << "* @note Original file can be found at" << endl
               << "*       " << file_id.valid_input_file.path << endl
               << "*/" << endl
               << endl;

        //
        const std::string input_content( ( std::istreambuf_iterator<char>( input ) ),
                                         ( std::istreambuf_iterator<char>() ) );

        //
        uint packing_size( 0 );

        //
        if ( file_id.valid_input_file.file.compress )
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
          file_id.valid_input_file.file.path,
          {
            file_id.valid_input_file.property,
            packing_size,
            file_id.valid_input_file.file.compress,
            true /**< raw data */
          },
          nullptr /**< not important here */
        };

        //
        output << "#include \"./embedded_file.h\"" << endl
               << "const erc::embedded_file erc::generated_embedded_files::" << file_id.file_unique_identifier << endl
               << ef << ";" << endl
               << endl;

      }
      catch ( const std::string & s )
      { throw std::runtime_error( "[embedded_rc::maker::src_generator::generate_file] " + s ); }

    }

  }
}
