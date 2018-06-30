#pragma once

#include <iostream>
#include <iomanip>

namespace erc {

#define OUTPUT_VAR(var) " " #var "(" << var << ") "
#define OV(var) OUTPUT_VAR(var)

  // inline std::ostream & operator<<( std::ostream & os, const QPoint & p )
  // {
  //   os << std::setprecision( 2 );
  //   os << std::setw( 5 ) << p.x() << "," << std::setw( 5 ) << p.y();
  //   return os;
  // }

}
