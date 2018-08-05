/**
* @brief Generated file for EmbeddedResource lib.
* @note Package file can be found at
*       tests_static/source_info.erc
*/

//#define ERC_FROM_GENERATED_PACKAGE 1
#include <erc/inventory_package.h>

#define for_map(pack) {pack.name, &pack}

namespace erc {

  namespace generated_package {
    extern erc::package pack_23584ec6c611217305b83264fd8f62ebdeb601203511ae646d8f4756e4bb19be;
  }

  namespace generated_inventory {
    //extern const erc::inventory_package inventory_aaaa;
    const erc::inventory_package inventory_aaaa
    {
      for_map( generated_package::pack_23584ec6c611217305b83264fd8f62ebdeb601203511ae646d8f4756e4bb19be ),
      //{{"source_info-static", &generated_package::pack_23584ec6c611217305b83264fd8f62ebdeb601203511ae646d8f4756e4bb19be}}
    };
  }

}

