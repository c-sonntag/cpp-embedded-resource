#pragma once

#include <string>

namespace erc {

  struct file_id
  {
    std::string package_name;
    std::string file_path;

    inline file_id( std::string _package_name, std::string _file_path ) :
      package_name( std::move( _package_name ) ), file_path( std::move( _file_path ) )
    {}

    inline std::string to_string() const { return package_name + ":/" + file_path; }
    inline operator std::string()  const { return to_string(); }
  };

}

