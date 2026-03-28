// File: poppler-fonts-iter-new-test-2231.cc
//
// Unit tests for the static helper:
//   static PopplerFontsIter *poppler_fonts_iter_new(std::vector<FontInfo *> &&items)
//
// NOTE: This function is `static` inside poppler-document.cc, so we include the .cc
// to compile it into this test translation unit and make it callable here.

#include <gtest/gtest.h>

#include <vector>
#include <cstddef>

// GLib (for g_slice_new used by the implementation, and general Poppler-GLib linkage)
#include <glib.h>

// Include the implementation file to access the `static` function under test.
#include "./TestProjects/poppler/glib/poppler-document.cc"

namespace {

class PopplerFontsIterNewTest_2231 : public ::testing::Test {
protected:
  // Prefer the public API deleter if available (Poppler-GLib typically exposes this).
  // If the symbol isn't available in a given build, you can adapt your test harness
  // to provide the proper cleanup function.
  static void FreeIter(PopplerFontsIter* iter) {
    if (!iter) return;
    poppler_fonts_iter_free(iter);
  }
};

TEST_F(PopplerFontsIterNewTest_2231, EmptyVectorCreatesNonNullIter_2231) {
  std::vector<FontInfo*> items;
  PopplerFontsIter* iter = poppler_fonts_iter_new(std::move(items));
  ASSERT_NE(iter, nullptr);

  // Observable behavior: should be safe to free via public API.
  ASSERT_NO_FATAL_FAILURE(FreeIter(iter));
}

TEST_F(PopplerFontsIterNewTest_2231, NonEmptyVectorCreatesNonNullIter_2231) {
  std::vector<FontInfo*> items;
  items.push_back(nullptr);
  items.push_back(nullptr);
  items.push_back(nullptr);

  PopplerFontsIter* iter = poppler_fonts_iter_new(std::move(items));
  ASSERT_NE(iter, nullptr);

  ASSERT_NO_FATAL_FAILURE(FreeIter(iter));
}

TEST_F(PopplerFontsIterNewTest_2231, LargeVectorBoundaryDoesNotCrash_2231) {
  std::vector<FontInfo*> items;
  items.resize(10000, nullptr);

  PopplerFontsIter* iter = poppler_fonts_iter_new(std::move(items));
  ASSERT_NE(iter, nullptr);

  ASSERT_NO_FATAL_FAILURE(FreeIter(iter));
}

TEST_F(PopplerFontsIterNewTest_2231, MultipleCallsReturnDistinctIters_2231) {
  std::vector<FontInfo*> a(1, nullptr);
  std::vector<FontInfo*> b(2, nullptr);

  PopplerFontsIter* iter1 = poppler_fonts_iter_new(std::move(a));
  PopplerFontsIter* iter2 = poppler_fonts_iter_new(std::move(b));

  ASSERT_NE(iter1, nullptr);
  ASSERT_NE(iter2, nullptr);
  EXPECT_NE(iter1, iter2);

  ASSERT_NO_FATAL_FAILURE(FreeIter(iter1));
  ASSERT_NO_FATAL_FAILURE(FreeIter(iter2));
}

} // namespace