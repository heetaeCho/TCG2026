// poppler-page-render-test-2434.cc
#include <gtest/gtest.h>

#include <glib.h>   // gboolean
#include <cairo.h>  // cairo_t

// Poppler public API (for PopplerPage and PopplerRenderAnnotsFlags, poppler_page_render()).
#include "poppler.h"

// Forward declare PopplerPage if poppler.h uses an incomplete type in C headers.
// (This is harmless if poppler.h already defines it.)
#ifndef POPPLER_TYPE_PAGE
typedef struct _PopplerPage PopplerPage;
#endif

namespace {

// Simple capture of the last call to poppler_page_render_full().
struct RenderFullCallState {
  int call_count = 0;
  PopplerPage* page = nullptr;
  cairo_t* cairo = nullptr;
  gboolean printing = FALSE;
  PopplerRenderAnnotsFlags flags = POPPLER_RENDER_ANNOTS_NONE;
};

RenderFullCallState g_state;

void ResetState() { g_state = RenderFullCallState{}; }

}  // namespace

// ---- Test seam / stub dependency ----
//
// poppler_page_render() is a thin wrapper that delegates to poppler_page_render_full().
// We provide a stub for poppler_page_render_full() to observe the delegation parameters.
//
// NOTE: This relies on the test binary resolving poppler_page_render_full() to this
// definition (common in unit-test builds where the dependency isn't linked, or symbol
// interposition is supported in the build).
extern "C" void poppler_page_render_full(PopplerPage* page,
                                        cairo_t* cairo,
                                        gboolean printing,
                                        PopplerRenderAnnotsFlags flags) {
  g_state.call_count++;
  g_state.page = page;
  g_state.cairo = cairo;
  g_state.printing = printing;
  g_state.flags = flags;
}

class PopplerPageRenderTest_2434 : public ::testing::Test {
protected:
  void SetUp() override { ResetState(); }
  void TearDown() override { ResetState(); }
};

TEST_F(PopplerPageRenderTest_2434, DelegatesToRenderFullWithExpectedDefaults_2434) {
  PopplerPage* page = reinterpret_cast<PopplerPage*>(0x1);
  cairo_t* cr = reinterpret_cast<cairo_t*>(0x2);

  poppler_page_render(page, cr);

  ASSERT_EQ(g_state.call_count, 1);
  EXPECT_EQ(g_state.page, page);
  EXPECT_EQ(g_state.cairo, cr);
  EXPECT_EQ(g_state.printing, FALSE);
  EXPECT_EQ(g_state.flags, POPPLER_RENDER_ANNOTS_ALL);
}

TEST_F(PopplerPageRenderTest_2434, AllowsNullPageAndStillDelegates_2434) {
  PopplerPage* page = nullptr;
  cairo_t* cr = reinterpret_cast<cairo_t*>(0x1234);

  poppler_page_render(page, cr);

  ASSERT_EQ(g_state.call_count, 1);
  EXPECT_EQ(g_state.page, nullptr);
  EXPECT_EQ(g_state.cairo, cr);
  EXPECT_EQ(g_state.printing, FALSE);
  EXPECT_EQ(g_state.flags, POPPLER_RENDER_ANNOTS_ALL);
}

TEST_F(PopplerPageRenderTest_2434, AllowsNullCairoAndStillDelegates_2434) {
  PopplerPage* page = reinterpret_cast<PopplerPage*>(0xBEEF);
  cairo_t* cr = nullptr;

  poppler_page_render(page, cr);

  ASSERT_EQ(g_state.call_count, 1);
  EXPECT_EQ(g_state.page, page);
  EXPECT_EQ(g_state.cairo, nullptr);
  EXPECT_EQ(g_state.printing, FALSE);
  EXPECT_EQ(g_state.flags, POPPLER_RENDER_ANNOTS_ALL);
}

TEST_F(PopplerPageRenderTest_2434, AllowsNullPageAndNullCairoAndStillDelegates_2434) {
  poppler_page_render(nullptr, nullptr);

  ASSERT_EQ(g_state.call_count, 1);
  EXPECT_EQ(g_state.page, nullptr);
  EXPECT_EQ(g_state.cairo, nullptr);
  EXPECT_EQ(g_state.printing, FALSE);
  EXPECT_EQ(g_state.flags, POPPLER_RENDER_ANNOTS_ALL);
}