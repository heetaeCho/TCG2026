// TEST_ID: 1606
// File: Mul0bTable_test_1606.cc

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

// Mul0bTable is defined in a .cc file (Decrypt.cc). To test the public interface,
// we include the implementation unit so the type is visible in this test TU.
#include "poppler/Decrypt.cc"

namespace {

class Mul0bTableTest_1606 : public ::testing::Test {};

TEST_F(Mul0bTableTest_1606, IsDefaultConstructibleAndCallable_1606) {
  // Normal operation: can be default-constructed and called with uint8_t.
  Mul0bTable table;

  const unsigned char v0 = table(static_cast<uint8_t>(0));
  const unsigned char v1 = table(static_cast<uint8_t>(1));
  const unsigned char v255 = table(static_cast<uint8_t>(255));

  // Observable properties from the signature/type.
  (void)v0;
  (void)v1;
  (void)v255;

  EXPECT_LE(static_cast<unsigned int>(v0),
            static_cast<unsigned int>(std::numeric_limits<unsigned char>::max()));
  EXPECT_LE(static_cast<unsigned int>(v255),
            static_cast<unsigned int>(std::numeric_limits<unsigned char>::max()));
}

TEST_F(Mul0bTableTest_1606, OperatorReturnTypeIsUnsignedChar_1606) {
  Mul0bTable table;

  // Interface contract: operator()(uint8_t) returns unsigned char.
  static_assert(std::is_same_v<decltype(table(static_cast<uint8_t>(0))), unsigned char>,
                "Mul0bTable::operator()(uint8_t) must return unsigned char");

  const auto v = table(static_cast<uint8_t>(42));
  EXPECT_TRUE((std::is_same_v<decltype(v), const unsigned char>));
}

TEST_F(Mul0bTableTest_1606, CanBeUsedInConstantExpression_1606) {
  // Boundary + compile-time usability: constexpr construction and call.
  constexpr Mul0bTable ctable{};
  constexpr unsigned char cv0 = ctable(static_cast<uint8_t>(0));
  constexpr unsigned char cv255 = ctable(static_cast<uint8_t>(255));
  constexpr unsigned char cv128 = ctable(static_cast<uint8_t>(128));

  // Compare compile-time computed values with runtime calls (no assumptions about
  // the internal table contents beyond consistency for the same input).
  Mul0bTable rtable{};
  EXPECT_EQ(cv0, rtable(static_cast<uint8_t>(0)));
  EXPECT_EQ(cv255, rtable(static_cast<uint8_t>(255)));
  EXPECT_EQ(cv128, rtable(static_cast<uint8_t>(128)));
}

TEST_F(Mul0bTableTest_1606, RepeatedCallsAreConsistentForSameInput_1606) {
  // Normal operation: deterministic for same input on same (const) instance.
  const Mul0bTable table{};

  const uint8_t in = static_cast<uint8_t>(200);
  const unsigned char a = table(in);
  const unsigned char b = table(in);
  const unsigned char c = table(in);

  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}

TEST_F(Mul0bTableTest_1606, AcceptsAllUint8Inputs_1606) {
  // Boundary coverage: exercise the full uint8_t domain [0, 255].
  Mul0bTable table;

  // Also ensures no observable exceptional/error behavior (e.g., crashes) for any uint8_t.
  unsigned int checksum = 0;
  for (int i = 0; i <= 255; ++i) {
    const auto v = table(static_cast<uint8_t>(i));
    checksum += static_cast<unsigned int>(v);
    EXPECT_LE(static_cast<unsigned int>(v),
              static_cast<unsigned int>(std::numeric_limits<unsigned char>::max()));
  }

  // Minimal sanity: checksum is within a possible range and uses results to avoid
  // being optimized away. We do not infer any specific mapping/table values.
  EXPECT_LE(checksum, 255u * static_cast<unsigned int>(std::numeric_limits<unsigned char>::max()));
}

}  // namespace