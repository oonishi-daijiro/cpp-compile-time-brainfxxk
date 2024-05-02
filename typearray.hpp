#pragma once
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

struct never;

template <typename E, typename T,
          template <typename...> typename assign = std::tuple>
struct repeat_impl;
template <typename E, size_t... N, template <typename...> typename assign>
struct repeat_impl<E, std::integer_sequence<size_t, N...>, assign> {
  template <size_t _> using discard = E;
  using type = assign<discard<N>...>;
};

template <typename T, size_t N, template <typename...> typename assign>
using repeat = repeat_impl<T, std::make_index_sequence<N>, assign>;

template <typename T, size_t N, template <typename...> typename assign>
using repeat = repeat_impl<T, std::make_index_sequence<N>, assign>;

template <int I, typename T> struct itype {};

template <typename Seq, typename... T> struct typearray_base;

template <size_t... N, typename... T>
struct typearray_base<std::integer_sequence<size_t, N...>, T...>
    : itype<N, T>..., itype<sizeof...(T), never> {};

template <typename seq, typename... T>
struct typearray_impl : typearray_base<seq, T...> {
  template <size_t N, typename TT>
  static constexpr auto caster(itype<N, TT>) -> TT;
  static constexpr auto size = sizeof...(T);
  template <size_t N> static constexpr auto safe_index = (N < size) ? N : size;

  template <size_t N>
  constexpr auto get_type() const -> decltype(caster<safe_index<N>>(*this));
};

template <size_t I, typename E, typename Seq, typename... T> struct set_impl;
template <size_t I, typename Seq, typename Src> struct slice_impl;
template <typename Tpl, template <typename, typename> typename T, typename Init>
struct reduce_impl;
template <typename Array, typename... T> struct concat_impl;
template <typename Seq, typename Array> struct pop_front_impl;
template <template <typename...> typename T, typename... TT> struct map_impl;

template <typename... T> struct typearray {
  using seq = std::make_index_sequence<sizeof...(T)>;

  static constexpr int size = sizeof...(T);
  static constexpr typearray_impl<seq, T...> array{};

  template <size_t N> using at = decltype(array.template get_type<N>());

  template <size_t I, typename E> using set = set_impl<I, E, seq, T...>::type;

  template <size_t I, size_t S>
  using slice =
      slice_impl<I, std::make_index_sequence<S>, typearray<T...>>::type;

  template <typename... E> using push_back = typearray<T..., E...>;

  using pop = slice<0, size - ((size >= 2) ? 2
                               : size == 1 ? 1
                               : size == 0 ? 0
                                           : 0)>;

  template <template <typename, typename> typename Reducer, typename Init>
  using reduce = reduce_impl<std::tuple<Init, T...>, Reducer, Init>::type;

  using to_tuple = std::tuple<T...>;

  using back =
      std::conditional_t<(size > 0), at<(size > 0) ? size - 1 : 0>, never>;

  template <typename array> using concat = concat_impl<array, T...>::type;

  using pop_front =
      pop_front_impl<std::make_index_sequence<(size > 0) ? size - 1 : 0>,
                     typearray<T...>>::type;

  template <template <typename...> typename M>
  using map = map_impl<M, T...>::type;
};

template <size_t I, typename E, size_t... N, typename... T>
struct set_impl<I, E, std::integer_sequence<size_t, N...>, T...> {
  using type = typearray<std::conditional_t<N != I, T, E>...>;
};

template <size_t I, size_t... N, typename Src>
struct slice_impl<I, std::integer_sequence<size_t, N...>, Src> {
  static_assert(Src::size >= I, "index is out of range");
  static_assert(Src::size >= sizeof...(N), "size is out of range");
  using type = typearray<typename Src::template at<N + I>...>;
};

template <typename First, typename Second, typename... Tail,
          template <typename, typename> typename T, typename Init>
struct reduce_impl<std::tuple<First, Second, Tail...>, T, Init> {
  using type = typename reduce_impl<std::tuple<T<First, Second>, Tail...>, T,
                                    Init>::type;
};

template <typename Last, typename Accum,
          template <typename, typename> typename T, typename Init>
struct reduce_impl<std::tuple<Accum, Last>, T, Init> {
  using type = T<Accum, Last>;
};

template <template <typename, typename> typename T, typename Init>
struct reduce_impl<std::tuple<Init>, T, Init> {
  using type = Init;
};

template <typename... T, typename... TT>
struct concat_impl<typearray<T...>, TT...> {
  using type = typearray<TT..., T...>;
};

template <size_t... N, typename Array>
struct pop_front_impl<std::integer_sequence<size_t, N...>, Array> {
  using type = typearray<typename Array::template at<N + 1>...>;
};

template <template <typename...> typename T, typename... TT> struct map_impl {
  using type = typearray<T<TT>...>;
};
