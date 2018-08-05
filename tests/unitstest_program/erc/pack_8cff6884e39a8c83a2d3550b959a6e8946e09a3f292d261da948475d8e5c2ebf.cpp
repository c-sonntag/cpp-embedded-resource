/**
* @brief Generated file for EmbeddedResource lib.
* @note Package file can be found at
*       unitstest_program/source_info.erc
*/

//#define ERC_FROM_GENERATED_PACKAGE 1
#include <erc/package.h>

//#include "./pack_8cff6884e39a8c83a2d3550b959a6e8946e09a3f292d261da948475d8e5c2ebf.h"

namespace erc {

  namespace generated_embedded_files {
    const extern erc::embedded_file erc_1c61b34033a91b58ac9f3e9dcace424e1629b61968fba90894ada4a52d9d080e;
    static const erc::embedded_file * const embedded_files[]
    {
      &erc_1c61b34033a91b58ac9f3e9dcace424e1629b61968fba90894ada4a52d9d080e,
    };
  }

  namespace generated_package {
    extern const erc::package pack_8cff6884e39a8c83a2d3550b959a6e8946e09a3f292d261da948475d8e5c2ebf;
    const erc::package pack_8cff6884e39a8c83a2d3550b959a6e8946e09a3f292d261da948475d8e5c2ebf
    //const erc::package source_info
    {
      "source_info",
      1,
      erc::generated_embedded_files::embedded_files
    };

//    const erc::package & source_info()
//    {
//      return pack_8cff6884e39a8c83a2d3550b959a6e8946e09a3f292d261da948475d8e5c2ebf;
//    }



    //static const struct initializer
    //{
    //  //inline initializer() { erc::inventory_package::push(pack_8cff6884e39a8c83a2d3550b959a6e8946e09a3f292d261da948475d8e5c2ebf); }
    //} _mypack;
  }
}

