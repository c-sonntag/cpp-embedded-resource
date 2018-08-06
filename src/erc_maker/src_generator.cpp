#include <erc_maker/src_generator.h>

#include <erc_maker/src_internal_names.h>
#include <erc_maker/file_system.h>

#include <cstring>
#include <stdexcept>

#include <picosha2.h>

namespace erc_maker {


  inline void src_generator::generation_rapport::insert( const std::string & file, const std::string & filepath, bool generated )
  {
    file_list.emplace_back( file_added{file, generated} );
    filepath_list.emplace_back( file_added{filepath, generated} );
    if ( generated ) ++nb_generated;
    else             ++nb_passed;
  }

  inline void src_generator::generation_rapport::reset()
  {
    file_list.clear();
    filepath_list.clear();
    nb_generated = 0;
    nb_passed = 0;
  }

  // ---- ---- ---- ----

  //inline hash256 src_generator::make_hash_for( const erc_maker::file & file ) const
  //{
  //  return hash256( package_unique_identifier.hex + ":" + file.path );
  //}

  // ---- ----

  src_generator::src_generator( const erc_inventory & _inventory ) :
    inventory( std::move( _inventory ) ),
    inventory_cache( inventory )
  { }

  // ---- ----

  void src_generator::open_caches_if_exists_into( const std::string & erc_working_directorypath )
  {
    inventory_cache.open_if_exist_into( erc_working_directorypath );
  }
  void src_generator::save_caches_into( const std::string & erc_working_directorypath ) const
  {
    inventory_cache.save_into( erc_working_directorypath );
  }

  // ---- ----

  void src_generator::generate_into( const std::string & erc_output_directorypath, bool generated_list_only )
  {

    //
    rapport.reset();

    //
    const fs::path output_directorypath( erc_output_directorypath );

    //
    bool have_new_package( false );

    //
    for ( const erc_prepared_package & pp : inventory.prepared_packages )
    {
      bool have_new_erc_embedded( false );

      for ( const erc_file_identifier & file_id : pp.files_identifier )
      {

        //
        const std::string erc_embedded_file_str( src_internal_names::to_file_erc( file_id ) );
        const fs::path erc_embedded_filepath( output_directorypath / fs::path( erc_embedded_file_str ) );

        //
        const bool not_exist( !fs::exists( erc_embedded_filepath ) );
        if ( not_exist ) have_new_erc_embedded = true;

        //
        //const bool need_generate( !cache_have_same_file( file_id ) || not_exist );
        const bool need_generate( !inventory_cache.have_same_file( file_id ) );
        rapport.insert( erc_embedded_file_str, generic_string_path( erc_embedded_filepath ), need_generate );

        //
        if ( !generated_list_only && need_generate )
          generate_file( file_id, erc_embedded_filepath.string() );
      }

      {
        //
        const std::string erc_package_file_str( src_internal_names::to_file_package( pp ) );
        const fs::path erc_package_filepath( output_directorypath / fs::path( erc_package_file_str ) );

        //
        const bool not_exist( !fs::exists( erc_package_filepath ) );
        if ( not_exist ) have_new_package = true;

        //
        const bool need_generate( not_exist || have_new_erc_embedded );
        rapport.insert( erc_package_file_str, generic_string_path( erc_package_filepath ), need_generate );

        //
        if ( !generated_list_only && need_generate )
          generate_package( pp, erc_package_filepath.string() );
      }
    }

    {
      //
      const std::string erc_inventory_file_str( src_internal_names::to_file_inventory( inventory ) );
      const fs::path erc_inventory_filepath( output_directorypath / fs::path( erc_inventory_file_str ) );

      //
      const bool need_generate(
        !fs::exists( erc_inventory_filepath ) ||
        have_new_package ||
        !inventory_cache.same_inventory()
      );
      rapport.insert( erc_inventory_file_str, generic_string_path( erc_inventory_filepath ), need_generate );

      //
      if ( !generated_list_only && need_generate )
        generate_inventory( erc_inventory_filepath.string() );
    }

  }


}

