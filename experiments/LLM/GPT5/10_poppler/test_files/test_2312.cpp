// poppler-form-field-get-action-test.cc
//
// Unit tests for poppler_form_field_get_action()
// File under test: ./TestProjects/poppler/glib/poppler-form-field.cc
//
// NOTE: These tests treat the implementation as a black box and only validate
// observable behavior via the public GLib Poppler API.

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace {

class PopplerFormFieldGetActionTest_2312 : public ::testing::Test {
protected:
  static std::string BuildPdfWithSingleWidgetField(bool include_action) {
    // Minimal PDF with:
    // - 1 page
    // - AcroForm with one field that is also a Widget annotation
    // - Optional /A (URI) action on the widget/field
    //
    // Objects:
    // 1: Catalog
    // 2: Pages
    // 3: Page
    // 4: Contents
    // 5: AcroForm
    // 6: Field/Widget (also in /Annots)
    // 7: Action (optional, URI)

    struct Obj {
      int num;
      std::string body;
    };

    std::vector<Obj> objs;

    // 4: Contents stream (empty content, but valid)
    objs.push_back({4,
                    "<< /Length 0 >>\n"
                    "stream\n"
                    "\n"
                    "endstream\n"});

    // 6: Field/Widget dict
    std::ostringstream field;
    field << "<<\n"
          << "  /Type /Annot\n"
          << "  /Subtype /Widget\n"
          << "  /Rect [10 10 60 30]\n"
          << "  /FT /Btn\n"
          << "  /T (btn1)\n"
          << "  /F 4\n"
          << "  /P 3 0 R\n";
    if (include_action) {
      field << "  /A 7 0 R\n";
    }
    field << ">>\n";
    objs.push_back({6, field.str()});

    // 5: AcroForm
    objs.push_back({5,
                    "<<\n"
                    "  /Fields [6 0 R]\n"
                    "  /NeedAppearances true\n"
                    ">>\n"});

    // 3: Page (with Annots containing 6 0 R)
    objs.push_back({3,
                    "<<\n"
                    "  /Type /Page\n"
                    "  /Parent 2 0 R\n"
                    "  /MediaBox [0 0 200 200]\n"
                    "  /Resources << >>\n"
                    "  /Contents 4 0 R\n"
                    "  /Annots [6 0 R]\n"
                    ">>\n"});

    // 2: Pages
    objs.push_back({2,
                    "<<\n"
                    "  /Type /Pages\n"
                    "  /Kids [3 0 R]\n"
                    "  /Count 1\n"
                    ">>\n"});

    // 1: Catalog (references AcroForm 5 0 R)
    objs.push_back({1,
                    "<<\n"
                    "  /Type /Catalog\n"
                    "  /Pages 2 0 R\n"
                    "  /AcroForm 5 0 R\n"
                    ">>\n"});

    // 7: URI Action (only if include_action)
    if (include_action) {
      objs.push_back({7,
                      "<<\n"
                      "  /S /URI\n"
                      "  /URI (https://example.com/)\n"
                      ">>\n"});
    }

    // Sort objects by number for stable xref layout.
    std::sort(objs.begin(), objs.end(), [](const Obj& a, const Obj& b) { return a.num < b.num; });

    std::ostringstream pdf;
    pdf << "%PDF-1.4\n%\\xE2\\xE3\\xCF\\xD3\n";

    // offsets[object_number] = byte offset
    const int max_obj_num = include_action ? 7 : 6;
    std::vector<long> offsets(max_obj_num + 1, 0);

    for (const auto& o : objs) {
      offsets[o.num] = static_cast<long>(pdf.tellp());
      pdf << o.num << " 0 obj\n" << o.body << "endobj\n";
    }

    const long xref_start = static_cast<long>(pdf.tellp());
    pdf << "xref\n";
    pdf << "0 " << (max_obj_num + 1) << "\n";
    pdf << "0000000000 65535 f \n";
    for (int i = 1; i <= max_obj_num; ++i) {
      pdf << std::setw(10) << std::setfill('0') << offsets[i] << " 00000 n \n";
    }

    pdf << "trailer\n"
        << "<< /Size " << (max_obj_num + 1) << " /Root 1 0 R >>\n"
        << "startxref\n"
        << xref_start << "\n"
        << "%%EOF\n";

    return pdf.str();
  }

  static std::string WriteTempPdfAndGetUri(const std::string& pdf_bytes) {
    gchar* tmp_path = nullptr;
    gint fd = g_file_open_tmp("poppler_form_field_get_action_XXXXXX.pdf", &tmp_path, nullptr);
    EXPECT_GE(fd, 0);
    EXPECT_NE(tmp_path, nullptr);

    // Write bytes
    gssize to_write = static_cast<gssize>(pdf_bytes.size());
    gssize written = write(fd, pdf_bytes.data(), static_cast<size_t>(to_write));
    close(fd);
    EXPECT_EQ(written, to_write);

    // Convert file path to file:// URI
    gchar* uri = g_filename_to_uri(tmp_path, nullptr, nullptr);
    EXPECT_NE(uri, nullptr);

    std::string uri_str(uri);

    g_free(uri);
    g_free(tmp_path);
    return uri_str;
  }

  static PopplerFormField* GetFirstFormFieldFromDoc(PopplerDocument* doc, PopplerPage** out_page) {
    EXPECT_NE(doc, nullptr);
    EXPECT_NE(out_page, nullptr);

    PopplerPage* page = poppler_document_get_page(doc, 0);
    EXPECT_NE(page, nullptr);

    GList* mappings = poppler_page_get_form_field_mapping(page);
    EXPECT_NE(mappings, nullptr);

    auto* mapping = static_cast<PopplerFormFieldMapping*>(mappings->data);
    EXPECT_NE(mapping, nullptr);
    EXPECT_NE(mapping->field, nullptr);

    PopplerFormField* field = mapping->field;

    poppler_page_free_form_field_mapping(mappings);

    *out_page = page; // caller unrefs
    return field;
  }
};

TEST_F(PopplerFormFieldGetActionTest_2312, ReturnsNullWhenWidgetHasNoActivationAction_2312) {
  const std::string pdf = BuildPdfWithSingleWidgetField(/*include_action=*/false);
  const std::string uri = WriteTempPdfAndGetUri(pdf);

  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
  ASSERT_NE(doc, nullptr);
  ASSERT_EQ(error, nullptr);

  PopplerPage* page = nullptr;
  PopplerFormField* field = GetFirstFormFieldFromDoc(doc, &page);
  ASSERT_NE(field, nullptr);

  // Observable behavior: no activation action => nullptr
  PopplerAction* action = poppler_form_field_get_action(field);
  EXPECT_EQ(action, nullptr);

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldGetActionTest_2312, ReturnsNonNullWhenWidgetHasUriActivationAction_2312) {
  const std::string pdf = BuildPdfWithSingleWidgetField(/*include_action=*/true);
  const std::string uri = WriteTempPdfAndGetUri(pdf);

  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
  ASSERT_NE(doc, nullptr);
  ASSERT_EQ(error, nullptr);

  PopplerPage* page = nullptr;
  PopplerFormField* field = GetFirstFormFieldFromDoc(doc, &page);
  ASSERT_NE(field, nullptr);

  PopplerAction* action = poppler_form_field_get_action(field);
  ASSERT_NE(action, nullptr);

  // Observable behavior through public PopplerAction fields (GLib API exposes them in poppler.h)
  EXPECT_EQ(action->type, POPPLER_ACTION_URI);
  ASSERT_NE(action->uri.uri, nullptr);
  EXPECT_STREQ(action->uri.uri, "https://example.com/");

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldGetActionTest_2312, CachesActionPointerOnRepeatedCalls_2312) {
  const std::string pdf = BuildPdfWithSingleWidgetField(/*include_action=*/true);
  const std::string uri = WriteTempPdfAndGetUri(pdf);

  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
  ASSERT_NE(doc, nullptr);
  ASSERT_EQ(error, nullptr);

  PopplerPage* page = nullptr;
  PopplerFormField* field = GetFirstFormFieldFromDoc(doc, &page);
  ASSERT_NE(field, nullptr);

  PopplerAction* action1 = poppler_form_field_get_action(field);
  ASSERT_NE(action1, nullptr);

  PopplerAction* action2 = poppler_form_field_get_action(field);
  ASSERT_NE(action2, nullptr);

  // Observable caching behavior: same pointer returned.
  EXPECT_EQ(action1, action2);

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldGetActionTest_2312, NoActionRemainsNullAcrossRepeatedCalls_2312) {
  const std::string pdf = BuildPdfWithSingleWidgetField(/*include_action=*/false);
  const std::string uri = WriteTempPdfAndGetUri(pdf);

  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
  ASSERT_NE(doc, nullptr);
  ASSERT_EQ(error, nullptr);

  PopplerPage* page = nullptr;
  PopplerFormField* field = GetFirstFormFieldFromDoc(doc, &page);
  ASSERT_NE(field, nullptr);

  PopplerAction* action1 = poppler_form_field_get_action(field);
  EXPECT_EQ(action1, nullptr);

  PopplerAction* action2 = poppler_form_field_get_action(field);
  EXPECT_EQ(action2, nullptr);

  g_object_unref(page);
  g_object_unref(doc);
}

} // namespace