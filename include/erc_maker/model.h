#pragma once

#include <erc_maker/hash.h>

#include <string>
#include <vector>
#include <regex>

namespace erc_maker {

  struct basic_link
  {
    bool compress = false;
    /**< @todo bool encrypted = false;   */
    std::string path;
    std::string prefix;

    inline basic_link() = default;
    inline basic_link( const std::string _path, bool _compress = false, const std::string _prefix = "" ) :
      compress( _compress ), path( std::move( _path ) ), prefix( std::move( _prefix ) )
    {}

    inline virtual hash256 hash() const
    { return prefix + "/" + path + ":" + ( compress ? "1" : "0" ); }
  };

  inline bool operator==( const basic_link & lhs, const basic_link & rhs )
  { return ( lhs.path == rhs.path ) && ( lhs.compress == rhs.compress ) && ( lhs.prefix == rhs.prefix );  }

  inline bool operator!=( const basic_link & lhs, const basic_link & rhs )
  { return !( lhs == rhs );  }

  // ---- ----

  struct file : public basic_link
  {
    using basic_link::basic_link;
    // inline file() = default;
    inline file( const basic_link & bl ) : basic_link( bl ) {}
  };

  // ---- ----

  struct directory : public basic_link
  {
   public:
    struct regex_tag
    {
      bool set = false;
      std::string str;
      std::regex rgx;
    };

   public:
    regex_tag regex_patern;
    regex_tag regex_extension;

   public:
    using basic_link::basic_link;
    inline directory() = default;
    inline directory( const basic_link & bl ) : basic_link( bl ) {}

   public:
    inline virtual hash256 hash() const
    { return basic_link::hash().hex + ":" + regex_patern.str + ":" + regex_extension.str; }
  };

  inline bool operator==( const directory & lhs, const directory & rhs )
  {
    return ( dynamic_cast<const basic_link &>( lhs ) == dynamic_cast<const basic_link &>( rhs ) ) &&
           ( lhs.regex_patern.str == rhs.regex_patern.str ) &&
           ( lhs.regex_patern.str == rhs.regex_patern.str );
  }

  inline bool operator!=( const directory & lhs, const directory & rhs )
  { return !( lhs == rhs );  }

  // ---- ----

  struct model
  {
    std::string package_name;
    std::string prefix;
    std::vector<file> files;
    std::vector<directory> directories;
  };

  inline bool operator==( const model & lhs, const model & rhs )
  {
    return ( lhs.package_name == rhs.package_name ) &&
           ( lhs.prefix == rhs.prefix ) &&
           ( lhs.files == rhs.files ) &&
           ( lhs.directories == rhs.directories );
  }

  inline bool operator!=( const model & lhs, const model & rhs )
  { return !( lhs == rhs );  }

}

