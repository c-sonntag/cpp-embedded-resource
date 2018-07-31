#include <erc_maker/src_generator.h>
#include <erc_maker/file_system.h>

#include <cstring>
#include <stdexcept>

#include <picosha2.h>

namespace erc_maker {

  hash256 hash256::from_hex_string( const hash_hex_string & hex )
  {
    hash256 hash;
    hash.hex = hex;
    hash.generate_generate_digest();
    return hash;
  }

 // hash256::hash256( const byte( &digested )[hash_digest_size] )
 // {
 //   memcpy( digest, digested, hash_digest_size );
 //   generate_hash_hex_string();
 // }

  hash256::hash256( const std::string & data )
  {
    picosha2::hash256( data.begin(), data.end(), digest, digest + hash_digest_size );
    generate_hash_hex_string();
  }

  void hash256::generate_hash_hex_string()
  {
    std::ostringstream oss;
    picosha2::output_hex( digest, digest + hash_digest_size, oss );
    hex.assign( oss.str() );
  }

  void hash256::generate_generate_digest()
  {
    //
    if ( hex.size() != hash_hex_size )
      throw std::runtime_error( "[hash256] Incompatible hash_hex_string size " + std::to_string( hex.size() ) );
    const char * hex_cstr( hex.c_str() );

    //
    for ( uint i( 0 ); i < hash_digest_size; ++i )
    {
      const std::string byte_hex( hex_cstr + i, 2 );
      const int byte_converted( std::stoi( byte_hex, nullptr, 16 ) );
      digest[i] = static_cast<byte>( byte_converted );
    }
  }

  // ---- ---- ---- ----

  inline void src_generator::generation_rapport::insert( const std::string & file, const std::string & filepath, bool generated )
  {
    file_list.emplace_back( file_added{file, generated} );
    filepath_list.emplace_back( file_added{filepath, generated} );
    if ( generated ) ++nb_generated;
    else             ++nb_passed;
  }

  inline void src_generator::generation_rapport::reset()
  {
    file_list.clear();
    filepath_list.clear();
    nb_generated = 0;
    nb_passed = 0;
  }


  // ---- ---- ---- ----

  inline src_generator::internal_names::internal_names( const src_generator & _sg ) :
    sg( _sg )
  {}

  // ---- ----

  std::string src_generator::internal_names::to_extern_erc( const src_file_identifier & sfi ) const
  { return "erc_" + sfi.file_unique_identifier.hex; }

  std::string src_generator::internal_names::to_extern_package() const
  { return "pack_" + sg.package_unique_identifier.hex; }

  // ---- ----

  std::string src_generator::internal_names::to_file_erc( const src_file_identifier & sfi ) const
  { return to_extern_erc( sfi ) + ".cpp"; }

  std::string src_generator::internal_names::to_file_package_file() const
  { return to_extern_package() + ".cpp"; }

  std::string src_generator::internal_names::to_file_cache_package_file() const
  { return to_extern_package() + ".cache"; }

  // ---- ---- ---- ----

  inline hash256 src_generator::make_hash_for( const erc_maker::file & file ) const
  {
    return hash256( package_unique_identifier.hex + ":" + file.path );
  }

  // ---- ----

  src_generator::src_generator( const erc_package_file_parser & _erc_package, const erc_files_list & _erc_files ) :
    erc_package( std::move( _erc_package ) ),
    erc_files( std::move( _erc_files ) ),
    package_unique_identifier( generate_package_identifier( erc_package ) ),
    names_generator( *this )
  {

    //
    for ( const std::pair<std::string, file_property_found> & ff_pair : erc_files.files_found )
      erc_files_identifier.emplace_back( ff_pair.second, make_hash_for( ff_pair.second.file ) );

  }

  // ---- ----

  void src_generator::generate_into( const std::string & erc_output_directorypath, bool generated_list_only )
  {

    //
    rapport.reset();

    //
    const fs::path output_directorypath( erc_output_directorypath );

    //
    bool new_erc_embedded( false );

    //
    for ( const src_file_identifier & file_id : erc_files_identifier )
    {
      //
      const std::string erc_embedded_file_str( names_generator.to_file_erc( file_id ) );
      const fs::path erc_embedded_filepath( output_directorypath / fs::path( erc_embedded_file_str ) );

      //
      const bool not_exist( !fs::exists( erc_embedded_filepath ) );
      if ( not_exist ) new_erc_embedded = true;

      //
      const bool need_generate( !cache_have_same_file( file_id ) || not_exist );
      rapport.insert( erc_embedded_file_str, generic_string_path( erc_embedded_filepath ), need_generate );

      //
      if ( !generated_list_only && need_generate )
        generate_file( file_id, erc_embedded_filepath.string() );
    }

    {
      //
      const std::string erc_package_file_str( names_generator.to_file_package_file() );
      const fs::path erc_package_filepath( output_directorypath / fs::path( erc_package_file_str ) );

      //
      const bool need_generate( !fs::exists( erc_package_filepath ) || new_erc_embedded );
      rapport.insert( erc_package_file_str, generic_string_path( erc_package_filepath ), need_generate );

      //
      if ( !generated_list_only && need_generate )
        generate_package( erc_package_filepath.string() );
    }
  }

  // ---- ----

  inline bool src_generator::cache_have_same_file( const src_file_identifier & file_id ) const
  {
    //
    const auto find_it( supplement_cache.find( file_id.file_unique_identifier.hex ) );
    if ( find_it == supplement_cache.end() )
      return false;

    //
    const file_cache_information & fci( find_it->second );
    return ( fci.size == file_id.valid_input_file.property.size ) &&
           ( fci.last_modification == file_id.valid_input_file.property.last_modification ) ;
  }

}

