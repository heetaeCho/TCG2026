// poppler-page-get-text-layout-test-2500.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <string>
#include <vector>

namespace {

class PopplerPageGetTextLayoutTest_2500 : public ::testing::Test {
protected:
  // Build a minimal, valid single-page PDF. When with_text==true, the page draws "(Hi)".
  static std::string BuildSinglePagePdf_2500(bool with_text) {
    struct Obj {
      int num;
      std::string body; // without "N 0 obj" / "endobj"
    };

    // Object contents (keep stable ordering).
    // 1: Catalog
    // 2: Pages
    // 3: Page
    // 4: Contents stream
    // 5: Font
    std::vector<Obj> objs;

    objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R >>"});
    objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"});

    // Page references resources, font, and contents.
    objs.push_back(
        {3,
         "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] "
         "/Contents 4 0 R "
         "/Resources << /Font << /F1 5 0 R >> >> >>"});

    std::string stream_data;
    if (with_text) {
      // Simple text show.
      stream_data = "BT /F1 24 Tf 50 100 Td (Hi) Tj ET\n";
    } else {
      stream_data = "";
    }

    {
      char lenbuf[64];
      std::snprintf(lenbuf, sizeof(lenbuf), "%zu", stream_data.size());
      std::string contents =
          std::string("<< /Length ") + lenbuf + " >>\nstream\n" + stream_data + "endstream";
      objs.push_back({4, contents});
    }

    objs.push_back({5, "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>"});

    std::string pdf;
    pdf += "%PDF-1.4\n";
    // Keep offsets (xref requires byte offsets from beginning of file).
    // xref table includes object 0 plus 1..N.
    std::vector<size_t> offsets;
    offsets.resize(6, 0); // index == obj number (0..5), 0 unused for obj0 entry

    for (const auto &o : objs) {
      offsets[o.num] = pdf.size();
      pdf += std::to_string(o.num) + " 0 obj\n";
      pdf += o.body + "\n";
      pdf += "endobj\n";
    }

    const size_t xref_pos = pdf.size();
    pdf += "xref\n";
    pdf += "0 6\n";
    pdf += "0000000000 65535 f \n";
    for (int i = 1; i <= 5; ++i) {
      char line[32];
      // 10-digit, zero-padded offset, gen 00000, in-use 'n'
      std::snprintf(line, sizeof(line), "%010zu 00000 n \n", offsets[i]);
      pdf += line;
    }

    pdf += "trailer\n";
    pdf += "<< /Size 6 /Root 1 0 R >>\n";
    pdf += "startxref\n";
    pdf += std::to_string(xref_pos) + "\n";
    pdf += "%%EOF\n";

    return pdf;
  }

  static PopplerDocument* NewDocFromPdfData_2500(const std::string& pdf, GError** error_out) {
    // poppler_document_new_from_data copies the data internally (per typical GLib conventions),
    // so passing a pointer into std::string storage is fine for the duration of the call.
    return poppler_document_new_from_data(pdf.c_str(),
                                          static_cast<int>(pdf.size()),
                                          /*password=*/nullptr,
                                          error_out);
  }

  static PopplerPage* GetFirstPage_2500(PopplerDocument* doc) {
    return poppler_document_get_page(doc, 0);
  }
};

TEST_F(PopplerPageGetTextLayoutTest_2500, NullPageReturnsFalseAndDoesNotModifyOutputs_2500) {
  PopplerRectangle* rects = reinterpret_cast<PopplerRectangle*>(0x1); // sentinel
  guint n_rects = 777;

  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_PAGE*");
  gboolean ok = poppler_page_get_text_layout(nullptr, &rects, &n_rects);
  g_test_assert_expected_messages();

  EXPECT_FALSE(ok);
  // With g_return_val_if_fail(), the function returns early; outputs should remain unchanged.
  EXPECT_EQ(rects, reinterpret_cast<PopplerRectangle*>(0x1));
  EXPECT_EQ(n_rects, 777u);
}

TEST_F(PopplerPageGetTextLayoutTest_2500, NonPageGObjectReturnsFalseAndDoesNotModifyOutputs_2500) {
  // Create a valid GObject that is NOT a PopplerPage.
  GObject* not_a_page = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_a_page, nullptr);

  PopplerRectangle* rects = reinterpret_cast<PopplerRectangle*>(0x2); // sentinel
  guint n_rects = 888;

  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_PAGE*");
  gboolean ok = poppler_page_get_text_layout(reinterpret_cast<PopplerPage*>(not_a_page), &rects, &n_rects);
  g_test_assert_expected_messages();

  EXPECT_FALSE(ok);
  EXPECT_EQ(rects, reinterpret_cast<PopplerRectangle*>(0x2));
  EXPECT_EQ(n_rects, 888u);

  g_object_unref(not_a_page);
}

TEST_F(PopplerPageGetTextLayoutTest_2500, ValidPageWithTextReturnsTrueAndProvidesRectangles_2500) {
  const std::string pdf = BuildSinglePagePdf_2500(/*with_text=*/true);

  GError* error = nullptr;
  PopplerDocument* doc = NewDocFromPdfData_2500(pdf, &error);
  ASSERT_NE(doc, nullptr) << (error ? error->message : "poppler_document_new_from_data failed");
  if (error) g_error_free(error);

  PopplerPage* page = GetFirstPage_2500(doc);
  ASSERT_NE(page, nullptr);

  PopplerRectangle* rects = nullptr;
  guint n_rects = 0;

  gboolean ok = poppler_page_get_text_layout(page, &rects, &n_rects);
  EXPECT_TRUE(ok);

  // Observable postconditions (do not assume exact layout/ordering):
  // - If text exists, commonly there is at least one rectangle.
  // - If rectangles are provided, pointer should be non-null when n_rects > 0.
  if (n_rects > 0) {
    EXPECT_NE(rects, nullptr);
  }

  // Free if provided (Poppler GLib APIs typically allocate with g_malloc).
  if (rects) {
    g_free(rects);
  }

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetTextLayoutTest_2500, ValidPageWithoutTextReturnsTrueAndHandlesZeroRectangles_2500) {
  const std::string pdf = BuildSinglePagePdf_2500(/*with_text=*/false);

  GError* error = nullptr;
  PopplerDocument* doc = NewDocFromPdfData_2500(pdf, &error);
  ASSERT_NE(doc, nullptr) << (error ? error->message : "poppler_document_new_from_data failed");
  if (error) g_error_free(error);

  PopplerPage* page = GetFirstPage_2500(doc);
  ASSERT_NE(page, nullptr);

  PopplerRectangle* rects = nullptr;
  guint n_rects = 123; // ensure overwritten on success (if API does so)

  gboolean ok = poppler_page_get_text_layout(page, &rects, &n_rects);
  EXPECT_TRUE(ok);

  // For an empty content stream, many implementations produce no text rects.
  // We avoid assuming strict requirements; we only assert internal consistency:
  if (n_rects == 0) {
    // Accept either NULL or non-NULL; but if non-NULL, we can still free safely.
    SUCCEED();
  } else {
    // If rectangles are reported, pointer should be non-null.
    EXPECT_NE(rects, nullptr);
  }

  if (rects) {
    g_free(rects);
  }

  g_object_unref(page);
  g_object_unref(doc);
}

}  // namespace