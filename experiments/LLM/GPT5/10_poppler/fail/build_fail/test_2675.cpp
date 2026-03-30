// pdfinfo_printInfo_test_2675.cc
//
// Unit tests for printInfo() in utils/pdfinfo.cc
// - Treat implementation as black box (verify only observable stdout output).
// - Use real PDFDoc instances backed by minimal PDF files we generate on the fly.
// - Access static printInfo() by including pdfinfo.cc into this translation unit.
//
// NOTE: pdfinfo.cc in Poppler utils commonly has a main(). To avoid conflicts, we
//       rename main before including it.

#include <gtest/gtest.h>

#include <cerrno>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

#if defined(_WIN32)
#include <io.h>
#define stat _stat
struct _stat;
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

// Rename main if pdfinfo.cc defines one.
#define main pdfinfo_main_2675
#include "utils/pdfinfo.cc"
#undef main

#include "poppler/GooString.h"
#include "poppler/PDFDoc.h"
#include "poppler/UnicodeMap.h"

namespace {

class PdfInfoPrintInfoTest_2675 : public ::testing::Test {
protected:
  void SetUp() override {
    // These are globals referenced by printInfo() / pdfinfo.cc.
    ::printBoxes = false;
    ::isoDates = false;
    ::rawDates = false;

    // firstPage/lastPage are defined in pdftoppm.cc in the real codebase; in tests
    // they are typically linked in. If not, pdfinfo.cc may still reference them.
    // We set them before calling printInfo().
    ::firstPage = 1;
    ::lastPage = 0;
  }

  static std::string TempPath(const std::string &name) {
#if defined(_WIN32)
    // Keep it simple for typical CI envs; adjust if needed.
    return name;
#else
    std::string base = "/tmp/";
    base += name;
    return base;
#endif
  }

  static long long FileSize(const std::string &path) {
#if defined(_WIN32)
    struct _stat st;
    if (_stat(path.c_str(), &st) != 0) {
      return -1;
    }
    return static_cast<long long>(st.st_size);
#else
    struct stat st;
    if (stat(path.c_str(), &st) != 0) {
      return -1;
    }
    return static_cast<long long>(st.st_size);
#endif
  }

  // Write a minimal PDF with:
  // - N pages (each with its own MediaBox and Rotate)
  // - Trailer /Info (standard keys and optional custom key)
  // - Optional catalog /Metadata stream
  //
  // We keep objects simple and avoid compression.
  static void WriteMinimalPdf(const std::string &path,
                              const std::vector<std::pair<double, double>> &pageSizesPts,
                              const std::vector<int> &pageRotates,
                              bool addCustomInfoKey,
                              bool addMetadataStream) {
    ASSERT_EQ(pageSizesPts.size(), pageRotates.size());

    struct Obj {
      int num;
      std::string body;
    };
    std::vector<Obj> objs;

    // Object numbering:
    // 1: Catalog
    // 2: Pages
    // 3..(2+N): Page objects
    // then: Contents objects (one per page)
    // then: Info dict
    // optionally: Metadata stream
    const int nPages = static_cast<int>(pageSizesPts.size());
    const int firstPageObj = 3;
    const int firstContentsObj = firstPageObj + nPages;
    const int infoObj = firstContentsObj + nPages;
    const int metadataObj = addMetadataStream ? (infoObj + 1) : -1;

    // Contents objects
    for (int i = 0; i < nPages; ++i) {
      const int objNum = firstContentsObj + i;
      // Empty content stream.
      std::string stream = "stream\n\nendstream";
      objs.push_back({objNum, "<< /Length 0 >>\n" + stream});
    }

    // Page objects
    for (int i = 0; i < nPages; ++i) {
      const int objNum = firstPageObj + i;
      const double w = pageSizesPts[i].first;
      const double h = pageSizesPts[i].second;
      const int rotate = pageRotates[i];

      // Set both MediaBox and CropBox to make crop getters consistent.
      // Minimal Resources dict to satisfy parsers.
      std::string body;
      body += "<< /Type /Page\n";
      body += "   /Parent 2 0 R\n";
      body += "   /Resources << >>\n";
      body += "   /MediaBox [0 0 " + std::to_string(w) + " " + std::to_string(h) + "]\n";
      body += "   /CropBox  [0 0 " + std::to_string(w) + " " + std::to_string(h) + "]\n";
      body += "   /Rotate " + std::to_string(rotate) + "\n";
      body += "   /Contents " + std::to_string(firstContentsObj + i) + " 0 R\n";
      body += ">>";
      objs.push_back({objNum, body});
    }

    // Pages object
    {
      std::string kids = "[ ";
      for (int i = 0; i < nPages; ++i) {
        kids += std::to_string(firstPageObj + i) + " 0 R ";
      }
      kids += "]";
      std::string body;
      body += "<< /Type /Pages\n";
      body += "   /Kids " + kids + "\n";
      body += "   /Count " + std::to_string(nPages) + "\n";
      body += ">>";
      objs.push_back({2, body});
    }

    // Metadata stream (optional) referenced from Catalog
    if (addMetadataStream) {
      // Minimal XMP-like content (not required to be valid for hasMetadata=true).
      const std::string xml = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\"/>";
      std::string body;
      body += "<< /Type /Metadata /Subtype /XML /Length " + std::to_string(xml.size()) + " >>\n";
      body += "stream\n" + xml + "\nendstream";
      objs.push_back({metadataObj, body});
    }

    // Catalog object
    {
      std::string body;
      body += "<< /Type /Catalog\n";
      body += "   /Pages 2 0 R\n";
      if (addMetadataStream) {
        body += "   /Metadata " + std::to_string(metadataObj) + " 0 R\n";
      }
      body += ">>";
      objs.push_back({1, body});
    }

    // Info dict object (with standard keys; optional custom key)
    {
      std::string body;
      body += "<<\n";
      body += "  /Title (T)\n";
      body += "  /Author (A)\n";
      body += "  /Subject (S)\n";
      body += "  /Keywords (K)\n";
      body += "  /Creator (C)\n";
      body += "  /Producer (P)\n";
      body += "  /CreationDate (D:20250101000000Z)\n";
      body += "  /ModDate (D:20250102000000Z)\n";
      if (addCustomInfoKey) {
        body += "  /MyCustomKey (X)\n";
      }
      body += ">>";
      objs.push_back({infoObj, body});
    }

    // Sort objects by number for stable xref generation.
    std::sort(objs.begin(), objs.end(), [](const Obj &a, const Obj &b) { return a.num < b.num; });

    // Write file with xref.
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    ASSERT_TRUE(out.is_open());

    out << "%PDF-1.4\n";

    // Track offsets: index by object number up to max.
    int maxObj = infoObj;
    if (addMetadataStream) maxObj = metadataObj;
    std::vector<long long> offsets(maxObj + 1, 0);

    for (const auto &o : objs) {
      offsets[o.num] = static_cast<long long>(out.tellp());
      out << o.num << " 0 obj\n";
      out << o.body << "\n";
      out << "endobj\n";
    }

    const long long xrefPos = static_cast<long long>(out.tellp());
    out << "xref\n";
    out << "0 " << (maxObj + 1) << "\n";
    out << "0000000000 65535 f \n";
    for (int i = 1; i <= maxObj; ++i) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010lld", offsets[i]);
      out << buf << " 00000 n \n";
    }

    out << "trailer\n";
    out << "<< /Size " << (maxObj + 1) << "\n";
    out << "   /Root 1 0 R\n";
    out << "   /Info " << infoObj << " 0 R\n";
    out << ">>\n";
    out << "startxref\n";
    out << xrefPos << "\n";
    out << "%%EOF\n";
    out.close();
  }

  static std::unique_ptr<PDFDoc> OpenDocOrFail(const std::string &path) {
    auto fileName = std::make_unique<GooString>(path.c_str());
    auto doc = std::make_unique<PDFDoc>(std::move(fileName),
                                        /*ownerPassword=*/std::nullopt,
                                        /*userPassword=*/std::nullopt,
                                        /*xrefReconstructedCallback=*/[]() {});
    EXPECT_TRUE(doc->isOk());
    return doc;
  }
};

TEST_F(PdfInfoPrintInfoTest_2675, SinglePageLetter_NoCustom_NoMetadataStream_2675) {
  const std::string path = TempPath("pdfinfo_printInfo_letter_2675.pdf");
  WriteMinimalPdf(
      path,
      /*pageSizesPts=*/{{612.0, 792.0}}, // US Letter
      /*pageRotates=*/{0},
      /*addCustomInfoKey=*/false,
      /*addMetadataStream=*/false);

  auto doc = OpenDocOrFail(path);
  ASSERT_TRUE(doc);
  auto uMap = UnicodeMap::parse("UTF-8");
  ASSERT_TRUE(uMap);

  ::firstPage = 1;
  ::lastPage = doc->getNumPages();
  ASSERT_EQ(::lastPage, 1);

  const long long filesize = FileSize(path);
  ASSERT_GT(filesize, 0);

  testing::internal::CaptureStdout();
  printInfo(doc.get(), uMap.get(), filesize, /*multiPage=*/false);
  const std::string out = testing::internal::GetCapturedStdout();

  // Observable outputs we can rely on.
  EXPECT_NE(out.find("Custom Metadata: no\n"), std::string::npos);
  EXPECT_NE(out.find("Metadata Stream: no\n"), std::string::npos);

  EXPECT_NE(out.find("Form: none\n"), std::string::npos);
  EXPECT_NE(out.find("JavaScript: no\n"), std::string::npos);

  EXPECT_NE(out.find("Pages: 1\n"), std::string::npos);

  // Page size line should include "(letter)" for 612x792 (or swapped).
  EXPECT_NE(out.find("Page size:"), std::string::npos);
  EXPECT_NE(out.find("(letter)"), std::string::npos);

  // Rotation line in single-page mode.
  EXPECT_NE(out.find("Page rot: 0\n"), std::string::npos);

  // Not encrypted in our minimal PDF.
  EXPECT_NE(out.find("Encrypted: no\n"), std::string::npos);

  // File size line uses the argument we passed.
  EXPECT_NE(out.find("File size: "), std::string::npos);
  EXPECT_NE(out.find(" bytes\n"), std::string::npos);
}

TEST_F(PdfInfoPrintInfoTest_2675, SinglePageA4_PrintsAseriesTag_2675) {
  const std::string path = TempPath("pdfinfo_printInfo_a4_2675.pdf");
  // A4 in points (approx): 595.276 x 841.89
  WriteMinimalPdf(
      path,
      /*pageSizesPts=*/{{595.276, 841.89}},
      /*pageRotates=*/{0},
      /*addCustomInfoKey=*/false,
      /*addMetadataStream=*/false);

  auto doc = OpenDocOrFail(path);
  ASSERT_TRUE(doc);
  auto uMap = UnicodeMap::parse("UTF-8");
  ASSERT_TRUE(uMap);

  ::firstPage = 1;
  ::lastPage = doc->getNumPages();
  ASSERT_EQ(::lastPage, 1);

  const long long filesize = FileSize(path);
  ASSERT_GT(filesize, 0);

  testing::internal::CaptureStdout();
  printInfo(doc.get(), uMap.get(), filesize, /*multiPage=*/false);
  const std::string out = testing::internal::GetCapturedStdout();

  // Should identify as an A-series page. A4 is the typical match.
  // We don't over-constrain if rounding/tolerance causes a different A#,
  // but we do require an "(A" tag.
  EXPECT_NE(out.find("Page size:"), std::string::npos);
  EXPECT_NE(out.find("(A"), std::string::npos);
}

TEST_F(PdfInfoPrintInfoTest_2675, MultiPage_PrintsPerPagePrefixesAndRotations_2675) {
  const std::string path = TempPath("pdfinfo_printInfo_multipage_2675.pdf");
  WriteMinimalPdf(
      path,
      /*pageSizesPts=*/{{612.0, 792.0}, {612.0, 792.0}},
      /*pageRotates=*/{0, 90},
      /*addCustomInfoKey=*/false,
      /*addMetadataStream=*/false);

  auto doc = OpenDocOrFail(path);
  ASSERT_TRUE(doc);
  auto uMap = UnicodeMap::parse("UTF-8");
  ASSERT_TRUE(uMap);

  ::firstPage = 1;
  ::lastPage = doc->getNumPages();
  ASSERT_EQ(::lastPage, 2);

  const long long filesize = FileSize(path);
  ASSERT_GT(filesize, 0);

  testing::internal::CaptureStdout();
  printInfo(doc.get(), uMap.get(), filesize, /*multiPage=*/true);
  const std::string out = testing::internal::GetCapturedStdout();

  // In multiPage mode, size/rot lines are prefixed with "Page %4d".
  EXPECT_NE(out.find("Page    1 size:"), std::string::npos);
  EXPECT_NE(out.find("Page    1 rot: 0\n"), std::string::npos);

  EXPECT_NE(out.find("Page    2 size:"), std::string::npos);
  EXPECT_NE(out.find("Page    2 rot: 90\n"), std::string::npos);
}

TEST_F(PdfInfoPrintInfoTest_2675, DetectsCustomMetadataAndMetadataStream_2675) {
  const std::string path = TempPath("pdfinfo_printInfo_custom_meta_2675.pdf");
  WriteMinimalPdf(
      path,
      /*pageSizesPts=*/{{612.0, 792.0}},
      /*pageRotates=*/{0},
      /*addCustomInfoKey=*/true,
      /*addMetadataStream=*/true);

  auto doc = OpenDocOrFail(path);
  ASSERT_TRUE(doc);
  auto uMap = UnicodeMap::parse("UTF-8");
  ASSERT_TRUE(uMap);

  ::firstPage = 1;
  ::lastPage = doc->getNumPages();
  ASSERT_EQ(::lastPage, 1);

  const long long filesize = FileSize(path);
  ASSERT_GT(filesize, 0);

  testing::internal::CaptureStdout();
  printInfo(doc.get(), uMap.get(), filesize, /*multiPage=*/false);
  const std::string out = testing::internal::GetCapturedStdout();

  // Custom metadata is reported "yes" when Info dict contains a non-standard key.
  EXPECT_NE(out.find("Custom Metadata: yes\n"), std::string::npos);

  // Metadata stream is reported "yes" when doc->readMetadata() returns non-null.
  EXPECT_NE(out.find("Metadata Stream: yes\n"), std::string::npos);
}

} // namespace