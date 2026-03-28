// File: poppler-font-info-new-test_2235.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

#include <cerrno>
#include <cstring>
#include <string>

namespace {

class GlibEnv_2235 : public ::testing::Environment {
public:
  void SetUp() override {
    // Ensure GLib/GObject type system is initialized.
    // This is safe to call multiple times across a test binary.
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }
};

::testing::Environment* const g_glib_env_2235 =
    ::testing::AddGlobalTestEnvironment(new GlibEnv_2235());

struct GErrorDeleter_2235 {
  void operator()(GError* e) const { g_error_free(e); }
};
using GErrorPtr_2235 = std::unique_ptr<GError, GErrorDeleter_2235>;

template <typename T>
struct GObjectDeleter_2235 {
  void operator()(T* obj) const {
    if (obj)
      g_object_unref(obj);
  }
};
template <typename T>
using GObjectPtr_2235 = std::unique_ptr<T, GObjectDeleter_2235<T>>;

// A tiny, valid PDF (1-page, blank) sufficient for poppler_document_new_from_file().
static const char kMinimalPdf_2235[] =
    "%PDF-1.4\n"
    "1 0 obj\n"
    "<< /Type /Catalog /Pages 2 0 R >>\n"
    "endobj\n"
    "2 0 obj\n"
    "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
    "endobj\n"
    "3 0 obj\n"
    "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 100 100] /Contents 4 0 R >>\n"
    "endobj\n"
    "4 0 obj\n"
    "<< /Length 0 >>\n"
    "stream\n"
    "endstream\n"
    "endobj\n"
    "xref\n"
    "0 5\n"
    "0000000000 65535 f \n"
    "0000000010 00000 n \n"
    "0000000060 00000 n \n"
    "0000000117 00000 n \n"
    "0000000211 00000 n \n"
    "trailer\n"
    "<< /Size 5 /Root 1 0 R >>\n"
    "startxref\n"
    "260\n"
    "%%EOF\n";

static std::string WriteTempPdfAndGetUri_2235() {
  gchar* tmpl = g_strdup("poppler-font-info-new-2235-XXXXXX.pdf");
  // Place in system temp dir with mkstemp (needs a writable path).
  gchar* tmpdir = g_strdup(g_get_tmp_dir());
  gchar* path = g_build_filename(tmpdir, tmpl, nullptr);
  g_free(tmpdir);
  g_free(tmpl);

  int fd = g_mkstemp(path);
  EXPECT_NE(fd, -1) << "g_mkstemp failed: " << std::strerror(errno);

  const gsize len = static_cast<gsize>(std::strlen(kMinimalPdf_2235));
  gssize written = write(fd, kMinimalPdf_2235, len);
  EXPECT_EQ(written, static_cast<gssize>(len));
  close(fd);

  GError* error = nullptr;
  gchar* uri = g_filename_to_uri(path, /*hostname=*/nullptr, &error);
  EXPECT_EQ(error, nullptr);
  std::string uri_str = uri ? uri : "";
  g_free(uri);
  g_free(path);
  return uri_str;
}

class PopplerFontInfoNewTest_2235 : public ::testing::Test {
protected:
  void SetUp() override {
    uri_ = WriteTempPdfAndGetUri_2235();

    GError* error = nullptr;
    PopplerDocument* doc =
        poppler_document_new_from_file(uri_.c_str(), /*password=*/nullptr, &error);
    ASSERT_EQ(error, nullptr);
    ASSERT_NE(doc, nullptr);

    document_.reset(doc);
  }

  void TearDown() override { document_.reset(); }

  std::string uri_;
  GObjectPtr_2235<PopplerDocument> document_;
};

}  // namespace

TEST_F(PopplerFontInfoNewTest_2235, ReturnsNonNullForValidDocument_2235) {
  PopplerFontInfo* font_info = poppler_font_info_new(document_.get());
  ASSERT_NE(font_info, nullptr);

  EXPECT_TRUE(POPPLER_IS_FONT_INFO(font_info));

  // Should be safe to unref immediately (no crashes, use-after-free).
  g_object_unref(font_info);
}

TEST_F(PopplerFontInfoNewTest_2235, ReturnsNullForNullDocument_2235) {
  // g_return_val_if_fail() typically logs a critical; verify it (observable behavior).
  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");

  PopplerFontInfo* font_info = poppler_font_info_new(nullptr);
  EXPECT_EQ(font_info, nullptr);

  g_test_assert_expected_messages();
}

TEST_F(PopplerFontInfoNewTest_2235, ReturnsNullForNonDocumentGObject_2235) {
  // Pass a valid GObject instance of the wrong type; should fail the type check
  // and return NULL without invoking undefined behavior.
  PopplerFontInfo* wrong_type_obj =
      (PopplerFontInfo*)g_object_new(POPPLER_TYPE_FONT_INFO, nullptr);
  ASSERT_NE(wrong_type_obj, nullptr);
  ASSERT_TRUE(POPPLER_IS_FONT_INFO(wrong_type_obj));

  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");

  PopplerFontInfo* font_info =
      poppler_font_info_new(reinterpret_cast<PopplerDocument*>(wrong_type_obj));
  EXPECT_EQ(font_info, nullptr);

  g_test_assert_expected_messages();
  g_object_unref(wrong_type_obj);
}

TEST_F(PopplerFontInfoNewTest_2235, MultipleCallsProduceDistinctInstances_2235) {
  PopplerFontInfo* a = poppler_font_info_new(document_.get());
  PopplerFontInfo* b = poppler_font_info_new(document_.get());
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  EXPECT_TRUE(POPPLER_IS_FONT_INFO(a));
  EXPECT_TRUE(POPPLER_IS_FONT_INFO(b));
  EXPECT_NE(a, b);  // Two separate objects should be returned.

  g_object_unref(a);
  g_object_unref(b);
}