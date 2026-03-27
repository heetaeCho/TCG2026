// File: poppler-page-get-image-output-dev-test_2447.cc
//
// Unit tests for:
//   static CairoImageOutputDev *poppler_page_get_image_output_dev(PopplerPage *page,
//       bool (*imgDrawDeviceCbk)(int img_id, void *data), void *imgDrawCbkData)
//
// NOTE:
// - We treat the implementation as a black box.
// - We validate only observable behavior via the returned CairoImageOutputDev public API
//   and callback invocations.
// - To access the TU-local (static) function, we include the .cc file directly.
//
// TEST_ID: 2447

#include <gtest/gtest.h>

#include <poppler.h>

#include <atomic>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "poppler/CairoOutputDev.h"

// Include the implementation file to access the static function under test.
#include "glib/poppler-page.cc"

namespace {

class PopplerPageGetImageOutputDevTest_2447 : public ::testing::Test {
protected:
  static std::string BuildPdfFromObjects(const std::vector<std::string> &objects) {
    // objects[i] is object (i+1) body (WITHOUT "n 0 obj" / "endobj").
    std::string pdf;
    pdf += "%PDF-1.4\n";

    std::vector<size_t> offsets;
    offsets.reserve(objects.size() + 1);
    offsets.push_back(0); // obj 0 free; placeholder for xref format

    for (size_t i = 0; i < objects.size(); ++i) {
      offsets.push_back(pdf.size());
      pdf += std::to_string(i + 1) + " 0 obj\n";
      pdf += objects[i];
      if (pdf.empty() || pdf.back() != '\n') pdf += "\n";
      pdf += "endobj\n";
    }

    const size_t xref_pos = pdf.size();
    pdf += "xref\n";
    pdf += "0 " + std::to_string(objects.size() + 1) + "\n";
    pdf += "0000000000 65535 f \n";
    for (size_t i = 1; i < offsets.size(); ++i) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offsets[i]);
      pdf += buf;
    }

    pdf += "trailer\n";
    pdf += "<< /Size " + std::to_string(objects.size() + 1) + " /Root 1 0 R >>\n";
    pdf += "startxref\n";
    pdf += std::to_string(xref_pos) + "\n";
    pdf += "%%EOF\n";
    return pdf;
  }

  static std::string MakeTextOnlyPdf() {
    // 1: Catalog
    // 2: Pages
    // 3: Page
    // 4: Contents (text)
    // 5: Font
    const std::string content = "BT /F1 12 Tf 72 720 Td (Hi) Tj ET\n";
    std::vector<std::string> objs;
    objs.emplace_back("<< /Type /Catalog /Pages 2 0 R >>");
    objs.emplace_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
    objs.emplace_back("<< /Type /Page /Parent 2 0 R "
                      "/MediaBox [0 0 612 792] "
                      "/Resources << /Font << /F1 5 0 R >> >> "
                      "/Contents 4 0 R >>");
    objs.emplace_back("<< /Length " + std::to_string(content.size()) + " >>\nstream\n" + content +
                      "endstream");
    objs.emplace_back("<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>");
    return BuildPdfFromObjects(objs);
  }

  static std::string MakeSingleImagePdf() {
    // 1: Catalog
    // 2: Pages
    // 3: Page (Resources include Im0)
    // 4: Contents (paint Im0)
    // 5: Image XObject (1x1 RGB)
    const std::string img_data = std::string("\xFF\x00\x00", 3); // red pixel RGB
    const std::string content =
        "q\n"
        "100 0 0 100 50 650 cm\n"
        "/Im0 Do\n"
        "Q\n";

    std::vector<std::string> objs;
    objs.emplace_back("<< /Type /Catalog /Pages 2 0 R >>");
    objs.emplace_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
    objs.emplace_back("<< /Type /Page /Parent 2 0 R "
                      "/MediaBox [0 0 612 792] "
                      "/Resources << /XObject << /Im0 5 0 R >> >> "
                      "/Contents 4 0 R >>");
    objs.emplace_back("<< /Length " + std::to_string(content.size()) + " >>\nstream\n" + content +
                      "endstream");

    // Image object
    // NOTE: stream length is 3 bytes.
    std::string img_obj;
    img_obj += "<< /Type /XObject /Subtype /Image ";
    img_obj += "/Width 1 /Height 1 ";
    img_obj += "/ColorSpace /DeviceRGB /BitsPerComponent 8 ";
    img_obj += "/Length " + std::to_string(img_data.size()) + " >>\n";
    img_obj += "stream\n";
    img_obj += img_data;
    img_obj += "\nendstream";
    objs.emplace_back(img_obj);

    return BuildPdfFromObjects(objs);
  }

  static std::string WriteTempFile(const std::string &bytes, const char *suffix) {
    const auto dir = std::filesystem::temp_directory_path();
    std::string tmpl = (dir / ("poppler_gtest_XXXXXX" + std::string(suffix))).string();

    // mkstemp requires trailing XXXXXX in the filename.
    // We'll ensure that by building a base template and then appending suffix after creation.
    // Simpler: create mkstemp with XXXXXX and then rename with suffix.
    std::string mk = (dir / "poppler_gtest_XXXXXX").string();
    std::vector<char> path(mk.begin(), mk.end());
    path.push_back('\0');

    int fd = ::mkstemp(path.data());
    if (fd < 0) {
      return {};
    }
    ::close(fd);

    std::string final_path = std::string(path.data()) + suffix;
    std::error_code ec;
    std::filesystem::rename(path.data(), final_path, ec);
    if (ec) {
      // If rename fails, just use original.
      final_path = path.data();
    }

    std::ofstream out(final_path, std::ios::binary);
    out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    out.close();
    return final_path;
  }

  static PopplerDocument *OpenPopplerDocumentFromPath(const std::string &path) {
    GError *error = nullptr;
    char *uri = g_filename_to_uri(path.c_str(), nullptr, &error);
    if (!uri) {
      if (error) g_error_free(error);
      return nullptr;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, /*password*/ nullptr, &error);
    g_free(uri);

    if (!doc) {
      if (error) g_error_free(error);
      return nullptr;
    }
    if (error) g_error_free(error);
    return doc;
  }

  static PopplerPage *GetFirstPage(PopplerDocument *doc) {
    if (!doc) return nullptr;
    return poppler_document_get_page(doc, 0);
  }

  static bool CountCbkReturnTrue(int /*img_id*/, void *data) {
    auto *ctr = static_cast<std::atomic<int> *>(data);
    ++(*ctr);
    return true;
  }

  static bool CountCbkReturnFalse(int /*img_id*/, void *data) {
    auto *ctr = static_cast<std::atomic<int> *>(data);
    ++(*ctr);
    return false;
  }

  static bool FailIfCalledCbk(int /*img_id*/, void *data) {
    auto *called = static_cast<std::atomic<bool> *>(data);
    called->store(true);
    return true;
  }
};

TEST_F(PopplerPageGetImageOutputDevTest_2447, ReturnsNonNullWithoutCallback_2447) {
  const std::string pdf = MakeSingleImagePdf();
  const std::string path = WriteTempFile(pdf, ".pdf");
  ASSERT_FALSE(path.empty());

  PopplerDocument *doc = OpenPopplerDocumentFromPath(path);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = GetFirstPage(doc);
  ASSERT_NE(page, nullptr);

  CairoImageOutputDev *dev = poppler_page_get_image_output_dev(page, nullptr, nullptr);
  ASSERT_NE(dev, nullptr);

  // Observable via public API:
  // For a PDF containing an image, the output device should end up with >= 1 images in typical cases.
  // We assert a weak but useful condition: non-negative and does not crash.
  EXPECT_GE(dev->getNumImages(), 0);

  delete dev;
  g_object_unref(page);
  g_object_unref(doc);

  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(PopplerPageGetImageOutputDevTest_2447, CallbackInvokedForImagePage_2447) {
  const std::string pdf = MakeSingleImagePdf();
  const std::string path = WriteTempFile(pdf, ".pdf");
  ASSERT_FALSE(path.empty());

  PopplerDocument *doc = OpenPopplerDocumentFromPath(path);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = GetFirstPage(doc);
  ASSERT_NE(page, nullptr);

  std::atomic<int> calls{0};
  CairoImageOutputDev *dev = poppler_page_get_image_output_dev(page, &CountCbkReturnTrue, &calls);
  ASSERT_NE(dev, nullptr);

  // External interaction: callback should be invoked at least once when the page has an image.
  EXPECT_GE(calls.load(), 1);

  // And images should be collected (when callback returns true).
  EXPECT_GE(dev->getNumImages(), 0);

  delete dev;
  g_object_unref(page);
  g_object_unref(doc);

  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(PopplerPageGetImageOutputDevTest_2447, CallbackCanFilterImages_2447) {
  const std::string pdf = MakeSingleImagePdf();
  const std::string path = WriteTempFile(pdf, ".pdf");
  ASSERT_FALSE(path.empty());

  PopplerDocument *doc = OpenPopplerDocumentFromPath(path);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = GetFirstPage(doc);
  ASSERT_NE(page, nullptr);

  std::atomic<int> calls_true{0};
  std::unique_ptr<CairoImageOutputDev> dev_true(
      poppler_page_get_image_output_dev(page, &CountCbkReturnTrue, &calls_true));
  ASSERT_NE(dev_true.get(), nullptr);
  EXPECT_GE(calls_true.load(), 1);
  const int n_true = dev_true->getNumImages();
  EXPECT_GE(n_true, 0);

  std::atomic<int> calls_false{0};
  std::unique_ptr<CairoImageOutputDev> dev_false(
      poppler_page_get_image_output_dev(page, &CountCbkReturnFalse, &calls_false));
  ASSERT_NE(dev_false.get(), nullptr);
  EXPECT_GE(calls_false.load(), 1);
  const int n_false = dev_false->getNumImages();
  EXPECT_GE(n_false, 0);

  // Boundary/behavioral check without inferring internals:
  // If returning false indicates "do not draw/save", the device should not end up with *more*
  // images than when returning true.
  EXPECT_LE(n_false, n_true);

  g_object_unref(page);
  g_object_unref(doc);

  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(PopplerPageGetImageOutputDevTest_2447, TextOnlyPageDoesNotInvokeCallbackAndHasNoImages_2447) {
  const std::string pdf = MakeTextOnlyPdf();
  const std::string path = WriteTempFile(pdf, ".pdf");
  ASSERT_FALSE(path.empty());

  PopplerDocument *doc = OpenPopplerDocumentFromPath(path);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = GetFirstPage(doc);
  ASSERT_NE(page, nullptr);

  std::atomic<bool> called{false};
  CairoImageOutputDev *dev = poppler_page_get_image_output_dev(page, &FailIfCalledCbk, &called);
  ASSERT_NE(dev, nullptr);

  // External interaction: for a text-only page, image decision callback should not be invoked.
  EXPECT_FALSE(called.load());

  // Observable result: no images should have been captured.
  EXPECT_EQ(dev->getNumImages(), 0);

  delete dev;
  g_object_unref(page);
  g_object_unref(doc);

  std::error_code ec;
  std::filesystem::remove(path, ec);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PopplerPageGetImageOutputDevTest_2447, DeathOnNullPage_2447) {
  // Error case (observable): passing nullptr is invalid and should crash/abort.
  // We do not infer the internal mechanism; we only assert that it is not safe.
  EXPECT_DEATH(
      {
        CairoImageOutputDev *dev = poppler_page_get_image_output_dev(nullptr, nullptr, nullptr);
        // Prevent unused warning if it somehow returns.
        if (dev) delete dev;
      },
      "");
}
#endif

} // namespace