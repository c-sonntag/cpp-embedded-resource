#pragma once

#include <erc/types.h>
#include <erc/maker/erc_files_list.h>

#include <string>

namespace erc {
  namespace maker {

    struct src_package_generator
    {

    };

    struct src_file_generator
    {
      const file_property_found & valid_input_file;
      const std::string generated_embedded_file_unique_identifier;
      const std::string output_src_file;

      src_file_generator( const file_property_found & _valid_input_file, const std::string _generated_embedded_file_unique_identifier, const std::string output_src_file );
      //src_file_generator( const erc_files_list & input_file, const std::string output_src_file );
    };


  }
}

