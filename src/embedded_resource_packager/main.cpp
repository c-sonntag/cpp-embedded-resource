#include <cstdio>
#include <iostream>
#include <exception>
#include <vector>

#include <erc_maker/src_generator.h>

void help()
{
  std::cout << "Embedded resource packager" << std::endl
            << "By Christophe Sonntag" << std::endl
            << std::endl
            << "   ./embedded_resource_packager  " << std::endl
            << "      [-h|--help] |" << std::endl
            << "      [--input-package <erc_xml_package_filepath>]" << std::endl
            << "      [--work-dir <directory_path>]" << std::endl
            << "      (" << std::endl
            << "         [--return-build-files | --return-build-files-path]" << std::endl
            << "         [--return-only-generated] [--cmake-list]" << std::endl
            << "      )" << std::endl
            << "" << std::endl
            << "   -h|--help : Print this message" << std::endl
            << "  --input-package <erc_xml_package_filepath> : ERC Package to be parsed and evaluate" << std::endl
            << "  --work-dir <directory_path>                : Directory to generate files" << std::endl
            << "  --return-build-files                       : Return only file generation in stdout" << std::endl
            << "  --return-build-files-path                  : Return only filepath generation in stdout" << std::endl
            << "  --return-only-generated                    : Return only new file ganerated (need cache)" << std::endl
            << "  --cmake-list                               : Format generation to cmake list with the \";\"" << std::endl
            << std::endl;
}


struct ParseCommand
{
 public:
  std::string input_package;
  std::string work_dir;
  bool return_files = false;
  bool return_files_path = false;
  bool return_only_generated = false;
  bool cmake_list = false;

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
        else if ( argument == "--return-build-files" )
          return_files = true;
        else if ( argument == "--return-build-files-path" )
          return_files_path = true;
        else if ( argument == "--return-only-generated" )
          return_only_generated = true;
        else if ( argument == "--cmake-list" )
          cmake_list = true;
      }
    }
    //
    if ( option != Option::None )
      throw std::runtime_error( "One option need an argument" );

    //
    if ( input_package.empty() || work_dir.empty() )
      throw std::runtime_error( "Need '--input-package' and '--work-dir' params" );

    //
    if ( return_files_path && return_files )
      throw std::runtime_error( "Need only one between '--return-files' and '--return-files-path' params" );
  }
};


int main( int argc, char * argv[] )
{


  try
  {
    const ParseCommand args{argc, argv};

    try
    {
      const erc_maker::erc_package_file_parser erc( args.input_package );
      const erc_maker::erc_files_list files( erc );
      erc_maker::src_generator generator( erc, files );

      if ( args.return_files || args.return_files_path )
      {
        //
        if ( args.return_only_generated )
        {
          try { generator.open_cache_if_exist_into( args.work_dir ); }
          catch ( ... ) {}
        }

        //
        generator.generate_into( args.work_dir, true );
        const erc_maker::src_generator::generation_rapport & rapport( generator.get_rapport() );

        //
        const auto & generated_list(
          args.return_files ? rapport.file_list : rapport.filepath_list
        );

        //
        bool first_passing( false );
        if ( args.cmake_list )
        {
          for ( const auto & f : generated_list )
          {
            if ( args.return_only_generated && !f.generated )
              continue;

            std::cout << ( first_passing ? ";" : "" ) << f.file;
            first_passing = true;
          }
        }
        else
        {
          for ( const auto & f : generated_list )
          {
            if ( args.return_only_generated && !f.generated )
              continue;

            std::cout << ( first_passing ? " " : "" );
            if ( args.return_files_path )
              std::cout << "\"" << f.file << "\"";
            else
              std::cout << f.file;
            first_passing = true;
          }
          std::cout << std::endl;
        }
      }
      else
      {
        //
        static const std::string prefix_out( "       [EmbeddedResource] " );

        //
        std::cout << prefix_out << "File : " << args.input_package << std::endl;

        //
        std::cout << prefix_out << "Opening cache (if exist)" << std::endl;
        try { generator.open_cache_if_exist_into( args.work_dir ); }
        catch ( const std::exception & e )
        { std::cout << prefix_out << "  -> Cache errors : " << e.what() << std::endl; }

        //
        generator.generate_into( args.work_dir );

        //
        const erc_maker::src_generator::generation_rapport & rapport( generator.get_rapport() );
        std::cout << prefix_out << "PackerSuccess : generation(" << rapport.nb_generated << ") passed(" << rapport.nb_passed << ") " << std::endl;

        //
        if ( rapport.nb_generated > 0 )
        {
          std::cout << prefix_out << "Saving changement in cache" << std::endl;
          generator.save_cache_into( args.work_dir );
        }

        // //
        // std::cout << "       See generated files : " << std::endl;
        // const std::vector<std::string> & generated_filepath_list( generator.get_generated_filepath_list() );
        // for ( const std::string & filepath : generated_filepath_list )
        //   std::cout << "  " << filepath << std::endl;
      }

    }
    catch ( std::exception & e )
    { std::cerr << "Error process : " << e.what() << std::endl; return EXIT_FAILURE; }
  }
  catch ( std::exception & e )
  { std::cerr << "Error arguments : " << e.what() << std::endl << "See help :" << std::endl << " ----- " << std::endl; help(); return EXIT_FAILURE; }


  return EXIT_SUCCESS;
}




