#pragma once

#include <unordered_set>

namespace erc_maker {

  template<class SetT, class RawT>
  struct custom_unordered_set_helper_getter
  { static inline const SetT & get( const RawT & r ) { static_cast<SetT>( r ); } };

  template<class SetT, class RawT, class RawTGetter>
  struct custom_unordered_set_helper_hash : public std::hash<SetT>
  {
    size_t operator()( const RawT & a ) const
    { return std::hash<SetT>::operator()( RawTGetter::get( a ) ); }
  };

  template<class SetT, class RawT, class RawTGetter>
  struct custom_unordered_set_helper_equal_comparator : public std::equal_to<SetT>
  {
    bool operator()( const RawT & a, const RawT & b ) const
    { return std::equal_to<SetT>::operator()( RawTGetter::get( a ), RawTGetter::get( b ) ); }
  };

  // ---- ---- ---- ----

  template<class SetT, class RawT, class RawTGetter = custom_unordered_set_helper_getter<SetT, RawT>>
  using custom_unordered_set =
    std::unordered_set <
    RawT, custom_unordered_set_helper_hash<SetT, RawT, RawTGetter>,
    custom_unordered_set_helper_equal_comparator<SetT, RawT, RawTGetter>
    >;

  // ---- ---- ---- ----

  template<class SetT, class RawT>
  struct custom_unordered_set_helper_getter_from_pointer
  { static inline const SetT & get( const RawT & r ) { return *r; } };

  template<class SetT>
  using custom_unordered_set_by_pointer =
    custom_unordered_set <
    SetT,
    const SetT *,
    custom_unordered_set_helper_getter_from_pointer<SetT, const SetT *>
    >;


}
