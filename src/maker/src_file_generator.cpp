#include <erc/maker/src_file_generator.h>

#include <erc/maker/model.h>

#include <memory>

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

namespace erc {
  namespace maker {

    //    struct internal_listner
    //    {
    //      const erc_file_parser & erc_parsed_content;
    //      const fs::path erc_file_path;
    //      const fs::path erc_directory_path;

    //      erc_files_list & base;

    //      internal_listner( const erc_file_parser & _erc_parsed_content, erc_files_list & _base );

    //      void push_file( const file & f, const fs::path & f_path );

    //      void push_file( const file & f );
    //      void push_directory( const directory & d );
    //    };

    // ---- ----

    //    internal_listner::internal_listner( const erc_file_parser & _erc_parsed_content, erc_files_list & _base ) :
    //      erc_parsed_content( _erc_parsed_content ),
    //      erc_file_path( erc_parsed_content.erc_file_path ),
    //      erc_directory_path( erc_file_path.parent_path() ),
    //      base( _base )
    //    {

    //      //
    //      for ( const file & f : erc_parsed_content.content.files )
    //        push_file( f );

    //      //
    //      for ( const directory & d : erc_parsed_content.content.directories )
    //        push_directory( d );

    //    }

    //    void internal_listner::push_file( const file & f, const fs::path & f_path )
    //    {
    //      if ( fs::exists( f_path ) )
    //      {
    //        const file_property property
    //        {
    //          f_path.filename().string(),
    //          f_path.extension().string(),
    //          fs::file_size( f_path )
    //        };
    //        base.files_found.emplace_back( f, property, f_path.string() );
    //      }
    //      else
    //        base.files_not_found.emplace_back( f.path );

    //    }

    //    void internal_listner::push_file( const file & f )
    //    {

    //      //
    //      const fs::path f_path( f.path );

    //      if ( f_path.is_absolute() )
    //        push_file( f, f_path );
    //      else
    //      {
    //        const fs::path f_absolute_path( fs::absolute( erc_directory_path / f_path ) );
    //        push_file( f, f_absolute_path );
    //      }

    //    }

    //    void internal_listner::push_directory( const directory & d )
    //    {
    //      // const file f( file( basic_link_tag_inheritance( e ) ) );
    //      // content.files.emplace_back( basic_link_tag_inheritance( e ) );
    //    }

    // ---- ---- ---- ----

    src_file_generator::src_file_generator( const std::string _input_file, const std::string _output_src_file ) :
      input_file( std::move( _input_file ) ),
      output_src_file( std::move( _output_src_file ) )
    {

      try
      {

        //        //
        //        internal_listner listner( erc_parsed_content, *this );

      }
      //catch ( const std::exception & e )
      catch ( ... )
      {
        throw;
        //        throw std::runtime_error( "[embedded_rc::maker::erc_files_list] bad link on file '" + erc_parsed_content.erc_file_path + "' : \n"
        //                                  + std::string( e.what() ) );
      }

    }

  }
}
