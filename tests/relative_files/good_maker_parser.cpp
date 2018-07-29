#include <erc/maker/erc_package_file_parser.h>

#include <tests_directories.h>
#include <gtest/gtest.h>

#include <vector>
#include <string>
#include <exception>

TEST( relative_files, good_maker_parser )
{

  //
  const erc::maker::erc_package_file_parser erc( tests_directories::relative_files + "composed_ressource.erc" );

  //
  ASSERT_EQ( erc.content.files.size(), 9 );
  ASSERT_EQ( erc.content.package_name, "composed_ressource" );
  ASSERT_EQ( erc.content.prefix.empty(), true );

  //
  ASSERT_EQ( erc.content.files[0], erc::maker::file( "file1.txt", false ) );
  ASSERT_EQ( erc.content.files[1], erc::maker::file( "file2.txt", false ) );
  ASSERT_EQ( erc.content.files[2], erc::maker::file( "file3.txt", true ) );
  ASSERT_EQ( erc.content.files[3], erc::maker::file( "file4.txt", false ) );
  ASSERT_EQ( erc.content.files[4], erc::maker::file( "file5.txt", true ) );
  ASSERT_EQ( erc.content.files[5], erc::maker::file( "sub_dir/sub_file1.txt" ) );
  ASSERT_EQ( erc.content.files[6], erc::maker::file( "sub_dir/sub_file2.txt" ) );
  ASSERT_EQ( erc.content.files[7], erc::maker::file( "nop1" ) );
  ASSERT_EQ( erc.content.files[8], erc::maker::file( "nop2" ) );


}
