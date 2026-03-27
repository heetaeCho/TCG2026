#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Rendition.h"



class MediaRenditionTest_1247 : public ::testing::Test {

protected:

    Dict dummyDict;

    std::unique_ptr<MediaRendition> mediaRendition;



    void SetUp() override {

        mediaRendition = std::make_unique<MediaRendition>(dummyDict);

    }

};



TEST_F(MediaRenditionTest_1247, IsOk_ReturnsTrue_1247) {

    EXPECT_TRUE(mediaRendition->isOk());

}



TEST_F(MediaRenditionTest_1247, GetMHParameters_ReturnsValidPointer_1247) {

    EXPECT_NE(mediaRendition->getMHParameters(), nullptr);

}



TEST_F(MediaRenditionTest_1247, GetBEParameters_ReturnsValidPointer_1247) {

    EXPECT_NE(mediaRendition->getBEParameters(), nullptr);

}



TEST_F(MediaRenditionTest_1247, GetContentType_ReturnsValidPointer_1247) {

    EXPECT_NE(mediaRendition->getContentType(), nullptr);

}



TEST_F(MediaRenditionTest_1247, GetFileName_ReturnsValidPointer_1247) {

    EXPECT_NE(mediaRendition->getFileName(), nullptr);

}



TEST_F(MediaRenditionTest_1247, GetIsEmbedded_ReturnsFalse_WhenNotEmbedded_1247) {

    // Assuming the MediaRendition is not embedded by default

    EXPECT_FALSE(mediaRendition->getIsEmbedded());

}



TEST_F(MediaRenditionTest_1247, GetEmbbededStream_ReturnsNullptr_WhenNotEmbedded_1247) {

    // Assuming the MediaRendition does not have an embedded stream if not embedded

    EXPECT_EQ(mediaRendition->getEmbbededStream(), nullptr);

}



TEST_F(MediaRenditionTest_1247, GetEmbbededStreamObject_ReturnsNullptr_WhenNotEmbedded_1247) {

    // Assuming the MediaRendition does not have an embedded stream object if not embedded

    EXPECT_EQ(mediaRendition->getEmbbededStreamObject(), nullptr);

}



TEST_F(MediaRenditionTest_1247, Copy_ReturnsNonNegativeValue_1247) {

    EXPECT_GE(mediaRendition->copy(), 0);

}
