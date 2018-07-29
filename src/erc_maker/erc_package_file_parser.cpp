#include <erc_maker/erc_package_file_parser.h>

#include <erc_maker/model.h>

#include <memory>
#include <stdexcept>
#include <list>
#include <string>
#include <regex>

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

#include <tinyxml2.h>


namespace erc_maker {

  static const std::regex valid_filename( "[^\\\\/:*?!\"<>|^\n\t]+" );
  static const std::regex valid_path( "[^\\\\:*?!\"<>|^\n\t]+" );

  // ---- ----

  struct internal_parser
  {
    const erc_package_file_parser & erc_parsed_content;
    model & content;

    internal_parser( erc_package_file_parser & _erc_parsed_content );

    void parse_tag_package_name( const std::string & tag_text );
    void parse_tag_prefix( const std::string & tag_text );

    void parse_tag_file( const tinyxml2::XMLElement & e );
    void parse_tag_directory( const tinyxml2::XMLElement & e );
  };


  // ---- ---- ---- ----

  internal_parser::internal_parser( erc_package_file_parser & _erc_parsed_content ) :
    erc_parsed_content( _erc_parsed_content ),
    content( _erc_parsed_content.content )
  {

    using namespace tinyxml2;

    XMLDocument doc;
    doc.LoadFile( erc_parsed_content.erc_package_filepath.c_str() );

    XMLPrinter printer;
    doc.Print( &printer );

    try
    {

      //
      std::list<std::string> erc_xml_error;

      //
      const XMLElement * root_erc( doc.RootElement() );
      if ( !root_erc )
        throw std::runtime_error( "Can't find root element" );

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
            parse_tag_package_name( tag_text );
          else if ( tag_name == "prefix" )
            parse_tag_prefix( tag_text );
          else if ( tag_name == "file" )
            parse_tag_file( e );
          else if ( tag_name == "directory" )
            parse_tag_directory( e );
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
        { err_on_this_tag(); erc_xml_error.emplace_back( "  " + e ); }
        catch ( const std::exception & e )
        { err_on_this_tag(); erc_xml_error.emplace_back( "  " + std::string( e.what() ) ); }

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

    //
    if ( content.package_name.empty() )
      content.package_name = fs::path( erc_parsed_content.erc_package_filepath ).stem().string();
  }

  // ---- ---- ---- ----

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

  // ---- ----

  inline basic_link basic_link_tag_inheritance( const tinyxml2::XMLElement & e )
  {
    basic_link bl;

    bl.path = e.GetText();
    bl.compress = e.BoolAttribute( "compress", false );

    return bl;
  }

  // ---- ----

  void internal_parser::parse_tag_package_name( const std::string & tag_text )
  {
    if ( !std::regex_match( tag_text, valid_filename ) )
      throw "incompatible \"" + tag_text + "\"";
    content.package_name = tag_text;
  }

  void internal_parser::parse_tag_prefix( const std::string & tag_text )
  {
    if ( !std::regex_match( tag_text, valid_path ) )
      throw "incompatible \"" + tag_text + "\"";
    content.prefix = tag_text;
  }

  void internal_parser::parse_tag_file( const tinyxml2::XMLElement & e )
  {
    // const file f( file( basic_link_tag_inheritance( e ) ) );
    content.files.emplace_back( basic_link_tag_inheritance( e ) );
  }

  void internal_parser::parse_tag_directory( const tinyxml2::XMLElement & e )
  {
#define SET_FROM_ATTRIBUTE_STR( var, attr_name ) \
  if ( const char * const v = e.Attribute( attr_name ) ) \
    var = std::string( v );

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

  // ---- ---- ---- ----

  erc_package_file_parser::erc_package_file_parser( const std::string _erc_package_filepath ) :
    erc_package_filepath( std::move( _erc_package_filepath ) )
  {
    try
    {
      internal_parser parser( *this );
    }
    catch ( const std::exception & e )
    {
      throw std::runtime_error( "[embedded_rc::erc_maker::erc_package_file_parser] errors on file '" + erc_package_filepath + "' : \n"
                                + std::string( e.what() ) );
    }

  }

}
