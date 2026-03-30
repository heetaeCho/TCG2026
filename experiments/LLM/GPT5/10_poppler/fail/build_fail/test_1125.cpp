#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <memory>
#include "SplashBitmap.h"  // Assuming SplashBitmap is defined in this header

class MockGfxSeparationColorSpace : public GfxSeparationColorSpace {
    // Mock class to use for testing the interaction with GfxSeparationColorSpace
};

TEST_F(SplashBitmapTest_1125, GetSeparationList_1125) {
    // Setup
    std::vector<std::unique_ptr<GfxSeparationColorSpace>> separationList;
    separationList.push_back(std::make_unique<MockGfxSeparationColorSpace>());
    
    SplashBitmap bitmap(100, 100, 0, SplashColorMode::splashModeRGB, true, true, &separationList);

    // Test
    auto result = bitmap.getSeparationList();

    // Verify
    ASSERT_EQ(result->size(), 1);
    ASSERT_NE(result->at(0), nullptr);
}

TEST_F(SplashBitmapTest_1126, GetSeparationList_Empty_1126) {
    // Setup
    std::vector<std::unique_ptr<GfxSeparationColorSpace>> separationList;
    
    SplashBitmap bitmap(100, 100, 0, SplashColorMode::splashModeRGB, true, true, &separationList);

    // Test
    auto result = bitmap.getSeparationList();

    // Verify
    ASSERT_EQ(result->size(), 0);
}

TEST_F(SplashBitmapTest_1127, GetSeparationList_1127) {
    // Setup
    const int testSeparationList[2] = {1, 2};
    SplashBitmap bitmap(100, 100, 0, SplashColorMode::splashModeRGB, true, true, testSeparationList);

    // Test
    auto result = bitmap.getSeparationList();

    // Verify
    ASSERT_EQ(result->size(), 2);
    // Further assertions depending on actual behavior of `SplashBitmap`
}

TEST_F(SplashBitmapTest_1128, GetSeparationList_Nullptr_1128) {
    // Setup
    const int * testSeparationList = nullptr;
    
    SplashBitmap bitmap(100, 100, 0, SplashColorMode::splashModeRGB, true, true, testSeparationList);

    // Test
    auto result = bitmap.getSeparationList();

    // Verify
    ASSERT_EQ(result, nullptr);  // Expecting nullptr since separation list was nullptr
}