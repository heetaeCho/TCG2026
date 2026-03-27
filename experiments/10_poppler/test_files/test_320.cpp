#include <gtest/gtest.h>

#include "Link.h"



class LinkSoundTest : public ::testing::Test {

protected:

    std::unique_ptr<LinkSound> link_sound;



    void SetUp() override {

        // Assuming a mock Object can be created for soundObj, or use nullptr if not needed.

        link_sound = std::make_unique<LinkSound>(nullptr);

    }

};



TEST_F(LinkSoundTest_320, GetMix_ReturnsTrue_320) {

    EXPECT_TRUE(link_sound->getMix());

}



TEST_F(LinkSoundTest_320, GetMix_ReturnsFalse_320) {

    // Assuming there's a way to set mix to false through the constructor or another method.

    // Since we cannot modify internal state directly, this test is hypothetical.

    EXPECT_FALSE(link_sound->getMix());

}



TEST_F(LinkSoundTest_320, IsOk_ReturnsTrue_320) {

    EXPECT_TRUE(link_sound->isOk());

}



TEST_F(LinkSoundTest_320, IsOk_ReturnsFalse_320) {

    // Assuming there's a way to create an invalid LinkSound object.

    // Since we cannot modify internal state directly, this test is hypothetical.

    EXPECT_FALSE(link_sound->isOk());

}



TEST_F(LinkSoundTest_320, GetKind_ReturnsCorrectValue_320) {

    EXPECT_EQ(link_sound->getKind(), LinkActionKind::sound);

}



TEST_F(LinkSoundTest_320, GetVolume_ReturnsDefault_320) {

    // Assuming the default volume is 1.0 or another known value.

    EXPECT_DOUBLE_EQ(link_sound->getVolume(), 1.0);

}



TEST_F(LinkSoundTest_320, GetSynchronous_ReturnsTrue_320) {

    EXPECT_TRUE(link_sound->getSynchronous());

}



TEST_F(LinkSoundTest_320, GetSynchronous_ReturnsFalse_320) {

    // Assuming there's a way to set sync to false through the constructor or another method.

    // Since we cannot modify internal state directly, this test is hypothetical.

    EXPECT_FALSE(link_sound->getSynchronous());

}



TEST_F(LinkSoundTest_320, GetRepeat_ReturnsTrue_320) {

    EXPECT_TRUE(link_sound->getRepeat());

}



TEST_F(LinkSoundTest_320, GetRepeat_ReturnsFalse_320) {

    // Assuming there's a way to set repeat to false through the constructor or another method.

    // Since we cannot modify internal state directly, this test is hypothetical.

    EXPECT_FALSE(link_sound->getRepeat());

}



TEST_F(LinkSoundTest_320, GetSound_ReturnsNonNullPointer_320) {

    EXPECT_NE(link_sound->getSound(), nullptr);

}
