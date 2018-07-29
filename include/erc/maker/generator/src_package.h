#pragma once

#include <erc/types.h>
#include <erc/maker/erc_files_list.h>

#include <string>

namespace erc {
  namespace maker {
    namespace generator {

      void src_package(
        const std::string & generated_package_unique_identifier,
        const std::vector<std::string> & generated_embedded_files_uniques_identifier,
        const std::string & output_src_file
      );

    }
  }
}

