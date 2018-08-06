#include <erc_maker/src_generator.h>

#include <fstream>
#include <sstream>

namespace erc_maker {

  void src_generator::generate_inventory( const std::string & output_src_file )
  {

    //
    using std::endl;

    try
    {

      //
      std::ofstream output( output_src_file, std::ofstream::out | std::ofstream::trunc );
      if ( !output )
        throw std::runtime_error( "can't write <output_src_file> at " + output_src_file );

      //
      output << "/**" << endl
             << "* @brief Generated Inventory file for EmbeddedResource lib." << endl
             << "*/" << endl
             << endl;

      /**< @todo */

    }
    catch ( const std::exception & e )
    { throw std::runtime_error( "[embedded_rc::erc_maker::src_generator::generate_inventory] " + std::string( e.what() ) ); }
  }

}
