#pragma once

#include <erc/maker/model.h>

#include <string>

namespace erc {
  namespace maker {

    struct erc_file_parser
    {
      const std::string erc_file_path;
      model content;

      erc_file_parser( const std::string _erc_file_path );
    };

  }
}

