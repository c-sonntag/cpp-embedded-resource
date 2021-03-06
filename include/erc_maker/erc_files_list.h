#pragma once

#include <erc/file.h>

#include <erc_maker/erc_package_file_parser.h>
#include <erc_maker/model.h>

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

namespace erc_maker {

  struct file_property_found
  {
    erc_maker::file file;
    erc::file_property property;
    std::string path;

    inline file_property_found(
      erc_maker::file _file_params,
      erc::file_property _file,
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
    using files_found_t = std::unordered_map<std::string, file_property_found>;
    files_found_t files_found;

    using not_found_path_t = std::unordered_set<std::string>;
    not_found_path_t files_not_found;
    not_found_path_t directories_not_found;

    erc_files_list( const erc_package_file_parser & erc_parsed_content );
  };

}

