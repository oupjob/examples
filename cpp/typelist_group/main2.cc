#include <type_traits>
#include <stdio.h>:

struct a1_t { int x; };
struct a2_t { int x; };
struct b1_t { int y; };
struct b2_t { int y; };
struct c1_t { int z; };
struct c2_t { int z; };
struct null_t {};


template <typename... Ts>
struct tlist
{
   using type = tlist;
   static constexpr size_t size() noexcept { return sizeof...(Ts); }
};

template <template<typename T> typename Pred, typename TList>
struct tlist_find_if_impl; // { using result = null_t; };

template <template<typename T> typename Pred>
struct tlist_find_if_impl<Pred, tlist<>> { using result = null_t; };

template <template<typename T> typename Pred, typename H, typename... Ts>
struct tlist_find_if_impl<Pred, tlist<H, Ts...>>
{
    using result = typename std::conditional<Pred<H>::value, H, typename tlist_find_if_impl<Pred, tlist<Ts...> >::result>::type;
};

// Wrapper
template <template <typename T> typename Pred, typename TList>
struct tlist_find_if;

template <template <typename T> typename Pred, typename... Ts>
struct tlist_find_if<Pred, tlist<Ts...>>
{
    using result = typename tlist_find_if_impl<Pred, tlist<Ts...> >::result;
};

template <typename T, typename U>
struct null_t_wrap
{
    using type = typename std::conditional<std::is_same_v<null_t, T>, U, T>::type;
};

template <template <typename...> typename F, typename T>
struct bind
{
    template <typename... Ts>
    using type = F<T, Ts...>;
};

using null_group = tlist<>;
using x_group = tlist<a1_t, a2_t>;
using y_group = tlist<b1_t, b2_t>;
using group_tlist = tlist<x_group, y_group>;

template <typename T>
struct null_setter { static void set(T& t, int x) { (void)t; (void)x; printf("null setter x = %d\n", x); } };

template <typename T>
struct x_setter { static void set(T& t, int x) { t.x = x; printf("set x = %d\n", x); } };

template <typename T>
struct y_setter { static void set(T& t, int y) { t.y = y; printf("set y = %d\n", y); } };

template <typename T, typename Group>
struct group_2_setter { using setter = null_setter<T>;  };
template <typename T>
struct group_2_setter<T, x_group> { using setter = x_setter<T>; };
template <typename T>
struct group_2_setter<T, y_group> { using setter = y_setter<T>; };

template <typename T, typename Group>
struct type_2_group 
{ 
    template <typename H>
    struct type_is_same_pred
    {
        static constexpr bool value = std::is_same<T, H>::value;
    };
    // using group = typename null_t_wrap<typename tlist_find_if<type_is_same_pred, Group>::result, null_group>::type;                       
    using group = typename tlist_find_if<type_is_same_pred, Group>::result;                       
};

template <typename T, typename Group>
struct type_in_group
{
    template <typename U>
    struct is_t
    {
        static constexpr bool value = std::is_same_v<T, U>; 
    };
    static constexpr bool value = std::is_same<T, typename tlist_find_if<is_t, Group>::result>::value;
};

template <typename T, typename GroupList>
struct group_list_2_group 
{ 
    template <typename Group>
    struct type_in_group_pred
    {
        // static constexpr bool value = std::is_same<Group, typename type_2_group<T, Group>::group >::value;
        
        static constexpr bool value = std::is_same<Group, typename tlist_find_if<bind<std::is_same, T>::type, Group>::result>::value;
    };
   // using group = typename null_t_wrap<typename tlist_find_if<type_in_group_pred, GroupList>::result, null_group>::type;
//    using group = typename tlist_find_if<type_in_group_pred, GroupList>::result;
    using group = typename tlist_find_if<type_in_group_pred, GroupList>::result;
};

template <typename T, typename GroupList>
struct type_2_setter 
{
    using setter = typename group_2_setter<T, typename group_list_2_group<T, GroupList>::group>::setter; 
};

int main()
{
    a1_t a1; 
    a2_t a2;
    b1_t b1;
    b2_t b2;
    c1_t c1;
    c2_t c2;

    using is_same_as_a1_t = bind<std::is_same, a1_t>::type<a1_t>;
    static_assert(is_same_as_a1_t::value);
//    using a1_t_setter = type_2_setter<a1_t, group_tlist>::setter;
//    a1_t_setter::set(a1, 1);
//  using group = type_2_group<a1_t, x_group>;
//  printf("%s\n", typeid(group).name());
//  static_assert(std::is_same_v<group, null_t>);
    
//    using a2_t_setter = type_2_setter<a2_t, group_tlist>::setter;
//    a2_t_setter::set(a2, 2);
        
//    using b1_t_setter = type_2_setter<b1_t, group_tlist>::setter;
//    b1_t_setter::set(b1, 1);
    
    using b2_t_setter = type_2_setter<b2_t, group_tlist>::setter;
    b2_t_setter::set(b2, 2);

//    using c1_t_setter = type_2_setter<c1_t, group_tlist>::setter;
//    c1_t_setter::set(c1, 2);

    using type = tlist_find_if<bind<std::is_same, a1_t>::type, x_group >::result; // , x_group>;
    static_assert(std::is_same_v<a1_t, type>);
    static_assert(std::is_same_v<a1_t, tlist_find_if<bind<std::is_same, a1_t>::type, x_group>::result>);
}

