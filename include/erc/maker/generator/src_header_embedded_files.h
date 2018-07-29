#pragma once

#include <erc/types.h>

#include <string>
#include <vector>

namespace erc {
  namespace maker {
    namespace generator {

      void src_header_embedded_files(
        const std::vector<std::string> & generated_embedded_files_uniques_identifier,
        const std::string output_src_file
      );

    }
  }
}

