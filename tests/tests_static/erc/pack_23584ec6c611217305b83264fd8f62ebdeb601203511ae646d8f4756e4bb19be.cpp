/**
* @brief Generated file for EmbeddedResource lib.
* @note Package file can be found at
*       tests_static/source_info.erc
*/

#define ERC_FROM_GENERATED_PACKAGE 1
#include <erc/inventory_package.h>

#include "./pack_23584ec6c611217305b83264fd8f62ebdeb601203511ae646d8f4756e4bb19be.h"

namespace erc {

  namespace generated_embedded_files {
    const extern erc::embedded_file erc_c00a0e03b8eaf16e7f78d565caf17e6f4f357381c5a4c192fc7b68cc81a76759;
    static const erc::embedded_file * const embedded_files[]
    {
      &erc_c00a0e03b8eaf16e7f78d565caf17e6f4f357381c5a4c192fc7b68cc81a76759,
    };
  }

  namespace generated_package {
    extern const erc::package pack_23584ec6c611217305b83264fd8f62ebdeb601203511ae646d8f4756e4bb19be;
    const erc::package pack_23584ec6c611217305b83264fd8f62ebdeb601203511ae646d8f4756e4bb19be
    //const erc::package source_info
    {
      "source_info-static",
      1,
      erc::generated_embedded_files::embedded_files
    };

   // const erc::package & source_info()
   // {
   //   return pack_23584ec6c611217305b83264fd8f62ebdeb601203511ae646d8f4756e4bb19be;
   // }
   //
   // //
   // const erc::package & source_info_bis()
   // {
   //   return pack_23584ec6c611217305b83264fd8f62ebdeb601203511ae646d8f4756e4bb19be;
   // }

    //static const struct initializer {
    //  //inline initializer() { erc::inventory_package::push(pack_23584ec6c611217305b83264fd8f62ebdeb601203511ae646d8f4756e4bb19be); }
    //} _mypack;
  }
}

