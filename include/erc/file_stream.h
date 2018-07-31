#pragma once

#include <erc/classes/non_copyable_movable.hpp>
#include <erc/file.h>

#include <istream>
#include <memory>


namespace erc {

  // struct file_stream : public std::istream
  // {
  //  private:
  //   erc_classes_non_copyable_movable( file_stream )
  //
  //  private:
  //   const embedded_file & ef;
  //   const std::unique_ptr<std::streambuf> membuf_up;
  //
  //  public:
  //   file_stream( const embedded_file & _ef );
  // };
  //
  // // ---- ---- Equal operators ---- ----
  //
  // bool operator==( const file_stream & lhs, const file_stream & rhs );
  //
  // inline bool operator!=( const file_stream & lhs, const file_stream & rhs )
  // { return !( lhs == rhs );  }



}

