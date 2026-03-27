#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PSOutputDev.h"

using namespace testing;

class PSOutputDevTest_1317 : public ::testing::Test {
protected:
    PSOutputDevTest_1317() {}
    ~PSOutputDevTest_1317() {}

    // Setup and teardown code if needed
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PSOutputDevTest_1317, GetEmbedTrueType_ReturnsCorrectValue_1317) {
    PSOutputDev psOutputDev("example.ps", nullptr, nullptr, 0, PSOutMode::kPrint, 8.5, 11.0, false, false, 0, 0, 0, 0, PSForceRasterize::kNone, false, nullptr, nullptr, PSLevel::kLevel1);
    
    // Set the embedTrueType flag directly
    psOutputDev.setEmbedTrueType(true);

    // Check the getter function
    EXPECT_TRUE(psOutputDev.getEmbedTrueType());
}

TEST_F(PSOutputDevTest_1317, SetEmbedTrueType_ValidInput_1317) {
    PSOutputDev psOutputDev("example.ps", nullptr, nullptr, 0, PSOutMode::kPrint, 8.5, 11.0, false, false, 0, 0, 0, 0, PSForceRasterize::kNone, false, nullptr, nullptr, PSLevel::kLevel1);
    
    // Set the embedTrueType flag via setter
    psOutputDev.setEmbedTrueType(true);

    // Verify via getter
    EXPECT_TRUE(psOutputDev.getEmbedTrueType());
}

TEST_F(PSOutputDevTest_1317, SetEmbedTrueType_InvalidInput_1317) {
    PSOutputDev psOutputDev("example.ps", nullptr, nullptr, 0, PSOutMode::kPrint, 8.5, 11.0, false, false, 0, 0, 0, 0, PSForceRasterize::kNone, false, nullptr, nullptr, PSLevel::kLevel1);
    
    // Set invalid value for embedTrueType (false)
    psOutputDev.setEmbedTrueType(false);

    // Verify via getter
    EXPECT_FALSE(psOutputDev.getEmbedTrueType());
}

TEST_F(PSOutputDevTest_1317, GetEmbedType1_ReturnsCorrectValue_1317) {
    PSOutputDev psOutputDev("example.ps", nullptr, nullptr, 0, PSOutMode::kPrint, 8.5, 11.0, false, false, 0, 0, 0, 0, PSForceRasterize::kNone, false, nullptr, nullptr, PSLevel::kLevel1);

    // Set the embedType1 flag directly
    psOutputDev.setEmbedType1(true);

    // Check the getter function
    EXPECT_TRUE(psOutputDev.getEmbedType1());
}

TEST_F(PSOutputDevTest_1317, SetEmbedCIDPostScript_ValidInput_1317) {
    PSOutputDev psOutputDev("example.ps", nullptr, nullptr, 0, PSOutMode::kPrint, 8.5, 11.0, false, false, 0, 0, 0, 0, PSForceRasterize::kNone, false, nullptr, nullptr, PSLevel::kLevel1);
    
    // Set the embedCIDPostScript flag via setter
    psOutputDev.setEmbedCIDPostScript(true);

    // Verify via getter
    EXPECT_TRUE(psOutputDev.getEmbedCIDPostScript());
}

TEST_F(PSOutputDevTest_1317, GetEnableLZW_ReturnsCorrectValue_1317) {
    PSOutputDev psOutputDev("example.ps", nullptr, nullptr, 0, PSOutMode::kPrint, 8.5, 11.0, false, false, 0, 0, 0, 0, PSForceRasterize::kNone, false, nullptr, nullptr, PSLevel::kLevel1);

    // Set the enableLZW flag directly
    psOutputDev.setEnableLZW(true);

    // Check the getter function
    EXPECT_TRUE(psOutputDev.getEnableLZW());
}

TEST_F(PSOutputDevTest_1317, SetEnableFlate_InvalidInput_1317) {
    PSOutputDev psOutputDev("example.ps", nullptr, nullptr, 0, PSOutMode::kPrint, 8.5, 11.0, false, false, 0, 0, 0, 0, PSForceRasterize::kNone, false, nullptr, nullptr, PSLevel::kLevel1);

    // Set invalid value for enableFlate (false)
    psOutputDev.setEnableFlate(false);

    // Verify via getter
    EXPECT_FALSE(psOutputDev.getEnableFlate());
}

// Boundary Test for Setting and Getting Embedding of Fonts
TEST_F(PSOutputDevTest_1317, SetEmbedFontsAndVerify_1317) {
    PSOutputDev psOutputDev("example.ps", nullptr, nullptr, 0, PSOutMode::kPrint, 8.5, 11.0, false, false, 0, 0, 0, 0, PSForceRasterize::kNone, false, nullptr, nullptr, PSLevel::kLevel1);

    // Test the boundary where we set the flags one by one
    psOutputDev.setEmbedTrueType(true);
    psOutputDev.setEmbedType1(false);
    psOutputDev.setEmbedCIDPostScript(true);

    EXPECT_TRUE(psOutputDev.getEmbedTrueType());
    EXPECT_FALSE(psOutputDev.getEmbedType1());
    EXPECT_TRUE(psOutputDev.getEmbedCIDPostScript());
}

// Exceptional Case for Setter (Invalid Data)
TEST_F(PSOutputDevTest_1317, SetInvalidEmbedTrueTypeValue_1317) {
    PSOutputDev psOutputDev("example.ps", nullptr, nullptr, 0, PSOutMode::kPrint, 8.5, 11.0, false, false, 0, 0, 0, 0, PSForceRasterize::kNone, false, nullptr, nullptr, PSLevel::kLevel1);

    // Setting with an invalid boolean value (invalid setter operation)
    // This would be caught as an exception if the setter checks invalid values
    EXPECT_NO_THROW(psOutputDev.setEmbedTrueType(false));
    EXPECT_TRUE(psOutputDev.getEmbedTrueType() == false); // Expect the value to be false after invalid set
}