#include <erc_maker/erc_prepared_package.h>

namespace erc_maker {


  std::string erc_prepared_package::generate_unique_identifier() const
  { return package.erc_package_absolute_filepath + ":" + package.content.package_name; }

  hash256 erc_prepared_package::make_hash_for( const erc_maker::file & file ) const
  { return hash256( package_unique_identifier.hex + ":" + file.hash().hex ); }

  // ---- ----

  erc_prepared_package::erc_prepared_package( const std::string _input_package_filepath ) :
    package_filepath( std::move( _input_package_filepath ) ),
    package( package_filepath ),
    files( package ),
    package_unique_identifier( generate_unique_identifier() )
  {
    {
      files_identifier.reserve( files.files_found.size() );
      for ( const std::pair<std::string, file_property_found> & ff_pair : files.files_found )
        files_identifier.emplace_back( ff_pair.second, make_hash_for( ff_pair.second.file ) );
    }
    {
      hash256_digestor digestor;
      digestor( package_unique_identifier.hex + ":" );
      for ( const erc_file_identifier & efi : files_identifier )
        digestor( efi.file_unique_identifier.hex );
      files_identifier_hash = digestor.hash();
    }

  }


  //erc_inventory::erc_inventory( const input_packages_filepaths_t & _input_packages_filepaths ) :
  //  input_packages_filepaths( std::move( _input_packages_filepaths ) ),
  //  prepared_packages( input_packages_filepaths.cbegin(), input_packages_filepaths.cend() )
  //{
  //  // for ( const std::string & input_packages_filepaths : input_packages_filepaths )
  //  //   prepared_packages.emplace_back( input_packages_filepaths );
  //}

}

