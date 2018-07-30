#pragma once

#include <erc_maker/model.h>

#include <string>

namespace erc_maker {

  struct erc_package_file_parser
  {
    const std::string erc_package_filepath;
    const std::string erc_package_absolute_filepath;
    model content;

    erc_package_file_parser( const std::string _erc_package_filepath );
  };

}

