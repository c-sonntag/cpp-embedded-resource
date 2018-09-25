#include <test_helper.hpp>

#include <erc_maker/erc_package_file_parser.h>
#include <erc_maker/erc_files_list.h>

#include <unitstest_program/tests_directories.h>
#include <gtest/gtest.h>

#include <vector>
#include <array>
#include <string>
#include <exception>

void good_maker_listener_by_helper( const test_helper & helper, const std::string & erc_filepath )
{
  //
  const erc_maker::erc_files_list files( erc_filepath );

  //
  ASSERT_EQ( files.files_found.size(), helper.final_efs.size() );
  ASSERT_EQ( files.files_not_found.size(), helper.nop_files_string.size() );

  //
  for ( const erc::embedded_file & ef : helper.final_efs )
  {
    const auto f_found_it( files.files_found.find( ef.path ) );
    ASSERT_TRUE( f_found_it != files.files_found.end() );
    if ( f_found_it != files.files_found.end() )
    {
      erc::file_property property_without_modification_time( f_found_it->second.property );
      property_without_modification_time.last_modification = 0;
      ASSERT_EQ( property_without_modification_time, ef.property.file );
    }
  }

  //
  for ( const auto & dfnf : helper.nop_files_string )
  {
    const auto nf_found_it( files.files_not_found.find( dfnf ) );
    ASSERT_TRUE( nf_found_it != files.files_not_found.end() );
  }

}


TEST( relative_files, good_maker_listener )
{ good_maker_listener_by_helper( relative_files_resource_helper, tests_directories::relative_files + "relative_files_resource.erc" ); }
