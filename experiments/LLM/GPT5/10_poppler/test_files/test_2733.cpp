// strrstr_test_2733.cc
#include <gtest/gtest.h>

#include <cstring>

// The function under test lives in HtmlOutputDev.cc and is declared static there.
// In this unit-test translation unit we copy only the *signature* and call it
// by including the implementation file so we can test observable behavior.
// NOTE: We do NOT re-implement logic elsewhere; we test the real compiled code.
#include "TestProjects/poppler/utils/HtmlOutputDev.cc"

namespace {

class StrrstrTest_2733 : public ::testing::Test {};

TEST_F(StrrstrTest_2733, ReturnsNullWhenNeedleNotFound_2733) {
  const char* s = "hello world";
  const char* ss = "xyz";
  EXPECT_EQ(strrstr(s, ss), nullptr);
}

TEST_F(StrrstrTest_2733, ReturnsPointerToOnlyOccurrence_2733) {
  const char* s = "abcdef";
  const char* ss = "cd";
  const char* p = strrstr(s, ss);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(p, s + 2);
  EXPECT_STREQ(p, "cdef");  // suffix from match position
}

TEST_F(StrrstrTest_2733, ReturnsPointerToLastOccurrence_2733) {
  const char* s = "ababa";
  const char* ss = "ba";
  const char* p = strrstr(s, ss);
  ASSERT_NE(p, nullptr);
  // "ba" occurs at indices 1 and 3; last is 3.
  EXPECT_EQ(p, s + 3);
  EXPECT_STREQ(p, "ba");
}

TEST_F(StrrstrTest_2733, HandlesOverlappingMatchesAndReturnsLastStart_2733) {
  const char* s = "aaaaa";
  const char* ss = "aaa";
  const char* p = strrstr(s, ss);
  ASSERT_NE(p, nullptr);
  // "aaa" overlaps: starts at 0,1,2; last start is 2.
  EXPECT_EQ(p, s + 2);
  EXPECT_STREQ(p, "aaa");
}

TEST_F(StrrstrTest_2733, ReturnsStartWhenNeedleEqualsHaystack_2733) {
  const char* s = "same";
  const char* ss = "same";
  const char* p = strrstr(s, ss);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(p, s);
  EXPECT_STREQ(p, "same");
}

TEST_F(StrrstrTest_2733, ReturnsLastOccurrenceForSingleCharacterNeedle_2733) {
  const char* s = "mississippi";
  const char* ss = "i";
  const char* p = strrstr(s, ss);
  ASSERT_NE(p, nullptr);
  // last 'i' is at index 10
  EXPECT_EQ(p, s + 10);
  EXPECT_STREQ(p, "i");
}

TEST_F(StrrstrTest_2733, ReturnsEndPointerForEmptyNeedle_2733) {
  const char* s = "abc";
  const char* ss = "";
  const char* p = strrstr(s, ss);
  // Standard strstr(s,"") returns s; the "last occurrence" of empty string is at end.
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(p, s + std::strlen(s));
  EXPECT_STREQ(p, "");
}

TEST_F(StrrstrTest_2733, ReturnsStartWhenBothStringsEmpty_2733) {
  const char* s = "";
  const char* ss = "";
  const char* p = strrstr(s, ss);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(p, s);  // also end
  EXPECT_STREQ(p, "");
}

TEST_F(StrrstrTest_2733, HandlesNeedleLongerThanHaystack_2733) {
  const char* s = "ab";
  const char* ss = "abcd";
  EXPECT_EQ(strrstr(s, ss), nullptr);
}

TEST_F(StrrstrTest_2733, WorksWithNeedleAtEnd_2733) {
  const char* s = "prefix_suffix";
  const char* ss = "suffix";
  const char* p = strrstr(s, ss);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(p, s + 7);
  EXPECT_STREQ(p, "suffix");
}

TEST_F(StrrstrTest_2733, WorksWithNeedleAtBeginningAndLaterOccurrence_2733) {
  const char* s = "test ... test";
  const char* ss = "test";
  const char* p = strrstr(s, ss);
  ASSERT_NE(p, nullptr);
  // occurrences at 0 and at 9 (in "test ... test")
  EXPECT_EQ(p, s + 9);
  EXPECT_STREQ(p, "test");
}

}  // namespace