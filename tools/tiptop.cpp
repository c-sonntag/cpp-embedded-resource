#include <cstdio>
#include <iostream>
#include <exception>
#include <vector>

void help()
{
  std::cout << "Tiptop" << std::endl
            << "By Christophe Sonntag" << std::endl
            << std::endl
            << "   ./tiptop [-h|--help]" << std::endl
            << "" << std::endl
            << "   -h|--help : Print this message" << std::endl
            << std::endl;
}


struct ParseCommand
{
 public:

  //

 private:
  enum struct Option { None = 0 };

 public:
  ParseCommand( int argc, char * argv[] ) {
    //

    //
    if ( argc <= 1 )
      return;
    // if ( argc <= 2 )
    //   throw std::runtime_error( "Need at least 2 arguments" );

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
        option = Option::None;
      }
      else {
        if ( ( argument == "--help" ) || ( argument == "-h" ) )
        {help( ); exit( EXIT_SUCCESS );}
      }
    }
    //
    if ( option != Option::None )
      throw std::runtime_error( "One option need an argument" );
  }
};


int main( int argc, char * argv[] )
{


  try
  {
    const ParseCommand args{argc, argv};

    try
    {


      /* doTipTop() */


    }
    catch ( std::exception & e )
    { std::cerr << "Error process : " << e.what() << std::endl; return EXIT_FAILURE; }
  }
  catch ( std::exception & e )
  { std::cerr << "Error arguments : " << e.what() << std::endl << "See help :" << std::endl << " ----- " << std::endl; help(); return EXIT_FAILURE; }



  return EXIT_SUCCESS;
}




