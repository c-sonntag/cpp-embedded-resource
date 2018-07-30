#pragma once

#include <algorithm>
#include <string>

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

namespace erc_maker {

  inline std::string generic_string_path( const fs::path & p )
  {
    std::string p_str( p.string() );
    std::replace( p_str.begin(), p_str.end(), '\\', '/' );
    return p_str;
  }

  inline std::string generic_string_path( std::string p_str )
  {
    std::replace( p_str.begin(), p_str.end(), '\\', '/' );
    return p_str;
  }

}
