#include <erc_maker/erc_inventory.h>

#include <iostream>

namespace erc_maker {

  //
  erc_inventory::erc_inventory( const input_packages_filepaths_t & _input_packages_filepaths, const std::string _inventory_name ) :
    input_packages_filepaths( std::move( _input_packages_filepaths ) ),
    inventory_name( std::move( _inventory_name ) ),
    prepared_packages( input_packages_filepaths.cbegin(), input_packages_filepaths.cend() )
    //inventory_unique_identifier( inventory_name )
  {
    for ( const erc_prepared_package & pp : prepared_packages )
      for ( const erc_file_identifier & file_id : pp.files_identifier )
        files_identifier_p.emplace( &file_id );
  }


  //erc_inventory::erc_inventory( const input_packages_filepaths_t & _input_packages_filepaths ) :
  //  input_packages_filepaths( std::move( _input_packages_filepaths ) ),
  //  prepared_packages( input_packages_filepaths.cbegin(), input_packages_filepaths.cend() )
  //{
  //  // for ( const std::string & input_packages_filepaths : input_packages_filepaths )
  //  //   prepared_packages.emplace_back( input_packages_filepaths );
  //}

}

