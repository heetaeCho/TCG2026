// File: poppler-form-field-choice-can-select-multiple-test_2342.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <poppler.h>

#include <cstdio>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

namespace {

class PopplerFormFieldChoiceCanSelectMultipleTest_2342 : public ::testing::Test {
protected:
  void SetUp() override {
    tmp_dir_ = g_dir_make_tmp("poppler-ff-choice-2342-XXXXXX", nullptr);
    ASSERT_NE(tmp_dir_, nullptr);

    pdf_path_ = std::string(tmp_dir_) + G_DIR_SEPARATOR_S + "choice_fields_2342.pdf";
    ASSERT_TRUE(WriteMinimalPdfWithFormFields(pdf_path_));

    gchar* uri = g_filename_to_uri(pdf_path_.c_str(), nullptr, nullptr);
    ASSERT_NE(uri, nullptr);

    GError* error = nullptr;
    doc_ = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
    g_free(uri);

    ASSERT_NE(doc_, nullptr) << (error ? error->message : "unknown error");
    if (error) g_error_free(error);

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);

    // Load mappings for page 0.
    fields_ = poppler_page_get_form_field_mapping(page_);
    ASSERT_NE(fields_, nullptr);
  }

  void TearDown() override {
    if (fields_) {
      poppler_page_free_form_field_mapping(fields_);
      fields_ = nullptr;
    }
    if (page_) {
      g_object_unref(page_);
      page_ = nullptr;
    }
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }

    if (!pdf_path_.empty()) {
      g_remove(pdf_path_.c_str());
    }
    if (tmp_dir_) {
      g_rmdir(tmp_dir_);
      g_free(tmp_dir_);
      tmp_dir_ = nullptr;
    }
  }

  // Creates a tiny PDF with 1 page and 3 widget annotations:
  // - Choice combo (single select)
  // - Choice listbox with MultiSelect flag
  // - Text field (non-choice)
  //
  // This is just test input data generation (not re-implementing Poppler logic).
  static bool WriteMinimalPdfWithFormFields(const std::string& path) {
    // Helper to emit PDF objects and a valid xref table.
    struct Obj {
      int num;
      std::string body; // without "n 0 obj" wrapper
    };

    // Choice flags:
    // combo = bit 18 => 1<<17 = 131072
    // multiselect = bit 22 => 1<<21 = 2097152
    const int kFfCombo = 131072;
    const int kFfMultiSelect = 2097152;

    // Object numbers:
    // 1: Catalog
    // 2: Pages
    // 3: Page
    // 4: Contents
    // 5: AcroForm
    // 6: Combo choice widget
    // 7: Multi-select choice widget
    // 8: Text widget
    std::vector<Obj> objs;

    // Contents: empty stream.
    objs.push_back({4,
                    "<< /Length 0 >>\n"
                    "stream\n"
                    "endstream\n"});

    // Combo choice widget annotation (also a field).
    objs.push_back({6,
                    "<<\n"
                    "  /Type /Annot\n"
                    "  /Subtype /Widget\n"
                    "  /FT /Ch\n"
                    "  /T (combo)\n"
                    "  /Rect [50 700 250 730]\n"
                    "  /F 4\n"
                    "  /Ff " +
                        std::to_string(kFfCombo) +
                        "\n"
                        "  /Opt [(One) (Two) (Three)]\n"
                        "  /P 3 0 R\n"
                        ">>\n"});

    // Multi-select listbox widget (also a field).
    objs.push_back({7,
                    "<<\n"
                    "  /Type /Annot\n"
                    "  /Subtype /Widget\n"
                    "  /FT /Ch\n"
                    "  /T (multi)\n"
                    "  /Rect [50 600 250 680]\n"
                    "  /F 4\n"
                    "  /Ff " +
                        std::to_string(kFfMultiSelect) +
                        "\n"
                        "  /Opt [(Red) (Green) (Blue)]\n"
                        "  /P 3 0 R\n"
                        ">>\n"});

    // Text widget (non-choice).
    objs.push_back({8,
                    "<<\n"
                    "  /Type /Annot\n"
                    "  /Subtype /Widget\n"
                    "  /FT /Tx\n"
                    "  /T (text)\n"
                    "  /Rect [50 520 250 550]\n"
                    "  /F 4\n"
                    "  /P 3 0 R\n"
                    ">>\n"});

    // AcroForm with fields array.
    objs.push_back({5,
                    "<<\n"
                    "  /NeedAppearances true\n"
                    "  /Fields [6 0 R 7 0 R 8 0 R]\n"
                    ">>\n"});

    // Page with Annots and Contents.
    objs.push_back({3,
                    "<<\n"
                    "  /Type /Page\n"
                    "  /Parent 2 0 R\n"
                    "  /MediaBox [0 0 612 792]\n"
                    "  /Contents 4 0 R\n"
                    "  /Annots [6 0 R 7 0 R 8 0 R]\n"
                    "  /Resources << >>\n"
                    ">>\n"});

    // Pages tree.
    objs.push_back({2,
                    "<<\n"
                    "  /Type /Pages\n"
                    "  /Kids [3 0 R]\n"
                    "  /Count 1\n"
                    ">>\n"});

    // Catalog.
    objs.push_back({1,
                    "<<\n"
                    "  /Type /Catalog\n"
                    "  /Pages 2 0 R\n"
                    "  /AcroForm 5 0 R\n"
                    ">>\n"});

    // Sort by object number (so xref is easy).
    std::sort(objs.begin(), objs.end(),
              [](const Obj& a, const Obj& b) { return a.num < b.num; });

    std::ofstream out(path, std::ios::binary);
    if (!out.is_open()) return false;

    out << "%PDF-1.7\n";
    out << "%\xE2\xE3\xCF\xD3\n";

    // We need offsets for xref. PDF objects are 1..max_obj.
    int max_obj = 0;
    for (const auto& o : objs) max_obj = std::max(max_obj, o.num);

    std::vector<long> offsets(max_obj + 1, 0);

    for (const auto& o : objs) {
      offsets[o.num] = static_cast<long>(out.tellp());
      out << o.num << " 0 obj\n" << o.body << "endobj\n";
    }

    long xref_pos = static_cast<long>(out.tellp());
    out << "xref\n";
    out << "0 " << (max_obj + 1) << "\n";
    out << "0000000000 65535 f \n";
    for (int i = 1; i <= max_obj; ++i) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
      out << buf;
    }

    out << "trailer\n";
    out << "<< /Size " << (max_obj + 1) << " /Root 1 0 R >>\n";
    out << "startxref\n";
    out << xref_pos << "\n";
    out << "%%EOF\n";

    out.flush();
    return out.good();
  }

  static PopplerFormField* GetFirstFieldOfType(GList* mappings, PopplerFormFieldType type) {
    for (GList* l = mappings; l; l = l->next) {
      auto* m = static_cast<PopplerFormFieldMapping*>(l->data);
      if (!m || !m->field) continue;
      if (poppler_form_field_get_field_type(m->field) == type) return m->field;
    }
    return nullptr;
  }

  static std::vector<PopplerFormField*> GetAllChoiceFields(GList* mappings) {
    std::vector<PopplerFormField*> out;
    for (GList* l = mappings; l; l = l->next) {
      auto* m = static_cast<PopplerFormFieldMapping*>(l->data);
      if (!m || !m->field) continue;
      if (poppler_form_field_get_field_type(m->field) == POPPLER_FORM_FIELD_CHOICE) {
        out.push_back(m->field);
      }
    }
    return out;
  }

  gchar* tmp_dir_ = nullptr;
  std::string pdf_path_;

  PopplerDocument* doc_ = nullptr;
  PopplerPage* page_ = nullptr;
  GList* fields_ = nullptr; // PopplerFormFieldMapping list
};

// Normal operation: the function is callable on real choice fields and returns a boolean.
TEST_F(PopplerFormFieldChoiceCanSelectMultipleTest_2342, ReturnsBooleanOnChoiceFields_2342) {
  auto choice_fields = GetAllChoiceFields(fields_);
  ASSERT_FALSE(choice_fields.empty()) << "Expected at least one choice field in the test PDF";

  for (auto* field : choice_fields) {
    // Just ensure it returns a valid gboolean without crashing.
    gboolean can_multi = poppler_form_field_choice_can_select_multiple(field);
    EXPECT_TRUE(can_multi == TRUE || can_multi == FALSE);
  }
}

// Boundary/behavioral verification:
// Observationally verify selection behavior is consistent with can_select_multiple().
TEST_F(PopplerFormFieldChoiceCanSelectMultipleTest_2342, SelectionBehaviorMatchesCapability_2342) {
  auto choice_fields = GetAllChoiceFields(fields_);
  ASSERT_FALSE(choice_fields.empty()) << "Expected at least one choice field in the test PDF";

  bool exercised_any_with_2_items = false;

  for (auto* field : choice_fields) {
    const int n_items = poppler_form_field_choice_get_n_items(field);
    if (n_items < 2) continue;

    exercised_any_with_2_items = true;

    // Reset selection state to a known baseline.
    poppler_form_field_choice_unselect_all(field);

    const gboolean can_multi = poppler_form_field_choice_can_select_multiple(field);

    // Select two distinct items.
    poppler_form_field_choice_select_item(field, 0);
    poppler_form_field_choice_select_item(field, 1);

    const gboolean sel0 = poppler_form_field_choice_is_item_selected(field, 0);
    const gboolean sel1 = poppler_form_field_choice_is_item_selected(field, 1);

    if (can_multi) {
      // Multi-select: both should be selected.
      EXPECT_TRUE(sel0) << "Expected item 0 selected when multi-select is supported";
      EXPECT_TRUE(sel1) << "Expected item 1 selected when multi-select is supported";
    } else {
      // Single-select: selecting item 1 after item 0 should leave only item 1 selected.
      EXPECT_FALSE(sel0) << "Expected item 0 not selected after selecting item 1 on single-select";
      EXPECT_TRUE(sel1) << "Expected item 1 selected on single-select";
    }

    // Cleanup for next iteration.
    poppler_form_field_choice_unselect_all(field);
  }

  EXPECT_TRUE(exercised_any_with_2_items)
      << "Expected at least one choice field with >=2 items to exercise selection behavior";
}

// Exceptional/error case (observable): calling this API on a non-choice field should return FALSE.
TEST_F(PopplerFormFieldChoiceCanSelectMultipleTest_2342, NonChoiceFieldReturnsFalse_2342) {
  PopplerFormField* non_choice =
      GetFirstFieldOfType(fields_, POPPLER_FORM_FIELD_TEXT);
  ASSERT_NE(non_choice, nullptr) << "Expected at least one non-choice (text) field in the test PDF";

  // g_return_val_if_fail should make this return FALSE (and likely log a critical).
  EXPECT_FALSE(poppler_form_field_choice_can_select_multiple(non_choice));
}

} // namespace