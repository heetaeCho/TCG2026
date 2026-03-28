// poppler-dest-copy-test_2283.cc
#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
#include "poppler-action.h"

// Function under test (implemented in poppler-action.cc)
PopplerDest *poppler_dest_copy(PopplerDest *dest);
}

namespace {

class PopplerDestCopyTest_2283 : public ::testing::Test {
 protected:
  static PopplerDest *NewDest() {
    // Use g_slice allocation since the implementation uses g_slice_dup.
    PopplerDest *d = g_slice_new0(PopplerDest);
    return d;
  }

  static void FreeDest(PopplerDest *d) {
    if (!d) return;
    // The real PopplerDest uses a string-like named_dest in practice; the provided
    // header snippet may be simplified/inaccurate. Freeing via g_free is safe
    // for memory allocated by g_strdup and is a no-op for nullptr.
    g_free(reinterpret_cast<gpointer>(d->named_dest));
    d->named_dest = nullptr;
    g_slice_free(PopplerDest, d);
  }
};

TEST_F(PopplerDestCopyTest_2283, CopiesAllScalarFieldsWhenNamedDestNull_2283) {
  PopplerDest *src = NewDest();
  ASSERT_NE(src, nullptr);

  src->type = static_cast<PopplerDestType>(1);
  src->page_num = 42;
  src->named_dest = nullptr;
  src->change_left = 1;
  src->change_top = 0;
  src->change_zoom = 1;

  PopplerDest *copy = poppler_dest_copy(src);
  ASSERT_NE(copy, nullptr);
  EXPECT_NE(copy, src);

  EXPECT_EQ(copy->type, src->type);
  EXPECT_EQ(copy->page_num, src->page_num);
  EXPECT_EQ(copy->named_dest, nullptr);
  EXPECT_EQ(copy->change_left, src->change_left);
  EXPECT_EQ(copy->change_top, src->change_top);
  EXPECT_EQ(copy->change_zoom, src->change_zoom);

  FreeDest(copy);
  FreeDest(src);
}

TEST_F(PopplerDestCopyTest_2283, DeepCopiesNamedDestWhenPresent_2283) {
  PopplerDest *src = NewDest();
  ASSERT_NE(src, nullptr);

  src->type = static_cast<PopplerDestType>(2);
  src->page_num = 7;
  const char *name = "Chapter1";
  src->named_dest = reinterpret_cast<decltype(src->named_dest)>(g_strdup(name));
  src->change_left = 0;
  src->change_top = 1;
  src->change_zoom = 0;

  PopplerDest *copy = poppler_dest_copy(src);
  ASSERT_NE(copy, nullptr);
  EXPECT_NE(copy, src);

  EXPECT_EQ(copy->type, src->type);
  EXPECT_EQ(copy->page_num, src->page_num);

  // Deep copy expectation: pointer differs but content matches.
  ASSERT_NE(copy->named_dest, nullptr);
  EXPECT_NE(copy->named_dest, src->named_dest);

  const char *copy_name = reinterpret_cast<const char *>(copy->named_dest);
  const char *src_name = reinterpret_cast<const char *>(src->named_dest);
  EXPECT_STREQ(copy_name, src_name);

  FreeDest(copy);
  FreeDest(src);
}

TEST_F(PopplerDestCopyTest_2283, DeepCopyIsIndependentFromSourceMutation_2283) {
  PopplerDest *src = NewDest();
  ASSERT_NE(src, nullptr);

  // Allocate a mutable string via g_strdup so we can safely mutate it.
  gchar *mutable_name = g_strdup("DestName");
  ASSERT_NE(mutable_name, nullptr);
  src->named_dest = reinterpret_cast<decltype(src->named_dest)>(mutable_name);

  PopplerDest *copy = poppler_dest_copy(src);
  ASSERT_NE(copy, nullptr);
  ASSERT_NE(copy->named_dest, nullptr);

  const char *before = reinterpret_cast<const char *>(copy->named_dest);
  EXPECT_STREQ(before, "DestName");

  // Mutate the source string.
  mutable_name[0] = 'X';

  const char *after_src = reinterpret_cast<const char *>(src->named_dest);
  const char *after_copy = reinterpret_cast<const char *>(copy->named_dest);

  EXPECT_STREQ(after_src, "XestName");
  // Copy should remain unchanged if it was deep-copied.
  EXPECT_STREQ(after_copy, "DestName");

  FreeDest(copy);
  FreeDest(src);
}

TEST_F(PopplerDestCopyTest_2283, HandlesEmptyNamedDestString_2283) {
  PopplerDest *src = NewDest();
  ASSERT_NE(src, nullptr);

  src->named_dest =
      reinterpret_cast<decltype(src->named_dest)>(g_strdup(""));
  ASSERT_NE(src->named_dest, nullptr);

  PopplerDest *copy = poppler_dest_copy(src);
  ASSERT_NE(copy, nullptr);
  ASSERT_NE(copy->named_dest, nullptr);

  EXPECT_NE(copy->named_dest, src->named_dest);
  EXPECT_STREQ(reinterpret_cast<const char *>(copy->named_dest), "");

  FreeDest(copy);
  FreeDest(src);
}

TEST_F(PopplerDestCopyTest_2283, HandlesNonAsciiNamedDestString_2283) {
  PopplerDest *src = NewDest();
  ASSERT_NE(src, nullptr);

  // UTF-8 content to ensure copying doesn't truncate/alter bytes.
  const char *utf8 = u8"목적지-テスト-✓";
  src->named_dest =
      reinterpret_cast<decltype(src->named_dest)>(g_strdup(utf8));
  ASSERT_NE(src->named_dest, nullptr);

  PopplerDest *copy = poppler_dest_copy(src);
  ASSERT_NE(copy, nullptr);
  ASSERT_NE(copy->named_dest, nullptr);

  EXPECT_NE(copy->named_dest, src->named_dest);
  EXPECT_STREQ(reinterpret_cast<const char *>(copy->named_dest), utf8);

  FreeDest(copy);
  FreeDest(src);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PopplerDestCopyTest_2283, DeathOnNullInput_2283) {
  // The implementation dereferences dest unconditionally; passing nullptr is
  // expected to crash. This is an observable error case through the interface.
  ASSERT_DEATH(
      {
        volatile PopplerDest *out = poppler_dest_copy(nullptr);
        (void)out;
      },
      "");
}
#endif

}  // namespace