// poppler_attachment_get_mtime_test_2274.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

extern "C" {
#include <poppler.h>
}

#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace {

static std::string BuildPdfWithSingleEmbeddedFile(const char* maybe_mod_date_pdf_format /* e.g. "D:20200101000000Z" or nullptr */) {
  // Minimal PDF with a single page and a single embedded file.
  // Embedded file's /Params can include /ModDate which PopplerAttachment exposes via poppler_attachment_get_mtime().
  const std::string embedded_payload = "Hello attachment\n";

  auto obj = [](int n, const std::string& body) {
    std::ostringstream oss;
    oss << n << " 0 obj\n" << body << "\nendobj\n";
    return oss.str();
  };

  // 1: Catalog with Names tree for EmbeddedFiles.
  const std::string obj1 =
      obj(1, "<< /Type /Catalog /Pages 2 0 R /Names << /EmbeddedFiles 5 0 R >> >>");

  // 2: Pages
  const std::string obj2 =
      obj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  // 3: Page
  const std::string obj3 =
      obj(3, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Contents 4 0 R /Resources << >> >>");

  // 4: Empty content stream
  const std::string obj4 =
      "4 0 obj\n<< /Length 0 >>\nstream\n\nendstream\nendobj\n";

  // 5: EmbeddedFiles name tree: maps "file.txt" -> filespec (6 0 R)
  const std::string obj5 =
      obj(5, "<< /Names [(file.txt) 6 0 R] >>");

  // 6: Filespec referencing embedded file stream (7 0 R)
  const std::string obj6 =
      obj(6, "<< /Type /Filespec /F (file.txt) /UF (file.txt) /EF << /F 7 0 R >> >>");

  // 7: EmbeddedFile stream with optional /ModDate in /Params
  std::ostringstream efDict;
  efDict << "<< /Type /EmbeddedFile /Length " << embedded_payload.size();
  if (maybe_mod_date_pdf_format) {
    efDict << " /Params << /ModDate (" << maybe_mod_date_pdf_format << ") >>";
  }
  efDict << " >>\nstream\n" << embedded_payload << "endstream\n";

  const std::string obj7 = "7 0 obj\n" + efDict.str() + "endobj\n";

  // Assemble with xref offsets.
  std::ostringstream file;
  file << "%PDF-1.4\n";
  const std::string header = file.str();

  std::vector<std::string> objects = {obj1, obj2, obj3, obj4, obj5, obj6, obj7};

  std::vector<std::int64_t> offsets;
  offsets.reserve(objects.size() + 1);
  offsets.push_back(0);  // object 0 is the free entry

  std::string body;
  body.reserve(4096);

  std::int64_t cursor = static_cast<std::int64_t>(header.size());
  for (const auto& s : objects) {
    offsets.push_back(cursor);
    body += s;
    cursor += static_cast<std::int64_t>(s.size());
  }

  file.str(std::string());
  file.clear();
  file << header << body;

  const std::int64_t xref_pos = static_cast<std::int64_t>(file.str().size());

  std::ostringstream xref;
  xref << "xref\n0 " << (objects.size() + 1) << "\n";
  xref << "0000000000 65535 f \n";
  for (size_t i = 1; i < offsets.size(); ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010lld", static_cast<long long>(offsets[i]));
    xref << buf << " 00000 n \n";
  }

  std::ostringstream trailer;
  trailer << "trailer\n<< /Size " << (objects.size() + 1) << " /Root 1 0 R >>\n";
  trailer << "startxref\n" << xref_pos << "\n%%EOF\n";

  file << xref.str() << trailer.str();
  return file.str();
}

class PopplerAttachmentGetMTimeTest_2274 : public ::testing::Test {
 protected:
  static std::string WriteTempPdf(const std::string& pdf_bytes) {
    gchar* tmpl = g_strdup("poppler-attachment-mtime-XXXXXX.pdf");
    int fd = g_mkstemp(tmpl);
    EXPECT_NE(fd, -1);

    // Write bytes
    ssize_t total = 0;
    const char* data = pdf_bytes.data();
    const ssize_t len = static_cast<ssize_t>(pdf_bytes.size());
    while (total < len) {
      ssize_t w = write(fd, data + total, len - total);
      if (w <= 0) break;
      total += w;
    }
    close(fd);

    EXPECT_EQ(total, len);

    std::string path = tmpl;
    g_free(tmpl);
    return path;
  }

  static PopplerDocument* OpenDocFromPathOrFail(const std::string& path) {
    GError* error = nullptr;
    gchar* uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, &error);
    EXPECT_EQ(error, nullptr);
    EXPECT_NE(uri, nullptr);

    PopplerDocument* doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
    g_free(uri);

    EXPECT_EQ(error, nullptr);
    EXPECT_NE(doc, nullptr);
    return doc;
  }
};

TEST_F(PopplerAttachmentGetMTimeTest_2274, NullAttachmentDies_2274) {
  // Observable error case: passing NULL is invalid and should crash (dereference via GET_PRIVATE()).
  ASSERT_DEATH(
      {
        (void)poppler_attachment_get_mtime(nullptr);
      },
      ".*");
}

TEST_F(PopplerAttachmentGetMTimeTest_2274, ReturnsNonNullWhenModDatePresent_2274) {
  const std::string pdf = BuildPdfWithSingleEmbeddedFile("D:20200101000000Z");
  const std::string path = WriteTempPdf(pdf);

  PopplerDocument* doc = OpenDocFromPathOrFail(path);

  // poppler_document_get_attachments(): [transfer full] list with PopplerAttachment elements.
  GList* attachments = poppler_document_get_attachments(doc);
  ASSERT_NE(attachments, nullptr);
  ASSERT_NE(attachments->data, nullptr);
  ASSERT_EQ(attachments->next, nullptr) << "Expected exactly one attachment in the generated PDF";

  auto* attachment = POPPLER_ATTACHMENT(attachments->data);

  GDateTime* mtime = poppler_attachment_get_mtime(attachment);
  ASSERT_NE(mtime, nullptr) << "ModDate was present in the PDF; expected non-null mtime";

  // Transfer-none semantics: pointer should remain valid across calls and be stable.
  EXPECT_EQ(mtime, poppler_attachment_get_mtime(attachment));

  // Validate the returned time is exactly 2020-01-01T00:00:00Z (Unix: 1577836800).
  // (If Poppler chooses a different interpretation, this will surface as an observable mismatch.)
  const gint64 got_unix = g_date_time_to_unix(mtime);
  const gint64 expected_unix = 1577836800LL;
  EXPECT_EQ(got_unix, expected_unix);

  // External interaction boundary: ref/unref should be safe on a non-null returned GDateTime.
  GDateTime* ref = g_date_time_ref(mtime);
  ASSERT_NE(ref, nullptr);
  g_date_time_unref(ref);

  g_list_free_full(attachments, g_object_unref);
  g_object_unref(doc);
  g_remove(path.c_str());
}

TEST_F(PopplerAttachmentGetMTimeTest_2274, ReturnsNullWhenModDateMissing_2274) {
  const std::string pdf = BuildPdfWithSingleEmbeddedFile(nullptr /* no ModDate */);
  const std::string path = WriteTempPdf(pdf);

  PopplerDocument* doc = OpenDocFromPathOrFail(path);

  GList* attachments = poppler_document_get_attachments(doc);
  ASSERT_NE(attachments, nullptr);
  ASSERT_NE(attachments->data, nullptr);

  auto* attachment = POPPLER_ATTACHMENT(attachments->data);

  GDateTime* mtime = poppler_attachment_get_mtime(attachment);
  EXPECT_EQ(mtime, nullptr) << "ModDate was omitted; expected NULL mtime";

  // Stable return for missing value.
  EXPECT_EQ(mtime, poppler_attachment_get_mtime(attachment));

  g_list_free_full(attachments, g_object_unref);
  g_object_unref(doc);
  g_remove(path.c_str());
}

TEST_F(PopplerAttachmentGetMTimeTest_2274, MultipleAttachmentsEachReportIndependentMTime_2274) {
  // Build two PDFs and ensure each attachment's mtime matches its own ModDate.
  const std::string pdfA = BuildPdfWithSingleEmbeddedFile("D:20210102030405Z");
  const std::string pdfB = BuildPdfWithSingleEmbeddedFile("D:20191231235959Z");

  const std::string pathA = WriteTempPdf(pdfA);
  const std::string pathB = WriteTempPdf(pdfB);

  PopplerDocument* docA = OpenDocFromPathOrFail(pathA);
  PopplerDocument* docB = OpenDocFromPathOrFail(pathB);

  GList* listA = poppler_document_get_attachments(docA);
  GList* listB = poppler_document_get_attachments(docB);
  ASSERT_NE(listA, nullptr);
  ASSERT_NE(listB, nullptr);

  auto* attA = POPPLER_ATTACHMENT(listA->data);
  auto* attB = POPPLER_ATTACHMENT(listB->data);

  GDateTime* mtimeA = poppler_attachment_get_mtime(attA);
  GDateTime* mtimeB = poppler_attachment_get_mtime(attB);
  ASSERT_NE(mtimeA, nullptr);
  ASSERT_NE(mtimeB, nullptr);

  // 2021-01-02T03:04:05Z = 1609556645
  EXPECT_EQ(g_date_time_to_unix(mtimeA), 1609556645LL);
  // 2019-12-31T23:59:59Z = 1577836799
  EXPECT_EQ(g_date_time_to_unix(mtimeB), 1577836799LL);

  g_list_free_full(listA, g_object_unref);
  g_list_free_full(listB, g_object_unref);
  g_object_unref(docA);
  g_object_unref(docB);
  g_remove(pathA.c_str());
  g_remove(pathB.c_str());
}

}  // namespace