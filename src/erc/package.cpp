#include <erc/package.h>

namespace erc {

  const erc::package * find_package_from_package_list( const package_list & pl, const std::string & name )
  {
    for ( const package_list * pl_p( &pl ); pl_p != nullptr; pl_p = pl_p->next )
      if ( pl_p->package.name == name )
        return &pl_p->package;
    return nullptr;
  }

}

