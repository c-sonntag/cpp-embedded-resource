#include <erc/file_stream.h>

#include <sstream>
#include <streambuf>


namespace erc {

  // /** @note from-author https://stackoverflow.com/a/7782037 */
  //
  // struct internal_membuf : std::streambuf
  // {
  //   inline internal_membuf( char * begin, char * end ) {
  //     this->setg( begin, begin, end );
  //   }
  //   virtual ~internal_membuf() = default;
  // };
  //
  // file_stream::file_stream( const embedded_file & _ef ) :
  //   ef( std::move( _ef ) ),
  //   membuf_up(std::make_unique<internal_membuf>(ef.data, ef.data + ef.property.size))
  // {}

}

