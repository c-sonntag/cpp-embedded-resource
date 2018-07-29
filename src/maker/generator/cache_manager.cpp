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
    static constexpr uint hash_str_length( 256 );

    // ---- ----

    inline uint input_for_uint( std::istream & is )
    {
      uint in( 0 );
      is.read( reinterpret_cast<char *>( &in ), sizeof( in ) );
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
          throw std::string( "can't open <erc_cache_filepath> at " + erc_cache_filepath );

        //
        char header_cstr[sizeof( current_version_header )] {0};
        input.read( header_cstr, sizeof( current_version_header ) );

        //
        if ( strncmp( header_cstr, current_version_header, sizeof( current_version_header ) ) != 0 )
          throw std::string( "Incompatible header version" );

        //
        const uint number_of_entries( input_for_uint( input ) );

        //
        for ( uint i( 0 ); i < number_of_entries; ++i )
        {
          //


        }

      }
      catch ( const std::string & s )
      { throw std::runtime_error( "[embedded_rc::maker::src_generator::open_cache_file] " + s ); }
    }

    // ---- ---- ---- ----



    // ---- ----

    void src_generator::save_cache_file( const std::string & erc_cache_filepath ) const
    {
      //
      try
      {

        //
        std::ofstream output( erc_cache_filepath, std::ofstream::out | std::ofstream::trunc );
        if ( !output )
          throw std::string( "can't write <erc_cache_filepath> at " + erc_cache_filepath );

        //
        output << current_version_header << std::endl;

        //
        file.write( reinterpret_cast<const char *>( &num ), sizeof( num ) );
        input

      }
      catch ( const std::string & s )
      { throw std::runtime_error( "[embedded_rc::maker::src_generator::save_cache_file] " + s ); }

    }


  }
}
