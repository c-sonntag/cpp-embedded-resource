#pragma once

#include <erc/file.h>

namespace erc {

  struct package
  {
    const std::string name;
    const size_t size;
    const erc::embedded_file * const * const embedded_files;

    inline package( const std::string & _name, const size_t _size, const erc::embedded_file * const * const _embedded_files ) :
      name( std::move( _name ) ), size( std::move( _size ) ), embedded_files( std::move( _embedded_files ) )
    {}
  };

  struct package_list
  {
    const erc::package & package;
    const package_list * const next;

    inline package_list( const erc::package & _package, const package_list * const _next ) :
      package( std::move( _package ) ), next( std::move( _next ) )
    {}
  };

  #if defined(ERC_MANAGER_MAIN_PACKAGE_LIST_EXIST) && (ERC_MANAGER_MAIN_PACKAGE_LIST_EXIST==1)
  extern const package_list main_package_list;
  #endif

}

