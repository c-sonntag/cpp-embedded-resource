#include <test_helper.hpp>

#include <unitstest_program/tests_directories.h>
#include <gtest/gtest.h>

#include <erc/package.h>
#include <erc/inventory_package.h>

#include <vector>
#include <string>
#include <exception>


void good_package_by_helper( const test_helper & helper, const std::string & package_name )
{

  const erc::inventory_package & inventory( erc::inventory_package::get() );

  //  std::cout << "---- debug inventory ---- " << std::endl;
  //  inventory.debug_print( std::cout );
  //  std::cout << "---- ---- " << std::endl;

  //
  const erc::package * const package_p( inventory.get_first_package( package_name ) );
  ASSERT_TRUE( package_p );

  //
  const erc::package & package( *package_p );

  //
  ASSERT_EQ( package.name, helper.final_package.name );
  ASSERT_EQ( package.size, helper.final_efs.size() );
  ASSERT_NE( package.embedded_files, nullptr );

  //
  for ( const erc::embedded_file & final_ef : helper.final_efs )
  {

    //
    const erc::embedded_file * const ef_p( package.get_embedded_file( final_ef.path ) );
    ASSERT_TRUE( ef_p != nullptr );

    //
    const erc::embedded_file & ef( *ef_p );

    //
    const std::string final_ef_proprer_data( final_ef.data, final_ef.data + final_ef.property.file.size );
    ASSERT_EQ( ef.get_proper_data(), final_ef_proprer_data );
    //std::cout << " Path(" << ef.path << ") : " << ef.get_proper_data() << " == " << final_ef_proprer_data << std::endl;

    //
    erc::embedded_data_property edp_without_modification_time( ef.property );
    edp_without_modification_time.file.last_modification = 0;

    //
    ASSERT_EQ( edp_without_modification_time, final_ef.property );
  }

  //for ( const erc::package_group & pg : erc::inventory_package::get_packages() ) {
  //  const erc::package & package( pg.package );
  //  std::cout << "Package name(" << package.name << ") : " << std::endl;
  //  const erc::embedded_file * const * const embedded_files( package.embedded_files );
  //  for ( unsigned int i( 0 ); i < package.size; ++i ) {
  //    const erc::embedded_file & ef( *embedded_files[i] );
  //    std::cout << "  File id(" << i << ") : " << std::endl
  //              << "    Path(" << ef.path << ")" << std::endl
  //              << "    Compressed(" << std::boolalpha << ef.property.compressed << ") Raw(" << std::boolalpha << ef.property.raw_data << ")  Size(" << std::boolalpha << ef.property.size << ")" << std::endl
  //              << "    Filename(" << std::boolalpha << ef.property.file.filename << ") RealSize(" << std::boolalpha << ef.property.file.size << ")" << std::endl;
  //    std::cout << std::endl;
  //  }


  //
  //  const erc::package_group * const package_group_p( erc::inventory_package::get_group( "relative_files_resource" ) );
  //  if ( package_group_p )
  //  {
  //    const erc::package & package( package_group_p->package );
  //    const erc::embedded_file * const * const embedded_files( package.embedded_files );
  //    for ( unsigned int i( 0 ); i < package.size; ++i )
  //    {
  //      const erc::embedded_file & ef( *embedded_files[i] );
  //      std::cout << "File id(" << i << ") : " << std::endl
  //                << "  Path(" << ef.path << ")" << std::endl
  //                << "  Compressed(" << std::boolalpha << ef.property.compressed << ") Raw(" << std::boolalpha << ef.property.raw_data << ")  Size(" << std::boolalpha << ef.property.size << ")" << std::endl
  //                << "  Filename(" << std::boolalpha << ef.property.file.filename << ") RealSize(" << std::boolalpha << ef.property.file.size << ")" << std::endl
  //                << "  Data : " << ef.get_proper_data() << std::endl;
  //      //std::cout.write( reinterpret_cast<const char *>( ef.data ), ef.property.size );
  //      std::cout << std::endl;
  //    }
  //  }


}


TEST( relative_files, good_package )
{ good_package_by_helper( relative_files_resource_helper, "relative_files_resource" ); }
