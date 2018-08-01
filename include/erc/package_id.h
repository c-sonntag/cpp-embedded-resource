#pragma once

#include <erc/file_id.h>
#include <string>

namespace erc {

  struct package_id
  {
    const std::string package_name;

    inline package_id( std::string _package_name ) :
      package_name( std::move( _package_name ) )
    {}

    inline file_id from( const std::string file_path )
    { return file_id( package_name, file_path ); }
  };

}

