// pdfinfo_printLinkDest_test_2670.cc
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

// pdfinfo.cc is a utility with its own main().  To include it into this test TU
// (so we can call the file-static printLinkDest), rename main to avoid conflicts.
#define main pdfinfo_main_2670
#include "TestProjects/poppler/utils/pdfinfo.cc"
#undef main

#include "poppler/Array.h"
#include "poppler/Link.h"
#include "poppler/Object.h"

namespace {

class PrintLinkDestTest_2670 : public ::testing::Test {
protected:
  // Keep Arrays alive for the lifetime of LinkDest usage (constructor behavior is
  // treated as a black box; this guarantees safety regardless of ownership/copying).
  std::vector<std::unique_ptr<Array>> arrays_;

  std::unique_ptr<LinkDest> MakeDestFromArray(std::unique_ptr<Array> a) {
    Array *raw = a.get();
    arrays_.push_back(std::move(a));
    return std::make_unique<LinkDest>(raw);
  }

  // Helpers to build destination arrays in standard PDF destination form:
  // [ page /Type ...params... ]
  std::unique_ptr<LinkDest> MakeXYZ_AllNull() {
    auto a = std::make_unique<Array>(nullptr);
    a->add(Object(1));
    a->add(Object(objName, "XYZ"));
    a->add(Object(objNull)); // left
    a->add(Object(objNull)); // top
    a->add(Object(objNull)); // zoom
    return MakeDestFromArray(std::move(a));
  }

  std::unique_ptr<LinkDest> MakeXYZ_LeftOnly(double left) {
    auto a = std::make_unique<Array>(nullptr);
    a->add(Object(1));
    a->add(Object(objName, "XYZ"));
    a->add(Object(left));    // left
    a->add(Object(objNull)); // top
    a->add(Object(objNull)); // zoom
    return MakeDestFromArray(std::move(a));
  }

  std::unique_ptr<LinkDest> MakeFit() {
    auto a = std::make_unique<Array>(nullptr);
    a->add(Object(1));
    a->add(Object(objName, "Fit"));
    return MakeDestFromArray(std::move(a));
  }

  std::unique_ptr<LinkDest> MakeFitH_Null() {
    auto a = std::make_unique<Array>(nullptr);
    a->add(Object(1));
    a->add(Object(objName, "FitH"));
    a->add(Object(objNull)); // top
    return MakeDestFromArray(std::move(a));
  }

  std::unique_ptr<LinkDest> MakeFitV_Null() {
    auto a = std::make_unique<Array>(nullptr);
    a->add(Object(1));
    a->add(Object(objName, "FitV"));
    a->add(Object(objNull)); // left
    return MakeDestFromArray(std::move(a));
  }

  std::unique_ptr<LinkDest> MakeFitR(double left, double bottom, double right, double top) {
    auto a = std::make_unique<Array>(nullptr);
    a->add(Object(1));
    a->add(Object(objName, "FitR"));
    a->add(Object(left));
    a->add(Object(bottom));
    a->add(Object(right));
    a->add(Object(top));
    return MakeDestFromArray(std::move(a));
  }

  std::unique_ptr<LinkDest> MakeFitB() {
    auto a = std::make_unique<Array>(nullptr);
    a->add(Object(1));
    a->add(Object(objName, "FitB"));
    return MakeDestFromArray(std::move(a));
  }

  std::unique_ptr<LinkDest> MakeFitBH_Null() {
    auto a = std::make_unique<Array>(nullptr);
    a->add(Object(1));
    a->add(Object(objName, "FitBH"));
    a->add(Object(objNull)); // top
    return MakeDestFromArray(std::move(a));
  }

  std::unique_ptr<LinkDest> MakeFitBV_Null() {
    auto a = std::make_unique<Array>(nullptr);
    a->add(Object(1));
    a->add(Object(objName, "FitBV"));
    a->add(Object(objNull)); // left
    return MakeDestFromArray(std::move(a));
  }

  static std::string CapturePrint(const std::unique_ptr<LinkDest> &dest) {
    testing::internal::CaptureStdout();
    printLinkDest(dest);
    return testing::internal::GetCapturedStdout();
  }

  static std::string PaddedToBracketAt26(const std::string &prefix) {
    // printLinkDest() forces ']' at index 26 and '\0' at index 27, so printf("%s")
    // prints exactly 27 bytes (0..26).  Everything between prefix and index 26
    // is expected to be spaces for cases where prefix does not reach index 26.
    std::string out = prefix;
    if (out.size() < 26) {
      out.append(26 - out.size(), ' ');
    } else if (out.size() > 26) {
      // If prefix is already longer than 26, truncation will happen in the
      // implementation; tests that rely on exact content should avoid this.
      out.resize(26);
    }
    out.push_back(']');
    return out;
  }

  static void ExpectFixedWidth27AndBracket(const std::string &out) {
    ASSERT_EQ(out.size(), 27u);
    EXPECT_EQ(out.back(), ']');
  }
};

TEST_F(PrintLinkDestTest_2670, XYZ_AllNull_PrintsNullFieldsAndFixedWidth_2670) {
  auto dest = MakeXYZ_AllNull();
  ASSERT_TRUE(dest);
  // If LinkDest exposes isOk(), ensure construction succeeded for this normal case.
  EXPECT_TRUE(dest->isOk());

  const std::string out = CapturePrint(dest);
  ExpectFixedWidth27AndBracket(out);

  // For all-null XYZ: "[ XYZ null null null " + " " then padding then ']'
  const std::string expectedPrefix = std::string("[ XYZ ") + "null " + "null " + "null " + " ";
  EXPECT_EQ(out, PaddedToBracketAt26(expectedPrefix));
}

TEST_F(PrintLinkDestTest_2670, Fit_PrintsFitAndFixedWidth_2670) {
  auto dest = MakeFit();
  ASSERT_TRUE(dest);
  EXPECT_TRUE(dest->isOk());

  const std::string out = CapturePrint(dest);
  ExpectFixedWidth27AndBracket(out);

  // "[ Fit " then trailing space after switch => two spaces after "Fit"
  const std::string expectedPrefix = std::string("[ Fit ") + " ";
  EXPECT_EQ(out, PaddedToBracketAt26(expectedPrefix));
}

TEST_F(PrintLinkDestTest_2670, FitH_NullTop_PrintsNullAndFixedWidth_2670) {
  auto dest = MakeFitH_Null();
  ASSERT_TRUE(dest);
  EXPECT_TRUE(dest->isOk());

  const std::string out = CapturePrint(dest);
  ExpectFixedWidth27AndBracket(out);

  const std::string expectedPrefix = std::string("[ FitH null ") + " ";
  EXPECT_EQ(out, PaddedToBracketAt26(expectedPrefix));
}

TEST_F(PrintLinkDestTest_2670, FitV_NullLeft_PrintsNullAndFixedWidth_2670) {
  auto dest = MakeFitV_Null();
  ASSERT_TRUE(dest);
  EXPECT_TRUE(dest->isOk());

  const std::string out = CapturePrint(dest);
  ExpectFixedWidth27AndBracket(out);

  const std::string expectedPrefix = std::string("[ FitV null ") + " ";
  EXPECT_EQ(out, PaddedToBracketAt26(expectedPrefix));
}

TEST_F(PrintLinkDestTest_2670, FitR_PrintsFitRPrefixAndFixedWidth_2670) {
  auto dest = MakeFitR(1.0, 2.0, 3.0, 4.0);
  ASSERT_TRUE(dest);
  EXPECT_TRUE(dest->isOk());

  const std::string out = CapturePrint(dest);
  ExpectFixedWidth27AndBracket(out);

  // Formatting of numbers is implementation-defined via GooString::appendf, so
  // assert the stable parts only.
  EXPECT_TRUE(out.rfind("[ FitR ", 0) == 0);
}

TEST_F(PrintLinkDestTest_2670, FitB_PrintsFitBAndFixedWidth_2670) {
  auto dest = MakeFitB();
  ASSERT_TRUE(dest);
  EXPECT_TRUE(dest->isOk());

  const std::string out = CapturePrint(dest);
  ExpectFixedWidth27AndBracket(out);

  const std::string expectedPrefix = std::string("[ FitB ") + " ";
  EXPECT_EQ(out, PaddedToBracketAt26(expectedPrefix));
}

TEST_F(PrintLinkDestTest_2670, FitBH_NullTop_PrintsNullAndFixedWidth_2670) {
  auto dest = MakeFitBH_Null();
  ASSERT_TRUE(dest);
  EXPECT_TRUE(dest->isOk());

  const std::string out = CapturePrint(dest);
  ExpectFixedWidth27AndBracket(out);

  const std::string expectedPrefix = std::string("[ FitBH null ") + " ";
  EXPECT_EQ(out, PaddedToBracketAt26(expectedPrefix));
}

TEST_F(PrintLinkDestTest_2670, FitBV_NullLeft_PrintsNullAndFixedWidth_2670) {
  auto dest = MakeFitBV_Null();
  ASSERT_TRUE(dest);
  EXPECT_TRUE(dest->isOk());

  const std::string out = CapturePrint(dest);
  ExpectFixedWidth27AndBracket(out);

  const std::string expectedPrefix = std::string("[ FitBV null ") + " ";
  EXPECT_EQ(out, PaddedToBracketAt26(expectedPrefix));
}

TEST_F(PrintLinkDestTest_2670, XYZ_LeftOnly_PrintsXYZPrefixAndFixedWidth_2670) {
  auto dest = MakeXYZ_LeftOnly(0.0);
  ASSERT_TRUE(dest);
  EXPECT_TRUE(dest->isOk());

  const std::string out = CapturePrint(dest);
  ExpectFixedWidth27AndBracket(out);

  // Avoid depending on numeric formatting/truncation; just verify key markers.
  EXPECT_TRUE(out.rfind("[ XYZ ", 0) == 0);
  // With left provided, output should not be the all-null XYZ exact string.
  const std::string allNullPrefix = std::string("[ XYZ ") + "null " + "null " + "null " + " ";
  EXPECT_NE(out, PaddedToBracketAt26(allNullPrefix));
}

} // namespace