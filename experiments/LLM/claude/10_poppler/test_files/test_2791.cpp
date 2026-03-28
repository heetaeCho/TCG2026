#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <optional>
#include <string>

#include "Annot.h"
#include "GooString.h"
#include "Form.h"
#include "GfxFont.h"
#include "Gfx.h"

class HorizontalTextLayouterTest_2791 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor creates an object with expected initial state
TEST_F(HorizontalTextLayouterTest_2791, DefaultConstructor_InitialState_2791) {
    HorizontalTextLayouter layouter;
    // Default constructed layouter should have zero consumed text
    EXPECT_EQ(layouter.consumedText, 0);
}

// Test default constructor totalWidth returns 0 for empty layouter
TEST_F(HorizontalTextLayouterTest_2791, DefaultConstructor_TotalWidthZero_2791) {
    HorizontalTextLayouter layouter;
    EXPECT_DOUBLE_EQ(layouter.totalWidth(), 0.0);
}

// Test default constructor totalCharCount returns 0 for empty layouter
TEST_F(HorizontalTextLayouterTest_2791, DefaultConstructor_TotalCharCountZero_2791) {
    HorizontalTextLayouter layouter;
    EXPECT_EQ(layouter.totalCharCount(), 0);
}

// Test that copy constructor is deleted (compile-time check expressed as a type trait test)
TEST_F(HorizontalTextLayouterTest_2791, CopyConstructorDeleted_2791) {
    EXPECT_FALSE(std::is_copy_constructible<HorizontalTextLayouter>::value);
}

// Test that copy assignment is deleted
TEST_F(HorizontalTextLayouterTest_2791, CopyAssignmentDeleted_2791) {
    EXPECT_FALSE(std::is_copy_assignable<HorizontalTextLayouter>::value);
}

// Test that move constructor works (default move should be available)
TEST_F(HorizontalTextLayouterTest_2791, MoveConstructorAvailable_2791) {
    EXPECT_TRUE(std::is_move_constructible<HorizontalTextLayouter>::value);
}

// Test that consumedText is publicly accessible and modifiable
TEST_F(HorizontalTextLayouterTest_2791, ConsumedTextIsPublic_2791) {
    HorizontalTextLayouter layouter;
    layouter.consumedText = 42;
    EXPECT_EQ(layouter.consumedText, 42);
}

// Test move construction preserves state
TEST_F(HorizontalTextLayouterTest_2791, MoveConstructorPreservesState_2791) {
    HorizontalTextLayouter layouter;
    layouter.consumedText = 10;
    
    HorizontalTextLayouter moved(std::move(layouter));
    EXPECT_EQ(moved.consumedText, 10);
}

// Test totalWidth and totalCharCount consistency for default object
TEST_F(HorizontalTextLayouterTest_2791, DefaultConstructor_WidthAndCountConsistent_2791) {
    HorizontalTextLayouter layouter;
    double width = layouter.totalWidth();
    int charCount = layouter.totalCharCount();
    
    // Both should be zero for a default-constructed layouter
    EXPECT_DOUBLE_EQ(width, 0.0);
    EXPECT_EQ(charCount, 0);
    EXPECT_EQ(layouter.consumedText, 0);
}
