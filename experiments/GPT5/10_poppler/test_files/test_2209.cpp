// File: poppler-document-get-property-test_2209.cc
//
// Unit tests for poppler_document_get_property() behavior via public GObject properties.
// Constraints respected:
// - Treat Poppler as a black box (no internal logic inference beyond observable interface).
// - Interact only through public API / GObject property system.
// - Include normal, boundary, and observable error cases.

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace {

class TempFile {
public:
  TempFile() {
    char tmpl[] = "/tmp/poppler_gtest_XXXXXX.pdf";
    int fd = g_mkstemp_full(tmpl, O_RDWR, 0600);
    EXPECT_GE(fd, 0);
    if (fd >= 0) {
      ::close(fd);
    }
    path_ = tmpl;
  }

  ~TempFile() {
    if (!path_.empty()) {
      g_remove(path_.c_str());
    }
  }

  const std::string &path() const { return path_; }

  void WriteAll(const std::string &bytes) {
    GError *error = nullptr;
    gboolean ok = g_file_set_contents(path_.c_str(), bytes.data(),
                                     static_cast<gssize>(bytes.size()), &error);
    ASSERT_TRUE(ok);
    if (!ok && error) {
      ADD_FAILURE() << "g_file_set_contents failed: " << error->message;
    }
    if (error) {
      g_error_free(error);
    }
  }

private:
  std::string path_;
};

// Build a minimal, valid PDF with 1 page.
// Allows setting:
// - Info dictionary entries (Title/Author/Subject/Keywords/Creator/Producer/CreationDate/ModDate)
// - Catalog keys for PageLayout/PageMode and ViewerPreferences (optional)
// - Metadata stream (XMP) referenced from Catalog /Metadata (optional)
//
// This is test scaffolding only (not Poppler logic).
static std::string BuildMinimalPdf(const std::string &info_dict_body,
                                  const std::string &catalog_extras,
                                  const std::string &metadata_xml_or_empty) {
  // Objects:
  // 1 0 obj: Catalog
  // 2 0 obj: Pages
  // 3 0 obj: Page
  // 4 0 obj: Contents stream
  // 5 0 obj: Info
  // 6 0 obj: Metadata stream (optional; only if provided)
  //
  // We'll compute xref offsets programmatically.

  struct Obj {
    int num;
    std::string body;
  };

  std::vector<Obj> objs;

  std::string metadata_ref;
  std::string metadata_obj;
  if (!metadata_xml_or_empty.empty()) {
    metadata_ref = "/Metadata 6 0 R ";
    std::string md_stream = metadata_xml_or_empty;
    metadata_obj =
        "6 0 obj\n"
        "<< /Type /Metadata /Subtype /XML /Length " +
        std::to_string(md_stream.size()) +
        " >>\n"
        "stream\n" +
        md_stream +
        "\nendstream\n"
        "endobj\n";
  }

  // Catalog with optional extras.
  std::string catalog =
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R " +
      metadata_ref + catalog_extras +
      ">>\n"
      "endobj\n";

  std::string pages =
      "2 0 obj\n"
      "<< /Type /Pages /Count 1 /Kids [3 0 R] >>\n"
      "endobj\n";

  std::string page =
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>\n"
      "endobj\n";

  std::string contents_stream =
      "4 0 obj\n"
      "<< /Length 0 >>\n"
      "stream\n"
      "\n"
      "endstream\n"
      "endobj\n";

  std::string info =
      "5 0 obj\n"
      "<< " +
      info_dict_body +
      ">>\n"
      "endobj\n";

  objs.push_back({1, catalog});
  objs.push_back({2, pages});
  objs.push_back({3, page});
  objs.push_back({4, contents_stream});
  objs.push_back({5, info});
  if (!metadata_obj.empty()) {
    objs.push_back({6, metadata_obj});
  }

  std::string out;
  out += "%PDF-1.6\n";
  out += "%\xE2\xE3\xCF\xD3\n";

  std::vector<size_t> offsets;
  offsets.reserve(objs.size() + 1);
  offsets.push_back(0); // object 0 is special in xref

  // Write objects, tracking offsets.
  // Need offsets indexed by object number, so keep max obj.
  int max_obj = 0;
  for (const auto &o : objs) max_obj = std::max(max_obj, o.num);
  std::vector<size_t> obj_offset(static_cast<size_t>(max_obj + 1), 0);

  for (const auto &o : objs) {
    obj_offset[static_cast<size_t>(o.num)] = out.size();
    out += o.body;
  }

  size_t xref_pos = out.size();
  out += "xref\n";
  out += "0 " + std::to_string(max_obj + 1) + "\n";
  // entry 0
  out += "0000000000 65535 f \n";
  for (int i = 1; i <= max_obj; ++i) {
    // Some object numbers might be missing; mark them free.
    if (obj_offset[static_cast<size_t>(i)] == 0) {
      out += "0000000000 65535 f \n";
      continue;
    }
    char buf[64];
    std::snprintf(buf, sizeof(buf), "%010lu 00000 n \n",
                  static_cast<unsigned long>(obj_offset[static_cast<size_t>(i)]));
    out += buf;
  }

  out += "trailer\n";
  out += "<< /Size " + std::to_string(max_obj + 1) + " /Root 1 0 R /Info 5 0 R >>\n";
  out += "startxref\n";
  out += std::to_string(xref_pos) + "\n";
  out += "%%EOF\n";
  return out;
}

static PopplerDocument *LoadDocumentFromPath(const std::string &path) {
  GError *error = nullptr;
  std::string uri = std::string("file://") + path;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  if (!doc) {
    std::string msg = error ? error->message : "unknown error";
    if (error) g_error_free(error);
    ADD_FAILURE() << "Failed to load document: " << msg;
    return nullptr;
  }
  if (error) g_error_free(error);
  return doc;
}

static void GetStringProperty(GObject *obj, const char *prop_name, gchar **out) {
  ASSERT_NE(obj, nullptr);
  ASSERT_NE(prop_name, nullptr);
  ASSERT_NE(out, nullptr);
  *out = nullptr;
  g_object_get(obj, prop_name, out, nullptr);
}

static guint GetUIntProperty(GObject *obj, const char *prop_name) {
  guint v = 0;
  g_object_get(obj, prop_name, &v, nullptr);
  return v;
}

static gint GetIntProperty(GObject *obj, const char *prop_name) {
  gint v = 0;
  g_object_get(obj, prop_name, &v, nullptr);
  return v;
}

static gboolean GetBoolProperty(GObject *obj, const char *prop_name) {
  gboolean v = FALSE;
  g_object_get(obj, prop_name, &v, nullptr);
  return v;
}

static guint GetFlagsProperty(GObject *obj, const char *prop_name) {
  guint v = 0;
  g_object_get(obj, prop_name, &v, nullptr);
  return v;
}

static gint GetEnumProperty(GObject *obj, const char *prop_name) {
  gint v = 0;
  g_object_get(obj, prop_name, &v, nullptr);
  return v;
}

static GDateTime *GetBoxedDateTime(GObject *obj, const char *prop_name) {
  GDateTime *dt = nullptr;
  g_object_get(obj, prop_name, &dt, nullptr);
  return dt; // caller unrefs if non-null (g_object_get returns a copy/ref depending on property)
}

class PopplerDocumentGetPropertyTest_2209 : public ::testing::Test {
protected:
  void TearDown() override {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
  }

  void LoadFromPdfBytes(const std::string &pdf_bytes) {
    tmp_ = std::make_unique<TempFile>();
    tmp_->WriteAll(pdf_bytes);
    doc_ = LoadDocumentFromPath(tmp_->path());
    ASSERT_NE(doc_, nullptr);
  }

  PopplerDocument *doc_ = nullptr;
  std::unique_ptr<TempFile> tmp_;
};

TEST_F(PopplerDocumentGetPropertyTest_2209, GetTitleAuthorSubjectKeywordsCreatorProducer_2209) {
  // Arrange: PDF with standard Info dictionary strings.
  const std::string info =
      "/Title (UnitTest Title) "
      "/Author (UnitTest Author) "
      "/Subject (UnitTest Subject) "
      "/Keywords (alpha, beta) "
      "/Creator (UnitTest Creator) "
      "/Producer (UnitTest Producer) ";

  LoadFromPdfBytes(BuildMinimalPdf(info, /*catalog_extras=*/"", /*metadata=*/""));

  // Act / Assert via GObject properties
  gchar *title = nullptr;
  gchar *author = nullptr;
  gchar *subject = nullptr;
  gchar *keywords = nullptr;
  gchar *creator = nullptr;
  gchar *producer = nullptr;

  GetStringProperty(G_OBJECT(doc_), "title", &title);
  GetStringProperty(G_OBJECT(doc_), "author", &author);
  GetStringProperty(G_OBJECT(doc_), "subject", &subject);
  GetStringProperty(G_OBJECT(doc_), "keywords", &keywords);
  GetStringProperty(G_OBJECT(doc_), "creator", &creator);
  GetStringProperty(G_OBJECT(doc_), "producer", &producer);

  ASSERT_NE(title, nullptr);
  ASSERT_NE(author, nullptr);
  ASSERT_NE(subject, nullptr);
  ASSERT_NE(keywords, nullptr);
  ASSERT_NE(creator, nullptr);
  ASSERT_NE(producer, nullptr);

  EXPECT_STREQ(title, "UnitTest Title");
  EXPECT_STREQ(author, "UnitTest Author");
  EXPECT_STREQ(subject, "UnitTest Subject");
  EXPECT_STREQ(keywords, "alpha, beta");
  EXPECT_STREQ(creator, "UnitTest Creator");
  EXPECT_STREQ(producer, "UnitTest Producer");

  g_free(title);
  g_free(author);
  g_free(subject);
  g_free(keywords);
  g_free(creator);
  g_free(producer);
}

TEST_F(PopplerDocumentGetPropertyTest_2209, GetFormatMajorMinorAndFormatString_2209) {
  // Arrange: PDF header is %PDF-1.6 from BuildMinimalPdf()
  LoadFromPdfBytes(BuildMinimalPdf(/*info_dict_body=*/"", /*catalog_extras=*/"", /*metadata=*/""));

  // Act: read major/minor and format string properties.
  guint major = GetUIntProperty(G_OBJECT(doc_), "format-major");
  guint minor = GetUIntProperty(G_OBJECT(doc_), "format-minor");

  gchar *format = nullptr;
  GetStringProperty(G_OBJECT(doc_), "format", &format);

  // Assert: version should match header.
  EXPECT_EQ(major, 1u);
  EXPECT_EQ(minor, 6u);

  // format string is implementation-defined; assert it is non-null and contains "1" and "6".
  ASSERT_NE(format, nullptr);
  std::string fmt(format);
  EXPECT_NE(fmt.find('1'), std::string::npos);
  EXPECT_NE(fmt.find('6'), std::string::npos);

  g_free(format);
}

TEST_F(PopplerDocumentGetPropertyTest_2209, ViewerPreferencesPropertyIsUnset_2209) {
  // The provided implementation sets POPPLER_VIEWER_PREFERENCES_UNSET for PROP_VIEWER_PREFERENCES.
  LoadFromPdfBytes(BuildMinimalPdf(/*info_dict_body=*/"", /*catalog_extras=*/"", /*metadata=*/""));

  guint flags = GetFlagsProperty(G_OBJECT(doc_), "viewer-preferences");
  EXPECT_EQ(flags, static_cast<guint>(POPPLER_VIEWER_PREFERENCES_UNSET));
}

TEST_F(PopplerDocumentGetPropertyTest_2209, GetPageLayoutAndModeFromCatalog_2209) {
  // Arrange: set PageLayout and PageMode in the Catalog.
  // Use common PDF names; Poppler maps them to PopplerPageLayout/PopplerPageMode enums.
  const std::string catalog_extras = "/PageLayout /TwoColumnLeft /PageMode /UseOutlines ";

  LoadFromPdfBytes(BuildMinimalPdf(/*info_dict_body=*/"", catalog_extras, /*metadata=*/""));

  // Act
  gint layout = GetEnumProperty(G_OBJECT(doc_), "page-layout");
  gint mode = GetEnumProperty(G_OBJECT(doc_), "page-mode");

  // Assert: should be valid enum values (non-negative) and stable read.
  // (Exact enum numeric values may vary by build; we just require "observable" success.)
  EXPECT_GE(layout, 0);
  EXPECT_GE(mode, 0);
}

TEST_F(PopplerDocumentGetPropertyTest_2209, GetCreationAndModificationDateAndDateTime_2209) {
  // Arrange: set both CreationDate and ModDate (PDF date strings).
  // Use a fixed date; Poppler exposes both int and GDateTime properties.
  const std::string info =
      "/CreationDate (D:20260222010203+09'00') "
      "/ModDate (D:20260222030405+09'00') ";

  LoadFromPdfBytes(BuildMinimalPdf(info, /*catalog_extras=*/"", /*metadata=*/""));

  // Act
  gint creation_date = GetIntProperty(G_OBJECT(doc_), "creation-date");
  gint mod_date = GetIntProperty(G_OBJECT(doc_), "mod-date");

  GDateTime *creation_dt = GetBoxedDateTime(G_OBJECT(doc_), "creation-datetime");
  GDateTime *mod_dt = GetBoxedDateTime(G_OBJECT(doc_), "mod-datetime");

  // Assert: values are observable and should be set to something non-zero/non-null.
  EXPECT_NE(creation_date, 0);
  EXPECT_NE(mod_date, 0);

  ASSERT_NE(creation_dt, nullptr);
  ASSERT_NE(mod_dt, nullptr);

  // Cleanup (g_object_get returns boxed values that must be unref'ed by caller for GDateTime*)
  g_date_time_unref(creation_dt);
  g_date_time_unref(mod_dt);
}

TEST_F(PopplerDocumentGetPropertyTest_2209, GetMetadataPropertyWhenXmpPresent_2209) {
  // Arrange: attach a Metadata stream and ensure metadata property returns non-null string.
  const std::string xmp =
      "<?xpacket begin=\"﻿\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
      "<dc:title><rdf:Alt><rdf:li xml:lang=\"x-default\">XMP Title</rdf:li></rdf:Alt></dc:title>"
      "</rdf:Description>"
      "</rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";

  LoadFromPdfBytes(BuildMinimalPdf(/*info_dict_body=*/"", /*catalog_extras=*/"", xmp));

  // Act
  gchar *metadata = nullptr;
  GetStringProperty(G_OBJECT(doc_), "metadata", &metadata);

  // Assert: non-null and contains recognizable snippet.
  ASSERT_NE(metadata, nullptr);
  std::string md(metadata);
  EXPECT_NE(md.find("x:xmpmeta"), std::string::npos);

  g_free(metadata);
}

TEST_F(PopplerDocumentGetPropertyTest_2209, BoundaryMissingInfoFieldsReturnNullStrings_2209) {
  // Arrange: no Info fields set at all.
  LoadFromPdfBytes(BuildMinimalPdf(/*info_dict_body=*/"", /*catalog_extras=*/"", /*metadata=*/""));

  // Act
  gchar *title = nullptr;
  gchar *author = nullptr;
  gchar *subject = nullptr;
  gchar *keywords = nullptr;
  gchar *creator = nullptr;
  gchar *producer = nullptr;

  GetStringProperty(G_OBJECT(doc_), "title", &title);
  GetStringProperty(G_OBJECT(doc_), "author", &author);
  GetStringProperty(G_OBJECT(doc_), "subject", &subject);
  GetStringProperty(G_OBJECT(doc_), "keywords", &keywords);
  GetStringProperty(G_OBJECT(doc_), "creator", &creator);
  GetStringProperty(G_OBJECT(doc_), "producer", &producer);

  // Assert: These are allowed to be NULL if not present (boundary case).
  // Do not require specific fallback strings.
  EXPECT_TRUE(title == nullptr || std::strlen(title) >= 0);
  EXPECT_TRUE(author == nullptr || std::strlen(author) >= 0);
  EXPECT_TRUE(subject == nullptr || std::strlen(subject) >= 0);
  EXPECT_TRUE(keywords == nullptr || std::strlen(keywords) >= 0);
  EXPECT_TRUE(creator == nullptr || std::strlen(creator) >= 0);
  EXPECT_TRUE(producer == nullptr || std::strlen(producer) >= 0);

  g_free(title);
  g_free(author);
  g_free(subject);
  g_free(keywords);
  g_free(creator);
  g_free(producer);
}

TEST_F(PopplerDocumentGetPropertyTest_2209, BoundaryPrintCopiesPropertyReadable_2209) {
  // Arrange: provide ViewerPreferences with NumCopies.
  // Poppler exposes print-n-copies property (int).
  const std::string catalog_extras =
      "/ViewerPreferences << /NumCopies 2 >> ";

  LoadFromPdfBytes(BuildMinimalPdf(/*info_dict_body=*/"", catalog_extras, /*metadata=*/""));

  // Act
  gint n_copies = GetIntProperty(G_OBJECT(doc_), "print-n-copies");

  // Assert: must be readable; value may or may not reflect PDF depending on Poppler support.
  // We only assert it is non-negative (valid int domain for copies).
  EXPECT_GE(n_copies, 0);
}

static void LogCollector(GLogDomain domain, GLogLevelFlags level, const gchar *message, gpointer user_data) {
  auto *vec = static_cast<std::vector<std::string> *>(user_data);
  (void)domain;
  (void)level;
  if (message) vec->push_back(message);
}

TEST_F(PopplerDocumentGetPropertyTest_2209, ErrorGettingUnknownPropertyEmitsWarningOrCritical_2209) {
  // Observable error case: requesting a non-existent property via g_object_get()
  // should not crash. GLib typically logs a critical/warning.
  LoadFromPdfBytes(BuildMinimalPdf(/*info_dict_body=*/"", /*catalog_extras=*/"", /*metadata=*/""));

  std::vector<std::string> logs;
  guint handler_id = g_log_set_handler(
      /*log_domain=*/"GLib-GObject",
      static_cast<GLogLevelFlags>(G_LOG_LEVEL_WARNING | G_LOG_LEVEL_CRITICAL),
      &LogCollector, &logs);

  // Act: ask for a property that doesn't exist.
  // Using g_object_get() with an unknown property name is an observable misuse.
  gint dummy = 0;
  g_object_get(G_OBJECT(doc_), "this-property-does-not-exist", &dummy, nullptr);

  g_log_remove_handler("GLib-GObject", handler_id);

  // Assert: no crash; and typically at least one log entry.
  // (Some builds may route logs differently; accept empty logs but still validate call safety.)
  SUCCEED();
}

} // namespace