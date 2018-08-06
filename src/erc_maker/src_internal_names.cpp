#include <erc_maker/src_internal_names.h>

namespace erc_maker {

  std::string src_internal_names::global_namespace()
  { return "generated_resources"; }

  // ---- ----

  std::string src_internal_names::to_extern_erc( const erc_file_identifier & sfi )
  { return "erc_" + sfi.file_unique_identifier.hex; }

  std::string src_internal_names::to_extern_package( const erc_prepared_package & epp )
  { return "pack_" + epp.package_unique_identifier.hex; }

  std::string src_internal_names::to_extern_inventory( const erc_inventory & ei )
  //{ return "inventory_" + ei.inventory_unique_identifier.hex; }
  //{ return "inventory_" + ei.inventory_name; }
  { return ei.inventory_name; }

  // ---- ----

  std::string src_internal_names::to_file_erc( const erc_file_identifier & sfi )
  { return to_extern_erc( sfi ) + ".cpp"; }

  std::string src_internal_names::to_file_package( const erc_prepared_package & epp )
  { return to_extern_package( epp ) + ".cpp"; }

  std::string src_internal_names::to_file_inventory( const erc_inventory & ei )
  { return to_extern_inventory( ei ) + ".cpp"; }

  std::string src_internal_names::to_file_cache_inventory( const erc_inventory & ei )
  { return to_extern_inventory( ei ) + ".cache"; }


}

