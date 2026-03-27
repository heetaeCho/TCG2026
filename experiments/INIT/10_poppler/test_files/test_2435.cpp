// poppler-page-render-for-printing-with-options-test.cc
// Unit tests for poppler_page_render_for_printing_with_options()
// TEST_ID: 2435

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <glib.h>

extern "C" {

// Forward decl for cairo_t (we only pass pointers through).
typedef struct _cairo cairo_t;

#include "poppler.h"
#include "poppler-private.h"

// Function under test (implemented in poppler-page.cc)
void poppler_page_render_for_printing_with_options(PopplerPage *page,
                                                   cairo_t *cairo,
                                                   PopplerPrintFlags options);

// Dependency we intercept to observe behavior.
// In this unit test TU, we provide a test double to record the call.
void poppler_page_render_full(PopplerPage *page,
                              cairo_t *cairo,
                              gboolean printing,
                              PopplerRenderAnnotsFlags flags);
}  // extern "C"

namespace {

struct RenderFullCallState2435 {
  int call_count = 0;
  PopplerPage *page = nullptr;
  cairo_t *cairo = nullptr;
  gboolean printing = FALSE;
  PopplerRenderAnnotsFlags flags = POPPLER_RENDER_ANNOTS_NONE;
};

RenderFullCallState2435 g_render_full_state_2435;

void ResetRenderFullState2435() {
  g_render_full_state_2435 = RenderFullCallState2435{};
}

// Test double implementation.
extern "C" void poppler_page_render_full(PopplerPage *page,
                                        cairo_t *cairo,
                                        gboolean printing,
                                        PopplerRenderAnnotsFlags flags) {
  g_render_full_state_2435.call_count++;
  g_render_full_state_2435.page = page;
  g_render_full_state_2435.cairo = cairo;
  g_render_full_state_2435.printing = printing;
  g_render_full_state_2435.flags = flags;
}

class PopplerPageRenderForPrintingWithOptionsTest_2435 : public ::testing::Test {
 protected:
  void SetUp() override { ResetRenderFullState2435(); }
  void TearDown() override { ResetRenderFullState2435(); }

  static PopplerPage *DummyPage() {
    // We only verify pointer pass-through; the callee must not dereference here.
    return reinterpret_cast<PopplerPage *>(static_cast<uintptr_t>(0x1));
  }

  static cairo_t *DummyCairo() {
    return reinterpret_cast<cairo_t *>(static_cast<uintptr_t>(0x2));
  }
};

TEST_F(PopplerPageRenderForPrintingWithOptionsTest_2435,
       NoOptions_UsesPrintDocumentFlagAndPrintingTrue_2435) {
  PopplerPage *page = DummyPage();
  cairo_t *cr = DummyCairo();

  poppler_page_render_for_printing_with_options(page, cr,
                                                static_cast<PopplerPrintFlags>(0));

  EXPECT_EQ(g_render_full_state_2435.call_count, 1);
  EXPECT_EQ(g_render_full_state_2435.page, page);
  EXPECT_EQ(g_render_full_state_2435.cairo, cr);
  EXPECT_TRUE(g_render_full_state_2435.printing);

  // Must always include document printing flag.
  EXPECT_EQ(g_render_full_state_2435.flags,
            static_cast<PopplerRenderAnnotsFlags>(
                static_cast<int>(POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT)));
}

TEST_F(PopplerPageRenderForPrintingWithOptionsTest_2435,
       StampOnlyOption_AddsPrintStampFlag_2435) {
  PopplerPage *page = DummyPage();
  cairo_t *cr = DummyCairo();

  poppler_page_render_for_printing_with_options(page, cr,
                                                POPPLER_PRINT_STAMP_ANNOTS_ONLY);

  EXPECT_EQ(g_render_full_state_2435.call_count, 1);
  EXPECT_EQ(g_render_full_state_2435.page, page);
  EXPECT_EQ(g_render_full_state_2435.cairo, cr);
  EXPECT_TRUE(g_render_full_state_2435.printing);

  const int expected =
      static_cast<int>(POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT) |
      static_cast<int>(POPPLER_RENDER_ANNOTS_PRINT_STAMP);

  EXPECT_EQ(static_cast<int>(g_render_full_state_2435.flags), expected);
}

TEST_F(PopplerPageRenderForPrintingWithOptionsTest_2435,
       MarkupOption_AddsPrintMarkupFlag_2435) {
  PopplerPage *page = DummyPage();
  cairo_t *cr = DummyCairo();

  poppler_page_render_for_printing_with_options(page, cr,
                                                POPPLER_PRINT_MARKUP_ANNOTS);

  EXPECT_EQ(g_render_full_state_2435.call_count, 1);
  EXPECT_EQ(g_render_full_state_2435.page, page);
  EXPECT_EQ(g_render_full_state_2435.cairo, cr);
  EXPECT_TRUE(g_render_full_state_2435.printing);

  const int expected =
      static_cast<int>(POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT) |
      static_cast<int>(POPPLER_RENDER_ANNOTS_PRINT_MARKUP);

  EXPECT_EQ(static_cast<int>(g_render_full_state_2435.flags), expected);
}

TEST_F(PopplerPageRenderForPrintingWithOptionsTest_2435,
       StampAndMarkupOptions_AddsBothFlags_2435) {
  PopplerPage *page = DummyPage();
  cairo_t *cr = DummyCairo();

  const PopplerPrintFlags options =
      static_cast<PopplerPrintFlags>(POPPLER_PRINT_STAMP_ANNOTS_ONLY |
                                     POPPLER_PRINT_MARKUP_ANNOTS);

  poppler_page_render_for_printing_with_options(page, cr, options);

  EXPECT_EQ(g_render_full_state_2435.call_count, 1);
  EXPECT_EQ(g_render_full_state_2435.page, page);
  EXPECT_EQ(g_render_full_state_2435.cairo, cr);
  EXPECT_TRUE(g_render_full_state_2435.printing);

  const int expected =
      static_cast<int>(POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT) |
      static_cast<int>(POPPLER_RENDER_ANNOTS_PRINT_STAMP) |
      static_cast<int>(POPPLER_RENDER_ANNOTS_PRINT_MARKUP);

  EXPECT_EQ(static_cast<int>(g_render_full_state_2435.flags), expected);
}

TEST_F(PopplerPageRenderForPrintingWithOptionsTest_2435,
       UnknownOptionBits_AreIgnoredBeyondDocumentAndKnownFlags_2435) {
  PopplerPage *page = DummyPage();
  cairo_t *cr = DummyCairo();

  // Include a high-bit "unknown" option along with none of the known ones.
  const PopplerPrintFlags options =
      static_cast<PopplerPrintFlags>(static_cast<unsigned>(0x80000000u));

  poppler_page_render_for_printing_with_options(page, cr, options);

  EXPECT_EQ(g_render_full_state_2435.call_count, 1);
  EXPECT_TRUE(g_render_full_state_2435.printing);

  // Should still only include the mandatory document flag.
  EXPECT_EQ(static_cast<int>(g_render_full_state_2435.flags),
            static_cast<int>(POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT));
}

TEST_F(PopplerPageRenderForPrintingWithOptionsTest_2435,
       NullPointers_ArePassedThroughToRenderFull_2435) {
  poppler_page_render_for_printing_with_options(
      /*page=*/nullptr, /*cairo=*/nullptr,
      static_cast<PopplerPrintFlags>(0));

  EXPECT_EQ(g_render_full_state_2435.call_count, 1);
  EXPECT_EQ(g_render_full_state_2435.page, nullptr);
  EXPECT_EQ(g_render_full_state_2435.cairo, nullptr);
  EXPECT_TRUE(g_render_full_state_2435.printing);
  EXPECT_EQ(static_cast<int>(g_render_full_state_2435.flags),
            static_cast<int>(POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT));
}

}  // namespace