// File: tinyxml2_dynarray_pop_test_8.cpp
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

using tinyxml2::DynArray;

struct NonTrivial {
	int v{};
	explicit NonTrivial(int vv = 0) : v(vv) {}
	bool operator==(const NonTrivial& other) const { return v == other.v; }
};

class DynArrayPopTest_8 : public ::testing::Test {};

TEST_F(DynArrayPopTest_8, PopReturnsLastPushedAndDecrementsSize_8) {
	DynArray<int, 4> arr;

	arr.Push(10);
	arr.Push(20);
	ASSERT_EQ(arr.Size(), 2u);

	const int popped = arr.Pop();
	EXPECT_EQ(popped, 20);
	EXPECT_EQ(arr.Size(), 1u);

	// Remaining element should still be the first pushed.
	EXPECT_EQ(arr.PeekTop(), 10);
	EXPECT_FALSE(arr.Empty());
}

TEST_F(DynArrayPopTest_8, PopMaintainsLifoOrderAcrossMultiplePops_8) {
	DynArray<int, 2> arr;

	arr.Push(1);
	arr.Push(2);
	arr.Push(3);
	ASSERT_EQ(arr.Size(), 3u);

	EXPECT_EQ(arr.Pop(), 3);
	EXPECT_EQ(arr.Pop(), 2);
	EXPECT_EQ(arr.Pop(), 1);
	EXPECT_EQ(arr.Size(), 0u);
	EXPECT_TRUE(arr.Empty());
}

TEST_F(DynArrayPopTest_8, PopTransitionsToEmptyWhenLastElementRemoved_8) {
	DynArray<int, 8> arr;

	EXPECT_TRUE(arr.Empty());
	arr.Push(42);
	EXPECT_FALSE(arr.Empty());
	ASSERT_EQ(arr.Size(), 1u);

	EXPECT_EQ(arr.Pop(), 42);
	EXPECT_TRUE(arr.Empty());
	EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayPopTest_8, PopWorksAfterPushArrAndReturnsLastArrElement_8) {
	DynArray<int, 2> arr;

	int* p = arr.PushArr(3);
	ASSERT_NE(p, nullptr);

	// Fill the returned contiguous region with known values.
	p[0] = 7;
	p[1] = 8;
	p[2] = 9;

	ASSERT_EQ(arr.Size(), 3u);
	EXPECT_EQ(arr.PeekTop(), 9);

	EXPECT_EQ(arr.Pop(), 9);
	EXPECT_EQ(arr.Size(), 2u);
	EXPECT_EQ(arr.PeekTop(), 8);
}

TEST_F(DynArrayPopTest_8, PopReturnsNonTrivialValue_8) {
	DynArray<NonTrivial, 2> arr;

	arr.Push(NonTrivial{100});
	arr.Push(NonTrivial{200});
	ASSERT_EQ(arr.Size(), 2u);

	NonTrivial popped = arr.Pop();
	EXPECT_EQ(popped.v, 200);
	EXPECT_EQ(arr.Size(), 1u);
	EXPECT_EQ(arr.PeekTop().v, 100);
}

#if GTEST_HAS_DEATH_TEST
// Pop() contains TIXMLASSERT(_size > 0). This is typically active in debug builds.
// If asserts are compiled out, this test is skipped.
TEST_F(DynArrayPopTest_8, PopOnEmptyTriggersAssertInDebug_8) {
#if !defined(NDEBUG)
	DynArray<int, 4> arr;
	ASSERT_TRUE(arr.Empty());

	EXPECT_DEATH(
		{
			(void)arr.Pop();
		},
		"");
#else
	GTEST_SKIP() << "Asserts are disabled (NDEBUG); Pop-on-empty behavior is not observable via death test.";
#endif
}
#endif  // GTEST_HAS_DEATH_TEST

}  // namespace
