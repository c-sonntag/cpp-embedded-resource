#include "./get_static_lib.hpp"

#include <erc/inventory_package.h>

#include <iostream>

//#include <pack_23584ec6c611217305b83264fd8f62ebdeb601203511ae646d8f4756e4bb19be.h>

//namespace erc {
//  namespace generated_package {
//    //  extern const erc::package pack_8cff6884e39a8c83a2d3550b959a6e8946e09a3f292d261da948475d8e5c2ebf;
//    extern const erc::package source_info;
//  }
//}


const erc::package * get_static_lib()
{
  return nullptr;
  //const erc::package_group * const pg_p( erc::inventory_package::get_group( "composed_ressource" ) );
  //if ( !pg_p ) return nullptr;
  //return &pg_p->package;
}

#define xstr(s) str(s)
#define str(s) #s

namespace erc {
  namespace generated_package {
    extern const erc::package pack_23584ec6c611217305b83264fd8f62ebdeb601203511ae646d8f4756e4bb19be;
  }
}

const erc::embedded_file * get_static_lib_source_info_file()
{
  static const erc::file_id source_info_erc_id( "source_info-static", "source_info.txt" );
  return erc::inventory_package::get().get_first_embedded_file( source_info_erc_id );
}

