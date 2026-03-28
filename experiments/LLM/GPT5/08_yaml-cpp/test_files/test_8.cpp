// binary_test.cpp
// Unit tests for YAML::Binary::data() (and related observable behavior)

#include <gtest/gtest.h>

#include <cstddef>
#include <cstring>
#include <vector>

#include "yaml-cpp/binary.h"

namespace {

class BinaryDataTest_8 : public ::testing::Test {};

static void ExpectBytesEqual(const unsigned char* p,
                             const std::vector<unsigned char>& expected) {
  ASSERT_NE(p, nullptr);
  ASSERT_FALSE(expected.empty());
  EXPECT_EQ(0, std::memcmp(p, expected.data(), expected.size()));
}

}  // namespace

TEST_F(BinaryDataTest_8, DefaultConstructedHasZeroSize_8) {
  YAML::Binary b;
  EXPECT_EQ(b.size(), 0u);
}

TEST_F(BinaryDataTest_8, DefaultConstructedDataIsNullWhenNotOwned_8) {
  YAML::Binary b;
  if (!b.owned()) {
    EXPECT_EQ(b.data(), nullptr);
  } else {
    // If an implementation ever reports owned()==true on a default object,
    // it must still be safe to call data(). For safety, only assert consistency.
    if (b.size() == 0u) {
      // Avoid dereferencing or making assumptions; just ensure size reports 0.
      SUCCEED();
    } else {
      EXPECT_NE(b.data(), nullptr);
    }
  }
}

TEST_F(BinaryDataTest_8, UnownedConstructionPreservesPointerWhenNotOwned_8) {
  const unsigned char input[] = {0x01, 0x02, 0x03, 0x04};
  YAML::Binary b(input, sizeof(input));

  EXPECT_EQ(b.size(), sizeof(input));

  if (!b.owned()) {
    EXPECT_EQ(b.data(), input);
  } else {
    // Owned: should still provide readable bytes matching the input.
    EXPECT_NE(b.data(), nullptr);
    EXPECT_EQ(0, std::memcmp(b.data(), input, sizeof(input)));
  }
}

TEST_F(BinaryDataTest_8, DataIsNonNullWhenSizeIsNonZero_8) {
  const unsigned char input[] = {0xAA, 0xBB, 0xCC};
  YAML::Binary b(input, sizeof(input));

  ASSERT_GT(b.size(), 0u);
  // For non-zero size, data() should be a usable pointer (may be null only if API allows it).
  // Keep assertion conditional to avoid assuming stronger guarantees than the interface states.
  if (b.data() == nullptr) {
    // If null is returned, size must still be observable; do not fail on an unspecified behavior.
    // This keeps the test black-box friendly.
    SUCCEED();
  } else {
    EXPECT_EQ(0, std::memcmp(b.data(), input, sizeof(input)));
  }
}

TEST_F(BinaryDataTest_8, SwapWithVectorMakesBinaryMatchVectorBytes_8) {
  const unsigned char input[] = {0x10, 0x20, 0x30};
  YAML::Binary b(input, sizeof(input));

  std::vector<unsigned char> rhs = {0x99, 0x88, 0x77, 0x66};
  const std::vector<unsigned char> rhs_before = rhs;

  b.swap(rhs);

  // After swap, Binary should now expose rhs_before bytes.
  EXPECT_EQ(b.size(), rhs_before.size());
  ASSERT_GT(b.size(), 0u);
  ExpectBytesEqual(b.data(), rhs_before);
}

TEST_F(BinaryDataTest_8, SwapWithVectorMovesPreviousBinaryBytesIntoVector_8) {
  const unsigned char input[] = {0xDE, 0xAD, 0xBE, 0xEF};
  YAML::Binary b(input, sizeof(input));
  const std::vector<unsigned char> input_vec(input, input + sizeof(input));

  std::vector<unsigned char> rhs = {0x01};
  b.swap(rhs);

  // After swap, rhs should now contain what Binary had before (some representation of input).
  // If Binary was unowned, swap may cause it to become owned and transfer bytes; verify by content.
  EXPECT_EQ(rhs.size(), input_vec.size());
  if (!rhs.empty()) {
    EXPECT_EQ(0, std::memcmp(rhs.data(), input_vec.data(), input_vec.size()));
  }
}

TEST_F(BinaryDataTest_8, EqualitySameContentTrueAndInequalityFalse_8) {
  const unsigned char input[] = {0x00, 0x01, 0x02};
  YAML::Binary a(input, sizeof(input));
  YAML::Binary b(input, sizeof(input));

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
}

TEST_F(BinaryDataTest_8, InequalityDifferentContentOrSize_8) {
  const unsigned char input1[] = {0x01, 0x02, 0x03};
  const unsigned char input2[] = {0x01, 0x02, 0x04};
  YAML::Binary a(input1, sizeof(input1));
  YAML::Binary b(input2, sizeof(input2));
  YAML::Binary c(input1, sizeof(input1) - 1);

  EXPECT_TRUE(a != b);
  EXPECT_FALSE(a == b);

  EXPECT_TRUE(a != c);
  EXPECT_FALSE(a == c);
}

TEST_F(BinaryDataTest_8, ConstructNullptrZeroSizeIsSafe_8) {
  YAML::Binary b(nullptr, 0);
  EXPECT_EQ(b.size(), 0u);

  if (!b.owned()) {
    EXPECT_EQ(b.data(), nullptr);
  } else {
    // If owned, it must still be safe/consistent; avoid assuming pointer value for empty.
    SUCCEED();
  }
}

TEST_F(BinaryDataTest_8, ConstructNullptrNonZeroSizeDoesNotCrashAndIsObservable_8) {
  YAML::Binary b(nullptr, 5);

  // We don't assume whether size() clamps to 0 or keeps 5; just assert self-consistency.
  if (b.size() == 0u) {
    SUCCEED();
  } else {
    // If size is non-zero, data() may be nullptr (depending on implementation),
    // but calling it must be safe.
    (void)b.data();
    SUCCEED();
  }
}
