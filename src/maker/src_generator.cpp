#include <erc/maker/src_generator.h>

#include <picosha2.h>

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

namespace erc {
  namespace maker {

    hash256::hash256( const std::string & data )
    {
      picosha2::hash256( data.begin(), data.end(), digest, digest + hash_digest_size );
      std::ostringstream oss;
      picosha2::output_hex( digest, digest + hash_digest_size, oss );
      hex.assign( oss.str() );
    }

    // ---- ---- ---- ----

    inline hash256 src_generator::make_hash_for( const maker::file & file ) const
    {
      return hash256( package_unique_identifier.hex + "/" + file.path );
    }

    // ---- ----

    src_generator::src_generator( const erc_package_file_parser & _erc_package, const erc_files_list & _erc_files ) :
      erc_package( std::move( _erc_package ) ),
      erc_files( std::move( _erc_files ) ),
      package_unique_identifier( erc_package.content.package_name )
    {

      //
      for ( const std::pair<std::string, file_property_found> & ff_pair : erc_files.files_found )
        erc_files_identifier.emplace_back( ff_pair.second, make_hash_for( ff_pair.second.file ) );

    }

    // ---- ----

    void src_generator::generate_into( const std::string & erc_output_directorypath )
    {
      //
      static const fs::path erc_header_package_file( "package.hpp" );
      static const fs::path erc_package_file( "package.hpp" );

      //
      const fs::path output_directorypath( erc_output_directorypath );

      //
      for ( const src_file_identifier & file_id : erc_files_identifier )
      {

        //
        const fs::path erc_embedded_file( "erc_" + file_id.file_unique_identifier.hex + ".cpp" );
        const fs::path erc_embedded_filepath( erc_output_directorypath / erc_embedded_file );
        generates_filepath_list.emplace_back( erc_embedded_filepath.string() );

        //
        const bool embedded_file_already_exist( fs::exists( erc_embedded_filepath ) );
        const bool last_embedded_file_is_different_or_unknown( cache_have_same_file( file_id ) );

        //
        if ( last_embedded_file_is_different_or_unknown || !embedded_file_already_exist )
          generate_file( file_id, erc_embedded_filepath.string() );
      }

      //
      const fs::path erc_header_package_filepath( erc_output_directorypath / erc_header_package_file );
      generate_header_package( erc_header_package_filepath.string() );

      //
      const fs::path erc_package_filepath( erc_output_directorypath / erc_package_file );
      generates_filepath_list.emplace_back( erc_package_filepath.string() );
      generate_package( erc_package_filepath.string() );
    }

    // ---- ----

    inline bool src_generator::cache_have_same_file( const src_file_identifier & file_id ) const
    {
      //
      const auto find_it( supplement_cache.find( file_id.file_unique_identifier ) );
      if ( find_it == supplement_cache.end() )
        return false;

      //
      const file_cache_information & fci( find_it->second );
      return ( fci.size == file_id.valid_input_file.property.size ) &&
             ( fci.last_modification == file_id.valid_input_file.property.last_modification ) ;
    }


  }
}

