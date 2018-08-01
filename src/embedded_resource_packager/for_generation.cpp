#include "head.hpp"

#include <iostream>
#include <exception>
#include <vector>

void embedded_resource_packager::for_generation()
{
  //
  static const std::string prefix_out( "       [EmbeddedResource] " );

  //
  std::cout << prefix_out << "File : " << erc.erc_package_filepath << std::endl;

  //
  std::cout << prefix_out << "Opening cache (if exist)" << std::endl;
  try { generator.open_cache_if_exist_into( work_dir ); }
  catch ( const std::exception & e )
  { std::cout << prefix_out << "  -> Cache errors : " << e.what() << std::endl; }

  //
  generator.generate_into( work_dir );

  //
  const erc_maker::src_generator::generation_rapport & rapport( generator.get_rapport() );
  std::cout << prefix_out << "PackerSuccess : generation(" << rapport.nb_generated << ") passed(" << rapport.nb_passed << ") " << std::endl;

  //
  if ( rapport.nb_generated > 0 )
  {
    std::cout << prefix_out << "Saving changement in cache" << std::endl;
    generator.save_cache_into( work_dir );
  }

  // //
  // std::cout << "       See generated files : " << std::endl;
  // const std::vector<std::string> & generated_filepath_list( generator.get_generated_filepath_list() );
  // for ( const std::string & filepath : generated_filepath_list )
  //   std::cout << "  " << filepath << std::endl;
}


