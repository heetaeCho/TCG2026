// TEST_ID: 1604
// Unit tests for Mul03Table (from poppler/Decrypt.cc)
// Constraints honored:
// - Treat implementation as black box (no assumptions about actual table contents)
// - Only test observable behavior via the public interface

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>
#include <vector>

// Mul03Table is defined in Decrypt.cc (not a public header). For unit testing this
// internal helper, we include the implementation file to access the definition.
#include "Decrypt.cc"

namespace {

TEST(Mul03TableTest_1604, CanDefaultConstruct_1604) {
  Mul03Table table;
  (void)table;
}

TEST(Mul03TableTest_1604, OperatorHasExpectedReturnType_1604) {
  Mul03Table table;
  const auto v = table(static_cast<uint8_t>(0));
  static_assert(std::is_same_v<decltype(v), unsigned char>,
                "Mul03Table::operator() must return unsigned char");
  (void)v;
}

TEST(Mul03TableTest_1604, RepeatedCallsWithSameIndexAreStable_1604) {
  Mul03Table table;

  const uint8_t idx = static_cast<uint8_t>(42);
  const unsigned char a = table(idx);
  const unsigned char b = table(idx);
  const unsigned char c = table(idx);

  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}

TEST(Mul03TableTest_1604, TwoInstancesProduceSameOutputsForSameInputs_1604) {
  Mul03Table t1;
  Mul03Table t2;

  for (int i = 0; i <= 255; ++i) {
    const auto idx = static_cast<uint8_t>(i);
    EXPECT_EQ(t1(idx), t2(idx)) << "Mismatch at index " << i;
  }
}

TEST(Mul03TableTest_1604, BoundaryIndicesZeroAndMaxAreCallableAndStable_1604) {
  Mul03Table table;

  const unsigned char z1 = table(static_cast<uint8_t>(0));
  const unsigned char z2 = table(static_cast<uint8_t>(0));
  EXPECT_EQ(z1, z2);

  const unsigned char m1 = table(static_cast<uint8_t>(255));
  const unsigned char m2 = table(static_cast<uint8_t>(255));
  EXPECT_EQ(m1, m2);
}

TEST(Mul03TableTest_1604, ExhaustiveRangeIsCallableAndDeterministic_1604) {
  Mul03Table table;

  std::vector<unsigned char> first(256);
  for (int i = 0; i <= 255; ++i) {
    first[static_cast<size_t>(i)] = table(static_cast<uint8_t>(i));
  }

  for (int i = 0; i <= 255; ++i) {
    const unsigned char again = table(static_cast<uint8_t>(i));
    EXPECT_EQ(first[static_cast<size_t>(i)], again) << "Changed at index " << i;
  }
}

TEST(Mul03TableTest_1604, SupportsConstexprUse_1604) {
  // This test is primarily about compile-time usability.
  // It intentionally does not assert specific byte values.
  constexpr Mul03Table table{};
  constexpr unsigned char v0 = table(static_cast<uint8_t>(0));
  constexpr unsigned char v255 = table(static_cast<uint8_t>(255));

  static_assert(std::is_same_v<decltype(v0), unsigned char>);
  static_assert(std::is_same_v<decltype(v255), unsigned char>);

  (void)v0;
  (void)v255;

  // Also ensure runtime access remains consistent with constexpr evaluation:
  Mul03Table rt;
  EXPECT_EQ(rt(static_cast<uint8_t>(0)), v0);
  EXPECT_EQ(rt(static_cast<uint8_t>(255)), v255);
}

}  // namespace