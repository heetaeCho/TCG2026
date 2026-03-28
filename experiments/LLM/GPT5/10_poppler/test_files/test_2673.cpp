// File: ./TestProjects/poppler/utils/pdfinfo_print_pdf_subtype_test_2673.cc

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <map>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "poppler/GooString.h"
#include "poppler/PDFDoc.h"
#include "poppler/UnicodeMap.h"

// pdfinfo.cc (the real tool) often defines a main(). To avoid collision with gtest's main,
// rename it if present. Including the .cc is intentional so we can call the TU-local static
// function `printPdfSubtype` without changing production code.
#define main pdfinfo_main_2673
#include "TestProjects/poppler/utils/pdfinfo.cc"
#undef main

namespace {

static std::string JoinPath(const std::string &dir, const std::string &base)
{
#ifdef _WIN32
  const char sep = '\\';
#else
  const char sep = '/';
#endif
  if (dir.empty()) {
    return base;
  }
  if (dir.back() == sep) {
    return dir + base;
  }
  return dir + sep + base;
}

static std::string TempDir()
{
  const char *tmp = std::getenv("TMPDIR");
  if (tmp && *tmp) {
    return std::string(tmp);
  }
#ifdef _WIN32
  const char *tmp2 = std::getenv("TEMP");
  if (tmp2 && *tmp2) {
    return std::string(tmp2);
  }
#endif
  return std::string("/tmp");
}

static std::string MakeUniquePath(const std::string &prefix, const std::string &suffix)
{
  static int counter = 0;
  std::ostringstream oss;
  oss << prefix << "_" << ::getpid() << "_" << (++counter) << suffix;
  return JoinPath(TempDir(), oss.str());
}

// Builds a minimal valid PDF with a single empty page and (optionally) an /Info dictionary.
// `infoEntries` maps PDF name keys to *literal string* values (without surrounding parentheses).
static std::string WriteMinimalPdfWithInfo_2673(const std::map<std::string, std::string> &infoEntries,
                                                bool includeInfoDict)
{
  struct Obj {
    int num;
    std::string body;
  };

  std::vector<Obj> objs;

  // 1 0 obj: Catalog
  objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R >>"});

  // 2 0 obj: Pages
  objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"});

  // 3 0 obj: Page
  objs.push_back({3, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>"});

  // 4 0 obj: Empty contents stream
  objs.push_back({4, "<< /Length 0 >>\nstream\nendstream"});

  int infoObjNum = -1;
  if (includeInfoDict) {
    infoObjNum = 5;
    std::ostringstream info;
    info << "<<\n";
    for (const auto &kv : infoEntries) {
      // keys are names (e.g. GTS_PDFA1Version) and values are literal strings.
      info << "  /" << kv.first << " (" << kv.second << ")\n";
    }
    info << ">>";
    objs.push_back({infoObjNum, info.str()});
  }

  std::ostringstream out;
  out << "%PDF-1.4\n";

  // Write objects while tracking offsets.
  std::vector<long long> offsets;
  offsets.resize(static_cast<size_t>(objs.size()) + 1, 0); // index by obj number (small here)

  auto writeObj = [&](int num, const std::string &body) {
    // Record current offset in bytes.
    std::string sofar = out.str();
    offsets[static_cast<size_t>(num)] = static_cast<long long>(sofar.size());
    out << num << " 0 obj\n" << body << "\nendobj\n";
  };

  for (const auto &o : objs) {
    writeObj(o.num, o.body);
  }

  // xref offset
  const long long xrefPos = static_cast<long long>(out.str().size());

  // xref table: objects 0..max
  const int maxObj = includeInfoDict ? 5 : 4;
  out << "xref\n0 " << (maxObj + 1) << "\n";
  // object 0: free
  out << "0000000000 65535 f \n";
  for (int i = 1; i <= maxObj; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010lld", offsets[static_cast<size_t>(i)]);
    out << buf << " 00000 n \n";
  }

  // trailer
  out << "trailer\n<< /Size " << (maxObj + 1) << " /Root 1 0 R";
  if (includeInfoDict) {
    out << " /Info " << infoObjNum << " 0 R";
  }
  out << " >>\nstartxref\n" << xrefPos << "\n%%EOF\n";

  const std::string path = MakeUniquePath("poppler_pdfinfo_2673", ".pdf");
  std::ofstream f(path, std::ios::binary);
  f << out.str();
  f.close();
  return path;
}

static std::unique_ptr<PDFDoc> OpenPdf_2673(const std::string &path)
{
  auto gs = std::make_unique<GooString>(path.c_str());
  std::optional<GooString> none;
  // xref reconstructed callback: no-op
  return std::make_unique<PDFDoc>(std::move(gs), none, none, []() {});
}

static std::unique_ptr<UnicodeMap> MakeUtf8Map_2673()
{
  // Use parse so we don't assume constructor ranges/func. If parse fails in some builds,
  // fall back to a direct constructor with unicodeOut=true.
  auto m = UnicodeMap::parse("UTF-8");
  if (!m) {
    m = std::make_unique<UnicodeMap>("UTF-8", true, 0);
  }
  return m;
}

} // namespace

TEST(PdfInfoPrintPdfSubtypeTest_2673, NoInfoDictProducesNoOutput_2673)
{
  const std::string pdfPath = WriteMinimalPdfWithInfo_2673(/*infoEntries=*/{}, /*includeInfoDict=*/false);
  auto doc = OpenPdf_2673(pdfPath);
  ASSERT_TRUE(doc);

  auto uMap = MakeUtf8Map_2673();
  ASSERT_TRUE(uMap);

  testing::internal::CaptureStdout();
  printPdfSubtype(doc.get(), uMap.get());
  const std::string out = testing::internal::GetCapturedStdout();

  // Observable behavior: with no /Info dict (or non-dict doc info), function should not print
  // any subtype details.
  EXPECT_TRUE(out.empty());
}

TEST(PdfInfoPrintPdfSubtypeTest_2673, InfoDictWithoutSubtypeProducesNoOutput_2673)
{
  // Include an /Info dict but without any known GTS_* subtype version keys.
  const std::string pdfPath =
      WriteMinimalPdfWithInfo_2673({{"Title", "Just a title"}}, /*includeInfoDict=*/true);
  auto doc = OpenPdf_2673(pdfPath);
  ASSERT_TRUE(doc);

  auto uMap = MakeUtf8Map_2673();
  ASSERT_TRUE(uMap);

  testing::internal::CaptureStdout();
  printPdfSubtype(doc.get(), uMap.get());
  const std::string out = testing::internal::GetCapturedStdout();

  // If Poppler doesn't detect a supported subtype (subtypeNull/subtypeNone), it should early-return.
  EXPECT_TRUE(out.empty());
}

TEST(PdfInfoPrintPdfSubtypeTest_2673, PdfASubtypePrintsExpectedHeadingsAndAbbreviation_2673)
{
  // Provide the specific key used by printPdfSubtype for PDF/A.
  // We intentionally only assert on stable, user-visible headings and the base abbreviation.
  const std::string pdfPath =
      WriteMinimalPdfWithInfo_2673({{"GTS_PDFA1Version", "1A"}}, /*includeInfoDict=*/true);
  auto doc = OpenPdf_2673(pdfPath);
  ASSERT_TRUE(doc);

  auto uMap = MakeUtf8Map_2673();
  ASSERT_TRUE(uMap);

  testing::internal::CaptureStdout();
  printPdfSubtype(doc.get(), uMap.get());
  const std::string out = testing::internal::GetCapturedStdout();

  // Normal operation: when subtype is recognized, these labels should appear.
  EXPECT_NE(out.find("Title:"), std::string::npos);
  EXPECT_NE(out.find("Abbreviation:"), std::string::npos);
  EXPECT_NE(out.find("Subtitle:"), std::string::npos);
  EXPECT_NE(out.find("Standard:"), std::string::npos);

  // PDF/A abbreviation should be present as a prefix (may have "-<part>" appended).
  EXPECT_NE(out.find("Abbreviation: PDF/A"), std::string::npos);

  // Should reference the PDF/A ISO description line that the tool prints as "Title:".
  EXPECT_NE(out.find("ISO 19005"), std::string::npos);
}

TEST(PdfInfoPrintPdfSubtypeTest_2673, PdfXSubtypePrintsExpectedHeadingsAndAbbreviation_2673)
{
  // Provide the specific key used by printPdfSubtype for PDF/X.
  const std::string pdfPath =
      WriteMinimalPdfWithInfo_2673({{"GTS_PDFXVersion", "1:2001"}}, /*includeInfoDict=*/true);
  auto doc = OpenPdf_2673(pdfPath);
  ASSERT_TRUE(doc);

  auto uMap = MakeUtf8Map_2673();
  ASSERT_TRUE(uMap);

  testing::internal::CaptureStdout();
  printPdfSubtype(doc.get(), uMap.get());
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_NE(out.find("Title:"), std::string::npos);
  EXPECT_NE(out.find("Abbreviation:"), std::string::npos);
  EXPECT_NE(out.find("Subtitle:"), std::string::npos);
  EXPECT_NE(out.find("Standard:"), std::string::npos);

  // PDF/X abbreviation should be present as a prefix (may have a specific "-1:2001", "-3:2002", etc).
  EXPECT_NE(out.find("Abbreviation: PDF/X"), std::string::npos);

  // PDF/X title references ISO 15930 in the text.
  EXPECT_NE(out.find("ISO 15930"), std::string::npos);
}