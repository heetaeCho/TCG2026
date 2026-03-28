#include <gtest/gtest.h>

#include "GfxState.h"



// Test fixture for GfxSeparationColorSpace

class GfxSeparationColorSpaceTest_478 : public ::testing::Test {

protected:

    std::unique_ptr<GooString> name;

    std::unique_ptr<GfxColorSpace> alt;

    std::unique_ptr<Function> func;



    void SetUp() override {

        name = std::make_unique<GooString>("TestName");

        alt = nullptr; // Assuming no alternative color space for simplicity

        func = nullptr; // Assuming no function for simplicity

    }

};



// Test that getName returns the correct GooString pointer

TEST_F(GfxSeparationColorSpaceTest_478, GetNameReturnsCorrectPointer_478) {

    GfxSeparationColorSpace separation(std::move(name), std::move(alt), std::move(func));

    EXPECT_EQ("TestName", separation.getName()->c_str());

}



// Test that getName returns the same pointer after multiple calls

TEST_F(GfxSeparationColorSpaceTest_478, GetNameConsistentPointer_478) {

    GfxSeparationColorSpace separation(std::make_unique<GooString>("TestName"), nullptr, nullptr);

    const GooString* namePtr1 = separation.getName();

    const GooString* namePtr2 = separation.getName();

    EXPECT_EQ(namePtr1, namePtr2);

}



// Test that getName returns a non-null pointer

TEST_F(GfxSeparationColorSpaceTest_478, GetNameReturnsNonNullPointer_478) {

    GfxSeparationColorSpace separation(std::make_unique<GooString>("TestName"), nullptr, nullptr);

    EXPECT_NE(nullptr, separation.getName());

}



// Test that getName returns a non-null pointer when name is empty

TEST_F(GfxSeparationColorSpaceTest_478, GetNameReturnsNonNullForEmptyName_478) {

    GfxSeparationColorSpace separation(std::make_unique<GooString>(""), nullptr, nullptr);

    EXPECT_NE(nullptr, separation.getName());

}



// Test that getName returns the correct name when alt and func are null

TEST_F(GfxSeparationColorSpaceTest_478, GetNameCorrectWithNullAltAndFunc_478) {

    GfxSeparationColorSpace separation(std::make_unique<GooString>("TestName"), nullptr, nullptr);

    EXPECT_EQ("TestName", separation.getName()->c_str());

}
