#include <relative_files/composed_resource.hpp>

#include <unitstest_program/tests_directories.h>
#include <gtest/gtest.h>

#include <erc/package.h>
#include <erc/inventory_package.h>

#include <vector>
#include <string>
#include <exception>

#include <tests_static/get_static_lib.hpp>

//#include <pack_8cff6884e39a8c83a2d3550b959a6e8946e09a3f292d261da948475d8e5c2ebf.h>

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




//TEST( relative_files, good_package_message )
//{

// //
// const erc::inventory_package & inventory( erc::inventory_package::get() );
// const erc::package * package_p( inventory.get_first_package( "composed_ressource" ) );
// ASSERT_TRUE( package_p );

//  const erc::package_group * const from_program_group_erc( erc::inventory_package::get_group( "composed_ressource" ) );
//  const erc::package * const from_static_erc_package( get_static_lib() );

//  ASSERT_TRUE( from_program_group_erc );
//  ASSERT_TRUE( from_static_erc_package );

//  const std::string from_program( compose_message_from_package( from_program_group_erc->package ) );
//  const std::string from_static_lib( compose_message_from_package( *from_static_erc_package ) );

//  //std::cout << "from_program:" << from_program << std::endl;
//  //std::cout << "from_static_lib:" << from_static_lib << std::endl;

//  ASSERT_EQ( from_program, from_static_lib );

//}


// namespace erc {
//   namespace generated_package {
//     extern const erc::package source_info;
//   }
// }


#define xstr(s) str(s)
#define str(s) #s


TEST( relative_files, good_package_message_source )
{
  //std::cout << "good_package_message_source: ERC_INVENTORY_PACKAGE_EXTERN_NAME(" xstr( ERC_INVENTORY_PACKAGE_EXTERN_NAME ) ")" << std::endl;
  //std::cout << "good_package_message_source: ERC_INVENTORY_PACKAGE_EXTERN_NAME(" xstr( ERC_INVENTORY_PACKAGE_EXTERN_NAME ) ") ref(" << &erc::inventory_package::get() << ")" << std::endl;
  std::cout << "good_package_message_source: ERC_INVENTORY_PACKAGE_EXTERN_NAME(" xstr( ERC_INVENTORY_PACKAGE_EXTERN_NAME ) ") ref(" << &erc::generated_inventory::ERC_INVENTORY_PACKAGE_EXTERN_NAME << ") ref-by-get(" << &erc::inventory_package::get() << ")" << std::endl;


  //
  const erc::inventory_package & inventory( erc::inventory_package::get() );
  const erc::package * package_p( inventory.get_first_package( "source_info" ) );
  ASSERT_TRUE( package_p );


  //const erc::package_group * const from_program_group_erc( erc::inventory_package::get_group( "source_info" ) );
  //ASSERT_TRUE( from_program_group_erc );
  //const erc::embedded_file * const from_program_source_info_erc( from_program_group_erc->package.get_embedded_file( "source_info.txt" ) );
  //const erc::embedded_file * const from_program_source_info_erc( erc::generated_package::source_info().get_embedded_file( "source_info.txt" ) );

  const erc::embedded_file * const from_program_source_info_erc( package_p->get_embedded_file( "source_info.txt" ) );
  const erc::embedded_file * const from_static_lib_source_info_erc( get_static_lib_source_info_file() );

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

