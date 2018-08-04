#include <erc/inventory_package.h>

#include <list>
#include <unordered_map>

#include <iostream>

namespace erc {

  static std::list<package_group> packages_groups;
  static std::unordered_map<std::string, package_group *> packages_groups_named;

  //std::list<package_group> inventory_package::packages_groups;
  //std::unordered_map<std::string, package_group *> inventory_package::packages_groups_named;

  void inventory_package::push( const package & pack )
  {
    std::cout << "[" << __TIME__ << "] inventory_package::push(name:" << pack.name << "; ref:" << &pack << ")" << std::endl;

    //
    packages_groups.emplace_back( pack );
    package_group & pg_inserted( packages_groups.back() );

    //
    auto find_it( packages_groups_named.find( pack.name ) );
    if ( find_it == packages_groups_named.end() )
    {
      packages_groups_named.emplace( pack.name, &pg_inserted );
      return;
    }

    //
    package_group * pg_last_next( find_it->second );
    for ( ; pg_last_next->next != nullptr; pg_last_next = pg_last_next->next );

    //
    pg_last_next->next = &pg_inserted;
  }

  // ---- ---- ---- ----

  const std::list<package_group> & inventory_package::get_packages()
  {
    return packages_groups;
  }

  // ---- ----

  const package_group * inventory_package::get_group( const std::string & name )
  {
    const auto find_it( packages_groups_named.find( name ) );
    return ( find_it == packages_groups_named.end() ) ? nullptr : find_it->second;
  }

  // ---- ---- ---- ----

  const erc::embedded_file * inventory_package::get_first_embedded_file( const file_id & id )
  {
    //
    const package_group * pg_p( get_group( id.package_name ) );
    if ( pg_p == nullptr )
      return nullptr;

    //
    for ( ; pg_p != nullptr; pg_p = pg_p->next )
    {
      const erc::embedded_file * const found_ef( pg_p->package.get_embedded_file( id.file_path ) );
      if ( found_ef )
        return found_ef;
    }
    return nullptr;
  }

  inventory_package::embedded_files inventory_package::get_embedded_files( const file_id & id )
  {
    //
    embedded_files efs;

    //
    const package_group * pg_p( get_group( id.package_name ) );
    if ( pg_p == nullptr )
      return efs;

    //
    for ( ; pg_p != nullptr; pg_p = pg_p->next )
    {
      const erc::embedded_file * const found_ef( pg_p->package.get_embedded_file( id.file_path ) );
      if ( found_ef )
        efs.emplace_back( found_ef );
    }
    return efs;
  }

  // ---- ---- ---- ----

  void inventory_package::debug_print( std::ostream & os, const bool print_properdata )
  {
    if ( packages_groups.empty() )
    {
      std::cout << "[erc:: inventory_package::debug_print] No Package" << std::endl;
      return;
    }

    std::cout << "[erc:: inventory_package::debug_print] Packages : " << std::endl;
    for ( const erc::package_group & pg : packages_groups )
    {
      const erc::package & package( pg.package );
      std::cout << "  Package name(" << package.name << ") : " << std::endl;
      const erc::embedded_file * const * const embedded_files( package.embedded_files );
      for ( unsigned int i( 0 ); i < package.size; ++i )
      {
        const erc::embedded_file & ef( *embedded_files[i] );
        std::cout << "    File id(" << i << ") : " << std::endl
                  << "      Path(" << ef.path << ")" << std::endl
                  << "      Compressed(" << std::boolalpha << ef.property.compressed << ") Raw(" << std::boolalpha << ef.property.raw_data << ")  Size(" << std::boolalpha << ef.property.size << ")" << std::endl
                  << "      Filename(" << std::boolalpha << ef.property.file.filename << ") RealSize(" << std::boolalpha << ef.property.file.size << ")" << std::endl;
        if ( print_properdata )
          std::cout << "      --- Data --- " << ef.get_proper_data() << std::endl
                    << "      --- EndData --- " << std::endl;
        std::cout << std::endl;
      }
    }
  }

}

