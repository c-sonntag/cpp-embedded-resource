#include "./get_static_lib.hpp"

#include <erc/inventory_package.h>

const erc::package * get_static_lib()
{
  const erc::package_group * const pg_p( erc::inventory_package::get_group( "composed_ressource" ) );
  if ( !pg_p ) return nullptr;
  return &pg_p->package;
}

const erc::embedded_file * get_static_lib_source_info_file()
{
  const erc::package_group * const pg_p( erc::inventory_package::get_group( "source_info" ) );
  if ( !pg_p ) return nullptr;
  return pg_p->package.get_embedded_file( "source_info.txt" );
}
