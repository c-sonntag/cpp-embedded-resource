#pragma once

#include <erc/types.h>

#include <erc/maker/erc_package_file_parser.h>
#include <erc/maker/erc_files_list.h>

#include <string>
#include <vector>

namespace erc {
  namespace maker {

    struct src_generator
    {
     public:
      const erc_package_file_parser & erc_package;
      const erc_files_list & erc_files;

     public:
      src_generator( const erc_package_file_parser & _erc_package, const erc_files_list & _erc_files );

     public:
      void open_cache_file( const std::string & erc_cache_filepath );
      void save_cache_file( const std::string & erc_cache_filepath );

     public:
      void generate_into( const std::string & erc_output_directorypath );

     private:
      void generate_header_embedded_files(
        const std::vector<std::string> & generated_embedded_files_uniques_identifier,
        const std::string output_src_file
      );

      void generate_header_package(
        const std::vector<std::string> generated_packages,
        const std::string output_src_file
      );

     private:
      void generate_file(
        const file_property_found & valid_input_file,
        const std::string & generated_embedded_file_unique_identifier,
        const std::string & output_src_file
      );

      void generate_package(
        const std::string & generated_package_unique_identifier,
        const std::vector<std::string> & generated_embedded_files_uniques_identifier,
        const std::string & output_src_file
      );


    };

  }
}

