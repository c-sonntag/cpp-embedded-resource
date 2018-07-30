#include <erc/package.h>

#include <vector>

namespace erc {

  //const erc::package * find_package_from_package_list( const package_list & pl, const std::string & name )
  //{
  //  for ( const package_list * pl_p( &pl ); pl_p != nullptr; pl_p = pl_p->next )
  //    if ( pl_p->package.name == name )
  //      return &pl_p->package;
  //  return nullptr;
  //}

  static std::vector<const package *> packages;

  void package_manager::push( const package & pack )
  {
    packages.emplace_back( &pack );
  }

  const package * package_manager::get( const std::string & name )
  {
    for ( const package * p_p : packages )
      if ( p_p->name == name )
        return p_p;
    return nullptr;
  }


}

