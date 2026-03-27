// poppler_layers_iter_get_layer_test_2251.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace {

class TempFile {
public:
  explicit TempFile(const std::string &contents, const char *suffix = ".pdf") {
    // Create a unique temp file path.
    char tmpl[] = "/tmp/poppler-ut-2251-XXXXXX";
    int fd = g_mkstemp(tmpl);
    EXPECT_GE(fd, 0);

    path_ = std::string(tmpl) + suffix;

    // Close the fd from mkstemp and recreate with suffix name.
    close(fd);
    g_unlink(tmpl);

    std::ofstream out(path_, std::ios::binary);
    out.write(contents.data(), static_cast<std::streamsize>(contents.size()));
    out.close();
  }

  ~TempFile() {
    if (!path_.empty()) {
      g_unlink(path_.c_str());
    }
  }

  const std::string &path() const { return path_; }

private:
  std::string path_;
};

static std::string BuildSimplePdf_NoLayers() {
  // Minimal 1-page PDF without Optional Content (layers).
  // We keep it simple; Poppler should be able to open it.
  std::ostringstream pdf;
  std::vector<long> offsets;

  auto add_obj = [&](int obj_num, const std::string &body) {
    offsets.push_back(static_cast<long>(pdf.tellp()));
    pdf << obj_num << " 0 obj\n" << body << "\nendobj\n";
  };

  pdf << "%PDF-1.4\n";

  add_obj(1, "<< /Type /Catalog /Pages 2 0 R >>");
  add_obj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
  add_obj(3, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] "
             "/Contents 4 0 R "
             "/Resources << /Font << /F1 5 0 R >> >> >>");

  const std::string stream =
      "BT\n"
      "/F1 12 Tf\n"
      "50 100 Td\n"
      "(Hello) Tj\n"
      "ET\n";
  {
    std::ostringstream obj4;
    obj4 << "<< /Length " << stream.size() << " >>\nstream\n" << stream << "endstream";
    add_obj(4, obj4.str());
  }

  add_obj(5, "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>");

  const long xref_pos = static_cast<long>(pdf.tellp());
  pdf << "xref\n";
  pdf << "0 " << (offsets.size() + 1) << "\n";
  pdf << "0000000000 65535 f \n";
  for (long off : offsets) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", off);
    pdf << buf << " 00000 n \n";
  }

  pdf << "trailer\n";
  pdf << "<< /Size " << (offsets.size() + 1) << " /Root 1 0 R >>\n";
  pdf << "startxref\n" << xref_pos << "\n%%EOF\n";

  return pdf.str();
}

static std::string BuildSimplePdf_WithOneLayer(const std::string &layer_name) {
  // Minimal 1-page PDF with a single Optional Content Group (OCG) and OCProperties.
  std::ostringstream pdf;
  std::vector<long> offsets;

  auto add_obj = [&](int obj_num, const std::string &body) {
    offsets.push_back(static_cast<long>(pdf.tellp()));
    pdf << obj_num << " 0 obj\n" << body << "\nendobj\n";
  };

  pdf << "%PDF-1.5\n";

  // 1: Catalog with OCProperties.
  add_obj(1,
          "<< /Type /Catalog /Pages 2 0 R "
          "/OCProperties << /OCGs [6 0 R] /D << /Order [6 0 R] >> >> >>");

  // 2: Pages
  add_obj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  // 3: Page, with Properties mapping /OC1 => OCG object (6 0).
  add_obj(3,
          "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] "
          "/Contents 4 0 R "
          "/Resources << "
          "  /Font << /F1 5 0 R >> "
          "  /Properties << /OC1 6 0 R >> "
          ">> >>");

  // 4: Content stream uses marked content with /OC /OC1.
  const std::string stream =
      "/OC /OC1 BDC\n"
      "BT\n"
      "/F1 12 Tf\n"
      "50 100 Td\n"
      "(Layered) Tj\n"
      "ET\n"
      "EMC\n";
  {
    std::ostringstream obj4;
    obj4 << "<< /Length " << stream.size() << " >>\nstream\n" << stream << "endstream";
    add_obj(4, obj4.str());
  }

  // 5: Font
  add_obj(5, "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>");

  // 6: OCG
  {
    std::ostringstream obj6;
    obj6 << "<< /Type /OCG /Name (" << layer_name << ") >>";
    add_obj(6, obj6.str());
  }

  const long xref_pos = static_cast<long>(pdf.tellp());
  pdf << "xref\n";
  pdf << "0 " << (offsets.size() + 1) << "\n";
  pdf << "0000000000 65535 f \n";
  for (long off : offsets) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", off);
    pdf << buf << " 00000 n \n";
  }

  pdf << "trailer\n";
  pdf << "<< /Size " << (offsets.size() + 1) << " /Root 1 0 R >>\n";
  pdf << "startxref\n" << xref_pos << "\n%%EOF\n";

  return pdf.str();
}

static PopplerDocument *OpenDocFromPathOrFail(const std::string &path) {
  GError *error = nullptr;
  gchar *uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, &error);
  EXPECT_NE(uri, nullptr);
  EXPECT_EQ(error, nullptr);

  PopplerDocument *doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
  g_free(uri);

  EXPECT_NE(doc, nullptr);
  EXPECT_EQ(error, nullptr);
  if (error) {
    g_error_free(error);
  }
  return doc;
}

class PopplerLayersIterGetLayerTest_2251 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure type system is initialized for older GLib setups; safe no-op on newer.
    static gsize once = 0;
    if (g_once_init_enter(&once)) {
#if !GLIB_CHECK_VERSION(2, 36, 0)
      g_type_init();
#endif
      g_once_init_leave(&once, 1);
    }
  }
};

}  // namespace

TEST_F(PopplerLayersIterGetLayerTest_2251, NullIterReturnsNull_2251) {
  // Observable behavior from g_return_val_if_fail: NULL return.
  EXPECT_EQ(poppler_layers_iter_get_layer(nullptr), nullptr);
}

TEST_F(PopplerLayersIterGetLayerTest_2251, NoLayersDocumentYieldsNoLayer_2251) {
  const std::string pdf = BuildSimplePdf_NoLayers();
  TempFile tmp(pdf);

  PopplerDocument *doc = OpenDocFromPathOrFail(tmp.path());
  ASSERT_NE(doc, nullptr);

  PopplerLayersIter *iter = poppler_document_get_layers(doc);

  // API may return nullptr if there are no layers; either way, get_layer should not produce a layer.
  if (iter == nullptr) {
    SUCCEED();
    g_object_unref(doc);
    return;
  }

  EXPECT_EQ(poppler_layers_iter_get_layer(iter), nullptr);

  poppler_layers_iter_free(iter);
  g_object_unref(doc);
}

TEST_F(PopplerLayersIterGetLayerTest_2251, LayeredDocumentReturnsLayerWithExpectedTitle_2251) {
  const std::string kLayerName = "Layer 1";
  const std::string pdf = BuildSimplePdf_WithOneLayer(kLayerName);
  TempFile tmp(pdf);

  PopplerDocument *doc = OpenDocFromPathOrFail(tmp.path());
  ASSERT_NE(doc, nullptr);

  PopplerLayersIter *iter = poppler_document_get_layers(doc);
  ASSERT_NE(iter, nullptr);

  PopplerLayer *layer = poppler_layers_iter_get_layer(iter);
  ASSERT_NE(layer, nullptr);

  // Verify observable behavior through public API: title exposed by PopplerLayer.
  gchar *title = poppler_layer_get_title(layer);
  ASSERT_NE(title, nullptr);
  EXPECT_STREQ(title, kLayerName.c_str());
  g_free(title);

  g_object_unref(layer);
  poppler_layers_iter_free(iter);
  g_object_unref(doc);
}

TEST_F(PopplerLayersIterGetLayerTest_2251, AdvancingPastEndYieldsNullLayer_2251) {
  const std::string pdf = BuildSimplePdf_WithOneLayer("OnlyLayer");
  TempFile tmp(pdf);

  PopplerDocument *doc = OpenDocFromPathOrFail(tmp.path());
  ASSERT_NE(doc, nullptr);

  PopplerLayersIter *iter = poppler_document_get_layers(doc);
  ASSERT_NE(iter, nullptr);

  // First layer should exist.
  PopplerLayer *first = poppler_layers_iter_get_layer(iter);
  ASSERT_NE(first, nullptr);
  g_object_unref(first);

  // Advance until no more; then get_layer should return nullptr (boundary).
  while (poppler_layers_iter_next(iter)) {
    // iterate
  }
  EXPECT_EQ(poppler_layers_iter_get_layer(iter), nullptr);

  poppler_layers_iter_free(iter);
  g_object_unref(doc);
}