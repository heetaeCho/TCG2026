// SPDX-License-Identifier: GPL-2.0-or-later
// File: goo_goostring_copy_test.cpp
//
// Unit tests for GooString::copy()
// TEST_ID: 22
//
// Constraints honored:
// - Treat GooString as a black box (only public API used)
// - No private state access (GooString privately inherits std::string)
// - Focus on observable behavior through toStr() and returned unique_ptr

#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "goo/GooString.h"

namespace {

class GooStringCopyTest_22 : public ::testing::Test {};

// Normal operation: copy() returns a non-null unique_ptr with identical content.
TEST_F(GooStringCopyTest_22, CopyReturnsNonNullAndSameContent_22) {
  GooString original("hello");

  std::unique_ptr<GooString> c = original.copy();

  ASSERT_NE(c, nullptr);
  EXPECT_EQ(c->toStr(), original.toStr());
}

// Boundary condition: copying an empty string yields an empty string.
TEST_F(GooStringCopyTest_22, CopyOfEmptyStringPreservesEmpty_22) {
  GooString original("");

  std::unique_ptr<GooString> c = original.copy();

  ASSERT_NE(c, nullptr);
  EXPECT_TRUE(c->toStr().empty());
  EXPECT_EQ(c->toStr(), original.toStr());
}

// Boundary condition: embedded NULs and explicit length construction are preserved.
TEST_F(GooStringCopyTest_22, CopyPreservesEmbeddedNulls_22) {
  const char buf[] = {'a', '\0', 'b', '\0', 'c'};
  GooString original(buf, sizeof(buf));

  std::unique_ptr<GooString> c = original.copy();

  ASSERT_NE(c, nullptr);
  EXPECT_EQ(c->toStr().size(), original.toStr().size());
  EXPECT_EQ(c->toStr(), original.toStr());
}

// Normal operation: copy should create an independent object (no aliasing).
// We verify by mutating the original and ensuring the copy does not change.
TEST_F(GooStringCopyTest_22, CopyIsIndependentFromOriginal_22) {
  GooString original("abc");
  std::unique_ptr<GooString> c = original.copy();
  ASSERT_NE(c, nullptr);
  ASSERT_EQ(c->toStr(), "abc");

  // Mutate original through public API.
  original.setChar(0, 'z');

  // Copy's observable content should remain unchanged.
  EXPECT_EQ(c->toStr(), "abc");
  EXPECT_EQ(original.toStr(), "zbc");
}

// Normal operation: multiple copies are consistent and independent of each other.
TEST_F(GooStringCopyTest_22, MultipleCopiesHaveSameContent_22) {
  GooString original("poppler");
  std::unique_ptr<GooString> c1 = original.copy();
  std::unique_ptr<GooString> c2 = original.copy();

  ASSERT_NE(c1, nullptr);
  ASSERT_NE(c2, nullptr);

  EXPECT_EQ(c1->toStr(), original.toStr());
  EXPECT_EQ(c2->toStr(), original.toStr());

  // Mutate one copy; the other copy and original should be unaffected.
  c1->setChar(0, 'P');

  EXPECT_EQ(c1->toStr(), "Poppler");
  EXPECT_EQ(c2->toStr(), "poppler");
  EXPECT_EQ(original.toStr(), "poppler");
}

// Exceptional/error case (observable): copy() is const and should work on const objects.
TEST_F(GooStringCopyTest_22, CopyWorksOnConstObject_22) {
  const GooString original("const-str");

  std::unique_ptr<GooString> c = original.copy();

  ASSERT_NE(c, nullptr);
  EXPECT_EQ(c->toStr(), original.toStr());
}

}  // namespace