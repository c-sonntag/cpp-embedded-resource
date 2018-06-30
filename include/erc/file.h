#pragma once

#include <erc/types.h>
#include <string>

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

  struct embedded_data
  {
    file_property file;
    //size_t offset;
    size_t size;
    char content_hash[12];
    bool compressed;

    inline embedded_data() = default;
    inline embedded_data(
      file_property _file,
      //size_t _offset,
      size_t _size,
      bool _compressed ) :
      file( std::move( _file ) ),
      //offset( std::move( _offset ) ),
      size( std::move( _size ) ),
      compressed( std::move( _compressed ) )
    {}
  };

  inline bool operator==( const embedded_data & lhs, const embedded_data & rhs )
  {
    return ( lhs.file == rhs.file ) &&
          // ( lhs.offset == rhs.offset ) &&
           ( lhs.size == rhs.size ) &&
           ( lhs.compressed == rhs.compressed );
  }

  inline bool operator!=( const embedded_data & lhs, const embedded_data & rhs )
  { return !( lhs == rhs );  }

}

