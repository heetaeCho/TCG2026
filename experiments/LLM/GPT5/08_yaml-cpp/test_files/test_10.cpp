// TEST_ID: 10
#include <gtest/gtest.h>

#include <array>
#include <cstddef>

#include "yaml-cpp/binary.h"

namespace {

using YAML::Binary;

class BinaryTest_10 : public ::testing::Test {};

TEST_F(BinaryTest_10, DefaultConstructedEqualsEmptyBinary_10) {
  Binary a;
  Binary b(nullptr, 0);

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
}

TEST_F(BinaryTest_10, SelfEqualityHolds_10) {
  const std::array<unsigned char, 3> bytes{{0x01, 0x02, 0x03}};
  Binary a(bytes.data(), bytes.size());

  EXPECT_TRUE(a == a);
  EXPECT_FALSE(a != a);
}

TEST_F(BinaryTest_10, DifferentSizesAreNotEqual_10) {
  const std::array<unsigned char, 3> bytes3{{0x01, 0x02, 0x03}};
  const std::array<unsigned char, 4> bytes4{{0x01, 0x02, 0x03, 0x04}};

  Binary a(bytes3.data(), bytes3.size());
  Binary b(bytes4.data(), bytes4.size());

  EXPECT_FALSE(a == b);
  EXPECT_TRUE(a != b);
}

TEST_F(BinaryTest_10, SameSizeSameBytesAreEqual_10) {
  const std::array<unsigned char, 5> bytes{{0x00, 0x10, 0x20, 0x30, 0xFF}};

  Binary a(bytes.data(), bytes.size());
  Binary b(bytes.data(), bytes.size());

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
}

TEST_F(BinaryTest_10, SameSizeDifferentBytesAreNotEqual_10) {
  const std::array<unsigned char, 5> bytes1{{0x00, 0x10, 0x20, 0x30, 0xFF}};
  const std::array<unsigned char, 5> bytes2{{0x00, 0x10, 0x21, 0x30, 0xFF}};  // differs at index 2

  Binary a(bytes1.data(), bytes1.size());
  Binary b(bytes2.data(), bytes2.size());

  EXPECT_FALSE(a == b);
  EXPECT_TRUE(a != b);
}

TEST_F(BinaryTest_10, EmptyBinariesAreEqual_10) {
  Binary a(nullptr, 0);
  Binary b(nullptr, 0);
  Binary c;  // also empty

  EXPECT_TRUE(a == b);
  EXPECT_TRUE(b == c);
  EXPECT_TRUE(a == c);

  EXPECT_FALSE(a != b);
  EXPECT_FALSE(b != c);
  EXPECT_FALSE(a != c);
}

TEST_F(BinaryTest_10, EqualityIsSymmetric_10) {
  const std::array<unsigned char, 4> bytesA{{0xAA, 0xBB, 0xCC, 0xDD}};
  const std::array<unsigned char, 4> bytesB{{0xAA, 0xBB, 0xCC, 0xDD}};
  const std::array<unsigned char, 4> bytesC{{0xAA, 0xBB, 0xCC, 0xDE}};

  Binary a(bytesA.data(), bytesA.size());
  Binary b(bytesB.data(), bytesB.size());
  Binary c(bytesC.data(), bytesC.size());

  EXPECT_EQ(a == b, b == a);
  EXPECT_EQ(a == c, c == a);
}

TEST_F(BinaryTest_10, EqualityIsTransitiveForIdenticalContent_10) {
  const std::array<unsigned char, 6> bytes{{0x01, 0x02, 0x03, 0x04, 0x05, 0x06}};

  Binary a(bytes.data(), bytes.size());
  Binary b(bytes.data(), bytes.size());
  Binary c(bytes.data(), bytes.size());

  ASSERT_TRUE(a == b);
  ASSERT_TRUE(b == c);
  EXPECT_TRUE(a == c);
}

TEST_F(BinaryTest_10, CopyConstructionPreservesEquality_10) {
  const std::array<unsigned char, 3> bytes{{0xDE, 0xAD, 0xBE}};
  Binary original(bytes.data(), bytes.size());

  Binary copy(original);

  EXPECT_TRUE(copy == original);
  EXPECT_FALSE(copy != original);
}

TEST_F(BinaryTest_10, MoveConstructionProducesObjectComparableToOriginalSnapshot_10) {
  const std::array<unsigned char, 4> bytes{{0x11, 0x22, 0x33, 0x44}};
  Binary src(bytes.data(), bytes.size());

  // Snapshot via copy (observable public behavior).
  Binary snapshot(src);

  Binary moved(std::move(src));

  // We do not assert anything about moved-from 'src' state.
  EXPECT_TRUE(moved == snapshot);
  EXPECT_FALSE(moved != snapshot);
}

}  // namespace
