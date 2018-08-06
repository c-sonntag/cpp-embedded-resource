#pragma once

#include <erc_maker/types.h>
#include <erc_maker/erc_inventory.h>
#include <erc_maker/erc_file_identifier.h>
#include <erc_maker/hash.h>

#include <string>
#include <vector>
#include <unordered_map>

namespace erc_maker {

  struct file_cache_information
  {
    bool compress = false;
    uint size = 0;
    time_t last_modification = 0;

    inline file_cache_information() = default;
    inline file_cache_information( const erc_maker::file_property_found & fpf ) :
      compress( fpf.file.compress ),
      size( fpf.property.size ),
      last_modification( fpf.property.last_modification )
    {}
  };

  inline bool operator ==( const file_cache_information & fci, const file_property_found & fpf )
  {
    return ( fci.compress == fpf.file.compress ) &&
           ( fci.size == fpf.property.size ) &&
           ( fci.last_modification == fpf.property.last_modification );
  }

  /**< @todo an file_cache_manager cound be apart */

  struct cache_inventory_manager
  {
   public:
    const erc_inventory & inventory;
    const hash256 packages_absolutes_paths_hash;

   private:
    struct
    {
      hash256 packages_absolutes_paths_hash;
      std::unordered_map<hash_hex_string, file_cache_information> files;
    } cache;
    void reset_cache();

   public:
    cache_inventory_manager( const erc_inventory & _inventory );

   public:
    void open_if_exist_into( const std::string & erc_working_directorypath );
    void save_into( const std::string & erc_working_directorypath ) const;

   public:
    bool same_inventory() const;
    bool have_same_file( const erc_file_identifier & file_id ) const;

  };

}

