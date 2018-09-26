#include <erc_maker/cache_inventory_manager.h>

#include <erc_maker/file_system.h>
#include <erc_maker/src_internal_names.h>

#include <istream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <cstring>

#define CACHE_FOR_FILE 0

namespace erc_maker {


  static const std::string current_version_header( "CacheEmbeddedResourceLib v1.0 - " + std::string( __DATE__ ) + " - " + std::string( __TIME__ ) + " \n" );

  // ---- ---- ---- ----

  static inline hash256 generate_packages_absolutes_paths_hash( const erc_inventory & inventory )
  {
    hash256_digestor digestor;
    for ( const erc_prepared_package & pp : inventory.prepared_packages )
      digestor( pp.package.erc_package_absolute_filepath );
    return digestor.hash();
  }

  cache_inventory_manager::cache_inventory_manager( const erc_inventory & _inventory )  :
    inventory( std::move( _inventory ) ),
    packages_absolutes_paths_hash( generate_packages_absolutes_paths_hash( inventory ) )
  {}

  // ---- ---- ---- ----

  bool cache_inventory_manager::same_inventory( const erc_inventory::prepared_packages_t & pps ) const
  {
    //C
    if ( packages_absolutes_paths_hash != cache.packages_absolutes_paths_hash )
      return false;

    //
    for ( const erc_prepared_package & pp : pps )
      if ( !have_same_package_files( pp ) )
        return false;

    //
    return true;
  }

  bool cache_inventory_manager::have_same_package_files( const erc_prepared_package & pp ) const
  {
    const auto find_it( cache.packages_files_identifier_hash.find( pp.files_identifier_hash.hex ) );
    return ( find_it != cache.packages_files_identifier_hash.end() );;
  }

  //  bool cache_inventory_manager::have_same_file( const erc_file_identifier & file_id ) const
  //  {
  //    //
  //    const auto find_it( cache.files.find( file_id.file_unique_identifier.hex ) );
  //    if ( find_it == cache.files.end() )
  //      return false;
  //    //
  //    return find_it->second == file_id.valid_input_file;
  //  }

  // ---- ---- ---- ----

  void cache_inventory_manager::reset_cache()
  {
    cache.packages_absolutes_paths_hash = hash256();
    cache.files.clear();
    cache.packages_files_identifier_hash.clear();
  }

  // ---- ---- ---- ----

  /** @todo SET cache for an folder
   *        need read/write blocking acces
   */

  // ---- ----

  template<typename T>
  inline T input_for( std::istream & is )
  {
    T in;
    is.read( reinterpret_cast<char *>( &in ), sizeof( T ) );
    return in;
  }

  void cache_inventory_manager::open_if_exist_into( const std::string & erc_working_directorypath )
  {
    //
    reset_cache();

    //
    const fs::path erc_cache_filepath_fs( fs::path( erc_working_directorypath ) / fs::path( src_internal_names::to_file_cache_inventory( inventory ) ) );
    if ( !fs::exists( erc_cache_filepath_fs ) )
      return;

    //
    const std::string erc_cache_filepath( erc_cache_filepath_fs.string() );

    //
    try
    {

      //
      std::ifstream input( erc_cache_filepath, std::ifstream::in | std::ifstream::binary );
      if ( !input )
        throw std::runtime_error( "can't open <erc_cache_filepath> at " + erc_cache_filepath );

      //
      std::vector<char> version_header_vec( current_version_header.size(), '\0' );
      input.read( version_header_vec.data(), static_cast<std::streamsize>( current_version_header.size() ) );
      const std::string version_header( version_header_vec.data(), current_version_header.size() );

      //
      if ( version_header != current_version_header )
        throw std::runtime_error( "Incompatible header version" );

      //
      input.read( reinterpret_cast<char *>( cache.packages_absolutes_paths_hash.digest ), hash256::hash_digest_size );
      cache.packages_absolutes_paths_hash.generate_hash_hex_string();

      //
      {
        const uint32_t number_of_packages_entries( input_for<uint32_t>( input ) );
        for ( uint i( 0 ); i < number_of_packages_entries && input.good(); ++i )
        {
          //
          hash256 entry_hash;
          input.read( reinterpret_cast<char *>( entry_hash.digest ), hash256::hash_digest_size );
          entry_hash.generate_hash_hex_string();

          //
          const auto entry_already_exist_it( cache.packages_files_identifier_hash.find( entry_hash.hex ) );
          if ( entry_already_exist_it != cache.packages_files_identifier_hash.end() )
            throw std::runtime_error( "PackageEntry with hash(" + entry_hash.hex + ") aleady exist in cache at entry number " + std::to_string( i ) );

          //
          cache.packages_files_identifier_hash.emplace( entry_hash.hex );
        }
      }

      //
      #if CACHE_FOR_FILE == 1
      {
        const uint32_t number_of_files_entries( input_for<uint32_t>( input ) );
        for ( uint i( 0 ); i < number_of_files_entries && input.good(); ++i )
        {
          //
          hash256 entry_hash;
          input.read( reinterpret_cast<char *>( entry_hash.digest ), hash256::hash_digest_size );
          entry_hash.generate_hash_hex_string();

          //
          const file_cache_information entry_information( input_for<file_cache_information>( input ) );

          //
          const auto entry_already_exist_it( cache.files.find( entry_hash.hex ) );
          if ( entry_already_exist_it != cache.files.end() )
            throw std::runtime_error( "FileEntry with hash(" + entry_hash.hex + ") aleady exist in cache at entry number " + std::to_string( i ) );

          //
          cache.files.emplace( entry_hash.hex, entry_information );
        }
      }
      #endif

    }
    catch ( const std::exception & e )
    {
      reset_cache();
      throw std::runtime_error( "[embedded_rc::erc_maker::cache_inventory_manager::open_cache_file] " + std::string( e.what() ) );
    }
  }

  // ---- ---- ---- ----

  template<typename T>
  inline void output_for( std::ostream & os, const T & out )
  {
    os.write( reinterpret_cast<const char *>( &out ), sizeof( T ) );
  }

  void cache_inventory_manager::save_into( const std::string & erc_working_directorypath ) const
  {

    //
    const std::string erc_cache_filepath(
      ( fs::path( erc_working_directorypath ) / fs::path( src_internal_names::to_file_cache_inventory( inventory ) )
      ).string()
    );


    //
    try
    {

      //
      std::ofstream output( erc_cache_filepath, std::ofstream::out | std::ofstream::trunc | std::ofstream::binary );
      if ( !output )
        throw std::runtime_error( "can't write <erc_cache_filepath> at " + erc_cache_filepath );

      //
      output << current_version_header;

      //
      output_for( output, packages_absolutes_paths_hash.digest );

      //
      output_for<uint32_t>( output, static_cast<uint32_t>( inventory.prepared_packages.size() ) );
      for ( const erc_prepared_package & pp : inventory.prepared_packages )
        output_for( output, pp.files_identifier_hash.digest );

      //
      #if CACHE_FOR_FILE == 1
      output_for<uint32_t>( output, static_cast<uint32_t>( inventory.files_identifier_p.size() ) );
      for ( const erc_file_identifier * const file_id : inventory.files_identifier_p )
      {
        output_for( output, file_id->file_unique_identifier.digest );
        const file_cache_information entry_information( file_id->valid_input_file );
        output_for( output, entry_information );
      }
      #endif
    }
    catch ( const std::exception & e )
    { throw std::runtime_error( "[embedded_rc::erc_maker::cache_inventory_manager::save_cache_file] " + std::string( e.what() ) ); }

  }

}
