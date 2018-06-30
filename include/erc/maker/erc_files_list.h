#pragma once

#include <erc/types.h>
#include <erc/file.h>

#include <erc/maker/erc_file_parser.h>
#include <erc/maker/model.h>

#include <unordered_map>
#include <vector>

namespace erc {
  namespace maker {

    struct file_property_found
    {
      maker::file file;
      file_property property;
      std::string path;

      inline file_property_found(
        maker::file _file_params,
        file_property _file,
        std::string _path
      ) :
        file( std::move( _file_params ) ),
        property( std::move( _file ) ),
        path( std::move( _path ) )
      {}
    };

    // ---- ----

    struct erc_files_list
    {
      std::unordered_map<std::string, file_property_found> files_found;
      std::vector<std::string> files_not_found;

      std::vector<std::string> directories_not_found;

      erc_files_list( const erc_file_parser & erc_parsed_content );
    };


  }
}

