#pragma once

#include <string>

namespace erc {

  struct file_id
  {
    std::string package_name;
    std::string file_path;

    inline file_id( std::string _package_name, std::string _file_path ) :
      package_name( _package_name ), file_path( std::move( _file_path ) )
    {}
  };

}

