#include <erc_maker/src_generator.h>

#include <erc_maker/src_internal_names.h>

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

      //
      output << "#include <erc/inventory_package.h>" << endl
             << endl
             << "#define for_map(pack) {pack.name, &pack}" << endl
             << endl
             << "namespace erc {" << endl
             << "  namespace " << src_internal_names::global_namespace() << " {" << endl
             << endl;

      for ( const erc_prepared_package & pp : inventory.prepared_packages )
        output << "    const extern erc::package " << src_internal_names::to_extern_package( pp ) << ";" << endl;
      output << endl;

      // output << "    const erc::inventory_package ERC_INVENTORY_PACKAGE_EXTERN_NAME" << endl
      output << "    const erc::inventory_package " << src_internal_names::to_extern_inventory( inventory ) << endl
             << "    {" << endl;

      for ( const erc_prepared_package & pp : inventory.prepared_packages )
        output << "      for_map(" << src_internal_names::to_extern_package( pp ) << ")," << endl;

      output << "    };" << endl
             << endl
             << "  }" << endl
             << "}" << endl
             << endl;


    }
    catch ( const std::exception & e )
    { throw std::runtime_error( "[embedded_rc::erc_maker::src_generator::generate_inventory] " + std::string( e.what() ) ); }
  }

}
