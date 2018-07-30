#pragma once

#include <erc/file.h>

namespace erc {

  struct package
  {
    const std::string name;
    const uint size;
    const erc::embedded_file * const * const embedded_files;

    inline package( const std::string & _name, const uint _size, const erc::embedded_file * const * const _embedded_files ) :
      name( std::move( _name ) ), size( std::move( _size ) ), embedded_files( std::move( _embedded_files ) )
    {}
  };

  struct package_manager
  {
   public:
    static void push( const package & );
    static const package * get( const std::string & name );
  };

  //struct package_list
  //{
  //  const erc::package & package;
  //  const package_list * const next;
  //
  //  inline package_list( const erc::package & _package, const package_list * const _next ) :
  //    package( std::move( _package ) ), next( std::move( _next ) )
  //  {}
  //};



  //const erc::package * find_package_from_package_list( const package_list & pl, const std::string & name );
  //
  //#if defined(ERC_MANAGER_MAIN_PACKAGE_LIST_EXIST) && (ERC_MANAGER_MAIN_PACKAGE_LIST_EXIST==1)
  //extern const package_list main_package_list;
  //
  //inline const erc::package * find_package( const std::string & name )
  //{ return find_package_from_package_list( main_package_list, name ); }
  //#endif


}

