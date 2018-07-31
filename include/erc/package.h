#pragma once

#include <erc/file.h>

namespace erc {

  struct package
  {
   public:
    const std::string name;
    const uint size;
    const erc::embedded_file * const * const embedded_files;

   public:
    inline package( const std::string & _name, const uint _size, const erc::embedded_file * const * const _embedded_files ) :
      name( std::move( _name ) ), size( std::move( _size ) ), embedded_files( std::move( _embedded_files ) )
    {}

   public:
    const erc::embedded_file * get_embedded_file( const std::string & file_path ) const;
  };

}

