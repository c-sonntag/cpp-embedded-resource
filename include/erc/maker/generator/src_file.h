#pragma once

#include <erc/types.h>
#include <erc/maker/erc_files_list.h>

#include <string>

namespace erc {
  namespace maker {
    namespace generator {

      void src_file(
        const file_property_found & valid_input_file,
        const std::string & generated_embedded_file_unique_identifier,
        const std::string & output_src_file
      );

    }
  }
}

