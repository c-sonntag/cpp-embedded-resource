#pragma once

#include <erc_maker/types.h>

#include <string>

namespace erc_maker {

  using hash_hex_string = std::string;

  struct hash256
  {
   public:
    static hash256 from_hex_string( const hash_hex_string & hex );

   public:
    static constexpr uint hash_digest_size {32};
    byte digest[hash_digest_size] {0};

    static constexpr uint hash_hex_size {hash_digest_size * 2};
    hash_hex_string hex;

   public:
    inline hash256() = default;
    //hash256( const byte( &digested )[hash_digest_size] );
    //hash256( const byte digested[hash_digest_size] );

    hash256( const std::string & data );

   public:
    void generate_hash_hex_string();
    void generate_generate_digest();
  };


}

