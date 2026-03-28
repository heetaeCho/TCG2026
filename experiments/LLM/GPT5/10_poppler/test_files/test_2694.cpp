// endPage_test_2694.cc
#include <gtest/gtest.h>

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <string>

//
// Test strategy:
// - Treat endPage(...) as a black box, but intercept *external* side effects:
//   - cairo_* functions
//   - writePageImage(...)
//   - fprintf(stderr, ...)
//
// Because endPage is `static` in pdftocairo.cc, we include the .cc directly so the
// test TU can call it, while macro-renaming external C calls to test stubs.
//

// -----------------------
// Minimal Cairo type stubs
// -----------------------
struct cairo_t {};
struct cairo_surface_t {};
using cairo_status_t = int;

// -----------------------
// Global variables referenced by pdftocairo.cc (as shown in the prompt)
// -----------------------
bool printing = false;
cairo_surface_t *surface = nullptr;

// Guarded in pdftocairo.cc by #ifdef CAIRO_HAS_WIN32_SURFACE
// We'll define it unconditionally; whether it's used depends on the macro in the build.
bool printToWin32 = false;

// -----------------------
// Test-side effect capture
// -----------------------
namespace {

struct Counters {
  int cairo_create = 0;
  int cairo_destroy = 0;
  int cairo_status = 0;
  int cairo_surface_show_page = 0;
  int cairo_surface_finish = 0;
  int cairo_surface_status = 0;
  int cairo_surface_destroy = 0;
  int cairo_status_to_string = 0;

  int writePageImage = 0;

  int win32EndPage = 0;

  int fprintf_calls = 0;
  std::string last_fprintf_fmt;

  // Statuses returned by our stubs (controllable by tests)
  cairo_status_t cairo_status_ret = 0;
  cairo_status_t cairo_surface_status_ret = 0;

  // Last-seen args
  cairo_surface_t *last_surface_arg = nullptr;
} g;

void ResetAll() {
  g = Counters{};
}

} // namespace

// -----------------------
// External function stubs (via macro renaming)
// -----------------------
extern "C" {

cairo_t *test_cairo_create(cairo_surface_t *s) {
  g.cairo_create++;
  g.last_surface_arg = s;
  static cairo_t fake;
  return &fake;
}

void test_cairo_destroy(cairo_t * /*cr*/) { g.cairo_destroy++; }

cairo_status_t test_cairo_status(cairo_t * /*cr*/) {
  g.cairo_status++;
  return g.cairo_status_ret;
}

const char *test_cairo_status_to_string(cairo_status_t /*status*/) {
  g.cairo_status_to_string++;
  return "stub-status";
}

void test_cairo_surface_show_page(cairo_surface_t * /*s*/) { g.cairo_surface_show_page++; }

void test_cairo_surface_finish(cairo_surface_t * /*s*/) { g.cairo_surface_finish++; }

cairo_status_t test_cairo_surface_status(cairo_surface_t * /*s*/) {
  g.cairo_surface_status++;
  return g.cairo_surface_status_ret;
}

void test_cairo_surface_destroy(cairo_surface_t * /*s*/) { g.cairo_surface_destroy++; }

int test_fprintf(std::FILE * /*stream*/, const char *fmt, ...) {
  g.fprintf_calls++;
  g.last_fprintf_fmt = (fmt ? fmt : "");

  // We do not attempt to fully format the message; we only verify that fprintf is invoked.
  // Consume varargs to keep ABI happy.
  va_list ap;
  va_start(ap, fmt);
  va_end(ap);
  return 0;
}

} // extern "C"

// -----------------------
// Minimal GooString + CairoOutputDev definitions
//
// Note: We avoid asserting on internal Poppler behavior; we only provide enough for compilation.
// -----------------------
class GooString {
public:
  GooString() = default;
  explicit GooString(const char *s) : s_(s ? s : "") {}
  const std::string &toStr() const { return s_; }

private:
  std::string s_;
};

class CairoOutputDev {
public:
  void setCairo(cairo_t * /*cr*/) {}
  void setCairo(std::nullptr_t) {}
  void setPrinting(bool /*p*/) {}
  void emitStructTree() {}
};

// -----------------------
// Other functions referenced by endPage()
// -----------------------
void writePageImage(GooString * /*imageFileName*/) { g.writePageImage++; }

#ifdef CAIRO_HAS_WIN32_SURFACE
void win32EndPage(GooString * /*imageFileName*/) { g.win32EndPage++; }
#endif

// -----------------------
// Macro-renaming to route external calls used by pdftocairo.cc into our stubs
// -----------------------
#define cairo_create test_cairo_create
#define cairo_destroy test_cairo_destroy
#define cairo_status test_cairo_status
#define cairo_status_to_string test_cairo_status_to_string
#define cairo_surface_show_page test_cairo_surface_show_page
#define cairo_surface_finish test_cairo_surface_finish
#define cairo_surface_status test_cairo_surface_status
#define cairo_surface_destroy test_cairo_surface_destroy
#define fprintf test_fprintf

// Include the production file so we can call the `static` endPage(...) directly.
// The build system should have the include path set so this resolves correctly.
#include "pdftocairo.cc"

// Undefine to avoid leaking macros into other includes/tests.
#undef cairo_create
#undef cairo_destroy
#undef cairo_status
#undef cairo_status_to_string
#undef cairo_surface_show_page
#undef cairo_surface_finish
#undef cairo_surface_status
#undef cairo_surface_destroy
#undef fprintf

// -----------------------
// Test fixture
// -----------------------
class EndPageTest_2694 : public ::testing::Test {
protected:
  void SetUp() override {
    ResetAll();
    printing = false;
    printToWin32 = false;
    static cairo_surface_t fakeSurface;
    surface = &fakeSurface;
    g.cairo_status_ret = 0;
    g.cairo_surface_status_ret = 0;
  }
};

// -----------------------
// Tests
// -----------------------

TEST_F(EndPageTest_2694, NonPrinting_WritesImageAndFinishesAndDestroysSurface_2694) {
  GooString fileName("out.png");
  CairoOutputDev out;

  printing = false;

  endPage(&fileName, &out, /*isLastPage=*/false);

  EXPECT_EQ(g.writePageImage, 1);
  EXPECT_EQ(g.cairo_surface_finish, 1);
  EXPECT_EQ(g.cairo_surface_status, 1);
  EXPECT_EQ(g.cairo_surface_destroy, 1);

  EXPECT_EQ(g.cairo_surface_show_page, 0);
  EXPECT_EQ(g.cairo_create, 0);
  EXPECT_EQ(g.cairo_destroy, 0);
}

TEST_F(EndPageTest_2694, Printing_NotLastPage_ShowsPageOnly_2694) {
  GooString fileName("print.pdf");
  CairoOutputDev out;

  printing = true;

  endPage(&fileName, &out, /*isLastPage=*/false);

  EXPECT_EQ(g.cairo_surface_show_page, 1);

  // Not last page: should not create/destroy a cairo_t in the shown snippet.
  EXPECT_EQ(g.cairo_create, 0);
  EXPECT_EQ(g.cairo_destroy, 0);

  // Printing path should not write images or finish/destroy surface in the shown snippet.
  EXPECT_EQ(g.writePageImage, 0);
  EXPECT_EQ(g.cairo_surface_finish, 0);
  EXPECT_EQ(g.cairo_surface_destroy, 0);
}

TEST_F(EndPageTest_2694, Printing_LastPage_CreatesAndDestroysCairoContextAndShowsPage_2694) {
  GooString fileName("print-last.pdf");
  CairoOutputDev out;

  printing = true;

  endPage(&fileName, &out, /*isLastPage=*/true);

  EXPECT_EQ(g.cairo_create, 1);
  EXPECT_EQ(g.cairo_destroy, 1);
  EXPECT_EQ(g.cairo_surface_show_page, 1);

  // Verify cairo_create was called with the global surface.
  EXPECT_EQ(g.last_surface_arg, surface);

  EXPECT_EQ(g.writePageImage, 0);
  EXPECT_EQ(g.cairo_surface_finish, 0);
  EXPECT_EQ(g.cairo_surface_destroy, 0);
}

TEST_F(EndPageTest_2694, Printing_LastPage_WhenCairoStatusNonZero_ReportsErrorViaFprintf_2694) {
  GooString fileName("print-last.pdf");
  CairoOutputDev out;

  printing = true;
  g.cairo_status_ret = 1; // non-zero => error path

  endPage(&fileName, &out, /*isLastPage=*/true);

  EXPECT_GE(g.fprintf_calls, 1);
  EXPECT_NE(g.last_fprintf_fmt.find("cairo error:"), std::string::npos);
  EXPECT_EQ(g.cairo_status, 1);
  EXPECT_EQ(g.cairo_status_to_string, 1);
}

TEST_F(EndPageTest_2694, NonPrinting_WhenSurfaceStatusNonZero_ReportsErrorViaFprintf_2694) {
  GooString fileName("out.png");
  CairoOutputDev out;

  printing = false;
  g.cairo_surface_status_ret = 2; // non-zero => error path

  endPage(&fileName, &out, /*isLastPage=*/false);

  EXPECT_EQ(g.writePageImage, 1);
  EXPECT_EQ(g.cairo_surface_status, 1);

  EXPECT_GE(g.fprintf_calls, 1);
  EXPECT_NE(g.last_fprintf_fmt.find("cairo error:"), std::string::npos);
  EXPECT_EQ(g.cairo_status_to_string, 1);
}

TEST_F(EndPageTest_2694, NullImageFileName_IsAcceptedOnBothPaths_2694) {
  CairoOutputDev out;

  // Non-printing path should call writePageImage(nullptr) via our stub safely.
  printing = false;
  endPage(/*imageFileName=*/nullptr, &out, /*isLastPage=*/false);
  EXPECT_EQ(g.writePageImage, 1);

  // Reset and try printing path; should not require imageFileName unless win32 page end is enabled.
  ResetAll();
  printing = true;
  endPage(/*imageFileName=*/nullptr, &out, /*isLastPage=*/false);
  EXPECT_EQ(g.cairo_surface_show_page, 1);
}

#ifdef CAIRO_HAS_WIN32_SURFACE
TEST_F(EndPageTest_2694, Printing_WithWin32Enabled_CallsWin32EndPage_2694) {
  GooString fileName("win32");
  CairoOutputDev out;

  printing = true;
  printToWin32 = true;

  endPage(&fileName, &out, /*isLastPage=*/false);

  EXPECT_EQ(g.cairo_surface_show_page, 1);
  EXPECT_EQ(g.win32EndPage, 1);
}
#endif