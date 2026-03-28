// File: HtmlLink_getX2_test_2656.cpp
#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/HtmlLinks.h"

// NOTE:
// - We treat HtmlLink as a black box.
// - We only test observable behavior from the public interface.
// - We avoid assumptions about GooString contents and internal state.
// - Since HtmlLink stores a unique_ptr<GooString>, we pass nullptr safely via unique_ptr.

namespace {

class HtmlLinkGetX2Test_2656 : public ::testing::Test {};

TEST_F(HtmlLinkGetX2Test_2656, ReturnsConstructorXmax_2656) {
  // Arrange
  const double xmin = 1.0;
  const double ymin = 2.0;
  const double xmax = 3.5;
  const double ymax = 4.0;

  HtmlLink link(xmin, ymin, xmax, ymax, std::unique_ptr<GooString>());

  // Act
  const double x2 = link.getX2();

  // Assert
  EXPECT_DOUBLE_EQ(x2, xmax);
}

TEST_F(HtmlLinkGetX2Test_2656, ReturnsNegativeXmax_2656) {
  // Arrange
  const double xmin = 0.0;
  const double ymin = 0.0;
  const double xmax = -123.456;
  const double ymax = 1.0;

  HtmlLink link(xmin, ymin, xmax, ymax, std::unique_ptr<GooString>());

  // Act + Assert
  EXPECT_DOUBLE_EQ(link.getX2(), xmax);
}

TEST_F(HtmlLinkGetX2Test_2656, ReturnsZeroXmax_2656) {
  // Arrange
  HtmlLink link(/*xmin=*/-10.0, /*ymin=*/5.0, /*xmax=*/0.0, /*ymax=*/7.0,
                std::unique_ptr<GooString>());

  // Act + Assert
  EXPECT_DOUBLE_EQ(link.getX2(), 0.0);
}

TEST_F(HtmlLinkGetX2Test_2656, ReturnsVeryLargeXmax_2656) {
  // Arrange
  const double xmax = 1e308; // within double finite range
  HtmlLink link(/*xmin=*/0.0, /*ymin=*/0.0, /*xmax=*/xmax, /*ymax=*/0.0,
                std::unique_ptr<GooString>());

  // Act + Assert
  EXPECT_DOUBLE_EQ(link.getX2(), xmax);
}

TEST_F(HtmlLinkGetX2Test_2656, CopyConstructedPreservesXmax_2656) {
  // Arrange
  const double xmax = 9.25;
  HtmlLink original(/*xmin=*/1.0, /*ymin=*/1.0, /*xmax=*/xmax, /*ymax=*/1.0,
                    std::unique_ptr<GooString>());

  // Act
  HtmlLink copy(original);

  // Assert
  EXPECT_DOUBLE_EQ(copy.getX2(), xmax);
  // Also ensure original remains unchanged through observable getter.
  EXPECT_DOUBLE_EQ(original.getX2(), xmax);
}

TEST_F(HtmlLinkGetX2Test_2656, GetX2UnaffectedByInLinkQueries_2656) {
  // Arrange
  const double xmax = 42.0;
  HtmlLink link(/*xmin=*/10.0, /*ymin=*/10.0, /*xmax=*/xmax, /*ymax=*/20.0,
                std::unique_ptr<GooString>());

  // Act
  // We don't assume what inLink returns; we only ensure it doesn't affect getX2().
  (void)link.inLink(/*xmin=*/0.0, /*ymin=*/0.0, /*xmax=*/100.0, /*ymax=*/100.0);
  (void)link.inLink(/*xmin=*/11.0, /*ymin=*/11.0, /*xmax=*/12.0, /*ymax=*/12.0);

  // Assert
  EXPECT_DOUBLE_EQ(link.getX2(), xmax);
}

}  // namespace