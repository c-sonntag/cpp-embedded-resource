#pragma once

#include <erc/package.h>

const erc::package * get_shared_lib( const std::string & package_name );
const erc::embedded_file * get_shared_lib_source_info_file();
