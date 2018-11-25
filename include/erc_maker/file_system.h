#pragma once

#include <algorithm>
#include <string>

#include <fstream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

namespace erc_maker {

  using uint = unsigned int;

  inline std::string generic_string_path( const fs::path& p )
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

  inline fs::path keep_basename( const fs::path& p )
  {
    std::string f( p.filename().string() );
    if( p.filename() == "." )
      return p.parent_path();
    return p;
  }

  inline bool same_write_datetime( const fs::path& p1, const fs::path& p2 )
  {
    return fs::last_write_time( p1 ) == fs::last_write_time( p2 );
  }

  inline void set_write_datetime( const fs::path& to, const fs::path& from )
  {
    fs::last_write_time( to, fs::last_write_time( from ) );
  }

  bool lock_file( const std::string& file_path, const uint timeout_millis = 300, const uint max_write_datetime_diff_seconds = 1 );
  bool unlock_file( const std::string& file_path );

}
