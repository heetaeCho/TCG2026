// poppler_font_info_scan_test_2236.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <glib.h>
#include <vector>

// Poppler GLib headers (expected to exist in the Poppler GLib build/test environment).
#include "poppler-private.h"

using ::testing::Return;
using ::testing::ByMove;
using ::testing::StrictMock;

// Forward declarations are enough for pointer usage in std::vector<FontInfo*>.
class FontInfo;

// We assume FontInfoScanner is a C++ class type used by PopplerFontInfo as shown in poppler-private.h.
// The production header should provide this declaration; we only need to derive and override scan().
class FontInfoScanner {
public:
  virtual ~FontInfoScanner() = default;
  virtual std::vector<FontInfo *> scan(int n_pages) = 0;
};

class MockFontInfoScanner : public FontInfoScanner {
public:
  MOCK_METHOD(std::vector<FontInfo *>, scan, (int n_pages), (override));
};

// Function under test (provided by the production code).
extern "C" {
gboolean poppler_font_info_scan(PopplerFontInfo *font_info, int n_pages, PopplerFontsIter **iter);
}

class PopplerFontInfoScanTest_2236 : public ::testing::Test {
protected:
  void SetUp() override {
    font_info_ = new _PopplerFontInfo();
    font_info_->scanner = &scanner_;
  }

  void TearDown() override {
    delete font_info_;
    font_info_ = nullptr;
  }

  // Helper to create a non-null dummy FontInfo* without assuming constructibility.
  static FontInfo *MakeDummyFontInfoPtr() {
    // Allocate something with a stable address; do NOT delete (unknown ownership semantics).
    static int dummy_storage = 0;
    return reinterpret_cast<FontInfo *>(&dummy_storage);
  }

  StrictMock<MockFontInfoScanner> scanner_;
  PopplerFontInfo *font_info_ = nullptr;
};

TEST_F(PopplerFontInfoScanTest_2236, ReturnsFalseWhenIterOutParamIsNull_2236) {
  // Should short-circuit via g_return_val_if_fail(iter != nullptr, FALSE).
  EXPECT_FALSE(poppler_font_info_scan(font_info_, /*n_pages=*/1, /*iter=*/nullptr));
}

TEST_F(PopplerFontInfoScanTest_2236, ReturnsFalseAndSetsIterNullWhenScannerReturnsEmpty_2236) {
  PopplerFontsIter *iter = reinterpret_cast<PopplerFontsIter *>(0x1); // sentinel non-null

  EXPECT_CALL(scanner_, scan(5)).WillOnce(Return(ByMove(std::vector<FontInfo *>{})));

  EXPECT_FALSE(poppler_font_info_scan(font_info_, /*n_pages=*/5, &iter));
  EXPECT_EQ(iter, nullptr) << "On empty scan result, iter must be set to nullptr";
}

TEST_F(PopplerFontInfoScanTest_2236, ReturnsTrueAndProvidesIterWhenScannerReturnsNonEmpty_2236) {
  PopplerFontsIter *iter = nullptr;

  std::vector<FontInfo *> items;
  items.push_back(MakeDummyFontInfoPtr());

  EXPECT_CALL(scanner_, scan(3)).WillOnce(Return(ByMove(std::move(items))));

  EXPECT_TRUE(poppler_font_info_scan(font_info_, /*n_pages=*/3, &iter));
  EXPECT_NE(iter, nullptr) << "On non-empty scan result, iter must be non-null";
}

TEST_F(PopplerFontInfoScanTest_2236, PassesZeroPagesToScanner_Boundary_2236) {
  PopplerFontsIter *iter = nullptr;

  std::vector<FontInfo *> items;
  items.push_back(MakeDummyFontInfoPtr());

  EXPECT_CALL(scanner_, scan(0)).WillOnce(Return(ByMove(std::move(items))));

  EXPECT_TRUE(poppler_font_info_scan(font_info_, /*n_pages=*/0, &iter));
  EXPECT_NE(iter, nullptr);
}

TEST_F(PopplerFontInfoScanTest_2236, PassesNegativePagesToScanner_Boundary_2236) {
  PopplerFontsIter *iter = nullptr;

  // We don't assume the function validates n_pages; it should simply pass it through to scan().
  std::vector<FontInfo *> items;
  items.push_back(MakeDummyFontInfoPtr());

  EXPECT_CALL(scanner_, scan(-1)).WillOnce(Return(ByMove(std::move(items))));

  EXPECT_TRUE(poppler_font_info_scan(font_info_, /*n_pages=*/-1, &iter));
  EXPECT_NE(iter, nullptr);
}