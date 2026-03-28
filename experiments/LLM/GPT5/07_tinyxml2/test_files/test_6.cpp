// File: ./TestProjects/tinyxml2/tests/DynArrayPush_test_6.cpp

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

template <typename T, size_t N>
using DynArray = tinyxml2::DynArray<T, N>;

class DynArrayPushTest_6 : public ::testing::Test {};

TEST_F(DynArrayPushTest_6, DefaultConstructed_IsEmptyWithZeroSize_6) {
  DynArray<int, 4> a;

  EXPECT_TRUE(a.Empty());
  EXPECT_EQ(a.Size(), 0u);
  EXPECT_GE(a.Capacity(), a.Size());

  // Mem() is part of the public interface; it should be a valid pointer.
  EXPECT_NE(a.Mem(), nullptr);
}

TEST_F(DynArrayPushTest_6, PushSingle_IncreasesSizeAndStoresValue_6) {
  DynArray<int, 4> a;

  a.Push(42);

  EXPECT_FALSE(a.Empty());
  EXPECT_EQ(a.Size(), 1u);
  EXPECT_GE(a.Capacity(), a.Size());

  EXPECT_EQ(a[0], 42);
  EXPECT_EQ(a.PeekTop(), 42);

  ASSERT_NE(a.Mem(), nullptr);
  EXPECT_EQ(a.Mem()[0], 42);
}

TEST_F(DynArrayPushTest_6, PushMultiple_PreservesInsertionOrder_6) {
  DynArray<int, 4> a;

  a.Push(1);
  a.Push(2);
  a.Push(3);

  EXPECT_EQ(a.Size(), 3u);
  EXPECT_FALSE(a.Empty());
  EXPECT_GE(a.Capacity(), a.Size());

  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a[1], 2);
  EXPECT_EQ(a[2], 3);
  EXPECT_EQ(a.PeekTop(), 3);
}

TEST_F(DynArrayPushTest_6, PushWithinInitialCapacity_DoesNotChangeMemPointer_6) {
  // From the provided header snippet, DynArray starts with _mem pointing to an
  // internal pool of size INITIAL_SIZE. Pushing up to that size should not
  // require growth, so Mem() should remain stable.
  DynArray<int, 4> a;

  const int* before = a.Mem();
  ASSERT_NE(before, nullptr);

  a.Push(10);
  a.Push(20);
  a.Push(30);
  a.Push(40);

  EXPECT_EQ(a.Size(), 4u);
  EXPECT_EQ(a.Mem(), before);

  EXPECT_EQ(a[0], 10);
  EXPECT_EQ(a[1], 20);
  EXPECT_EQ(a[2], 30);
  EXPECT_EQ(a[3], 40);
}

TEST_F(DynArrayPushTest_6, PushBeyondInitialCapacity_ContentsPreservedAndCapacityGteSize_6) {
  DynArray<int, 2> a;

  // Push enough elements to force growth beyond INITIAL_SIZE (2).
  for (int i = 0; i < 10; ++i) {
    a.Push(i);
  }

  EXPECT_EQ(a.Size(), 10u);
  EXPECT_GE(a.Capacity(), a.Size());
  EXPECT_FALSE(a.Empty());
  EXPECT_EQ(a.PeekTop(), 9);

  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(a[static_cast<size_t>(i)], i) << "at index " << i;
  }

  ASSERT_NE(a.Mem(), nullptr);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(a.Mem()[static_cast<size_t>(i)], i) << "via Mem() at index " << i;
  }
}

TEST_F(DynArrayPushTest_6, PushCopiesValueForNonTrivialType_String_6) {
  DynArray<std::string, 2> a;

  std::string s = "hello";
  a.Push(s);

  // Mutate original after push; stored value should remain as it was at push time.
  s = "changed";

  EXPECT_EQ(a.Size(), 1u);
  EXPECT_FALSE(a.Empty());
  EXPECT_EQ(a[0], "hello");
  EXPECT_EQ(a.PeekTop(), "hello");
}

}  // namespace
