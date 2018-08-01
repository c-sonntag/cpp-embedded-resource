#include "head.hpp"

#include <cstdio>
#include <iostream>
#include <exception>
#include <vector>

void help()
{
  std::cout << "Embedded resource packager" << std::endl
            << "By Christophe Sonntag" << std::endl
            << std::endl
            << "   ./embedded_resource_packager  " << std::endl
            << "      [-h|--help] |" << std::endl
            << "      [--input-package <erc_xml_package_filepath>]" << std::endl
            << "      [--work-dir <directory_path>]" << std::endl
            << "      [--get-for-cmake-target]" << std::endl
            << "" << std::endl
            << "   -h|--help : Print this message" << std::endl
            << "  --input-package <erc_xml_package_filepath> : ERC Package to be parsed and evaluate" << std::endl
            << "  --work-dir <directory_path>                : Directory to generate files" << std::endl
            << "  --get-for-cmake-target                     : Return file generation data in stdout for CMake" << std::endl
            << std::endl;
}


struct ParseCommand
{
 public:
  std::string input_package;
  std::string work_dir;
  bool get_for_cmake_target = false;

 private:
  enum struct Option { None = 0, InputPackage, WorkDir };

 public:
  ParseCommand( int argc, char * argv[] ) {

    //
    std::vector<std::string> args( argv + 1, argv + argc );

    //
    Option option{Option::None};

    //
    for ( auto it = args.cbegin(); it != args.cend(); ++it ) {
      const std::string & argument = *it;
      //
      if ( option != Option::None ) {

        //
        if ( option == Option::InputPackage )
          input_package = argument;
        else if ( option == Option::WorkDir )
          work_dir = argument;

        //
        option = Option::None;
      }
      else {
        if ( ( argument == "--help" ) || ( argument == "-h" ) )
        {help( ); exit( EXIT_SUCCESS );}
        else if ( argument == "--input-package" )
          option = Option::InputPackage;
        else if ( argument == "--work-dir" )
          option = Option::WorkDir;
        else if ( argument == "--get-for-cmake-target" )
          get_for_cmake_target = true;
      }
    }
    //
    if ( option != Option::None )
      throw std::runtime_error( "One option need an argument" );

    //
    if ( input_package.empty() || work_dir.empty() )
      throw std::runtime_error( "Need '--input-package' and '--work-dir' params" );
  }
};


int main( int argc, char * argv[] )
{
  try
  {
    const ParseCommand args{argc, argv};
    try
    {
      embedded_resource_packager erp( args.input_package, args.work_dir );
      if ( args.get_for_cmake_target )
        erp.for_cmake_target();
      else
        erp.for_generation();
    }
    catch ( std::exception & e )
    { std::cerr << "Error process : " << e.what() << std::endl; return EXIT_FAILURE; }
  }
  catch ( std::exception & e )
  { std::cerr << "Error arguments : " << e.what() << std::endl << "See help :" << std::endl << " ----- " << std::endl; help(); return EXIT_FAILURE; }


  return EXIT_SUCCESS;
}




