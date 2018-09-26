#pragma once

#include <erc_maker/erc_prepared_package.h>

#include <erc_maker/hash.h>
#include <erc_maker/custom_unordered_set.h>

#include <list>
#include <vector>

namespace erc_maker {

  using input_packages_filepaths_t = std::vector<std::string>;

  struct erc_file_identifier_p_getter
  {
    static inline const std::string & get( const erc_file_identifier * const efi_p )
    { return efi_p->file_unique_identifier.hex; }
  };

  struct erc_inventory
  {
   public:
    const input_packages_filepaths_t & input_packages_filepaths;
    const std::string inventory_name;

   public:
    using prepared_packages_t = std::list<erc_prepared_package>;
    const prepared_packages_t prepared_packages;
    //const hash256 inventory_unique_identifier;

   public:
    custom_unordered_set<std::string, const erc_file_identifier *, erc_file_identifier_p_getter> files_identifier_p;

   public:
    erc_inventory( const input_packages_filepaths_t & _input_packages_filepaths, const std::string _inventory_name );
  };

}

