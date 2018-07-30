#include <tests_directories.h>
#include <gtest/gtest.h>

#include <erc/package.h>

#include <vector>
#include <string>
#include <exception>


TEST( relative_files, good_package )
{

  //
  const erc::package * const package_p( erc::package_manager::get("composed_ressource") );
  ASSERT_NE( package_p, nullptr );

  //
  const erc::package & package(*package_p);

  //
  ASSERT_EQ( package.name, "composed_ressource" );
  ASSERT_EQ( package.size, 7 );
  ASSERT_NE( package.embedded_files, nullptr );

  //
  const erc::embedded_file * const * const embedded_files( package.embedded_files );

  //
  for ( unsigned int i( 0 ); i < package.size; ++i )
  {
    const erc::embedded_file & ef( *embedded_files[i] );
    std::cout << "File id(" << i << ") : " << std::endl
              << "  Path(" << ef.path << ")" << std::endl
              << "  Compressed(" << std::boolalpha << ef.property.compressed << ") Raw(" << std::boolalpha << ef.property.raw_data << ")  Size(" << std::boolalpha << ef.property.size << ")" << std::endl
              << "  Filename(" << std::boolalpha << ef.property.file.filename << ") RealSize(" << std::boolalpha << ef.property.file.size << ")" << std::endl
              << "  Data : ";
    std::cout.write( reinterpret_cast<const char *>( ef.data ), ef.property.size );
    std::cout << std::endl;
  }


}
