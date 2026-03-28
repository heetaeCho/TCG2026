// pdfinfo_printCustomInfo_test_2674.cc
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "poppler/GooString.h"
#include "poppler/PDFDoc.h"
#include "poppler/UnicodeMap.h"

using ::testing::HasSubstr;
using ::testing::Not;

namespace {

// Creates a minimal, valid single-page PDF file.
// Returns the path to the created file.
static std::string CreateMinimalPdfFile_2674(const std::string &path) {
  std::ofstream out(path, std::ios::binary | std::ios::trunc);
  EXPECT_TRUE(out.is_open());

  // We will write objects while tracking their byte offsets for xref.
  auto write = [&](const std::string &s) { out.write(s.data(), static_cast<std::streamsize>(s.size())); };
  std::vector<std::streamoff> offsets;

  write("%PDF-1.4\n");
  write("%\xE2\xE3\xCF\xD3\n"); // binary comment

  offsets.push_back(out.tellp());
  write("1 0 obj\n");
  write("<< /Type /Catalog /Pages 2 0 R >>\n");
  write("endobj\n");

  offsets.push_back(out.tellp());
  write("2 0 obj\n");
  write("<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n");
  write("endobj\n");

  offsets.push_back(out.tellp());
  write("3 0 obj\n");
  write("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 100 100] /Contents 4 0 R /Resources << >> >>\n");
  write("endobj\n");

  offsets.push_back(out.tellp());
  write("4 0 obj\n");
  write("<< /Length 0 >>\n");
  write("stream\n");
  write("\n");
  write("endstream\n");
  write("endobj\n");

  const std::streamoff xref_pos = out.tellp();
  write("xref\n");
  write("0 5\n");
  write("0000000000 65535 f \n");

  auto write_xref_entry = [&](std::streamoff off) {
    // 10-digit, zero-padded byte offset; generation 00000; in-use 'n'
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010lld 00000 n \n", static_cast<long long>(off));
    write(std::string(buf));
  };

  // Objects 1..4
  ASSERT_EQ(offsets.size(), 4u);
  for (auto off : offsets) {
    write_xref_entry(off);
  }

  write("trailer\n");
  write("<< /Size 5 /Root 1 0 R >>\n");
  write("startxref\n");
  write(std::to_string(static_cast<long long>(xref_pos)));
  write("\n%%EOF\n");

  out.flush();
  out.close();
  return path;
}

static std::unique_ptr<PDFDoc> OpenPdfDoc_2674(const std::string &path) {
  auto gs = std::make_unique<GooString>(path.c_str());
  auto doc = std::make_unique<PDFDoc>(
      std::move(gs),
      std::optional<GooString>{},   // ownerPassword
      std::optional<GooString>{},   // userPassword
      std::function<void(void)>{}   // xrefReconstructedCallback
  );
  return doc;
}

} // namespace

// Trick to make pdfinfo.cc testable: compile it into this TU and rename its main().
#define main pdfinfo_main_2674
#include "./TestProjects/poppler/utils/pdfinfo.cc"
#undef main

// NOTE: printCustomInfo is `static` in pdfinfo.cc, but since we include the .cc above,
// it is in the same translation unit and callable here.

class PrintCustomInfoTest_2674 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure deterministic date printing behavior for tests that assert raw strings.
    // These are globals in pdfinfo.cc.
    isoDates = false;
    rawDates = true;
  }
};

TEST_F(PrintCustomInfoTest_2674, NoOutputWhenDocInfoIsNotDict_2674) {
  const std::string path = CreateMinimalPdfFile_2674("/tmp/printCustomInfo_noinfo_2674.pdf");
  auto doc = OpenPdfDoc_2674(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  // Remove DocInfo so getDocInfo() should not be a dict.
  doc->removeDocInfo();

  auto uMap = UnicodeMap::parse("UTF-8");
  ASSERT_TRUE(uMap);

  testing::internal::CaptureStdout();
  printCustomInfo(doc.get(), uMap.get());
  const std::string output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(output.empty());
}

TEST_F(PrintCustomInfoTest_2674, PrintsCustomStringKeysSortedAndSkipsTrapped_2674) {
  const std::string path = CreateMinimalPdfFile_2674("/tmp/printCustomInfo_customkeys_2674.pdf");
  auto doc = OpenPdfDoc_2674(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  // Add keys in non-sorted order to verify output uses sorted order.
  doc->setDocInfoStringEntry("BKey", std::make_unique<GooString>("BVal"));
  doc->setDocInfoStringEntry("AKey", std::make_unique<GooString>("AVal"));

  // "Trapped" must be skipped by printCustomInfo.
  doc->setDocInfoStringEntry("Trapped", std::make_unique<GooString>("True"));

  auto uMap = UnicodeMap::parse("UTF-8");
  ASSERT_TRUE(uMap);

  testing::internal::CaptureStdout();
  printCustomInfo(doc.get(), uMap.get());
  const std::string output = testing::internal::GetCapturedStdout();

  EXPECT_THAT(output, HasSubstr("AKey:"));
  EXPECT_THAT(output, HasSubstr("AVal"));
  EXPECT_THAT(output, HasSubstr("BKey:"));
  EXPECT_THAT(output, HasSubstr("BVal"));
  EXPECT_THAT(output, Not(HasSubstr("Trapped")));

  // Sorted order: AKey line should appear before BKey line.
  const auto posA = output.find("AKey:");
  const auto posB = output.find("BKey:");
  ASSERT_NE(posA, std::string::npos);
  ASSERT_NE(posB, std::string::npos);
  EXPECT_LT(posA, posB);
}

TEST_F(PrintCustomInfoTest_2674, PrintsCreationAndModDatesUsingRawStringWhenRawDatesEnabled_2674) {
  const std::string path = CreateMinimalPdfFile_2674("/tmp/printCustomInfo_dates_2674.pdf");
  auto doc = OpenPdfDoc_2674(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  // Force raw date printing path in printCustomInfo().
  isoDates = false;
  rawDates = true;

  // Set dates. These setters correspond to "CreationDate" / "ModDate" entries.
  const std::string creation = "D:20240224010203+09'00'";
  const std::string mod = "D:20240225040506+09'00'";
  doc->setDocInfoCreatDate(std::make_unique<GooString>(creation.c_str()));
  doc->setDocInfoModDate(std::make_unique<GooString>(mod.c_str()));

  auto uMap = UnicodeMap::parse("UTF-8");
  ASSERT_TRUE(uMap);

  testing::internal::CaptureStdout();
  printCustomInfo(doc.get(), uMap.get());
  const std::string output = testing::internal::GetCapturedStdout();

  // We only assert the observable, high-level contract: the labeled lines appear and contain raw strings.
  EXPECT_THAT(output, HasSubstr("CreationDate:"));
  EXPECT_THAT(output, HasSubstr(creation));
  EXPECT_THAT(output, HasSubstr("ModDate:"));
  EXPECT_THAT(output, HasSubstr(mod));
}

TEST_F(PrintCustomInfoTest_2674, HandlesLongKeyNames_2674) {
  const std::string path = CreateMinimalPdfFile_2674("/tmp/printCustomInfo_longkey_2674.pdf");
  auto doc = OpenPdfDoc_2674(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  const std::string longKey = "ThisIsAVeryLongKeyNameOver16Chars";
  const std::string longVal = "SomeValue";
  doc->setDocInfoStringEntry(longKey.c_str(), std::make_unique<GooString>(longVal.c_str()));

  auto uMap = UnicodeMap::parse("UTF-8");
  ASSERT_TRUE(uMap);

  testing::internal::CaptureStdout();
  printCustomInfo(doc.get(), uMap.get());
  const std::string output = testing::internal::GetCapturedStdout();

  EXPECT_THAT(output, HasSubstr(longKey + ":"));
  EXPECT_THAT(output, HasSubstr(longVal));
}