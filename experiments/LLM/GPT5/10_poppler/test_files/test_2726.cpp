// File: test_printDocBBox_2726.cc
#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "goo/GooString.h"
#include "poppler/PDFDoc.h"
#include "poppler/TextOutputDev.h"

// Function under test (implemented in utils/pdftotext.cc)
void printDocBBox(FILE *f, PDFDoc *doc, TextOutputDev *textOut, int first, int last);

// Globals declared in utils/pdftoppm.cc (used by printDocBBox)
extern double resolution;
extern bool useCropBox;

namespace {

static std::vector<unsigned char> DecodeBase64(const std::string &in) {
  static const int8_t kDec[256] = {
      -1,-1,-1,-1,-1,-1,-1,-1,-1,-1, // 0-9
      -1,-1,-1,-1,-1,-1,-1,-1,-1,-1, // 10-19
      -1,-1,-1,-1,-1,-1,-1,-1,-1,-1, // 20-29
      -1,-1,-1,-1,-1,-1,-1,-1,-1,-1, // 30-39
      -1,-1,-1,62,-1,-1,-1,63,52,53, // 40-49  '+'=62 '/'=63 '0'=52
      54,55,56,57,58,59,60,61,-1,-1, // 50-59
      -1,-1,-1,-1,-1, 0, 1, 2, 3, 4, // 60-69 'A'=0
       5, 6, 7, 8, 9,10,11,12,13,14, // 70-79
      15,16,17,18,19,20,21,22,23,24, // 80-89
      25,-1,-1,-1,-1,-1,-1,26,27,28, // 90-99 'a'=26
      29,30,31,32,33,34,35,36,37,38, // 100-109
      39,40,41,42,43,44,45,46,47,48, // 110-119
      49,50,51,-1,-1,-1,-1,-1,
      // rest init to -1
  };

  auto dec = [&](unsigned char c) -> int {
    if (c < sizeof(kDec)) return kDec[c];
    return -1;
  };

  std::vector<unsigned char> out;
  out.reserve(in.size() * 3 / 4);

  int val = 0;
  int valb = -8;
  for (unsigned char c : in) {
    if (c == '=') break;
    if (c == '\n' || c == '\r' || c == ' ' || c == '\t') continue;
    int d = dec(c);
    if (d < 0) continue;
    val = (val << 6) + d;
    valb += 6;
    if (valb >= 0) {
      out.push_back(static_cast<unsigned char>((val >> valb) & 0xFF));
      valb -= 8;
    }
  }
  return out;
}

static std::string WriteTempPdfFromBase64(const std::string &b64) {
  std::vector<unsigned char> bytes = DecodeBase64(b64);

  std::string tmpl = "/tmp/poppler_printDocBBox_2726_XXXXXX.pdf";
  // mkstemps needs a mutable buffer.
  std::vector<char> path(tmpl.begin(), tmpl.end());
  path.push_back('\0');

  // suffix length = ".pdf" = 4
  int fd = mkstemps(path.data(), 4);
  if (fd < 0) {
    return "";
  }

  FILE *fp = fdopen(fd, "wb");
  if (!fp) {
    close(fd);
    return "";
  }
  size_t wrote = fwrite(bytes.data(), 1, bytes.size(), fp);
  fclose(fp);

  if (wrote != bytes.size()) {
    std::remove(path.data());
    return "";
  }

  return std::string(path.data());
}

static std::string ReadAll(FILE *f) {
  std::fflush(f);
  std::rewind(f);
  std::string out;
  char buf[4096];
  while (true) {
    size_t n = std::fread(buf, 1, sizeof(buf), f);
    if (n == 0) break;
    out.append(buf, buf + n);
  }
  return out;
}

static int CountSubstr(const std::string &s, const std::string &needle) {
  if (needle.empty()) return 0;
  int count = 0;
  size_t pos = 0;
  while ((pos = s.find(needle, pos)) != std::string::npos) {
    ++count;
    pos += needle.size();
  }
  return count;
}

// A tiny 2-page PDF generated with PyPDF2:
// - MediaBox: 200 x 400 (points)
// - CropBox:  100 x 300 (points)
// - Blank pages (so we don't depend on printLine output).
static const char kTwoPageMedia200x400Crop100x300_PdfB64[] =
    "JVBERi0xLjMKJeLjz9MKMSAwIG9iago8PAovVHlwZSAvUGFnZXMKL0NvdW50IDIK"
    "L0tpZHMgWyA0IDAgUiA1IDAgUiBdCj4+CmVuZG9iagoyIDAgb2JqCjw8Ci9Qcm9k"
    "dWNlciAoUHlQREYyKQovTmVlZEFwcGVhcmFuY2VzIHRydWUKPj4KZW5kb2JqCjMg"
    "MCBvYmoKPDwKL1R5cGUgL0NhdGFsb2cKL1BhZ2VzIDEgMCBSCj4+CmVuZG9iago0"
    "IDAgb2JqCjw8Ci9UeXBlIC9QYWdlCi9QYXJlbnQgMSAwIFIKL01lZGlhQm94IFsg"
    "MCAwIDIwMCA0MDAgXQovQ3JvcEJveCBbIDAgMCAxMDAgMzAwIF0KL1Jlc291cmNl"
    "cyA8PAo+PgovQ29udGVudHMgNiAwIFIKPj4KZW5kb2JqCjUgMCBvYmoKPDwKL1R5"
    "cGUgL1BhZ2UKL1BhcmVudCAxIDAgUgovTWVkaWFCb3ggWyAwIDAgMjAwIDQwMCBd"
    "Ci9Dcm9wQm94IFsgMCAwIDEwMCAzMDAgXQovUmVzb3VyY2VzIDw8Cj4+Ci9Db250"
    "ZW50cyA3IDAgUgo+PgplbmRvYmoKNiAwIG9iago8PAovTGVuZ3RoIDAKPj4Kc3Ry"
    "ZWFtCgplbmRzdHJlYW0KZW5kb2JqCjcgMCBvYmoKPDwKL0xlbmd0aCAwCj4+CnN0"
    "cmVhbQoKZW5kc3RyZWFtCmVuZG9iagp4cmVmCjAgOAowMDAwMDAwMDAwIDY1NTM1"
    "IGYgCjAwMDAwMDAwMTUgMDAwMDAgbiAKMDAwMDAwMDA3NSAwMDAwMCBuIAowMDAw"
    "MDAwMTQ2IDAwMDAwIG4gCjAwMDAwMDAxOTYgMDAwMDAgbiAKMDAwMDAwMDMzOSAw"
    "MDAwMCBuIAowMDAwMDAwNDgyIDAwMDAwIG4gCjAwMDAwMDA1MTkgMDAwMDAgbiAK"
    "dHJhaWxlcgo8PAovU2l6ZSA4Ci9Sb290IDMgMCBSCi9JbmZvIDIgMCBSCj4+CnN0"
    "YXJ0eHJlZgo1NTYKJSVFT0YK";

class PrintDocBBoxTest_2726 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure deterministic DPI arguments (used for displayPage).
    resolution = 72.0;
    // Default to media box unless overridden in a test.
    useCropBox = false;

    pdfPath_ = WriteTempPdfFromBase64(kTwoPageMedia200x400Crop100x300_PdfB64);
    ASSERT_FALSE(pdfPath_.empty());

    doc_ = std::make_unique<PDFDoc>(
        std::make_unique<GooString>(pdfPath_.c_str()),
        std::optional<GooString>{}, std::optional<GooString>{},
        []() {});
    ASSERT_TRUE(doc_);
    ASSERT_TRUE(doc_->isOk());
    ASSERT_GE(doc_->getNumPages(), 2);

    // Use /dev/null as output sink; we only need internal text structures.
    textOut_ = std::make_unique<TextOutputDev>("/dev/null",
                                              /*physLayoutA=*/false,
                                              /*fixedPitchA=*/0.0,
                                              /*rawOrderA=*/false,
                                              /*append=*/false,
                                              /*discardDiagA=*/false);
    ASSERT_TRUE(textOut_);
    ASSERT_TRUE(textOut_->isOk());
  }

  void TearDown() override {
    textOut_.reset();
    doc_.reset();
    if (!pdfPath_.empty()) {
      std::remove(pdfPath_.c_str());
    }
  }

  std::string pdfPath_;
  std::unique_ptr<PDFDoc> doc_;
  std::unique_ptr<TextOutputDev> textOut_;
};

TEST_F(PrintDocBBoxTest_2726, PrintsDocAndSinglePageUsingMediaBox_2726) {
  useCropBox = false;

  FILE *out = std::tmpfile();
  ASSERT_NE(out, nullptr);

  printDocBBox(out, doc_.get(), textOut_.get(), /*first=*/1, /*last=*/1);

  const std::string s = ReadAll(out);
  std::fclose(out);

  EXPECT_NE(s.find("<doc>\n"), std::string::npos);
  EXPECT_NE(s.find("</doc>\n"), std::string::npos);

  // MediaBox is 200x400 for our generated PDF.
  EXPECT_NE(s.find(" <page width=\"200.000000\" height=\"400.000000\">\n"),
            std::string::npos);
  EXPECT_NE(s.find(" </page>\n"), std::string::npos);
}

TEST_F(PrintDocBBoxTest_2726, PrintsPageUsingCropBoxWhenEnabled_2726) {
  useCropBox = true;

  FILE *out = std::tmpfile();
  ASSERT_NE(out, nullptr);

  printDocBBox(out, doc_.get(), textOut_.get(), /*first=*/1, /*last=*/1);

  const std::string s = ReadAll(out);
  std::fclose(out);

  // CropBox is 100x300 for our generated PDF.
  EXPECT_NE(s.find(" <page width=\"100.000000\" height=\"300.000000\">\n"),
            std::string::npos);
}

TEST_F(PrintDocBBoxTest_2726, PrintsMultiplePagesForRange_2726) {
  useCropBox = false;

  FILE *out = std::tmpfile();
  ASSERT_NE(out, nullptr);

  printDocBBox(out, doc_.get(), textOut_.get(), /*first=*/1, /*last=*/2);

  const std::string s = ReadAll(out);
  std::fclose(out);

  const std::string needle = " <page width=\"200.000000\" height=\"400.000000\">\n";
  EXPECT_EQ(CountSubstr(s, needle), 2);
  EXPECT_EQ(CountSubstr(s, " </page>\n"), 2);
}

TEST_F(PrintDocBBoxTest_2726, EmptyRangePrintsOnlyDocRoot_2726) {
  useCropBox = false;

  FILE *out = std::tmpfile();
  ASSERT_NE(out, nullptr);

  // first > last => page loop does not run.
  printDocBBox(out, doc_.get(), textOut_.get(), /*first=*/2, /*last=*/1);

  const std::string s = ReadAll(out);
  std::fclose(out);

  EXPECT_EQ(s, std::string("<doc>\n</doc>\n"));
}

}  // namespace