// poppler_fonts_iter_get_font_type_test_2224.cc
#include <gtest/gtest.h>

#include <poppler.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace {

class ScopedGError {
public:
  ScopedGError() : err_(nullptr) {}
  ~ScopedGError() { clear(); }
  GError **out_ptr() { return &err_; }
  GError *get() const { return err_; }
  void clear() {
    if (err_) {
      g_error_free(err_);
      err_ = nullptr;
    }
  }

private:
  GError *err_;
};

class ScopedGObject {
public:
  ScopedGObject() : obj_(nullptr) {}
  explicit ScopedGObject(gpointer obj) : obj_(obj) {}
  ~ScopedGObject() {
    if (obj_) {
      g_object_unref(obj_);
      obj_ = nullptr;
    }
  }
  ScopedGObject(const ScopedGObject &) = delete;
  ScopedGObject &operator=(const ScopedGObject &) = delete;

  gpointer get() const { return obj_; }
  template <typename T>
  T *as() const {
    return static_cast<T *>(obj_);
  }
  gpointer *out_ptr() { return &obj_; }
  void reset(gpointer obj) {
    if (obj_) g_object_unref(obj_);
    obj_ = obj;
  }

private:
  gpointer obj_;
};

static std::string BuildMinimalPdfWithType1Helvetica() {
  // Construct a minimal, valid, single-page PDF that uses a Type1 Helvetica font.
  // This is a test fixture asset generator (not Poppler logic).
  struct Obj {
    int num;
    std::string body;
  };

  std::vector<Obj> objs;
  objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R >>"});
  objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"});
  objs.push_back({3,
                  "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 300 144]\n"
                  "   /Resources << /Font << /F1 4 0 R >> >>\n"
                  "   /Contents 5 0 R >>"});
  objs.push_back({4, "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>"});

  const std::string stream =
      "BT\n"
      "/F1 12 Tf\n"
      "72 72 Td\n"
      "(Hi) Tj\n"
      "ET\n";
  {
    std::ostringstream ss;
    ss << "<< /Length " << stream.size() << " >>\n"
       << "stream\n"
       << stream
       << "endstream";
    objs.push_back({5, ss.str()});
  }

  std::ostringstream out;
  out << "%PDF-1.4\n";

  // Track offsets for xref.
  std::vector<long> offsets(6, 0);  // indices 0..5
  for (const auto &o : objs) {
    offsets[o.num] = static_cast<long>(out.tellp());
    out << o.num << " 0 obj\n" << o.body << "\nendobj\n";
  }

  const long xref_pos = static_cast<long>(out.tellp());
  out << "xref\n";
  out << "0 6\n";
  out << "0000000000 65535 f \n";
  for (int i = 1; i <= 5; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    out << buf;
  }

  out << "trailer\n";
  out << "<< /Size 6 /Root 1 0 R >>\n";
  out << "startxref\n";
  out << xref_pos << "\n";
  out << "%%EOF\n";
  return out.str();
}

static std::string WriteToTempPdfFile(const std::string &pdf_bytes) {
  // Use glib helper to safely create a temporary file name.
  gchar *tmp_name = nullptr;
  int fd = g_file_open_tmp("poppler-fonttype-2224-XXXXXX.pdf", &tmp_name, nullptr);
  EXPECT_NE(fd, -1);
  EXPECT_NE(tmp_name, nullptr);

  // Write bytes.
  {
    std::ofstream ofs(tmp_name, std::ios::binary);
    EXPECT_TRUE(ofs.good());
    ofs.write(pdf_bytes.data(), static_cast<std::streamsize>(pdf_bytes.size()));
    ofs.flush();
    EXPECT_TRUE(ofs.good());
  }

  // Close the fd returned by g_file_open_tmp.
#if defined(G_OS_WIN32)
  _close(fd);
#else
  close(fd);
#endif

  std::string path(tmp_name);
  g_free(tmp_name);
  return path;
}

static std::string FilenameToUri(const std::string &path) {
  ScopedGError err;
  gchar *uri = g_filename_to_uri(path.c_str(), nullptr, err.out_ptr());
  EXPECT_EQ(err.get(), nullptr);
  EXPECT_NE(uri, nullptr);
  std::string out(uri);
  g_free(uri);
  return out;
}

static bool IsValidPopplerFontTypeEnum(PopplerFontType t) {
  // Based on the enum in poppler-document.h (0..11).
  return t >= POPPLER_FONT_TYPE_UNKNOWN && t <= POPPLER_FONT_TYPE_CID_TYPE2OT;
}

class PopplerFontsIterGetFontTypeTest_2224 : public ::testing::Test {
protected:
  void TearDown() override {
    if (!tmp_pdf_path_.empty()) {
      g_remove(tmp_pdf_path_.c_str());
      tmp_pdf_path_.clear();
    }
  }

  PopplerDocument *LoadDocFromGeneratedPdf() {
    const std::string pdf = BuildMinimalPdfWithType1Helvetica();
    tmp_pdf_path_ = WriteToTempPdfFile(pdf);
    const std::string uri = FilenameToUri(tmp_pdf_path_);

    ScopedGError err;
    PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, err.out_ptr());
    EXPECT_EQ(err.get(), nullptr);
    EXPECT_NE(doc, nullptr);
    return doc;
  }

private:
  std::string tmp_pdf_path_;
};

}  // namespace

TEST_F(PopplerFontsIterGetFontTypeTest_2224, NullIterReturnsUnknown_2224) {
  // Observable behavior from g_return_val_if_fail(iter != nullptr, POPPLER_FONT_TYPE_UNKNOWN)
  EXPECT_EQ(poppler_fonts_iter_get_font_type(nullptr), POPPLER_FONT_TYPE_UNKNOWN);
}

TEST_F(PopplerFontsIterGetFontTypeTest_2224, ScannedHelveticaType1ReportsType1_2224) {
  ScopedGObject doc(LoadDocFromGeneratedPdf());
  ASSERT_NE(doc.get(), nullptr);

  ScopedGObject font_info(poppler_font_info_new(doc.as<PopplerDocument>()));
  ASSERT_NE(font_info.get(), nullptr);

  PopplerFontsIter *iter = nullptr;
  const gboolean found = poppler_font_info_scan(font_info.as<PopplerFontInfo>(), /*n_pages=*/1, &iter);
  ASSERT_TRUE(found);
  ASSERT_NE(iter, nullptr);

  const PopplerFontType t = poppler_fonts_iter_get_font_type(iter);
  // We expect the generated PDF's Helvetica to be Type1.
  EXPECT_EQ(t, POPPLER_FONT_TYPE_TYPE1);

  poppler_fonts_iter_free(iter);
}

TEST_F(PopplerFontsIterGetFontTypeTest_2224, CopyIterPreservesFontType_2224) {
  ScopedGObject doc(LoadDocFromGeneratedPdf());
  ASSERT_NE(doc.get(), nullptr);

  ScopedGObject font_info(poppler_font_info_new(doc.as<PopplerDocument>()));
  ASSERT_NE(font_info.get(), nullptr);

  PopplerFontsIter *iter = nullptr;
  ASSERT_TRUE(poppler_font_info_scan(font_info.as<PopplerFontInfo>(), /*n_pages=*/1, &iter));
  ASSERT_NE(iter, nullptr);

  PopplerFontsIter *copy = poppler_fonts_iter_copy(iter);
  ASSERT_NE(copy, nullptr);

  const PopplerFontType t1 = poppler_fonts_iter_get_font_type(iter);
  const PopplerFontType t2 = poppler_fonts_iter_get_font_type(copy);
  EXPECT_EQ(t1, t2);

  poppler_fonts_iter_free(copy);
  poppler_fonts_iter_free(iter);
}

TEST_F(PopplerFontsIterGetFontTypeTest_2224, ScanWithZeroPagesDoesNotCrashAndTypeIsSaneIfPresent_2224) {
  ScopedGObject doc(LoadDocFromGeneratedPdf());
  ASSERT_NE(doc.get(), nullptr);

  ScopedGObject font_info(poppler_font_info_new(doc.as<PopplerDocument>()));
  ASSERT_NE(font_info.get(), nullptr);

  PopplerFontsIter *iter = nullptr;
  // Boundary condition: n_pages = 0.
  const gboolean found = poppler_font_info_scan(font_info.as<PopplerFontInfo>(), /*n_pages=*/0, &iter);

  // We don't assume whether it "finds" fonts with 0 pages; we only assert safe/observable outcomes.
  if (found && iter) {
    const PopplerFontType t = poppler_fonts_iter_get_font_type(iter);
    EXPECT_TRUE(IsValidPopplerFontTypeEnum(t));
    poppler_fonts_iter_free(iter);
  } else {
    EXPECT_TRUE(iter == nullptr);
  }
}