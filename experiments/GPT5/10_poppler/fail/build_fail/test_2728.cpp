// File: print_word_bbox_test_2728.cc
#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <fstream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "poppler/PDFDoc.h"
#include "poppler/GooString.h"
#include "poppler/TextOutputDev.h"
#include "poppler/GlobalParams.h"

// Function under test (defined in utils/pdftotext.cc)
extern void printWordBBox(FILE *f, PDFDoc *doc, TextOutputDev *textOut, int first, int last);

// Globals used by printWordBBox (defined in utils/pdftoppm.cc)
extern double resolution;
extern bool useCropBox;

// Poppler global params (commonly required for PDFDoc/TextOutputDev to work)
extern std::unique_ptr<GlobalParams> globalParams;

namespace {

struct PdfPageSpec {
  std::string contents; // stream contents (can be empty)
  // MediaBox is required. CropBox is optional.
  double mediaW = 200.0;
  double mediaH = 400.0;
  std::optional<std::pair<double, double>> cropWH; // {w,h} if set
};

static std::string ReadAllFromFile(FILE *f) {
  fflush(f);
  long cur = ftell(f);
  (void)cur;
  fseek(f, 0, SEEK_END);
  long sz = ftell(f);
  fseek(f, 0, SEEK_SET);
  if (sz < 0) return std::string();
  std::string out;
  out.resize(static_cast<size_t>(sz));
  size_t nread = fread(out.data(), 1, out.size(), f);
  out.resize(nread);
  return out;
}

static std::string WriteTempFile(const std::string &bytes) {
  // Use mkstemp for a real file path.
  std::string pattern = "/tmp/poppler_printWordBBox_XXXXXX.pdf";
  std::vector<char> buf(pattern.begin(), pattern.end());
  buf.push_back('\0');
  int fd = mkstemps(buf.data(), 4 /*.pdf*/);
  EXPECT_NE(fd, -1);
  if (fd == -1) {
    return std::string();
  }
  // Write bytes
  FILE *fp = fdopen(fd, "wb");
  EXPECT_NE(fp, nullptr);
  if (!fp) {
    close(fd);
    return std::string();
  }
  size_t wrote = fwrite(bytes.data(), 1, bytes.size(), fp);
  EXPECT_EQ(wrote, bytes.size());
  fflush(fp);
  fclose(fp);
  return std::string(buf.data());
}

static std::string BuildMinimalPdf(const std::vector<PdfPageSpec> &pages) {
  // Very small PDF generator that produces correct xref offsets.
  // Objects:
  //  1 0 obj: Catalog
  //  2 0 obj: Pages
  //  3 0 obj: Font (Helvetica)
  //  then for each page i:
  //    pageObj
  //    contentObj
  //
  // /Kids in Pages points to each pageObj.
  // Each page points to the shared font object.

  struct Obj {
    int num;
    std::string body;
  };

  std::vector<Obj> objs;
  objs.push_back({3, "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>"});

  const int catalogNum = 1;
  const int pagesNum = 2;
  const int fontNum = 3;

  // Assign numbers for page and content objects
  int nextNum = 4;
  std::vector<int> pageObjNums;
  std::vector<int> contentObjNums;
  pageObjNums.reserve(pages.size());
  contentObjNums.reserve(pages.size());
  for (size_t i = 0; i < pages.size(); ++i) {
    pageObjNums.push_back(nextNum++);
    contentObjNums.push_back(nextNum++);
  }

  // Pages object (Kids filled now)
  {
    std::ostringstream kids;
    kids << "[";
    for (size_t i = 0; i < pageObjNums.size(); ++i) {
      kids << " " << pageObjNums[i] << " 0 R";
    }
    kids << " ]";
    std::ostringstream body;
    body << "<< /Type /Pages /Kids " << kids.str() << " /Count " << pages.size() << " >>";
    objs.push_back({pagesNum, body.str()});
  }

  // Catalog object
  objs.push_back({catalogNum, "<< /Type /Catalog /Pages 2 0 R >>"});

  // Per-page objects and content streams
  for (size_t i = 0; i < pages.size(); ++i) {
    const auto &p = pages[i];

    // Content stream object
    {
      const std::string &streamData = p.contents;
      std::ostringstream body;
      body << "<< /Length " << streamData.size() << " >>\n"
           << "stream\n"
           << streamData
           << "\nendstream";
      objs.push_back({contentObjNums[i], body.str()});
    }

    // Page object
    {
      std::ostringstream body;
      body << "<< /Type /Page"
           << " /Parent 2 0 R"
           << " /MediaBox [0 0 " << p.mediaW << " " << p.mediaH << "]";
      if (p.cropWH.has_value()) {
        body << " /CropBox [0 0 " << p.cropWH->first << " " << p.cropWH->second << "]";
      }
      body << " /Resources << /Font << /F1 " << fontNum << " 0 R >> >>"
           << " /Contents " << contentObjNums[i] << " 0 R"
           << " >>";
      objs.push_back({pageObjNums[i], body.str()});
    }
  }

  // Sort objects by object number for nicer xref (not strictly required, but typical)
  std::sort(objs.begin(), objs.end(), [](const Obj &a, const Obj &b) { return a.num < b.num; });

  std::ostringstream pdf;
  pdf << "%PDF-1.4\n";

  // Track offsets
  const int maxObjNum = nextNum - 1;
  std::vector<long> offsets(maxObjNum + 1, -1);

  for (const auto &o : objs) {
    offsets[o.num] = static_cast<long>(pdf.tellp());
    pdf << o.num << " 0 obj\n" << o.body << "\nendobj\n";
  }

  long xrefPos = static_cast<long>(pdf.tellp());
  pdf << "xref\n";
  pdf << "0 " << (maxObjNum + 1) << "\n";
  // Object 0 free entry
  pdf << "0000000000 65535 f \n";
  for (int n = 1; n <= maxObjNum; ++n) {
    long off = offsets[n];
    if (off < 0) {
      // Missing object number: put a free entry (rare in our generator)
      pdf << "0000000000 65535 f \n";
    } else {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", off);
      pdf << buf;
    }
  }

  pdf << "trailer\n"
      << "<< /Size " << (maxObjNum + 1) << " /Root 1 0 R >>\n"
      << "startxref\n"
      << xrefPos << "\n"
      << "%%EOF\n";

  return pdf.str();
}

static std::unique_ptr<PDFDoc> OpenDocFromPath(const std::string &path) {
  auto fn = std::make_unique<GooString>(path.c_str());
  std::optional<GooString> none;
  auto doc = std::make_unique<PDFDoc>(std::move(fn), none, none, []() {});
  return doc;
}

class PrintWordBBoxTest_2728 : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    if (!globalParams) {
      globalParams = std::make_unique<GlobalParams>();
    }
  }

  void SetUp() override {
    resolution = 72.0;
    useCropBox = false;
  }
};

} // namespace

TEST_F(PrintWordBBoxTest_2728, FirstGreaterThanLastPrintsOnlyDocTags_2728) {
  // No pages should be emitted when first > last; only <doc> ... </doc>.
  const std::string pdfBytes = BuildMinimalPdf({PdfPageSpec{""}});
  const std::string path = WriteTempFile(pdfBytes);
  ASSERT_FALSE(path.empty());

  auto doc = OpenDocFromPath(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  TextOutputDev textOut(nullptr, /*physLayoutA=*/true, /*fixedPitchA=*/0.0,
                        /*rawOrderA=*/false, /*append=*/false, /*discardDiagA=*/false);
  ASSERT_TRUE(textOut.isOk());

  FILE *out = tmpfile();
  ASSERT_NE(out, nullptr);

  printWordBBox(out, doc.get(), &textOut, /*first=*/2, /*last=*/1);

  const std::string s = ReadAllFromFile(out);
  fclose(out);

  EXPECT_NE(s.find("<doc>\n"), std::string::npos);
  EXPECT_NE(s.find("</doc>\n"), std::string::npos);
  EXPECT_EQ(s.find("<page "), std::string::npos);
  EXPECT_EQ(s.find("<word "), std::string::npos);
}

TEST_F(PrintWordBBoxTest_2728, SinglePageWithTextEmitsWordElements_2728) {
  // One page containing "Hello" should produce at least one <word> and include "Hello" text.
  PdfPageSpec p;
  p.mediaW = 200;
  p.mediaH = 400;
  p.contents =
      "BT\n"
      "/F1 24 Tf\n"
      "72 300 Td\n"
      "(Hello) Tj\n"
      "ET";
  const std::string pdfBytes = BuildMinimalPdf({p});
  const std::string path = WriteTempFile(pdfBytes);
  ASSERT_FALSE(path.empty());

  auto doc = OpenDocFromPath(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  TextOutputDev textOut(nullptr, /*physLayoutA=*/true, /*fixedPitchA=*/0.0,
                        /*rawOrderA=*/false, /*append=*/false, /*discardDiagA=*/false);
  ASSERT_TRUE(textOut.isOk());

  FILE *out = tmpfile();
  ASSERT_NE(out, nullptr);

  printWordBBox(out, doc.get(), &textOut, /*first=*/1, /*last=*/1);

  const std::string s = ReadAllFromFile(out);
  fclose(out);

  EXPECT_NE(s.find("<doc>\n"), std::string::npos);
  EXPECT_NE(s.find(" <page "), std::string::npos);
  EXPECT_NE(s.find("</doc>\n"), std::string::npos);

  // A word element should be present and should contain the text "Hello" for plain text.
  EXPECT_NE(s.find("<word "), std::string::npos);
  EXPECT_NE(s.find(">Hello</word>"), std::string::npos);
}

TEST_F(PrintWordBBoxTest_2728, BlankPageWritesNoWordAndReportsToStderr_2728) {
  // A page with no text should yield an empty word list and print "no word list" to stderr.
  PdfPageSpec p;
  p.mediaW = 200;
  p.mediaH = 400;
  p.contents = ""; // no text operators

  const std::string pdfBytes = BuildMinimalPdf({p});
  const std::string path = WriteTempFile(pdfBytes);
  ASSERT_FALSE(path.empty());

  auto doc = OpenDocFromPath(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  TextOutputDev textOut(nullptr, /*physLayoutA=*/true, /*fixedPitchA=*/0.0,
                        /*rawOrderA=*/false, /*append=*/false, /*discardDiagA=*/false);
  ASSERT_TRUE(textOut.isOk());

  FILE *out = tmpfile();
  ASSERT_NE(out, nullptr);

  testing::internal::CaptureStderr();
  printWordBBox(out, doc.get(), &textOut, /*first=*/1, /*last=*/1);
  const std::string err = testing::internal::GetCapturedStderr();

  const std::string s = ReadAllFromFile(out);
  fclose(out);

  EXPECT_NE(err.find("no word list"), std::string::npos);
  EXPECT_NE(s.find("<doc>\n"), std::string::npos);
  EXPECT_NE(s.find(" <page "), std::string::npos);
  EXPECT_EQ(s.find("<word "), std::string::npos);
}

TEST_F(PrintWordBBoxTest_2728, UseCropBoxControlsReportedPageSize_2728) {
  // MediaBox 200x400, CropBox 100x100. The emitted <page width/height> should switch.
  PdfPageSpec p;
  p.mediaW = 200;
  p.mediaH = 400;
  p.cropWH = std::make_pair(100.0, 100.0);
  p.contents =
      "BT\n"
      "/F1 12 Tf\n"
      "10 10 Td\n"
      "(X) Tj\n"
      "ET";

  const std::string pdfBytes = BuildMinimalPdf({p});
  const std::string path = WriteTempFile(pdfBytes);
  ASSERT_FALSE(path.empty());

  auto doc = OpenDocFromPath(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  TextOutputDev textOut(nullptr, /*physLayoutA=*/true, /*fixedPitchA=*/0.0,
                        /*rawOrderA=*/false, /*append=*/false, /*discardDiagA=*/false);
  ASSERT_TRUE(textOut.isOk());

  // First: useCropBox = false => MediaBox size
  {
    useCropBox = false;
    FILE *out = tmpfile();
    ASSERT_NE(out, nullptr);

    printWordBBox(out, doc.get(), &textOut, 1, 1);
    const std::string s = ReadAllFromFile(out);
    fclose(out);

    EXPECT_NE(s.find(" <page width=\"200.000000\" height=\"400.000000\">"), std::string::npos);
  }

  // Second: useCropBox = true => CropBox size
  {
    useCropBox = true;
    FILE *out = tmpfile();
    ASSERT_NE(out, nullptr);

    printWordBBox(out, doc.get(), &textOut, 1, 1);
    const std::string s = ReadAllFromFile(out);
    fclose(out);

    EXPECT_NE(s.find(" <page width=\"100.000000\" height=\"100.000000\">"), std::string::npos);
  }
}

TEST_F(PrintWordBBoxTest_2728, MultiplePagesEmitMultiplePageSections_2728) {
  // Two pages: "A" and "B" -> output should include two <page ...> blocks and both words.
  PdfPageSpec p1;
  p1.mediaW = 200;
  p1.mediaH = 400;
  p1.contents =
      "BT\n"
      "/F1 24 Tf\n"
      "72 300 Td\n"
      "(A) Tj\n"
      "ET";

  PdfPageSpec p2;
  p2.mediaW = 200;
  p2.mediaH = 400;
  p2.contents =
      "BT\n"
      "/F1 24 Tf\n"
      "72 300 Td\n"
      "(B) Tj\n"
      "ET";

  const std::string pdfBytes = BuildMinimalPdf({p1, p2});
  const std::string path = WriteTempFile(pdfBytes);
  ASSERT_FALSE(path.empty());

  auto doc = OpenDocFromPath(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  TextOutputDev textOut(nullptr, /*physLayoutA=*/true, /*fixedPitchA=*/0.0,
                        /*rawOrderA=*/false, /*append=*/false, /*discardDiagA=*/false);
  ASSERT_TRUE(textOut.isOk());

  FILE *out = tmpfile();
  ASSERT_NE(out, nullptr);

  printWordBBox(out, doc.get(), &textOut, /*first=*/1, /*last=*/2);

  const std::string s = ReadAllFromFile(out);
  fclose(out);

  // Expect two page openings and closings.
  size_t pos = 0;
  int pageOpenCount = 0;
  while ((pos = s.find(" <page width=", pos)) != std::string::npos) {
    ++pageOpenCount;
    pos += 8;
  }
  EXPECT_EQ(pageOpenCount, 2);

  // Both A and B should appear inside <word> elements.
  EXPECT_NE(s.find(">A</word>"), std::string::npos);
  EXPECT_NE(s.find(">B</word>"), std::string::npos);
}