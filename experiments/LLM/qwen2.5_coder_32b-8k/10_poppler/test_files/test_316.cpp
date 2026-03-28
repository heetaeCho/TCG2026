#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Link.h"



using namespace testing;



class LinkSoundTest_316 : public Test {

protected:

    NiceMock<MockObject> mockSoundObj;

    std::unique_ptr<LinkSound> linkSound;



    void SetUp() override {

        linkSound = std::make_unique<LinkSound>(&mockSoundObj);

    }

};



TEST_F(LinkSoundTest_316, GetKindReturnsActionSound_316) {

    EXPECT_EQ(linkSound->getKind(), actionSound);

}



TEST_F(LinkSoundTest_316, IsOkReturnsTrueForValidObject_316) {

    EXPECT_CALL(mockSoundObj, isDict()).WillOnce(Return(true));

    EXPECT_TRUE(linkSound->isOk());

}



TEST_F(LinkSoundTest_316, GetVolumeReturnsExpectedValue_316) {

    // Assuming a way to set the volume for testing purposes

    EXPECT_CALL(mockSoundObj, dictLookup("V", _))

        .WillOnce(DoAll(SetArgReferee<1>(Object(0.5)), Return(true)));

    EXPECT_DOUBLE_EQ(linkSound->getVolume(), 0.5);

}



TEST_F(LinkSoundTest_316, GetSynchronousReturnsExpectedValue_316) {

    // Assuming a way to set the sync for testing purposes

    EXPECT_CALL(mockSoundObj, dictLookup("S", _))

        .WillOnce(DoAll(SetArgReferee<1>(Object(true)), Return(true)));

    EXPECT_TRUE(linkSound->getSynchronous());

}



TEST_F(LinkSoundTest_316, GetRepeatReturnsExpectedValue_316) {

    // Assuming a way to set the repeat for testing purposes

    EXPECT_CALL(mockSoundObj, dictLookup("R", _))

        .WillOnce(DoAll(SetArgReferee<1>(Object(false)), Return(true)));

    EXPECT_FALSE(linkSound->getRepeat());

}



TEST_F(LinkSoundTest_316, GetMixReturnsExpectedValue_316) {

    // Assuming a way to set the mix for testing purposes

    EXPECT_CALL(mockSoundObj, dictLookup("M", _))

        .WillOnce(DoAll(SetArgReferee<1>(Object(true)), Return(true)));

    EXPECT_TRUE(linkSound->getMix());

}



TEST_F(LinkSoundTest_316, GetSoundReturnsNonNullPointer_316) {

    EXPECT_CALL(mockSoundObj, dictLookup("Sound", _))

        .WillOnce(DoAll(SetArgReferee<1>(Object(Object::sound)), Return(true)));

    EXPECT_NE(linkSound->getSound(), nullptr);

}
