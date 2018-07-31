#include <erc_maker/src_generator.h>

#include <erc/compress.h>

#include <fstream>
#include <sstream>


namespace erc_maker {

  inline const char * named_boolean_str( const bool value )
  {
    static const char * true_str{"true"};
    static const char * false_str{"false"};
    return value ? true_str : false_str;
  }

  // ---- ---- ---- ----

  std::ostream & operator <<( std::ostream & os, const erc::file_property & fp )
  {
    using std::endl;
    os << "{\"" << fp.filename << "\", \"" << fp.extension << "\", " << fp.size << ", " << fp.last_modification << "}";
    return os;
  }

  std::ostream & operator <<( std::ostream & os, const erc::embedded_data_property & edp )
  {
    using std::endl;
    os << "      {" << endl
       << "        " << edp.file << "," << endl
       << "        " << edp.size << ", " << named_boolean_str( edp.compressed ) << ", " << named_boolean_str( edp.raw_data ) << endl
       << "      }";
    return os;
  }

  std::ostream & operator <<( std::ostream & os, const erc::embedded_file & ef )
  {
    using std::endl;
    os << "    {" << endl
       << "      \"" << ef.path << "\"," << endl
       << ef.property << "," << endl
       << "      data" << endl
       << "    }";
    return os;
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
        throw std::runtime_error( "invalid <input_file> " + file_id.valid_input_file.path );

      //
      std::ofstream output( output_src_file, std::ofstream::out | std::ofstream::trunc );
      if ( !output )
        throw std::runtime_error( "can't write <output_src_file> at " + output_src_file );

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
        const std::string input_compressed_content( erc::compress_string( input_content ) );
        data_block_writer( output, input_compressed_content );
        packing_size = input_compressed_content.size();
      }
      else
      {
        data_block_writer( output, input_content );
        packing_size = input_content.size();
      }

      //
      erc::embedded_file ef
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
      output << "#include <erc/file.h>" << endl
             << endl
             << "namespace erc {" << endl
             << "  namespace generated_embedded_files {" << endl
             << "    const extern erc::embedded_file " << names_generator.to_extern_erc( file_id ) << ";" << endl
             << "    const erc::embedded_file " << names_generator.to_extern_erc( file_id ) << endl
             << ef << ";" << endl
             << "  }" << endl
             << "}" << endl
             << endl;

    }
    catch ( const std::exception & e )
    { throw std::runtime_error( "[embedded_rc::erc_maker::src_generator::generate_file] " + std::string( e.what() ) ); }

  }

}
