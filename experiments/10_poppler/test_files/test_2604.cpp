#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "SplashFTFontEngine.h"



class SplashFTFontEngineTest : public ::testing::Test {

protected:

    std::unique_ptr<SplashFTFontEngine> fontEngine;



    void SetUp() override {

        fontEngine = std::unique_ptr<SplashFTFontEngine>(SplashFTFontEngine::init(true, true, true));

    }

};



TEST_F(SplashFTFontEngineTest_2604, GetAA_ReturnsTrue_2604) {

    EXPECT_TRUE(fontEngine->getAA());

}



TEST_F(SplashFTFontEngineTest_2604, SetAAToFalse_GetAAReturnsFalse_2604) {

    fontEngine->setAA(false);

    EXPECT_FALSE(fontEngine->getAA());

}



TEST_F(SplashFTFontEngineTest_2604, SetAAToTrue_GetAAReturnsTrue_2604) {

    fontEngine->setAA(true);

    EXPECT_TRUE(fontEngine->getAA());

}



// Boundary conditions for boolean values are already covered by the above tests.

// Since there are no parameters or external dependencies that can be mocked directly,

// we do not have additional boundary condition or exceptional/error cases to test.



TEST_F(SplashFTFontEngineTest_2604, LoadType1Font_ReturnsValidPointer_2604) {

    const char* enc = nullptr;

    auto fontFile = fontEngine->loadType1Font(1, 1, &enc, 0);

    EXPECT_NE(fontFile, nullptr);

}



TEST_F(SplashFTFontEngineTest_2604, LoadType1CFont_ReturnsValidPointer_2604) {

    const char* enc = nullptr;

    auto fontFile = fontEngine->loadType1CFont(1, 1, &enc, 0);

    EXPECT_NE(fontFile, nullptr);

}



TEST_F(SplashFTFontEngineTest_2604, LoadOpenTypeT1CFont_ReturnsValidPointer_2604) {

    const char* enc = nullptr;

    auto fontFile = fontEngine->loadOpenTypeT1CFont(1, 1, &enc, 0);

    EXPECT_NE(fontFile, nullptr);

}



TEST_F(SplashFTFontEngineTest_2604, LoadCIDFont_ReturnsValidPointer_2604) {

    auto fontFile = fontEngine->loadCIDFont(1, 1, 0);

    EXPECT_NE(fontFile, nullptr);

}



TEST_F(SplashFTFontEngineTest_2604, LoadOpenTypeCFFFont_ReturnsValidPointer_2604) {

    int codeToGID = 0;

    auto fontFile = fontEngine->loadOpenTypeCFFFont(1, 1, std::move(codeToGID), 0);

    EXPECT_NE(fontFile, nullptr);

}



TEST_F(SplashFTFontEngineTest_2604, LoadTrueTypeFont_ReturnsValidPointer_2604) {

    int codeToGID = 0;

    auto fontFile = fontEngine->loadTrueTypeFont(1, 1, std::move(codeToGID), 0);

    EXPECT_NE(fontFile, nullptr);

}
