// TEST_ID: 267
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::array;

class DragonboxArrayTest_267 : public ::testing::Test {};

TEST_F(DragonboxArrayTest_267, IndexAccessReturnsStoredValue_Int_267) {
  array<int, 3> a{{1, -2, 42}};

  EXPECT_EQ(a[stdr::size_t{0}], 1);
  EXPECT_EQ(a[stdr::size_t{1}], -2);
  EXPECT_EQ(a[stdr::size_t{2}], 42);
}

TEST_F(DragonboxArrayTest_267, IndexAccessReturnsStoredValue_Char_267) {
  array<char, 4> a{{'a', 'Z', '\0', '9'}};

  EXPECT_EQ(a[stdr::size_t{0}], 'a');
  EXPECT_EQ(a[stdr::size_t{1}], 'Z');
  EXPECT_EQ(a[stdr::size_t{2}], '\0');
  EXPECT_EQ(a[stdr::size_t{3}], '9');
}

TEST_F(DragonboxArrayTest_267, BoundaryIndicesFirstAndLast_267) {
  array<long long, 5> a{{10, 20, 30, 40, 50}};

  EXPECT_EQ(a[stdr::size_t{0}], 10);
  EXPECT_EQ(a[stdr::size_t{4}], 50);
}

TEST_F(DragonboxArrayTest_267, OperatorIsNoexcept_267) {
  using Arr = array<int, 2>;
  static_assert(noexcept(std::declval<const Arr&>()[stdr::size_t{0}]),
                "array::operator[] must be noexcept");

  // Also verify at runtime (non-fatal) that the expression is well-formed.
  Arr a{{7, 8}};
  (void)a[stdr::size_t{1}];
  SUCCEED();
}

TEST_F(DragonboxArrayTest_267, OperatorReturnsByValue_NotByReference_267) {
  array<int, 2> a{{1, 2}};

  // Observable behavior: modifying the returned value does not affect stored data
  // (only meaningful if the operator returns by value).
  int v = a[stdr::size_t{0}];
  v = 999;

  EXPECT_EQ(a[stdr::size_t{0}], 1);
}

TEST_F(DragonboxArrayTest_267, ConstexprEvaluationWorks_267) {
  // If operator[] is constexpr, this should be usable in constant evaluation.
  constexpr array<int, 3> a{{3, 5, 8}};
  static_assert(a[stdr::size_t{0}] == 3, "constexpr access at index 0 failed");
  static_assert(a[stdr::size_t{1}] == 5, "constexpr access at index 1 failed");
  static_assert(a[stdr::size_t{2}] == 8, "constexpr access at index 2 failed");

  // Keep a minimal runtime check too.
  EXPECT_EQ(a[stdr::size_t{2}], 8);
}

}  // namespace