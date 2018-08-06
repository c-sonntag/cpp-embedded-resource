#include <erc_maker/src_generator.h>

#include <erc_maker/src_internal_names.h>

#include <fstream>
#include <sstream>

namespace erc_maker {

  void src_generator::generate_package( const erc_prepared_package & pp, const std::string & output_src_file )
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
             << "* @brief Generated Package file for EmbeddedResource lib." << endl
             << "* @note Package file can be found at" << endl
             << "*       " << pp.package.erc_package_filepath << endl
             << "*/" << endl
             << endl;

      //
      output << "#include <erc/package.h>" << endl
             << endl
             << "namespace erc {" << endl
             << "  namespace " << src_internal_names::global_namespace() << " {" << endl
             << endl;

      //
      for ( const erc_file_identifier & file_id : pp.files_identifier )
        output << "    const extern erc::embedded_file " << src_internal_names::to_extern_erc( file_id ) << ";" << endl;

      //
      output << "    static const erc::embedded_file * const embedded_files[]" << endl
             << "    {" << endl;
      for ( const erc_file_identifier & file_id : pp.files_identifier )
        output << "      &" << src_internal_names::to_extern_erc( file_id ) << "," << endl;
      output << "    };" << endl
             << endl;

      //
      output << "    extern const erc::package " << src_internal_names::to_extern_package( pp ) << ";" << endl
             << "    const erc::package " << src_internal_names::to_extern_package( pp ) << endl
             << "    {" << endl
             << "      \"" << pp.package.content.package_name << "\"," << endl
             << "      " << pp.files_identifier.size() << "," << endl
             << "      embedded_files" << endl
             << "    };" << endl
             << endl
             << "  }" << endl
             << "}" << endl
             << endl;
    }
    catch ( const std::exception & e )
    { throw std::runtime_error( "[embedded_rc::erc_maker::src_generator::generate_package] " + std::string( e.what() ) ); }
  }

}
