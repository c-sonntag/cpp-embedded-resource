#include "./get_shared_lib.hpp"

#include <erc/inventory_package.h>

//#include <iostream>

const erc::package * get_shared_lib( const std::string & package_name )
{
  //erc::inventory_package::get().debug_print( std::cout );
  return erc::inventory_package::get().get_first_package( package_name );
}

const erc::embedded_file * get_shared_lib_source_info_file()
{
  return erc::inventory_package::get().get_first_embedded_file( "source_info", "source_info.txt" );
}

