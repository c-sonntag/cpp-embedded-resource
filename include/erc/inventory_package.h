#pragma once

#include <erc/package.h>

#include <erc/file_id.h>
#include <erc/package_id.h>

//#ifndef ERC_FROM_GENERATED_PACKAGE
#include <list>
#include <vector>
#include <ostream>
#include <unordered_map>
#include <unordered_set>
//#endif

#include <iostream>

namespace erc {

  //using inventory = std::unordered_multimap<std::string, const erc::package *>;

  //struct inventory_package : public std::unordered_multimap<std::string, const erc::package *>
  //{
  //};

  // struct package_group
  // {
  //   const erc::package & package;
  //   package_group * next;
  //
  //   inline package_group( const erc::package & _package, package_group * _next = nullptr ) :
  //     package( std::move( _package ) ), next( std::move( _next ) )
  //   {}
  // };

  // #ifndef ERC_FROM_GENERATED_PACKAGE
  // static std::list<package_group> packages_groups;
  // static std::unordered_map<std::string, package_group *> packages_groups_named;
  // #endif

  #ifdef ERC_INVENTORY_PACKAGE_EXTERN_NAME
  struct inventory_package;
  namespace generated_resources { extern const erc::inventory_package ERC_INVENTORY_PACKAGE_EXTERN_NAME;  }
  #endif

  using inventory_package_map = std::unordered_multimap<std::string, const erc::package *>;

  struct inventory_package : inventory_package_map
  {
   public:
    #ifdef ERC_INVENTORY_PACKAGE_EXTERN_NAME
    static __forceinline constexpr const inventory_package & get() {
      return ::erc::generated_resources::ERC_INVENTORY_PACKAGE_EXTERN_NAME;
    }
    #endif

   public:
    using inventory_package_map::inventory_package_map;
    using inventory_package_range = std::pair<const_iterator, const_iterator>;

   public:
    //static void push( const package & );
    inline inventory_package_range get_range( const std::string & name ) const
    { return equal_range( name ); }

    // #ifndef ERC_FROM_GENERATED_PACKAGE
    //private:
    // static std::list<package_group> packages_groups;
    // static std::unordered_map<std::string, package_group *> packages_groups_named;

    //public:
    // const std::list<package_group> & get_packages();

   public:
    using packages = std::vector<const erc::package *>;
    using embedded_files = std::vector<const erc::embedded_file *>;

   public:
    const erc::package * get_first_package( const std::string & package_name ) const;
    packages get_packages( const std::string & package_name ) const;

   public:
    const erc::embedded_file * get_first_embedded_file( const std::string & package_name, const std::string & file_path ) const;
    embedded_files get_embedded_files( const std::string & package_name, const std::string & file_path ) const;

   public:
    inline const erc::package * get_first_package( const package_id & id ) const {return get_first_package( id.package_name ); }
    inline packages get_packages( const package_id & id ) const {return get_packages( id.package_name ); }

    inline const erc::embedded_file * get_first_embedded_file( const file_id & id ) const {return get_first_embedded_file( id.package_name, id.file_path ); }
    inline embedded_files get_embedded_files( const file_id & id ) const {return get_embedded_files( id.package_name, id.file_path ); }

   public:
    void debug_print( std::ostream & os, const bool print_properdata = false ) const;
    //#endif
  };


}

