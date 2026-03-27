// SPDX-License-Identifier: GPL-2.0-or-later
// Unit tests for PDFDoc::getPageRotate
//
// File under test: ./TestProjects/poppler/poppler/PDFDoc.h
//
// NOTE: Tests treat PDFDoc as a black box and validate only observable behavior.

#include <gtest/gtest.h>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <optional>
#include <random>
#include <sstream>
#include <string>

#include "poppler/PDFDoc.h"
#include "poppler/GooString.h"

namespace {

class PDFDocGetPageRotateTest_958 : public ::testing::Test {
protected:
  static std::string MakeUniqueTempPath(const std::string &suffix) {
    const auto dir = std::filesystem::temp_directory_path();

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<unsigned long long> dist;

    std::ostringstream name;
    name << "poppler_pdfdoc_getpagerotate_" << std::hex << dist(gen) << suffix;

    return (dir / name.str()).string();
  }

  static std::string BuildSinglePagePdfWithOptionalRotate(const std::optional<int> rotate) {
    // Build a minimal, valid PDF with:
    // 1 0 obj: Catalog
    // 2 0 obj: Pages
    // 3 0 obj: Page (optional /Rotate)
    // 4 0 obj: Contents stream
    //
    // We compute xref offsets dynamically to keep it valid.
    std::ostringstream out;
    out << "%PDF-1.4\n";

    auto writeObj = [&](int objNum, const std::string &body, long long &offsetOut) {
      offsetOut = static_cast<long long>(out.tellp());
      out << objNum << " 0 obj\n" << body << "\nendobj\n";
    };

    long long off1 = 0, off2 = 0, off3 = 0, off4 = 0;

    writeObj(1, "<< /Type /Catalog /Pages 2 0 R >>", off1);
    writeObj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>", off2);

    std::ostringstream pageDict;
    pageDict << "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R";
    if (rotate.has_value()) {
      pageDict << " /Rotate " << *rotate;
    }
    pageDict << " >>";
    writeObj(3, pageDict.str(), off3);

    const std::string streamData = "q\nQ\n";
    std::ostringstream contents;
    contents << "<< /Length " << streamData.size() << " >>\n"
             << "stream\n"
             << streamData
             << "endstream";
    writeObj(4, contents.str(), off4);

    const long long xrefPos = static_cast<long long>(out.tellp());
    out << "xref\n";
    out << "0 5\n";
    out << "0000000000 65535 f \n";

    auto xrefEntry = [&](long long off) {
      // 10-digit, zero-padded offset + " 00000 n"
      std::ostringstream e;
      e << std::setw(10) << std::setfill('0') << off << " 00000 n \n";
      return e.str();
    };

    out << xrefEntry(off1);
    out << xrefEntry(off2);
    out << xrefEntry(off3);
    out << xrefEntry(off4);

    out << "trailer\n";
    out << "<< /Size 5 /Root 1 0 R >>\n";
    out << "startxref\n";
    out << xrefPos << "\n";
    out << "%%EOF\n";

    return out.str();
  }

  static void WriteFile(const std::string &path, const std::string &bytes) {
    std::ofstream ofs(path, std::ios::binary);
    ASSERT_TRUE(ofs.is_open());
    ofs.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    ASSERT_TRUE(ofs.good());
  }

  static std::unique_ptr<PDFDoc> OpenPdfFromPath(const std::string &path) {
    auto gs = std::make_unique<GooString>(path.c_str());
    std::optional<GooString> ownerPw;
    std::optional<GooString> userPw;
    std::function<void(void)> cb = []() {};
    return std::make_unique<PDFDoc>(std::move(gs), ownerPw, userPw, cb);
  }
};

TEST_F(PDFDocGetPageRotateTest_958, ReturnsRotateValueWhenPageHasRotate_958) {
  const std::string path = MakeUniqueTempPath(".pdf");
  WriteFile(path, BuildSinglePagePdfWithOptionalRotate(90));

  auto doc = OpenPdfFromPath(path);
  ASSERT_NE(doc, nullptr);

  // Observable behavior: if page exists and has rotation, getPageRotate should reflect it.
  EXPECT_EQ(doc->getPageRotate(1), 90);

  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(PDFDocGetPageRotateTest_958, ReturnsZeroWhenPageHasNoRotate_958) {
  const std::string path = MakeUniqueTempPath(".pdf");
  WriteFile(path, BuildSinglePagePdfWithOptionalRotate(std::nullopt));

  auto doc = OpenPdfFromPath(path);
  ASSERT_NE(doc, nullptr);

  // Observable behavior from inline implementation: should be 0 when page exists but rotation is absent.
  EXPECT_EQ(doc->getPageRotate(1), 0);

  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(PDFDocGetPageRotateTest_958, ReturnsZeroWhenPageNumberIsOutOfRange_958) {
  const std::string path = MakeUniqueTempPath(".pdf");
  WriteFile(path, BuildSinglePagePdfWithOptionalRotate(180));

  auto doc = OpenPdfFromPath(path);
  ASSERT_NE(doc, nullptr);

  // Boundary / error-style behavior: if getPage(page) is null, getPageRotate returns 0.
  EXPECT_EQ(doc->getPageRotate(0), 0);
  EXPECT_EQ(doc->getPageRotate(-1), 0);
  EXPECT_EQ(doc->getPageRotate(2), 0);
  EXPECT_EQ(doc->getPageRotate(9999), 0);

  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(PDFDocGetPageRotateTest_958, ReturnsZeroOnErrorPdfDocInstance_958) {
  // Observable behavior: even for an "error" doc instance, getPageRotate should not crash and should
  // return 0 when the page cannot be obtained (getPage(page) == nullptr).
  auto errDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("nonexistent.pdf"));
  ASSERT_NE(errDoc, nullptr);

  EXPECT_EQ(errDoc->getPageRotate(1), 0);
  EXPECT_EQ(errDoc->getPageRotate(0), 0);
  EXPECT_EQ(errDoc->getPageRotate(-5), 0);
}

} // namespace