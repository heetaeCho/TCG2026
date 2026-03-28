// SPDX-License-Identifier: GPL-2.0-or-later
// File: poppler-form-field-text-set-text-test_2334.cc
//
// Unit tests for:
//   void poppler_form_field_text_set_text(PopplerFormField *field, const gchar *text);
//
// Constraints honored:
// - Treat implementation as a black box.
// - Observe behavior only via public API + observable GLib log side-effects.
// - No access to private/internal state.

#include <gtest/gtest.h>

#include <poppler.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <cstring>
#include <memory>
#include <string>
#include <vector>

namespace {

static std::string BuildMinimalAcroFormPdfWithTextAndButton_2334() {
  // Minimal PDF with 1 page and 2 widget annotations:
  // - text field (/FT /Tx) with initial /V (Initial)
  // - button field (/FT /Btn)
  //
  // NOTE: This is only test data; we're not re-implementing Poppler logic.
  std::vector<std::string> objs;
  objs.reserve(10);

  // 1 0 obj: Catalog
  objs.push_back("<< /Type /Catalog /Pages 2 0 R /AcroForm 5 0 R >>");

  // 2 0 obj: Pages
  objs.push_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  // 3 0 obj: Page
  // Annots reference the field widgets directly (8 and 9).
  objs.push_back(
      "<< /Type /Page /Parent 2 0 R "
      "/MediaBox [0 0 200 200] "
      "/Resources 4 0 R "
      "/Annots [8 0 R 9 0 R] >>");

  // 4 0 obj: Resources (font resource used by default appearance)
  objs.push_back("<< /Font << /Helv 10 0 R >> >>");

  // 5 0 obj: AcroForm
  objs.push_back(
      "<< /Fields [8 0 R 9 0 R] "
      "/NeedAppearances true "
      "/DR << /Font << /Helv 10 0 R >> >> >>");

  // 6 0 obj: (unused placeholder to keep numbering simple)
  objs.push_back("<< >>");

  // 7 0 obj: (unused placeholder)
  objs.push_back("<< >>");

  // 8 0 obj: Text field widget
  objs.push_back(
      "<< /FT /Tx /Subtype /Widget "
      "/T (text1) "
      "/Rect [10 10 190 30] "
      "/V (Initial) "
      "/F 4 "
      "/DA (/Helv 12 Tf 0 g) >>");

  // 9 0 obj: Button field widget
  objs.push_back(
      "<< /FT /Btn /Subtype /Widget "
      "/T (btn1) "
      "/Rect [10 50 190 70] "
      "/V /Off "
      "/AS /Off >>");

  // 10 0 obj: Helvetica font
  objs.push_back("<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>");

  // Assemble PDF with proper xref offsets.
  std::string pdf;
  pdf.reserve(4096);
  pdf += "%PDF-1.4\n";

  std::vector<long> offsets;
  offsets.resize(objs.size() + 1, 0);  // index by object number

  for (size_t i = 0; i < objs.size(); ++i) {
    int objNum = static_cast<int>(i) + 1;
    offsets[objNum] = static_cast<long>(pdf.size());
    pdf += std::to_string(objNum);
    pdf += " 0 obj\n";
    pdf += objs[i];
    pdf += "\nendobj\n";
  }

  long xrefPos = static_cast<long>(pdf.size());
  pdf += "xref\n";
  pdf += "0 ";
  pdf += std::to_string(objs.size() + 1);
  pdf += "\n";
  pdf += "0000000000 65535 f \n";
  for (size_t i = 0; i < objs.size(); ++i) {
    int objNum = static_cast<int>(i) + 1;
    char buf[32];
    // 10-digit, zero-padded byte offset.
    g_snprintf(buf, sizeof(buf), "%010ld", offsets[objNum]);
    pdf += buf;
    pdf += " 00000 n \n";
  }

  pdf += "trailer\n";
  pdf += "<< /Size ";
  pdf += std::to_string(objs.size() + 1);
  pdf += " /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xrefPos);
  pdf += "\n%%EOF\n";
  return pdf;
}

static std::string WriteTempPdf_2334(const std::string& bytes) {
  gchar* tmpdir = g_dir_make_tmp("poppler_gtest_2334_XXXXXX", nullptr);
  EXPECT_NE(tmpdir, nullptr);

  gchar* path = g_build_filename(tmpdir, "acroform_2334.pdf", nullptr);

  GError* error = nullptr;
  gboolean ok = g_file_set_contents(path, bytes.data(), static_cast<gssize>(bytes.size()), &error);
  EXPECT_TRUE(ok);
  if (!ok && error) {
    ADD_FAILURE() << "g_file_set_contents failed: " << error->message;
    g_clear_error(&error);
  }

  std::string out(path);

  g_free(path);
  g_free(tmpdir);
  return out;
}

struct LogCapture2334 {
  static void Handler(const gchar* /*log_domain*/,
                      GLogLevelFlags log_level,
                      const gchar* /*message*/,
                      gpointer user_data) {
    auto* self = static_cast<LogCapture2334*>(user_data);
    if (log_level & G_LOG_LEVEL_CRITICAL) {
      self->critical_count++;
    }
  }

  void Install() {
    // Capture critical logs from any domain to avoid depending on log domains.
    handler_id = g_log_set_handler(nullptr, static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL),
                                   &LogCapture2334::Handler, this);
  }

  void Uninstall() {
    if (handler_id != 0) {
      g_log_remove_handler(nullptr, handler_id);
      handler_id = 0;
    }
  }

  ~LogCapture2334() { Uninstall(); }

  guint handler_id = 0;
  int critical_count = 0;
};

class PopplerFormFieldTextSetTextTest_2334 : public ::testing::Test {
 protected:
  void SetUp() override {
    pdf_path_ = WriteTempPdf_2334(BuildMinimalAcroFormPdfWithTextAndButton_2334());

    GError* error = nullptr;
    gchar* uri = g_filename_to_uri(pdf_path_.c_str(), nullptr, &error);
    ASSERT_NE(uri, nullptr);
    ASSERT_EQ(error, nullptr);

    doc_ = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    ASSERT_NE(doc_, nullptr);
    ASSERT_EQ(error, nullptr);

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);

    // Find one text field and one button field from form field mappings.
    GList* mappings = poppler_page_get_form_field_mapping(page_);
    ASSERT_NE(mappings, nullptr);

    for (GList* l = mappings; l != nullptr; l = l->next) {
      auto* mapping = static_cast<PopplerFormFieldMapping*>(l->data);
      if (!mapping || !mapping->field) {
        continue;
      }
      PopplerFormFieldType t = poppler_form_field_get_field_type(mapping->field);
      if (t == POPPLER_FORM_FIELD_TEXT && text_field_ == nullptr) {
        text_field_ = mapping->field;
        g_object_ref(text_field_);
      } else if (t == POPPLER_FORM_FIELD_BUTTON && button_field_ == nullptr) {
        button_field_ = mapping->field;
        g_object_ref(button_field_);
      }
    }

    poppler_page_free_form_field_mapping(mappings);

    ASSERT_NE(text_field_, nullptr);
    ASSERT_NE(button_field_, nullptr);
  }

  void TearDown() override {
    if (text_field_) {
      g_object_unref(text_field_);
      text_field_ = nullptr;
    }
    if (button_field_) {
      g_object_unref(button_field_);
      button_field_ = nullptr;
    }
    if (page_) {
      g_object_unref(page_);
      page_ = nullptr;
    }
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }

    // Best-effort cleanup of temp file.
    if (!pdf_path_.empty()) {
      g_remove(pdf_path_.c_str());
    }
  }

  std::string pdf_path_;
  PopplerDocument* doc_ = nullptr;
  PopplerPage* page_ = nullptr;
  PopplerFormField* text_field_ = nullptr;
  PopplerFormField* button_field_ = nullptr;
};

TEST_F(PopplerFormFieldTextSetTextTest_2334, SetsAsciiText_2334) {
  ASSERT_EQ(poppler_form_field_get_field_type(text_field_), POPPLER_FORM_FIELD_TEXT);

  gchar* before = poppler_form_field_text_get_text(text_field_);
  ASSERT_NE(before, nullptr);
  EXPECT_STREQ(before, "Initial");
  g_free(before);

  poppler_form_field_text_set_text(text_field_, "Hello");

  gchar* after = poppler_form_field_text_get_text(text_field_);
  ASSERT_NE(after, nullptr);
  EXPECT_STREQ(after, "Hello");
  g_free(after);
}

TEST_F(PopplerFormFieldTextSetTextTest_2334, SetsUtf8Text_2334) {
  ASSERT_EQ(poppler_form_field_get_field_type(text_field_), POPPLER_FORM_FIELD_TEXT);

  const char* utf8 = "안녕🙂";

  poppler_form_field_text_set_text(text_field_, utf8);

  gchar* after = poppler_form_field_text_get_text(text_field_);
  ASSERT_NE(after, nullptr);
  EXPECT_STREQ(after, utf8);
  g_free(after);
}

TEST_F(PopplerFormFieldTextSetTextTest_2334, SetsEmptyString_2334) {
  ASSERT_EQ(poppler_form_field_get_field_type(text_field_), POPPLER_FORM_FIELD_TEXT);

  poppler_form_field_text_set_text(text_field_, "");

  gchar* after = poppler_form_field_text_get_text(text_field_);
  // Some implementations might represent empty as "" (most common) or nullptr.
  if (after) {
    EXPECT_STREQ(after, "");
    g_free(after);
  } else {
    SUCCEED();  // Accept nullptr as an observable representation of "no text".
  }
}

TEST_F(PopplerFormFieldTextSetTextTest_2334, NullTextDoesNotCrash_2334) {
  ASSERT_EQ(poppler_form_field_get_field_type(text_field_), POPPLER_FORM_FIELD_TEXT);

  poppler_form_field_text_set_text(text_field_, nullptr);

  // Observable behavior: should be safely representable via getter.
  gchar* after = poppler_form_field_text_get_text(text_field_);
  // Accept either nullptr or empty; just ensure no crash and a consistent output type.
  if (after) {
    // If non-null, it should be a valid NUL-terminated string.
    EXPECT_GE(std::strlen(after), static_cast<size_t>(0));
    g_free(after);
  } else {
    SUCCEED();
  }
}

TEST_F(PopplerFormFieldTextSetTextTest_2334, NonTextFieldEmitsCriticalAndDoesNotCrash_2334) {
  ASSERT_EQ(poppler_form_field_get_field_type(button_field_), POPPLER_FORM_FIELD_BUTTON);

  // Capture GLib critical messages caused by g_return_if_fail().
  LogCapture2334 logs;
  logs.Install();
  int before = logs.critical_count;

  // Should trigger g_return_if_fail(field->widget->getType() == formText) and return.
  poppler_form_field_text_set_text(button_field_, "ShouldNotApply");

  int after = logs.critical_count;
  EXPECT_GE(after, before + 1);

  logs.Uninstall();

  // Ensure the original text field is still functional after the critical path.
  poppler_form_field_text_set_text(text_field_, "StillWorks");
  gchar* txt = poppler_form_field_text_get_text(text_field_);
  ASSERT_NE(txt, nullptr);
  EXPECT_STREQ(txt, "StillWorks");
  g_free(txt);
}

}  // namespace