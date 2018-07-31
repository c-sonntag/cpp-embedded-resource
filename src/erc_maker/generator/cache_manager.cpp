#include <erc_maker/src_generator.h>

#include <erc_maker/file_system.h>

#include <istream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <cstring>


namespace erc_maker {

  static const char current_version_header[] { "CacheEmbeddedResourceLib v1.0\n" };
  static constexpr uint current_version_header_size { sizeof( current_version_header ) - 1 };

  // ---- ----

  template<typename T>
  inline T input_for( std::istream & is )
  {
    T in;
    is.read( reinterpret_cast<char *>( &in ), sizeof( T ) );
    return in;
  }

  void src_generator::open_cache_if_exist_into( const std::string & erc_working_directorypath )
  {
    //
    supplement_cache.clear();

    //
    const fs::path erc_cache_filepath_fs( fs::path( erc_working_directorypath ) / fs::path( names_generator.to_file_cache_package_file() ) );
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
      char header_cstr[current_version_header_size] {0};
      input.read( header_cstr, current_version_header_size );

      //
      if ( strncmp( header_cstr, current_version_header, current_version_header_size ) != 0 )
        throw std::runtime_error( "Incompatible header version" );

      //
      const uint32_t number_of_entries( input_for<uint32_t>( input ) );

      //
      for ( uint i( 0 ); i < number_of_entries && input.good(); ++i )
      {
        //
        hash256 entry_hash;
        input.read( reinterpret_cast<char *>( entry_hash.digest ), hash256::hash_digest_size );
        entry_hash.generate_hash_hex_string();

        //
        const file_cache_information entry_information( input_for<file_cache_information>( input ) );

        //
        const auto entry_already_exist_it( supplement_cache.find( entry_hash.hex ) );
        if ( entry_already_exist_it != supplement_cache.end() )
          throw std::runtime_error( "Entry with hash(" + entry_hash.hex + ") aleady exist in cache at entry number " + std::to_string( i ) );

        //
        supplement_cache.emplace( entry_hash.hex, entry_information );
      }

    }
    catch ( const std::exception & e )
    {
      supplement_cache.clear();
      throw std::runtime_error( "[embedded_rc::erc_maker::src_generator::open_cache_file] " + std::string( e.what() ) );
    }
  }

  // ---- ---- ---- ----

  template<typename T>
  inline void output_for( std::ostream & os, const T & out )
  {
    os.write( reinterpret_cast<const char *>( &out ), sizeof( T ) );
  }

  void src_generator::save_cache_into( const std::string & erc_working_directorypath ) const
  {

    //
    const std::string erc_cache_filepath(
      ( fs::path( erc_working_directorypath ) / fs::path( names_generator.to_file_cache_package_file() )
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
      output_for<uint32_t>( output, static_cast<uint32_t>(erc_files_identifier.size()) );

      //
      for ( const src_file_identifier & file_id : erc_files_identifier )
      {
        //
        output_for( output, file_id.file_unique_identifier.digest );

        //
        const file_cache_information entry_information( file_id.valid_input_file.property );
        output_for( output, entry_information );
      }
    }
    catch ( const std::exception & e )
    { throw std::runtime_error( "[embedded_rc::erc_maker::src_generator::save_cache_file] " + std::string( e.what() ) ); }

  }

}
