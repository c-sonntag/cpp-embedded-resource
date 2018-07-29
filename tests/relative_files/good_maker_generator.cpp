#include <erc/maker/erc_package_file_parser.h>
#include <erc/maker/erc_files_list.h>

#include <erc/maker/src_generator.h>

#include <tests_directories.h>
#include <gtest/gtest.h>

#include <vector>
#include <array>
#include <string>
#include <exception>

TEST( relative_files, good_maker_generator )
{

  //
  const erc::maker::erc_package_file_parser erc( tests_directories::relative_files + "composed_ressource.erc" );

  //
  const erc::maker::erc_files_list files( erc );

  //
  erc::maker::src_generator generator( erc, files );
  generator.generate_into( "./" );



}
