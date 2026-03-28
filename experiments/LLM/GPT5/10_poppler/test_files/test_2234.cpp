// File: poppler-font-info-finalize-test_2234.cc
//
// Unit tests for poppler_font_info_finalize() via observable GObject lifetime behavior.
//
// NOTE:
// - We do NOT call poppler_font_info_finalize() directly (it is static in poppler-document.cc).
// - We verify behavior only through public/observable effects: reference ownership and object finalization.
// - We avoid touching private/internal state of PopplerFontInfo/PopplerDocument.

#include <gtest/gtest.h>

#include <glib-object.h>
#include <glib.h>

#include <poppler.h>

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace {

struct TempPdfFile {
  std::string path;
  std::string uri;
};

static std::string Pad10(gsize off) {
  char buf[32];
  std::snprintf(buf, sizeof(buf), "%010" G_GSIZE_FORMAT, off);
  return std::string(buf);
}

// Build a minimal, valid single-page PDF to avoid relying on external test data files.
// This is test scaffolding, not re-implementing any Poppler logic.
static TempPdfFile CreateMinimalPdfFile() {
  gchar* tmp_path_c = nullptr;
  gint fd = g_file_open_tmp("poppler_gtest_2234_XXXXXX.pdf", &tmp_path_c, nullptr);
  EXPECT_GE(fd, 0);
  EXPECT_NE(tmp_path_c, nullptr);

  TempPdfFile out;
  out.path = tmp_path_c;
  g_free(tmp_path_c);

  // Build PDF bytes in-memory with a correct xref.
  std::string pdf;
  pdf.reserve(2048);

  auto append = [&](const std::string& s) { pdf.append(s); };
  auto append_ln = [&](const std::string& s) { pdf.append(s).append("\n"); };

  // Header
  append_ln("%PDF-1.4");
  // A binary comment line is common but optional; keep ASCII-only for simplicity.
  append_ln("%\x25\x25\x25\x25");  // "%%%%"

  // Track offsets for objects 0..4 (0 is the free object).
  std::vector<gsize> obj_off(5, 0);

  // Object 1: Catalog
  obj_off[1] = pdf.size();
  append_ln("1 0 obj");
  append_ln("<< /Type /Catalog /Pages 2 0 R >>");
  append_ln("endobj");

  // Object 2: Pages
  obj_off[2] = pdf.size();
  append_ln("2 0 obj");
  append_ln("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
  append_ln("endobj");

  // Object 3: Page (no resources needed for empty content stream)
  obj_off[3] = pdf.size();
  append_ln("3 0 obj");
  append_ln("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>");
  append_ln("endobj");

  // Object 4: Empty contents stream
  obj_off[4] = pdf.size();
  append_ln("4 0 obj");
  append_ln("<< /Length 0 >>");
  append_ln("stream");
  append_ln("");
  append_ln("endstream");
  append_ln("endobj");

  // XRef
  const gsize xref_off = pdf.size();
  append_ln("xref");
  append_ln("0 5");
  append_ln("0000000000 65535 f ");

  for (int i = 1; i <= 4; ++i) {
    // Each xref entry: 10-digit offset, 5-digit generation, n/f, space, newline.
    append_ln(Pad10(obj_off[i]) + " 00000 n ");
  }

  // Trailer
  append_ln("trailer");
  append_ln("<< /Size 5 /Root 1 0 R >>");
  append_ln("startxref");
  append_ln(std::to_string(static_cast<unsigned long long>(xref_off)));
  append_ln("%%EOF");

  // Write to temp file
  const gssize written = ::write(fd, pdf.data(), static_cast<gsize>(pdf.size()));
  EXPECT_EQ(written, static_cast<gssize>(pdf.size()));
  ::close(fd);

  // Build file:// URI
  gchar* uri_c = g_filename_to_uri(out.path.c_str(), nullptr, nullptr);
  EXPECT_NE(uri_c, nullptr);
  out.uri = uri_c;
  g_free(uri_c);

  return out;
}

static void WeakNotifyFlag(gpointer data, GObject* /*where_the_object_was*/) {
  auto* flag = static_cast<bool*>(data);
  *flag = true;
}

class PopplerFontInfoFinalizeTest_2234 : public ::testing::Test {
protected:
  void TearDown() override {
    // Ensure any temp file is removed.
    if (!tmp_.path.empty()) {
      (void)g_remove(tmp_.path.c_str());
      tmp_.path.clear();
      tmp_.uri.clear();
    }
  }

  TempPdfFile tmp_;
};

TEST_F(PopplerFontInfoFinalizeTest_2234, DocumentRefHeldUntilFontInfoFinalized_2234) {
  tmp_ = CreateMinimalPdfFile();

  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(tmp_.uri.c_str(), /*password=*/nullptr, &error);
  ASSERT_NE(doc, nullptr);
  ASSERT_EQ(error, nullptr);

  // Observe when the document is finalized.
  bool doc_finalized = false;
  g_object_weak_ref(G_OBJECT(doc), WeakNotifyFlag, &doc_finalized);

  // Create PopplerFontInfo; it should hold a reference to the document (observable by lifetime).
  PopplerFontInfo* fi = poppler_font_info_new(doc);
  ASSERT_NE(fi, nullptr);

  // Drop our explicit reference to doc; doc should still be alive because fi holds it.
  g_object_unref(doc);
  EXPECT_FALSE(doc_finalized);

  // Releasing font info should release its ref to doc; doc should now be finalized.
  g_object_unref(fi);
  EXPECT_TRUE(doc_finalized);
}

TEST_F(PopplerFontInfoFinalizeTest_2234, ExtraDocumentRefKeepsAliveAfterFontInfoFinalized_2234) {
  tmp_ = CreateMinimalPdfFile();

  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(tmp_.uri.c_str(), /*password=*/nullptr, &error);
  ASSERT_NE(doc, nullptr);
  ASSERT_EQ(error, nullptr);

  bool doc_finalized = false;
  g_object_weak_ref(G_OBJECT(doc), WeakNotifyFlag, &doc_finalized);

  // Hold an extra ref we control.
  g_object_ref(doc);

  PopplerFontInfo* fi = poppler_font_info_new(doc);
  ASSERT_NE(fi, nullptr);

  // Drop the "original" ref. doc should remain alive due to (a) our extra ref and (b) fi's ref.
  g_object_unref(doc);
  EXPECT_FALSE(doc_finalized);

  // Drop font info; doc should still be alive because of our extra ref.
  g_object_unref(fi);
  EXPECT_FALSE(doc_finalized);

  // Now drop our extra ref; doc should finalize.
  g_object_unref(doc);
  EXPECT_TRUE(doc_finalized);
}

TEST_F(PopplerFontInfoFinalizeTest_2234, NewWithNullDocumentReturnsNullOrSafeObject_2234) {
  // Public API should handle null input safely (commonly returns NULL via g_return_val_if_fail).
  // We accept either:
  //  - returns NULL, or
  //  - returns a non-NULL object that can be unref'd safely.
  PopplerFontInfo* fi = poppler_font_info_new(nullptr);

  if (fi == nullptr) {
    SUCCEED();
    return;
  }

  // If it returns a valid object, it must be safe to release.
  g_object_unref(fi);
  SUCCEED();
}

}  // namespace