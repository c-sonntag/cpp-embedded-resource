#include <erc/maker/erc_file_parser.h>

#include <erc/maker/model.h>

#include <memory>
#include <stdexcept>
#include <list>
#include <string>
#include <regex>

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

#include <tinyxml2.h>


namespace erc {
  namespace maker {


#define SET_FROM_ATTRIBUTE_STR( var, attr_name ) \
  if ( const char * const v = e.Attribute( attr_name ) ) \
    var = std::string( v );

    inline bool check_regex( const std::string & r )
    {
      try
      {
        std::regex myregex( r );
      }
      catch ( const std::regex_error & )
      {
        return false;
        //if ( e.code() == std::regex_constants::error_badrepeat )
        //  std::cerr << "Repeat was not preceded by a valid regular expression.\n";
        //else std::cerr << "Some other regex exception happened.\n";
      }
      return true;
    }

    inline basic_link basic_link_tag_inheritance( const tinyxml2::XMLElement & e )
    {
      basic_link bl;

      bl.path = e.GetText();
      bl.compress = e.BoolAttribute( "compress", false );

      return bl;
    }

    void parse_tag_file( const tinyxml2::XMLElement & e, model & content )
    {
      // const file f( file( basic_link_tag_inheritance( e ) ) );
      content.files.emplace_back( basic_link_tag_inheritance( e ) );
    }

    void parse_tag_directory( const tinyxml2::XMLElement & e, model & content )
    {
      directory d( basic_link_tag_inheritance( e ) );

      SET_FROM_ATTRIBUTE_STR( d.regex_patern, "regex_patern" )
      SET_FROM_ATTRIBUTE_STR( d.regex_extension, "regex_extension" )

      std::list<std::string> regex_xml_errors;

      if ( !d.regex_patern.empty() )
        if ( !check_regex( d.regex_patern ) )
          regex_xml_errors.emplace_back( "Invalid regex_patern : " + d.regex_patern );

      if ( !d.regex_extension.empty() )
        if ( !check_regex( d.regex_extension ) )
          regex_xml_errors.emplace_back( "Invalid regex_extension : " + d.regex_extension );

      if ( !regex_xml_errors.empty() )
        throw regex_xml_errors;

      content.directories.emplace_back( d );
    }

    // ---- ----

    erc_file_parser::erc_file_parser( const std::string _erc_file_path ) :
      erc_file_path( std::move( _erc_file_path ) )
    {
      using namespace tinyxml2;

      try
      {

        XMLDocument doc;
        doc.LoadFile( erc_file_path.c_str() );

        XMLPrinter printer;
        doc.Print( &printer );

        try
        {
          //
          std::list<std::string> erc_xml_error;

          //
          const XMLElement * root_erc( doc.RootElement() );
          if ( !root_erc )
            throw std::string( "Can't find root element" );

          //
          if ( std::string( root_erc->Name() ) != "erc" )
            erc_xml_error.emplace_back( "Root element need to be 'erc' tag" );

          //
          for (
            const XMLElement * e_p( root_erc->FirstChildElement() );
            e_p != nullptr;
            e_p = e_p->NextSiblingElement()
          )
          {

            //
            const XMLElement & e( *e_p );
            const std::string tag_name( e.Value() );
            const std::string tag_text( e.GetText() );

            //
            const auto err_on_this_tag( [&erc_xml_error, &tag_name]()
            { erc_xml_error.emplace_back( "tag <" + tag_name + "> have error on :" );  } );

            try
            {

              //
              if ( tag_name == "package_name" )
                content.package_name = tag_text;
              else if ( tag_name == "prefix" )
                content.prefix = tag_text;
              else if ( tag_name == "file" )
                parse_tag_file( e, content );
              else if ( tag_name == "directory" )
                parse_tag_directory( e, content );
              else
                erc_xml_error.emplace_back( "unknown tag <" + tag_name + ">" );

            }
            catch ( const std::list<std::string> & errors )
            {
              err_on_this_tag();
              for ( const std::string & e : errors )
                erc_xml_error.emplace_back( "  " + e );
            }
            catch ( const std::string & e )
            { err_on_this_tag(); erc_xml_error.emplace_back( e ); }
            catch ( const std::exception & e )
            { err_on_this_tag(); erc_xml_error.emplace_back( e.what() ); }

          }

          //
          if ( !erc_xml_error.empty() )
            throw erc_xml_error;

        }
        catch ( const std::list<std::string> & errors )
        {
          std::string errors_str;
          for ( const std::string & e : errors )
            errors_str += ( errors_str.empty() ? "  - " : "\n  - " ) + e;
          throw std::runtime_error( errors_str );
        }
        catch ( const std::string & e )
        { throw std::runtime_error( "  - " + e ); }

      }
      catch ( const std::exception & e )
      {
        throw std::runtime_error( "[embedded_rc::maker::erc_file_parser] errors on file '" + erc_file_path + "' : \n"
                                  + std::string( e.what() ) );
      }

      //
      if ( content.package_name.empty() )
        content.package_name = fs::path( erc_file_path ).stem().string();



    }

  }
}
