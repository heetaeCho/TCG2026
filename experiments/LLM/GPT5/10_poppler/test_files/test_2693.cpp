// renderPage_test_2693.cc
#include <gtest/gtest.h>

#include <cairo.h>
#include <cstdint>
#include <cstring>

// -----------------------------------------------------------------------------
// Provide the globals that pdftocairo.cc expects (some are declared in other utils
// like pdftoppm.cc). These are referenced by renderPage().
// -----------------------------------------------------------------------------
double x_resolution = 150.0;
double y_resolution = 150.0;
bool useCropBox = false;

bool ps = false;
int crop_x = 0;
int crop_y = 0;
bool transp = false;
bool printing = false;

// Some builds may define antialiasEnum in pdftocairo.cc; declare it weakly here
// only if the compilation unit doesn't already provide it.
// (If pdftocairo.cc defines it, this will be a harmless duplicate declaration.)
extern "C" {
  extern cairo_antialias_t antialiasEnum;
}

// -----------------------------------------------------------------------------
// Test doubles for external collaborators.
// We use macro renaming so that including pdftocairo.cc binds renderPage() to
// these controllable types (without needing Poppler's real PDFDoc/CairoOutputDev).
// -----------------------------------------------------------------------------
class CairoOutputDev_TestDouble;

class PDFDoc_TestDouble {
public:
  // Match the call-site signature used in the provided renderPage() snippet.
  void displayPageSlice(CairoOutputDev_TestDouble *out,
                        int page,
                        double hDPI,
                        double vDPI,
                        int rotate,
                        bool useMediaBox,
                        bool crop,
                        bool doPrinting,
                        int sliceX,
                        int sliceY,
                        int sliceW,
                        int sliceH) {
    ++display_calls;
    last_out = out;
    last_page = page;
    last_hDPI = hDPI;
    last_vDPI = vDPI;
    last_rotate = rotate;
    last_useMediaBox = useMediaBox;
    last_crop = crop;
    last_printing = doPrinting;
    last_sliceX = sliceX;
    last_sliceY = sliceY;
    last_sliceW = sliceW;
    last_sliceH = sliceH;
  }

  int display_calls = 0;

  CairoOutputDev_TestDouble *last_out = nullptr;
  int last_page = 0;
  double last_hDPI = 0.0;
  double last_vDPI = 0.0;
  int last_rotate = 0;
  bool last_useMediaBox = false;
  bool last_crop = false;
  bool last_printing = false;
  int last_sliceX = 0, last_sliceY = 0, last_sliceW = 0, last_sliceH = 0;
};

class CairoOutputDev_TestDouble {
public:
  void setCairo(cairo_t *cr) {
    ++set_cairo_calls;
    last_cairo = cr;
    if (cr == nullptr) {
      ++set_cairo_null_calls;
    }
  }

  void setPrinting(bool p) {
    ++set_printing_calls;
    last_printing = p;
  }

  int set_cairo_calls = 0;
  int set_cairo_null_calls = 0;
  cairo_t *last_cairo = nullptr;

  int set_printing_calls = 0;
  bool last_printing = false;
};

// Rename types inside pdftocairo.cc to our test doubles.
#define PDFDoc PDFDoc_TestDouble
#define CairoOutputDev CairoOutputDev_TestDouble

// -----------------------------------------------------------------------------
// Include the production .cc so the static renderPage() is in this test TU.
// -----------------------------------------------------------------------------
#include "./TestProjects/poppler/utils/pdftocairo.cc"

// Undo renames for safety in the rest of this file.
#undef PDFDoc
#undef CairoOutputDev

// -----------------------------------------------------------------------------
// Access production globals from pdftocairo.cc that renderPage() uses.
// If they are file-scope variables (not static), these will link directly.
// If they are static, they are still accessible here because we included the .cc.
// -----------------------------------------------------------------------------
extern cairo_surface_t *surface;

// -----------------------------------------------------------------------------
// Helpers
// -----------------------------------------------------------------------------
static uint32_t ReadARGB32Pixel(cairo_surface_t *s, int x, int y) {
  cairo_surface_flush(s);
  unsigned char *data = cairo_image_surface_get_data(s);
  const int stride = cairo_image_surface_get_stride(s);
  uint32_t pixel = 0;
  std::memcpy(&pixel, data + y * stride + x * 4, 4);
  return pixel;
}

static uint8_t A_FromARGB32(uint32_t p) { return static_cast<uint8_t>((p >> 24) & 0xFF); }
static uint8_t R_FromARGB32(uint32_t p) { return static_cast<uint8_t>((p >> 16) & 0xFF); }
static uint8_t G_FromARGB32(uint32_t p) { return static_cast<uint8_t>((p >> 8) & 0xFF); }
static uint8_t B_FromARGB32(uint32_t p) { return static_cast<uint8_t>(p & 0xFF); }

// -----------------------------------------------------------------------------
// Test fixture
// -----------------------------------------------------------------------------
class RenderPageTest_2693 : public ::testing::Test {
protected:
  void SetUp() override {
    // Reset globals that affect behavior.
    ps = false;
    crop_x = 0;
    crop_y = 0;
    transp = false;
    printing = false;
    useCropBox = false;
    x_resolution = 150.0;
    y_resolution = 150.0;

    // Create a known ARGB32 image surface and clear it to fully transparent.
    img = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, kW, kH);
    ASSERT_NE(img, nullptr);

    cairo_t *cr = cairo_create(img);
    ASSERT_NE(cr, nullptr);
    cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
    cairo_set_source_rgba(cr, 0, 0, 0, 0);
    cairo_paint(cr);
    cairo_destroy(cr);

    // Point production global surface at our test surface.
    surface = img;
  }

  void TearDown() override {
    // Detach and destroy.
    surface = nullptr;
    if (img) {
      cairo_surface_destroy(img);
      img = nullptr;
    }
  }

  static constexpr int kW = 32;
  static constexpr int kH = 32;
  cairo_surface_t *img = nullptr;
};

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

TEST_F(RenderPageTest_2693, CallsDisplayPageSliceWithExpectedFixedParameters_2693) {
  PDFDoc_TestDouble doc;
  CairoOutputDev_TestDouble out;

  // Ensure we exercise the non-printing path.
  printing = false;
  transp = true; // avoid background fill affecting surface
  useCropBox = false;

  renderPage(&doc, &out, /*pg=*/1,
             /*page_w=*/612, /*page_h=*/792,
             /*output_w=*/612, /*output_h=*/792);

  ASSERT_EQ(doc.display_calls, 1);
  EXPECT_EQ(doc.last_out, &out);
  EXPECT_EQ(doc.last_page, 1);
  EXPECT_DOUBLE_EQ(doc.last_hDPI, 72.0);
  EXPECT_DOUBLE_EQ(doc.last_vDPI, 72.0);
  EXPECT_EQ(doc.last_rotate, 0);

  // From the provided snippet:
  // useMediaBox = !useCropBox
  EXPECT_TRUE(doc.last_useMediaBox);

  // Crop parameter equals "printing" in the snippet.
  EXPECT_FALSE(doc.last_crop);
  EXPECT_FALSE(doc.last_printing);

  // Slice params are -1 in the snippet.
  EXPECT_EQ(doc.last_sliceX, -1);
  EXPECT_EQ(doc.last_sliceY, -1);
  EXPECT_EQ(doc.last_sliceW, -1);
  EXPECT_EQ(doc.last_sliceH, -1);

  // External interaction: CairoOutputDev receives cairo context then nullptr.
  EXPECT_GE(out.set_cairo_calls, 2);
  EXPECT_EQ(out.set_cairo_null_calls, 1);
}

TEST_F(RenderPageTest_2693, SetsPrintingFlagOnOutputDevWhenPrintingTrue_2693) {
  PDFDoc_TestDouble doc;
  CairoOutputDev_TestDouble out;

  printing = true;
  transp = true;

  renderPage(&doc, &out, /*pg=*/2,
             /*page_w=*/500, /*page_h=*/700,
             /*output_w=*/500, /*output_h=*/700);

  EXPECT_EQ(doc.display_calls, 1);
  EXPECT_TRUE(doc.last_crop);      // crop == printing
  EXPECT_TRUE(doc.last_printing);  // printing == printing

  EXPECT_GE(out.set_printing_calls, 1);
  EXPECT_TRUE(out.last_printing);
}

TEST_F(RenderPageTest_2693, PaintsWhiteBackgroundWhenNotPrintingAndNotTransparent_2693) {
  PDFDoc_TestDouble doc;
  CairoOutputDev_TestDouble out;

  printing = false;
  transp = false; // triggers background paint in the snippet

  // Start from fully transparent pixel at center.
  const uint32_t before = ReadARGB32Pixel(img, kW / 2, kH / 2);
  EXPECT_EQ(A_FromARGB32(before), 0);

  renderPage(&doc, &out, /*pg=*/1,
             /*page_w=*/612, /*page_h=*/792,
             /*output_w=*/612, /*output_h=*/792);

  // With our PDFDoc_TestDouble drawing nothing, the only visible effect should be
  // the "DEST_OVER white paint" background fill: center becomes opaque white.
  const uint32_t after = ReadARGB32Pixel(img, kW / 2, kH / 2);
  EXPECT_EQ(A_FromARGB32(after), 0xFF);
  EXPECT_EQ(R_FromARGB32(after), 0xFF);
  EXPECT_EQ(G_FromARGB32(after), 0xFF);
  EXPECT_EQ(B_FromARGB32(after), 0xFF);
}

TEST_F(RenderPageTest_2693, DoesNotPaintWhiteBackgroundWhenTransparentTrue_2693) {
  PDFDoc_TestDouble doc;
  CairoOutputDev_TestDouble out;

  printing = false;
  transp = true; // should skip background paint

  const uint32_t before = ReadARGB32Pixel(img, kW / 2, kH / 2);
  EXPECT_EQ(A_FromARGB32(before), 0);

  renderPage(&doc, &out, /*pg=*/1,
             /*page_w=*/612, /*page_h=*/792,
             /*output_w=*/612, /*output_h=*/792);

  const uint32_t after = ReadARGB32Pixel(img, kW / 2, kH / 2);
  // Still transparent since doc draws nothing and background fill is skipped.
  EXPECT_EQ(A_FromARGB32(after), 0);
}

TEST_F(RenderPageTest_2693, HandlesNonZeroCropOffsetsWithoutCrashing_2693) {
  PDFDoc_TestDouble doc;
  CairoOutputDev_TestDouble out;

  crop_x = 10;
  crop_y = 20;
  printing = false;
  transp = true;

  renderPage(&doc, &out, /*pg=*/1,
             /*page_w=*/612, /*page_h=*/792,
             /*output_w=*/300, /*output_h=*/400);

  EXPECT_EQ(doc.display_calls, 1);
  EXPECT_EQ(doc.last_page, 1);
}

TEST_F(RenderPageTest_2693, UsesUseCropBoxToFlipUseMediaBoxParameter_2693) {
  PDFDoc_TestDouble doc;
  CairoOutputDev_TestDouble out;

  printing = false;
  transp = true;

  useCropBox = false;
  renderPage(&doc, &out, /*pg=*/1, 100, 100, 100, 100);
  ASSERT_EQ(doc.display_calls, 1);
  EXPECT_TRUE(doc.last_useMediaBox);

  // Reset call count by recreating doc for clarity.
  PDFDoc_TestDouble doc2;
  useCropBox = true;
  renderPage(&doc2, &out, /*pg=*/1, 100, 100, 100, 100);
  ASSERT_EQ(doc2.display_calls, 1);
  EXPECT_FALSE(doc2.last_useMediaBox);
}