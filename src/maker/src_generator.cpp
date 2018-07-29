#include <erc/maker/src_generator.h>

#include <picosha2.h>

namespace erc {
  namespace maker {

    src_generator::src_generator( const erc_package_file_parser & _erc_package, const erc_files_list & _erc_files ) :
      erc_package( std::move( _erc_package ) ),
      erc_files( std::move( _erc_files ) )
    {
        //

    }




  }
}

