#include "./get_static_lib.hpp"

#include <erc/inventory_package.h>

//#include <iostream>

const erc::package * get_static_lib()
{
  //erc::inventory_package::get().debug_print( std::cout );
  return erc::inventory_package::get().get_first_package( "composed_ressource" );
}

const erc::embedded_file * get_static_lib_source_info_file()
{
  return erc::inventory_package::get().get_first_embedded_file( "source_info", "source_info.txt" );
}

