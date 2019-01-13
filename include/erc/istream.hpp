#pragma once

#include <erc/classes/non_copyable_movable.hpp>

#include <bits/move.h>
#include <streambuf>
#include <istream>
#include <string>

namespace erc {

  /**
   * @see https://stackoverflow.com/a/13059195
   */
  struct membuf : std::streambuf
  {
   public:
    inline membuf( const char* const base, size_t size )
    {
      char* p( const_cast<char*>( base ) );
      this->setg( p, p, p + size );
    }

   public:
    inline membuf( membuf&& p ) = default;

   public:
    membuf( const membuf& ) = delete;
    membuf& operator =( const membuf& ) = delete;
  };

  /**
   * @see https://stackoverflow.com/a/13059195
   */
  struct imemstream : protected membuf, public std::istream
  {
   protected:
    inline imemstream( membuf&& b ) :
      membuf( std::move( b ) ),
      std::istream( static_cast<std::streambuf*>( this ) )
    {}

   public:
    inline imemstream( char const* base, size_t size ) :
      imemstream( membuf( base, size ) ) {}

    inline imemstream( const std::string& s ) :
      imemstream( membuf( s.data(), s.size() ) ) {}

   public:
    inline imemstream( imemstream&& p ) :
      membuf( std::move( dynamic_cast<membuf&&>( p ) ) ),
      std::istream( std::move( dynamic_cast<std::istream&&>( p ) ) )
    {}

   public:
    imemstream( const imemstream& ) = delete;
    imemstream& operator =( const imemstream& ) = delete;
  };

}
