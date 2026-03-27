// poppler-form-field-choice-set-text-test.cc
//
// Unit tests for poppler_form_field_choice_set_text()
// TEST_ID: 2351
//
// These tests treat Poppler as a black box and validate only observable behavior
// via the public GLib API (loading PDFs, obtaining PopplerFormField, calling the API,
// and observing results via getters / log behavior).

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

// ---------------------------
// Minimal PDF builder helper
// ---------------------------
// Builds a tiny, valid PDF in-memory with a single page and a single AcroForm field.
// We generate a correct xref table so Poppler can parse it reliably.
class PdfBuilder_2351 {
public:
  // Adds an indirect object "n 0 obj ... endobj" and returns its object number.
  int addObject(const std::string &body) {
    objects_.push_back(body);
    return static_cast<int>(objects_.size()); // 1-based object numbers
  }

  std::string build() const {
    std::string out;
    out += "%PDF-1.4\n";

    // Offsets array: xref entry for object 0 plus N objects.
    std::vector<long> offsets;
    offsets.reserve(objects_.size() + 1);
    offsets.push_back(0); // object 0 is the free object

    for (size_t i = 0; i < objects_.size(); ++i) {
      offsets.push_back(static_cast<long>(out.size()));
      out += std::to_string(i + 1);
      out += " 0 obj\n";
      out += objects_[i];
      if (!out.empty() && out.back() != '\n') out += "\n";
      out += "endobj\n";
    }

    const long xref_offset = static_cast<long>(out.size());
    out += "xref\n";
    out += "0 ";
    out += std::to_string(objects_.size() + 1);
    out += "\n";

    // Object 0 entry.
    out += "0000000000 65535 f \n";

    // Other entries.
    for (size_t i = 1; i < offsets.size(); ++i) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
      out += buf;
    }

    out += "trailer\n";
    out += "<< /Size ";
    out += std::to_string(objects_.size() + 1);
    out += " /Root 1 0 R >>\n";
    out += "startxref\n";
    out += std::to_string(xref_offset);
    out += "\n%%EOF\n";
    return out;
  }

private:
  std::vector<std::string> objects_;
};

// ---------------------------------------
// GLib log capture for g_return_if_fail()
// ---------------------------------------
class GlibCriticalCapture_2351 {
public:
  GlibCriticalCapture_2351() {
    prev_handler_ = g_log_set_default_handler(&GlibCriticalCapture_2351::Handler, this);
  }

  ~GlibCriticalCapture_2351() {
    g_log_set_default_handler(prev_handler_, nullptr);
  }

  int critical_count() const { return critical_count_; }

private:
  static void Handler(const gchar *log_domain,
                      GLogLevelFlags log_level,
                      const gchar *message,
                      gpointer user_data) {
    auto *self = static_cast<GlibCriticalCapture_2351 *>(user_data);
    if ((log_level & G_LOG_LEVEL_CRITICAL) != 0) {
      self->critical_count_++;
    }
    // Forward to previous handler (so tests behave like normal unless asserted).
    if (self->prev_handler_) {
      self->prev_handler_(log_domain, log_level, message, nullptr);
    }
  }

  int critical_count_ = 0;
  GLogFunc prev_handler_ = nullptr;
};

// ---------------------------
// Test utilities
// ---------------------------
static PopplerDocument *LoadDocFromPdfData_2351(const std::string &pdf_data) {
  GError *error = nullptr;

  // poppler_document_new_from_data copies/uses the buffer during load; we keep
  // the std::string alive in the caller for the duration of the call.
  PopplerDocument *doc =
      poppler_document_new_from_data(pdf_data.c_str(),
                                     static_cast<int>(pdf_data.size()),
                                     /*password=*/nullptr,
                                     &error);
  if (!doc) {
    const std::string msg = error ? error->message : "unknown error";
    if (error) g_error_free(error);
    ADD_FAILURE() << "Failed to load PDF data: " << msg;
    return nullptr;
  }
  if (error) g_error_free(error);
  return doc;
}

static PopplerFormField *GetFirstFormFieldOnFirstPage_2351(PopplerDocument *doc) {
  PopplerPage *page = poppler_document_get_page(doc, 0);
  if (!page) return nullptr;

  GList *mappings = poppler_page_get_form_field_mapping(page);
  g_object_unref(page);

  if (!mappings) return nullptr;

  auto *mapping = static_cast<PopplerFormFieldMapping *>(mappings->data);
  PopplerFormField *field = mapping ? mapping->field : nullptr;

  // Important: Poppler's mapping list is owned; free it with the provided API.
  poppler_page_free_form_field_mapping(mappings);

  return field;
}

// Builds a PDF with a single editable combo box choice field (/FT /Ch, /Ff combo+edit).
static std::string BuildPdfWithEditableChoiceField_2351(const char *initial_value_utf8) {
  PdfBuilder_2351 b;

  // 1: Catalog (Root)
  // 2: Pages
  // 3: Page
  // 4: Field dictionary (parent)
  // 5: Widget annotation (kid)
  // 6: Empty content stream

  // Placeholder references are stable because we add objects in known order.

  b.addObject("<< /Type /Catalog /Pages 2 0 R /AcroForm << /Fields [4 0 R] >> >>");

  b.addObject("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  b.addObject("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 300 300]\n"
              "   /Resources << >>\n"
              "   /Annots [5 0 R]\n"
              "   /Contents 6 0 R\n"
              ">>");

  // Choice flags: Combo (bit 17) + Edit (bit 18) => 131072 + 262144 = 393216.
  std::string v = initial_value_utf8 ? initial_value_utf8 : "";
  b.addObject("<< /FT /Ch /T (choice1) /Ff 393216 /V (" + v + ") /Kids [5 0 R] >>");

  b.addObject("<< /Type /Annot /Subtype /Widget /Rect [50 250 250 280]\n"
              "   /Parent 4 0 R\n"
              "   /FT /Ch /T (choice1) /Ff 393216 /V (" +
              v + ")\n"
              ">>");

  b.addObject("<< /Length 0 >>\nstream\nendstream");

  return b.build();
}

// Builds a PDF with a single text field (/FT /Tx) to exercise g_return_if_fail path.
static std::string BuildPdfWithTextField_2351(const char *initial_value_utf8) {
  PdfBuilder_2351 b;

  b.addObject("<< /Type /Catalog /Pages 2 0 R /AcroForm << /Fields [4 0 R] >> >>");
  b.addObject("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  b.addObject("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 300 300]\n"
              "   /Resources << >>\n"
              "   /Annots [5 0 R]\n"
              "   /Contents 6 0 R\n"
              ">>");

  std::string v = initial_value_utf8 ? initial_value_utf8 : "";
  b.addObject("<< /FT /Tx /T (text1) /V (" + v + ") /Kids [5 0 R] >>");

  b.addObject("<< /Type /Annot /Subtype /Widget /Rect [50 250 250 280]\n"
              "   /Parent 4 0 R\n"
              "   /FT /Tx /T (text1) /V (" +
              v + ")\n"
              ">>");

  b.addObject("<< /Length 0 >>\nstream\nendstream");

  return b.build();
}

// ---------------------------
// Tests (TEST_ID: 2351)
// ---------------------------
class PopplerFormFieldChoiceSetTextTest_2351 : public ::testing::Test {};

TEST_F(PopplerFormFieldChoiceSetTextTest_2351, SetTextUpdatesGetText_2351) {
  const std::string pdf = BuildPdfWithEditableChoiceField_2351("Initial");
  PopplerDocument *doc = LoadDocFromPdfData_2351(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerFormField *field = GetFirstFormFieldOnFirstPage_2351(doc);
  ASSERT_NE(field, nullptr);

  ASSERT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_CHOICE);

  poppler_form_field_choice_set_text(field, "Hello");

  // Observable behavior: via public getter.
  gchar *out = poppler_form_field_choice_get_text(field);
  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "Hello");
  g_free(out);

  g_object_unref(doc);
}

TEST_F(PopplerFormFieldChoiceSetTextTest_2351, SetTextEmptyStringRoundTrips_2351) {
  const std::string pdf = BuildPdfWithEditableChoiceField_2351("Initial");
  PopplerDocument *doc = LoadDocFromPdfData_2351(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerFormField *field = GetFirstFormFieldOnFirstPage_2351(doc);
  ASSERT_NE(field, nullptr);
  ASSERT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_CHOICE);

  poppler_form_field_choice_set_text(field, "");

  gchar *out = poppler_form_field_choice_get_text(field);
  // Some implementations may return "" or possibly nullptr; both are observable and acceptable.
  if (out) {
    EXPECT_STREQ(out, "");
    g_free(out);
  } else {
    SUCCEED() << "choice_get_text returned nullptr after setting empty string";
  }

  g_object_unref(doc);
}

TEST_F(PopplerFormFieldChoiceSetTextTest_2351, SetTextNullDoesNotCrash_2351) {
  const std::string pdf = BuildPdfWithEditableChoiceField_2351("Initial");
  PopplerDocument *doc = LoadDocFromPdfData_2351(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerFormField *field = GetFirstFormFieldOnFirstPage_2351(doc);
  ASSERT_NE(field, nullptr);
  ASSERT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_CHOICE);

  // Boundary: nullptr text should be accepted by the API (observable: no crash).
  poppler_form_field_choice_set_text(field, nullptr);

  // Observable outcome: allow either nullptr or empty/changed value, but must not crash.
  gchar *out = poppler_form_field_choice_get_text(field);
  if (out) {
    // If non-null, it should be valid UTF-8; empty string is a reasonable boundary value.
    EXPECT_TRUE(g_utf8_validate(out, -1, nullptr));
    g_free(out);
  } else {
    SUCCEED() << "choice_get_text returned nullptr after setting nullptr";
  }

  g_object_unref(doc);
}

TEST_F(PopplerFormFieldChoiceSetTextTest_2351, NonChoiceFieldEmitsCriticalAndReturns_2351) {
  const std::string pdf = BuildPdfWithTextField_2351("InitialText");
  PopplerDocument *doc = LoadDocFromPdfData_2351(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerFormField *field = GetFirstFormFieldOnFirstPage_2351(doc);
  ASSERT_NE(field, nullptr);
  ASSERT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_TEXT);

  GlibCriticalCapture_2351 capture;
  const int before = capture.critical_count();

  // Error/exceptional path (observable through GLib critical log from g_return_if_fail):
  poppler_form_field_choice_set_text(field, "ShouldNotApply");

  const int after = capture.critical_count();
  EXPECT_GE(after, before + 1) << "Expected at least one GLib CRITICAL from g_return_if_fail";

  g_object_unref(doc);
}

TEST_F(PopplerFormFieldChoiceSetTextTest_2351, SetTextWithNonAsciiUtf8RoundTrips_2351) {
  const std::string pdf = BuildPdfWithEditableChoiceField_2351("초기"); // Korean "initial"
  PopplerDocument *doc = LoadDocFromPdfData_2351(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerFormField *field = GetFirstFormFieldOnFirstPage_2351(doc);
  ASSERT_NE(field, nullptr);
  ASSERT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_CHOICE);

  // Non-ASCII UTF-8 boundary/normal case.
  poppler_form_field_choice_set_text(field, "가나다");

  gchar *out = poppler_form_field_choice_get_text(field);
  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "가나다");
  EXPECT_TRUE(g_utf8_validate(out, -1, nullptr));
  g_free(out);

  g_object_unref(doc);
}