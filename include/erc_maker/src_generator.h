#pragma once

#include <erc_maker/types.h>
#include <erc_maker/erc_package_file_parser.h>
#include <erc_maker/erc_files_list.h>

#include <string>
#include <vector>
#include <unordered_map>

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

  // ---- ----

  struct file_cache_information
  {
    uint size = 0;
    time_t last_modification = 0;

    inline file_cache_information() = default;
    inline file_cache_information( const erc::file_property & fp ) :
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

  inline hash256 generate_package_identifier( const erc_package_file_parser & erc_package )
  {
    //return erc_package.erc_package_absolute_filepath;
    return erc_package.content.package_name;
  }

  // ---- ----

  struct src_generator
  {
   public:
    struct generation_rapport
    {
      struct file_added { std::string file; bool generated; file_added() = default; };

      inline void insert( const std::string & file, const std::string & filepath, bool generated );
      inline void reset();

      std::vector<file_added> file_list;
      std::vector<file_added> filepath_list;
      uint nb_generated = 0;
      uint nb_passed = 0;
    };

   private:
    struct internal_names
    {
      const src_generator & sg;
      inline internal_names( const src_generator & _sg );

      std::string to_extern_erc( const src_file_identifier & sfi ) const;
      std::string to_extern_package() const;

      std::string to_file_erc( const src_file_identifier & sfi ) const;
      std::string to_file_package_file() const;
      std::string to_file_cache_package_file() const;
    };

   public:
    const erc_package_file_parser & erc_package;
    const erc_files_list & erc_files;
    const hash256 package_unique_identifier;
    const internal_names names_generator;

   private:
    inline hash256 make_hash_for( const erc_maker::file & file ) const;

   private:
    std::vector<src_file_identifier> erc_files_identifier;

   public:
    src_generator( const erc_package_file_parser & _erc_package, const erc_files_list & _erc_files );

   private:
    generation_rapport rapport;

   private:
    void generate_file( const src_file_identifier & file_id, const std::string & output_src_file );
    void generate_header_package( const std::string output_src_file );
    void generate_package( const std::string & output_src_file );

   public:
    void generate_into( const std::string & erc_output_directorypath, bool generated_list_only = false );
    const generation_rapport & get_rapport() const {return rapport;}

   private:
    std::unordered_map<hash_hex_string, file_cache_information> supplement_cache;

   public:
    void open_cache_if_exist_into( const std::string & erc_working_directorypath );
    void save_cache_into( const std::string & erc_working_directorypath ) const;

   private:
    inline bool cache_have_same_file( const src_file_identifier & file_id ) const;

  };

}

