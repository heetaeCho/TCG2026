// File: poppler-form-field-text-is-rich-text-test.cc
//
// Unit tests for:
//   gboolean poppler_form_field_text_is_rich_text(PopplerFormField *field)
//
// Constraints respected:
// - Treat implementation as a black box.
// - Test only observable behavior (return values + emitted critical logs via GLib).
// - No access to private/internal state.
// - No reimplementation of Poppler internals.

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

// ---------------------------
// Minimal PDF builder helpers
// ---------------------------
namespace {

class PdfBuilder {
 public:
  PdfBuilder() {
    // PDF header + binary comment line
    buf_.append("%PDF-1.5\n");
    buf_.append("%\xE2\xE3\xCF\xD3\n");
    // Object 0 is reserved
    offsets_.push_back(0);
  }

  // Adds an indirect object with the given dictionary body, e.g. "<< /Type /Catalog ... >>"
  int AddObjectDict(const std::string& dict_body) {
    const int obj_num = static_cast<int>(offsets_.size());
    offsets_.push_back(static_cast<uint32_t>(buf_.size()));

    buf_.append(std::to_string(obj_num));
    buf_.append(" 0 obj\n");
    buf_.append(dict_body);
    buf_.append("\nendobj\n");
    return obj_num;
  }

  std::string FinishWithRoot(int root_obj_num) {
    const uint32_t xref_off = static_cast<uint32_t>(buf_.size());

    buf_.append("xref\n");
    buf_.append("0 ");
    buf_.append(std::to_string(offsets_.size()));
    buf_.append("\n");
    buf_.append("0000000000 65535 f \n");

    for (size_t i = 1; i < offsets_.size(); ++i) {
      char line[32];
      std::snprintf(line, sizeof(line), "%010u 00000 n \n", offsets_[i]);
      buf_.append(line);
    }

    buf_.append("trailer\n");
    buf_.append("<< /Size ");
    buf_.append(std::to_string(offsets_.size()));
    buf_.append(" /Root ");
    buf_.append(std::to_string(root_obj_num));
    buf_.append(" 0 R >>\n");
    buf_.append("startxref\n");
    buf_.append(std::to_string(xref_off));
    buf_.append("\n%%EOF\n");

    return buf_;
  }

 private:
  std::string buf_;
  std::vector<uint32_t> offsets_;
};

static std::string BuildPdfWithSingleTextField(bool rich_text) {
  PdfBuilder b;

  // 1: Catalog
  // 2: Pages
  // 3: Page (with Annots [6 0 R])
  // 5: Field dictionary (text)
  // 6: Widget annotation
  //
  // We keep the structure very small but valid enough for Poppler to parse.

  const int pages_obj = b.AddObjectDict("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  const int page_obj = b.AddObjectDict(
      "<< /Type /Page /Parent 2 0 R "
      "/MediaBox [0 0 300 300] "
      "/Resources << >> "
      "/Annots [6 0 R] >>");

  (void)pages_obj;
  (void)page_obj;

  std::string field_dict = "<< /FT /Tx /T (Field1) /V (Hello)";
  if (rich_text) {
    // Rich text value (/RV) commonly indicates rich text content for text fields.
    // We keep it a plain string to avoid extra stream objects.
    field_dict += " /RV (<body xmlns=\\\"http://www.w3.org/1999/xhtml\\\"><p>Hi</p></body>)";
  }
  field_dict += " /Kids [6 0 R] >>";
  const int field_obj = b.AddObjectDict(field_dict);

  const int widget_obj = b.AddObjectDict(
      "<< /Type /Annot /Subtype /Widget "
      "/Parent 4 0 R "
      "/Rect [10 10 120 40] "
      "/P 3 0 R >>");

  // NOTE: We referenced Parent 4 0 R above but our field object number is `field_obj`.
  // To keep object numbers aligned, we build in order so `field_obj` becomes 4 and `widget_obj` becomes 5.
  // However, because we already added 2 (Pages) and 3 (Page), `field_obj` should indeed be 4, widget 5.
  // We still keep variables, but rely on this order.

  (void)widget_obj;

  // AcroForm Fields [4 0 R]
  const int catalog_obj = b.AddObjectDict("<< /Type /Catalog /Pages 2 0 R /AcroForm << /Fields [4 0 R] >> >>");

  return b.FinishWithRoot(catalog_obj);
}

static std::string BuildPdfWithSingleButtonField() {
  PdfBuilder b;

  b.AddObjectDict("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  b.AddObjectDict(
      "<< /Type /Page /Parent 2 0 R "
      "/MediaBox [0 0 300 300] "
      "/Resources << >> "
      "/Annots [6 0 R] >>");

  // Button field (/FT /Btn)
  const int field_obj = b.AddObjectDict("<< /FT /Btn /T (Btn1) /Kids [6 0 R] >>");
  (void)field_obj;

  // Widget annot
  b.AddObjectDict(
      "<< /Type /Annot /Subtype /Widget "
      "/Parent 4 0 R "
      "/Rect [10 10 120 40] "
      "/P 3 0 R >>");

  const int catalog_obj = b.AddObjectDict("<< /Type /Catalog /Pages 2 0 R /AcroForm << /Fields [4 0 R] >> >>");
  return b.FinishWithRoot(catalog_obj);
}

// ---------------------------
// Temp file + Poppler helpers
// ---------------------------
static std::string WriteTempPdfFileOrDie(const std::string& pdf_bytes) {
  std::string tmpl = std::string(g_get_tmp_dir()) + G_DIR_SEPARATOR_S + "poppler_gtest_XXXXXX.pdf";

  // mkstemp requires mutable buffer.
  std::vector<char> path(tmpl.begin(), tmpl.end());
  path.push_back('\0');

  int fd = g_mkstemp_full(path.data(), O_CREAT | O_EXCL | O_RDWR, 0600);
  if (fd < 0) {
    ADD_FAILURE() << "Failed to create temp file: " << g_strerror(errno);
    return std::string();
  }

  ssize_t wrote = ::write(fd, pdf_bytes.data(), static_cast<unsigned long>(pdf_bytes.size()));
  ::close(fd);

  if (wrote < 0 || static_cast<size_t>(wrote) != pdf_bytes.size()) {
    ADD_FAILURE() << "Failed to write PDF bytes to temp file";
    g_remove(path.data());
    return std::string();
  }

  return std::string(path.data());
}

static PopplerFormField* LoadFirstFormFieldOrDie(const std::string& filepath,
                                                 PopplerPage** out_page,
                                                 PopplerDocument** out_doc) {
  *out_page = nullptr;
  *out_doc = nullptr;

  GError* error = nullptr;
  gchar* uri = g_filename_to_uri(filepath.c_str(), nullptr, &error);
  ASSERT_NE(uri, nullptr) << "g_filename_to_uri failed: " << (error ? error->message : "");
  g_clear_error(&error);

  PopplerDocument* doc = poppler_document_new_from_file(uri, nullptr, &error);
  g_free(uri);
  ASSERT_NE(doc, nullptr) << "poppler_document_new_from_file failed: " << (error ? error->message : "");
  g_clear_error(&error);

  PopplerPage* page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  GList* mappings = poppler_page_get_form_field_mapping(page);
  ASSERT_NE(mappings, nullptr);

  auto* mapping = static_cast<PopplerFormFieldMapping*>(mappings->data);
  ASSERT_NE(mapping, nullptr);
  ASSERT_NE(mapping->field, nullptr);

  PopplerFormField* field = mapping->field;

  // Free mapping list (does NOT unref field/page/doc).
  poppler_page_free_form_field_mapping(mappings);

  *out_page = page;
  *out_doc = doc;
  return field;
}

// ---------------------------
// GLib critical log catcher
// ---------------------------
class ScopedCriticalLogCatcher {
 public:
  ScopedCriticalLogCatcher() {
    prev_handler_ = g_log_set_default_handler(&ScopedCriticalLogCatcher::Handler, this);
  }

  ~ScopedCriticalLogCatcher() {
    g_log_set_default_handler(prev_handler_, nullptr);
  }

  int critical_count() const { return critical_count_; }

  const std::vector<std::string>& messages() const { return messages_; }

 private:
  static void Handler(const gchar* log_domain,
                      GLogLevelFlags log_level,
                      const gchar* message,
                      gpointer user_data) {
    auto* self = static_cast<ScopedCriticalLogCatcher*>(user_data);
    if ((log_level & G_LOG_LEVEL_CRITICAL) != 0) {
      self->critical_count_++;
      std::string msg;
      if (log_domain) {
        msg.append(log_domain);
        msg.append(": ");
      }
      if (message) msg.append(message);
      self->messages_.push_back(std::move(msg));
      return;  // swallow
    }

    // For non-critical logs, forward to previous default handler.
    if (self->prev_handler_) {
      self->prev_handler_(log_domain, log_level, message, nullptr);
    }
  }

  GLogFunc prev_handler_ = nullptr;
  int critical_count_ = 0;
  std::vector<std::string> messages_;
};

}  // namespace

// ---------------------------
// Tests
// ---------------------------

TEST(PopplerFormFieldTextIsRichTextTest_2338, ReturnsTrueForRichTextField_2338) {
  const std::string pdf = BuildPdfWithSingleTextField(/*rich_text=*/true);
  const std::string path = WriteTempPdfFileOrDie(pdf);
  ASSERT_FALSE(path.empty());

  PopplerPage* page = nullptr;
  PopplerDocument* doc = nullptr;
  PopplerFormField* field = LoadFirstFormFieldOrDie(path, &page, &doc);

  // Ensure we're actually testing a text field at the public API level.
  EXPECT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_TEXT);

  EXPECT_TRUE(poppler_form_field_text_is_rich_text(field));

  g_object_unref(page);
  g_object_unref(doc);
  g_remove(path.c_str());
}

TEST(PopplerFormFieldTextIsRichTextTest_2338, ReturnsFalseForPlainTextField_2338) {
  const std::string pdf = BuildPdfWithSingleTextField(/*rich_text=*/false);
  const std::string path = WriteTempPdfFileOrDie(pdf);
  ASSERT_FALSE(path.empty());

  PopplerPage* page = nullptr;
  PopplerDocument* doc = nullptr;
  PopplerFormField* field = LoadFirstFormFieldOrDie(path, &page, &doc);

  EXPECT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_TEXT);

  EXPECT_FALSE(poppler_form_field_text_is_rich_text(field));

  g_object_unref(page);
  g_object_unref(doc);
  g_remove(path.c_str());
}

TEST(PopplerFormFieldTextIsRichTextTest_2338, ReturnsFalseAndLogsCriticalOnNullField_2338) {
  ScopedCriticalLogCatcher catcher;

  EXPECT_FALSE(poppler_form_field_text_is_rich_text(nullptr));

  // g_return_val_if_fail should emit a CRITICAL.
  EXPECT_GE(catcher.critical_count(), 1);
}

TEST(PopplerFormFieldTextIsRichTextTest_2338, ReturnsFalseAndLogsCriticalOnNonTextWidget_2338) {
  const std::string pdf = BuildPdfWithSingleButtonField();
  const std::string path = WriteTempPdfFileOrDie(pdf);
  ASSERT_FALSE(path.empty());

  PopplerPage* page = nullptr;
  PopplerDocument* doc = nullptr;
  PopplerFormField* field = LoadFirstFormFieldOrDie(path, &page, &doc);

  // Verify it is NOT a text field via public API.
  EXPECT_NE(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_TEXT);

  ScopedCriticalLogCatcher catcher;
  EXPECT_FALSE(poppler_form_field_text_is_rich_text(field));
  EXPECT_GE(catcher.critical_count(), 1);

  g_object_unref(page);
  g_object_unref(doc);
  g_remove(path.c_str());
}