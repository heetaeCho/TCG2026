// File: poppler_attachment_new_test_2270.cc
//
// Unit tests for Poppler attachment creation behavior (indirectly exercising
// _poppler_attachment_new via poppler_document_get_attachments()).
//
// NOTE: These tests treat Poppler as a black box and validate only observable
// behavior through public GLib API results and public PopplerAttachment fields.

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {

class PopplerAttachmentNewTest_2270 : public ::testing::Test {
protected:
  void TearDown() override {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
    if (!tmp_path_.empty()) {
      g_remove(tmp_path_.c_str());
      tmp_path_.clear();
    }
  }

  // Writes content to a temp file and returns a file:// URI.
  std::string WriteTempPdfAndGetUri_2270(const std::string &pdf_bytes) {
    char tmpl[] = "/tmp/poppler-attachment-2270-XXXXXX.pdf";
    int fd = g_mkstemp(tmpl);
    EXPECT_NE(fd, -1);

    FILE *f = fdopen(fd, "wb");
    EXPECT_NE(f, nullptr);

    size_t written = fwrite(pdf_bytes.data(), 1, pdf_bytes.size(), f);
    EXPECT_EQ(written, pdf_bytes.size());

    fclose(f); // also closes fd

    tmp_path_ = tmpl;

    // Build URI: file:///tmp/...
    std::string uri = "file://";
    uri += tmp_path_;
    return uri;
  }

  // Minimal PDF writer with 3 objects:
  // 1 0: Catalog with EmbeddedFiles name tree.
  // 2 0: FileSpec (/F, /Desc, /EF).
  // 3 0: EmbeddedFile stream (or non-stream if make_stream=false).
  //
  // If include_dates is true, dates are written as PDF date strings.
  // If include_checksum is true, /CheckSum <hex> is included.
  // If make_stream is false, object 3 is a string object instead of a stream.
  std::string MakePdfWithSingleAttachment_2270(
      const std::string &filename,
      const std::string &desc,
      const std::string &payload,
      bool make_stream,
      bool include_dates,
      bool include_checksum,
      const std::string &checksum_hex, // e.g. "616263" for "abc"
      const std::string &creation_date, // e.g. "D:19700101000000Z"
      const std::string &mod_date       // e.g. "D:19700102000000Z"
  ) {
    auto escape_paren = [](const std::string &s) {
      std::string out;
      out.reserve(s.size());
      for (char c : s) {
        if (c == '(' || c == ')' || c == '\\') out.push_back('\\');
        out.push_back(c);
      }
      return out;
    };

    const std::string f_esc = escape_paren(filename);
    const std::string d_esc = escape_paren(desc);

    std::ostringstream obj1;
    obj1 << "1 0 obj\n"
         << "<< /Type /Catalog\n"
         << "   /Names << /EmbeddedFiles << /Names [ (" << f_esc << ") 2 0 R ] >> >>\n"
         << ">>\n"
         << "endobj\n";

    std::ostringstream obj2;
    obj2 << "2 0 obj\n"
         << "<< /Type /Filespec\n"
         << "   /F (" << f_esc << ")\n";
    if (!desc.empty()) {
      obj2 << "   /Desc (" << d_esc << ")\n";
    }
    obj2 << "   /EF << /F 3 0 R >>\n"
         << ">>\n"
         << "endobj\n";

    std::ostringstream obj3;
    if (make_stream) {
      obj3 << "3 0 obj\n"
           << "<< /Type /EmbeddedFile\n"
           << "   /Length " << payload.size() << "\n";

      // /Params dict is where Size/CreationDate/ModDate/CheckSum commonly live.
      obj3 << "   /Params << /Size " << payload.size();
      if (include_dates) {
        obj3 << " /CreationDate (" << escape_paren(creation_date) << ")"
             << " /ModDate (" << escape_paren(mod_date) << ")";
      }
      if (include_checksum) {
        obj3 << " /CheckSum <" << checksum_hex << ">";
      }
      obj3 << " >>\n";

      obj3 << ">>\n"
           << "stream\n"
           << payload << "\n"
           << "endstream\n"
           << "endobj\n";
    } else {
      // Not a stream object -> should lead to warning and missing attachment.
      obj3 << "3 0 obj\n"
           << "(" << escape_paren(payload) << ")\n"
           << "endobj\n";
    }

    const std::string header = "%PDF-1.7\n";
    std::vector<std::string> objs = {obj1.str(), obj2.str(), obj3.str()};

    // Compute offsets
    std::vector<long> offsets;
    offsets.reserve(objs.size() + 1);
    offsets.push_back(0); // object 0 (free)
    long cur = static_cast<long>(header.size());
    for (const auto &o : objs) {
      offsets.push_back(cur);
      cur += static_cast<long>(o.size());
    }

    std::ostringstream xref;
    xref << "xref\n"
         << "0 4\n"
         << "0000000000 65535 f \n";
    for (int i = 1; i <= 3; ++i) {
      xref << std::setw(10) << std::setfill('0') << offsets[i]
           << " 00000 n \n";
    }

    std::ostringstream trailer;
    trailer << "trailer\n"
            << "<< /Size 4 /Root 1 0 R >>\n"
            << "startxref\n"
            << cur << "\n"
            << "%%EOF\n";

    std::ostringstream pdf;
    pdf << header;
    for (const auto &o : objs) pdf << o;
    pdf << xref.str();
    pdf << trailer.str();
    return pdf.str();
  }

  PopplerDocument *OpenDocFromPdfBytes_2270(const std::string &pdf_bytes) {
    std::string uri = WriteTempPdfAndGetUri_2270(pdf_bytes);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
    if (!doc) {
      std::string msg = "poppler_document_new_from_file failed";
      if (error && error->message) msg += std::string(": ") + error->message;
      if (error) g_error_free(error);
      ADD_FAILURE() << msg;
      return nullptr;
    }
    if (error) g_error_free(error);
    return doc;
  }

  static PopplerAttachment *FirstAttachmentOrNull_2270(PopplerDocument *doc) {
    if (!doc) return nullptr;
    GList *atts = poppler_document_get_attachments(doc);
    if (!atts) return nullptr;
    PopplerAttachment *att = static_cast<PopplerAttachment *>(atts->data);
    g_list_free_full(atts, (GDestroyNotify)g_object_unref);
    return att; // NOTE: freed above; so instead, caller must fetch differently.
  }

  // Helper: return list and let caller free.
  static GList *GetAttachments_2270(PopplerDocument *doc) {
    return poppler_document_get_attachments(doc);
  }

  PopplerDocument *doc_ = nullptr;
  std::string tmp_path_;
};

TEST_F(PopplerAttachmentNewTest_2270, NormalOperation_ParsesAttachmentFields_2270) {
  const std::string pdf = MakePdfWithSingleAttachment_2270(
      "att.txt",
      "My desc",
      "hello",
      /*make_stream=*/true,
      /*include_dates=*/true,
      /*include_checksum=*/true,
      /*checksum_hex=*/"616263", // "abc"
      /*creation_date=*/"D:19700101000000Z",
      /*mod_date=*/"D:19700102000000Z");

  doc_ = OpenDocFromPdfBytes_2270(pdf);
  ASSERT_NE(doc_, nullptr);

  GList *atts = GetAttachments_2270(doc_);
  ASSERT_NE(atts, nullptr);
  ASSERT_NE(atts->data, nullptr);

  auto *att = static_cast<PopplerAttachment *>(atts->data);

  // Observable fields (public struct fields in poppler-glib).
  ASSERT_NE(att->name, nullptr);
  EXPECT_STREQ(att->name, "att.txt");

  ASSERT_NE(att->description, nullptr);
  EXPECT_STREQ(att->description, "My desc");

  EXPECT_EQ(att->size, 5u);

  // Deprecated unix times are still expected to be populated when dates exist.
  // 1970-01-01 00:00:00Z -> 0; 1970-01-02 00:00:00Z -> 86400.
  EXPECT_EQ(static_cast<gint64>(att->ctime), 0);
  EXPECT_EQ(static_cast<gint64>(att->mtime), 86400);

  ASSERT_NE(att->checksum, nullptr);
  ASSERT_NE(att->checksum->str, nullptr);
  EXPECT_EQ(std::string(att->checksum->str, att->checksum->len), "abc");

  g_list_free_full(atts, (GDestroyNotify)g_object_unref);
}

TEST_F(PopplerAttachmentNewTest_2270, Boundary_ZeroSizeStreamStillCreatesAttachment_2270) {
  const std::string pdf = MakePdfWithSingleAttachment_2270(
      "empty.bin",
      "Empty payload",
      "",
      /*make_stream=*/true,
      /*include_dates=*/false,
      /*include_checksum=*/false,
      /*checksum_hex=*/"",
      /*creation_date=*/"",
      /*mod_date=*/"");

  doc_ = OpenDocFromPdfBytes_2270(pdf);
  ASSERT_NE(doc_, nullptr);

  GList *atts = GetAttachments_2270(doc_);
  ASSERT_NE(atts, nullptr);
  auto *att = static_cast<PopplerAttachment *>(atts->data);

  ASSERT_NE(att->name, nullptr);
  EXPECT_STREQ(att->name, "empty.bin");
  EXPECT_EQ(att->size, 0u);

  // No dates => times should remain default (often 0); we only assert they are not negative.
  EXPECT_GE(static_cast<gint64>(att->ctime), 0);
  EXPECT_GE(static_cast<gint64>(att->mtime), 0);

  // No checksum entry => should be null (or empty); accept either but prefer null.
  if (att->checksum) {
    EXPECT_EQ(att->checksum->len, 0u);
  }

  g_list_free_full(atts, (GDestroyNotify)g_object_unref);
}

TEST_F(PopplerAttachmentNewTest_2270, Boundary_EmptyChecksumDoesNotPopulateChecksum_2270) {
  // /CheckSum <> (empty)
  const std::string pdf = MakePdfWithSingleAttachment_2270(
      "chk.txt",
      "Has empty checksum",
      "x",
      /*make_stream=*/true,
      /*include_dates=*/false,
      /*include_checksum=*/true,
      /*checksum_hex=*/"", // empty
      /*creation_date=*/"",
      /*mod_date=*/"");

  doc_ = OpenDocFromPdfBytes_2270(pdf);
  ASSERT_NE(doc_, nullptr);

  GList *atts = GetAttachments_2270(doc_);
  ASSERT_NE(atts, nullptr);
  auto *att = static_cast<PopplerAttachment *>(atts->data);

  // The production code only sets checksum if non-empty. We accept either null
  // or an empty GString depending on how core parsing represents <>.
  if (att->checksum) {
    EXPECT_EQ(att->checksum->len, 0u);
  } else {
    SUCCEED();
  }

  g_list_free_full(atts, (GDestroyNotify)g_object_unref);
}

TEST_F(PopplerAttachmentNewTest_2270, ErrorCase_MissingStreamObjectYieldsNoAttachments_2270) {
  // Object 3 is NOT a stream -> underlying creation should warn and drop attachment.
  const std::string pdf = MakePdfWithSingleAttachment_2270(
      "nostream.txt",
      "Should fail",
      "not a stream",
      /*make_stream=*/false,
      /*include_dates=*/false,
      /*include_checksum=*/false,
      /*checksum_hex=*/"",
      /*creation_date=*/"",
      /*mod_date=*/"");

  // Expect a warning about missing stream object for embedded file.
  // Domain may vary depending on build; we match any domain with g_test_expect_message
  // by passing nullptr, which matches any domain in GLib's test API.
  g_test_expect_message(nullptr, G_LOG_LEVEL_WARNING, "*Missing stream object for embedded file*");

  doc_ = OpenDocFromPdfBytes_2270(pdf);
  ASSERT_NE(doc_, nullptr);

  GList *atts = GetAttachments_2270(doc_);
  EXPECT_EQ(atts, nullptr);

  g_test_assert_expected_messages();
}

TEST_F(PopplerAttachmentNewTest_2270, Boundary_NullDescriptionAllowed_NameStillPresent_2270) {
  // desc empty -> omit /Desc entry entirely.
  const std::string pdf = MakePdfWithSingleAttachment_2270(
      "nodesc.txt",
      /*desc=*/"",
      "data",
      /*make_stream=*/true,
      /*include_dates=*/true,
      /*include_checksum=*/false,
      /*checksum_hex=*/"",
      /*creation_date=*/"D:19700101000000Z",
      /*mod_date=*/"D:19700101000000Z");

  doc_ = OpenDocFromPdfBytes_2270(pdf);
  ASSERT_NE(doc_, nullptr);

  GList *atts = GetAttachments_2270(doc_);
  ASSERT_NE(atts, nullptr);
  auto *att = static_cast<PopplerAttachment *>(atts->data);

  ASSERT_NE(att->name, nullptr);
  EXPECT_STREQ(att->name, "nodesc.txt");

  // Description may be null when absent.
  EXPECT_TRUE(att->description == nullptr || std::string(att->description).empty());

  g_list_free_full(atts, (GDestroyNotify)g_object_unref);
}

} // namespace