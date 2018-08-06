#pragma once

#include <erc_maker/erc_files_list.h>
#include <erc_maker/hash.h>

namespace erc_maker {

  struct erc_file_identifier
  {
    const file_property_found valid_input_file; /**< @todo check by ref */
    const hash256 file_unique_identifier;

    inline erc_file_identifier() = default;
    inline erc_file_identifier( const file_property_found _valid_input_file, const hash256 _file_unique_identifier ) :
      valid_input_file( std::move( _valid_input_file ) ),
      file_unique_identifier( std::move( _file_unique_identifier ) )
    {}
  };

}

