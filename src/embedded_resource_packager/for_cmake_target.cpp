#include "head.hpp"

#include <iostream>
#include <exception>
#include <vector>
#include <unordered_map>
#include <unordered_set>



std::ostream & operator<<( std::ostream & os, const erc_maker::src_generator::generation_rapport::file_added & fa )
{ os << fa.file; return os; }

std::ostream & operator<<( std::ostream & os, const std::pair<std::string, erc_maker::file_property_found> & ff_pair )
{ os << ff_pair.second.path; return os; }

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

// ---- ---- ---- ----

void embedded_resource_packager::for_cmake_target()
{

  //
  generator.generate_into( work_dir, true );
  const erc_maker::src_generator::generation_rapport & rapport( generator.get_rapport() );

  //
  const char * delimiter( "\n" );

  //
  std::cout << "Package:" << generator.names_generator.to_extern_package() << delimiter
            << "InputFiles:" << files.files_found << delimiter
            << "GeneratedFiles:" << rapport.filepath_list << delimiter
            << "NotFoundModelFiles:" << files.files_not_found << delimiter
            << "NotFoundModelDirs:" << files.directories_not_found << delimiter
            ;
}

