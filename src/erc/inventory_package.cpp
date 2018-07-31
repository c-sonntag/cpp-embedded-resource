#include <erc/inventory_package.h>

#include <list>
#include <unordered_map>

namespace erc {

  static std::list<package_group> packages_groups;
  static std::unordered_map<std::string, package_group *> packages_groups_named;

  void inventory_package::push( const package & pack )
  {
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
    for ( ; pg_p->next != nullptr; pg_p = pg_p->next )
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
    for ( ; pg_p->next != nullptr; pg_p = pg_p->next )
    {
      const erc::embedded_file * const found_ef( pg_p->package.get_embedded_file( id.file_path ) );
      if ( found_ef )
        efs.emplace_back( found_ef );
    }
    return efs;
  }

}

