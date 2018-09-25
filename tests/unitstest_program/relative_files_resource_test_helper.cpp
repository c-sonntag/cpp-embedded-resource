#include <test_helper.hpp>

static const std::vector<erc::embedded_file> final_efs
{
  {"file1.txt",             {{ "file1.txt",     ".txt", 5,  0 }, 5,  false, true}, reinterpret_cast<const unsigned char *>( "Hello" )},
  {"file2.txt",             {{ "file2.txt",     ".txt", 5,  0 }, 5,  false, true}, reinterpret_cast<const unsigned char *>( "world" )},
  {"file3.txt",             {{ "file3.txt",     ".txt", 3,  0 }, 11, true,  true}, reinterpret_cast<const unsigned char *>( "!!!" )},
  {"file4.txt",             {{ "file4.txt",     ".txt", 8,  0 }, 8,  false, true}, reinterpret_cast<const unsigned char *>( "Composed" )},
  {"file5.txt",             {{ "file5.txt",     ".txt", 8,  0 }, 16, true,  true}, reinterpret_cast<const unsigned char *>( "resource" )},
  {"sub_dir/sub_file1.txt", {{ "sub_file1.txt", ".txt", 11, 0 }, 11, false, true}, reinterpret_cast<const unsigned char *>( "And file on" )},
  {"sub_dir/sub_file2.txt", {{ "sub_file2.txt", ".txt", 12, 0 }, 12, false, true}, reinterpret_cast<const unsigned char *>( "subdirectory" )},
};

static const erc::package final_package
{
  "relative_files_resource",
  erc::uint( final_efs.size() ),
  nullptr
};


static const std::vector<std::string> parsed_files_string
{ "file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt", "sub_dir/sub_file1.txt", "sub_dir/sub_file2.txt", "nop1", "nop2", };

static const std::vector<std::string> parsed_directories_string
{};


static const std::vector<std::string> nop_files_string
{ "nop1", "nop2" };

static const std::vector<std::string> nop_directories_string
{};


const test_helper relative_files_resource_helper
{ final_efs, final_package, parsed_files_string, parsed_directories_string, nop_files_string, nop_directories_string };
