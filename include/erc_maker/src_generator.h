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

  // ---- ----

  struct src_generator
  {
   public:
    struct generation_rapport
    {
      struct file_added { std::string file; bool generated; file_added() = default; };

      inline void insert( const std::string & file, const std::string & filepath, bool generated );
      inline void reset();

      std::vector<file_added> file_list;
      std::vector<file_added> filepath_list;
      uint nb_generated = 0;
      uint nb_passed = 0;
    };

   public:
    const erc_inventory & inventory;

   private:
    inline hash256 make_hash_for( const erc_maker::file & file ) const;

   public:
    src_generator( const erc_inventory & _inventory );

   private:
    generation_rapport rapport;

   private:
    void generate_file( const erc_file_identifier & file_id, const std::string & output_src_file );
    void generate_package( const erc_prepared_package & pp, const std::string & output_src_file );
    void generate_inventory( const std::string & output_src_file );

   public:
    void generate_into( const std::string & erc_output_directorypath, bool generated_list_only = false );
    const generation_rapport & get_rapport() const {return rapport;}

   private:
    std::unordered_map<hash_hex_string, file_cache_information> supplement_cache;

   public:
    void open_cache_if_exist_into( const std::string & erc_working_directorypath );
    void save_cache_into( const std::string & erc_working_directorypath ) const;

   private:
    inline bool cache_have_same_file( const erc_file_identifier & file_id ) const;

  };

}

