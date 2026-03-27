// File: Page_getNum_test_702.cpp
#include <gtest/gtest.h>

#include <climits>
#include <memory>
#include <utility>

#include "poppler/Page.h"

namespace {

class PageTest_702 : public ::testing::Test {};

// Normal operation: getNum() returns the number passed to the constructor.
TEST_F(PageTest_702, GetNumReturnsConstructorValue_702) {
  const int kNum = 7;

  ASSERT_NO_THROW({
    Page page(nullptr, kNum, Object(), Ref(), /*attrsA=*/0);
    EXPECT_EQ(page.getNum(), kNum);
  });
}

// Boundary: zero page number.
TEST_F(PageTest_702, GetNumSupportsZero_702) {
  const int kNum = 0;

  ASSERT_NO_THROW({
    Page page(nullptr, kNum, Object(), Ref(), /*attrsA=*/0);
    EXPECT_EQ(page.getNum(), kNum);
  });
}

// Boundary: negative page number (should still be observable via the getter).
TEST_F(PageTest_702, GetNumSupportsNegative_702) {
  const int kNum = -1;

  ASSERT_NO_THROW({
    Page page(nullptr, kNum, Object(), Ref(), /*attrsA=*/0);
    EXPECT_EQ(page.getNum(), kNum);
  });
}

// Boundary: very large page number.
TEST_F(PageTest_702, GetNumSupportsIntMax_702) {
  const int kNum = INT_MAX;

  ASSERT_NO_THROW({
    Page page(nullptr, kNum, Object(), Ref(), /*attrsA=*/0);
    EXPECT_EQ(page.getNum(), kNum);
  });
}

// Const-correctness: getNum() works on a const Page.
TEST_F(PageTest_702, GetNumWorksOnConstPage_702) {
  const int kNum = 123;

  ASSERT_NO_THROW({
    const Page page(nullptr, kNum, Object(), Ref(), /*attrsA=*/0);
    EXPECT_EQ(page.getNum(), kNum);
  });
}

}  // namespace