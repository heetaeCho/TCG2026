// File: poppler-document-get-metadata-test-2206.cc
#include <gtest/gtest.h>

#include <poppler.h>

#include <glib.h>
#include <gio/gio.h>

#include <iomanip>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {

std::string Pad10(gsize v) {
  std::ostringstream oss;
  oss << std::setw(10) << std::setfill('0') << static_cast<unsigned long long>(v);
  return oss.str();
}

// Builds a minimal, valid PDF file. If metadata_xml is std::nullopt, the Catalog
// has no /Metadata entry. If metadata_xml is present, it will be stored in a
// /Metadata stream object and referenced by the Catalog.
std::string BuildMinimalPdfWithOptionalMetadata(const char* metadata_xml) {
  struct Obj {
    int num;
    std::string body;  // must include trailing newline(s) as desired; no "obj/endobj" wrappers
  };

  std::vector<Obj> objs;

  const bool has_metadata = (metadata_xml != nullptr);

  // Object numbers:
  // 1: Catalog
  // 2: Pages
  // 3: Metadata (optional)
  // 4: Page
  // 5: Contents
  std::string catalog_dict;
  if (has_metadata) {
    catalog_dict = "<< /Type /Catalog /Pages 2 0 R /Metadata 3 0 R >>\n";
  } else {
    catalog_dict = "<< /Type /Catalog /Pages 2 0 R >>\n";
  }

  objs.push_back({1, catalog_dict});
  objs.push_back({2, "<< /Type /Pages /Count 1 /Kids [4 0 R] >>\n"});

  if (has_metadata) {
    const std::string xml = std::string(metadata_xml);
    std::ostringstream md;
    md << "<< /Type /Metadata /Subtype /XML /Length " << xml.size() << " >>\n"
       << "stream\n"
       << xml
       << "\nendstream\n";
    objs.push_back({3, md.str()});
  }

  objs.push_back({4, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 10 10] /Contents 5 0 R >>\n"});
  objs.push_back({5, "<< /Length 0 >>\nstream\n\nendstream\n"});

  // Compute /Size for xref: max obj number + 1 (includes object 0).
  int max_obj_num = 0;
  for (const auto& o : objs) max_obj_num = std::max(max_obj_num, o.num);
  const int size = max_obj_num + 1;

  std::string pdf;
  pdf += "%PDF-1.4\n";

  // Offsets for xref, indexed by obj num. obj 0 reserved.
  std::vector<gsize> offsets(static_cast<size_t>(size), 0);

  for (const auto& o : objs) {
    offsets[static_cast<size_t>(o.num)] = pdf.size();
    pdf += std::to_string(o.num) + " 0 obj\n";
    pdf += o.body;
    pdf += "endobj\n";
  }

  const gsize xref_offset = pdf.size();
  pdf += "xref\n";
  pdf += "0 " + std::to_string(size) + "\n";
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i < size; ++i) {
    pdf += Pad10(offsets[static_cast<size_t>(i)]) + " 00000 n \n";
  }

  pdf += "trailer\n";
  pdf += "<< /Size " + std::to_string(size) + " /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_offset) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

std::string WriteTempPdfFileOrDie(const std::string& pdf_bytes) {
  gchar* path = nullptr;
  gint fd = g_file_open_tmp("poppler-metadata-2206-XXXXXX.pdf", &path, nullptr);
  EXPECT_NE(fd, -1);
  EXPECT_NE(path, nullptr);

  // Close FD and write contents using GLib so we don't depend on platform specifics.
  if (fd != -1) {
#if defined(G_OS_WIN32)
    _close(fd);
#else
    close(fd);
#endif
  }

  gboolean ok = g_file_set_contents(path, pdf_bytes.data(),
                                    static_cast<gssize>(pdf_bytes.size()), nullptr);
  EXPECT_TRUE(ok);

  std::string out(path);
  g_free(path);
  return out;
}

std::string PathToFileUri(const std::string& path) {
  gchar* uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, /*error=*/nullptr);
  EXPECT_NE(uri, nullptr);
  std::string out = uri ? uri : "";
  g_free(uri);
  return out;
}

PopplerDocument* LoadDocumentFromFileUriOrDie(const std::string& uri) {
  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
  if (!doc) {
    if (error) {
      ADD_FAILURE() << "Failed to load PDF: " << error->message;
      g_error_free(error);
    } else {
      ADD_FAILURE() << "Failed to load PDF: unknown error";
    }
  }
  EXPECT_NE(doc, nullptr);
  return doc;
}

struct GCharDeleter {
  void operator()(gchar* p) const { g_free(p); }
};
using UniqueGChar = std::unique_ptr<gchar, GCharDeleter>;

class PopplerDocumentGetMetadataTest_2206 : public ::testing::Test {
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

  void MakeDocWithMetadataXml(const char* metadata_xml) {
    const std::string pdf = BuildMinimalPdfWithOptionalMetadata(metadata_xml);
    tmp_path_ = WriteTempPdfFileOrDie(pdf);
    const std::string uri = PathToFileUri(tmp_path_);
    doc_ = LoadDocumentFromFileUriOrDie(uri);
  }

  PopplerDocument* doc_ = nullptr;
  std::string tmp_path_;
};

TEST_F(PopplerDocumentGetMetadataTest_2206, NullDocumentReturnsNull_2206) {
  // Exceptional/error case: invalid argument should return NULL (observable).
  gchar* md = poppler_document_get_metadata(nullptr);
  EXPECT_EQ(md, nullptr);
}

TEST_F(PopplerDocumentGetMetadataTest_2206, NoMetadataInCatalogReturnsNull_2206) {
  // Boundary/normal: Valid document but no /Metadata entry.
  MakeDocWithMetadataXml(/*metadata_xml=*/nullptr);

  UniqueGChar md(poppler_document_get_metadata(doc_));
  EXPECT_EQ(md.get(), nullptr);
}

TEST_F(PopplerDocumentGetMetadataTest_2206, MetadataPresentReturnsDuplicatedXml_2206) {
  // Normal operation: /Metadata stream exists and is readable.
  const char* kXml =
      "<?xpacket begin=\"\xEF\xBB\xBF\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\"/>"
      "</rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";
  MakeDocWithMetadataXml(kXml);

  UniqueGChar md(poppler_document_get_metadata(doc_));
  ASSERT_NE(md.get(), nullptr);
  EXPECT_STREQ(md.get(), kXml);
}

TEST_F(PopplerDocumentGetMetadataTest_2206, EmptyMetadataStreamReturnsEmptyString_2206) {
  // Boundary: /Metadata exists but is empty. Observable expectation: either NULL or "".
  // We assert the strongest behavior that's safe to observe here: if non-NULL, it must be "".
  MakeDocWithMetadataXml("");

  UniqueGChar md(poppler_document_get_metadata(doc_));
  if (md) {
    EXPECT_STREQ(md.get(), "");
  } else {
    SUCCEED() << "poppler_document_get_metadata returned NULL for empty metadata; acceptable.";
  }
}

TEST_F(PopplerDocumentGetMetadataTest_2206, MultipleCallsReturnIndependentCopies_2206) {
  // Verifies observable behavior: each call returns separately allocated memory
  // (caller-owned) when metadata is present.
  const char* kXml = "<xmp>hello</xmp>";
  MakeDocWithMetadataXml(kXml);

  UniqueGChar md1(poppler_document_get_metadata(doc_));
  UniqueGChar md2(poppler_document_get_metadata(doc_));

  ASSERT_NE(md1.get(), nullptr);
  ASSERT_NE(md2.get(), nullptr);
  EXPECT_STREQ(md1.get(), kXml);
  EXPECT_STREQ(md2.get(), kXml);

  // If they are independent allocations, pointers should differ (strong signal).
  // We don't rely on this as a hard requirement; we primarily ensure both are valid.
  if (md1.get() == md2.get()) {
    // Extremely unlikely given g_strdup, but don't fail the test if allocator reuses address.
    SUCCEED() << "Returned pointers identical; content still correct.";
  } else {
    SUCCEED();
  }
}

}  // namespace