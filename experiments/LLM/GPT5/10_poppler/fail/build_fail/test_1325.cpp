#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PSOutputDev.h"

class PSOutputDevTest : public ::testing::Test {
protected:
    PSOutputDev* psOutputDev;

    void SetUp() override {
        // Initialize the PSOutputDev object with necessary parameters
        psOutputDev = new PSOutputDev("testfile.ps", nullptr, "Test Title", 1, PSOutMode::psLevel1, 600, 800, false, false, 0, 0, 100, 100, PSForceRasterize::none, false, nullptr, nullptr, PSLevel::psLevel1);
    }

    void TearDown() override {
        delete psOutputDev;
    }
};

// Test the setEmbedType1 function
TEST_F(PSOutputDevTest, SetEmbedType1_True) {
    // Set the embedType1 to true
    psOutputDev->setEmbedType1(true);

    // Check if the state is correctly updated
    ASSERT_TRUE(psOutputDev->getEmbedType1());
}

TEST_F(PSOutputDevTest, SetEmbedType1_False) {
    // Set the embedType1 to false
    psOutputDev->setEmbedType1(false);

    // Check if the state is correctly updated
    ASSERT_FALSE(psOutputDev->getEmbedType1());
}

// Test the boundary condition of setting embedType1 with true
TEST_F(PSOutputDevTest, SetEmbedType1_Boundary) {
    // Test boundary scenario, setting embedType1 to true
    psOutputDev->setEmbedType1(true);
    ASSERT_TRUE(psOutputDev->getEmbedType1());
}

// Test exceptional case for checking invalid behavior of setEmbedType1 (if applicable)
TEST_F(PSOutputDevTest, SetEmbedType1_ExceptionalCase) {
    // Assuming there are no exceptions thrown directly by setEmbedType1, 
    // but we can simulate a callback exception if it's possible in real-world conditions
    try {
        psOutputDev->setEmbedType1(true);
        ASSERT_TRUE(psOutputDev->getEmbedType1());
    } catch (const std::exception& e) {
        FAIL() << "Exception thrown during setting embedType1: " << e.what();
    }
}

// Test for the PSOutputDev constructor
TEST_F(PSOutputDevTest, Constructor_ValidParameters) {
    ASSERT_NO_THROW({
        PSOutputDev psTest("test.ps", nullptr, "Test", 1, PSOutMode::psLevel1, 600, 800, false, false, 0, 0, 100, 100, PSForceRasterize::none, false, nullptr, nullptr, PSLevel::psLevel1);
    });
}

// Test the exceptional case for invalid file path (if applicable)
TEST_F(PSOutputDevTest, Constructor_InvalidFilePath) {
    ASSERT_THROW({
        PSOutputDev psTest(nullptr, nullptr, "InvalidTest", 1, PSOutMode::psLevel1, 600, 800, false, false, 0, 0, 100, 100, PSForceRasterize::none, false, nullptr, nullptr, PSLevel::psLevel1);
    }, std::invalid_argument);
}

// Test external interactions with callbacks (if they can be mocked)
TEST_F(PSOutputDevTest, SetUnderlayCallback_Interaction) {
    // Define mock callbacks using Google Mock (if necessary)
    auto mockCallback = [](PSOutputDev* psOut, void* data) {
        // Mock callback behavior here
    };

    // Setting the underlay callback
    psOutputDev->setUnderlayCbk(mockCallback, nullptr);

    // Verification of external callback interaction (if the callback is actually called)
    // You may use Google Mock's EXPECT_CALL here to check if callback is triggered.
}

// Test for boundary on raster resolution
TEST_F(PSOutputDevTest, SetRasterResolution_Boundary) {
    psOutputDev->setRasterResolution(0.0);
    ASSERT_EQ(psOutputDev->getRasterResolution(), 0.0);

    psOutputDev->setRasterResolution(10000.0);  // boundary value test
    ASSERT_EQ(psOutputDev->getRasterResolution(), 10000.0);
}