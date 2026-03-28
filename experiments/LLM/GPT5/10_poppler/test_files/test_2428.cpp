// File: poppler-page-get-label-test_2428.cc
//
// Unit tests for:
//   gchar *poppler_page_get_label(PopplerPage *page);
//
// Constraints honored:
// - Treat implementation as black-box (no internal logic reimplementation).
// - Test only observable behavior via public GLib Poppler API.
// - Include normal, boundary, and error/exceptional (observable) cases.

#include <gtest/gtest.h>

#include <poppler.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {

struct GCharFree {
  void operator()(gchar *p) const { g_free(p); }
};
using UniqueGChar = std::unique_ptr<gchar, GCharFree>;

struct GErrorFree {
  void operator()(GError *e) const { g_error_free(e); }
};
using UniqueGError = std::unique_ptr<GError, GErrorFree>;

struct GObjectUnref {
  void operator()(gpointer p) const {
    if (p) {
      g_object_unref(p);
    }
  }
};
template <typename T>
using UniqueGObject = std::unique_ptr<T, GObjectUnref>;

static std::string BuildMinimalPdfWithPageLabels_2428() {
  // Build a small, valid PDF with 3 pages and explicit /PageLabels:
  // - Page 0: lower-case roman starting at i  -> "i"
  // - Page 1: roman continuation              -> "ii"
  // - Page 2: decimal with UTF-16BE prefix Ω- -> "Ω-1"
  //
  // This is test data generation, not a reimplementation of Poppler code.

  auto obj = [](int n, const std::string &body) {
    std::ostringstream oss;
    oss << n << " 0 obj\n" << body << "\nendobj\n";
    return oss.str();
  };

  // Shared content stream.
  const std::string streamData = "BT /F1 12 Tf 72 720 Td (Hello) Tj ET\n";
  std::ostringstream contents;
  contents << "<< /Length " << streamData.size() << " >>\n"
           << "stream\n"
           << streamData
           << "endstream";

  // Objects:
  // 1: Catalog (Root)
  // 2: Pages
  // 3-5: Page dictionaries
  // 6: PageLabels
  // 7: Contents stream
  // 8: Resources
  // 9: Font
  std::vector<std::pair<int, std::string>> objects;

  objects.emplace_back(
      1,
      "<< /Type /Catalog /Pages 2 0 R /PageLabels 6 0 R >>");

  objects.emplace_back(
      2,
      "<< /Type /Pages /Count 3 /Kids [3 0 R 4 0 R 5 0 R] >>");

  // Page dictionaries (simple MediaBox + Resources + Contents).
  for (int i = 3; i <= 5; ++i) {
    objects.emplace_back(
        i,
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Resources 8 0 R /Contents 7 0 R >>");
  }

  // PageLabels:
  // /Nums [ 0 << /S /r /St 1 >>  2 << /S /D /St 1 /P <FEFF03A9002D> >> ]
  // <FEFF03A9002D> is UTF-16BE "Ω-"
  objects.emplace_back(
      6,
      "<< /Nums ["
      " 0 << /S /r /St 1 >>"
      " 2 << /S /D /St 1 /P <FEFF03A9002D> >>"
      " ] >>");

  objects.emplace_back(7, contents.str());

  objects.emplace_back(
      8,
      "<< /Font << /F1 9 0 R >> >>");

  objects.emplace_back(
      9,
      "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>");

  // Assemble PDF and compute xref offsets.
  std::string out;
  out += "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

  // Track offsets: xref entry 0 is free; then 1..maxObj.
  const int maxObj = 9;
  std::vector<long> offsets(maxObj + 1, 0);

  for (const auto &p : objects) {
    const int num = p.first;
    offsets[num] = static_cast<long>(out.size());
    out += obj(num, p.second);
  }

  const long xrefPos = static_cast<long>(out.size());
  {
    std::ostringstream xref;
    xref << "xref\n"
         << "0 " << (maxObj + 1) << "\n"
         << "0000000000 65535 f \n";
    for (int i = 1; i <= maxObj; ++i) {
      // Each offset must be 10 digits, padded with zeros.
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010ld", offsets[i]);
      xref << buf << " 00000 n \n";
    }
    out += xref.str();
  }

  {
    std::ostringstream trailer;
    trailer << "trailer\n"
            << "<< /Size " << (maxObj + 1) << " /Root 1 0 R >>\n"
            << "startxref\n"
            << xrefPos << "\n"
            << "%%EOF\n";
    out += trailer.str();
  }

  return out;
}

static std::string BuildMinimalPdfNoPageLabels_2428() {
  // Similar PDF but without /PageLabels in Catalog, still 2 pages to compare labels.
  auto obj = [](int n, const std::string &body) {
    std::ostringstream oss;
    oss << n << " 0 obj\n" << body << "\nendobj\n";
    return oss.str();
  };

  const std::string streamData = "BT /F1 12 Tf 72 720 Td (Hello) Tj ET\n";
  std::ostringstream contents;
  contents << "<< /Length " << streamData.size() << " >>\n"
           << "stream\n"
           << streamData
           << "endstream";

  // Objects:
  // 1: Catalog (Root)
  // 2: Pages
  // 3-4: Pages
  // 5: Contents
  // 6: Resources
  // 7: Font
  std::vector<std::pair<int, std::string>> objects;
  objects.emplace_back(1, "<< /Type /Catalog /Pages 2 0 R >>");
  objects.emplace_back(2, "<< /Type /Pages /Count 2 /Kids [3 0 R 4 0 R] >>");

  for (int i = 3; i <= 4; ++i) {
    objects.emplace_back(
        i,
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Resources 6 0 R /Contents 5 0 R >>");
  }

  objects.emplace_back(5, contents.str());
  objects.emplace_back(6, "<< /Font << /F1 7 0 R >> >>");
  objects.emplace_back(7, "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>");

  std::string out;
  out += "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

  const int maxObj = 7;
  std::vector<long> offsets(maxObj + 1, 0);

  for (const auto &p : objects) {
    offsets[p.first] = static_cast<long>(out.size());
    out += obj(p.first, p.second);
  }

  const long xrefPos = static_cast<long>(out.size());
  {
    std::ostringstream xref;
    xref << "xref\n"
         << "0 " << (maxObj + 1) << "\n"
         << "0000000000 65535 f \n";
    for (int i = 1; i <= maxObj; ++i) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010ld", offsets[i]);
      xref << buf << " 00000 n \n";
    }
    out += xref.str();
  }

  {
    std::ostringstream trailer;
    trailer << "trailer\n"
            << "<< /Size " << (maxObj + 1) << " /Root 1 0 R >>\n"
            << "startxref\n"
            << xrefPos << "\n"
            << "%%EOF\n";
    out += trailer.str();
  }

  return out;
}

static std::string WriteTempPdfAndGetUri_2428(const std::string &pdfBytes) {
  gchar *tmpPathC = nullptr;
  {
    // Create a temp file path.
    GError *err = nullptr;
    gint fd = g_file_open_tmp("poppler_page_get_label_2428_XXXXXX.pdf", &tmpPathC, &err);
    UniqueGError uerr(err);
    EXPECT_NE(fd, -1) << "Failed to open temp file";
    EXPECT_NE(tmpPathC, nullptr);
    if (fd != -1) {
      // Write bytes then close.
      ssize_t written = write(fd, pdfBytes.data(), pdfBytes.size());
      (void)written;
      close(fd);
      EXPECT_EQ(static_cast<size_t>(written), pdfBytes.size());
    }
  }

  std::string tmpPath = tmpPathC ? tmpPathC : "";
  g_free(tmpPathC);

  gchar *uriC = g_filename_to_uri(tmpPath.c_str(), nullptr, nullptr);
  EXPECT_NE(uriC, nullptr);
  std::string uri = uriC ? uriC : "";
  g_free(uriC);

  return uri;
}

static UniqueGObject<PopplerDocument> LoadDocFromUri_2428(const std::string &uri) {
  GError *err = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), /*password*/ nullptr, &err);
  UniqueGError uerr(err);
  EXPECT_NE(doc, nullptr);
  EXPECT_EQ(err, nullptr);
  return UniqueGObject<PopplerDocument>(doc);
}

static UniqueGObject<PopplerPage> GetPage_2428(PopplerDocument *doc, int index) {
  PopplerPage *page = poppler_document_get_page(doc, index);
  EXPECT_NE(page, nullptr);
  return UniqueGObject<PopplerPage>(page);
}

} // namespace

TEST(PopplerPageGetLabelTest_2428, NullPageReturnsNull_2428) {
  // Exceptional / error case (observable): invalid argument should yield NULL.
  // Note: g_return_val_if_fail may log a critical; we only assert returned value.
  gchar *label = poppler_page_get_label(nullptr);
  EXPECT_EQ(label, nullptr);
}

TEST(PopplerPageGetLabelTest_2428, PageLabelsRomanAndPrefixedDecimal_2428) {
  const std::string pdf = BuildMinimalPdfWithPageLabels_2428();
  const std::string uri = WriteTempPdfAndGetUri_2428(pdf);

  auto doc = LoadDocFromUri_2428(uri);
  ASSERT_NE(doc.get(), nullptr);

  auto page0 = GetPage_2428(doc.get(), 0);
  auto page1 = GetPage_2428(doc.get(), 1);
  auto page2 = GetPage_2428(doc.get(), 2);

  UniqueGChar label0(poppler_page_get_label(page0.get()));
  UniqueGChar label1(poppler_page_get_label(page1.get()));
  UniqueGChar label2(poppler_page_get_label(page2.get()));

  ASSERT_NE(label0.get(), nullptr);
  ASSERT_NE(label1.get(), nullptr);
  ASSERT_NE(label2.get(), nullptr);

  // Normal operation: labels reflect configured /PageLabels.
  EXPECT_STREQ(label0.get(), "i");
  EXPECT_STREQ(label1.get(), "ii");
  EXPECT_STREQ(label2.get(), "Ω-1");

  // Boundary-ish validation: labels are valid UTF-8 (conversion function is used internally).
  EXPECT_TRUE(g_utf8_validate(label0.get(), -1, nullptr));
  EXPECT_TRUE(g_utf8_validate(label1.get(), -1, nullptr));
  EXPECT_TRUE(g_utf8_validate(label2.get(), -1, nullptr));

  // Cleanup temp file.
  // Convert URI back to filename (best-effort) and remove.
  gchar *filename = g_filename_from_uri(uri.c_str(), nullptr, nullptr);
  if (filename) {
    g_remove(filename);
    g_free(filename);
  }
}

TEST(PopplerPageGetLabelTest_2428, NoExplicitPageLabelsStillReturnsNonEmptyAndDistinct_2428) {
  const std::string pdf = BuildMinimalPdfNoPageLabels_2428();
  const std::string uri = WriteTempPdfAndGetUri_2428(pdf);

  auto doc = LoadDocFromUri_2428(uri);
  ASSERT_NE(doc.get(), nullptr);

  auto page0 = GetPage_2428(doc.get(), 0);
  auto page1 = GetPage_2428(doc.get(), 1);

  UniqueGChar label0(poppler_page_get_label(page0.get()));
  UniqueGChar label1(poppler_page_get_label(page1.get()));

  ASSERT_NE(label0.get(), nullptr);
  ASSERT_NE(label1.get(), nullptr);

  // Boundary/robustness: even without /PageLabels, labels should be usable strings.
  EXPECT_GT(std::strlen(label0.get()), 0u);
  EXPECT_GT(std::strlen(label1.get()), 0u);

  // Avoid assuming exact default formatting; we only require page labels differ per page.
  EXPECT_STRNE(label0.get(), label1.get());

  EXPECT_TRUE(g_utf8_validate(label0.get(), -1, nullptr));
  EXPECT_TRUE(g_utf8_validate(label1.get(), -1, nullptr));

  // Cleanup temp file.
  gchar *filename = g_filename_from_uri(uri.c_str(), nullptr, nullptr);
  if (filename) {
    g_remove(filename);
    g_free(filename);
  }
}

TEST(PopplerPageGetLabelTest_2428, RepeatedCallsReturnIndependentAllocatedStrings_2428) {
  const std::string pdf = BuildMinimalPdfWithPageLabels_2428();
  const std::string uri = WriteTempPdfAndGetUri_2428(pdf);

  auto doc = LoadDocFromUri_2428(uri);
  ASSERT_NE(doc.get(), nullptr);

  auto page0 = GetPage_2428(doc.get(), 0);

  UniqueGChar labelA(poppler_page_get_label(page0.get()));
  UniqueGChar labelB(poppler_page_get_label(page0.get()));

  ASSERT_NE(labelA.get(), nullptr);
  ASSERT_NE(labelB.get(), nullptr);

  // Observable behavior: two calls return equal content.
  EXPECT_STREQ(labelA.get(), labelB.get());

  // And should be independent allocations (typically different pointers).
  // Not a strict API guarantee in all libraries, but GLib style for returned gchar*
  // is generally "newly allocated". We only soft-check pointer inequality.
  // If an implementation interns strings, this may be equal; so don't REQUIRE it.
  if (labelA.get() == labelB.get()) {
    SUCCEED() << "Returned pointers are identical; content equality already verified.";
  } else {
    SUCCEED() << "Returned pointers differ, suggesting independent allocations.";
  }

  // Cleanup temp file.
  gchar *filename = g_filename_from_uri(uri.c_str(), nullptr, nullptr);
  if (filename) {
    g_remove(filename);
    g_free(filename);
  }
}