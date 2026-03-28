// File: array_cat_tests_149.cpp
#include <gtest/gtest.h>
#include <array>
#include <algorithm>

// Under test:
// namespace Catch { namespace Matchers { namespace Detail {
//   template<std::size_t N>
//   std::array<void const*, N+1> array_cat(std::array<void const*, N> && lhs, void const* rhs);
// }}} // namespaces

// For convenience
using Catch::Matchers::Detail::array_cat;

class ArrayCatTest_149 : public ::testing::Test {};

// Normal operation: concatenates a single element array with rhs; order preserved.
TEST_F(ArrayCatTest_149, ConcatenatesSingleElement_149) {
  int a = 1, b = 2;
  std::array<void const*, 1> lhs{ { static_cast<void const*>(&a) } };
  void const* rhs = static_cast<void const*>(&b);

  auto result = array_cat<1>(std::move(lhs), rhs);

  ASSERT_EQ(result.size(), 2u);
  EXPECT_EQ(result[0], static_cast<void const*>(&a));
  EXPECT_EQ(result[1], rhs);
}

// Normal operation: multiple elements; verifies entire sequence is preserved then rhs appended.
TEST_F(ArrayCatTest_149, MultipleElementsOrderPreserved_149) {
  int a = 1, b = 2, c = 3, d = 4;
  std::array<void const*, 3> lhs{
      static_cast<void const*>(&a),
      static_cast<void const*>(&b),
      static_cast<void const*>(&c)
  };
  void const* rhs = static_cast<void const*>(&d);

  auto result = array_cat<3>(std::move(lhs), rhs);

  ASSERT_EQ(result.size(), 4u);
  EXPECT_EQ(result[0], static_cast<void const*>(&a));
  EXPECT_EQ(result[1], static_cast<void const*>(&b));
  EXPECT_EQ(result[2], static_cast<void const*>(&c));
  EXPECT_EQ(result[3], rhs);
}

// Boundary condition: N == 0 (empty lhs). Result should contain only rhs.
TEST_F(ArrayCatTest_149, HandlesEmptyLhs_149) {
  int x = 42;
  std::array<void const*, 0> lhs{};
  void const* rhs = static_cast<void const*>(&x);

  auto result = array_cat<0>(std::move(lhs), rhs);

  ASSERT_EQ(result.size(), 1u);
  EXPECT_EQ(result[0], rhs);
}

// Edge/robustness: nullptrs are valid elements; ensure they are copied/appended correctly.
TEST_F(ArrayCatTest_149, SupportsNullptrElements_149) {
  int a = 1;
  std::array<void const*, 2> lhs{ nullptr, static_cast<void const*>(&a) };
  void const* rhs = nullptr;

  auto result = array_cat<2>(std::move(lhs), rhs);

  ASSERT_EQ(result.size(), 3u);
  EXPECT_EQ(result[0], nullptr);
  EXPECT_EQ(result[1], static_cast<void const*>(&a));
  EXPECT_EQ(result[2], nullptr);
}

// Interface/type verification (compile-time): return type has N+1 extent.
TEST_F(ArrayCatTest_149, ReturnTypeHasCorrectExtent_149) {
  int a = 0, b = 0, c = 0;
  std::array<void const*, 2> lhs{ static_cast<void const*>(&a), static_cast<void const*>(&b) };
  void const* rhs = static_cast<void const*>(&c);

  auto result = array_cat<2>(std::move(lhs), rhs);

  static_assert(std::tuple_size<decltype(result)>::value == 3,
                "array_cat<N> must return std::array<void const*, N+1>");
  // Also verify runtime size just in case.
  EXPECT_EQ(result.size(), 3u);
}
