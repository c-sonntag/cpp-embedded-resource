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

   public:
    const hash256 package_unique_identifier;

   private:
    inline hash256 make_hash_for( const erc_maker::file & file ) const
    { return hash256( package_unique_identifier.hex + ":" + file.path ); }

   public:
    std::vector<erc_file_identifier> files_identifier;

   private:
    inline std::string generate_unique_identifier() const
    { return package.erc_package_absolute_filepath + ":" + package.content.package_name; }

   public:
    inline erc_prepared_package( const std::string _input_package_filepath ) :
      package_filepath( std::move( _input_package_filepath ) ),
      package( package_filepath ),
      files( package ),
      package_unique_identifier( generate_unique_identifier() ) {
      //
      files_identifier.reserve( files.files_found.size() );
      for ( const std::pair<std::string, file_property_found> & ff_pair : files.files_found )
        files_identifier.emplace_back( ff_pair.second, make_hash_for( ff_pair.second.file ) );
    }
  };

}

