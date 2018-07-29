#include <erc/maker/src_generator.h>

#include <fstream>
#include <sstream>

namespace erc {
  namespace maker {

      void src_generator::header_embedded_files(
        const std::vector<std::string> & generated_embedded_files_uniques_identifier,
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
                 << "#include <erc/file.h>" << endl
                 << "namespace erc {" << endl
                 << "  namespace generated_embedded_files {" << endl;

          //
          for ( const std::string & generated_embedded_file_unique_identifier : generated_embedded_files_uniques_identifier )
            output << "    const extern erc::embedded_file " << generated_embedded_file_unique_identifier << ";" << endl;

          //
          output << "  }" << endl
                 << "}" << endl
                 << endl;

        }
        catch ( const std::string & s )
        { throw std::runtime_error( "[embedded_rc::maker::generator::src_header_embedded_files] " + s ); }

      }

  }
}
