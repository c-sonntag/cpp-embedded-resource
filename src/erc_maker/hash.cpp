#include <erc_maker/hash.h>

#include <cstring>
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

  // ---- ----

  bool operator==( const hash256 & lhs, const hash256 & rhs )
  {
    return memcmp( lhs.digest, rhs.digest, hash256::hash_digest_size ) == 0;
  }

  // ---- ---- ---- ----

  void hash256_digestor::operator()( const std::string & data )
  {
    digesting = digesting.hex + data; /** @todo improve better performance (using stream digestion or other) */
  }

  hash256 hash256_digestor::hash() const
  {
    return digesting;
  }



}

