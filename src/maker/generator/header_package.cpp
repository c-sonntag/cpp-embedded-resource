#include <erc/maker/generator/src_header_package.h>

#include <fstream>
#include <sstream>

namespace erc {
  namespace maker {
    namespace generator {


      void src_header_package(
        const std::vector<std::string> generated_packages,
        const std::string output_src_file
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
                 << "* @brief Generated file for EmbeddedResource lib." << endl
                 << "*/" << endl
                 << endl;

          //
          output << "#pragma once" << endl
                 << "#include <erc/package.h>" << endl
                 << "namespace erc {" << endl
                 << "  namespace generated_package {" << endl;

          //
          for ( const std::string & generated_package : generated_packages )
            output << "    const extern erc::package " << generated_package << ";" << endl;

          //
          output << "  }" << endl
                 << "}" << endl
                 << endl;

        }
        catch ( const std::string & s )
        {
          throw std::runtime_error( "[embedded_rc::maker::generator::src_header_package] " + s );
        }


      }

    }
  }
}
