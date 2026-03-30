// Mul02Table_test_1603.cc
#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <type_traits>

// Mul02Table is defined in Decrypt.cc (implementation file). For unit testing this
// internal helper, we include the translation unit to access the type.
// This follows the "test the provided interface" constraint: we only use the
// public surface (values + operator()) and do not infer how values are populated.
#include "Decrypt.cc"

namespace {

TEST(Mul02TableTest_1603, Has256Entries_1603) {
  Mul02Table t;

  ASSERT_EQ(sizeof(t.values), 256u);
  ASSERT_EQ(sizeof(t.values) / sizeof(t.values[0]), 256u);

  // Sanity: operator() return type is unsigned char (or compatible).
  static_assert(std::is_same_v<decltype(t(uint8_t{0})), unsigned char>,
                "Mul02Table::operator() must return unsigned char");
}

TEST(Mul02TableTest_1603, OperatorMatchesPublicValuesForBoundaries_1603) {
  Mul02Table t;

  EXPECT_EQ(t(uint8_t{0}), t.values[0]);
  EXPECT_EQ(t(uint8_t{1}), t.values[1]);
  EXPECT_EQ(t(uint8_t{254}), t.values[254]);
  EXPECT_EQ(t(uint8_t{255}), t.values[255]);
}

TEST(Mul02TableTest_1603, OperatorMatchesPublicValuesForAllIndices_1603) {
  Mul02Table t;

  for (int i = 0; i <= 255; ++i) {
    const auto idx = static_cast<uint8_t>(i);
    EXPECT_EQ(t(idx), t.values[i]) << "index=" << i;
  }
}

TEST(Mul02TableTest_1603, OperatorIsRepeatableAndDoesNotMutateValues_1603) {
  Mul02Table t;

  // Take a snapshot of the public table.
  unsigned char snapshot[256];
  for (int i = 0; i <= 255; ++i) {
    snapshot[i] = t.values[i];
  }

  // Call operator() many times (normal use) and ensure public contents unchanged.
  for (int round = 0; round < 3; ++round) {
    for (int i = 0; i <= 255; ++i) {
      const auto idx = static_cast<uint8_t>(i);
      EXPECT_EQ(t(idx), snapshot[i]) << "round=" << round << " index=" << i;
    }
  }

  for (int i = 0; i <= 255; ++i) {
    EXPECT_EQ(t.values[i], snapshot[i]) << "index=" << i;
  }
}

TEST(Mul02TableTest_1603, HandlesWrappedUint8Inputs_1603) {
  Mul02Table t;

  // Even if a caller casts out-of-range integers to uint8_t, the interface
  // accepts uint8_t and indexes accordingly. We verify the observable behavior
  // without asserting any particular table contents.
  const uint8_t minus_one = static_cast<uint8_t>(-1);   // wraps to 255
  const uint8_t two_fifty_six = static_cast<uint8_t>(256); // wraps to 0

  EXPECT_EQ(minus_one, uint8_t{255});
  EXPECT_EQ(two_fifty_six, uint8_t{0});

  EXPECT_EQ(t(minus_one), t.values[255]);
  EXPECT_EQ(t(two_fifty_six), t.values[0]);
}

#if defined(__cpp_constexpr) && (__cpp_constexpr >= 201304L)
TEST(Mul02TableTest_1603, CanBeUsedInConstexprContext_1603) {
  // If Mul02Table is truly constexpr-constructible and operator() is constexpr,
  // this should compile and run. This does not assume any specific values.
  constexpr Mul02Table t{};
  static_assert(t(uint8_t{0}) == t.values[0], "constexpr operator() mismatch");
  static_assert(t(uint8_t{255}) == t.values[255], "constexpr operator() mismatch");

  EXPECT_EQ(t(uint8_t{0}), t.values[0]);
  EXPECT_EQ(t(uint8_t{255}), t.values[255]);
}
#endif

}  // namespace