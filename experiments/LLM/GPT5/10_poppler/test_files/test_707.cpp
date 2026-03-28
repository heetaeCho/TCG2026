// Page_getMediaHeight_707_test.cpp
// Unit tests for Page::getMediaHeight (black-box via public Poppler API)
//
// TEST_ID: 707

#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <fstream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>

#include "Page.h"

// These headers are part of Poppler's public C++ API in most builds.
#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

namespace {

// Poppler typically exposes a global pointer.
extern GlobalParams *globalParams;

class GlobalParamsGuard {
public:
  GlobalParamsGuard() {
    if (!globalParams) {
      globalParams = new GlobalParams();
      owns_ = true;
    }
  }
  ~GlobalParamsGuard() {
    if (owns_) {
      delete globalParams;
      globalParams = nullptr;
    }
  }

  GlobalParamsGuard(const GlobalParamsGuard &) = delete;
  GlobalParamsGuard &operator=(const GlobalParamsGuard &) = delete;

private:
  bool owns_ = false;
};

static std::string WriteOnePagePdfWithMediaBox(const testing::TestInfo *ti,
                                               double x1, double y1,
                                               double x2, double y2) {
  const std::string path =
      std::string(testing::TempDir()) + "/" + ti->test_suite_name() + "_" +
      ti->name() + ".pdf";

  // Minimal one-page PDF. MediaBox is set on the page dictionary.
  // Height should be (y2 - y1), matching Page::getMediaHeight().
  const std::string pdf =
      "%PDF-1.4\n"
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n"
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n"
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R\n"
      "   /MediaBox [" + std::to_string(x1) + " " + std::to_string(y1) + " " +
      std::to_string(x2) + " " + std::to_string(y2) + "]\n"
      "   /Contents 4 0 R\n"
      "   /Resources << >>\n"
      ">>\n"
      "endobj\n"
      "4 0 obj\n"
      "<< /Length 0 >>\n"
      "stream\n"
      "endstream\n"
      "endobj\n"
      "xref\n"
      "0 5\n"
      "0000000000 65535 f \n"
      "trailer\n"
      "<< /Size 5 /Root 1 0 R >>\n"
      "startxref\n"
      "0\n"
      "%%EOF\n";

  std::ofstream os(path, std::ios::binary);
  os.write(pdf.data(), static_cast<std::streamsize>(pdf.size()));
  os.close();

  return path;
}

template <typename T>
using is_unique_ptr = std::false_type;
template <typename U>
struct is_unique_ptr<std::unique_ptr<U>> : std::true_type {};

static std::unique_ptr<PDFDoc> OpenPdfDoc(const std::string &path) {
  // Prefer owning std::unique_ptr<PDFDoc> so we can handle multiple Poppler ABIs.
  auto fileName = std::make_unique<GooString>(path.c_str());

  if constexpr (std::is_constructible_v<PDFDoc, std::unique_ptr<GooString>>) {
    return std::make_unique<PDFDoc>(std::move(fileName));
  } else if constexpr (std::is_constructible_v<PDFDoc, GooString *>) {
    // Some builds take a raw pointer (and assume ownership).
    return std::unique_ptr<PDFDoc>(new PDFDoc(fileName.release()));
  } else if constexpr (std::is_constructible_v<PDFDoc, const GooString &>) {
    return std::make_unique<PDFDoc>(*fileName);
  } else {
    // If your Poppler build uses a different factory/API, this will fail fast.
    return nullptr;
  }
}

static Page *GetFirstPage(PDFDoc &doc) {
  // Most Poppler builds provide PDFDoc::getPage(int).
  if constexpr (std::is_same_v<decltype(std::declval<PDFDoc &>().getPage(1)),
                               Page *>) {
    return doc.getPage(1);
  } else {
    return nullptr;
  }
}

class PageTest_707 : public ::testing::Test {
protected:
  GlobalParamsGuard guard_;
};

} // namespace

TEST_F(PageTest_707, MediaHeightMatchesMediaBox_707) {
  const std::string path =
      WriteOnePagePdfWithMediaBox(this->GetTestInfo(), 0.0, 0.0, 200.0, 400.0);

  auto doc = OpenPdfDoc(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Page *page = GetFirstPage(*doc);
  ASSERT_NE(page, nullptr);

  EXPECT_DOUBLE_EQ(page->getMediaHeight(), 400.0);
}

TEST_F(PageTest_707, MediaHeightZeroWhenY1EqualsY2_707) {
  const std::string path =
      WriteOnePagePdfWithMediaBox(this->GetTestInfo(), 0.0, 10.0, 200.0, 10.0);

  auto doc = OpenPdfDoc(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Page *page = GetFirstPage(*doc);
  ASSERT_NE(page, nullptr);

  EXPECT_DOUBLE_EQ(page->getMediaHeight(), 0.0);
}

TEST_F(PageTest_707, MediaHeightSupportsNegativeCoordinates_707) {
  // y2 - y1 = 50 - (-150) = 200
  const std::string path = WriteOnePagePdfWithMediaBox(this->GetTestInfo(),
                                                       0.0, -150.0, 200.0,
                                                       50.0);

  auto doc = OpenPdfDoc(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Page *page = GetFirstPage(*doc);
  ASSERT_NE(page, nullptr);

  EXPECT_DOUBLE_EQ(page->getMediaHeight(), 200.0);
}

TEST_F(PageTest_707, MediaHeightLargeValues_707) {
  // Height = 1e9 - (-1e9) = 2e9
  const std::string path =
      WriteOnePagePdfWithMediaBox(this->GetTestInfo(), 0.0, -1e9, 1.0, 1e9);

  auto doc = OpenPdfDoc(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Page *page = GetFirstPage(*doc);
  ASSERT_NE(page, nullptr);

  EXPECT_DOUBLE_EQ(page->getMediaHeight(), 2e9);
}

TEST_F(PageTest_707, InvalidPdfDoesNotProduceUsablePage_707) {
  const std::string path =
      std::string(testing::TempDir()) + "/" + this->GetTestInfo()->name() +
      "_invalid.pdf";
  {
    std::ofstream os(path, std::ios::binary);
    os << "not a pdf";
  }

  auto doc = OpenPdfDoc(path);
  // Depending on Poppler build, doc may be null or isOk() may be false.
  if (!doc) {
    SUCCEED();
    return;
  }
  EXPECT_FALSE(doc->isOk());
}