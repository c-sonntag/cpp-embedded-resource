#pragma once

#include <erc/types.h>
#include <string>
#include <cstring>

namespace erc {

  struct file_property
  {
    std::string filename;
    std::string extension;
    size_t size;

    inline file_property() = default;
    inline file_property( std::string _filename, std::string _extension, size_t _size ) :
      filename( _filename ), extension( std::move( _extension ) ), size( std::move( _size ) )
    {}
  };

  inline bool operator==( const file_property & lhs, const file_property & rhs )
  {
    return ( lhs.filename == rhs.filename ) &&
           ( lhs.extension == rhs.extension ) &&
           ( lhs.size == rhs.size );
  }

  inline bool operator!=( const file_property & lhs, const file_property & rhs )
  { return !( lhs == rhs );  }

  // ---- ----

  struct embedded_data_property
  {
    file_property file;
    //size_t offset;
    size_t size;
    //char content_hash[12];
    bool compressed;
    bool raw_data;

    inline embedded_data_property() = default;
    inline embedded_data_property(
      file_property _file,
      //size_t _offset,
      size_t _size,
      bool _compressed,
      bool _raw_data ) :
      file( std::move( _file ) ),
      //offset( std::move( _offset ) ),
      size( std::move( _size ) ),
      compressed( std::move( _compressed ) ),
      raw_data( std::move( _raw_data ) )
    {}
  };

  inline bool operator==( const embedded_data_property & lhs, const embedded_data_property & rhs )
  {
    return ( lhs.file == rhs.file ) &&
           // ( lhs.offset == rhs.offset ) &&
           ( lhs.size == rhs.size ) &&
           ( lhs.compressed == rhs.compressed ) &&
           ( lhs.raw_data == rhs.raw_data );
  }

  inline bool operator!=( const embedded_data_property & lhs, const embedded_data_property & rhs )
  { return !( lhs == rhs );  }

  // ---- ----

  struct embedded_file
  {
    const std::string path;
    const embedded_data_property property;
    const unsigned char * const data;

    inline embedded_file() = default;
    inline embedded_file( std::string _path, embedded_data_property _property, const unsigned char * const _data ) :
      path( _path ), property( std::move( _property ) ), data( std::move( _data ) )
    {}
  };

  inline bool operator==( const embedded_file & lhs, const embedded_file & rhs )
  {
    bool same_data( false );

    if ( ( lhs.data == nullptr ) || ( rhs.data == nullptr ) )
      same_data = true;
    else if ( lhs.property.size != rhs.property.size )
      same_data = false;
    else if ( ( lhs.data != nullptr ) && ( rhs.data != nullptr ) )
      same_data = ( std::memcmp( lhs.data, rhs.data, lhs.property.size ) == 0 );

    if ( !same_data )
      return false;

    return ( lhs.path == rhs.path ) &&
           ( lhs.property == rhs.property );
  }

  inline bool operator!=( const embedded_file & lhs, const embedded_file & rhs )
  { return !( lhs == rhs );  }

}

