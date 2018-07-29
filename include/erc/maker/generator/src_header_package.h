#pragma once

#include <erc/types.h>

#include <string>
#include <vector>

namespace erc {
  namespace maker {
    namespace generator {

      void src_header_package(
        const std::vector<std::string> generated_packages,
        const std::string output_src_file
      );

    }
  }
}

