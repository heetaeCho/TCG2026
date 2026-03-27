// poppler-document-get-id-test-2150.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstring>
#include <string>
#include <vector>

// Build a tiny valid PDF (with xref offsets) and a trailer /ID entry.
// permanent_id_hex32 and update_id_hex32 must be exactly 32 hex characters each.
static std::string BuildPdfWithId32(const std::string &permanent_id_hex32,
                                   const std::string &update_id_hex32) {
  // Minimal 1-page PDF with a simple content stream.
  // Objects:
  // 1 0 obj: Catalog
  // 2 0 obj: Pages
  // 3 0 obj: Page
  // 4 0 obj: Contents stream
  std::string pdf;
  pdf.reserve(2048);

  auto append = [&](const std::string &s) { pdf += s; };

  append("%PDF-1.4\n");
  append("%\xE2\xE3\xCF\xD3\n"); // binary comment

  // Record offsets for xref: entry 0 is free; entries 1..4 are objects.
  std::vector<size_t> offsets(5, 0);

  offsets[1] = pdf.size();
  append("1 0 obj\n"
         "<< /Type /Catalog /Pages 2 0 R >>\n"
         "endobj\n");

  offsets[2] = pdf.size();
  append("2 0 obj\n"
         "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
         "endobj\n");

  offsets[3] = pdf.size();
  append("3 0 obj\n"
         "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
         "   /Contents 4 0 R >>\n"
         "endobj\n");

  const char *stream_payload = "BT /F1 12 Tf 72 100 Td (Hello) Tj ET\n";
  const int stream_len = static_cast<int>(std::strlen(stream_payload));

  offsets[4] = pdf.size();
  append("4 0 obj\n");
  append("<< /Length " + std::to_string(stream_len) + " >>\n");
  append("stream\n");
  append(stream_payload);
  append("endstream\n");
  append("endobj\n");

  const size_t xref_offset = pdf.size();
  append("xref\n");
  append("0 5\n");
  // object 0: free
  append("0000000000 65535 f \n");

  auto xref_line = [&](size_t off) {
    char buf[64];
    // 10-digit, zero-padded offset, generation 00000, in-use 'n'
    std::snprintf(buf, sizeof(buf), "%010lu 00000 n \n",
                  static_cast<unsigned long>(off));
    append(buf);
  };

  xref_line(offsets[1]);
  xref_line(offsets[2]);
  xref_line(offsets[3]);
  xref_line(offsets[4]);

  append("trailer\n");
  append("<< /Size 5 /Root 1 0 R ");
  append("/ID [<" + permanent_id_hex32 + "><" + update_id_hex32 + ">] ");
  append(">>\n");
  append("startxref\n");
  append(std::to_string(static_cast<unsigned long>(xref_offset)));
  append("\n%%EOF\n");

  return pdf;
}

static PopplerDocument *LoadDocFromDataOrFail_2150(const std::string &pdf_data) {
  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_data(
      pdf_data.data(), static_cast<int>(pdf_data.size()), /*password=*/nullptr,
      &error);
  if (!doc) {
    std::string msg = "Failed to create PopplerDocument from in-memory PDF.";
    if (error && error->message) {
      msg += " GError: ";
      msg += error->message;
    }
    if (error) {
      g_error_free(error);
    }
    ADD_FAILURE() << msg;
  }
  if (error) {
    // Some builds might still set an informational error; be strict and free it.
    g_error_free(error);
  }
  return doc;
}

class PopplerDocumentGetIdTest_2150 : public ::testing::Test {
protected:
  void TearDown() override {
    // Nothing global to tear down.
  }
};

TEST_F(PopplerDocumentGetIdTest_2150, ReturnsTrueAndFillsBothIdsWhenPresent_2150) {
  const std::string perm = "0123456789abcdef0123456789abcdef";
  const std::string upd  = "fedcba9876543210fedcba9876543210";
  ASSERT_EQ(perm.size(), 32u);
  ASSERT_EQ(upd.size(), 32u);

  const std::string pdf = BuildPdfWithId32(perm, upd);
  PopplerDocument *doc = LoadDocFromDataOrFail_2150(pdf);
  ASSERT_NE(doc, nullptr);

  gchar *permanent_id = nullptr;
  gchar *update_id = nullptr;

  const gboolean ok = poppler_document_get_id(doc, &permanent_id, &update_id);

  EXPECT_TRUE(ok);
  ASSERT_NE(permanent_id, nullptr);
  ASSERT_NE(update_id, nullptr);

  // The API copies 32 bytes; do not assume NUL termination.
  EXPECT_EQ(0, std::memcmp(permanent_id, perm.data(), 32));
  EXPECT_EQ(0, std::memcmp(update_id, upd.data(), 32));

  g_free(permanent_id);
  g_free(update_id);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetIdTest_2150, ReturnsTrueWhenOnlyPermanentOutParamProvided_2150) {
  const std::string perm = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  const std::string upd  = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
  const std::string pdf = BuildPdfWithId32(perm, upd);
  PopplerDocument *doc = LoadDocFromDataOrFail_2150(pdf);
  ASSERT_NE(doc, nullptr);

  gchar *permanent_id = nullptr;

  const gboolean ok = poppler_document_get_id(doc, &permanent_id, nullptr);

  EXPECT_TRUE(ok);
  ASSERT_NE(permanent_id, nullptr);
  EXPECT_EQ(0, std::memcmp(permanent_id, perm.data(), 32));

  g_free(permanent_id);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetIdTest_2150, ReturnsTrueWhenOnlyUpdateOutParamProvided_2150) {
  const std::string perm = "cccccccccccccccccccccccccccccccc";
  const std::string upd  = "dddddddddddddddddddddddddddddddd";
  const std::string pdf = BuildPdfWithId32(perm, upd);
  PopplerDocument *doc = LoadDocFromDataOrFail_2150(pdf);
  ASSERT_NE(doc, nullptr);

  gchar *update_id = nullptr;

  const gboolean ok = poppler_document_get_id(doc, nullptr, &update_id);

  EXPECT_TRUE(ok);
  ASSERT_NE(update_id, nullptr);
  EXPECT_EQ(0, std::memcmp(update_id, upd.data(), 32));

  g_free(update_id);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetIdTest_2150, ReturnsTrueWhenNoOutParamsProvided_2150) {
  const std::string perm = "11111111111111111111111111111111";
  const std::string upd  = "22222222222222222222222222222222";
  const std::string pdf = BuildPdfWithId32(perm, upd);
  PopplerDocument *doc = LoadDocFromDataOrFail_2150(pdf);
  ASSERT_NE(doc, nullptr);

  const gboolean ok = poppler_document_get_id(doc, nullptr, nullptr);

  // Observable behavior: should not crash and should return success when ID exists.
  EXPECT_TRUE(ok);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetIdTest_2150, NullDocumentReturnsFalse_2150) {
  // Error/exceptional case observable through return value.
  const gboolean ok = poppler_document_get_id(nullptr, nullptr, nullptr);
  EXPECT_FALSE(ok);
}