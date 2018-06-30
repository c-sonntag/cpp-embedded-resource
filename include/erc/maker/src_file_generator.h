#pragma once

#include <erc/types.h>
#include <erc/maker/erc_files_list.h>

#include <string>

namespace erc {
  namespace maker {

    struct src_file_generator
    {



     const std::string input_file;
     const std::string output_src_file;

      src_file_generator( const std::string input_file, const std::string output_src_file );
      //src_file_generator( const erc_files_list & input_file, const std::string output_src_file );
    };


  }
}

