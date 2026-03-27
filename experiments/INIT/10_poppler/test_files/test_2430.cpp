// poppler-page-get-transition-test-2430.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

namespace {

class PopplerPageGetTransitionTest_2430 : public ::testing::Test {
protected:
  static void ExpectCriticalAndNull(PopplerPage *page) {
    // g_return_val_if_fail() logs a CRITICAL message; in some environments it can be fatal.
    // Use GLib's test log facilities to expect and swallow it.
    g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*");
    PopplerPageTransition *t = poppler_page_get_transition(page);
    EXPECT_EQ(t, nullptr);
    g_test_assert_expected_messages();
  }

  static std::string BuildMinimalPdfWithOptionalTrans(const std::string &trans_entry) {
    // A minimal, valid PDF with one page. Optionally inject a /Trans dictionary on the page object.
    // Objects:
    // 1: Catalog
    // 2: Pages
    // 3: Page (includes optional /Trans)
    // 4: Contents (empty stream)
    std::vector<std::string> objs;

    objs.emplace_back("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");
    objs.emplace_back("2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");

    std::ostringstream page;
    page << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] "
            "/Resources <<>> /Contents 4 0 R ";
    if (!trans_entry.empty()) {
      page << trans_entry << " ";
    }
    page << ">>\nendobj\n";
    objs.push_back(page.str());

    // Empty contents stream
    objs.emplace_back("4 0 obj\n<< /Length 0 >>\nstream\n\nendstream\nendobj\n");

    // Assemble with xref
    std::ostringstream pdf;
    pdf << "%PDF-1.5\n%\xE2\xE3\xCF\xD3\n"; // binary comment
    std::vector<long> offsets;
    offsets.reserve(objs.size() + 1);
    offsets.push_back(0); // object 0 (free), special

    for (const auto &o : objs) {
      offsets.push_back(static_cast<long>(pdf.tellp()));
      pdf << o;
    }

    const long xref_pos = static_cast<long>(pdf.tellp());
    pdf << "xref\n0 " << (objs.size() + 1) << "\n";
    pdf << "0000000000 65535 f \n";
    for (size_t i = 1; i < offsets.size(); ++i) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010ld", offsets[i]);
      pdf << buf << " 00000 n \n";
    }

    pdf << "trailer\n<< /Size " << (objs.size() + 1) << " /Root 1 0 R >>\n";
    pdf << "startxref\n" << xref_pos << "\n%%EOF\n";

    return pdf.str();
  }

  static std::string WriteTempPdfAndReturnUri(const std::string &pdf_bytes) {
    gchar *tmp_path = nullptr;
    gint fd = g_file_open_tmp("poppler-transition-2430-XXXXXX.pdf", &tmp_path, nullptr);
    EXPECT_GE(fd, 0);
    EXPECT_NE(tmp_path, nullptr);

    // Close fd and write via fstream for simplicity.
    if (fd >= 0) {
      close(fd);
    }

    {
      std::ofstream out(tmp_path, std::ios::binary);
      EXPECT_TRUE(out.good());
      out.write(pdf_bytes.data(), static_cast<std::streamsize>(pdf_bytes.size()));
      out.close();
      EXPECT_TRUE(out.good());
    }

    gchar *uri = g_filename_to_uri(tmp_path, nullptr, nullptr);
    EXPECT_NE(uri, nullptr);

    std::string uri_str(uri);
    g_free(uri);
    g_free(tmp_path);
    return uri_str;
  }

  template <typename FieldT, typename ValueT>
  static void ExpectFieldEquals(FieldT field, ValueT expected) {
    if constexpr (std::is_floating_point_v<std::remove_reference_t<FieldT>> ||
                  std::is_floating_point_v<std::remove_reference_t<ValueT>>) {
      EXPECT_DOUBLE_EQ(static_cast<double>(field), static_cast<double>(expected));
    } else {
      EXPECT_EQ(field, static_cast<std::remove_reference_t<FieldT>>(expected));
    }
  }
};

TEST_F(PopplerPageGetTransitionTest_2430, NullPage_ReturnsNullAndLogsCritical_2430) {
  ExpectCriticalAndNull(nullptr);
}

TEST_F(PopplerPageGetTransitionTest_2430, NonPagePointer_ReturnsNullAndLogsCritical_2430) {
  // Pass a non-PopplerPage object casted to PopplerPage* to trigger POPPLER_IS_PAGE failure.
  GObject *obj = g_object_new(G_TYPE_OBJECT, nullptr);
  ASSERT_NE(obj, nullptr);

  ExpectCriticalAndNull(reinterpret_cast<PopplerPage *>(obj));

  g_object_unref(obj);
}

TEST_F(PopplerPageGetTransitionTest_2430, PageWithoutTrans_ReturnsNull_2430) {
  const std::string pdf = BuildMinimalPdfWithOptionalTrans(/*trans_entry=*/"");
  const std::string uri = WriteTempPdfAndReturnUri(pdf);

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
  ASSERT_NE(doc, nullptr);
  ASSERT_EQ(error, nullptr);

  PopplerPage *page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  PopplerPageTransition *transition = poppler_page_get_transition(page);
  EXPECT_EQ(transition, nullptr);

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetTransitionTest_2430, FadeTransition_MapsTypeAndFields_2430) {
  // /Trans dictionary (PDF): /S /Fade, /D duration
  // We only assert fields that are observable through the returned struct.
  const std::string trans = "/Trans << /S /Fade /D 2 >>";
  const std::string pdf = BuildMinimalPdfWithOptionalTrans(trans);
  const std::string uri = WriteTempPdfAndReturnUri(pdf);

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  ASSERT_NE(doc, nullptr);
  ASSERT_EQ(error, nullptr);

  PopplerPage *page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  PopplerPageTransition *t = poppler_page_get_transition(page);
  ASSERT_NE(t, nullptr);

  EXPECT_EQ(t->type, POPPLER_PAGE_TRANSITION_FADE);

  // Duration is set from PageTransition::getDuration(); also copied into duration_real.
  // In some Poppler versions duration/duration_real are doubles; in others duration_real may be int.
  ExpectFieldEquals(t->duration_real, 2);

  // Clean up. PopplerPageTransition is typically a boxed/heap struct; g_free is safe for plain alloc.
  g_free(t);
  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetTransitionTest_2430, SplitHorizontalInward_MapsAlignmentAndDirection_2430) {
  // For Split transitions, PDF typically uses:
  //  /S /Split
  //  /Dm /H or /V
  //  /M /I or /O
  //  /D duration
  const std::string trans = "/Trans << /S /Split /Dm /H /M /I /D 1 >>";
  const std::string pdf = BuildMinimalPdfWithOptionalTrans(trans);
  const std::string uri = WriteTempPdfAndReturnUri(pdf);

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  ASSERT_NE(doc, nullptr);
  ASSERT_EQ(error, nullptr);

  PopplerPage *page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  PopplerPageTransition *t = poppler_page_get_transition(page);
  ASSERT_NE(t, nullptr);

  EXPECT_EQ(t->type, POPPLER_PAGE_TRANSITION_SPLIT);
  EXPECT_EQ(t->alignment, POPPLER_PAGE_TRANSITION_HORIZONTAL);
  EXPECT_EQ(t->direction, POPPLER_PAGE_TRANSITION_INWARD);
  ExpectFieldEquals(t->duration_real, 1);

  g_free(t);
  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetTransitionTest_2430, DurationZero_Boundary_IsPropagated_2430) {
  const std::string trans = "/Trans << /S /Replace /D 0 >>";
  const std::string pdf = BuildMinimalPdfWithOptionalTrans(trans);
  const std::string uri = WriteTempPdfAndReturnUri(pdf);

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  ASSERT_NE(doc, nullptr);
  ASSERT_EQ(error, nullptr);

  PopplerPage *page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  PopplerPageTransition *t = poppler_page_get_transition(page);
  ASSERT_NE(t, nullptr);

  EXPECT_EQ(t->type, POPPLER_PAGE_TRANSITION_REPLACE);
  ExpectFieldEquals(t->duration_real, 0);

  g_free(t);
  g_object_unref(page);
  g_object_unref(doc);
}

} // namespace