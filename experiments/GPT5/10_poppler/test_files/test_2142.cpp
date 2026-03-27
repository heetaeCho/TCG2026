// poppler-document-new-from-stream-test_2142.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <gio/gio.h>

#include <poppler.h>

#include <string>
#include <vector>

// NOTE: These tests treat poppler_document_new_from_stream() as a black box.
// We only validate observable behavior: return values and GError outputs.

namespace {

class PopplerDocumentNewFromStreamTest_2142 : public ::testing::Test {
protected:
  static std::vector<guint8> BuildMinimalValidPdfBytes() {
    // Build a tiny, valid PDF with correct xref offsets.
    //
    // Objects:
    // 1 0 Catalog -> /Pages 2 0 R
    // 2 0 Pages -> /Kids [3 0 R], /Count 1
    // 3 0 Page -> /Parent 2 0 R, /MediaBox, /Contents 4 0 R
    // 4 0 Contents -> stream "Hello"
    //
    // We compute byte offsets to write a correct xref table.
    std::string pdf;
    pdf += "%PDF-1.4\n";

    auto append_obj = [&](int obj_num, const std::string &body) {
      pdf += std::to_string(obj_num) + " 0 obj\n";
      pdf += body;
      if (!body.empty() && body.back() != '\n') {
        pdf += "\n";
      }
      pdf += "endobj\n";
    };

    // Record offsets at the start of each "N 0 obj" line.
    std::vector<size_t> offsets(5, 0); // 0..4 (0 is the free object)
    auto mark_offset = [&](int obj_num) { offsets[obj_num] = pdf.size(); };

    mark_offset(1);
    append_obj(1, "<< /Type /Catalog /Pages 2 0 R >>");

    mark_offset(2);
    append_obj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

    mark_offset(3);
    append_obj(3,
               "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] "
               "/Contents 4 0 R >>");

    const std::string stream_data = "BT\n/F1 24 Tf\n72 120 Td\n(Hello) Tj\nET\n";
    mark_offset(4);
    {
      pdf += "4 0 obj\n";
      pdf += "<< /Length " + std::to_string(stream_data.size()) + " >>\n";
      pdf += "stream\n";
      pdf += stream_data;
      pdf += "endstream\n";
      pdf += "endobj\n";
    }

    const size_t xref_offset = pdf.size();
    pdf += "xref\n";
    pdf += "0 5\n";
    pdf += "0000000000 65535 f \n";
    for (int i = 1; i <= 4; ++i) {
      char buf[32];
      // 10-digit, zero-padded offsets, generation 00000, in-use 'n'
      g_snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offsets[i]);
      pdf += buf;
    }

    pdf += "trailer\n";
    pdf += "<< /Size 5 /Root 1 0 R >>\n";
    pdf += "startxref\n";
    pdf += std::to_string(xref_offset) + "\n";
    pdf += "%%EOF\n";

    return std::vector<guint8>(pdf.begin(), pdf.end());
  }

  static GInputStream *MakeMemoryInputStreamCopying(const std::vector<guint8> &bytes) {
    // Make a GMemoryInputStream that owns its data.
    guint8 *copy = static_cast<guint8 *>(g_memdup2(bytes.data(), bytes.size()));
    return g_memory_input_stream_new_from_data(copy, bytes.size(),
                                               reinterpret_cast<GDestroyNotify>(g_free));
  }

  static GInputStream *MakeNonSeekableWrapper(GInputStream *base) {
    // Wrap the stream in a filter stream type that is not seekable itself.
    // GDataInputStream does not implement GSeekable.
    return G_INPUT_STREAM(g_data_input_stream_new(base));
  }
};

TEST_F(PopplerDocumentNewFromStreamTest_2142, NullStreamReturnsNull_2142) {
  GError *error = nullptr;
  PopplerDocument *doc =
      poppler_document_new_from_stream(nullptr, (goffset)-1, nullptr, nullptr, &error);

  EXPECT_EQ(doc, nullptr);
  // g_return_val_if_fail typically does not set GError; we only verify it didn't return a doc.
  if (error) {
    g_error_free(error);
  }
}

TEST_F(PopplerDocumentNewFromStreamTest_2142, InvalidLengthZeroReturnsNull_2142) {
  auto pdf = BuildMinimalValidPdfBytes();
  GInputStream *stream = MakeMemoryInputStreamCopying(pdf);

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_stream(stream, 0, nullptr, nullptr, &error);

  EXPECT_EQ(doc, nullptr);
  if (error) {
    g_error_free(error);
  }
  g_object_unref(stream);
}

TEST_F(PopplerDocumentNewFromStreamTest_2142, NonSeekableStreamReturnsNotSupportedError_2142) {
  auto pdf = BuildMinimalValidPdfBytes();
  GInputStream *base = MakeMemoryInputStreamCopying(pdf);
  GInputStream *wrapped = MakeNonSeekableWrapper(base);

  // wrapped holds a reference to base; unref base after wrapping.
  g_object_unref(base);

  GError *error = nullptr;
  PopplerDocument *doc =
      poppler_document_new_from_stream(wrapped, static_cast<goffset>(pdf.size()), nullptr,
                                       nullptr, &error);

  EXPECT_EQ(doc, nullptr);
  ASSERT_NE(error, nullptr);
  EXPECT_EQ(error->domain, G_IO_ERROR);
  EXPECT_EQ(error->code, G_IO_ERROR_NOT_SUPPORTED);
  EXPECT_STREQ(error->message, "Stream is not seekable");

  g_error_free(error);
  g_object_unref(wrapped);
}

TEST_F(PopplerDocumentNewFromStreamTest_2142, SeekableMemoryStreamWithExplicitLengthSucceeds_2142) {
  auto pdf = BuildMinimalValidPdfBytes();
  GInputStream *stream = MakeMemoryInputStreamCopying(pdf);

  GError *error = nullptr;
  PopplerDocument *doc =
      poppler_document_new_from_stream(stream, static_cast<goffset>(pdf.size()), nullptr,
                                       nullptr, &error);

  ASSERT_NE(doc, nullptr);
  EXPECT_EQ(error, nullptr);

  g_object_unref(doc);
  g_object_unref(stream);
}

TEST_F(PopplerDocumentNewFromStreamTest_2142, SeekableMemoryStreamWithAutoLengthMinusOneSucceeds_2142) {
  auto pdf = BuildMinimalValidPdfBytes();
  GInputStream *stream = MakeMemoryInputStreamCopying(pdf);

  GError *error = nullptr;
  PopplerDocument *doc =
      poppler_document_new_from_stream(stream, (goffset)-1, nullptr, nullptr, &error);

  ASSERT_NE(doc, nullptr);
  EXPECT_EQ(error, nullptr);

  g_object_unref(doc);
  g_object_unref(stream);
}

TEST_F(PopplerDocumentNewFromStreamTest_2142, InvalidPdfDataReturnsNullAndSetsError_2142) {
  // Provide seekable stream and valid length, but invalid PDF bytes.
  const std::string not_a_pdf = "this is not a pdf";
  std::vector<guint8> bytes(not_a_pdf.begin(), not_a_pdf.end());
  GInputStream *stream = MakeMemoryInputStreamCopying(bytes);

  GError *error = nullptr;
  PopplerDocument *doc =
      poppler_document_new_from_stream(stream, static_cast<goffset>(bytes.size()), nullptr,
                                       nullptr, &error);

  EXPECT_EQ(doc, nullptr);
  // Error should be observable for a parse/load failure (exact domain/code may vary by build),
  // so only assert that some error is reported.
  EXPECT_NE(error, nullptr);

  if (error) {
    g_error_free(error);
  }
  g_object_unref(stream);
}

} // namespace