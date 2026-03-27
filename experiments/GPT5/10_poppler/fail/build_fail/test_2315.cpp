// File: poppler-form-field-button-get-state-test_2315.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

// Internal headers (used only to construct a controlled PopplerFormField for error-path testing)
#include "poppler-private.h"
#include "poppler/Form.h"

// Unit under test (declaration may be in poppler-form-field.h, but we include poppler.h above;
// still, declare explicitly to avoid header/visibility issues in some build setups).
extern "C" gboolean poppler_form_field_button_get_state(PopplerFormField *field);

namespace {

class PopplerFormFieldButtonGetStateTest_2315 : public ::testing::Test {
 protected:
  static std::string BuildMinimalCheckboxPdf_2315() {
    // Build a minimal PDF with a single page and a single checkbox widget (/FT /Btn).
    // This is test data generation, not re-implementation of Poppler logic.
    struct Obj_2315 {
      int num;
      std::string body;
    };

    std::vector<Obj_2315> objs;
    objs.push_back(Obj_2315{
        1,
        "<< /Type /Catalog /Pages 2 0 R /AcroForm << /Fields [5 0 R] /NeedAppearances true >> >>"});
    objs.push_back(Obj_2315{2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"});
    objs.push_back(Obj_2315{3,
                            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
                            "   /Resources << >>\n"
                            "   /Annots [6 0 R]\n"
                            ">>"});
    // Form field dictionary
    objs.push_back(Obj_2315{5, "<< /FT /Btn /T (cb) /V /Off /Kids [6 0 R] >>"});

    // Widget annotation for the checkbox
    objs.push_back(Obj_2315{
        6,
        "<< /Type /Annot /Subtype /Widget /Parent 5 0 R\n"
        "   /Rect [20 20 40 40]\n"
        "   /AS /Off\n"
        "   /AP << /N << /Off 7 0 R /Yes 8 0 R >> >>\n"
        ">>"});

    // Appearance streams (empty form XObjects are sufficient for Poppler to parse the widget)
    objs.push_back(Obj_2315{7,
                            "<< /Type /XObject /Subtype /Form /BBox [0 0 20 20]\n"
                            "   /Resources << >> /Length 0 >>\n"
                            "stream\n"
                            "endstream"});
    objs.push_back(Obj_2315{8,
                            "<< /Type /XObject /Subtype /Form /BBox [0 0 20 20]\n"
                            "   /Resources << >> /Length 0 >>\n"
                            "stream\n"
                            "endstream"});

    // We'll generate objects 1..8 (note: object 4 is unused; that's fine).
    const int kMaxObj_2315 = 8;

    std::string pdf;
    pdf.reserve(4096);
    pdf += "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

    std::vector<long> offsets(kMaxObj_2315 + 1, 0);

    auto append_obj = [&](int num, const std::string& body) {
      offsets[num] = static_cast<long>(pdf.size());
      pdf += std::to_string(num) + " 0 obj\n";
      pdf += body;
      pdf += "\nendobj\n";
    };

    // Emit in numeric order to keep xref straightforward.
    for (int n = 1; n <= kMaxObj_2315; ++n) {
      for (const auto& o : objs) {
        if (o.num == n) {
          append_obj(o.num, o.body);
          break;
        }
      }
    }

    const long xref_pos = static_cast<long>(pdf.size());
    pdf += "xref\n";
    pdf += "0 " + std::to_string(kMaxObj_2315 + 1) + "\n";
    pdf += "0000000000 65535 f \n";

    auto fmt10 = [](long v) {
      char buf[32];
      g_snprintf(buf, sizeof(buf), "%010ld", v);
      return std::string(buf);
    };

    for (int n = 1; n <= kMaxObj_2315; ++n) {
      pdf += fmt10(offsets[n]) + " 00000 n \n";
    }

    pdf += "trailer\n";
    pdf += "<< /Size " + std::to_string(kMaxObj_2315 + 1) + " /Root 1 0 R >>\n";
    pdf += "startxref\n";
    pdf += std::to_string(xref_pos) + "\n";
    pdf += "%%EOF\n";
    return pdf;
  }

  static std::string WriteTempPdfAndGetUri_2315(const std::string& pdf_bytes) {
    gchar* tmpl = g_strdup("poppler_form_field_button_get_state_2315_XXXXXX.pdf");
    gchar* tmp_path = nullptr;

    // Create a temp file name.
    int fd = g_file_open_tmp(tmpl, &tmp_path, nullptr);
    g_free(tmpl);
    EXPECT_NE(fd, -1);
    if (fd != -1) {
      close(fd);
    }

    GError* err = nullptr;
    gboolean ok = g_file_set_contents(tmp_path, pdf_bytes.data(),
                                      static_cast<gssize>(pdf_bytes.size()), &err);
    EXPECT_TRUE(ok);
    if (!ok && err) {
      ADD_FAILURE() << "g_file_set_contents failed: " << err->message;
      g_error_free(err);
    }

    gchar* uri = g_filename_to_uri(tmp_path, nullptr, nullptr);
    std::string uri_str = uri ? uri : "";
    g_free(uri);
    g_free(tmp_path);
    return uri_str;
  }
};

TEST_F(PopplerFormFieldButtonGetStateTest_2315, ReturnsFalseInitiallyForCheckbox_2315) {
  const std::string pdf = BuildMinimalCheckboxPdf_2315();
  const std::string uri = WriteTempPdfAndGetUri_2315(pdf);

  GError* err = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &err);
  ASSERT_NE(doc, nullptr);
  if (err) {
    g_error_free(err);
    err = nullptr;
  }

  PopplerPage* page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  // Find a button form field via public API
  GList* mappings = poppler_page_get_form_field_mapping(page);
  ASSERT_NE(mappings, nullptr);

  PopplerFormField* button_field = nullptr;
  for (GList* l = mappings; l; l = l->next) {
    auto* m = static_cast<PopplerFormFieldMapping*>(l->data);
    if (!m || !m->field)
      continue;
    if (poppler_form_field_get_field_type(m->field) == POPPLER_FORM_FIELD_BUTTON) {
      button_field = m->field;
      break;
    }
  }
  ASSERT_NE(button_field, nullptr);

  // UUT: should be FALSE initially (PDF sets /V /Off and /AS /Off).
  EXPECT_FALSE(poppler_form_field_button_get_state(button_field));

  poppler_page_free_form_field_mapping(mappings);
  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldButtonGetStateTest_2315, ReflectsStateAfterSetState_2315) {
  const std::string pdf = BuildMinimalCheckboxPdf_2315();
  const std::string uri = WriteTempPdfAndGetUri_2315(pdf);

  GError* err = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &err);
  ASSERT_NE(doc, nullptr);
  if (err) {
    g_error_free(err);
    err = nullptr;
  }

  PopplerPage* page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  GList* mappings = poppler_page_get_form_field_mapping(page);
  ASSERT_NE(mappings, nullptr);

  PopplerFormField* button_field = nullptr;
  for (GList* l = mappings; l; l = l->next) {
    auto* m = static_cast<PopplerFormFieldMapping*>(l->data);
    if (!m || !m->field)
      continue;
    if (poppler_form_field_get_field_type(m->field) == POPPLER_FORM_FIELD_BUTTON) {
      button_field = m->field;
      break;
    }
  }
  ASSERT_NE(button_field, nullptr);

  // Baseline
  const gboolean initial = poppler_form_field_button_get_state(button_field);

  // Toggle to TRUE and verify UUT reflects it
  poppler_form_field_button_set_state(button_field, TRUE);
  EXPECT_TRUE(poppler_form_field_button_get_state(button_field));

  // Toggle back to FALSE and verify UUT reflects it
  poppler_form_field_button_set_state(button_field, FALSE);
  EXPECT_FALSE(poppler_form_field_button_get_state(button_field));

  // Boundary-ish: set to same state again should keep consistent observable value
  poppler_form_field_button_set_state(button_field, FALSE);
  EXPECT_FALSE(poppler_form_field_button_get_state(button_field));

  // Restore (not strictly necessary)
  poppler_form_field_button_set_state(button_field, initial);

  poppler_page_free_form_field_mapping(mappings);
  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldButtonGetStateTest_2315, ReturnsFalseWhenWidgetTypeIsNotButton_2315) {
  // Error path: g_return_val_if_fail(field->widget->getType() == formButton, FALSE)
  // Construct a controlled PopplerFormField with a non-button FormWidget.
  class NonButtonWidget_2315 : public FormWidget {
   public:
    // FormWidget has a non-trivial ctor in Poppler; however, for this specific test we only need
    // getType() to be callable. We intentionally do not invoke any other behavior.
    //
    // If FormWidget is abstract with pure virtuals, define minimal overrides required by build.
    NonButtonWidget_2315() = default;

    FormWidgetType getType() override { return formText; }  // any non-formButton type
  };

  NonButtonWidget_2315 non_button;

  _PopplerFormField field{};
  field.widget = &non_button;
  field.field_modified_action = nullptr;
  field.format_field_action = nullptr;
  field.validate_field_action = nullptr;
  field.calculate_field_action = nullptr;

  EXPECT_FALSE(poppler_form_field_button_get_state(reinterpret_cast<PopplerFormField*>(&field)));
}

}  // namespace