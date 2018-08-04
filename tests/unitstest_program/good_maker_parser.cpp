#include <relative_files/composed_resource.hpp>

#include <erc_maker/erc_package_file_parser.h>

#include <unitstest_program/tests_directories.h>
#include <gtest/gtest.h>

#include <vector>
#include <string>
#include <exception>

TEST( relative_files, good_maker_parser )
{

  //
  const erc_maker::erc_package_file_parser erc( tests_directories::relative_files + "composed_ressource.erc" );

  //
  ASSERT_EQ( erc.content.files.size(), 9 );
  ASSERT_EQ( erc.content.package_name, final_package.name );
  ASSERT_EQ( erc.content.prefix.empty(), true );

  //
  for ( const erc::embedded_file & ef : final_efs )
  {
    const erc_maker::file ef_converted( ef.path, ef.property.compressed );
    bool found( false );
    for ( const erc_maker::file & mf : erc.content.files )
      if ( ef_converted == mf )
        found = true;
    ASSERT_TRUE( found );
  }

  //
  std::vector<erc_maker::file> nop_files
  { {"nop1"}, {"nop2"} };

  for ( const erc_maker::file & nop_mf : nop_files )
  {
    bool found( false );
    for ( const erc_maker::file & mf : erc.content.files )
      if ( nop_mf == mf )
        found = true;
    ASSERT_TRUE( found );
  }


}
