#pragma once

#include <string>

namespace tests_directories {

#define ADD_CONSTEXPR_TESTS_DIRECTORIES(var,path) \
  static const std::string var { _TESTS_DIRECTORY_PATH "/" path "/" };

  ADD_CONSTEXPR_TESTS_DIRECTORIES( relative_files, "relative_files" )
  ADD_CONSTEXPR_TESTS_DIRECTORIES( relative_directory, "relative_directory" )

}

