// Page_getTrans_ut_726.cpp
// Unit tests for Page::getTrans()
// TEST_ID: 726

#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "poppler/PDFDoc.h"
#include "poppler/Page.h"
#include "poppler/Object.h"
#include "poppler/GooString.h"

namespace {

static std::string BuildMinimalPdfWithObjects(const std::vector<std::string> &objs) {
  // Builds a minimal PDF with the given objects (1-based object numbers in order),
  // and a correct xref/trailer. Returns the PDF bytes as a std::string.
  //
  // Note: This is *not* re-implementing Page/Object logic; it only creates test inputs (PDF bytes).
  std::string pdf;
  pdf += "%PDF-1.4\n";
  pdf += "%\xE2\xE3\xCF\xD3\n";

  std::vector<size_t> offsets;
  offsets.reserve(objs.size() + 1);
  offsets.push_back(0); // object 0 is free

  for (size_t i = 0; i < objs.size(); ++i) {
    offsets.push_back(pdf.size());
    pdf += std::to_string(i + 1);
    pdf += " 0 obj\n";
    pdf += objs[i];
    if (!objs[i].empty() && objs[i].back() != '\n') pdf += "\n";
    pdf += "endobj\n";
  }

  const size_t xrefOffset = pdf.size();
  pdf += "xref\n";
  pdf += "0 " + std::to_string(objs.size() + 1) + "\n";
  pdf += "0000000000 65535 f \n";
  for (size_t i = 1; i < offsets.size(); ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offsets[i]);
    pdf += buf;
  }

  // Assume object 1 is the catalog.
  pdf += "trailer\n";
  pdf += "<< /Size " + std::to_string(objs.size() + 1) + " /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xrefOffset) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

static std::filesystem::path WriteTempFile(const std::string &bytes, const std::string &suffix) {
  const auto dir = std::filesystem::temp_directory_path();
  // A simple unique-ish name per test invocation.
  const auto filename =
      "poppler_page_getTrans_" + std::to_string(::getpid()) + "_" + std::to_string(std::rand()) + suffix;
  const auto path = dir / filename;

  std::ofstream out(path, std::ios::binary);
  out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  out.close();
  return path;
}

static bool IsNullish(const Object &o) {
  return o.isNull() || o.isNone() || o.isEOF() || o.isError();
}

static std::unique_ptr<PDFDoc> OpenDocFromPath(const std::filesystem::path &p) {
  auto fname = std::make_unique<GooString>(p.string().c_str());
  // Common Poppler ctor form: PDFDoc(fileName, ownerPW, userPW)
  // (If your build uses a different signature, adjust accordingly.)
  return std::make_unique<PDFDoc>(std::move(fname), nullptr, nullptr);
}

} // namespace

class PageGetTransTest_726 : public ::testing::Test {
protected:
  void TearDown() override {
    for (const auto &p : tmpFiles_) {
      std::error_code ec;
      std::filesystem::remove(p, ec);
    }
    tmpFiles_.clear();
  }

  std::filesystem::path KeepTemp(const std::filesystem::path &p) {
    tmpFiles_.push_back(p);
    return p;
  }

private:
  std::vector<std::filesystem::path> tmpFiles_;
};

TEST_F(PageGetTransTest_726, NoTransEntry_ReturnsNullish_726) {
  // PDF structure:
  // 1: Catalog
  // 2: Pages
  // 3: Page (no /Trans)
  // 4: Contents (empty stream)
  const std::vector<std::string> objs = {
      "<< /Type /Catalog /Pages 2 0 R >>",
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>",
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>",
      "<< /Length 0 >>\nstream\n\nendstream",
  };

  const auto pdf = BuildMinimalPdfWithObjects(objs);
  const auto path = KeepTemp(WriteTempFile(pdf, ".pdf"));
  auto doc = OpenDocFromPath(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  const Object trans = page->getTrans();

  // If there's no /Trans entry, observable behavior should be "null-ish" (null/none/error/eof).
  EXPECT_TRUE(IsNullish(trans));
}

TEST_F(PageGetTransTest_726, DirectTransDict_ReturnsDictWithExpectedFields_726) {
  // Put /Trans directly as a dictionary in the page dict.
  // We'll check that getTrans returns a dictionary and that key /S is the expected name.
  const std::vector<std::string> objs = {
      "<< /Type /Catalog /Pages 2 0 R >>",
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>",
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R "
      "   /Trans << /S /Dissolve /D 1 >> >>",
      "<< /Length 0 >>\nstream\n\nendstream",
  };

  const auto pdf = BuildMinimalPdfWithObjects(objs);
  const auto path = KeepTemp(WriteTempFile(pdf, ".pdf"));
  auto doc = OpenDocFromPath(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  const Object trans = page->getTrans();
  ASSERT_TRUE(trans.isDict()) << "Expected a dictionary Object from Page::getTrans()";

  const Object s = trans.dictLookup("S", /*recursion*/ 0);
  ASSERT_TRUE(s.isName()) << "Expected /S to be a name";
  EXPECT_EQ(std::string(s.getName()), "Dissolve");

  const Object d = trans.dictLookup("D", /*recursion*/ 0);
  // Some implementations may coerce/validate; we only require that if present, it is numeric.
  if (!IsNullish(d)) {
    EXPECT_TRUE(d.isNum() || d.isInt() || d.isInt64() || d.isReal());
  }
}

TEST_F(PageGetTransTest_726, IndirectTransRef_IsFetchedAndResolvedToDict_726) {
  // Put /Trans as an indirect reference: /Trans 5 0 R
  // and define object 5 as the dictionary.
  const std::vector<std::string> objs = {
      "<< /Type /Catalog /Pages 2 0 R >>",
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>",
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R /Trans 5 0 R >>",
      "<< /Length 0 >>\nstream\n\nendstream",
      "<< /S /Wipe /D 2 >>",
  };

  const auto pdf = BuildMinimalPdfWithObjects(objs);
  const auto path = KeepTemp(WriteTempFile(pdf, ".pdf"));
  auto doc = OpenDocFromPath(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  const Object trans = page->getTrans();

  // Key observable requirement from the partial implementation: it calls fetch(xref).
  // If /Trans is a ref, fetch should resolve it into the referenced object.
  ASSERT_TRUE(trans.isDict()) << "Expected fetched /Trans to resolve to a dict";

  const Object s = trans.dictLookup("S", /*recursion*/ 0);
  ASSERT_TRUE(s.isName());
  EXPECT_EQ(std::string(s.getName()), "Wipe");
}

TEST_F(PageGetTransTest_726, TransWrongType_DoesNotCrashAndReturnsSomethingObservable_726) {
  // Boundary / error-ish input: /Trans is an integer.
  // We only assert that getTrans is callable and returns an Object (not crashing),
  // and that the result is either int/num, or null-ish, or error-ish (implementation-defined).
  const std::vector<std::string> objs = {
      "<< /Type /Catalog /Pages 2 0 R >>",
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>",
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R /Trans 123 >>",
      "<< /Length 0 >>\nstream\n\nendstream",
  };

  const auto pdf = BuildMinimalPdfWithObjects(objs);
  const auto path = KeepTemp(WriteTempFile(pdf, ".pdf"));
  auto doc = OpenDocFromPath(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  const Object trans = page->getTrans();

  // Accept a range of observable behaviors without guessing internals.
  const bool okType =
      trans.isInt() || trans.isInt64() || trans.isNum() || IsNullish(trans) || trans.isError();
  EXPECT_TRUE(okType);
}

TEST_F(PageGetTransTest_726, MultipleCalls_AreConsistentForSamePage_726) {
  // Ensures getTrans can be called repeatedly and yields consistent observable properties.
  const std::vector<std::string> objs = {
      "<< /Type /Catalog /Pages 2 0 R >>",
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>",
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R "
      "   /Trans << /S /Split /D 3 >> >>",
      "<< /Length 0 >>\nstream\n\nendstream",
  };

  const auto pdf = BuildMinimalPdfWithObjects(objs);
  const auto path = KeepTemp(WriteTempFile(pdf, ".pdf"));
  auto doc = OpenDocFromPath(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  const Object t1 = page->getTrans();
  const Object t2 = page->getTrans();

  ASSERT_TRUE(t1.isDict());
  ASSERT_TRUE(t2.isDict());

  const Object s1 = t1.dictLookup("S", 0);
  const Object s2 = t2.dictLookup("S", 0);

  ASSERT_TRUE(s1.isName());
  ASSERT_TRUE(s2.isName());
  EXPECT_EQ(std::string(s1.getName()), std::string(s2.getName()));
  EXPECT_EQ(std::string(s1.getName()), "Split");
}