#include <gtest/gtest.h>

#include "GfxState.h"



// Mock class if needed (not required based on current interface)

// class MockGfxColorSpace : public GfxColorSpace {

//     // Define mock methods as needed

// };



class GfxICCBasedColorSpaceTest_461 : public ::testing::Test {

protected:

    void SetUp() override {

        alt = std::make_unique<GfxColorSpace>();

        testObject = std::make_unique<GfxICCBasedColorSpace>(3, std::move(alt), nullptr);

    }



    std::unique_ptr<GfxColorSpace> alt;

    std::unique_ptr<GfxICCBasedColorSpace> testObject;

};



TEST_F(GfxICCBasedColorSpaceTest_461, GetAltReturnsCorrectPointer_461) {

    EXPECT_EQ(testObject->getAlt(), alt.get());

}



// Assuming getRef and setProfile/getProfile can be tested with some mock or stub if needed

// For now, we only have the method based on provided interface



TEST_F(GfxICCBasedColorSpaceTest_461, GetAltReturnsNullIfAltNotSet_461) {

    testObject = std::make_unique<GfxICCBasedColorSpace>(3, nullptr, nullptr);

    EXPECT_EQ(testObject->getAlt(), nullptr);

}
