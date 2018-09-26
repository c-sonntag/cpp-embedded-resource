#pragma once

#include <erc_maker/types.h>
#include <erc_maker/erc_inventory.h>
#include <erc_maker/erc_file_identifier.h>
#include <erc_maker/hash.h>

#include <erc_maker/cache_inventory_manager.h>

#include <string>
#include <vector>
#include <unordered_map>

namespace erc_maker {


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

      struct lock_file { std::string from, to; };
      std::vector<lock_file> lock_filepath_list;

      uint nb_generated = 0;
      uint nb_passed = 0;
    };

   public:
    const erc_inventory & inventory;

   private:
    inline hash256 make_hash_for( const erc_maker::file & file ) const;

   private:
    bool have_changement_file( const erc_file_identifier & input_file_id, const std::string & output );
    bool have_changement_package( const erc_prepared_package & input_pp, const std::string & output );
    bool have_changement_inventory();

   public:
    src_generator( const erc_inventory & _inventory );

   private:
    generation_rapport rapport;

   private:
    void generate_file( const erc_file_identifier & file_id, const std::string & output_src_file );
    void generate_package( const erc_prepared_package & pp, const std::string & output_src_file );
    void generate_inventory( const std::string & output_src_file );

   public:
    void open_caches_if_exists_into( const std::string & erc_working_directorypath );
    void save_caches_into( const std::string & erc_working_directorypath ) const;

   private:
    /**< @todo an file_cache_manager cound be apart */
    cache_inventory_manager inventory_cache;

   public:
    void generate_into( const  std::string & erc_output_directorypath, bool generated_list_only = false );
    const generation_rapport & get_rapport() const {return rapport;}


  };

}

