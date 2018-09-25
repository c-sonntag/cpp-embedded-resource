#pragma once

#include <erc/file.h>
#include <erc/package.h>

#include <vector>

struct test_helper
{
  const std::vector<erc::embedded_file> & final_efs;
  const erc::package & final_package;

  const std::vector<std::string> & parsed_files_string;
  const std::vector<std::string> & parsed_directories_string;

  const std::vector<std::string> & nop_files_string;
  const std::vector<std::string> & nop_directories_string;
};

extern const test_helper relative_files_resource_helper;
