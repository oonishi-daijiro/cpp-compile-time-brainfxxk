#include <bits/utility.h>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include <utility>

#include "brainfxxk_operations.hpp"
#include "brainfxxks.hpp"
#include "tuple_utility.hpp"
#include "typearray.hpp"

using runtime_type = int;
using memory_type = uint8_t;
constexpr auto memory_size = 255;

// map
template <typename Seq, template <auto> typename M> struct map;

template <size_t... N, template <auto> typename M>
struct map<std::integer_sequence<size_t, N...>, M> {
  using type = std::integer_sequence<std::remove_const_t<decltype(M<0>::value)>,
                                     M<N>::value...>;
};

// at
template <typename Seq, size_t I> struct at;

template <typename VT, VT... V, size_t I>
struct at<std::integer_sequence<VT, V...>, I> {
  static constexpr VT data[sizeof...(V)]{V...};
  static constexpr auto value = data[I];
};

// set
template <typename Seq, typename iSeq, size_t I, auto NV> struct set;

template <typename VT, VT... V, size_t... Index, size_t I, auto NV>
struct set<std::integer_sequence<VT, V...>, std::index_sequence<Index...>, I,
           NV> {
  using type = std::integer_sequence<VT, (Index == I ? NV : V)...>;
};

// pop
template <typename Seq,
          typename iSeq = std::make_index_sequence<Seq::size() - 1>>
struct pop;
template <typename VT, VT... V, size_t... Index>
struct pop<std::integer_sequence<VT, V...>, std::index_sequence<Index...>> {
  static constexpr VT data[sizeof...(V)]{V...};
  using type = std::integer_sequence<VT, data[Index]...>;
};

// push_back
template <typename Seq, auto V> struct push_back;
template <typename VT, VT... V, auto PV>
struct push_back<std::integer_sequence<VT, V...>, PV> {
  using type = std::integer_sequence<VT, V..., PV>;
};

// pop_front
template <typename Seq> struct pop_front;

template <typename VT, VT H, VT... V>
struct pop_front<std::integer_sequence<VT, H, V...>> {
  using type = std::integer_sequence<VT, V...>;
};

template <auto V1, auto V2> struct pair {
  static constexpr auto l = V1;
  static constexpr auto r = V2;
};

// calltable

template <typename Accum, typename Current> struct reducer_create_calltable {
  using stack = Accum::stack;
  using type = Accum::type;
  static constexpr auto index = Accum::index + 1;
};

template <typename Accum> struct reducer_create_calltable<Accum, lb> {
  using stack = push_back<typename Accum::stack, Accum::index>::type;
  using type = Accum::type;
  static constexpr auto index = Accum::index + 1;
};

template <typename Accum> struct reducer_create_calltable<Accum, le> {
  static constexpr auto index = Accum::index + 1;

  using stack = pop<typename Accum::stack>::type;

  static constexpr auto lbi =
      at<typename Accum::stack, Accum::stack::size() - 1>::value;

  using type = Accum::type::template push_back<pair<lbi, Accum::index>>;
};

struct reducer_create_calltanle_init {
  using stack = std::integer_sequence<runtime_type>;
  using type = typearray<>;
  static constexpr auto index = 0;
};

template <typename program>
using create_calltable =
    tuple_utility::reduce<program, reducer_create_calltable,
                          reducer_create_calltanle_init>::type;

// next_call

template <typename callstack, typename O, runtime_type I> struct next_call;

template <typename Head, typename... Tail, runtime_type I>
struct next_call<std::tuple<Head, Tail...>, lb, I> {
  static constexpr auto value =
      Head::l == I ? Head::r : next_call<std::tuple<Tail...>, lb, I>::value;
};
template <typename Head, typename... Tail, runtime_type I>
struct next_call<std::tuple<Head, Tail...>, le, I> {
  static constexpr auto value =
      Head::r == I ? Head::l : next_call<std::tuple<Tail...>, le, I>::value;
};

template <runtime_type I> struct next_call<std::tuple<>, lb, I> {
  static constexpr auto value = -1;
};

template <runtime_type I> struct next_call<std::tuple<>, le, I> {
  static constexpr auto value = -1;
};

// memory
template <typename Seq, typename iSeq> struct memory {
  using data = Seq;
  using indices = iSeq;
};

// program and callstack
using program = hello_world::push_back<end>;
using callstack = create_calltable<program::to_tuple>::type::to_tuple;

// runtime
template <typename Memory, typename I, typename O> struct brainfxxk_runtime {
  using memory = Memory;
  using in = I;
  using out = O;
};

template <typename runtime, typename operation = program::at<0>,
          runtime_type ptr = 0, int head = 0>
struct brainfxxk_impl;

// end
// ##############################################
template <typename runtime, runtime_type ptr, int head>
struct brainfxxk_impl<runtime, end, ptr, head> {
  using result = runtime;
};

// inc
// ##############################################
template <typename runtime, runtime_type ptr, int head>
struct brainfxxk_impl<runtime, inc, ptr, head> {
  using next = program::at<head + 1>;

  static constexpr auto memv = at<typename runtime::memory::data, ptr>::value;

  using new_mem =
      set<typename runtime::memory::data, typename runtime::memory::indices,
          ptr, memv == 255 ? 0 : memv + 1>::type;

  using result = brainfxxk_impl<
      brainfxxk_runtime<memory<new_mem, typename runtime::memory::indices>,
                        typename runtime::in, typename runtime::out>,
      next, ptr, head + 1>::result;
};

// ##############################################

// dec
// ##############################################
template <typename runtime, runtime_type ptr, int head>
struct brainfxxk_impl<runtime, dec, ptr, head> {
  using next = program::at<head + 1>;

  static constexpr auto memv = at<typename runtime::memory::data, ptr>::value;

  using new_mem =
      set<typename runtime::memory::data, typename runtime::memory::indices,
          ptr, memv == 0 ? 255 : memv - 1>::type;

  using result = brainfxxk_impl<
      brainfxxk_runtime<memory<new_mem, typename runtime::memory::indices>,
                        typename runtime::in, typename runtime::out>,
      next, ptr, head + 1>::result;
};
// ##############################################

// iptr
// ##############################################
template <typename runtime, runtime_type ptr, int head>
struct brainfxxk_impl<runtime, iptr, ptr, head> {
  using next = program::at<head + 1>;

  using result = brainfxxk_impl<
      brainfxxk_runtime<typename runtime::memory, typename runtime::in,
                        typename runtime::out>,
      next, ptr + 1, head + 1>::result;
};
// ##############################################

// dptr
// ##############################################
template <typename runtime, runtime_type ptr, int head>
struct brainfxxk_impl<runtime, dptr, ptr, head> {
  using next = program::at<head + 1>;

  using result = brainfxxk_impl<
      brainfxxk_runtime<typename runtime::memory, typename runtime::in,
                        typename runtime::out>,
      next, ptr - 1, head + 1>::result;
};
// ##############################################

// out
// ##############################################
template <typename runtime, runtime_type ptr, int head>
struct brainfxxk_impl<runtime, out, ptr, head> {
  using next = program::at<head + 1>;

  static constexpr auto memv = at<typename runtime::memory::data, ptr>::value;

  using new_out = push_back<typename runtime::out, memv>::type;

  using result =
      brainfxxk_impl<brainfxxk_runtime<typename runtime::memory,
                                       typename runtime::in, new_out>,
                     next, ptr, head + 1>::result;
};
// ##############################################

// in
// ##############################################
template <typename runtime, runtime_type ptr, int head>
struct brainfxxk_impl<runtime, in, ptr, head> {
  using next = program::at<head + 1>;
  static constexpr auto iv = at<typename runtime::input, 0>::value;

  using new_mem = set<typename runtime::memory::data,
                      typename runtime::memory::indices, ptr, iv>::type;
  using new_in = pop_front<typename runtime::input>::type;

  using result = brainfxxk_impl<
      brainfxxk_runtime<memory<new_mem, typename runtime::memory::indices>,
                        new_in, typename runtime::out>,
      next, ptr, head + 1>::result;
};
// ##############################################

// lb
// ##############################################
template <typename runtime, runtime_type ptr, int head>
struct brainfxxk_impl<runtime, lb, ptr, head> {
  static constexpr auto memv = at<typename runtime::memory::data, ptr>::value;

  static constexpr auto new_head =
      memv == 0 ? next_call<callstack, lb, head>::value : head + 1;
  using next = program::at<new_head>;

  using result = brainfxxk_impl<
      brainfxxk_runtime<typename runtime::memory, typename runtime::in,
                        typename runtime::out>,
      next, ptr, new_head>::result;
};
// ##############################################

// le
// ##############################################
template <typename runtime, runtime_type ptr, int head>
struct brainfxxk_impl<runtime, le, ptr, head> {
  static constexpr auto memv = at<typename runtime::memory::data, ptr>::value;
  static constexpr auto new_head =
      memv != 0 ? next_call<callstack, le, head>::value : head + 1;
  using next = program::at<new_head>;

  using result = brainfxxk_impl<
      brainfxxk_runtime<typename runtime::memory, typename runtime::in,
                        typename runtime::out>,
      next, ptr, new_head>::result;
};

template <auto V> struct zero {
  static constexpr memory_type value = 0;
};

using initial_memory =
    memory<map<std::make_index_sequence<memory_size>, zero>::type,
           std::make_index_sequence<memory_size>>;

template <typename input = std::integer_sequence<memory_type>>
using brainfxxk = brainfxxk_impl<brainfxxk_runtime<
    initial_memory, input, std::integer_sequence<memory_type>>>::result;

template <typename Seq> struct unwrap;

template <memory_type... V>
struct unwrap<std::integer_sequence<memory_type, V...>> {
  static constexpr auto size = sizeof...(V);
  static constexpr memory_type value[sizeof...(V)]{V...};
};

// main
int main() { std::cout << unwrap<brainfxxk<>::out>::value; }
