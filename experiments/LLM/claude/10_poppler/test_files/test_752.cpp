#include <gtest/gtest.h>
#include "Annot.h"

class AnnotBorderArrayTest_752 : public ::testing::Test {
protected:
    void SetUp() override {
        borderArray = new AnnotBorderArray();
    }

    void TearDown() override {
        delete borderArray;
    }

    AnnotBorderArray* borderArray;
};

// Test default construction - horizontal corner should have a default value
TEST_F(AnnotBorderArrayTest_752, DefaultConstructor_HorizontalCorner_752) {
    double hc = borderArray->getHorizontalCorner();
    // Default constructed value, typically 0.0
    EXPECT_DOUBLE_EQ(0.0, hc);
}

// Test default construction - vertical corner should have a default value
TEST_F(AnnotBorderArrayTest_752, DefaultConstructor_VerticalCorner_752) {
    double vc = borderArray->getVerticalCorner();
    EXPECT_DOUBLE_EQ(0.0, vc);
}

// Test setHorizontalCorner and getHorizontalCorner
TEST_F(AnnotBorderArrayTest_752, SetAndGetHorizontalCorner_752) {
    borderArray->setHorizontalCorner(5.5);
    EXPECT_DOUBLE_EQ(5.5, borderArray->getHorizontalCorner());
}

// Test setVerticalCorner and getVerticalCorner
TEST_F(AnnotBorderArrayTest_752, SetAndGetVerticalCorner_752) {
    borderArray->setVerticalCorner(3.7);
    EXPECT_DOUBLE_EQ(3.7, borderArray->getVerticalCorner());
}

// Test setting horizontal corner to zero
TEST_F(AnnotBorderArrayTest_752, SetHorizontalCornerZero_752) {
    borderArray->setHorizontalCorner(10.0);
    borderArray->setHorizontalCorner(0.0);
    EXPECT_DOUBLE_EQ(0.0, borderArray->getHorizontalCorner());
}

// Test setting vertical corner to zero
TEST_F(AnnotBorderArrayTest_752, SetVerticalCornerZero_752) {
    borderArray->setVerticalCorner(10.0);
    borderArray->setVerticalCorner(0.0);
    EXPECT_DOUBLE_EQ(0.0, borderArray->getVerticalCorner());
}

// Test setting horizontal corner to a negative value
TEST_F(AnnotBorderArrayTest_752, SetHorizontalCornerNegative_752) {
    borderArray->setHorizontalCorner(-2.5);
    EXPECT_DOUBLE_EQ(-2.5, borderArray->getHorizontalCorner());
}

// Test setting vertical corner to a negative value
TEST_F(AnnotBorderArrayTest_752, SetVerticalCornerNegative_752) {
    borderArray->setVerticalCorner(-1.3);
    EXPECT_DOUBLE_EQ(-1.3, borderArray->getVerticalCorner());
}

// Test setting horizontal corner to a large value
TEST_F(AnnotBorderArrayTest_752, SetHorizontalCornerLargeValue_752) {
    borderArray->setHorizontalCorner(1e10);
    EXPECT_DOUBLE_EQ(1e10, borderArray->getHorizontalCorner());
}

// Test setting vertical corner to a large value
TEST_F(AnnotBorderArrayTest_752, SetVerticalCornerLargeValue_752) {
    borderArray->setVerticalCorner(1e10);
    EXPECT_DOUBLE_EQ(1e10, borderArray->getVerticalCorner());
}

// Test setting horizontal corner to a very small positive value
TEST_F(AnnotBorderArrayTest_752, SetHorizontalCornerSmallPositive_752) {
    borderArray->setHorizontalCorner(1e-15);
    EXPECT_DOUBLE_EQ(1e-15, borderArray->getHorizontalCorner());
}

// Test setting vertical corner to a very small positive value
TEST_F(AnnotBorderArrayTest_752, SetVerticalCornerSmallPositive_752) {
    borderArray->setVerticalCorner(1e-15);
    EXPECT_DOUBLE_EQ(1e-15, borderArray->getVerticalCorner());
}

// Test multiple sets on horizontal corner - last value should persist
TEST_F(AnnotBorderArrayTest_752, MultipleSetHorizontalCorner_752) {
    borderArray->setHorizontalCorner(1.0);
    borderArray->setHorizontalCorner(2.0);
    borderArray->setHorizontalCorner(3.0);
    EXPECT_DOUBLE_EQ(3.0, borderArray->getHorizontalCorner());
}

// Test multiple sets on vertical corner - last value should persist
TEST_F(AnnotBorderArrayTest_752, MultipleSetVerticalCorner_752) {
    borderArray->setVerticalCorner(1.0);
    borderArray->setVerticalCorner(2.0);
    borderArray->setVerticalCorner(3.0);
    EXPECT_DOUBLE_EQ(3.0, borderArray->getVerticalCorner());
}

// Test that setting horizontal does not affect vertical
TEST_F(AnnotBorderArrayTest_752, SetHorizontalDoesNotAffectVertical_752) {
    borderArray->setVerticalCorner(5.0);
    borderArray->setHorizontalCorner(10.0);
    EXPECT_DOUBLE_EQ(5.0, borderArray->getVerticalCorner());
    EXPECT_DOUBLE_EQ(10.0, borderArray->getHorizontalCorner());
}

// Test that setting vertical does not affect horizontal
TEST_F(AnnotBorderArrayTest_752, SetVerticalDoesNotAffectHorizontal_752) {
    borderArray->setHorizontalCorner(7.0);
    borderArray->setVerticalCorner(12.0);
    EXPECT_DOUBLE_EQ(7.0, borderArray->getHorizontalCorner());
    EXPECT_DOUBLE_EQ(12.0, borderArray->getVerticalCorner());
}

// Test copy produces an independent copy
TEST_F(AnnotBorderArrayTest_752, CopyProducesIndependentObject_752) {
    borderArray->setHorizontalCorner(4.0);
    borderArray->setVerticalCorner(6.0);
    auto copied = borderArray->copy();
    ASSERT_NE(nullptr, copied.get());
    // The copy should be a different object
    EXPECT_NE(static_cast<AnnotBorder*>(borderArray), copied.get());
}
