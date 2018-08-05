#include <erc/inventory_package.h>

#include <list>
#include <unordered_map>

#include <ostream>

namespace erc {

  // static std::list<package_group> packages_groups;
  // static std::unordered_map<std::string, package_group *> packages_groups_named;

  //std::list<package_group> inventory_package::packages_groups;
  //std::unordered_map<std::string, package_group *> inventory_package::packages_groups_named;

  //  void inventory_package::push( const package & pack )
  //  {
  //    std::cout << "[" << __TIME__ << "] inventory_package::push(name:" << pack.name << "; ref:" << &pack << ")" << std::endl;

  //    //
  //    packages_groups.emplace_back( pack );
  //    package_group & pg_inserted( packages_groups.back() );

  //    //
  //    auto find_it( packages_groups_named.find( pack.name ) );
  //    if ( find_it == packages_groups_named.end() )
  //    {
  //      packages_groups_named.emplace( pack.name, &pg_inserted );
  //      return;
  //    }

  //    //
  //    package_group * pg_last_next( find_it->second );
  //    for ( ; pg_last_next->next != nullptr; pg_last_next = pg_last_next->next );

  //    //
  //    pg_last_next->next = &pg_inserted;
  //  }

  // ---- ---- ---- ----

  //const std::list<package_group> & inventory_package::get_packages()
  //{
  //
  //  return packages_groups;
  //}

  // ---- ----
  //
  //const package_group * inventory_package::get_group( const std::string & name )
  //{
  //   return equal_range(name);
  //
  //  const auto find_it( packages_groups_named.find( name ) );
  //  return ( find_it == packages_groups_named.end() ) ? nullptr : find_it->second;
  //}

  // ---- ---- ---- ----

  const erc::package * inventory_package::get_first_package( const std::string & package_name ) const
  {
    const const_iterator find_it( find( package_name ) );
    return ( find_it == cend() ) ? nullptr : find_it->second;
  }

  inventory_package::packages inventory_package::get_packages( const std::string & package_name ) const
  {
    //
    packages ps;

    //
    const inventory_package_range ranges( get_range( package_name ) );
    if ( ranges.first == ranges.second )
      return ps;

    //
    for ( auto ranges_it( ranges.first ); ranges_it != ranges.second; ++ranges_it )
      ps.emplace_back( ranges_it->second );

    //
    return ps;
  }

  // ---- ---- ---- ----

  const erc::embedded_file * inventory_package::get_first_embedded_file( const std::string & package_name, const std::string & file_path ) const
  {
    const inventory_package_range ranges( get_range( package_name ) );
    if ( ranges.first == ranges.second )
      return nullptr;

    //
    for ( auto ranges_it( ranges.first ); ranges_it != ranges.second; ++ranges_it )
    {
      const erc::embedded_file * const found_ef( ranges_it->second->get_embedded_file( file_path ) );
      if ( found_ef )
        return found_ef;
    }

    //
    return nullptr;
  }

  inventory_package::embedded_files inventory_package::get_embedded_files( const std::string & package_name, const std::string & file_path ) const
  {
    //
    embedded_files efs;

    //
    const inventory_package_range ranges( get_range( package_name ) );
    if ( ranges.first == ranges.second )
      return efs;

    //
    for ( auto ranges_it( ranges.first ); ranges_it != ranges.second; ++ranges_it )
    {
      const erc::embedded_file * const found_ef( ranges_it->second->get_embedded_file( file_path ) );
      if ( found_ef )
        efs.emplace_back( found_ef );
    }

    //
    return efs;
  }

  // ---- ---- ---- ----

  void inventory_package::debug_print( std::ostream & os, const bool print_properdata ) const
  {
    if ( empty() )
    { os << "[erc::inventory_package::debug_print] No Package" << std::endl; return; }

    os << "[erc:: inventory_package::debug_print] Packages : " << std::endl;
    for ( const value_type & pack_pair : *this )
    {
      const erc::package & package( *pack_pair.second );
      os << "  Package name(" << package.name << ") : " << std::endl;
      const erc::embedded_file * const * const embedded_files( package.embedded_files );
      for ( unsigned int i( 0 ); i < package.size; ++i )
      {
        const erc::embedded_file & ef( *embedded_files[i] );
        os << "    File id(" << i << ") : " << std::endl
           << "      Path(" << ef.path << ")" << std::endl
           << "      Compressed(" << std::boolalpha << ef.property.compressed << ") Raw(" << std::boolalpha << ef.property.raw_data << ")  Size(" << std::boolalpha << ef.property.size << ")" << std::endl
           << "      Filename(" << std::boolalpha << ef.property.file.filename << ") RealSize(" << std::boolalpha << ef.property.file.size << ")" << std::endl;
        if ( print_properdata )
          os << "      --- Data --- " << ef.get_proper_data() << std::endl
             << "      --- EndData --- " << std::endl;
        os << std::endl;
      }
    }
  }

}

