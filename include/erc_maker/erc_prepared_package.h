#pragma once

#include <erc_maker/types.h>
#include <erc_maker/erc_package_file_parser.h>
#include <erc_maker/erc_files_list.h>
#include <erc_maker/erc_file_identifier.h>

#include <erc_maker/hash.h>

#include <list>
#include <vector>
#include <memory>

namespace erc_maker {

  struct erc_prepared_package
  {
   public:
    const std::string package_filepath;
    const erc_package_file_parser package;
    const erc_files_list files;

   private:
    std::string generate_unique_identifier() const;
    hash256 make_hash_for( const erc_maker::file & file ) const;

   public:
    const hash256 package_unique_identifier;

   public:
    std::vector<erc_file_identifier> files_identifier;
    hash256 files_identifier_hash;

   public:
    erc_prepared_package( const std::string _input_package_filepath );
  };

}

