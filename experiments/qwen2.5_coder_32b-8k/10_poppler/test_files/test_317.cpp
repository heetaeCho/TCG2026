#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Link.h"



class LinkSoundTest_317 : public ::testing::Test {

protected:

    LinkSound* linkSound;



    virtual void SetUp() {

        // Assuming a valid Object is required to construct LinkSound

        // Here we mock or assume an appropriate Object for testing

        Object soundObj; // This should be properly initialized as per actual usage

        linkSound = new LinkSound(&soundObj);

    }



    virtual void TearDown() {

        delete linkSound;

    }

};



TEST_F(LinkSoundTest_317, GetVolume_ReturnsExpectedValue_317) {

    double expectedVolume = 0.5; // Assuming a way to set or know the volume

    EXPECT_EQ(linkSound->getVolume(), expectedVolume);

}



TEST_F(LinkSoundTest_317, IsOk_ReturnsTrueForValidLinkSound_317) {

    EXPECT_TRUE(linkSound->isOk());

}



TEST_F(LinkSoundTest_317, GetKind_ReturnsCorrectType_317) {

    EXPECT_EQ(linkSound->getKind(), LinkActionKind::sound);

}



TEST_F(LinkSoundTest_317, GetSynchronous_ReturnsExpectedValue_317) {

    bool expectedSync = true; // Assuming a way to set or know the sync value

    EXPECT_EQ(linkSound->getSynchronous(), expectedSync);

}



TEST_F(LinkSoundTest_317, GetRepeat_ReturnsExpectedValue_317) {

    bool expectedRepeat = false; // Assuming a way to set or know the repeat value

    EXPECT_EQ(linkSound->getRepeat(), expectedRepeat);

}



TEST_F(LinkSoundTest_317, GetMix_ReturnsExpectedValue_317) {

    bool expectedMix = true; // Assuming a way to set or know the mix value

    EXPECT_EQ(linkSound->getMix(), expectedMix);

}



TEST_F(LinkSoundTest_317, GetSound_ReturnsNonNullPointer_317) {

    EXPECT_NE(linkSound->getSound(), nullptr);

}
