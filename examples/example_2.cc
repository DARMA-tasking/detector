/*
//@HEADER
// *****************************************************************************
//
//                                 example_2.cc
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

namespace detector { namespace example {

template <typename T>
struct TestTrait {
  template <typename U>
  using MyTestType = decltype(std::declval<U>().myTest(
    std::declval<int>(), std::declval<double>()
  ));
  using HasMyTestType = detection::is_detected<MyTestType, T>;

  static constexpr auto const followsTestTrait = HasMyTestType::value;
};

struct Pass {
  void myTest(int, double) { }
};

struct Fail {
  void myTest(int) { }
  void myTest(double) { }
  void myTest(int, int) { }
  void myTest(double, int) { }
  void myTest(double, double) { }
};

}} // end namespace detector::example

int main(int, char**) {
  using namespace detector::example;

  static_assert(TestTrait<Pass>::followsTestTrait, "Should follow.");
  static_assert(not TestTrait<Fail>::followsTestTrait, "Should not follow.");

  return 0;
}
