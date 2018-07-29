#include <erc/maker/src_generator.h>

#include <fstream>
#include <sstream>

namespace erc {
  namespace maker {

    void src_generator::generate_header_package( const std::string output_src_file )
    {

      //
      using std::endl;

      try
      {
        //
        std::ofstream output( output_src_file, std::ofstream::out | std::ofstream::trunc );
        if ( !output )
          throw std::string( "can't write <output_src_file> at " + output_src_file );

        //
        output << "/**" << endl
               << "* @brief Generated file for EmbeddedResource lib." << endl
               << "* @note Package file can be found at" << endl
               << "*       " << erc_package.erc_package_filepath << endl
               << "*/" << endl
               << endl;

        //
        output << "#pragma once" << endl
               << endl
               << "#include <erc/file.h>" << endl
               << "#include <erc/package.h>" << endl
               << endl
               << "namespace erc {" << endl
               << endl
               << "  namespace generated_embedded_files {" << endl;

        //
        for ( const src_file_identifier & file_id : erc_files_identifier )
          output << "    const extern erc::embedded_file " << file_id.file_unique_identifier.hex << ";" << endl;

        //
        output << "  }" << endl
               << endl
               << "  namespace generated_package {" << endl;

        //
        output << "    const extern erc::package " << package_unique_identifier.hex << ";" << endl;

        //
        // for ( const std::string & generated_package : generated_packages )
        //   output << "    const extern erc::package " << generated_package << ";" << endl;

        //
        output << "  }" << endl
               << "}" << endl
               << endl;
      }
      catch ( const std::string & s )
      { throw std::runtime_error( "[embedded_rc::maker::src_generator::generate_header_package] " + s ); }
    }
  }
}
