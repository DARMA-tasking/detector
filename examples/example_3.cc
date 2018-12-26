
#include "detector.h"

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
