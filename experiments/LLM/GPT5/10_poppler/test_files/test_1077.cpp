#include <gtest/gtest.h>
#include "./TestProjects/poppler/poppler/OutputDev.h"

// Test class to verify the functionality of OutputDev class methods
class OutputDevTest_1077 : public testing::Test {
protected:
    // You can add setup and teardown if needed
    OutputDev* outputDev;

    void SetUp() override {
        // Initialize the OutputDev object
        outputDev = new OutputDev();
    }

    void TearDown() override {
        delete outputDev;
    }
};

// Test normal operation of getVectorAntialias method
TEST_F(OutputDevTest_1077, GetVectorAntialiasNormal_1077) {
    // Verify that getVectorAntialias returns false by default
    EXPECT_FALSE(outputDev->getVectorAntialias());
}

// Test normal operation of setVectorAntialias method
TEST_F(OutputDevTest_1077, SetVectorAntialiasNormal_1077) {
    // Set the vector antialias flag to true
    outputDev->setVectorAntialias(true);

    // Verify that the flag is set correctly
    EXPECT_TRUE(outputDev->getVectorAntialias());

    // Set the vector antialias flag to false
    outputDev->setVectorAntialias(false);

    // Verify that the flag is set back to false
    EXPECT_FALSE(outputDev->getVectorAntialias());
}

// Test boundary condition for getVectorAntialias when no action is taken
TEST_F(OutputDevTest_1077, GetVectorAntialiasBoundary_1077) {
    // Verify that getVectorAntialias returns false by default
    EXPECT_FALSE(outputDev->getVectorAntialias());
}

// Test exceptional or error case for getVectorAntialias
TEST_F(OutputDevTest_1077, GetVectorAntialiasError_1077) {
    // There is no clear error case for this method, but we can test edge conditions if applicable
    // No action is required for this method as the default value is already false.
    EXPECT_FALSE(outputDev->getVectorAntialias());
}

// Test external interaction using setVectorAntialias and getVectorAntialias together
TEST_F(OutputDevTest_1077, SetAndGetVectorAntialiasInteraction_1077) {
    // Set vector antialias to true
    outputDev->setVectorAntialias(true);
    
    // Verify that getVectorAntialias returns true
    EXPECT_TRUE(outputDev->getVectorAntialias());
    
    // Set vector antialias to false
    outputDev->setVectorAntialias(false);
    
    // Verify that getVectorAntialias returns false
    EXPECT_FALSE(outputDev->getVectorAntialias());
}