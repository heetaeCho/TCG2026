// TEST_ID: 10
#include <gtest/gtest.h>

#include "tinyxml2.h"

namespace tinyxml2 {

class DynArrayEmptyTest_10 : public ::testing::Test {};

TEST_F(DynArrayEmptyTest_10, DefaultConstructedIsEmpty_10) {
  DynArray<int, 4> arr;
  EXPECT_TRUE(arr.Empty());
  EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayEmptyTest_10, PushMakesNotEmpty_10) {
  DynArray<int, 4> arr;

  arr.Push(123);

  EXPECT_FALSE(arr.Empty());
  EXPECT_EQ(arr.Size(), 1u);
  EXPECT_EQ(arr.PeekTop(), 123);
}

TEST_F(DynArrayEmptyTest_10, ClearRestoresEmpty_10) {
  DynArray<int, 4> arr;
  arr.Push(1);
  arr.Push(2);
  ASSERT_FALSE(arr.Empty());
  ASSERT_EQ(arr.Size(), 2u);

  arr.Clear();

  EXPECT_TRUE(arr.Empty());
  EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayEmptyTest_10, PopToEmptyBecomesEmpty_10) {
  DynArray<int, 4> arr;
  arr.Push(7);
  ASSERT_FALSE(arr.Empty());
  ASSERT_EQ(arr.Size(), 1u);

  const int v = arr.Pop();

  EXPECT_EQ(v, 7);
  EXPECT_TRUE(arr.Empty());
  EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayEmptyTest_10, PushArrThenPopArrBecomesEmpty_10) {
  DynArray<int, 2> arr;
  ASSERT_TRUE(arr.Empty());

  int* mem = arr.PushArr(3);
  ASSERT_NE(mem, nullptr);
  mem[0] = 10;
  mem[1] = 20;
  mem[2] = 30;

  EXPECT_FALSE(arr.Empty());
  EXPECT_EQ(arr.Size(), 3u);
  EXPECT_EQ(arr.PeekTop(), 30);

  arr.PopArr(3);

  EXPECT_TRUE(arr.Empty());
  EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayEmptyTest_10, PopArrPartialDoesNotBecomeEmpty_10) {
  DynArray<int, 2> arr;
  int* mem = arr.PushArr(4);
  ASSERT_NE(mem, nullptr);
  mem[0] = 1;
  mem[1] = 2;
  mem[2] = 3;
  mem[3] = 4;

  ASSERT_FALSE(arr.Empty());
  ASSERT_EQ(arr.Size(), 4u);

  arr.PopArr(3);

  EXPECT_FALSE(arr.Empty());
  EXPECT_EQ(arr.Size(), 1u);
  EXPECT_EQ(arr.PeekTop(), 1);
}

}  // namespace tinyxml2
