// File: poppler_annot_file_attachment_get_attachment_test_2104.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>
#include <poppler.h>

#include <string>
#include <vector>

// The function under test lives in poppler-annot.cc; it should be reachable via linkage.
// If the header already declares it, this forward declaration will be compatible.
extern "C" PopplerAttachment *poppler_annot_file_attachment_get_attachment(
    PopplerAnnotFileAttachment *poppler_annot);

namespace {

std::string BuildPdfWithSingleFileAttachmentAnnot(const char *filename_in_filespec) {
  // Minimal PDF with a single /FileAttachment annotation whose /FS is a basic /Filespec with /F (name).
  // Objects:
  // 1 0 Catalog
  // 2 0 Pages
  // 3 0 Page (Annots [5 0 R])
  // 4 0 Contents (empty stream)
  // 5 0 Annot (Subtype /FileAttachment, FS << /Type /Filespec /F (test.txt) >>)
  const std::string header = "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

  std::vector<std::string> objs;
  objs.emplace_back("");  // index 0 unused

  objs.emplace_back(
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n");

  objs.emplace_back(
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n");

  objs.emplace_back(
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
      "   /Contents 4 0 R\n"
      "   /Annots [5 0 R]\n"
      ">>\n"
      "endobj\n");

  objs.emplace_back(
      "4 0 obj\n"
      "<< /Length 0 >>\n"
      "stream\n"
      "endstream\n"
      "endobj\n");

  // Put the provided filename into the literal string for /F.
  std::string annot =
      "5 0 obj\n"
      "<< /Type /Annot /Subtype /FileAttachment /Rect [10 10 20 20]\n"
      "   /FS << /Type /Filespec /F (";
  annot += filename_in_filespec ? filename_in_filespec : "test.txt";
  annot += ") >>\n"
           ">>\n"
           "endobj\n";
  objs.emplace_back(annot);

  // Build body while tracking offsets for xref.
  std::string body;
  std::vector<size_t> offsets(objs.size(), 0);

  body.reserve(2048);
  size_t cursor = header.size();

  for (size_t i = 1; i < objs.size(); ++i) {
    offsets[i] = cursor;
    body += objs[i];
    cursor += objs[i].size();
  }

  // xref
  std::string xref = "xref\n0 6\n";
  xref += "0000000000 65535 f \n";
  for (size_t i = 1; i < 6; ++i) {
    char line[32];
    // 10-digit offset, gen 00000, in-use 'n'
    g_snprintf(line, sizeof(line), "%010lu 00000 n \n",
               static_cast<unsigned long>(offsets[i]));
    xref += line;
  }

  // trailer
  std::string trailer =
      "trailer\n"
      "<< /Size 6 /Root 1 0 R >>\n"
      "startxref\n";

  // startxref points to the beginning of xref section (after header + body)
  const size_t startxref = header.size() + body.size();
  trailer += std::to_string(startxref);
  trailer += "\n%%EOF\n";

  return header + body + xref + trailer;
}

std::string WriteTempPdfFileOrDie(const std::string &pdf_bytes) {
  gchar tmpl[] = "/tmp/poppler_glib_test_2104_XXXXXX.pdf";
  int fd = g_mkstemp(tmpl);
  EXPECT_NE(fd, -1) << "Failed to create temporary file";
  if (fd == -1) {
    return {};
  }

  // Write all bytes.
  gsize to_write = static_cast<gsize>(pdf_bytes.size());
  const char *p = pdf_bytes.data();
  while (to_write > 0) {
    const ssize_t n = write(fd, p, to_write);
    if (n <= 0) {
      close(fd);
      // Best-effort cleanup.
      g_unlink(tmpl);
      ADD_FAILURE() << "Failed to write PDF bytes to temp file";
      return {};
    }
    p += n;
    to_write -= static_cast<gsize>(n);
  }
  close(fd);
  return std::string(tmpl);
}

PopplerAnnot *GetFirstAnnotOrNull(PopplerPage *page) {
  if (!page) {
    return nullptr;
  }
  GList *mappings = poppler_page_get_annot_mapping(page);
  if (!mappings) {
    return nullptr;
  }

  PopplerAnnot *annot = nullptr;
  // Use the first mapping.
  auto *mapping = static_cast<PopplerAnnotMapping *>(mappings->data);
  if (mapping) {
    annot = mapping->annot;
  }

  poppler_page_free_annot_mapping(mappings);
  return annot;
}

}  // namespace

class PopplerAnnotFileAttachmentGetAttachmentTest_2104 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Build and write a PDF containing a single FileAttachment annotation.
    pdf_path_ = WriteTempPdfFileOrDie(BuildPdfWithSingleFileAttachmentAnnot("test.txt"));
    ASSERT_FALSE(pdf_path_.empty());

    // poppler_document_new_from_file expects a URI.
    gchar *uri = g_filename_to_uri(pdf_path_.c_str(), nullptr, nullptr);
    ASSERT_NE(uri, nullptr);

    GError *error = nullptr;
    doc_ = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
    g_free(uri);

    ASSERT_EQ(error, nullptr) << (error ? error->message : "");
    ASSERT_NE(doc_, nullptr);
  }

  void TearDown() override {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
    if (!pdf_path_.empty()) {
      g_unlink(pdf_path_.c_str());
      pdf_path_.clear();
    }
  }

  PopplerDocument *doc_ = nullptr;
  std::string pdf_path_;
};

TEST_F(PopplerAnnotFileAttachmentGetAttachmentTest_2104, ReturnsNullForNullInput_2104) {
  PopplerAttachment *attachment =
      poppler_annot_file_attachment_get_attachment(nullptr);
  EXPECT_EQ(attachment, nullptr);
}

TEST_F(PopplerAnnotFileAttachmentGetAttachmentTest_2104, ReturnsNullForWrongAnnotType_2104) {
  // Create a text annotation PDF and ensure passing a non-file-attachment annot returns NULL.
  const std::string pdf_bytes =
      "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n"
      "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
      "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
      "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
      "   /Contents 4 0 R\n"
      "   /Annots [5 0 R]\n"
      ">>\nendobj\n"
      "4 0 obj\n<< /Length 0 >>\nstream\nendstream\nendobj\n"
      "5 0 obj\n<< /Type /Annot /Subtype /Text /Rect [10 10 20 20] /Contents (hi) >>\nendobj\n"
      "xref\n0 6\n"
      "0000000000 65535 f \n"
      "0000000015 00000 n \n"
      "0000000064 00000 n \n"
      "0000000121 00000 n \n"
      "0000000237 00000 n \n"
      "0000000286 00000 n \n"
      "trailer\n<< /Size 6 /Root 1 0 R >>\n"
      "startxref\n361\n%%EOF\n";

  const std::string path = WriteTempPdfFileOrDie(pdf_bytes);
  ASSERT_FALSE(path.empty());

  gchar *uri = g_filename_to_uri(path.c_str(), nullptr, nullptr);
  ASSERT_NE(uri, nullptr);

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
  g_free(uri);

  ASSERT_EQ(error, nullptr) << (error ? error->message : "");
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  PopplerAnnot *annot = GetFirstAnnotOrNull(page);
  ASSERT_NE(annot, nullptr);
  EXPECT_FALSE(POPPLER_IS_ANNOT_FILE_ATTACHMENT(annot));
  EXPECT_TRUE(POPPLER_IS_ANNOT(annot));

  // Intentionally pass the wrong annot object pointer type; g_return_val_if_fail should guard.
  PopplerAttachment *attachment =
      poppler_annot_file_attachment_get_attachment(reinterpret_cast<PopplerAnnotFileAttachment *>(annot));
  EXPECT_EQ(attachment, nullptr);

  g_object_unref(page);
  g_object_unref(doc);
  g_unlink(path.c_str());
}

TEST_F(PopplerAnnotFileAttachmentGetAttachmentTest_2104, ReturnsNonNullAttachmentForValidAnnot_2104) {
  PopplerPage *page = poppler_document_get_page(doc_, 0);
  ASSERT_NE(page, nullptr);

  PopplerAnnot *annot = GetFirstAnnotOrNull(page);
  ASSERT_NE(annot, nullptr);
  ASSERT_TRUE(POPPLER_IS_ANNOT_FILE_ATTACHMENT(annot));

  auto *file_annot = reinterpret_cast<PopplerAnnotFileAttachment *>(annot);
  PopplerAttachment *attachment = poppler_annot_file_attachment_get_attachment(file_annot);
  ASSERT_NE(attachment, nullptr);

  // Observable behavior via PopplerAttachment API: name should be present.
  const gchar *name = poppler_attachment_get_name(attachment);
  ASSERT_NE(name, nullptr);
  EXPECT_NE(std::string(name).find("test.txt"), std::string::npos);

  g_object_unref(attachment);
  g_object_unref(page);
}

TEST_F(PopplerAnnotFileAttachmentGetAttachmentTest_2104, MultipleCallsReturnIndependentAttachments_2104) {
  PopplerPage *page = poppler_document_get_page(doc_, 0);
  ASSERT_NE(page, nullptr);

  PopplerAnnot *annot = GetFirstAnnotOrNull(page);
  ASSERT_NE(annot, nullptr);
  ASSERT_TRUE(POPPLER_IS_ANNOT_FILE_ATTACHMENT(annot));

  auto *file_annot = reinterpret_cast<PopplerAnnotFileAttachment *>(annot);

  PopplerAttachment *a1 = poppler_annot_file_attachment_get_attachment(file_annot);
  PopplerAttachment *a2 = poppler_annot_file_attachment_get_attachment(file_annot);

  ASSERT_NE(a1, nullptr);
  ASSERT_NE(a2, nullptr);

  // Without assuming internal caching, the safe observable expectation is that both are valid objects.
  // It's also reasonable (and observable) that they can be unref'd independently without crashing.
  const gchar *n1 = poppler_attachment_get_name(a1);
  const gchar *n2 = poppler_attachment_get_name(a2);
  ASSERT_NE(n1, nullptr);
  ASSERT_NE(n2, nullptr);
  EXPECT_NE(std::string(n1).find("test.txt"), std::string::npos);
  EXPECT_NE(std::string(n2).find("test.txt"), std::string::npos);

  g_object_unref(a2);
  g_object_unref(a1);
  g_object_unref(page);
}