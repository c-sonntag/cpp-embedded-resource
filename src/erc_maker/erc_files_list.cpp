#include <erc_maker/erc_files_list.h>

#include <erc_maker/types.h>
#include <erc_maker/model.h>
#include <erc_maker/file_system.h>

#include <memory>
#include <stdexcept>
#include <list>
#include <string>
#include <regex>
#include <unordered_set>

#include <bits/stdc++.h>


namespace erc_maker {

  struct internal_listner
  {
    const erc_package_file_parser & erc_parsed_content;
    const fs::path erc_package_filepath;
    const fs::path erc_directory_path;

    erc_files_list & base;

    std::unordered_set<std::string> same_filepath;

    internal_listner( const erc_package_file_parser & _erc_parsed_content, erc_files_list & _base );

    void push_file( const file & f );
    void push_file( const file & f, const fs::path & f_path );

    void push_directory( const directory & d );
    void push_directory( const directory & d, const fs::path & d_path, const std::string & push_file_sub_dir = "" );
  };

  // ---- ----

  internal_listner::internal_listner( const erc_package_file_parser & _erc_parsed_content, erc_files_list & _base ) :
    erc_parsed_content( _erc_parsed_content ),
    erc_package_filepath( erc_parsed_content.erc_package_filepath ),
    erc_directory_path( erc_package_filepath.parent_path() ),
    base( _base )
  {

    //
    for ( const file & f : erc_parsed_content.content.files )
      push_file( f );

    //
    for ( const directory & d : erc_parsed_content.content.directories )
      push_directory( d );

    //
    if ( !same_filepath.empty() )
    {
      std::stringstream ss;
      for ( const std::string & p : same_filepath )
        ss << "  " << p << std::endl;
      throw std::runtime_error( "Some file path are similars : \n" + ss.str() );
    }

  }

  // ---- ---- ---- ----

  void internal_listner::push_file( const file & f )
  { push_file( f, f.path ); }

  void internal_listner::push_file( const file & f, const fs::path & f_path )
  {
    const fs::path f_absolute_path(
      f_path.is_absolute() ? f_path : ( fs::absolute( erc_directory_path / f_path ) )
    );
    if ( fs::exists( f_absolute_path ) )
    {
      const uint64_t file_size( fs::file_size( f_absolute_path ) );
      if ( file_size > UINT_MAX )
        throw std::runtime_error( "File size reached, " + std::to_string( file_size ) + " <= " + std::to_string( UINT_MAX ) );

      const erc::file_property property
      {
        f_absolute_path.filename().string(),
        f_absolute_path.extension().string(),
        static_cast<uint>( file_size ),
        fs::file_time_type::clock::to_time_t( fs::last_write_time( f_absolute_path ) )
      };

      auto find_it( base.files_found.find( f.path ) );
      if ( find_it != base.files_found.end() )
      {
        same_filepath.emplace( find_it->first );
        find_it->second = file_property_found( f, property, generic_string_path( f_absolute_path ) );
      }
      else
        base.files_found.emplace( f.path, file_property_found( f, property, generic_string_path( f_absolute_path ) ) );
    }
    else
      base.files_not_found.emplace( f.path );
  }

  // ---- ---- ---- ----

  void internal_listner::push_directory( const directory & d )
  { push_directory( d, d.path ); }

  void internal_listner::push_directory( const directory & d, const fs::path & d_path, const std::string & push_file_sub_dir )
  {
    const fs::path d_absolute_path(
      d_path.is_absolute() ? d_path : ( fs::absolute( erc_directory_path / d_path ) )
    );
    if ( fs::exists( d_absolute_path ) )
    {
      for ( const fs::path & p : fs::directory_iterator( d_absolute_path ) )
      {
        const std::string p_filename( p.filename().string() );
        if ( fs::is_regular_file( p ) )
        {
          file f( d );
          f.path = generic_string_path( push_file_sub_dir + p_filename );
          push_file( f, p );
        }
        else if ( fs::is_directory( p ) )
          push_directory( d, p, p_filename + "/" );
      }

    }
    else
      base.directories_not_found.emplace( d.path );


    // const file f( file( basic_link_tag_inheritance( e ) ) );
    // content.files.emplace_back( basic_link_tag_inheritance( e ) );
  }

  // ---- ---- ---- ----

  erc_files_list::erc_files_list( const erc_package_file_parser & erc_parsed_content )
  {

    try
    {

      //
      internal_listner listner( erc_parsed_content, *this );

    }
    catch ( const std::exception & e )
    {
      throw std::runtime_error( "[embedded_rc::erc_maker::erc_files_list] error on file '" + erc_parsed_content.erc_package_filepath + "' : \n"
        + std::string( e.what() ) );
    }

  }

}
