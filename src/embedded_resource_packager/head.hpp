#pragma once

#include <erc_maker/src_generator.h>

#include <string>

struct embedded_resource_packager
{
  const erc_maker::erc_package_file_parser erc;
  const erc_maker::erc_files_list files;
  const std::string work_dir;

  erc_maker::src_generator generator;

  embedded_resource_packager( const std::string _input_package, const std::string _work_dir ) :
    erc( std::move( _input_package ) ), files( erc ),
    work_dir( std::move( _work_dir ) ),
    generator( erc, files )
  {}

  void for_cmake_target();
  void for_generation();

};



