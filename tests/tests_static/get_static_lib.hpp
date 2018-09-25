#pragma once

#include <erc/package.h>

const erc::package * get_static_lib( const std::string & package_name );
const erc::embedded_file * get_static_lib_source_info_file();
