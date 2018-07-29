#pragma once

#include <erc/types.h>

#include <erc/maker/erc_package_file_parser.h>
#include <erc/maker/erc_files_list.h>

#include <string>

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

    };

  }
}

