#include <erc/maker/src_generator.h>

#include <istream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <cstring>


namespace erc {
  namespace maker {

    static const char current_version_header[] { "CacheEmbeddedResourceLib v1.0" };

    // ---- ----

    template<typename T>
    inline T input_for( std::istream & is )
    {
      T in;
      is.read( reinterpret_cast<char *>( &in ), sizeof( T ) );
      return in;
    }

    void src_generator::open_cache_file( const std::string & erc_cache_filepath )
    {
      //
      supplement_cache.clear();

      //
      try
      {

        //
        std::ifstream input( erc_cache_filepath, std::ifstream::in );
        if ( !input )
          throw std::runtime_error( "can't open <erc_cache_filepath> at " + erc_cache_filepath );

        //
        char header_cstr[sizeof( current_version_header )] {0};
        input.read( header_cstr, sizeof( current_version_header ) );
        input.get(); // pass "\n"

        //
        if ( strncmp( header_cstr, current_version_header, sizeof( current_version_header ) ) != 0 )
          throw std::runtime_error( "Incompatible header version" );

        //
        const uint number_of_entries( input_for<uint>( input ) );

        //
        for ( uint i( 0 ); i < number_of_entries; ++i )
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
            throw std::runtime_error( "Entry with hash(" + entry_hash.hex + ") aleady exist in cache" );

          //
          supplement_cache.emplace( entry_hash.hex, entry_information );
        }

      }
      catch ( const std::exception & e )
      { throw std::runtime_error( "[embedded_rc::maker::src_generator::open_cache_file] " + std::string( e.what() ) ); }
    }

    // ---- ---- ---- ----

    template<typename T>
    inline void output_for( std::ostream & os, const T & out )
    {
      os.write( reinterpret_cast<const char *>( &out ), sizeof( T ) );
    }

    void src_generator::save_cache_file( const std::string & erc_cache_filepath ) const
    {
      //
      try
      {

        //
        std::ofstream output( erc_cache_filepath, std::ofstream::out | std::ofstream::trunc );
        if ( !output )
          throw std::runtime_error( "can't write <erc_cache_filepath> at " + erc_cache_filepath );

        //
        output << current_version_header << "\n";

        //
        output_for( output, erc_files_identifier.size() );

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
      { throw std::runtime_error( "[embedded_rc::maker::src_generator::save_cache_file] " + std::string( e.what() ) ); }

    }


  }
}
