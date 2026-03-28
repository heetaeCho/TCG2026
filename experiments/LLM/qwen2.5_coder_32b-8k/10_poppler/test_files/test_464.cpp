#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



// Mocking GfxLCMSProfilePtr for testing purposes if needed

class MockGfxLCMSProfile : public GfxLCMSProfile {

    // Add any necessary mock methods here

};



using ::testing::Return;

using ::testing::_;



class GfxICCBasedColorSpaceTest_464 : public ::testing::Test {

protected:

    std::unique_ptr<GfxColorSpace> altColorSpace;

    Ref iccProfileStreamRef;

    std::shared_ptr<MockGfxLCMSProfile> mockProfile;



    void SetUp() override {

        altColorSpace = nullptr; // Assuming no alternative color space for simplicity

        iccProfileStreamRef.num = 0;

        iccProfileStreamRef.gen = 0;

        mockProfile = std::make_shared<MockGfxLCMSProfile>();

    }



    GfxICCBasedColorSpace createTestSubject() {

        return GfxICCBasedColorSpace(3, std::move(altColorSpace), &iccProfileStreamRef);

    }

};



TEST_F(GfxICCBasedColorSpaceTest_464, GetProfile_ReturnsInitialProfile_464) {

    GfxICCBasedColorSpace subject = createTestSubject();

    EXPECT_EQ(subject.getProfile(), nullptr);

}



TEST_F(GfxICCBasedColorSpaceTest_464, SetAndGetProfile_SuccessfullySetsAndRetrievesProfile_464) {

    GfxICCBasedColorSpace subject = createTestSubject();

    GfxLCMSProfilePtr profilePtr = mockProfile;

    subject.setProfile(profilePtr);

    EXPECT_EQ(subject.getProfile(), profilePtr);

}



TEST_F(GfxICCBasedColorSpaceTest_464, SetProfile_NullptrDoesNotThrow_464) {

    GfxICCBasedColorSpace subject = createTestSubject();

    GfxLCMSProfilePtr nullProfile = nullptr;

    EXPECT_NO_THROW(subject.setProfile(nullProfile));

}



TEST_F(GfxICCBasedColorSpaceTest_464, SetProfile_MultipleTimesRetainsLastProfile_464) {

    GfxICCBasedColorSpace subject = createTestSubject();

    GfxLCMSProfilePtr firstProfile = mockProfile;

    subject.setProfile(firstProfile);



    auto secondMockProfile = std::make_shared<MockGfxLCMSProfile>();

    GfxLCMSProfilePtr secondProfile = secondMockProfile;

    subject.setProfile(secondProfile);

    

    EXPECT_EQ(subject.getProfile(), secondProfile);

}
