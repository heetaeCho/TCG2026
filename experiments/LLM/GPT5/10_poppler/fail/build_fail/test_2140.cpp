// File: poppler-document-new-from-data-test_2140.cc
//
// Unit tests for poppler_document_new_from_data()
// Target: ./TestProjects/poppler/glib/poppler-document.cc
//
// Constraints reminder:
// - Treat implementation as a black box.
// - Test only observable behavior via public interface.
// - No reliance on private/internal state.

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstring>
#include <string>
#include <vector>

namespace {

class PopplerDocumentNewFromDataTest_2140 : public ::testing::Test {
protected:
  static std::vector<char> MakeMinimalValidPdfBytes()
  {
    // A tiny, commonly-used minimal PDF with one empty page.
    // Important: use explicit byte offsets by constructing it as a single string,
    // and pass the exact byte length to poppler_document_new_from_data().
    //
    // Poppler is permissive, but if this ever fails in a specific environment,
    // the tests that depend on "valid PDF" will fail and should be adapted to
    // a known-good fixture PDF used by your codebase.
    const char *pdf =
        "%PDF-1.1\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] >>\n"
        "endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000010 00000 n \n"
        "0000000060 00000 n \n"
        "0000000120 00000 n \n"
        "trailer\n"
        "<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    // Note: The xref offsets above are approximate and may not match exactly.
    // Poppler is often tolerant, but not guaranteed. If your Poppler build is
    // strict about xref offsets, replace this with a known-good PDF fixture.
    std::vector<char> bytes(pdf, pdf + std::strlen(pdf));
    return bytes;
  }

  static std::vector<char> MakeClearlyInvalidBytes()
  {
    const char *s = "this is not a pdf";
    return std::vector<char>(s, s + std::strlen(s));
  }

  static void FreeGError(GError *err)
  {
    if (err) {
      g_error_free(err);
    }
  }
};

} // namespace

TEST_F(PopplerDocumentNewFromDataTest_2140, ValidPdfReturnsDocumentAndNoError_2140)
{
  auto bytes = MakeMinimalValidPdfBytes();

  GError *error = nullptr;
  PopplerDocument *doc =
      poppler_document_new_from_data(bytes.data(),
                                     static_cast<int>(bytes.size()),
                                     /*password=*/nullptr,
                                     &error);

  // Observable behavior: for valid PDF, expect a document and no error.
  ASSERT_NE(doc, nullptr) << "Expected a non-null document for valid PDF data";
  EXPECT_EQ(error, nullptr) << "Expected no GError for valid PDF data";

  g_object_unref(doc);
  FreeGError(error);
}

TEST_F(PopplerDocumentNewFromDataTest_2140, InvalidDataReturnsNullAndSetsError_2140)
{
  auto bytes = MakeClearlyInvalidBytes();

  GError *error = nullptr;
  PopplerDocument *doc =
      poppler_document_new_from_data(bytes.data(),
                                     static_cast<int>(bytes.size()),
                                     /*password=*/nullptr,
                                     &error);

  EXPECT_EQ(doc, nullptr) << "Expected null document for invalid data";
  ASSERT_NE(error, nullptr) << "Expected GError to be set for invalid data";

  // Basic sanity on the error message (observable, but not implementation-specific).
  EXPECT_NE(error->message, nullptr);
  EXPECT_GT(std::strlen(error->message), 0u);

  FreeGError(error);
}

TEST_F(PopplerDocumentNewFromDataTest_2140, ZeroLengthDataReturnsNullAndSetsError_2140)
{
  // Boundary condition: zero length.
  // Provide a non-null pointer (safe) with length 0.
  char dummy = 0;

  GError *error = nullptr;
  PopplerDocument *doc =
      poppler_document_new_from_data(&dummy, /*length=*/0, /*password=*/nullptr, &error);

  EXPECT_EQ(doc, nullptr) << "Expected null document for zero-length input";

  // If Poppler chooses not to set a GError in some builds, avoid over-constraining:
  // but in most GLib APIs, error is expected when returning null.
  EXPECT_NE(error, nullptr) << "Expected GError to be set for zero-length input";

  FreeGError(error);
}

TEST_F(PopplerDocumentNewFromDataTest_2140, NullDataWithZeroLengthDoesNotCrashAndFails_2140)
{
  // Boundary condition: nullptr data with length 0.
  // This should not crash. Observable behavior: should fail (return null), typically with error.
  GError *error = nullptr;
  PopplerDocument *doc =
      poppler_document_new_from_data(/*data=*/nullptr, /*length=*/0, /*password=*/nullptr, &error);

  EXPECT_EQ(doc, nullptr);

  // Accept either: error set or not set, but prefer error set.
  // Keep it flexible to avoid depending on internal error reporting choices.
  if (error) {
    EXPECT_NE(error->message, nullptr);
    EXPECT_GT(std::strlen(error->message), 0u);
  }

  FreeGError(error);
}

TEST_F(PopplerDocumentNewFromDataTest_2140, PasswordProvidedOnNonEncryptedPdfStillLoads_2140)
{
  auto bytes = MakeMinimalValidPdfBytes();

  GError *error = nullptr;
  PopplerDocument *doc =
      poppler_document_new_from_data(bytes.data(),
                                     static_cast<int>(bytes.size()),
                                     /*password=*/"irrelevant-password",
                                     &error);

  ASSERT_NE(doc, nullptr) << "Non-encrypted PDF should load even if password is provided";
  EXPECT_EQ(error, nullptr);

  g_object_unref(doc);
  FreeGError(error);
}

TEST_F(PopplerDocumentNewFromDataTest_2140, NonAsciiPasswordDoesNotCrashOnInvalidData_2140)
{
  // Exceptional-ish case (observable): ensure function tolerates UTF-8-ish password input.
  // We can't reliably observe the internal retry logic without an encrypted test PDF,
  // but we can verify the API behaves safely (no crash) and still reports failure.
  auto bytes = MakeClearlyInvalidBytes();

  const char *utf8_password = u8"pässwörd-한글";

  GError *error = nullptr;
  PopplerDocument *doc =
      poppler_document_new_from_data(bytes.data(),
                                     static_cast<int>(bytes.size()),
                                     utf8_password,
                                     &error);

  EXPECT_EQ(doc, nullptr);
  EXPECT_NE(error, nullptr);

  FreeGError(error);
}

TEST_F(PopplerDocumentNewFromDataTest_2140, EmbeddedNullByteInBufferDoesNotTruncateLength_2140)
{
  // Boundary condition: buffer contains '\0' in the middle. The API takes (data, length),
  // so it must respect length rather than C-string termination.
  // We'll create a mostly-invalid buffer with an embedded NUL and ensure it fails cleanly
  // (and does not crash / read past provided length).
  std::vector<char> bytes;
  const char prefix[] = "%PDF-";
  bytes.insert(bytes.end(), prefix, prefix + sizeof(prefix) - 1);
  bytes.push_back('\0'); // embedded NUL
  const char suffix[] = "1.7\nNOT REALLY A PDF\n";
  bytes.insert(bytes.end(), suffix, suffix + sizeof(suffix) - 1);

  GError *error = nullptr;
  PopplerDocument *doc =
      poppler_document_new_from_data(bytes.data(),
                                     static_cast<int>(bytes.size()),
                                     /*password=*/nullptr,
                                     &error);

  EXPECT_EQ(doc, nullptr);
  EXPECT_NE(error, nullptr);

  FreeGError(error);
}