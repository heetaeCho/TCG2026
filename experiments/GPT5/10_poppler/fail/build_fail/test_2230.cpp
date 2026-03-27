// poppler_fonts_iter_free_test_2230.cc
#include <gtest/gtest.h>

#include <glib.h>

#include <atomic>
#include <new>
#include <vector>

// ---- Minimal declarations to exercise the provided interface ----
//
// We only rely on what is observable through the function behavior.
// The production code frees:
//  - each pointer in iter->items via `delete`
//  - destroys the vector via explicit destructor call
//  - releases iter via g_slice_free
//
// To be able to create a compatible object in tests, we provide a minimal
// PopplerFontsIter with a std::vector<FontInfo*> field and a FontInfo type
// whose destructor is observable.

struct FontInfo {
  static std::atomic<int> dtor_calls;

  FontInfo() = default;
  ~FontInfo() { ++dtor_calls; }

  FontInfo(const FontInfo&) = delete;
  FontInfo& operator=(const FontInfo&) = delete;
};

std::atomic<int> FontInfo::dtor_calls{0};

struct _PopplerFontsIter {
  std::vector<FontInfo*> items;
};

using PopplerFontsIter = _PopplerFontsIter;

extern "C" void poppler_fonts_iter_free(PopplerFontsIter* iter);

// Helper: allocate PopplerFontsIter the same way the implementation frees it.
static PopplerFontsIter* NewIter_2230() {
  PopplerFontsIter* iter = static_cast<PopplerFontsIter*>(g_slice_alloc(sizeof(PopplerFontsIter)));
  // g_slice_alloc does not run constructors, so we must placement-new the vector.
  new (&iter->items) std::vector<FontInfo*>();
  return iter;
}

TEST(PopplerFontsIterFreeTest_2230, NullptrIsNoOp_2230) {
  // Should not crash.
  EXPECT_NO_THROW(poppler_fonts_iter_free(nullptr));
}

TEST(PopplerFontsIterFreeTest_2230, EmptyItemsDoesNotCallDestructor_2230) {
  FontInfo::dtor_calls.store(0);

  PopplerFontsIter* iter = NewIter_2230();
  ASSERT_NE(iter, nullptr);
  ASSERT_TRUE(iter->items.empty());

  EXPECT_NO_THROW(poppler_fonts_iter_free(iter));
  EXPECT_EQ(FontInfo::dtor_calls.load(), 0);
}

TEST(PopplerFontsIterFreeTest_2230, DeletesAllEntries_2230) {
  FontInfo::dtor_calls.store(0);

  PopplerFontsIter* iter = NewIter_2230();
  ASSERT_NE(iter, nullptr);

  iter->items.push_back(new FontInfo());
  iter->items.push_back(new FontInfo());
  iter->items.push_back(new FontInfo());

  EXPECT_NO_THROW(poppler_fonts_iter_free(iter));
  EXPECT_EQ(FontInfo::dtor_calls.load(), 3);
}

TEST(PopplerFontsIterFreeTest_2230, HandlesNullEntriesInVector_2230) {
  FontInfo::dtor_calls.store(0);

  PopplerFontsIter* iter = NewIter_2230();
  ASSERT_NE(iter, nullptr);

  iter->items.push_back(new FontInfo());
  iter->items.push_back(nullptr);  // delete nullptr is well-defined
  iter->items.push_back(new FontInfo());

  EXPECT_NO_THROW(poppler_fonts_iter_free(iter));
  EXPECT_EQ(FontInfo::dtor_calls.load(), 2);
}

TEST(PopplerFontsIterFreeTest_2230, LargeNumberOfEntries_2230) {
  FontInfo::dtor_calls.store(0);

  PopplerFontsIter* iter = NewIter_2230();
  ASSERT_NE(iter, nullptr);

  constexpr int kCount = 1024;
  iter->items.reserve(kCount);
  for (int i = 0; i < kCount; ++i) {
    iter->items.push_back(new FontInfo());
  }

  EXPECT_NO_THROW(poppler_fonts_iter_free(iter));
  EXPECT_EQ(FontInfo::dtor_calls.load(), kCount);
}