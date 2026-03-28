#include <gtest/gtest.h>

#include "yaml-cpp/binary.h"

namespace {

using YAML::Binary;

class BinaryNotEqualTest_11 : public ::testing::Test {};

TEST_F(BinaryNotEqualTest_11, DefaultConstructedSelfConsistency_11) {
  Binary a;
  // operator!= must be the logical negation of operator== (as defined).
  EXPECT_EQ(a != a, !(a == a));
}

TEST_F(BinaryNotEqualTest_11, DifferentContentSelfConsistency_11) {
  const unsigned char d1[] = {0x00, 0x01, 0x02};
  const unsigned char d2[] = {0x00, 0x01, 0x03};

  Binary a(d1, sizeof(d1));
  Binary b(d2, sizeof(d2));

  EXPECT_EQ(a != b, !(a == b));
  EXPECT_EQ(b != a, !(b == a));
}

TEST_F(BinaryNotEqualTest_11, SameContentDifferentInstancesSelfConsistency_11) {
  const unsigned char d[] = {0x10, 0x20, 0x30, 0x40};

  Binary a(d, sizeof(d));
  Binary b(d, sizeof(d));

  EXPECT_EQ(a != b, !(a == b));
  EXPECT_EQ(b != a, !(b == a));
}

TEST_F(BinaryNotEqualTest_11, AfterMoveConstructSelfConsistency_11) {
  const unsigned char d[] = {0xAA, 0xBB, 0xCC};

  Binary original(d, sizeof(d));
  Binary moved(std::move(original));
  Binary other(d, sizeof(d));

  // Validate operator!= is still consistent with operator== on a moved-to object.
  EXPECT_EQ(moved != other, !(moved == other));
  EXPECT_EQ(other != moved, !(other == moved));
}

}  // namespace
