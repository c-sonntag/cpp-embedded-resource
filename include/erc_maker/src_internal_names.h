#pragma once

#include <erc_maker/erc_inventory.h>
#include <erc_maker/erc_file_identifier.h>

#include <list>
#include <vector>

namespace erc_maker {

  struct src_internal_names
  {
    static std::string global_namespace();

    static std::string to_extern_erc( const erc_file_identifier & sfi );
    static std::string to_extern_package( const erc_prepared_package & epp );
    static std::string to_extern_inventory( const erc_inventory & ei );

    static std::string to_file_erc( const erc_file_identifier & sfi );
    static std::string to_file_package( const erc_prepared_package & epp );
    static std::string to_file_inventory( const erc_inventory & ei );
    static std::string to_file_cache_inventory( const erc_inventory & ei );
  };

}

