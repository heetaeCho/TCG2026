#include <gtest/gtest.h>
#include "Annot.h"

// Test fixture for AnnotBorderArray
class AnnotBorderArrayTest_753 : public ::testing::Test {
protected:
    void SetUp() override {
        borderArray = new AnnotBorderArray();
    }

    void TearDown() override {
        delete borderArray;
    }

    AnnotBorderArray* borderArray;
};

// Test default construction - vertical corner should have a default value
TEST_F(AnnotBorderArrayTest_753, DefaultConstructor_VerticalCornerDefault_753) {
    AnnotBorderArray ba;
    double vc = ba.getVerticalCorner();
    // Default constructed should have some deterministic value (likely 0)
    EXPECT_DOUBLE_EQ(vc, 0.0);
}

// Test default construction - horizontal corner should have a default value
TEST_F(AnnotBorderArrayTest_753, DefaultConstructor_HorizontalCornerDefault_753) {
    AnnotBorderArray ba;
    double hc = ba.getHorizontalCorner();
    EXPECT_DOUBLE_EQ(hc, 0.0);
}

// Test setVerticalCorner and getVerticalCorner
TEST_F(AnnotBorderArrayTest_753, SetAndGetVerticalCorner_753) {
    borderArray->setVerticalCorner(5.5);
    EXPECT_DOUBLE_EQ(borderArray->getVerticalCorner(), 5.5);
}

// Test setHorizontalCorner and getHorizontalCorner
TEST_F(AnnotBorderArrayTest_753, SetAndGetHorizontalCorner_753) {
    borderArray->setHorizontalCorner(3.7);
    EXPECT_DOUBLE_EQ(borderArray->getHorizontalCorner(), 3.7);
}

// Test setting vertical corner to zero
TEST_F(AnnotBorderArrayTest_753, SetVerticalCornerToZero_753) {
    borderArray->setVerticalCorner(10.0);
    borderArray->setVerticalCorner(0.0);
    EXPECT_DOUBLE_EQ(borderArray->getVerticalCorner(), 0.0);
}

// Test setting horizontal corner to zero
TEST_F(AnnotBorderArrayTest_753, SetHorizontalCornerToZero_753) {
    borderArray->setHorizontalCorner(10.0);
    borderArray->setHorizontalCorner(0.0);
    EXPECT_DOUBLE_EQ(borderArray->getHorizontalCorner(), 0.0);
}

// Test setting vertical corner to negative value
TEST_F(AnnotBorderArrayTest_753, SetVerticalCornerNegative_753) {
    borderArray->setVerticalCorner(-2.5);
    EXPECT_DOUBLE_EQ(borderArray->getVerticalCorner(), -2.5);
}

// Test setting horizontal corner to negative value
TEST_F(AnnotBorderArrayTest_753, SetHorizontalCornerNegative_753) {
    borderArray->setHorizontalCorner(-1.0);
    EXPECT_DOUBLE_EQ(borderArray->getHorizontalCorner(), -1.0);
}

// Test setting vertical corner to a large value
TEST_F(AnnotBorderArrayTest_753, SetVerticalCornerLargeValue_753) {
    borderArray->setVerticalCorner(1e10);
    EXPECT_DOUBLE_EQ(borderArray->getVerticalCorner(), 1e10);
}

// Test setting horizontal corner to a large value
TEST_F(AnnotBorderArrayTest_753, SetHorizontalCornerLargeValue_753) {
    borderArray->setHorizontalCorner(1e10);
    EXPECT_DOUBLE_EQ(borderArray->getHorizontalCorner(), 1e10);
}

// Test setting vertical corner to a very small positive value
TEST_F(AnnotBorderArrayTest_753, SetVerticalCornerSmallPositive_753) {
    borderArray->setVerticalCorner(1e-15);
    EXPECT_DOUBLE_EQ(borderArray->getVerticalCorner(), 1e-15);
}

// Test setting horizontal corner to a very small positive value
TEST_F(AnnotBorderArrayTest_753, SetHorizontalCornerSmallPositive_753) {
    borderArray->setHorizontalCorner(1e-15);
    EXPECT_DOUBLE_EQ(borderArray->getHorizontalCorner(), 1e-15);
}

// Test multiple sets overwrite previous values for vertical corner
TEST_F(AnnotBorderArrayTest_753, MultipleSetVerticalCorner_753) {
    borderArray->setVerticalCorner(1.0);
    EXPECT_DOUBLE_EQ(borderArray->getVerticalCorner(), 1.0);
    borderArray->setVerticalCorner(2.0);
    EXPECT_DOUBLE_EQ(borderArray->getVerticalCorner(), 2.0);
    borderArray->setVerticalCorner(3.0);
    EXPECT_DOUBLE_EQ(borderArray->getVerticalCorner(), 3.0);
}

// Test multiple sets overwrite previous values for horizontal corner
TEST_F(AnnotBorderArrayTest_753, MultipleSetHorizontalCorner_753) {
    borderArray->setHorizontalCorner(1.0);
    EXPECT_DOUBLE_EQ(borderArray->getHorizontalCorner(), 1.0);
    borderArray->setHorizontalCorner(2.0);
    EXPECT_DOUBLE_EQ(borderArray->getHorizontalCorner(), 2.0);
    borderArray->setHorizontalCorner(3.0);
    EXPECT_DOUBLE_EQ(borderArray->getHorizontalCorner(), 3.0);
}

// Test that setting horizontal corner does not affect vertical corner
TEST_F(AnnotBorderArrayTest_753, SetHorizontalDoesNotAffectVertical_753) {
    borderArray->setVerticalCorner(5.0);
    borderArray->setHorizontalCorner(10.0);
    EXPECT_DOUBLE_EQ(borderArray->getVerticalCorner(), 5.0);
    EXPECT_DOUBLE_EQ(borderArray->getHorizontalCorner(), 10.0);
}

// Test that setting vertical corner does not affect horizontal corner
TEST_F(AnnotBorderArrayTest_753, SetVerticalDoesNotAffectHorizontal_753) {
    borderArray->setHorizontalCorner(7.0);
    borderArray->setVerticalCorner(3.0);
    EXPECT_DOUBLE_EQ(borderArray->getHorizontalCorner(), 7.0);
    EXPECT_DOUBLE_EQ(borderArray->getVerticalCorner(), 3.0);
}

// Test copy method returns a valid copy with the same corner values
TEST_F(AnnotBorderArrayTest_753, CopyPreservesCornerValues_753) {
    borderArray->setHorizontalCorner(4.0);
    borderArray->setVerticalCorner(6.0);
    
    std::unique_ptr<AnnotBorder> copied = borderArray->copy();
    ASSERT_NE(copied, nullptr);
    
    // Dynamic cast to AnnotBorderArray to check values
    AnnotBorderArray* copiedArray = dynamic_cast<AnnotBorderArray*>(copied.get());
    ASSERT_NE(copiedArray, nullptr);
    EXPECT_DOUBLE_EQ(copiedArray->getHorizontalCorner(), 4.0);
    EXPECT_DOUBLE_EQ(copiedArray->getVerticalCorner(), 6.0);
}

// Test that const getters work on const objects
TEST_F(AnnotBorderArrayTest_753, ConstGetters_753) {
    borderArray->setVerticalCorner(9.9);
    borderArray->setHorizontalCorner(8.8);
    
    const AnnotBorderArray& constRef = *borderArray;
    EXPECT_DOUBLE_EQ(constRef.getVerticalCorner(), 9.9);
    EXPECT_DOUBLE_EQ(constRef.getHorizontalCorner(), 8.8);
}
