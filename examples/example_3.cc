/*
//@HEADER
// *****************************************************************************
//
//                                 example_3.cc
//                           DARMA Toolkit v. 1.0.0
//                   DARMA/detector => C++ Meta-Detection
//
// Copyright 2019 National Technology & Engineering Solutions of Sandia, LLC
// (NTESS). Under the terms of Contract DE-NA0003525 with NTESS, the U.S.
// Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from this
//   software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact darma@sandia.gov
//
// *****************************************************************************
//@HEADER
*/

#include "detector.h"
#include <cstdint>
#include <cstdlib>

namespace test {

struct MyType {
  MyType() = delete;
  MyType(MyType const&) = delete;
};

}

namespace detector { namespace example {


template <typename T>
struct TestTrait {
  template <typename U>
  using MyTestType = decltype(std::declval<U>().myTest(
    std::declval<int>(), std::declval<double>()
  ));
  using ReturnType = ::test::MyType const&;
  using HasMyTestTypeExact = detection::is_detected_exact<ReturnType, MyTestType, T>;
  using HasMyTestTypeConvert = detection::is_detected_convertible<ReturnType, MyTestType, T>;

  static constexpr auto const followsTestTraitExact = HasMyTestTypeExact::value;
  static constexpr auto const followsTestTraitConvert = HasMyTestTypeConvert::value;
};

struct Pass {
  ::test::MyType const& myTest(int, double);
};

struct Fail1 {
  ::test::MyType& myTest(int, double);
};

struct Fail2 {
  ::test::MyType myTest(int, double);
};

struct Fail3 {
  void myTest(int, double);
};

struct Index1D {};

struct TestConstructorNoIdx {
  TestConstructorNoIdx(int32_t, int32_t);
};

struct TestConstructorIdxFst {
  TestConstructorIdxFst(Index1D idx, int32_t, int32_t);
};

struct TestConstructorIdxSnd {
  TestConstructorIdxSnd(int32_t, int32_t, Index1D idx);
};

template <typename ColT, typename IndexT, typename... Args>
struct DetectCons {
  template <typename U>
  using non_idx_t = decltype(U(std::declval<Args>()...));
  template <typename U>
  using idx_fst_t = decltype(U(std::declval<IndexT>(),std::declval<Args>()...));
  template <typename U>
  using idx_snd_t = decltype(U(std::declval<Args>()...,std::declval<IndexT>()));

  using has_non_index_cons = detection::is_detected<non_idx_t, ColT>;
  using has_index_fst      = detection::is_detected<idx_fst_t, ColT>;
  using has_index_snd      = detection::is_detected<idx_snd_t, ColT>;

  static constexpr auto const non_index_cons = has_non_index_cons::value;
  static constexpr auto const index_fst      = has_index_fst::value;
  static constexpr auto const index_snd      = has_index_snd::value;

  static constexpr auto const use_no_index   =
    non_index_cons && !index_snd && !index_fst;
  static constexpr auto const use_index_fst  =
    index_fst;
  static constexpr auto const use_index_snd  =
    index_snd && !index_fst;
};

}} // end namespace detector::example

int main(int, char**) {
  using namespace detector::example;

  // static_assert(TestTrait<Pass>::followsTestTraitExact, "Should follow.");
  // static_assert(not TestTrait<Fail1>::followsTestTraitExact, "Should not follow.");
  // static_assert(not TestTrait<Fail2>::followsTestTraitExact, "Should not follow.");
  // static_assert(not TestTrait<Fail3>::followsTestTraitExact, "Should not follow.");


  // static_assert(TestTrait<Pass>::followsTestTraitConvert, "Should follow.");
  // static_assert(TestTrait<Fail1>::followsTestTraitConvert, "Should follow.");
  // static_assert(TestTrait<Fail2>::followsTestTraitConvert, "Should follow.");
  // static_assert(not TestTrait<Fail3>::followsTestTraitConvert, "Should not follow.");

  // static_assert(
  //   DetectCons<TestConstructorNoIdx, Index1D, int32_t, int32_t>::non_index_cons &&
  //   !DetectCons<TestConstructorNoIdx, Index1D, int32_t, int32_t>::index_fst &&
  //   !DetectCons<TestConstructorNoIdx, Index1D, int32_t, int32_t>::index_snd,
  //   "No index detector failed"
  // );

  // static_assert(
  //   !DetectCons<TestConstructorIdxFst, Index1D, int32_t, int32_t>::non_index_cons &&
  //   DetectCons<TestConstructorIdxFst, Index1D, int32_t, int32_t>::index_fst &&
  //   !DetectCons<TestConstructorIdxFst, Index1D, int32_t, int32_t>::index_snd,
  //   "First index detector failed"
  // );

  // static_assert(
  //   !DetectCons<TestConstructorIdxSnd, Index1D, int32_t, int32_t>::non_index_cons &&
  //   !DetectCons<TestConstructorIdxSnd, Index1D, int32_t, int32_t>::index_fst &&
  //   DetectCons<TestConstructorIdxSnd, Index1D, int32_t, int32_t>::index_snd,
  //   "Second index detector failed"
  // );


  return 0;
}
