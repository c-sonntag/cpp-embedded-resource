#pragma once

#include <erc/file_id.h>
#include <erc/package.h>

#ifndef ERC_FROM_GENERATED_PACKAGE
#include <vector>
#endif

namespace erc {

  struct package_group
  {
    const erc::package & package;
    package_group * next;

    inline package_group( const erc::package & _package, package_group * _next = nullptr ) :
      package( std::move( _package ) ), next( std::move( _next ) )
    {}
  };

  struct inventory_package
  {
   public:
    static void push( const package & );
    static const package_group * get_group( const std::string & name );

    #ifndef ERC_FROM_GENERATED_PACKAGE
   public:
    using embedded_files = std::vector<const erc::embedded_file *>;

   public:
    static const erc::embedded_file * get_first_embedded_file( const file_id & id );
    static embedded_files get_embedded_files( const file_id & id );
    #endif
  };

}

