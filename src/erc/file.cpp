#include <erc/file.h>

#include <erc/compress.h>

namespace erc {

  const std::string & embedded_file::get_proper_data() const
  {
    //
    if ( proper_data_p == nullptr )
    {
      const std::string * const data_str_p( new std::string( data, data + property.size ) );
      if ( property.compressed )
      {
        proper_data_p = new std::string( erc::decompress_string( *data_str_p ) );
        delete data_str_p;
      }
      else
        proper_data_p = data_str_p;
    }

    //
    return *proper_data_p;
  }

  void embedded_file::unallocate_proper_data() const
  {
    if ( proper_data_p != nullptr )
      delete proper_data_p;
  }

}

