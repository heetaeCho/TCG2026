// TEST_ID: 724
// File: Page_getContents_724_test.cpp

#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "poppler/Page.h"
#include "poppler/PDFDoc.h"
#include "poppler/Catalog.h"
#include "poppler/GooString.h"
#include "poppler/GlobalParams.h"

// Poppler typically exposes this global.
extern GlobalParams *globalParams;

namespace {

// Build a minimal, valid PDF with exactly 1 page.
// If includeContentsKey is true, the page's /Contents is an indirect reference to a stream (object 4).
// Otherwise, /Contents is omitted from the page dictionary.
std::string buildOnePagePdf(const std::string &streamData, bool includeContentsKey) {
  // Objects:
  // 1 0 obj: Catalog
  // 2 0 obj: Pages
  // 3 0 obj: Page (optionally refers to 4 0 R)
  // 4 0 obj: Contents stream (only meaningful if referenced)

  const std::string header = "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

  std::string obj1 =
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n";

  std::string obj2 =
      "2 0 obj\n"
      "<< /Type /Pages /Count 1 /Kids [3 0 R] >>\n"
      "endobj\n";

  std::string pageDict =
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R\n"
      "   /MediaBox [0 0 200 200]\n";
  if (includeContentsKey) {
    pageDict += "   /Contents 4 0 R\n";
  }
  pageDict += ">>\nendobj\n";

  std::string obj4;
  if (includeContentsKey) {
    obj4 =
        "4 0 obj\n"
        "<< /Length " +
        std::to_string(streamData.size()) +
        " >>\n"
        "stream\n" +
        streamData + "\n"
        "endstream\n"
        "endobj\n";
  }

  // Assemble and compute xref offsets.
  std::string body;
  body.reserve(4096);
  body += header;

  std::vector<long> offsets(5, 0); // 0..4
  offsets[0] = 0;

  offsets[1] = static_cast<long>(body.size());
  body += obj1;

  offsets[2] = static_cast<long>(body.size());
  body += obj2;

  offsets[3] = static_cast<long>(body.size());
  body += pageDict;

  if (includeContentsKey) {
    offsets[4] = static_cast<long>(body.size());
    body += obj4;
  } else {
    offsets[4] = 0;
  }

  const long xrefPos = static_cast<long>(body.size());

  // xref table: must list entries from 0..4.
  std::string xref;
  xref += "xref\n";
  xref += "0 5\n";
  xref += "0000000000 65535 f \n";
  auto fmtOff = [](long off) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", off);
    return std::string(buf);
  };
  xref += fmtOff(offsets[1]) + " 00000 n \n";
  xref += fmtOff(offsets[2]) + " 00000 n \n";
  xref += fmtOff(offsets[3]) + " 00000 n \n";
  // If object 4 is omitted, still provide a well-formed xref entry; use offset 0 but keep "n".
  // Poppler should ignore it because nothing references it.
  xref += fmtOff(includeContentsKey ? offsets[4] : 0) + " 00000 n \n";

  std::string trailer =
      "trailer\n"
      "<< /Size 5 /Root 1 0 R >>\n"
      "startxref\n" +
      std::to_string(xrefPos) +
      "\n%%EOF\n";

  return body + xref + trailer;
}

std::string writeTempFile(const std::string &bytes) {
  // Simple, portable-ish temp file creation.
  // (In CI this is usually fine; path uniqueness is "good enough" for tests.)
  char tmpName[L_tmpnam];
  std::tmpnam(tmpName);
  std::string path = std::string(tmpName) + "_poppler_page_724.pdf";

  std::ofstream os(path, std::ios::binary);
  os.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  os.close();
  return path;
}

std::unique_ptr<PDFDoc> openPdfDocFromPath(const std::string &path) {
  // Most Poppler builds support this classic constructor:
  // PDFDoc(GooString *fileNameA, GooString *ownerPasswordA, GooString *userPasswordA, void *guiDataA)
  auto *name = new GooString(path.c_str());
  auto doc = std::make_unique<PDFDoc>(name, nullptr, nullptr, nullptr);
  return doc;
}

int readFirstNonWhitespaceChar(Object &streamObj) {
  // Object::streamRewind + streamGetChar are part of Object's public interface.
  // If rewind fails, just attempt reading anyway.
  (void)streamObj.streamRewind();
  for (int i = 0; i < 4096; ++i) {
    int c = streamObj.streamGetChar();
    if (c < 0) {
      return c;
    }
    if (c != ' ' && c != '\t' && c != '\r' && c != '\n') {
      return c;
    }
  }
  return -1;
}

class PageGetContentsTest_724 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure globalParams exists for Poppler internals that expect it.
    if (!globalParams) {
      globalParams = new GlobalParams();
    }
  }

  void TearDown() override {
    // Keep globalParams alive across tests in the same binary to avoid teardown-order issues.
    // (Poppler projects often do this in test harnesses.)
  }
};

} // namespace

TEST_F(PageGetContentsTest_724, ReturnsStreamAndIsNotRefWhenIndirectStream_724) {
  const std::string pdf = buildOnePagePdf("q\nQ", /*includeContentsKey=*/true);
  const std::string path = writeTempFile(pdf);

  auto doc = openPdfDocFromPath(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Catalog *catalog = doc->getCatalog();
  ASSERT_NE(catalog, nullptr);

  Page *page = catalog->getPage(1);
  ASSERT_NE(page, nullptr);
  ASSERT_TRUE(page->isOk());

  Object contents = page->getContents();

  // Observable: getContents() returns an Object by value.
  // For this PDF, /Contents is an indirect reference to a stream, so fetch(xref) should resolve it.
  EXPECT_TRUE(contents.isStream());
  EXPECT_FALSE(contents.isRef());

  // Read the first meaningful byte from the stream (black-box observable behavior).
  const int first = readFirstNonWhitespaceChar(contents);
  EXPECT_EQ(first, 'q');

  std::remove(path.c_str());
}

TEST_F(PageGetContentsTest_724, EmptyStreamBoundary_ReadReturnsEOF_724) {
  const std::string pdf = buildOnePagePdf("", /*includeContentsKey=*/true);
  const std::string path = writeTempFile(pdf);

  auto doc = openPdfDocFromPath(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getCatalog()->getPage(1);
  ASSERT_NE(page, nullptr);
  ASSERT_TRUE(page->isOk());

  Object contents = page->getContents();
  ASSERT_TRUE(contents.isStream());
  EXPECT_FALSE(contents.isRef());

  (void)contents.streamRewind();
  const int c = contents.streamGetChar();
  EXPECT_LT(c, 0); // EOF or error sentinel are both negative in Poppler streams.

  std::remove(path.c_str());
}

TEST_F(PageGetContentsTest_724, MissingContentsKeyReturnsNullOrNone_724) {
  const std::string pdf = buildOnePagePdf("q\nQ", /*includeContentsKey=*/false);
  const std::string path = writeTempFile(pdf);

  auto doc = openPdfDocFromPath(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getCatalog()->getPage(1);
  ASSERT_NE(page, nullptr);
  ASSERT_TRUE(page->isOk());

  Object contents = page->getContents();

  // With no /Contents in the page dictionary, Poppler typically exposes an "empty" object.
  // We avoid assuming the exact internal representation; we assert one of the "empty" public states.
  EXPECT_TRUE(contents.isNull() || contents.isNone());

  std::remove(path.c_str());
}