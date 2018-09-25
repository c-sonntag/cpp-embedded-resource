#include <test_helper.hpp>

#include <erc_maker/erc_package_file_parser.h>

#include <unitstest_program/tests_directories.h>
#include <gtest/gtest.h>

#include <vector>
#include <string>
#include <exception>

void good_maker_parser_by_helper( const test_helper & helper, const std::string & erc_filepath )
{
  //
  const erc_maker::erc_package_file_parser erc( erc_filepath );

  //
  ASSERT_EQ( erc.content.files.size(), helper.parsed_files_string.size() );
  ASSERT_EQ( erc.content.directories.size(), helper.parsed_directories_string.size() );
  ASSERT_EQ( erc.content.package_name, helper.final_package.name );
  ASSERT_EQ( erc.content.prefix.empty(), true );

  //
  for ( const erc::embedded_file & ef : helper.final_efs )
  {
    const erc_maker::file ef_converted( ef.path, ef.property.compressed );
    bool found( false );
    for ( const erc_maker::file & mf : erc.content.files )
      if ( ef_converted == mf )
        found = true;
    ASSERT_TRUE( found );
  }

  for ( const erc_maker::file & nop_mf : helper.nop_files_string )
  {
    bool found( false );
    for ( const erc_maker::file & mf : erc.content.files )
      if ( nop_mf == mf )
        found = true;
    ASSERT_TRUE( found );
  }

}

TEST( relative_files, good_maker_parser )
{ good_maker_parser_by_helper( relative_files_resource_helper, tests_directories::relative_files + "relative_files_resource.erc" ); }
