#include "head.hpp"

#include <iostream>
#include <exception>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <erc_maker/src_internal_names.h>
#include <erc_maker/custom_unordered_set.h>


std::ostream & operator<<( std::ostream & os, const erc_maker::src_generator::generation_rapport::file_added & fa )
{ os << fa.file; return os; }

//std::ostream & operator<<( std::ostream & os, const std::pair<std::string, erc_maker::file_property_found> & ff_pair )
//{ os << ff_pair.second.path; return os; }

std::ostream & operator<<( std::ostream & os, const erc_maker::erc_file_identifier * const efi )
{ os << efi->valid_input_file.path; return os; }

// ---- ----

template<typename T>
void iterate_on( std::ostream & os, const T & container )
{
  auto it( container.cbegin() );
  if ( it != container.end() )
    std::cout << *it;
  const auto end_it( container.cend() );
  for ( ; it != end_it; ++it )
    std::cout << ";" << *it;
}

// ---- ----

template<typename T>
std::ostream & operator<<( std::ostream & os, const std::vector<T> & vec )
{ iterate_on( os, vec ); return os;}

template<typename T1, typename T2>
std::ostream & operator<<( std::ostream & os, const std::unordered_map<T1, T2> & map )
{ iterate_on( os, map ); return os;}

template<typename T>
std::ostream & operator<<( std::ostream & os, const std::unordered_set<T> & set )
{ iterate_on( os, set ); return os;}

template<typename T1, typename T2, typename T3>
std::ostream & operator<<( std::ostream & os, const std::unordered_set<T1, T2, T3> & set )
{ iterate_on( os, set ); return os;}

// ---- ---- ---- ----



void embedded_resource_packager::for_cmake_target()
{

  //
  src_generator.generate_into( parsed.work_dir, true );
  const erc_maker::src_generator::generation_rapport & rapport( src_generator.get_rapport() );

  //
  const char * delimiter( "\n" );

  //
  std::unordered_set<erc_maker::erc_files_list::not_found_path_t::value_type> files_not_found;
  std::unordered_set<erc_maker::erc_files_list::not_found_path_t::value_type> directories_not_found;
  for ( const erc_maker::erc_prepared_package & pp : src_generator.inventory.prepared_packages )
  {
    const erc_maker::erc_files_list & files( pp.files );
    files_not_found.insert( files.files_not_found.cbegin(), files.files_not_found.cend() );
    directories_not_found.insert( files.directories_not_found.cbegin(), files.directories_not_found.cend() );
  }

  //
  std::cout << "Inventory:" <<  erc_maker::src_internal_names::to_extern_inventory( src_generator.inventory ) << delimiter
            << "InputFiles:" << src_generator.inventory.files_identifier_p << delimiter
            << "GeneratedFiles:" << rapport.filepath_list << delimiter
            << "NotFoundModelFiles:" << files_not_found << delimiter
            << "NotFoundModelDirs:" << directories_not_found << delimiter
            ;
}

