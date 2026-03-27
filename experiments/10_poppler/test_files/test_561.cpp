#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



using namespace testing;



// Mock class for GfxColorTransform if needed

class MockGfxColorTransform : public GfxColorTransform {

public:

    MOCK_METHOD0(someMethod, void());

};



TEST(GfxXYZ2DisplayTransformsTest_561, GetSat_ReturnsNonNullPointer_561) {

    GfxLCMSProfilePtr mockProfile = std::make_shared<GfxLCMSProfile>();

    GfxXYZ2DisplayTransforms transforms(mockProfile);

    EXPECT_NE(transforms.getSat(), nullptr);

}



TEST(GfxXYZ2DisplayTransformsTest_561, GetSat_ReturnsConsistentPointer_561) {

    GfxLCMSProfilePtr mockProfile = std::make_shared<GfxLCMSProfile>();

    GfxXYZ2DisplayTransforms transforms(mockProfile);

    auto sat1 = transforms.getSat();

    auto sat2 = transforms.getSat();

    EXPECT_EQ(sat1, sat2);

}



TEST(GfxXYZ2DisplayTransformsTest_561, GetRelCol_ReturnsNonNullPointer_561) {

    GfxLCMSProfilePtr mockProfile = std::make_shared<GfxLCMSProfile>();

    GfxXYZ2DisplayTransforms transforms(mockProfile);

    EXPECT_NE(transforms.getRelCol(), nullptr);

}



TEST(GfxXYZ2DisplayTransformsTest_561, GetAbsCol_ReturnsNonNullPointer_561) {

    GfxLCMSProfilePtr mockProfile = std::make_shared<GfxLCMSProfile>();

    GfxXYZ2DisplayTransforms transforms(mockProfile);

    EXPECT_NE(transforms.getAbsCol(), nullptr);

}



TEST(GfxXYZ2DisplayTransformsTest_561, GetPerc_ReturnsNonNullPointer_561) {

    GfxLCMSProfilePtr mockProfile = std::make_shared<GfxLCMSProfile>();

    GfxXYZ2DisplayTransforms transforms(mockProfile);

    EXPECT_NE(transforms.getPerc(), nullptr);

}



TEST(GfxXYZ2DisplayTransformsTest_561, GetDisplayProfile_ReturnsProvidedProfile_561) {

    auto mockProfile = std::make_shared<GfxLCMSProfile>();

    GfxXYZ2DisplayTransforms transforms(mockProfile);

    EXPECT_EQ(transforms.getDisplayProfile(), mockProfile);

}
