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
    extern erc::package pack_8cff6884e39a8c83a2d3550b959a6e8946e09a3f292d261da948475d8e5c2ebf;
    extern erc::package pack_39b7c4c30a81a4f37b63c68e58a833a27ad5b7c0eea9ddfe27adfb780a13ae09;
  }

  namespace generated_inventory {
    extern const erc::inventory_package inventory_bbbb;
    const erc::inventory_package inventory_bbbb
    {
      for_map( generated_package::pack_8cff6884e39a8c83a2d3550b959a6e8946e09a3f292d261da948475d8e5c2ebf ),
      for_map( generated_package::pack_39b7c4c30a81a4f37b63c68e58a833a27ad5b7c0eea9ddfe27adfb780a13ae09 ),
    };
  }

}

