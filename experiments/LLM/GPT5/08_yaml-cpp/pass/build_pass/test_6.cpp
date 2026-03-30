#include <gtest/gtest.h>

#include "yaml-cpp/binary.h"

namespace {

TEST(BinaryTest_6, DefaultConstructedIsOwned_6) {
  YAML::Binary b;
  EXPECT_TRUE(b.owned());
}

TEST(BinaryTest_6, ConstructedWithNullptrIsOwned_6) {
  YAML::Binary b(nullptr, 0);
  EXPECT_TRUE(b.owned());
}

TEST(BinaryTest_6, ConstructedWithNonNullDataIsUnowned_6) {
  const unsigned char bytes[] = {0x00, 0xAB, 0xFF};
  YAML::Binary b(bytes, sizeof(bytes));
  EXPECT_FALSE(b.owned());
}

TEST(BinaryTest_6, ConstructedWithNonNullDataAndZeroSizeIsUnowned_6) {
  const unsigned char one = 0x42;
  YAML::Binary b(&one, 0);
  EXPECT_FALSE(b.owned());
}

TEST(BinaryTest_6, CopyConstructionPreservesOwnedState_6) {
  YAML::Binary owned;
  YAML::Binary owned_copy(owned);
  EXPECT_TRUE(owned.owned());
  EXPECT_TRUE(owned_copy.owned());

  const unsigned char bytes[] = {0x10, 0x20};
  YAML::Binary unowned(bytes, sizeof(bytes));
  YAML::Binary unowned_copy(unowned);
  EXPECT_FALSE(unowned.owned());
  EXPECT_FALSE(unowned_copy.owned());
}

TEST(BinaryTest_6, MoveConstructionPreservesOwnedState_6) {
  YAML::Binary owned;
  YAML::Binary owned_moved(std::move(owned));
  EXPECT_TRUE(owned_moved.owned());

  const unsigned char bytes[] = {0x7E, 0x7F, 0x80};
  YAML::Binary unowned(bytes, sizeof(bytes));
  YAML::Binary unowned_moved(std::move(unowned));
  EXPECT_FALSE(unowned_moved.owned());
}

TEST(BinaryTest_6, CopyAssignmentPreservesOwnedState_6) {
  YAML::Binary owned_src;
  YAML::Binary owned_dst(nullptr, 0);
  owned_dst = owned_src;
  EXPECT_TRUE(owned_src.owned());
  EXPECT_TRUE(owned_dst.owned());

  const unsigned char bytes[] = {0xDE, 0xAD, 0xBE, 0xEF};
  YAML::Binary unowned_src(bytes, sizeof(bytes));
  YAML::Binary unowned_dst;
  unowned_dst = unowned_src;
  EXPECT_FALSE(unowned_src.owned());
  EXPECT_FALSE(unowned_dst.owned());
}

TEST(BinaryTest_6, MoveAssignmentPreservesOwnedState_6) {
  YAML::Binary owned_src;
  YAML::Binary owned_dst;
  owned_dst = std::move(owned_src);
  EXPECT_TRUE(owned_dst.owned());

  const unsigned char bytes[] = {0x01, 0x02};
  YAML::Binary unowned_src(bytes, sizeof(bytes));
  YAML::Binary unowned_dst;
  unowned_dst = std::move(unowned_src);
  EXPECT_FALSE(unowned_dst.owned());
}

}  // namespace
