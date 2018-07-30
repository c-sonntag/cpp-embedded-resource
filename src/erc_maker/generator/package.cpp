#include <erc_maker/src_generator.h>

#include <fstream>
#include <sstream>

namespace erc_maker {

  void src_generator::generate_package( const std::string & output_src_file )
  {

    //
    using std::endl;

    try
    {

      //
      std::ofstream output( output_src_file, std::ofstream::out | std::ofstream::trunc );
      if ( !output )
        throw std::runtime_error( "can't write <output_src_file> at " + output_src_file );

      //
      output << "/**" << endl
             << "* @brief Generated file for EmbeddedResource lib." << endl
             << "* @note Package file can be found at" << endl
             << "*       " << erc_package.erc_package_filepath << endl
             << "*/" << endl
             << endl;

      //
      output << "#include \"./" << names_generator.to_file_header_package_file() << "\"" << endl
             << endl
             << "namespace erc {" << endl
             << endl
             << "  namespace generated_embedded_files {" << endl
             << "    static const erc::embedded_file * const embedded_files[]" << endl
             << "    {" << endl;

      //
      for ( const src_file_identifier & file_id : erc_files_identifier )
        output << "      &" << names_generator.to_extern_erc( file_id ) << "," << endl;

      //
      output << "    };" << endl
             << "  }" << endl
             << endl;

      //
      output << "  const erc::package generated_package::" << names_generator.to_extern_package() << endl
             << "  {" << endl
             << "    \"" << erc_package.content.package_name << "\"," << endl
             << "    " << erc_files_identifier.size() << "," << endl
             << "    erc::generated_embedded_files::embedded_files" << endl
             << "  };" << endl
             << endl
             << "}" << endl
             << endl;
    }
    catch ( const std::exception & e )
    { throw std::runtime_error( "[embedded_rc::erc_maker::src_generator::generate_package] " + std::string( e.what() ) ); }
  }

}
