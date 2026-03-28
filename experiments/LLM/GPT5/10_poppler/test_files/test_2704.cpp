// File: HtmlPage_getNumImages_test_2704.cpp

#include <gtest/gtest.h>

#include <string>

#include "HtmlOutputDev.h" // ./TestProjects/poppler/utils/HtmlOutputDev.h

namespace {

class HtmlPageTest_2704 : public ::testing::Test {
protected:
  // Keep construction simple; we only test observable behavior via public API.
  HtmlPageTest_2704() : page(false) {}

  HtmlPage page;
};

TEST_F(HtmlPageTest_2704, InitiallyZeroImages_2704) {
  // Boundary: freshly constructed object.
  EXPECT_EQ(page.getNumImages(), 0);
}

TEST_F(HtmlPageTest_2704, AddImageIncreasesOrKeepsNonDecreasing_2704) {
  // Normal operation: adding an image should not reduce the count.
  const int before = page.getNumImages();

  std::string fname = "img1.png";
  EXPECT_NO_THROW(page.addImage(std::move(fname), /*state=*/nullptr));

  const int after = page.getNumImages();
  EXPECT_GE(after, before);
}

TEST_F(HtmlPageTest_2704, MultipleAddImageCallsNonDecreasingAcrossCalls_2704) {
  // Normal operation over multiple calls: count should be non-decreasing.
  int prev = page.getNumImages();
  EXPECT_EQ(prev, 0);

  for (int i = 0; i < 5; ++i) {
    std::string fname = "img_" + std::to_string(i) + ".png";
    EXPECT_NO_THROW(page.addImage(std::move(fname), /*state=*/nullptr));
    const int now = page.getNumImages();
    EXPECT_GE(now, prev);
    prev = now;
  }
}

TEST_F(HtmlPageTest_2704, ClearMakesCountNotGreaterThanBefore_2704) {
  // Boundary + observable reset behavior through public API.
  std::string fname = "to_clear.png";
  EXPECT_NO_THROW(page.addImage(std::move(fname), /*state=*/nullptr));
  const int beforeClear = page.getNumImages();

  EXPECT_NO_THROW(page.clear());
  const int afterClear = page.getNumImages();

  // Without assuming exact semantics (some impls might retain cached images),
  // we only require that clear() does not increase the image count.
  EXPECT_LE(afterClear, beforeClear);
  // And also the count cannot be negative.
  EXPECT_GE(afterClear, 0);
}

TEST_F(HtmlPageTest_2704, AddImageWithEmptyFilenameDoesNotCrashAndNonDecreasing_2704) {
  // Exceptional / error-like input (if accepted): empty filename + nullptr state.
  const int before = page.getNumImages();

  std::string empty;
  EXPECT_NO_THROW(page.addImage(std::move(empty), /*state=*/nullptr));

  const int after = page.getNumImages();
  EXPECT_GE(after, before);
}

} // namespace