// poppler_page_get_text_attributes_for_area_test_2504.cc
#include <gtest/gtest.h>

#include <poppler.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <cerrno>
#include <cstring>
#include <string>
#include <vector>

namespace {

struct TempPdfFile {
  std::string path;  // local filesystem path
  std::string uri;   // file:// URI
};

static std::string BuildMinimalSinglePagePdfWithText(const std::string &text) {
  // Build a minimal PDF with one page and one content stream rendering `text`.
  // Offsets for xref are computed dynamically.
  //
  // Objects:
  // 1 0 obj: Catalog
  // 2 0 obj: Pages
  // 3 0 obj: Page
  // 4 0 obj: Font (Helvetica)
  // 5 0 obj: Contents stream

  auto EscapePdfString = [](const std::string &s) {
    std::string out;
    out.reserve(s.size());
    for (char c : s) {
      if (c == '\\' || c == '(' || c == ')') out.push_back('\\');
      out.push_back(c);
    }
    return out;
  };

  const std::string escaped = EscapePdfString(text);
  const std::string contents =
      "BT\n"
      "/F1 24 Tf\n"
      "72 720 Td\n"
      "(" +
      escaped +
      ") Tj\n"
      "ET\n";

  std::vector<std::string> objs;
  objs.reserve(6);

  // Dummy to make indices align with object numbers.
  objs.push_back("");

  objs.push_back(
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n");

  objs.push_back(
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n");

  objs.push_back(
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R\n"
      "   /MediaBox [0 0 612 792]\n"
      "   /Resources << /Font << /F1 4 0 R >> >>\n"
      "   /Contents 5 0 R\n"
      ">>\n"
      "endobj\n");

  objs.push_back(
      "4 0 obj\n"
      "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
      "endobj\n");

  // Stream object with explicit length
  const std::string stream =
      "5 0 obj\n"
      "<< /Length " +
      std::to_string(contents.size()) +
      " >>\n"
      "stream\n" +
      contents +
      "endstream\n"
      "endobj\n";
  objs.push_back(stream);

  std::string pdf;
  pdf.reserve(2048);

  pdf += "%PDF-1.4\n";
  std::vector<long> offsets(6, 0);

  for (int i = 1; i <= 5; ++i) {
    offsets[i] = static_cast<long>(pdf.size());
    pdf += objs[i];
  }

  const long xref_offset = static_cast<long>(pdf.size());

  pdf += "xref\n";
  pdf += "0 6\n";
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i <= 5; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    pdf += buf;
  }

  pdf += "trailer\n";
  pdf += "<< /Size 6 /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_offset);
  pdf += "\n%%EOF\n";

  return pdf;
}

static TempPdfFile WriteTempPdfOrDie(const std::string &pdf_bytes) {
  GError *err = nullptr;
  gchar *tmp_name = nullptr;

  int fd = g_file_open_tmp("poppler_text_attrs_XXXXXX.pdf", &tmp_name, &err);
  if (fd == -1) {
    std::string msg = "g_file_open_tmp failed: ";
    msg += (err && err->message) ? err->message : "unknown";
    if (err) g_error_free(err);
    ADD_FAILURE() << msg;
    return {};
  }

  ssize_t total = 0;
  const char *data = pdf_bytes.data();
  const ssize_t len = static_cast<ssize_t>(pdf_bytes.size());
  while (total < len) {
    const ssize_t w = ::write(fd, data + total, static_cast<size_t>(len - total));
    if (w < 0) {
      int e = errno;
      ::close(fd);
      g_unlink(tmp_name);
      std::string msg = "write() failed: ";
      msg += std::strerror(e);
      g_free(tmp_name);
      ADD_FAILURE() << msg;
      return {};
    }
    total += w;
  }
  ::close(fd);

  gchar *uri_c = g_filename_to_uri(tmp_name, /*hostname=*/nullptr, &err);
  if (!uri_c) {
    std::string msg = "g_filename_to_uri failed: ";
    msg += (err && err->message) ? err->message : "unknown";
    if (err) g_error_free(err);
    g_unlink(tmp_name);
    g_free(tmp_name);
    ADD_FAILURE() << msg;
    return {};
  }

  TempPdfFile out;
  out.path = tmp_name;
  out.uri = uri_c;

  g_free(uri_c);
  g_free(tmp_name);
  return out;
}

static void FreeTextAttributesList(GList *list) {
  if (!list) return;

  // PopplerTextAttributes is a boxed type in poppler-glib; free function exists.
  g_list_free_full(list, reinterpret_cast<GDestroyNotify>(poppler_text_attributes_free));
}

}  // namespace

class PopplerPageGetTextAttributesForAreaTest_2504 : public ::testing::Test {
 protected:
  void SetUp() override {
    const std::string pdf = BuildMinimalSinglePagePdfWithText("Hello");
    tmp_ = WriteTempPdfOrDie(pdf);
    ASSERT_FALSE(tmp_.path.empty());
    ASSERT_FALSE(tmp_.uri.empty());

    GError *err = nullptr;
    doc_ = poppler_document_new_from_file(tmp_.uri.c_str(), /*password=*/nullptr, &err);
    ASSERT_NE(doc_, nullptr) << (err && err->message ? err->message : "poppler_document_new_from_file failed");
    if (err) g_error_free(err);

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);
  }

  void TearDown() override {
    if (page_) g_object_unref(page_);
    if (doc_) g_object_unref(doc_);

    if (!tmp_.path.empty()) {
      g_unlink(tmp_.path.c_str());
    }
  }

  TempPdfFile tmp_;
  PopplerDocument *doc_ = nullptr;
  PopplerPage *page_ = nullptr;
};

TEST_F(PopplerPageGetTextAttributesForAreaTest_2504, NullPageReturnsNull_2504) {
  PopplerRectangle area;
  area.x1 = 0;
  area.y1 = 0;
  area.x2 = 612;
  area.y2 = 792;

  GList *attrs = poppler_page_get_text_attributes_for_area(nullptr, &area);
  EXPECT_EQ(attrs, nullptr);
}

TEST_F(PopplerPageGetTextAttributesForAreaTest_2504, NullAreaReturnsNull_2504) {
  GList *attrs = poppler_page_get_text_attributes_for_area(page_, nullptr);
  EXPECT_EQ(attrs, nullptr);
}

TEST_F(PopplerPageGetTextAttributesForAreaTest_2504, AreaWithNoSelectedWordsReturnsNull_2504) {
  // Pick a rectangle far outside the page area to (typically) select nothing.
  PopplerRectangle area;
  area.x1 = -10000;
  area.y1 = -10000;
  area.x2 = -9000;
  area.y2 = -9000;

  GList *attrs = poppler_page_get_text_attributes_for_area(page_, &area);
  EXPECT_EQ(attrs, nullptr);
}

TEST_F(PopplerPageGetTextAttributesForAreaTest_2504, FullPageAreaReturnsNonEmptyListWithSaneIndices_2504) {
  PopplerRectangle area;
  area.x1 = 0;
  area.y1 = 0;
  area.x2 = 612;
  area.y2 = 792;

  GList *attrs = poppler_page_get_text_attributes_for_area(page_, &area);
  ASSERT_NE(attrs, nullptr);

  // Observable behavior: returned list elements should be PopplerTextAttributes with indices.
  // We only assert index monotonicity / sanity (black-box safe).
  int last_start = -1;
  int last_end = -1;
  int count = 0;

  for (GList *l = attrs; l; l = l->next) {
    auto *a = static_cast<PopplerTextAttributes *>(l->data);
    ASSERT_NE(a, nullptr);

    EXPECT_GE(a->start_index, 0);
    EXPECT_GE(a->end_index, 0);
    EXPECT_LE(a->start_index, a->end_index);

    // Since the function reverses a prepend-built list, start_index should be non-decreasing.
    EXPECT_GE(a->start_index, last_start);
    // end_index should also be non-decreasing overall in typical segmentation.
    EXPECT_GE(a->end_index, last_end);

    last_start = a->start_index;
    last_end = a->end_index;
    ++count;
  }

  EXPECT_GT(count, 0);

  FreeTextAttributesList(attrs);
}

TEST_F(PopplerPageGetTextAttributesForAreaTest_2504, DegenerateZeroSizedAreaDoesNotCrash_2504) {
  // Boundary condition: zero-sized rectangle.
  PopplerRectangle area;
  area.x1 = 72;
  area.y1 = 720;
  area.x2 = 72;
  area.y2 = 720;

  GList *attrs = poppler_page_get_text_attributes_for_area(page_, &area);

  // Black-box friendly: accept either nullptr (no selection) or a non-null list,
  // but if non-null, it should contain sane indices.
  if (attrs) {
    for (GList *l = attrs; l; l = l->next) {
      auto *a = static_cast<PopplerTextAttributes *>(l->data);
      ASSERT_NE(a, nullptr);
      EXPECT_GE(a->start_index, 0);
      EXPECT_GE(a->end_index, 0);
      EXPECT_LE(a->start_index, a->end_index);
    }
    FreeTextAttributesList(attrs);
  } else {
    SUCCEED();
  }
}