#include <erc/package.h>

namespace erc {

  const erc::embedded_file * package::get_embedded_file( const std::string & file_path ) const
  {
    for ( uint i( 0 ); i < size; ++i )
    {
      const erc::embedded_file & ef( *embedded_files[i] );
      if ( ef.path == file_path )
        return &ef;
    }
    return nullptr;
  }

}

