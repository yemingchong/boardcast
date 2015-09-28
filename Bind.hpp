#ifndef _BIND_HEADER_
#define _BIND_HEADER_

#include <cstddef>
#include <functional>
#include <type_traits>

namespace std
{
	template<int> // begin with 0 here!
	struct placeholder_template
	{};

	template<int N>
	struct is_placeholder< placeholder_template<N> >
		: std::integral_constant<int, N+1> // the one is important
	{};
}

namespace type
{
	template<int ...>
	struct seq { };

	template<int N, int ...S>
	struct gens : gens<N-1, N-1, S...> { };

	template<int ...S>
	struct gens<0, S...> {
		typedef seq<S...> type;
	};

	template<int...> 
	struct int_sequence {};

	template<int N, int... Is> 
	struct make_int_sequence: make_int_sequence<N-1, N-1, Is...> {};

	template<int... Is>
	struct make_int_sequence<0, Is...>: int_sequence<Is...> {};

	template<class Ret, class... Args, int... Is>
	auto bind(Ret (*p)(Args...), int_sequence<Is...>)->decltype(std::bind(p, std::placeholder_template<Is>{}...))
	{
		return std::bind(p, std::placeholder_template<Is>{}...);
	}

	template<class Ret, class... Args>
	auto bind(Ret (*p)(Args...))->decltype(zero::bind(p, make_int_sequence< sizeof...(Args) >{}))
	{
		return zero::bind(p, make_int_sequence< sizeof...(Args) >{});
	}

	template<class Ret, class C , class... Args, int... Is>
	auto bind(Ret (C::*p)(Args...), C* obj , int_sequence<Is...>)->decltype(std::bind(p, obj , std::placeholder_template<Is>{}...))
	{
		return std::bind(p, obj , std::placeholder_template<Is>{}...);
	}

	template<class Ret, class C , class... Args>
	auto bind(Ret (C::*p)(Args...) , C* obj)->decltype(zero::bind(p, obj , make_int_sequence< sizeof...(Args) >()))
	{
		return zero::bind(p, obj , make_int_sequence< sizeof...(Args) >{});
	}
}

#endif