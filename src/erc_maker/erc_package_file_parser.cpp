#include <erc_maker/erc_package_file_parser.h>

#include <erc_maker/model.h>
#include <erc_maker/file_system.h>

#include <memory>
#include <stdexcept>
#include <list>
#include <string>
#include <regex>

#include <tinyxml2.h>

namespace erc_maker {

  static const std::regex valid_filename( "[^\\\\/:*?!\"<>|^\n\t]+" );
  static const std::regex valid_path( "[^\\\\:*?!\"<>|^\n\t]+" );

  // ---- ----

  struct internal_parser
  {
   public:
    struct
    {
      bool compress = false;
    } default_config;

   public:
    const erc_package_file_parser & erc_parsed_content;
    model & content;

   public:
    internal_parser( erc_package_file_parser & _erc_parsed_content );

   public:
    void parse_attributes_erc( const tinyxml2::XMLElement & e );

   private:
    inline basic_link basic_link_tag_inheritance( const tinyxml2::XMLElement & e );

   public:
    void parse_tag_package_name( const std::string & tag_text );
    void parse_tag_prefix( const std::string & tag_text );

   private:
    bool compil_regex( directory::regex_tag & rt );

   public:
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
    const XMLError open_error_code( doc.LoadFile( erc_parsed_content.erc_package_filepath.c_str() ) );
    if ( open_error_code == XML_ERROR_FILE_NOT_FOUND )
      throw std::runtime_error( "[XMLError] XMLError(XML_ERROR_FILE_NOT_FOUND) on opening file : " + erc_parsed_content.erc_package_filepath );
    if ( open_error_code != 0 )
      throw std::runtime_error( "[XMLError] XMLErrorCode(" + std::to_string( static_cast<int>( open_error_code ) ) + ") on opening file : " + erc_parsed_content.erc_package_filepath );

    // XMLPrinter printer;
    // doc.Print( &printer );

    try
    {

      //
      std::list<std::string> erc_xml_error;

      //
      const XMLElement * const root_erc( doc.RootElement() );
      if ( !root_erc )
        throw std::runtime_error( "Can't find root element like '<erc>' tag" );

      //
      if ( std::string( root_erc->Name() ) != "erc" )
        erc_xml_error.emplace_back( "Root element need to be 'erc' tag" );

      //
      parse_attributes_erc( *root_erc );

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
          //else if ( tag_name == "source" )
          //    parse_tag_source( e );
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


  void internal_parser::parse_attributes_erc( const tinyxml2::XMLElement & e )
  {
    default_config.compress = e.BoolAttribute( "default-compress", false );
  }

  // ---- ----

  std::string normalize_prefix( const std::string & p )
  {
    if ( !std::regex_match( p, valid_path ) )
      throw "incompatible prefix path \"" + std::string( p ) + "\"";
    std::string normalized( generic_string_path( p ) );
    if ( !normalized.empty() )
      if ( normalized.back() != '/' )
        normalized += "/";
    return normalized;
  }

  // ---- ----

  inline basic_link internal_parser::basic_link_tag_inheritance( const tinyxml2::XMLElement & e )
  {
    basic_link bl;

    //
    bl.path = e.GetText();
    bl.compress = e.BoolAttribute( "compress", default_config.compress );

    //
    const char * const att_prefix( e.Attribute( "prefix" ) );
    if ( att_prefix )
      bl.prefix = normalize_prefix( std::string( att_prefix ) );

    //
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
    content.prefix = normalize_prefix( tag_text );
  }

  // ---- ---- ---- ----


  inline bool internal_parser::compil_regex( directory::regex_tag & rt )
  {
    rt.set = false;
    if ( !rt.str.empty() )
    {
      try
      {
        rt.rgx = std::regex( rt.str );
        rt.set = true;
      }
      catch ( const std::regex_error & )
      {
        return false;
        //if ( e.code() == std::regex_constants::error_badrepeat )
        //  std::cerr << "Repeat was not preceded by a valid regular expression.\n";
        //else std::cerr << "Some other regex exception happened.\n";
      }
    }
    return true;
  }

  // ---- ----

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

    SET_FROM_ATTRIBUTE_STR( d.regex_patern.str, "regex_patern" )
    SET_FROM_ATTRIBUTE_STR( d.regex_extension.str, "regex_extension" )

    std::list<std::string> regex_xml_errors;

    if ( !compil_regex( d.regex_patern ) )
      regex_xml_errors.emplace_back( "Invalid regex_patern : " + d.regex_patern.str );

    if ( !compil_regex( d.regex_extension ) )
      regex_xml_errors.emplace_back( "Invalid regex_extension : " + d.regex_extension.str );

    if ( !regex_xml_errors.empty() )
      throw regex_xml_errors;

    content.directories.emplace_back( d );
  }

  // ---- ---- ---- ----

  erc_package_file_parser::erc_package_file_parser( const std::string _erc_package_filepath ) :
    erc_package_filepath( generic_string_path( std::move( _erc_package_filepath ) ) ),
    erc_package_absolute_filepath( generic_string_path( fs::absolute( fs::path( erc_package_filepath ) ) ) )
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
