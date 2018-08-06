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
            << "      [--input-packages <erc_xml_packages_filepaths...>]" << std::endl
            << "      [--work-dir <directory_path>]" << std::endl
            << "      [--get-for-cmake-target]" << std::endl
            << "" << std::endl
            << "   -h|--help : Print this message" << std::endl
            << "  --input-package <erc_xml_package_filepath>       : ERC Package to be parsed and evaluate" << std::endl
            << "  --input-packages <erc_xml_packages_filepaths...> : ERC Packages to be evaluate (only until generation)" << std::endl
            << "  --work-dir <directory_path>                      : Directory to generate files" << std::endl
            << "  --get-for-cmake-target                           : Return file generation data in stdout for CMake" << std::endl
            << std::endl;
}


struct ParseCommand
{
 public:
  ParsedCommand parsed;
  bool get_for_cmake_target = false;

 private:
  enum struct Option { None = 0, InputPackage, WorkDir };
  enum struct MultiArgs { None = 0, InputPackages };

 public:
  ParseCommand( int argc, char * argv[] ) {

    //
    std::vector<std::string> args( argv + 1, argv + argc );

    //
    Option option{Option::None};
    MultiArgs multiArgs{MultiArgs::None};

    //
    for ( auto it = args.cbegin(); it != args.cend(); ++it ) {
      const std::string & argument = *it;
      //
      if ( option != Option::None ) {
        if ( option == Option::InputPackage )
          parsed.input_packages.emplace_back( argument );
        else if ( option == Option::WorkDir )
          parsed.work_dir = argument;
        //
        option = Option::None;
        multiArgs = MultiArgs::None;
      }
      else {
        if ( ( argument == "--help" ) || ( argument == "-h" ) )
        {help( ); exit( EXIT_SUCCESS );}
        else if ( argument == "--input-package" )
          option = Option::InputPackage;
        else if ( argument == "--input-packages" )
          multiArgs = MultiArgs::InputPackages;
        else if ( argument == "--work-dir" )
          option = Option::WorkDir;
        else if ( argument == "--get-for-cmake-target" )
          get_for_cmake_target = true;
        else {
          if ( multiArgs == MultiArgs::InputPackages )
            parsed.input_packages.emplace_back( argument );
        }
      }
    }
    //
    if ( option != Option::None )
      throw std::runtime_error( "One option need an argument" );

    //
    if ( ( parsed.input_packages.empty() ) || parsed.work_dir.empty() )
      throw std::runtime_error( "Need ('--input-package' | '--input-packages') and '--work-dir' params" );
  }
};


int main( int argc, char * argv[] )
{
  try
  {
    const ParseCommand args{argc, argv};
    try
    {
      embedded_resource_packager erp( args.parsed );
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




