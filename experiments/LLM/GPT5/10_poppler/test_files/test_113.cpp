// Dict_getLength_test_113.cpp

#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "poppler/Dict.h"
#include "poppler/Object.h"

namespace {

// Helper to generate unique keys.
static std::string makeKey(int i) {
  return "K" + std::to_string(i);
}

class DictTest_113 : public ::testing::Test {
protected:
  // In Poppler, Dict is typically associated with an XRef, but a null XRef is
  // commonly accepted for simple dictionary manipulation in tests.
  Dict makeEmptyDict() { return Dict(nullptr); }
};

TEST_F(DictTest_113, GetLength_InitiallyZero_113) {
  Dict d = makeEmptyDict();
  EXPECT_EQ(d.getLength(), 0);
}

TEST_F(DictTest_113, GetLength_IncreasesAfterAddWithNewKey_113) {
  Dict d = makeEmptyDict();

  d.add("A", Object::null());
  EXPECT_EQ(d.getLength(), 1);

  d.add("B", Object::null());
  EXPECT_EQ(d.getLength(), 2);
}

TEST_F(DictTest_113, GetLength_DecreasesAfterRemoveExistingKey_113) {
  Dict d = makeEmptyDict();

  d.add("A", Object::null());
  d.add("B", Object::null());
  ASSERT_EQ(d.getLength(), 2);

  d.remove("A");
  EXPECT_EQ(d.getLength(), 1);

  // Removing the remaining key should reach zero.
  d.remove("B");
  EXPECT_EQ(d.getLength(), 0);
}

TEST_F(DictTest_113, GetLength_RemoveMissingKeyDoesNotIncrease_113) {
  Dict d = makeEmptyDict();

  // Removing from an empty dict should not make length negative or increase it.
  d.remove("missing");
  EXPECT_GE(d.getLength(), 0);
  EXPECT_EQ(d.getLength(), 0);

  d.add("A", Object::null());
  ASSERT_EQ(d.getLength(), 1);

  // Removing a key that doesn't exist should not increase length.
  d.remove("missing");
  EXPECT_GE(d.getLength(), 0);
  EXPECT_LE(d.getLength(), 1);
}

TEST_F(DictTest_113, GetLength_AddManyKeysMatchesCount_113) {
  Dict d = makeEmptyDict();

  constexpr int kCount = 200;
  for (int i = 0; i < kCount; ++i) {
    d.add(makeKey(i), Object::null());
  }
  EXPECT_EQ(d.getLength(), kCount);

  // Boundary-ish: remove a few and ensure length tracks downwards.
  d.remove(makeKey(0));
  d.remove(makeKey(1));
  EXPECT_EQ(d.getLength(), kCount - 2);
}

} // namespace