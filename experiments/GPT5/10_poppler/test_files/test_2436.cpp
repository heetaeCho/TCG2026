// poppler-page-render-for-printing-test.cc
//
// Unit tests for poppler_page_render_for_printing()
// TEST_ID: 2436
//
// These tests treat the implementation as a black box and only verify
// observable behavior via the public C API interaction: that
// poppler_page_render_for_printing() forwards to poppler_page_render_full()
// with printing=TRUE and flags=POPPLER_RENDER_ANNOTS_PRINT_ALL.

#include <gtest/gtest.h>

#include <glib.h>

extern "C" {

// Forward declarations to avoid relying on private internals.
typedef struct _PopplerPage PopplerPage;
typedef struct _cairo cairo_t;

// Enum comes from poppler.h in the project; include it if available.
// If your build already includes poppler.h via other includes, keeping this
// include is still fine.
#include "poppler.h"

// Function under test (defined in poppler-page.cc)
void poppler_page_render_for_printing(PopplerPage *page, cairo_t *cairo);

// Collaborator we intercept (called by poppler_page_render_for_printing).
// We provide a test double definition below to capture arguments.
void poppler_page_render_full(PopplerPage *page,
                             cairo_t *cairo,
                             gboolean printing,
                             PopplerRenderAnnotsFlags flags);
} // extern "C"

namespace {

// Simple capture state for our link-time test double.
struct RenderFullCapture {
  int call_count = 0;
  PopplerPage *last_page = nullptr;
  cairo_t *last_cairo = nullptr;
  gboolean last_printing = FALSE;
  PopplerRenderAnnotsFlags last_flags = POPPLER_RENDER_ANNOTS_NONE;

  void Reset() { *this = RenderFullCapture(); }
};

RenderFullCapture g_capture;

} // namespace

extern "C" void poppler_page_render_full(PopplerPage *page,
                                        cairo_t *cairo,
                                        gboolean printing,
                                        PopplerRenderAnnotsFlags flags) {
  // Test double: capture observable external interaction.
  g_capture.call_count++;
  g_capture.last_page = page;
  g_capture.last_cairo = cairo;
  g_capture.last_printing = printing;
  g_capture.last_flags = flags;
}

class PopplerPageRenderForPrintingTest_2436 : public ::testing::Test {
protected:
  void SetUp() override { g_capture.Reset(); }
  void TearDown() override { g_capture.Reset(); }
};

TEST_F(PopplerPageRenderForPrintingTest_2436, ForwardsToRenderFullWithPrintingTrueAndPrintAllFlags_2436) {
  // Arrange: use opaque non-null pointers without touching internals.
  auto *fake_page = reinterpret_cast<PopplerPage *>(0x1);
  auto *fake_cairo = reinterpret_cast<cairo_t *>(0x2);

  // Act
  poppler_page_render_for_printing(fake_page, fake_cairo);

  // Assert: exactly one forwarding call with expected parameters.
  EXPECT_EQ(g_capture.call_count, 1);
  EXPECT_EQ(g_capture.last_page, fake_page);
  EXPECT_EQ(g_capture.last_cairo, fake_cairo);
  EXPECT_EQ(g_capture.last_printing, TRUE);
  EXPECT_EQ(g_capture.last_flags, POPPLER_RENDER_ANNOTS_PRINT_ALL);
}

TEST_F(PopplerPageRenderForPrintingTest_2436, AcceptsNullPageAndStillForwardsArguments_2436) {
  // Act
  poppler_page_render_for_printing(nullptr, reinterpret_cast<cairo_t *>(0x3));

  // Assert
  EXPECT_EQ(g_capture.call_count, 1);
  EXPECT_EQ(g_capture.last_page, nullptr);
  EXPECT_EQ(g_capture.last_cairo, reinterpret_cast<cairo_t *>(0x3));
  EXPECT_EQ(g_capture.last_printing, TRUE);
  EXPECT_EQ(g_capture.last_flags, POPPLER_RENDER_ANNOTS_PRINT_ALL);
}

TEST_F(PopplerPageRenderForPrintingTest_2436, AcceptsNullCairoAndStillForwardsArguments_2436) {
  // Act
  poppler_page_render_for_printing(reinterpret_cast<PopplerPage *>(0x4), nullptr);

  // Assert
  EXPECT_EQ(g_capture.call_count, 1);
  EXPECT_EQ(g_capture.last_page, reinterpret_cast<PopplerPage *>(0x4));
  EXPECT_EQ(g_capture.last_cairo, nullptr);
  EXPECT_EQ(g_capture.last_printing, TRUE);
  EXPECT_EQ(g_capture.last_flags, POPPLER_RENDER_ANNOTS_PRINT_ALL);
}

TEST_F(PopplerPageRenderForPrintingTest_2436, MultipleCallsForwardEachTime_2436) {
  auto *fake_page1 = reinterpret_cast<PopplerPage *>(0x10);
  auto *fake_cairo1 = reinterpret_cast<cairo_t *>(0x20);
  auto *fake_page2 = reinterpret_cast<PopplerPage *>(0x11);
  auto *fake_cairo2 = reinterpret_cast<cairo_t *>(0x21);

  poppler_page_render_for_printing(fake_page1, fake_cairo1);
  EXPECT_EQ(g_capture.call_count, 1);
  EXPECT_EQ(g_capture.last_page, fake_page1);
  EXPECT_EQ(g_capture.last_cairo, fake_cairo1);

  poppler_page_render_for_printing(fake_page2, fake_cairo2);
  EXPECT_EQ(g_capture.call_count, 2);
  EXPECT_EQ(g_capture.last_page, fake_page2);
  EXPECT_EQ(g_capture.last_cairo, fake_cairo2);
  EXPECT_EQ(g_capture.last_printing, TRUE);
  EXPECT_EQ(g_capture.last_flags, POPPLER_RENDER_ANNOTS_PRINT_ALL);
}