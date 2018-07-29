#pragma once

#include <erc/maker/model.h>

#include <string>

namespace erc {
  namespace maker {

    struct erc_package_file_parser
    {
      const std::string erc_package_filepath;
      model content;

      erc_package_file_parser( const std::string _erc_package_filepath );
    };

  }
}

