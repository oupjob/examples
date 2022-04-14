#include <type_traits>

struct a1_t { int x; };
struct a2_t { int x; };
struct b1_t { int y; };
struct b2_t { int y; };

template <typename... Ts>
struct tlist
{
    using type = tlist;
    static constexpr size_t size() noexcept { return sizeof...(Ts); }

};

//-----------------------------------------------------------------------------
/// Search a typelist for a first occurrence of the type T

/// Implementation: has index as a template parameter
  template <size_t idx, typename T, class List>
  struct tlist_index_of_impl;

  template <size_t idx, typename T> /// The type T is not in the list
  struct tlist_index_of_impl <idx, T, tlist<>>
  {
    using type = std::integral_constant<int, -1>;
  };

  template <size_t idx, typename T, typename... Ts>    ///> The type is found
  struct tlist_index_of_impl <idx, T, tlist<T, Ts...>>
  {
    using type = std::integral_constant<int, idx>;
  };

  template <size_t idx, typename T, typename H, typename... Ts>  ///> Recursion
  struct tlist_index_of_impl <idx, T, tlist<H, Ts...>>
  {
    using type = typename tlist_index_of_impl<idx + 1, T, tlist<Ts...>>::type;
  };

/// Wrapping to supply initial index 0
  template <typename T, class List>
  struct tlist_index_of;

/// Specializing for idx >= 0
  template <typename T, typename... Ts>
  struct tlist_index_of<T, tlist<Ts...>>
  {
    using type = typename tlist_index_of_impl<0, T, tlist<Ts...>>::type;
    using value_type = typename type::value_type;
    static constexpr value_type value = type::value;
  };


struct null {};

using null_group = tlist<>;
using x_group = tlist<a1_t, a2_t>;
using y_group = tlist<b1_t, b2_t>;

struct null_setter { static void set(T& t, int x) { (void)t; (void)x } };

template <typename T>
struct x_setter { static void set(T& t, int x) { t.x = x; } };

template <typename T>
struct y_setter { static void set(T& t, int y) { t.y = y; } };

template <typename Group>
struct group_2_setter { using setter = null_setter<T>;  };
template <typename T>
struct group_2_setter<x_group> { using setter = x_setter<T>; };
template <typename T>
struct group_2_setter<y_group> { using setter = y_setter<T>; };

template <typename T>
struct type_2_group { using group = type_2_group_impl<tlist_index_of<T, ; };

template <typename T>
struct type_2_group<-1, > { using group = x_xroup_t; };

template <typename T>
struct type_2_group<y_group> { using group = y_yroup_t; };

template <typename T, template <typename... Ts> List>
struct type_2_setter { using setter = setter<type_2_group, List>  };

