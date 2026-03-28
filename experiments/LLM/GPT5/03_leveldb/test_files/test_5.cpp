// slice_end_test_5.cc
#include <gtest/gtest.h>
#include <string>
#include "leveldb/slice.h"

using leveldb::Slice;

class SliceEndTest_5 : public ::testing::Test {};

// [Normal] Default-constructed slice: end()==begin(), size()==0
TEST_F(SliceEndTest_5, DefaultConstructed_EmptyEndEqualsBegin_5) {
  Slice s;
  EXPECT_EQ(s.size(), 0u);
  EXPECT_EQ(s.end(), s.begin());
  EXPECT_EQ(s.end(), s.data());  // end == data when size==0
}

// [Normal] From C-string: end() == begin() + size()
TEST_F(SliceEndTest_5, FromCString_EndMatchesBeginPlusSize_5) {
  const char* cstr = "world";
  Slice s(cstr);
  ASSERT_GT(s.size(), 0u);
  EXPECT_EQ(static_cast<size_t>(s.end() - s.begin()), s.size());
  EXPECT_EQ(*(s.end() - 1), 'd');  // last character before end()
}

// [Normal] From std::string: last character is at end()-1
TEST_F(SliceEndTest_5, FromStdString_LastCharBeforeEnd_5) {
  std::string str = "hello";
  Slice s(str);
  ASSERT_EQ(s.size(), str.size());
  EXPECT_EQ(static_cast<size_t>(s.end() - s.begin()), s.size());
  EXPECT_EQ(*(s.end() - 1), 'o');
}

// [Boundary] Explicit length with embedded NULs: end() respects size(), not strlen
TEST_F(SliceEndTest_5, ExplicitLength_WithEmbeddedNulls_EndUsesSizeNotStrlen_5) {
  const char raw[] = {'a', 'b', 'c', '\0', 'd', 'e', 'f'};
  const size_t n = sizeof(raw); // 7
  Slice s(raw, n);
  EXPECT_EQ(s.size(), n);
  EXPECT_EQ(static_cast<size_t>(s.end() - s.begin()), n);
  EXPECT_EQ(*(s.end() - 1), 'f');  // last byte before end()
}

// [Boundary] remove_prefix: end() should remain invariant (data()+size() unchanged)
TEST_F(SliceEndTest_5, RemovePrefix_KeepsEndPointerInvariant_5) {
  const char* text = "abcdef";
  Slice s(text);
  const char* old_end = s.end();
  // Remove a valid prefix; observable behavior: size decreases, begin advances.
  s.remove_prefix(2);
  ASSERT_EQ(*(s.begin()), 'c');
  EXPECT_EQ(s.size(), static_cast<size_t>(4));
  EXPECT_EQ(s.end(), old_end);  // end pointer stays the same address
}

// [Exceptional/State change] clear(): end()==data() and size()==0 afterwards
TEST_F(SliceEndTest_5, Clear_MakesEndEqualData_5) {
  Slice s("xyz");
  s.clear();
  EXPECT_EQ(s.size(), 0u);
  EXPECT_EQ(s.end(), s.data());
  EXPECT_EQ(s.end(), s.begin());
}

// [Boundary] Explicit zero length: end()==data() even if pointer non-null
TEST_F(SliceEndTest_5, ZeroLengthExplicit_EndEqualsDataPointer_5) {
  const char* buf = "unused";
  Slice s(buf, 0);
  EXPECT_EQ(s.size(), 0u);
  EXPECT_EQ(s.end(), s.data());
  EXPECT_EQ(s.end(), s.begin());
}

// [Normal] Copy-constructed slice: end() matches original end()
TEST_F(SliceEndTest_5, CopyConstructed_EndSameAsOriginal_5) {
  Slice original("copyme");
  Slice copy = original;  // copy-construct
  EXPECT_EQ(static_cast<size_t>(copy.end() - copy.begin()), copy.size());
  EXPECT_EQ(static_cast<size_t>(original.end() - original.begin()), original.size());
  // Observable equality of sizes implies both have same distance to end
  EXPECT_EQ(copy.size(), original.size());
}
