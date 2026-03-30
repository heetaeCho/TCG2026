// Copyright 2026
// Unit tests for poppler_page_add_annot
// File: poppler-page-add-annot-test.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstddef>
#include <cstring>
#include <string>
#include <vector>

namespace {

class PopplerPageAddAnnotTest_2461 : public ::testing::Test {
protected:
  static std::string BuildPdfWithSingleAnnot(bool text_markup,
                                            bool rotated_page,
                                            bool include_crop_box) {
    // Build a small, valid PDF with:
    // - 1 page
    // - /Annots [5 0 R]
    // - Either /Subtype /Text (non-markup) or /Subtype /Highlight (text-markup)
    //
    // CropBox is optional so we can exercise the "offset by cropBox" behavior
    // without asserting internal geometry.
    struct Obj {
      int num;
      std::string body;
    };

    std::vector<Obj> objs;

    // 1 0 obj: Catalog
    objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R >>"});

    // 2 0 obj: Pages
    objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"});

    // 3 0 obj: Page (with optional Rotate, optional CropBox)
    {
      std::string page_dict = "<< /Type /Page /Parent 2 0 R "
                              "/MediaBox [0 0 200 200] ";
      if (include_crop_box) {
        // Non-zero CropBox offset to make the add_annot offset path meaningful.
        page_dict += "/CropBox [10 20 210 220] ";
      }
      if (rotated_page) {
        page_dict += "/Rotate 90 ";
      }
      page_dict += "/Resources << >> "
                   "/Contents 4 0 R "
                   "/Annots [5 0 R] "
                   ">>";
      objs.push_back({3, page_dict});
    }

    // 4 0 obj: empty content stream
    objs.push_back({4, "<< /Length 0 >>\nstream\n\nendstream"});

    // 5 0 obj: Annotation
    if (text_markup) {
      // Text markup annotation (Highlight) uses QuadPoints.
      // QuadPoints are required by spec for highlight; Poppler typically parses them.
      objs.push_back(
          {5,
           "<< /Type /Annot "
           "/Subtype /Highlight "
           "/Rect [50 60 150 80] "
           "/QuadPoints [50 80 150 80 50 60 150 60] "
           "/C [1 1 0] "
           ">>"});
    } else {
      // Non-markup annotation (Text).
      objs.push_back(
          {5,
           "<< /Type /Annot "
           "/Subtype /Text "
           "/Rect [50 60 70 80] "
           "/Contents (Hello) "
           ">>"});
    }

    // Assemble PDF with correct xref offsets.
    std::string pdf;
    pdf.reserve(2048);

    auto append = [&](const std::string &s) { pdf += s; };

    append("%PDF-1.4\n");
    // Some parsers like a binary comment line; harmless if present.
    append("%\xE2\xE3\xCF\xD3\n");

    // Record offsets: xref needs offsets for objects 0..N.
    const int max_obj = 5;
    std::vector<std::size_t> offsets(max_obj + 1, 0);
    offsets[0] = 0; // free object

    for (const auto &o : objs) {
      offsets[o.num] = pdf.size();
      append(std::to_string(o.num));
      append(" 0 obj\n");
      append(o.body);
      append("\nendobj\n");
    }

    const std::size_t xref_pos = pdf.size();
    append("xref\n");
    append("0 ");
    append(std::to_string(max_obj + 1));
    append("\n");

    // Entry 0: free object
    append("0000000000 65535 f \n");

    // Entries 1..max_obj
    for (int i = 1; i <= max_obj; ++i) {
      char buf[32];
      // 10-digit, zero-padded byte offset; 5-digit generation number.
      std::snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offsets[i]);
      append(buf);
    }

    append("trailer\n");
    append("<< /Size ");
    append(std::to_string(max_obj + 1));
    append(" /Root 1 0 R >>\n");
    append("startxref\n");
    append(std::to_string(xref_pos));
    append("\n%%EOF\n");

    return pdf;
  }

  static PopplerDocument *LoadDocFromPdfData(const std::string &pdf_data) {
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_data(
        pdf_data.data(), static_cast<int>(pdf_data.size()),
        /*password=*/nullptr, &error);
    if (!doc) {
      if (error) {
        g_error_free(error);
      }
    }
    return doc;
  }

  static PopplerPage *GetFirstPage(PopplerDocument *doc) {
    // Page index 0.
    return poppler_document_get_page(doc, 0);
  }

  static GList *GetAnnotMapping(PopplerPage *page) {
    // Returns a GList of PopplerAnnotMapping*
    return poppler_page_get_annot_mapping(page);
  }

  static void FreeAnnotMapping(GList *mapping) {
    poppler_page_free_annot_mapping(mapping);
  }

  static PopplerAnnot *FirstAnnotFromMapping(GList *mapping) {
    if (!mapping) {
      return nullptr;
    }
    auto *m = static_cast<PopplerAnnotMapping *>(mapping->data);
    if (!m) {
      return nullptr;
    }
    return m->annot;
  }

  static int MappingLength(GList *mapping) { return g_list_length(mapping); }
};

TEST_F(PopplerPageAddAnnotTest_2461, NullPageTriggersCriticalAndReturns_2461) {
  // g_return_if_fail should emit a critical and return without crashing.
  // We don't assert exact message text (it can vary), but we do assert a CRITICAL
  // from the Poppler domain.
  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_PAGE*");
  poppler_page_add_annot(nullptr, nullptr);
  g_test_assert_expected_messages();
}

TEST_F(PopplerPageAddAnnotTest_2461, NullAnnotTriggersCriticalAndReturns_2461) {
  const std::string pdf = BuildPdfWithSingleAnnot(
      /*text_markup=*/false, /*rotated_page=*/false, /*include_crop_box=*/true);
  PopplerDocument *doc = LoadDocFromPdfData(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = GetFirstPage(doc);
  ASSERT_NE(page, nullptr);

  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT*");
  poppler_page_add_annot(page, nullptr);
  g_test_assert_expected_messages();

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageAddAnnotTest_2461, RemoveThenAddBackNonMarkupAnnotRestoresPresence_2461) {
  const std::string pdf = BuildPdfWithSingleAnnot(
      /*text_markup=*/false, /*rotated_page=*/false, /*include_crop_box=*/true);
  PopplerDocument *doc = LoadDocFromPdfData(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = GetFirstPage(doc);
  ASSERT_NE(page, nullptr);

  GList *mapping = GetAnnotMapping(page);
  ASSERT_NE(mapping, nullptr);
  EXPECT_EQ(MappingLength(mapping), 1);

  PopplerAnnot *annot = FirstAnnotFromMapping(mapping);
  ASSERT_NE(annot, nullptr);

  // Remove the existing annot (observable via mapping count).
  poppler_page_remove_annot(page, annot);
  FreeAnnotMapping(mapping);

  mapping = GetAnnotMapping(page);
  ASSERT_NE(mapping, nullptr);
  EXPECT_EQ(MappingLength(mapping), 0);

  // Add it back using the API under test.
  poppler_page_add_annot(page, annot);
  FreeAnnotMapping(mapping);

  mapping = GetAnnotMapping(page);
  ASSERT_NE(mapping, nullptr);
  EXPECT_GE(MappingLength(mapping), 1);

  FreeAnnotMapping(mapping);
  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageAddAnnotTest_2461, RemoveThenAddBackTextMarkupAnnotRestoresPresence_2461) {
  // Exercises the AnnotTextMarkup path (quadrilaterals adjustments) without
  // asserting internal geometry.
  const std::string pdf = BuildPdfWithSingleAnnot(
      /*text_markup=*/true, /*rotated_page=*/false, /*include_crop_box=*/true);
  PopplerDocument *doc = LoadDocFromPdfData(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = GetFirstPage(doc);
  ASSERT_NE(page, nullptr);

  GList *mapping = GetAnnotMapping(page);
  ASSERT_NE(mapping, nullptr);
  EXPECT_EQ(MappingLength(mapping), 1);

  PopplerAnnot *annot = FirstAnnotFromMapping(mapping);
  ASSERT_NE(annot, nullptr);

  poppler_page_remove_annot(page, annot);
  FreeAnnotMapping(mapping);

  mapping = GetAnnotMapping(page);
  ASSERT_NE(mapping, nullptr);
  EXPECT_EQ(MappingLength(mapping), 0);

  poppler_page_add_annot(page, annot);
  FreeAnnotMapping(mapping);

  mapping = GetAnnotMapping(page);
  ASSERT_NE(mapping, nullptr);
  EXPECT_GE(MappingLength(mapping), 1);

  FreeAnnotMapping(mapping);
  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageAddAnnotTest_2461, AddTextMarkupAnnotOnRotatedPageDoesNotCrashAndIsPresent_2461) {
  // Exercises the "page rotated" branch. We only assert observable results.
  const std::string pdf = BuildPdfWithSingleAnnot(
      /*text_markup=*/true, /*rotated_page=*/true, /*include_crop_box=*/true);
  PopplerDocument *doc = LoadDocFromPdfData(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = GetFirstPage(doc);
  ASSERT_NE(page, nullptr);

  GList *mapping = GetAnnotMapping(page);
  ASSERT_NE(mapping, nullptr);
  EXPECT_EQ(MappingLength(mapping), 1);

  PopplerAnnot *annot = FirstAnnotFromMapping(mapping);
  ASSERT_NE(annot, nullptr);

  // Remove then add back; add_annot must cope with rotated pages.
  poppler_page_remove_annot(page, annot);
  FreeAnnotMapping(mapping);

  mapping = GetAnnotMapping(page);
  ASSERT_NE(mapping, nullptr);
  EXPECT_EQ(MappingLength(mapping), 0);

  poppler_page_add_annot(page, annot);
  FreeAnnotMapping(mapping);

  mapping = GetAnnotMapping(page);
  ASSERT_NE(mapping, nullptr);
  EXPECT_GE(MappingLength(mapping), 1);

  FreeAnnotMapping(mapping);
  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageAddAnnotTest_2461, AddSameAnnotTwiceDoesNotRemoveExistingAnnots_2461) {
  // Boundary-ish: calling add twice should not reduce the number of annotations.
  // We avoid assuming whether duplicates are allowed.
  const std::string pdf = BuildPdfWithSingleAnnot(
      /*text_markup=*/false, /*rotated_page=*/false, /*include_crop_box=*/true);
  PopplerDocument *doc = LoadDocFromPdfData(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = GetFirstPage(doc);
  ASSERT_NE(page, nullptr);

  GList *mapping = GetAnnotMapping(page);
  ASSERT_NE(mapping, nullptr);
  EXPECT_EQ(MappingLength(mapping), 1);

  PopplerAnnot *annot = FirstAnnotFromMapping(mapping);
  ASSERT_NE(annot, nullptr);

  poppler_page_remove_annot(page, annot);
  FreeAnnotMapping(mapping);

  mapping = GetAnnotMapping(page);
  ASSERT_NE(mapping, nullptr);
  EXPECT_EQ(MappingLength(mapping), 0);
  FreeAnnotMapping(mapping);

  // Add twice.
  poppler_page_add_annot(page, annot);
  mapping = GetAnnotMapping(page);
  ASSERT_NE(mapping, nullptr);
  const int after_first = MappingLength(mapping);
  EXPECT_GE(after_first, 1);
  FreeAnnotMapping(mapping);

  poppler_page_add_annot(page, annot);
  mapping = GetAnnotMapping(page);
  ASSERT_NE(mapping, nullptr);
  const int after_second = MappingLength(mapping);

  // Must not decrease.
  EXPECT_GE(after_second, after_first);

  FreeAnnotMapping(mapping);
  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageAddAnnotTest_2461, AddAnnotWithNoCropBoxStillWorks_2461) {
  // Boundary condition: no explicit CropBox (CropBox == MediaBox typically).
  const std::string pdf = BuildPdfWithSingleAnnot(
      /*text_markup=*/true, /*rotated_page=*/false, /*include_crop_box=*/false);
  PopplerDocument *doc = LoadDocFromPdfData(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = GetFirstPage(doc);
  ASSERT_NE(page, nullptr);

  GList *mapping = GetAnnotMapping(page);
  ASSERT_NE(mapping, nullptr);
  EXPECT_EQ(MappingLength(mapping), 1);

  PopplerAnnot *annot = FirstAnnotFromMapping(mapping);
  ASSERT_NE(annot, nullptr);

  poppler_page_remove_annot(page, annot);
  FreeAnnotMapping(mapping);

  mapping = GetAnnotMapping(page);
  ASSERT_NE(mapping, nullptr);
  EXPECT_EQ(MappingLength(mapping), 0);

  poppler_page_add_annot(page, annot);
  FreeAnnotMapping(mapping);

  mapping = GetAnnotMapping(page);
  ASSERT_NE(mapping, nullptr);
  EXPECT_GE(MappingLength(mapping), 1);

  FreeAnnotMapping(mapping);
  g_object_unref(page);
  g_object_unref(doc);
}

} // namespace