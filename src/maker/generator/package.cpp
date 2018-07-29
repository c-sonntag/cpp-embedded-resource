#include <erc/maker/src_generator.h>

#include <fstream>
#include <sstream>

namespace erc {
  namespace maker {

    void src_generator::generate_package(
      const std::string & generated_package_unique_identifier,
      const std::vector<std::string> & generated_embedded_files_uniques_identifier,
      const std::string & output_src_file
    )
    {

      //
      using std::endl;

      try
      {

        //
        std::ofstream output( output_src_file, std::fstream::out | std::fstream::trunc );
        if ( !output )
          throw std::string( "can't write <output_file> at " + output_src_file );

        //
        output << "/**" << endl
               << "* @brief Generated file for EmbeddedResource lib" << endl
               << "* @note Package file can be found at" << endl
               << "*       " << erc_package.erc_package_filepath << endl
               << "*/" << endl
               << endl;

        //
        output << "#include \"./embedded_file.h\"" << endl
               << "#include \"./package.h\"" << endl
               << endl
               << "namespace {" << endl
               << "  using namespace erc::generated_embedded_files;" << endl
               << "  const erc::embedded_file * const package_list[]" << endl
               << "  {" << endl;

        //
        for ( const std::string & generated_embedded_file_unique_identifier : generated_embedded_files_uniques_identifier )
          output << "    &" << generated_embedded_file_unique_identifier << "," << endl;

        //
        output << "  };" << endl
               << "}" << endl
               << endl;

        //
        output << "const erc::manager::package erc::generated_package::" << aa << "(" << endl
               << "  \"" << aa << "\"," << endl
               << "  " << aa << "," << endl
               << "  package_list" << endl
               << ");" << endl
               << endl;


      }
      catch ( const std::string & s )
      {
        throw std::runtime_error( "[embedded_rc::maker::generator::src_package] " + s );
      }


    }

  }
}
