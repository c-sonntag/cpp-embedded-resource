#include "./composed_resource.hpp"

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
  ASSERT_EQ( files.files_found.size(), final_efs_size );
  ASSERT_EQ( files.files_not_found.size(), 2 );

  //
  for ( const erc::embedded_file & ef : final_efs )
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
