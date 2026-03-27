// File: poppler-document-new-from-bytes-test_2141.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace {

class PopplerDocumentNewFromBytesTest_2141 : public ::testing::Test {
protected:
  static std::string BuildMinimalPdf_2141() {
    // Build a minimal, valid PDF with a correct xref table.
    // This is test input generation (not re-implementing Poppler logic).
    struct Obj_2141 {
      int num;
      std::string body;
    };

    std::vector<Obj_2141> objs;
    objs.push_back({1, "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"});
    objs.push_back({2, "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"});
    objs.push_back({3,
                    "3 0 obj\n"
                    "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
                    "   /Contents 4 0 R /Resources << >> >>\n"
                    "endobj\n"});

    const std::string streamData =
        "BT\n"
        "1 0 0 1 72 120 Tm\n"
        "(Hello) Tj\n"
        "ET\n";
    const std::string obj4 =
        "4 0 obj\n"
        "<< /Length " +
        std::to_string(streamData.size()) +
        " >>\n"
        "stream\n" +
        streamData +
        "endstream\n"
        "endobj\n";
    objs.push_back({4, obj4});

    std::string pdf;
    pdf += "%PDF-1.4\n";
    // binary marker line (commonly used; harmless)
    pdf += "%\xE2\xE3\xCF\xD3\n";

    // Offsets: xref needs byte offsets from beginning of file.
    // xref includes object 0 as the free head entry.
    std::vector<std::size_t> offsets(5, 0);
    for (const auto &o : objs) {
      offsets[o.num] = pdf.size();
      pdf += o.body;
    }

    const std::size_t xrefPos = pdf.size();
    pdf += "xref\n";
    pdf += "0 5\n";
    pdf += "0000000000 65535 f \n";

    auto fmt10 = [](std::size_t v) -> std::string {
      std::string s = std::to_string(v);
      if (s.size() < 10) s = std::string(10 - s.size(), '0') + s;
      return s;
    };
    for (int i = 1; i <= 4; ++i) {
      pdf += fmt10(offsets[i]) + " 00000 n \n";
    }

    pdf += "trailer\n";
    pdf += "<< /Size 5 /Root 1 0 R >>\n";
    pdf += "startxref\n";
    pdf += std::to_string(xrefPos) + "\n";
    pdf += "%%EOF\n";
    return pdf;
  }

  static GBytes *MakeBytesFromString_2141(const std::string &s) {
    // g_bytes_new copies the data; safe for temporary buffers.
    return g_bytes_new(s.data(), s.size());
  }
};

TEST_F(PopplerDocumentNewFromBytesTest_2141, NullBytesReturnsNull_2141) {
  // Precondition: bytes must not be nullptr.
  PopplerDocument *doc = poppler_document_new_from_bytes(nullptr, nullptr, nullptr);
  EXPECT_EQ(doc, nullptr);
}

TEST_F(PopplerDocumentNewFromBytesTest_2141, NonNullErrorWithPreexistingGErrorReturnsNull_2141) {
  // Precondition: error == nullptr OR *error == nullptr.
  GError *existing = g_error_new_literal(g_quark_from_static_string("test-domain-2141"),
                                        2141,
                                        "preexisting");
  ASSERT_NE(existing, nullptr);

  const std::string pdf = BuildMinimalPdf_2141();
  GBytes *bytes = MakeBytesFromString_2141(pdf);
  ASSERT_NE(bytes, nullptr);

  PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &existing);
  EXPECT_EQ(doc, nullptr);

  // The guard returns early; the original error should still be set.
  EXPECT_NE(existing, nullptr);

  g_clear_error(&existing);
  g_bytes_unref(bytes);
}

TEST_F(PopplerDocumentNewFromBytesTest_2141, ValidPdfBytesWithNullErrorPointerSucceedsOrReturnsNonNull_2141) {
  const std::string pdf = BuildMinimalPdf_2141();
  GBytes *bytes = MakeBytesFromString_2141(pdf);
  ASSERT_NE(bytes, nullptr);

  // error == nullptr is allowed by the interface.
  PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, nullptr);

  // For a well-formed minimal PDF, PopplerDocument is expected to be created.
  // If build/configuration differences cause failure, the observable contract
  // is simply that it returns either a valid doc or nullptr (no crash).
  EXPECT_NE(doc, nullptr);

  if (doc) {
    g_object_unref(doc);
  }
  g_bytes_unref(bytes);
}

TEST_F(PopplerDocumentNewFromBytesTest_2141, ValidPdfBytesKeepsErrorNullOnSuccess_2141) {
  const std::string pdf = BuildMinimalPdf_2141();
  GBytes *bytes = MakeBytesFromString_2141(pdf);
  ASSERT_NE(bytes, nullptr);

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);

  ASSERT_NE(doc, nullptr);
  EXPECT_EQ(error, nullptr);

  g_object_unref(doc);
  g_bytes_unref(bytes);
}

TEST_F(PopplerDocumentNewFromBytesTest_2141, EmptyBytesFailsAndSetsErrorWhenProvided_2141) {
  // Boundary: empty byte stream.
  static const char kEmpty = '\0';
  GBytes *bytes = g_bytes_new(&kEmpty, 0);
  ASSERT_NE(bytes, nullptr);

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);

  EXPECT_EQ(doc, nullptr);
  // On failure, error is typically set when provided. Assert observable outcome.
  EXPECT_NE(error, nullptr);

  g_clear_error(&error);
  g_bytes_unref(bytes);
}

TEST_F(PopplerDocumentNewFromBytesTest_2141, NonEncryptedPdfIgnoresPasswordParameterAndStillLoads_2141) {
  const std::string pdf = BuildMinimalPdf_2141();
  GBytes *bytes = MakeBytesFromString_2141(pdf);
  ASSERT_NE(bytes, nullptr);

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_bytes(bytes, "some-password", &error);

  ASSERT_NE(doc, nullptr);
  EXPECT_EQ(error, nullptr);

  g_object_unref(doc);
  g_bytes_unref(bytes);
}

}  // namespace