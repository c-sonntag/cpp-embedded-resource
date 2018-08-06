#pragma once

#include <erc_maker/erc_inventory.h>
#include <erc_maker/src_generator.h>

#include <string>


struct ParsedCommand
{
  std::vector<std::string> input_packages;
  std::string work_dir;
  std::string inventory_name;
};

struct embedded_resource_packager
{
  const ParsedCommand & parsed;
  const erc_maker::erc_inventory erc_inventory;

  erc_maker::src_generator src_generator;

  embedded_resource_packager( const ParsedCommand & _parsed ) :
    parsed( std::move( _parsed ) ),
    erc_inventory( parsed.input_packages, parsed.inventory_name ),
    src_generator( erc_inventory )
  {}

  void for_cmake_target();
  void for_generation();

};



