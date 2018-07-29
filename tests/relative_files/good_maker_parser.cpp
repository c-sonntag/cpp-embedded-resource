#include <erc_maker/erc_package_file_parser.h>

#include <tests_directories.h>
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
  ASSERT_EQ( erc.content.package_name, "composed_ressource" );
  ASSERT_EQ( erc.content.prefix.empty(), true );

  //
  ASSERT_EQ( erc.content.files[0], erc_maker::file( "file1.txt", false ) );
  ASSERT_EQ( erc.content.files[1], erc_maker::file( "file2.txt", false ) );
  ASSERT_EQ( erc.content.files[2], erc_maker::file( "file3.txt", true ) );
  ASSERT_EQ( erc.content.files[3], erc_maker::file( "file4.txt", false ) );
  ASSERT_EQ( erc.content.files[4], erc_maker::file( "file5.txt", true ) );
  ASSERT_EQ( erc.content.files[5], erc_maker::file( "sub_dir/sub_file1.txt" ) );
  ASSERT_EQ( erc.content.files[6], erc_maker::file( "sub_dir/sub_file2.txt" ) );
  ASSERT_EQ( erc.content.files[7], erc_maker::file( "nop1" ) );
  ASSERT_EQ( erc.content.files[8], erc_maker::file( "nop2" ) );


}
