// File: poppler-font-info-init-test_2233.cc
#include <gtest/gtest.h>

// NOTE:
// The function under test is declared `static` inside poppler-document.cc,
// so we include the implementation file to bring it into this translation unit.
// This is a common technique for unit-testing internal-linkage helpers.
#include "poppler-document.cc"

namespace {

class PopplerFontInfoInitTest_2233 : public ::testing::Test {
protected:
  PopplerFontInfoInitTest_2233() = default;
  ~PopplerFontInfoInitTest_2233() override = default;
};

TEST_F(PopplerFontInfoInitTest_2233, SetsDocumentAndScannerToNull_2233) {
  PopplerFontInfo font_info;

  // Seed with non-null values so the effect of init is observable.
  font_info.document = reinterpret_cast<PopplerDocument*>(0x1);
  font_info.scanner = reinterpret_cast<FontInfoScanner*>(0x2);

  poppler_font_info_init(&font_info);

  EXPECT_EQ(font_info.document, nullptr);
  EXPECT_EQ(font_info.scanner, nullptr);
}

TEST_F(PopplerFontInfoInitTest_2233, IdempotentWhenCalledMultipleTimes_2233) {
  PopplerFontInfo font_info;

  font_info.document = reinterpret_cast<PopplerDocument*>(0x1234);
  font_info.scanner = reinterpret_cast<FontInfoScanner*>(0x5678);

  poppler_font_info_init(&font_info);
  ASSERT_EQ(font_info.document, nullptr);
  ASSERT_EQ(font_info.scanner, nullptr);

  // Call again to ensure it remains in the initialized state.
  font_info.document = reinterpret_cast<PopplerDocument*>(0x9);  // try to "dirty" it
  font_info.scanner = reinterpret_cast<FontInfoScanner*>(0xA);
  poppler_font_info_init(&font_info);

  EXPECT_EQ(font_info.document, nullptr);
  EXPECT_EQ(font_info.scanner, nullptr);
}

TEST_F(PopplerFontInfoInitTest_2233, WorksWithAlreadyNullMembers_2233) {
  PopplerFontInfo font_info;
  font_info.document = nullptr;
  font_info.scanner = nullptr;

  // Boundary-ish: already initialized/zeroed input should remain valid.
  poppler_font_info_init(&font_info);

  EXPECT_EQ(font_info.document, nullptr);
  EXPECT_EQ(font_info.scanner, nullptr);
}

}  // namespace