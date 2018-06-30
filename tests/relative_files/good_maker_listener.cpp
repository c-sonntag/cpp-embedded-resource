#include <erc/maker/erc_file_parser.h>
#include <erc/maker/erc_files_list.h>

#include <tests_directories.h>
#include <gtest/gtest.h>

#include <vector>
#include <string>
#include <exception>

TEST( relative_files, good_maker_listener )
{

  //
  const erc::maker::erc_file_parser erc( tests_directories::relative_files + "composed_ressource.erc" );

  //
  const erc::maker::erc_files_list files( erc );

  //
  ASSERT_EQ( files.files_found.size(), 7 );
  ASSERT_EQ( files.files_not_found.size(), 2 );

  //
  //ASSERT_EQ( files.files_found[0].property, erc::file_property( "file1.txt", ".txt", 5 ) );
  //ASSERT_EQ( files.files_found[1].property, erc::file_property( "file2.txt", ".txt", 5 ) );
  //ASSERT_EQ( files.files_found[2].property, erc::file_property( "file3.txt", ".txt", 3 ) );
  //ASSERT_EQ( files.files_found[3].property, erc::file_property( "file4.txt", ".txt", 8 ) );
  //ASSERT_EQ( files.files_found[4].property, erc::file_property( "file5.txt", ".txt", 9 ) );
  //ASSERT_EQ( files.files_found[5].property, erc::file_property( "sub_file1.txt", ".txt", 11 ) );
  //ASSERT_EQ( files.files_found[6].property, erc::file_property( "sub_file2.txt", ".txt", 12 ) );

  //
  ASSERT_EQ( files.files_not_found[0], "nop1" );
  ASSERT_EQ( files.files_not_found[1], "nop2" );


}
