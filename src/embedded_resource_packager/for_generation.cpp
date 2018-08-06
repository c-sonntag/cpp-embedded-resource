#include "head.hpp"

#include <iostream>
#include <exception>
#include <vector>

void embedded_resource_packager::for_generation()
{
  //
  static const std::string prefix_out( "       [EmbeddedResource] " );

  //
  if ( erc_inventory.prepared_packages.size() == 1 )
    std::cout << prefix_out << "PackageFile : " << erc_inventory.prepared_packages.front().package_filepath << std::endl;
  else
  {
    std::cout << prefix_out << "PackagesFiles : " << std::endl;
    for ( const erc_maker::erc_prepared_package & epp : erc_inventory.prepared_packages )
      std::cout << prefix_out << "   - " << epp.package_filepath << std::endl;
  }

  //
  std::cout << prefix_out << "Opening cache (if exist)" << std::endl;
  try { src_generator.open_caches_if_exists_into( parsed.work_dir ); }
  catch ( const std::exception & e )
  { std::cout << prefix_out << "  -> Cache errors : " << e.what() << std::endl; }

  //
  src_generator.generate_into( parsed.work_dir );

  //
  const erc_maker::src_generator::generation_rapport & rapport( src_generator.get_rapport() );
  std::cout << prefix_out << "InventorySuccess : generation(" << rapport.nb_generated << ") passed(" << rapport.nb_passed << ")  " << std::endl;

  //
  if ( rapport.nb_generated > 0 )
  {
    std::cout << prefix_out << "Saving changement in cache" << std::endl;
    src_generator.save_caches_into( parsed.work_dir );
  }

  // //
  // std::cout << "       See generated files : " << std::endl;
  // const std::vector<std::string> & generated_filepath_list( src_generator.get_generated_filepath_list() );
  // for ( const std::string & filepath : generated_filepath_list )
  //   std::cout << "  " << filepath << std::endl;
}


