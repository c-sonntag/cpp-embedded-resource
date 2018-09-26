#include <erc_maker/file_system.h>

#include <chrono>
#include <thread>

//#ifdef _WIN32
//  #include <windows.h>
//#elif __APPLE__
//#   error "No Apple implementation"
//#elif __linux__
//#   error "No Linux implementation"
//#else
//#   error "Unknown compiler"
//#endif

namespace erc_maker {

  bool lock_file( const std::string & file_path, const uint timeout_millis, const uint max_write_datetime_diff_seconds )
  {
    //
    const std::string lock_file_path( file_path + ".lock" );

    //
    if ( !fs::exists( lock_file_path ) )
    {
      std::ofstream filock( lock_file_path, std::ios::out | std::ios::binary );
      filock << 1;
      return filock.is_open(); // implicit filock.close();
    }

    //
    {
      const fs::file_time_type file_ftime( fs::last_write_time( file_path ) );
      const std::time_t file_cftime( fs::file_time_type::clock::to_time_t( file_ftime ) );
      const std::time_t current_time( std::time( nullptr ) );
      const uint time_diff_seconds( uint( std::max( std::difftime( current_time, file_cftime ), 0. ) ) );
      if ( time_diff_seconds > max_write_datetime_diff_seconds )
      {
        std::ofstream filock( lock_file_path, std::ios::out | std::ios::binary );
        filock << 1;
        return filock.is_open(); // implicit filock.close();
      }
    }

    //
    {
      static constexpr uint millis_count = 20;
      uint elapsed_millis = 0;
      //
      do
      {
        if ( elapsed_millis >= timeout_millis )
          return false;

        //
        std::this_thread::sleep_for( std::chrono::milliseconds( millis_count ) );
        elapsed_millis += millis_count;
      }
      while ( fs::exists( lock_file_path ) );
    }

    return true;
  }

  bool unlock_file( const std::string & file_path )
  {
    const std::string lock_file_path( file_path + ".lock" );
    if ( fs::exists( lock_file_path ) )
      return  fs::remove( lock_file_path );
    return false;
  }


  //  #ifdef _WIN32

  //  #elif __APPLE__
  //#   error "Unknown Apple platform"
  //  #elif __linux__
  //  // linux
  //  #else
  //#   error "Unknown compiler"
  //  #endif

}
