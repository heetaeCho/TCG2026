#include <gtest/gtest.h>
#include <memory>
#include "Annot.h"

// Test fixture for AnnotAppearanceCharacs
class AnnotAppearanceCharacsTest_766 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a Dict to construct AnnotAppearanceCharacs
        // Since we don't have easy access to create a Dict, we'll test
        // what we can through the public interface
    }
};

// Test that setBorderColor sets the border color and getBorderColor retrieves it
TEST_F(AnnotAppearanceCharacsTest_766, SetBorderColorWithValidColor_766) {
    // Create an AnnotAppearanceCharacs from a nullptr Dict if possible
    // Since the constructor requires a Dict*, we need to work with what's available
    
    // We'll test the setBorderColor method through the partial implementation provided
    // The method moves the unique_ptr into the member variable
    
    // Since we can only test the interface as shown, let's verify the move semantics
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0); // Red color
    
    // We need an actual AnnotAppearanceCharacs object to test
    // Attempting construction with an empty/null dict
    AnnotAppearanceCharacs characs(nullptr);
    
    characs.setBorderColor(std::move(color));
    
    // After setting, getBorderColor should return non-null
    const AnnotColor *retrieved = characs.getBorderColor();
    ASSERT_NE(retrieved, nullptr);
}

// Test that setBorderColor with nullptr clears the border color
TEST_F(AnnotAppearanceCharacsTest_766, SetBorderColorWithNullptr_766) {
    AnnotAppearanceCharacs characs(nullptr);
    
    // First set a valid color
    auto color = std::make_unique<AnnotColor>(0.0, 1.0, 0.0);
    characs.setBorderColor(std::move(color));
    ASSERT_NE(characs.getBorderColor(), nullptr);
    
    // Now set to nullptr
    characs.setBorderColor(nullptr);
    EXPECT_EQ(characs.getBorderColor(), nullptr);
}

// Test that setBackColor sets the back color and getBackColor retrieves it
TEST_F(AnnotAppearanceCharacsTest_766, SetBackColorWithValidColor_766) {
    AnnotAppearanceCharacs characs(nullptr);
    
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 1.0); // Blue
    characs.setBackColor(std::move(color));
    
    const AnnotColor *retrieved = characs.getBackColor();
    ASSERT_NE(retrieved, nullptr);
}

// Test that setBackColor with nullptr clears the back color
TEST_F(AnnotAppearanceCharacsTest_766, SetBackColorWithNullptr_766) {
    AnnotAppearanceCharacs characs(nullptr);
    
    auto color = std::make_unique<AnnotColor>(1.0, 1.0, 0.0);
    characs.setBackColor(std::move(color));
    ASSERT_NE(characs.getBackColor(), nullptr);
    
    characs.setBackColor(nullptr);
    EXPECT_EQ(characs.getBackColor(), nullptr);
}

// Test that default constructed (from null dict) has expected defaults
TEST_F(AnnotAppearanceCharacsTest_766, DefaultValuesFromNullDict_766) {
    AnnotAppearanceCharacs characs(nullptr);
    
    // Default rotation should be 0
    EXPECT_EQ(characs.getRotation(), 0);
    
    // Default colors should be null
    EXPECT_EQ(characs.getBorderColor(), nullptr);
    EXPECT_EQ(characs.getBackColor(), nullptr);
    
    // Default captions should be null
    EXPECT_EQ(characs.getNormalCaption(), nullptr);
}

// Test that setBorderColor replaces existing color
TEST_F(AnnotAppearanceCharacsTest_766, SetBorderColorReplacesExisting_766) {
    AnnotAppearanceCharacs characs(nullptr);
    
    auto color1 = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    characs.setBorderColor(std::move(color1));
    const AnnotColor *first = characs.getBorderColor();
    ASSERT_NE(first, nullptr);
    
    auto color2 = std::make_unique<AnnotColor>(0.0, 1.0, 0.0);
    characs.setBorderColor(std::move(color2));
    const AnnotColor *second = characs.getBorderColor();
    ASSERT_NE(second, nullptr);
    
    // The pointers should be different (new color replaced old)
    EXPECT_NE(first, second);
}

// Test that setBackColor replaces existing color
TEST_F(AnnotAppearanceCharacsTest_766, SetBackColorReplacesExisting_766) {
    AnnotAppearanceCharacs characs(nullptr);
    
    auto color1 = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    characs.setBackColor(std::move(color1));
    const AnnotColor *first = characs.getBackColor();
    ASSERT_NE(first, nullptr);
    
    auto color2 = std::make_unique<AnnotColor>(0.0, 0.0, 1.0);
    characs.setBackColor(std::move(color2));
    const AnnotColor *second = characs.getBackColor();
    ASSERT_NE(second, nullptr);
    
    EXPECT_NE(first, second);
}

// Test the source unique_ptr is null after move into setBorderColor
TEST_F(AnnotAppearanceCharacsTest_766, SetBorderColorMovesOwnership_766) {
    AnnotAppearanceCharacs characs(nullptr);
    
    auto color = std::make_unique<AnnotColor>(0.5, 0.5, 0.5);
    AnnotColor *rawPtr = color.get();
    
    characs.setBorderColor(std::move(color));
    
    // After move, the source should be null
    EXPECT_EQ(color.get(), nullptr);
    
    // The object should hold the pointer
    EXPECT_EQ(characs.getBorderColor(), rawPtr);
}

// Test the source unique_ptr is null after move into setBackColor
TEST_F(AnnotAppearanceCharacsTest_766, SetBackColorMovesOwnership_766) {
    AnnotAppearanceCharacs characs(nullptr);
    
    auto color = std::make_unique<AnnotColor>(0.5, 0.5, 0.5);
    AnnotColor *rawPtr = color.get();
    
    characs.setBackColor(std::move(color));
    
    EXPECT_EQ(color.get(), nullptr);
    EXPECT_EQ(characs.getBackColor(), rawPtr);
}

// Test multiple set/get cycles for border color
TEST_F(AnnotAppearanceCharacsTest_766, MultipleBorderColorSetGetCycles_766) {
    AnnotAppearanceCharacs characs(nullptr);
    
    for (int i = 0; i < 10; ++i) {
        double val = static_cast<double>(i) / 10.0;
        auto color = std::make_unique<AnnotColor>(val, val, val);
        characs.setBorderColor(std::move(color));
        EXPECT_NE(characs.getBorderColor(), nullptr);
    }
    
    // Clear it
    characs.setBorderColor(nullptr);
    EXPECT_EQ(characs.getBorderColor(), nullptr);
}
