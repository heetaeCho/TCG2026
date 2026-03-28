// dest_new_named_test_2290.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <string>

// Headers from the project
#include "poppler-action.h"
#include "goo/GooString.h"

// NOTE:
// dest_new_named() is a static function in poppler-action.cc.
// To test it as a black box via its observable outputs, we include the .cc
// so the symbol is available in this translation unit.
//
// This pattern assumes the test target is built in a way that does NOT also
// link another compiled copy of poppler-action.cc (to avoid duplicate symbols).
#include "poppler-action.cc"

namespace {

class DestNewNamedTest_2290 : public ::testing::Test {
protected:
  static void FreeDest(PopplerDest* dest) {
    if (!dest) return;
    // Best-effort cleanup to avoid leaks in test runs.
    // poppler_named_dest_from_bytestring() is expected to return GLib-allocated memory.
    if (dest->named_dest) {
      g_free(dest->named_dest);
      dest->named_dest = nullptr;
    }
    g_slice_free(PopplerDest, dest);
  }
};

TEST_F(DestNewNamedTest_2290, NullptrInputReturnsUnknownType_2290) {
  PopplerDest* dest = dest_new_named(nullptr);
  ASSERT_NE(dest, nullptr);

  EXPECT_EQ(dest->type, POPPLER_DEST_UNKNOWN);
  EXPECT_EQ(dest->named_dest, nullptr);

  // g_slice_new0() implies zero-initialization; these are directly observable fields.
  EXPECT_EQ(dest->page_num, 0);
  EXPECT_EQ(dest->change_left, 0);
  EXPECT_EQ(dest->change_top, 0);
  EXPECT_EQ(dest->change_zoom, 0);

  FreeDest(dest);
}

TEST_F(DestNewNamedTest_2290, NonNullNamedDestSetsNamedType_2290) {
  GooString gs("Chapter1");
  PopplerDest* dest = dest_new_named(&gs);
  ASSERT_NE(dest, nullptr);

  EXPECT_EQ(dest->type, POPPLER_DEST_NAMED);

  // We don't assume details of the encoding/contents, only that a conversion was attempted.
  // Some implementations could return nullptr for certain inputs; for a typical non-empty
  // ASCII name we expect a non-null pointer.
  EXPECT_NE(dest->named_dest, nullptr);

  FreeDest(dest);
}

TEST_F(DestNewNamedTest_2290, EmptyStringStillSetsNamedType_2290) {
  GooString gs("");
  PopplerDest* dest = dest_new_named(&gs);
  ASSERT_NE(dest, nullptr);

  EXPECT_EQ(dest->type, POPPLER_DEST_NAMED);

  // Do not assert named_dest non-null: conversion might reasonably yield nullptr for empty input.
  FreeDest(dest);
}

TEST_F(DestNewNamedTest_2290, EmbeddedNullBytesDoesNotCrashAndSetsNamedType_2290) {
  const char raw[] = {'a', '\0', 'b', 'c'};
  GooString gs(raw, sizeof(raw));
  PopplerDest* dest = dest_new_named(&gs);
  ASSERT_NE(dest, nullptr);

  EXPECT_EQ(dest->type, POPPLER_DEST_NAMED);

  FreeDest(dest);
}

TEST_F(DestNewNamedTest_2290, VeryLongNameDoesNotCrashAndSetsNamedType_2290) {
  std::string long_name(4096, 'x');
  GooString gs(long_name);
  PopplerDest* dest = dest_new_named(&gs);
  ASSERT_NE(dest, nullptr);

  EXPECT_EQ(dest->type, POPPLER_DEST_NAMED);

  FreeDest(dest);
}

TEST_F(DestNewNamedTest_2290, MultipleCallsReturnIndependentDestObjects_2290) {
  GooString gs1("A");
  GooString gs2("B");

  PopplerDest* d1 = dest_new_named(&gs1);
  PopplerDest* d2 = dest_new_named(&gs2);

  ASSERT_NE(d1, nullptr);
  ASSERT_NE(d2, nullptr);

  EXPECT_NE(d1, d2);
  EXPECT_EQ(d1->type, POPPLER_DEST_NAMED);
  EXPECT_EQ(d2->type, POPPLER_DEST_NAMED);

  FreeDest(d1);
  FreeDest(d2);
}

} // namespace