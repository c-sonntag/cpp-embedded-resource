#pragma once

#include <erc/types.h>

#include <erc/maker/erc_package_file_parser.h>
#include <erc/maker/erc_files_list.h>

#include <string>
#include <vector>
#include <unordered_map>

namespace erc {
  namespace maker {

    using hash_hex_string = std::string;

    struct hash256
    {
     public:
      static hash256 from_hex_string( const hash_hex_string & hex );

     public:
      static constexpr uint hash_digest_size {32};
      byte digest[hash_digest_size];

      static constexpr uint hash_hex_size {hash_digest_size * 2};
      hash_hex_string hex;

     public:
      inline hash256() = default;
      hash256( const byte( &digested )[hash_digest_size] );
      hash256( const byte digested[hash_digest_size] );

      hash256( const std::string & data );

     public:
      void generate_hash_hex_string();
      void generate_generate_digest();
    };

    // ---- ----

    struct file_cache_information
    {
      uint size = 0;
      std::time_t last_modification = 0;

      inline file_cache_information() = default;
      inline file_cache_information( const file_property & fp ) :
        size( fp.size ), last_modification( fp.last_modification )
      {}
      //inline file_cache_information( uint _size, std::time_t _last_modification ) :
      //  size( std::move( _size ) ), last_modification( std::move( _last_modification ) )
      //{}
    };

    struct src_file_identifier
    {
      const file_property_found valid_input_file;
      const hash256 file_unique_identifier;

      inline src_file_identifier() = default;
      inline src_file_identifier( const file_property_found _valid_input_file, const hash256 _file_unique_identifier ) :
        valid_input_file( std::move( _valid_input_file ) ),
        file_unique_identifier( std::move( _file_unique_identifier ) )
      {}
    };

    // ---- ----

    struct src_generator
    {
     public:
      const erc_package_file_parser & erc_package;
      const erc_files_list & erc_files;
      const hash256 package_unique_identifier;

     private:
      inline hash256 make_hash_for( const maker::file & file ) const;

     private:
      std::vector<src_file_identifier> erc_files_identifier;

     public:
      src_generator( const erc_package_file_parser & _erc_package, const erc_files_list & _erc_files );

     private:
      std::vector<std::string> generates_filepath_list;

     private:
      void generate_file( const src_file_identifier & file_id, const std::string & output_src_file );
      void generate_header_package( const std::string output_src_file );
      void generate_package( const std::string & output_src_file );

     public:
      void generate_into( const std::string & erc_output_directorypath );
      const std::vector<std::string> & get_generates_filepath_list() const;

     private:
      std::unordered_map<hash_hex_string, file_cache_information> supplement_cache;

     public:
      void open_cache_file( const std::string & erc_cache_filepath );
      void save_cache_file( const std::string & erc_cache_filepath ) const;

     private:
      inline bool cache_have_same_file( const src_file_identifier & file_id ) const;

    };

  }
}

