#include "./get_shared_lib.hpp"

#include <erc/inventory_package.h>


const erc::package * get_shared_lib()
{
  return nullptr;
  //const erc::package_group * const pg_p( erc::inventory_package::get_group( "composed_ressource" ) );
  //if ( !pg_p ) return nullptr;
  //return &pg_p->package;
}


namespace erc {
  namespace generated_package {
    extern const erc::package pack_23584ec6c611217305b83264fd8f62ebdeb601203511ae646d8f4756e4bb19be;
  }
}

const erc::embedded_file * get_shared_lib_source_info_file()
{
  static const erc::file_id source_info_erc_id( "source_info", "source_info.txt" );
  return erc::inventory_package::get().get_first_embedded_file( source_info_erc_id );
}

