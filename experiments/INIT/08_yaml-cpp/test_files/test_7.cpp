// TEST_ID = 7
#include <gtest/gtest.h>

#include <array>
#include <cstddef>

#include "yaml-cpp/binary.h"

namespace {

TEST(BinarySizeTest_7, DefaultConstructorReturnsZero_7) {
  YAML::Binary b;
  EXPECT_EQ(b.size(), static_cast<std::size_t>(0));
}

TEST(BinarySizeTest_7, ConstructWithNonEmptyDataReturnsProvidedSize_7) {
  const std::array<unsigned char, 4> bytes{{0x01, 0x02, 0x03, 0x04}};
  YAML::Binary b(bytes.data(), bytes.size());

  EXPECT_EQ(b.size(), bytes.size());
}

TEST(BinarySizeTest_7, ConstructWithSingleByteReturnsOne_7) {
  const unsigned char byte = 0xAB;
  YAML::Binary b(&byte, 1);

  EXPECT_EQ(b.size(), static_cast<std::size_t>(1));
}

TEST(BinarySizeTest_7, ConstructWithLargerBufferReturnsProvidedSize_7) {
  std::array<unsigned char, 256> bytes{};
  bytes[0] = 0x10;
  bytes[255] = 0xFF;

  YAML::Binary b(bytes.data(), bytes.size());
  EXPECT_EQ(b.size(), bytes.size());
}

TEST(BinarySizeTest_7, SizeIsStableAcrossMultipleCalls_7) {
  const std::array<unsigned char, 8> bytes{{0, 1, 2, 3, 4, 5, 6, 7}};
  YAML::Binary b(bytes.data(), bytes.size());

  const std::size_t first = b.size();
  const std::size_t second = b.size();

  EXPECT_EQ(first, bytes.size());
  EXPECT_EQ(second, bytes.size());
}

TEST(BinarySizeTest_7, CopyConstructorPreservesSize_7) {
  const std::array<unsigned char, 5> bytes{{9, 8, 7, 6, 5}};
  YAML::Binary original(bytes.data(), bytes.size());

  YAML::Binary copy(original);

  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.size(), bytes.size());
}

TEST(BinarySizeTest_7, MoveConstructorPreservesMovedToSize_7) {
  const std::array<unsigned char, 6> bytes{{1, 1, 2, 3, 5, 8}};
  YAML::Binary original(bytes.data(), bytes.size());
  const std::size_t original_size = original.size();

  YAML::Binary moved(std::move(original));

  EXPECT_EQ(moved.size(), original_size);
}

TEST(BinarySizeTest_7, CopyAssignmentPreservesSize_7) {
  const std::array<unsigned char, 3> bytes_a{{0xA, 0xB, 0xC}};
  const std::array<unsigned char, 10> bytes_b{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};

  YAML::Binary a(bytes_a.data(), bytes_a.size());
  YAML::Binary b(bytes_b.data(), bytes_b.size());

  a = b;

  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.size(), bytes_b.size());
}

TEST(BinarySizeTest_7, MoveAssignmentPreservesMovedToSize_7) {
  const std::array<unsigned char, 2> bytes_a{{0x01, 0x02}};
  const std::array<unsigned char, 12> bytes_b{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}};

  YAML::Binary a(bytes_a.data(), bytes_a.size());
  YAML::Binary b(bytes_b.data(), bytes_b.size());
  const std::size_t b_size = b.size();

  a = std::move(b);

  EXPECT_EQ(a.size(), b_size);
}

}  // namespace
