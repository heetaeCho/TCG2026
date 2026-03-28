#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "./TestProjects/poppler/poppler/PSOutputDev.h"

// Test fixture for PSOutputDev
class PSOutputDevTest_1316 : public ::testing::Test {
protected:
    PSOutputDevTest_1316() {
        // Setup code if needed
    }

    ~PSOutputDevTest_1316() override {
        // Cleanup code if needed
    }

    PSOutputDev* psOutputDev;  // Pointer to the object being tested
};

// Test for getEmbedType1 function - Normal operation
TEST_F(PSOutputDevTest_1316, GetEmbedType1_Normal_1316) {
    psOutputDev = new PSOutputDev("file.ps", nullptr, "Test Title", 1, PSOutMode::eps, 100, 100, false, false, 0, 0, 0, 0, PSForceRasterize::no, false, nullptr, nullptr, PSLevel::level1);
    
    // Assuming we have the proper constructor and state set
    EXPECT_FALSE(psOutputDev->getEmbedType1());  // Assuming default value is false

    // Cleanup
    delete psOutputDev;
}

// Test for getEmbedType1 with altered state - Boundary Condition
TEST_F(PSOutputDevTest_1316, GetEmbedType1_AlteredState_1316) {
    psOutputDev = new PSOutputDev("file.ps", nullptr, "Test Title", 1, PSOutMode::eps, 100, 100, false, false, 0, 0, 0, 0, PSForceRasterize::no, false, nullptr, nullptr, PSLevel::level1);
    
    // Set EmbedType1 to true to test boundary condition
    psOutputDev->setEmbedType1(true);
    EXPECT_TRUE(psOutputDev->getEmbedType1());

    // Cleanup
    delete psOutputDev;
}

// Test for getEmbedType1 when state is false - Exceptional/Error case
TEST_F(PSOutputDevTest_1316, GetEmbedType1_Exceptional_1316) {
    psOutputDev = new PSOutputDev("file.ps", nullptr, "Test Title", 1, PSOutMode::eps, 100, 100, false, false, 0, 0, 0, 0, PSForceRasterize::no, false, nullptr, nullptr, PSLevel::level1);

    // Set EmbedType1 to false, should return false
    psOutputDev->setEmbedType1(false);
    EXPECT_FALSE(psOutputDev->getEmbedType1());

    // Cleanup
    delete psOutputDev;
}

// Test for setEmbedType1 - Normal operation
TEST_F(PSOutputDevTest_1316, SetEmbedType1_Normal_1316) {
    psOutputDev = new PSOutputDev("file.ps", nullptr, "Test Title", 1, PSOutMode::eps, 100, 100, false, false, 0, 0, 0, 0, PSForceRasterize::no, false, nullptr, nullptr, PSLevel::level1);

    // Set EmbedType1 to true and verify it
    psOutputDev->setEmbedType1(true);
    EXPECT_TRUE(psOutputDev->getEmbedType1());

    // Cleanup
    delete psOutputDev;
}

// Test for setting multiple embed types - Boundary condition
TEST_F(PSOutputDevTest_1316, SetMultipleEmbedTypes_1316) {
    psOutputDev = new PSOutputDev("file.ps", nullptr, "Test Title", 1, PSOutMode::eps, 100, 100, false, false, 0, 0, 0, 0, PSForceRasterize::no, false, nullptr, nullptr, PSLevel::level1);

    // Setting multiple embed types and testing them
    psOutputDev->setEmbedType1(true);
    psOutputDev->setEmbedTrueType(true);
    psOutputDev->setEmbedCIDPostScript(true);
    
    // Verify the states of the embed types
    EXPECT_TRUE(psOutputDev->getEmbedType1());
    EXPECT_TRUE(psOutputDev->getEmbedTrueType());
    EXPECT_TRUE(psOutputDev->getEmbedCIDPostScript());

    // Cleanup
    delete psOutputDev;
}