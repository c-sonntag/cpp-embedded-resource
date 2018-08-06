#include "./get_static_lib.hpp"

#include <erc/inventory_package.h>

static const erc::package_id package_erc_id( "source_info" );
static const erc::file_id source_info_erc_id( package_erc_id.from( "source_info.txt" ) );

const erc::package * get_static_lib()
{
  return erc::inventory_package::get().get_first_package( package_erc_id );
}

const erc::embedded_file * get_static_lib_source_info_file()
{
  return erc::inventory_package::get().get_first_embedded_file( source_info_erc_id );
}

