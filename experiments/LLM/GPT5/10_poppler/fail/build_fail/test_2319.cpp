// File: poppler-form-field-get-name-test-2319.cc
#include <gtest/gtest.h>

#include <glib.h>

#include <string>
#include <vector>

extern "C" {
#include <poppler.h>
}

namespace {

struct PdfObj {
  int num;
  std::string body; // without "obj/endobj"
};

static std::string BuildPdfFromObjects(const std::vector<PdfObj>& objs, int root_obj_num) {
  // Build a minimal PDF with xref.
  std::string pdf;
  pdf += "%PDF-1.4\n";
  // A binary comment line is common; keep it ASCII-safe for source files.
  pdf += "%\xE2\xE3\xCF\xD3\n";

  // Track offsets: offsets[i] is byte offset of object i (1..max_obj), offsets[0] is 0 for free obj.
  int max_obj = 0;
  for (const auto& o : objs) max_obj = std::max(max_obj, o.num);
  std::vector<long> offsets(max_obj + 1, 0);

  for (const auto& o : objs) {
    offsets[o.num] = static_cast<long>(pdf.size());
    pdf += std::to_string(o.num) + " 0 obj\n";
    pdf += o.body;
    if (!pdf.empty() && pdf.back() != '\n')
      pdf += "\n";
    pdf += "endobj\n";
  }

  const long xref_offset = static_cast<long>(pdf.size());
  pdf += "xref\n";
  pdf += "0 " + std::to_string(max_obj + 1) + "\n";
  // obj 0
  pdf += "0000000000 65535 f \n";

  for (int i = 1; i <= max_obj; ++i) {
    char buf[32];
    // 10-digit, zero-padded byte offset
    g_snprintf(buf, sizeof(buf), "%010ld", offsets[i]);
    pdf += std::string(buf) + " 00000 n \n";
  }

  pdf += "trailer\n";
  pdf += "<< /Size " + std::to_string(max_obj + 1) + " /Root " + std::to_string(root_obj_num) +
         " 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_offset) + "\n";
  pdf += "%%EOF\n";
  return pdf;
}

static std::string BuildPdf_SingleTextField_WithName(const std::string& field_name) {
  // Object numbers:
  // 1 Catalog
  // 2 Pages
  // 3 Page
  // 4 Contents (empty stream)
  // 5 Widget annotation
  // 6 AcroForm
  // 7 Field (terminal)
  std::vector<PdfObj> objs;

  objs.push_back(PdfObj{
      1, "<< /Type /Catalog /Pages 2 0 R /AcroForm 6 0 R >>",
  });

  objs.push_back(PdfObj{
      2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>",
  });

  objs.push_back(PdfObj{
      3,
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 300 144] "
      "/Resources << >> "
      "/Contents 4 0 R "
      "/Annots [5 0 R] >>",
  });

  // Empty content stream.
  objs.push_back(PdfObj{
      4,
      "<< /Length 0 >>\n"
      "stream\n"
      "\n"
      "endstream",
  });

  // Widget annot; /Parent points to the field dict.
  objs.push_back(PdfObj{
      5,
      "<< /Type /Annot /Subtype /Widget /Rect [10 10 110 30] "
      "/FT /Tx /P 3 0 R "
      "/Parent 7 0 R >>",
  });

  objs.push_back(PdfObj{
      6, "<< /Fields [7 0 R] /NeedAppearances true >>",
  });

  // Terminal field dict: /T is the (partial + fully qualified) name.
  // Kids include the widget.
  objs.push_back(PdfObj{
      7,
      "<< /FT /Tx /T (" + field_name + ") "
      "/Kids [5 0 R] >>",
  });

  return BuildPdfFromObjects(objs, /*root_obj_num=*/1);
}

static std::string BuildPdf_HierarchicalTextField_ParentChild(const std::string& parent_name,
                                                             const std::string& child_name) {
  // Object numbers:
  // 1 Catalog
  // 2 Pages
  // 3 Page
  // 4 Contents (empty stream)
  // 5 Widget annotation
  // 6 AcroForm
  // 7 Parent field (non-terminal)
  // 8 Child field (terminal)
  std::vector<PdfObj> objs;

  objs.push_back(PdfObj{
      1, "<< /Type /Catalog /Pages 2 0 R /AcroForm 6 0 R >>",
  });

  objs.push_back(PdfObj{
      2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>",
  });

  objs.push_back(PdfObj{
      3,
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 300 144] "
      "/Resources << >> "
      "/Contents 4 0 R "
      "/Annots [5 0 R] >>",
  });

  objs.push_back(PdfObj{
      4,
      "<< /Length 0 >>\n"
      "stream\n"
      "\n"
      "endstream",
  });

  // Widget annot; /Parent points to terminal child field.
  objs.push_back(PdfObj{
      5,
      "<< /Type /Annot /Subtype /Widget /Rect [10 10 110 30] "
      "/FT /Tx /P 3 0 R "
      "/Parent 8 0 R >>",
  });

  objs.push_back(PdfObj{
      6, "<< /Fields [7 0 R] /NeedAppearances true >>",
  });

  // Parent field with /Kids -> child field.
  objs.push_back(PdfObj{
      7,
      "<< /T (" + parent_name + ") "
      "/Kids [8 0 R] >>",
  });

  // Child field with /T and /Kids -> widget.
  objs.push_back(PdfObj{
      8,
      "<< /FT /Tx /T (" + child_name + ") "
      "/Kids [5 0 R] >>",
  });

  return BuildPdfFromObjects(objs, /*root_obj_num=*/1);
}

class PopplerFormFieldGetNameTest_2319 : public ::testing::Test {
 protected:
  static PopplerDocument* NewDocFromDataOrFail(const std::string& pdf_data) {
    GError* err = nullptr;
    PopplerDocument* doc =
        poppler_document_new_from_data(pdf_data.data(), static_cast<int>(pdf_data.size()),
                                       /*password=*/nullptr, &err);
    if (!doc) {
      std::string msg = "poppler_document_new_from_data failed";
      if (err && err->message) {
        msg += ": ";
        msg += err->message;
      }
      if (err) g_error_free(err);
      ADD_FAILURE() << msg;
      return nullptr;
    }
    if (err) g_error_free(err);
    return doc;
  }

  static PopplerFormField* FirstFieldFromFirstPageOrFail(PopplerDocument* doc) {
    PopplerPage* page = poppler_document_get_page(doc, 0);
    if (!page) {
      ADD_FAILURE() << "poppler_document_get_page(0) returned NULL";
      return nullptr;
    }

    GList* mappings = poppler_page_get_form_field_mapping(page);
    g_object_unref(page);

    if (!mappings) {
      ADD_FAILURE() << "poppler_page_get_form_field_mapping returned empty list";
      return nullptr;
    }

    auto* mapping = static_cast<PopplerFormFieldMapping*>(mappings->data);
    PopplerFormField* field = mapping ? mapping->field : nullptr;

    poppler_page_free_form_field_mapping(mappings);

    if (!field) {
      ADD_FAILURE() << "First PopplerFormFieldMapping has NULL field";
      return nullptr;
    }
    return field;
  }
};

TEST_F(PopplerFormFieldGetNameTest_2319, ReturnsNullForNullField_2319) {
  EXPECT_EQ(poppler_form_field_get_name(nullptr), nullptr);
}

TEST_F(PopplerFormFieldGetNameTest_2319, ReturnsNullForNonFormFieldObject_2319) {
  // Passing a valid GObject of the wrong type should trigger g_return_val_if_fail and return NULL.
  // Expect a CRITICAL log; domain may vary by build, but Poppler commonly uses "Poppler".
  g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_FORM_FIELD*");
  PopplerDocument* doc = g_object_new(POPPLER_TYPE_DOCUMENT, nullptr);
  ASSERT_NE(doc, nullptr);

  gchar* name = poppler_form_field_get_name(reinterpret_cast<PopplerFormField*>(doc));
  EXPECT_EQ(name, nullptr);

  g_object_unref(doc);
  g_test_assert_expected_messages();
}

TEST_F(PopplerFormFieldGetNameTest_2319, ReturnsUtf8NameForSimpleField_2319) {
  const std::string pdf = BuildPdf_SingleTextField_WithName("Field1");
  PopplerDocument* doc = NewDocFromDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerFormField* field = FirstFieldFromFirstPageOrFail(doc);
  ASSERT_NE(field, nullptr);

  gchar* name = poppler_form_field_get_name(field);
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "Field1");

  g_free(name);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldGetNameTest_2319, ReturnsFullyQualifiedNameForHierarchy_2319) {
  const std::string pdf = BuildPdf_HierarchicalTextField_ParentChild("Parent", "Child");
  PopplerDocument* doc = NewDocFromDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerFormField* field = FirstFieldFromFirstPageOrFail(doc);
  ASSERT_NE(field, nullptr);

  gchar* name = poppler_form_field_get_name(field);
  ASSERT_NE(name, nullptr);

  // Observable expectation: a "fully qualified" name should include both components.
  // Poppler commonly joins hierarchical names with a dot, but we avoid assuming the exact
  // delimiter by checking both parts are present and in order.
  const std::string s(name);
  EXPECT_NE(s.find("Parent"), std::string::npos);
  EXPECT_NE(s.find("Child"), std::string::npos);
  EXPECT_LT(s.find("Parent"), s.find("Child"));

  g_free(name);
  g_object_unref(doc);
}

} // namespace