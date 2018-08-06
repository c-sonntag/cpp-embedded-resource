#include <relative_files/composed_resource.hpp>

#include <unitstest_program/tests_directories.h>
#include <gtest/gtest.h>

#include <erc/package.h>
#include <erc/inventory_package.h>

#include <vector>
#include <string>
#include <exception>

#include <tests_static/get_static_lib.hpp>


std::string compose_message_from_package( const erc::package & p )
{
  std::string msg;
  for ( const erc::embedded_file & final_ef : final_efs )
  {
    const erc::embedded_file * const want_erc_file( p.get_embedded_file( final_ef.path ) );
    if ( want_erc_file )
      msg += ( msg.empty() ? "" : " " ) + want_erc_file->get_proper_data();
  }
  return msg;
}


TEST( relative_files, good_package_message )
{
  //
  const erc::inventory_package & inventory( erc::inventory_package::get() );

  //
  const erc::package * const from_program_erc_package( inventory.get_first_package( "composed_ressource" ) );
  const erc::package * const from_static_erc_package( get_static_lib() );

  ASSERT_TRUE( from_program_erc_package );
  ASSERT_TRUE( from_static_erc_package );

  const std::string from_program( compose_message_from_package( *from_program_erc_package ) );
  const std::string from_static_lib( compose_message_from_package( *from_static_erc_package ) );

  ASSERT_EQ( from_program, from_static_lib );
}


TEST( relative_files, good_package_message_source )
{
  //
  static const erc::file_id source_info_erc_id( "source_info", "source_info.txt" );
  const erc::inventory_package & inventory( erc::inventory_package::get() );
  const erc::embedded_file * const from_program_source_info_erc( inventory.get_first_embedded_file( source_info_erc_id ) );

  //
  const erc::embedded_file * const from_static_lib_source_info_erc( get_static_lib_source_info_file() );

  //
  ASSERT_TRUE( from_program_source_info_erc );
  ASSERT_TRUE( from_static_lib_source_info_erc );

  const std::string from_program_source_info_str( from_program_source_info_erc->get_proper_data() );
  const std::string from_static_lib_source_info_str( from_static_lib_source_info_erc->get_proper_data() );

  std::cout << "from_program_source_info_str:" << from_program_source_info_str << std::endl;
  std::cout << "from_static_lib_source_info_str:" << from_static_lib_source_info_str << std::endl;

  //ASSERT_NE( from_program_source_info_str, from_static_lib_source_info_str );

  ASSERT_EQ( from_program_source_info_str, "unitstest_program" );
  ASSERT_EQ( from_static_lib_source_info_str, "tests_static" );

}

