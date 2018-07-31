#pragma once

#include <erc/file.h>
#include <erc/package.h>

static const erc::embedded_file final_efs[]
{
  {"file1.txt",             {{ "file1.txt",     ".txt", 5,  0 }, 5,  false, true}, reinterpret_cast<const unsigned char *>( "Hello" )},
  {"file2.txt",             {{ "file2.txt",     ".txt", 5,  0 }, 5,  false, true}, reinterpret_cast<const unsigned char *>( "world" )},
  {"file3.txt",             {{ "file3.txt",     ".txt", 3,  0 }, 11, true,  true}, reinterpret_cast<const unsigned char *>( "!!!a" )},
  {"file4.txt",             {{ "file4.txt",     ".txt", 8,  0 }, 8,  false, true}, reinterpret_cast<const unsigned char *>( "Composed" )},
  {"file5.txt",             {{ "file5.txt",     ".txt", 8,  0 }, 16, true,  true}, reinterpret_cast<const unsigned char *>( "resource" )},
  {"sub_dir/sub_file1.txt", {{ "sub_file1.txt", ".txt", 11, 0 }, 11, false, true}, reinterpret_cast<const unsigned char *>( "And file on" )},
  {"sub_dir/sub_file2.txt", {{ "sub_file2.txt", ".txt", 12, 0 }, 12, false, true}, reinterpret_cast<const unsigned char *>( "subdirectory" )},
};

static constexpr size_t final_efs_size( sizeof( final_efs ) / sizeof( erc::embedded_file ) );

const erc::package final_package
{
  "composed_ressource",
  final_efs_size,
  nullptr
};
