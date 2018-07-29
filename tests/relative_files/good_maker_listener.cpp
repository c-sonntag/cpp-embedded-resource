#include <erc_maker/erc_package_file_parser.h>
#include <erc_maker/erc_files_list.h>

#include <tests_directories.h>
#include <gtest/gtest.h>

#include <vector>
#include <array>
#include <string>
#include <exception>

TEST( relative_files, good_maker_listener )
{

  //
  const erc_maker::erc_package_file_parser erc( tests_directories::relative_files + "composed_ressource.erc" );

  //
  const erc_maker::erc_files_list files( erc );

  //
  ASSERT_EQ( files.files_found.size(), 7 );
  ASSERT_EQ( files.files_not_found.size(), 2 );

  //
  const struct { std::string path; erc::file_property property; } desired_files_found[7]
  {
    {"file1.txt",             { "file1.txt",     ".txt", 5, 0 }},
    {"file2.txt",             { "file2.txt",     ".txt", 5, 0 }},
    {"file3.txt",             { "file3.txt",     ".txt", 3, 0 }},
    {"file4.txt",             { "file4.txt",     ".txt", 8, 0 }},
    {"file5.txt",             { "file5.txt",     ".txt", 9, 0 }},
    {"sub_dir/sub_file1.txt", { "sub_file1.txt", ".txt", 11, 0 }},
    {"sub_dir/sub_file2.txt", { "sub_file2.txt", ".txt", 12, 0 }},
  };
  for ( const auto & dff : desired_files_found )
  {
    const auto f_found_it( files.files_found.find( dff.path ) );
    ASSERT_TRUE( f_found_it != files.files_found.end() );
    if ( f_found_it != files.files_found.end() )
    {
      erc::file_property property_without_modification_time( f_found_it->second.property );
      property_without_modification_time.last_modification = 0;
      ASSERT_EQ( property_without_modification_time, dff.property );
    }
  }

  //
  const std::string desired_files_not_found[2]
  {
    "nop1", "nop2",
  };
  for ( const auto & dfnf : desired_files_not_found )
  {
    const auto nf_found_it( files.files_not_found.find( dfnf ) );
    ASSERT_TRUE( nf_found_it != files.files_not_found.end() );
  }


}
