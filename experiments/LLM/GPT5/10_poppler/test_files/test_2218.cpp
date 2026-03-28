// File: poppler-index-iter-next-test_2218.cc
//
// Unit tests for poppler_index_iter_next()
// NOTE: Tests treat implementation as a black box and only validate observable behavior.

#include <gtest/gtest.h>

#include <glib.h>
#include <vector>

extern "C" {

// Forward declare public type + function under test.
typedef struct _PopplerIndexIter PopplerIndexIter;
gboolean poppler_index_iter_next(PopplerIndexIter *iter);

} // extern "C"

// The provided snippet indicates PopplerIndexIter has public fields `items` and `index`.
// Also, the implementation calls `iter->items->size()`, so `items` must be a pointer to a
// container with `size()`. We keep this minimal and only to enable construction in tests.
struct _PopplerIndexIter {
  const std::vector<int> *items;
  size_t index;
};

class PopplerIndexIterNextTest_2218 : public ::testing::Test {};

TEST_F(PopplerIndexIterNextTest_2218, NullIterReturnsFalse_2218) {
  // Observable behavior: returns FALSE for nullptr input.
  EXPECT_EQ(poppler_index_iter_next(nullptr), FALSE);
}

TEST_F(PopplerIndexIterNextTest_2218, AdvancesIndexAndReturnsTrueWhenStillWithinRange_2218) {
  const std::vector<int> items = {1, 2, 3};
  PopplerIndexIter iter{&items, 0};

  const gboolean ret = poppler_index_iter_next(&iter);

  EXPECT_EQ(ret, TRUE);
  EXPECT_EQ(iter.index, static_cast<size_t>(1));
}

TEST_F(PopplerIndexIterNextTest_2218, ReturnsFalseWhenAdvancingPastLastElement_2218) {
  const std::vector<int> items = {10, 20, 30};
  PopplerIndexIter iter{&items, items.size() - 1};  // last valid index

  const gboolean ret = poppler_index_iter_next(&iter);

  // Observable behavior: index increments, and function returns FALSE when index >= size().
  EXPECT_EQ(ret, FALSE);
  EXPECT_EQ(iter.index, items.size());
}

TEST_F(PopplerIndexIterNextTest_2218, SingleElementReturnsFalseAfterOneAdvance_2218) {
  const std::vector<int> items = {42};
  PopplerIndexIter iter{&items, 0};

  const gboolean ret = poppler_index_iter_next(&iter);

  EXPECT_EQ(ret, FALSE);
  EXPECT_EQ(iter.index, static_cast<size_t>(1));
}

TEST_F(PopplerIndexIterNextTest_2218, EmptyItemsReturnsFalseAndStillIncrementsIndex_2218) {
  const std::vector<int> items = {};
  PopplerIndexIter iter{&items, 0};

  const gboolean ret = poppler_index_iter_next(&iter);

  EXPECT_EQ(ret, FALSE);
  EXPECT_EQ(iter.index, static_cast<size_t>(1));
}

TEST_F(PopplerIndexIterNextTest_2218, RepeatedCallsAfterFalseKeepReturningFalseAndIncrementing_2218) {
  const std::vector<int> items = {1};
  PopplerIndexIter iter{&items, 0};

  // First call: crosses size boundary => FALSE.
  EXPECT_EQ(poppler_index_iter_next(&iter), FALSE);
  EXPECT_EQ(iter.index, static_cast<size_t>(1));

  // Subsequent calls: still FALSE; index keeps incrementing (observable).
  EXPECT_EQ(poppler_index_iter_next(&iter), FALSE);
  EXPECT_EQ(iter.index, static_cast<size_t>(2));

  EXPECT_EQ(poppler_index_iter_next(&iter), FALSE);
  EXPECT_EQ(iter.index, static_cast<size_t>(3));
}