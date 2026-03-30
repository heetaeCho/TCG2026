// TEST_ID: 9
#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "yaml-cpp/binary.h"

namespace {

std::vector<unsigned char> Bytes(std::initializer_list<unsigned int> xs) {
  std::vector<unsigned char> out;
  out.reserve(xs.size());
  for (auto v : xs) out.push_back(static_cast<unsigned char>(v & 0xFFu));
  return out;
}

static void ExpectBytesEq(const unsigned char* data, std::size_t size,
                          const std::vector<unsigned char>& expected) {
  ASSERT_EQ(size, expected.size());
  if (size == 0) return;
  ASSERT_NE(data, nullptr);
  EXPECT_TRUE(std::equal(data, data + size, expected.begin()));
}

class BinarySwapTest_9 : public ::testing::Test {};

}  // namespace

TEST_F(BinarySwapTest_9, SwapFromDefaultBinaryMovesVectorIntoBinary_9) {
  YAML::Binary b;  // should be a valid empty binary
  std::vector<unsigned char> rhs = Bytes({0x10, 0x20, 0x30, 0x40});

  b.swap(rhs);

  EXPECT_TRUE(rhs.empty());
  ExpectBytesEq(b.data(), b.size(), Bytes({0x10, 0x20, 0x30, 0x40}));
}

TEST_F(BinarySwapTest_9, SwapWithEmptyVectorLeavesBinaryEmptyAndVectorEmpty_9) {
  YAML::Binary b;
  std::vector<unsigned char> rhs;

  b.swap(rhs);

  EXPECT_TRUE(rhs.empty());
  EXPECT_EQ(b.size(), 0u);
  // data() for size==0 is allowed to be nullptr or non-null; don't assert it.
}

TEST_F(BinarySwapTest_9, SwapFromUnownedBinaryCopiesUnownedBytesIntoVector_9) {
  const std::vector<unsigned char> source = Bytes({0xAB, 0xCD, 0xEF, 0x01, 0x02});
  YAML::Binary b(source.data(), source.size());
  ASSERT_FALSE(b.owned()) << "Precondition: constructor(data,size) should create an unowned Binary for this test.";

  std::vector<unsigned char> rhs = Bytes({0x11, 0x22});  // some existing content

  b.swap(rhs);

  // After swap, vector should contain the original unowned bytes (copied).
  EXPECT_EQ(rhs, source);

  // And binary should now expose the original vector bytes (moved/swapped in).
  ExpectBytesEq(b.data(), b.size(), Bytes({0x11, 0x22}));

  // Unowned state should be cleared (observable via owned()).
  EXPECT_TRUE(b.owned());
}

TEST_F(BinarySwapTest_9, SwapFromUnownedBinaryWithEmptyRhsYieldsBinaryEmptyVectorGetsSource_9) {
  const std::vector<unsigned char> source = Bytes({0x01, 0x02, 0x03});
  YAML::Binary b(source.data(), source.size());
  ASSERT_FALSE(b.owned()) << "Precondition: constructor(data,size) should create an unowned Binary for this test.";

  std::vector<unsigned char> rhs;  // empty

  b.swap(rhs);

  EXPECT_EQ(rhs, source);
  EXPECT_EQ(b.size(), 0u);
  EXPECT_TRUE(b.owned());
}

TEST_F(BinarySwapTest_9, SwapFromUnownedBinaryWithZeroSizeProducesEmptyVector_9) {
  const unsigned char dummy = 0x7Fu;
  YAML::Binary b(&dummy, 0u);
  ASSERT_FALSE(b.owned()) << "Precondition: constructor(data,0) should create an unowned Binary for this test.";

  std::vector<unsigned char> rhs = Bytes({0xAA, 0xBB});

  b.swap(rhs);

  EXPECT_TRUE(rhs.empty());  // unowned size is 0, so vector becomes empty
  ExpectBytesEq(b.data(), b.size(), Bytes({0xAA, 0xBB}));
  EXPECT_TRUE(b.owned());
}

TEST_F(BinarySwapTest_9, SwapHandlesLargerPayloads_9) {
  // Build a larger source buffer.
  std::vector<unsigned char> source(4096);
  for (std::size_t i = 0; i < source.size(); ++i) {
    source[i] = static_cast<unsigned char>(i & 0xFFu);
  }

  YAML::Binary b(source.data(), source.size());
  ASSERT_FALSE(b.owned()) << "Precondition: constructor(data,size) should create an unowned Binary for this test.";

  std::vector<unsigned char> rhs(1024, static_cast<unsigned char>(0x5A));

  b.swap(rhs);

  EXPECT_EQ(rhs, source);
  EXPECT_EQ(b.size(), 1024u);
  if (b.size() > 0) {
    ASSERT_NE(b.data(), nullptr);
    for (std::size_t i = 0; i < b.size(); ++i) {
      EXPECT_EQ(b.data()[i], static_cast<unsigned char>(0x5A));
    }
  }
  EXPECT_TRUE(b.owned());
}
