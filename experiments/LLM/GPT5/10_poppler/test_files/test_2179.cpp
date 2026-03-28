// File: poppler-document-set-keywords-test_2179.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstring>
#include <string>

// -------------------- Helpers --------------------

static std::string MakeMinimalPdf_2179(const char* keywords_in_info = nullptr) {
  // A tiny, valid one-page PDF with an /Info dictionary.
  // Note: offsets are computed dynamically to keep it valid.
  std::string pdf;
  auto append = [&](const std::string& s) { pdf += s; };

  append("%PDF-1.4\n");

  std::vector<size_t> obj_offs;

  auto add_obj = [&](int objnum, const std::string& body) {
    obj_offs.push_back(pdf.size());
    append(std::to_string(objnum));
    append(" 0 obj\n");
    append(body);
    append("\nendobj\n");
  };

  // 1: Catalog
  add_obj(1, "<< /Type /Catalog /Pages 2 0 R >>");

  // 2: Pages
  add_obj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  // 3: Page
  add_obj(3,
          "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R "
          "/Resources << >> >>");

  // 4: Contents stream
  add_obj(4,
          "<< /Length 12 >>\n"
          "stream\n"
          "BT\n"
          "/F1 12 Tf\n"
          "ET\n"
          "endstream");

  // 5: Info
  std::string info = "<< ";
  info += "/Producer (unit-test) ";
  if (keywords_in_info) {
    // Put initial keywords to verify updates.
    info += "/Keywords (";
    info += keywords_in_info;
    info += ") ";
  }
  info += ">>";
  add_obj(5, info);

  // xref
  const size_t xref_off = pdf.size();
  append("xref\n");
  append("0 6\n");
  append("0000000000 65535 f \n");
  // objects 1..5
  for (size_t i = 0; i < obj_offs.size(); ++i) {
    char buf[32];
    // 10-digit, zero-padded offsets
    std::snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj_offs[i]);
    append(buf);
  }

  // trailer
  append("trailer\n");
  append("<< /Size 6 /Root 1 0 R /Info 5 0 R >>\n");
  append("startxref\n");
  append(std::to_string(xref_off));
  append("\n%%EOF\n");
  return pdf;
}

struct GErrorDeleter_2179 {
  void operator()(GError* e) const { g_error_free(e); }
};

static PopplerDocument* NewDocumentFromData_2179(const std::string& pdf_data) {
  std::unique_ptr<GError, GErrorDeleter_2179> error;
  GError* err = nullptr;

  PopplerDocument* doc =
      poppler_document_new_from_data(pdf_data.data(),
                                     static_cast<int>(pdf_data.size()),
                                     /*password=*/nullptr,
                                     &err);
  error.reset(err);
  EXPECT_NE(doc, nullptr) << "Failed to create PopplerDocument: "
                          << (error ? error->message : "unknown error");
  return doc;
}

static gchar* GetKeywords_2179(PopplerDocument* doc) {
  // Poppler GLib API returns newly allocated string (or NULL); caller frees.
  return poppler_document_get_keywords(doc);
}

// Simple GLib log capture for g_return_if_fail() criticals.
class GlibLogCapture_2179 {
 public:
  GlibLogCapture_2179() = default;

  void Install(const gchar* domain = nullptr, GLogLevelFlags levels = G_LOG_LEVEL_CRITICAL) {
    domain_ = domain ? domain : "";
    levels_ = levels;
    handler_id_ = g_log_set_handler(
        domain_ && domain_[0] ? domain_ : nullptr,
        static_cast<GLogLevelFlags>(levels_ | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION),
        &GlibLogCapture_2179::HandlerThunk,
        this);
  }

  ~GlibLogCapture_2179() {
    if (handler_id_ != 0) {
      g_log_remove_handler(domain_ && domain_[0] ? domain_ : nullptr, handler_id_);
      handler_id_ = 0;
    }
  }

  int critical_count() const { return critical_count_; }

 private:
  static void HandlerThunk(const gchar* /*log_domain*/,
                           GLogLevelFlags /*log_level*/,
                           const gchar* /*message*/,
                           gpointer user_data) {
    auto* self = static_cast<GlibLogCapture_2179*>(user_data);
    self->critical_count_++;
    // Do not abort; just record.
  }

  const gchar* domain_ = "";
  GLogLevelFlags levels_ = G_LOG_LEVEL_CRITICAL;
  guint handler_id_ = 0;
  int critical_count_ = 0;
};

// -------------------- Tests --------------------

class PopplerDocumentSetKeywordsTest_2179 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
  }

  PopplerDocument* doc_ = nullptr;
};

TEST_F(PopplerDocumentSetKeywordsTest_2179, SetKeywordsUpdatesGetKeywords_2179) {
  const std::string pdf = MakeMinimalPdf_2179("initial");
  doc_ = NewDocumentFromData_2179(pdf);
  ASSERT_NE(doc_, nullptr);

  // Baseline
  {
    gchar* before = GetKeywords_2179(doc_);
    ASSERT_NE(before, nullptr);
    EXPECT_STREQ(before, "initial");
    g_free(before);
  }

  // Update
  poppler_document_set_keywords(doc_, "hello world");

  gchar* after = GetKeywords_2179(doc_);
  ASSERT_NE(after, nullptr);
  EXPECT_STREQ(after, "hello world");
  g_free(after);
}

TEST_F(PopplerDocumentSetKeywordsTest_2179, SetKeywordsEmptyStringIsObservable_2179) {
  const std::string pdf = MakeMinimalPdf_2179("initial");
  doc_ = NewDocumentFromData_2179(pdf);
  ASSERT_NE(doc_, nullptr);

  poppler_document_set_keywords(doc_, "");

  gchar* after = GetKeywords_2179(doc_);
  // Some implementations may store empty as "" (non-null). Assert that it is
  // observable and not equal to the previous non-empty value.
  if (after) {
    EXPECT_STREQ(after, "");
    g_free(after);
  } else {
    // If Poppler chooses to normalize empty to NULL, accept that as well.
    SUCCEED();
  }
}

TEST_F(PopplerDocumentSetKeywordsTest_2179, SetKeywordsNullClearsOrEmpties_2179) {
  const std::string pdf = MakeMinimalPdf_2179("initial");
  doc_ = NewDocumentFromData_2179(pdf);
  ASSERT_NE(doc_, nullptr);

  poppler_document_set_keywords(doc_, nullptr);

  gchar* after = GetKeywords_2179(doc_);
  // Clearing may result in NULL or empty string depending on backend behavior.
  if (after) {
    EXPECT_TRUE(after[0] == '\0');
    g_free(after);
  } else {
    SUCCEED();
  }
}

TEST_F(PopplerDocumentSetKeywordsTest_2179, InvalidUtf8DoesNotChangeExistingKeywords_2179) {
  const std::string pdf = MakeMinimalPdf_2179("initial");
  doc_ = NewDocumentFromData_2179(pdf);
  ASSERT_NE(doc_, nullptr);

  // Set a known good value first.
  poppler_document_set_keywords(doc_, "good");

  {
    gchar* mid = GetKeywords_2179(doc_);
    ASSERT_NE(mid, nullptr);
    EXPECT_STREQ(mid, "good");
    g_free(mid);
  }

  // Provide invalid UTF-8; per implementation, conversion failure returns early.
  const char invalid_utf8[] = "\xFF\xFF";
  poppler_document_set_keywords(doc_, invalid_utf8);

  gchar* after = GetKeywords_2179(doc_);
  ASSERT_NE(after, nullptr);
  EXPECT_STREQ(after, "good");
  g_free(after);
}

TEST_F(PopplerDocumentSetKeywordsTest_2179, NullDocumentTriggersGReturnIfFailAndDoesNotCrash_2179) {
  GlibLogCapture_2179 capture;
  capture.Install(/*domain=*/nullptr, G_LOG_LEVEL_CRITICAL);

  // Should early-return and log a critical (g_return_if_fail).
  poppler_document_set_keywords(nullptr, "x");

  EXPECT_GE(capture.critical_count(), 1);
}