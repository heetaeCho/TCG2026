// poppler-annot-set-border-width-test.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cmath>
#include <limits>
#include <memory>

// Poppler GLib private struct (PopplerAnnot -> _PopplerAnnot { std::shared_ptr<Annot> annot; })
#include "poppler-private.h"

// Poppler core annotation border types.
#include "Annot.h"
#include "AnnotBorder.h"

using ::testing::_;
using ::testing::Invoke;

namespace {

class MockAnnot : public Annot {
public:
  // In Poppler, Annot::setBorder takes a std::unique_ptr<AnnotBorder>.
  MOCK_METHOD(void, setBorder, (std::unique_ptr<AnnotBorder> border), (override));
};

class PopplerAnnotSetBorderWidthTest_2123 : public ::testing::Test {
protected:
  PopplerAnnotSetBorderWidthTest_2123() : mock_annot_(std::make_shared<MockAnnot>()) {
    poppler_annot_.annot = mock_annot_;
  }

  _PopplerAnnot poppler_annot_{};
  std::shared_ptr<MockAnnot> mock_annot_;
};

TEST_F(PopplerAnnotSetBorderWidthTest_2123, SetsBorderWidth_2123) {
  const double kWidth = 3.5;

  EXPECT_CALL(*mock_annot_, setBorder(_))
      .WillOnce(Invoke([&](std::unique_ptr<AnnotBorder> border) {
        ASSERT_NE(border, nullptr);

        auto* array_border = dynamic_cast<AnnotBorderArray*>(border.get());
        ASSERT_NE(array_border, nullptr) << "Expected an AnnotBorderArray to be passed";

        // Verify the width stored in the border object matches the input.
        EXPECT_DOUBLE_EQ(array_border->getWidth(), kWidth);
      }));

  poppler_annot_set_border_width(reinterpret_cast<PopplerAnnot*>(&poppler_annot_), kWidth);
}

TEST_F(PopplerAnnotSetBorderWidthTest_2123, SetsZeroWidth_2123) {
  const double kWidth = 0.0;

  EXPECT_CALL(*mock_annot_, setBorder(_))
      .WillOnce(Invoke([&](std::unique_ptr<AnnotBorder> border) {
        ASSERT_NE(border, nullptr);
        auto* array_border = dynamic_cast<AnnotBorderArray*>(border.get());
        ASSERT_NE(array_border, nullptr);
        EXPECT_DOUBLE_EQ(array_border->getWidth(), kWidth);
      }));

  poppler_annot_set_border_width(reinterpret_cast<PopplerAnnot*>(&poppler_annot_), kWidth);
}

TEST_F(PopplerAnnotSetBorderWidthTest_2123, SetsNegativeWidth_2123) {
  const double kWidth = -2.0;

  EXPECT_CALL(*mock_annot_, setBorder(_))
      .WillOnce(Invoke([&](std::unique_ptr<AnnotBorder> border) {
        ASSERT_NE(border, nullptr);
        auto* array_border = dynamic_cast<AnnotBorderArray*>(border.get());
        ASSERT_NE(array_border, nullptr);
        EXPECT_DOUBLE_EQ(array_border->getWidth(), kWidth);
      }));

  poppler_annot_set_border_width(reinterpret_cast<PopplerAnnot*>(&poppler_annot_), kWidth);
}

TEST_F(PopplerAnnotSetBorderWidthTest_2123, SetsVeryLargeWidth_2123) {
  const double kWidth = 1e12;

  EXPECT_CALL(*mock_annot_, setBorder(_))
      .WillOnce(Invoke([&](std::unique_ptr<AnnotBorder> border) {
        ASSERT_NE(border, nullptr);
        auto* array_border = dynamic_cast<AnnotBorderArray*>(border.get());
        ASSERT_NE(array_border, nullptr);
        EXPECT_DOUBLE_EQ(array_border->getWidth(), kWidth);
      }));

  poppler_annot_set_border_width(reinterpret_cast<PopplerAnnot*>(&poppler_annot_), kWidth);
}

TEST_F(PopplerAnnotSetBorderWidthTest_2123, PassesNaNWidthThrough_2123) {
  const double kWidth = std::numeric_limits<double>::quiet_NaN();

  EXPECT_CALL(*mock_annot_, setBorder(_))
      .WillOnce(Invoke([&](std::unique_ptr<AnnotBorder> border) {
        ASSERT_NE(border, nullptr);
        auto* array_border = dynamic_cast<AnnotBorderArray*>(border.get());
        ASSERT_NE(array_border, nullptr);
        EXPECT_TRUE(std::isnan(array_border->getWidth()));
      }));

  poppler_annot_set_border_width(reinterpret_cast<PopplerAnnot*>(&poppler_annot_), kWidth);
}

TEST_F(PopplerAnnotSetBorderWidthTest_2123, PassesInfinityWidthThrough_2123) {
  const double kWidth = std::numeric_limits<double>::infinity();

  EXPECT_CALL(*mock_annot_, setBorder(_))
      .WillOnce(Invoke([&](std::unique_ptr<AnnotBorder> border) {
        ASSERT_NE(border, nullptr);
        auto* array_border = dynamic_cast<AnnotBorderArray*>(border.get());
        ASSERT_NE(array_border, nullptr);
        EXPECT_TRUE(std::isinf(array_border->getWidth()));
        EXPECT_GT(array_border->getWidth(), 0.0);
      }));

  poppler_annot_set_border_width(reinterpret_cast<PopplerAnnot*>(&poppler_annot_), kWidth);
}

TEST_F(PopplerAnnotSetBorderWidthTest_2123, ReplacesBorderOnMultipleCalls_2123) {
  const double kWidth1 = 1.0;
  const double kWidth2 = 2.0;

  EXPECT_CALL(*mock_annot_, setBorder(_))
      .WillOnce(Invoke([&](std::unique_ptr<AnnotBorder> border) {
        ASSERT_NE(border, nullptr);
        auto* array_border = dynamic_cast<AnnotBorderArray*>(border.get());
        ASSERT_NE(array_border, nullptr);
        EXPECT_DOUBLE_EQ(array_border->getWidth(), kWidth1);
      }))
      .WillOnce(Invoke([&](std::unique_ptr<AnnotBorder> border) {
        ASSERT_NE(border, nullptr);
        auto* array_border = dynamic_cast<AnnotBorderArray*>(border.get());
        ASSERT_NE(array_border, nullptr);
        EXPECT_DOUBLE_EQ(array_border->getWidth(), kWidth2);
      }));

  poppler_annot_set_border_width(reinterpret_cast<PopplerAnnot*>(&poppler_annot_), kWidth1);
  poppler_annot_set_border_width(reinterpret_cast<PopplerAnnot*>(&poppler_annot_), kWidth2);
}

TEST(PopplerAnnotSetBorderWidthDeathTest_2123, NullPopplerAnnotDies_2123) {
#if GTEST_HAS_DEATH_TEST
  EXPECT_DEATH(poppler_annot_set_border_width(nullptr, 1.0), "");
#endif
}

TEST(PopplerAnnotSetBorderWidthDeathTest_2123, NullAnnotSharedPtrDies_2123) {
#if GTEST_HAS_DEATH_TEST
  _PopplerAnnot poppler_annot{};
  poppler_annot.annot.reset();  // nullptr

  EXPECT_DEATH(poppler_annot_set_border_width(reinterpret_cast<PopplerAnnot*>(&poppler_annot), 1.0), "");
#endif
}

}  // namespace