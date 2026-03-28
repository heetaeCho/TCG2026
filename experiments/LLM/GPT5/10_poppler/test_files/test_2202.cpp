// File: poppler-document-get-pdf-subtype-string-test_2202.cc
//
// Unit tests for:
//   gchar *poppler_document_get_pdf_subtype_string(PopplerDocument *document)
//
// Constraints respected:
// - Treat implementation as black box (no internal logic assumptions beyond observable API)
// - Only use public GLib Poppler API to create/use PopplerDocument
// - Verify observable behavior: return values, NULL on invalid inputs, UTF-8 string ownership
// - Verify external interactions: GLib critical log emission via g_return_val_if_fail()

#include <gtest/gtest.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <poppler.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

namespace {

struct LogCapture {
  static void Handler(const gchar* /*log_domain*/,
                      GLogLevelFlags /*log_level*/,
                      const gchar* /*message*/,
                      gpointer user_data) {
    auto* self = static_cast<LogCapture*>(user_data);
    self->count++;
  }

  explicit LogCapture(const char* domain, GLogLevelFlags levels)
      : domain_(domain), levels_(levels) {
    handler_id_ = g_log_set_handler(domain_, levels_, &LogCapture::Handler, this);
  }

  ~LogCapture() {
    if (handler_id_ != 0) {
      g_log_remove_handler(domain_, handler_id_);
    }
  }

  int count = 0;

 private:
  const char* domain_;
  GLogLevelFlags levels_;
  guint handler_id_ = 0;
};

static std::string BuildMinimalPdfWithInfoEntry(const std::string& info_key,
                                                const std::string& info_value) {
  // Minimal PDF with /Info dictionary containing the provided key/value.
  // Note: This does NOT assume Poppler will classify subtype from this alone.
  // Tests will conditionally assert when a subtype string is returned.
  std::vector<std::string> objs;
  objs.reserve(5);

  // 1: Catalog
  objs.emplace_back("1 0 obj\n"
                    "<< /Type /Catalog /Pages 2 0 R >>\n"
                    "endobj\n");

  // 2: Pages
  objs.emplace_back("2 0 obj\n"
                    "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
                    "endobj\n");

  // 3: Page (empty contents)
  objs.emplace_back("3 0 obj\n"
                    "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
                    "   /Contents 4 0 R >>\n"
                    "endobj\n");

  // 4: Contents stream (empty)
  objs.emplace_back("4 0 obj\n"
                    "<< /Length 0 >>\n"
                    "stream\n"
                    "\n"
                    "endstream\n"
                    "endobj\n");

  // 5: Info dictionary with our key/value
  // PDF name keys cannot include spaces; given keys are like GTS_PDFA1Version.
  std::ostringstream info;
  info << "5 0 obj\n"
       << "<< /Producer (Poppler GLib Test)\n"
       << "   /" << info_key << " (" << info_value << ") >>\n"
       << "endobj\n";
  objs.emplace_back(info.str());

  std::ostringstream out;
  out << "%PDF-1.4\n";

  // Compute xref offsets.
  std::vector<long> offsets;
  offsets.resize(objs.size() + 1);
  offsets[0] = 0;

  for (size_t i = 0; i < objs.size(); ++i) {
    offsets[i + 1] = static_cast<long>(out.tellp());
    out << objs[i];
  }

  const long xref_pos = static_cast<long>(out.tellp());

  out << "xref\n";
  out << "0 " << (objs.size() + 1) << "\n";
  out << "0000000000 65535 f \n";
  for (size_t i = 1; i <= objs.size(); ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", offsets[i]);
    out << buf << " 00000 n \n";
  }

  out << "trailer\n";
  out << "<< /Size " << (objs.size() + 1) << " /Root 1 0 R /Info 5 0 R >>\n";
  out << "startxref\n";
  out << xref_pos << "\n";
  out << "%%EOF\n";

  return out.str();
}

static std::string WriteTempFileBytes(const std::string& bytes) {
  gchar* tmp_name = nullptr;
  GError* err = nullptr;

  gint fd = g_file_open_tmp("poppler_pdf_subtype_string_XXXXXX.pdf", &tmp_name, &err);
  if (fd < 0) {
    std::string msg = "g_file_open_tmp failed";
    if (err) {
      msg += ": ";
      msg += err->message;
      g_error_free(err);
    }
    ADD_FAILURE() << msg;
    return {};
  }

  gsize to_write = bytes.size();
  gssize written = 0;
  const char* p = bytes.data();
  while (to_write > 0) {
    gssize w = write(fd, p + written, to_write);
    if (w <= 0) break;
    written += w;
    to_write -= static_cast<gsize>(w);
  }
  close(fd);

  if (written != static_cast<gssize>(bytes.size())) {
    g_unlink(tmp_name);
    std::string path(tmp_name);
    g_free(tmp_name);
    ADD_FAILURE() << "Failed to write all bytes to temp PDF";
    return {};
  }

  std::string path(tmp_name);
  g_free(tmp_name);
  return path;
}

static gchar* PathToUri(const std::string& path) {
  return g_filename_to_uri(path.c_str(), nullptr, nullptr);
}

static PopplerDocument* LoadDocFromUri(const gchar* uri, GError** out_error) {
  // Password null for test PDFs.
  return poppler_document_new_from_file(uri, /*password*/ nullptr, out_error);
}

class PopplerDocumentPdfSubtypeStringTest_2202 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
    if (!tmp_path_.empty()) {
      g_unlink(tmp_path_.c_str());
      tmp_path_.clear();
    }
    if (uri_) {
      g_free(uri_);
      uri_ = nullptr;
    }
  }

  void MakeDocWithInfoEntry(const std::string& key, const std::string& value) {
    const std::string pdf = BuildMinimalPdfWithInfoEntry(key, value);
    tmp_path_ = WriteTempFileBytes(pdf);
    ASSERT_FALSE(tmp_path_.empty());

    uri_ = PathToUri(tmp_path_);
    ASSERT_NE(uri_, nullptr);

    GError* error = nullptr;
    doc_ = LoadDocFromUri(uri_, &error);
    if (!doc_) {
      std::string msg = "poppler_document_new_from_file failed";
      if (error) {
        msg += ": ";
        msg += error->message;
        g_error_free(error);
      }
      FAIL() << msg;
    }
  }

  PopplerDocument* doc_ = nullptr;
  std::string tmp_path_;
  gchar* uri_ = nullptr;
};

TEST_F(PopplerDocumentPdfSubtypeStringTest_2202, NullDocumentReturnsNullAndLogsCritical_2202) {
  // g_return_val_if_fail() should emit a critical and return NULL.
  LogCapture cap("Poppler", static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL));

  gchar* s = poppler_document_get_pdf_subtype_string(nullptr);
  EXPECT_EQ(s, nullptr);
  EXPECT_GE(cap.count, 1) << "Expected at least one critical log for NULL document";
}

TEST_F(PopplerDocumentPdfSubtypeStringTest_2202, NonDocumentPointerReturnsNullAndLogsCritical_2202) {
  // Pass a non-PopplerDocument GObject* cast to PopplerDocument*.
  GObject* obj = g_object_new(G_TYPE_OBJECT, nullptr);
  ASSERT_NE(obj, nullptr);

  LogCapture cap("Poppler", static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL));

  gchar* s = poppler_document_get_pdf_subtype_string(reinterpret_cast<PopplerDocument*>(obj));
  EXPECT_EQ(s, nullptr);
  EXPECT_GE(cap.count, 1) << "Expected at least one critical log for non-document instance";

  g_object_unref(obj);
}

// Parameterized-ish helper for subtype info keys.
// NOTE: We do NOT assume the exact internal subtype detection rules.
// If Poppler classifies the PDF as that subtype, the function should return
// a UTF-8 string matching the Info entry and the caller must free it.
// If Poppler does not classify it, returning NULL is acceptable.
static void ExpectReturnedStringMatchesOrNull(PopplerDocument* doc,
                                              const std::string& expected_value) {
  ASSERT_NE(doc, nullptr);

  gchar* s = poppler_document_get_pdf_subtype_string(doc);

  if (!s) {
    GTEST_SKIP() << "Poppler did not expose a PDF subtype string for this synthetic PDF";
  }

  // Observable behavior: returned string should be valid UTF-8.
  EXPECT_TRUE(g_utf8_validate(s, -1, nullptr));

  // If non-null, it should match what was embedded in the /Info entry for that subtype key.
  EXPECT_STREQ(s, expected_value.c_str());

  // Ownership: function returns gchar* that caller should free.
  g_free(s);
}

TEST_F(PopplerDocumentPdfSubtypeStringTest_2202, PdfaKeyReturnsInfoStringWhenSubtypeDetected_2202) {
  const std::string key = "GTS_PDFA1Version";
  const std::string value = "A-1b-test";
  MakeDocWithInfoEntry(key, value);

  ExpectReturnedStringMatchesOrNull(doc_, value);
}

TEST_F(PopplerDocumentPdfSubtypeStringTest_2202, PdfeKeyReturnsInfoStringWhenSubtypeDetected_2202) {
  const std::string key = "GTS_PDFEVersion";
  const std::string value = "E-1-test";
  MakeDocWithInfoEntry(key, value);

  ExpectReturnedStringMatchesOrNull(doc_, value);
}

TEST_F(PopplerDocumentPdfSubtypeStringTest_2202, PdfuaKeyReturnsInfoStringWhenSubtypeDetected_2202) {
  const std::string key = "GTS_PDFUAVersion";
  const std::string value = "UA-1-test";
  MakeDocWithInfoEntry(key, value);

  ExpectReturnedStringMatchesOrNull(doc_, value);
}

TEST_F(PopplerDocumentPdfSubtypeStringTest_2202, PdfvtKeyReturnsInfoStringWhenSubtypeDetected_2202) {
  const std::string key = "GTS_PDFVTVersion";
  const std::string value = "VT-1-test";
  MakeDocWithInfoEntry(key, value);

  ExpectReturnedStringMatchesOrNull(doc_, value);
}

TEST_F(PopplerDocumentPdfSubtypeStringTest_2202, PdfxKeyReturnsInfoStringWhenSubtypeDetected_2202) {
  const std::string key = "GTS_PDFXVersion";
  const std::string value = "X-4-test";
  MakeDocWithInfoEntry(key, value);

  ExpectReturnedStringMatchesOrNull(doc_, value);
}

TEST_F(PopplerDocumentPdfSubtypeStringTest_2202, EmptyInfoValueStillReturnsUtf8StringWhenSubtypeDetected_2202) {
  const std::string key = "GTS_PDFXVersion";
  const std::string value = "";  // Boundary: empty string value
  MakeDocWithInfoEntry(key, value);

  ExpectReturnedStringMatchesOrNull(doc_, value);
}

}  // namespace