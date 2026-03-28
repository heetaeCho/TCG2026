#include <gtest/gtest.h>

#include "Rendition.h"



class MediaRenditionTest : public ::testing::Test {

protected:

    // Setup any common objects or state here if needed.

};



TEST_F(MediaRenditionTest_1244, IsOk_ReturnsTrue_1244) {

    Dict dict;

    MediaRendition mediaRendition(dict);

    EXPECT_TRUE(mediaRendition.isOk());

}



TEST_F(MediaRenditionTest_1244, GetMHParameters_ReturnsNonNull_1244) {

    Dict dict;

    MediaRendition mediaRendition(dict);

    EXPECT_NE(nullptr, mediaRendition.getMHParameters());

}



TEST_F(MediaRenditionTest_1244, GetBEParameters_ReturnsNonNull_1244) {

    Dict dict;

    MediaRendition mediaRendition(dict);

    EXPECT_NE(nullptr, mediaRendition.getBEParameters());

}



TEST_F(MediaRenditionTest_1244, GetContentType_ReturnsNonNull_1244) {

    Dict dict;

    MediaRendition mediaRendition(dict);

    EXPECT_NE(nullptr, mediaRendition.getContentType());

}



TEST_F(MediaRenditionTest_1244, GetFileName_ReturnsNonNull_1244) {

    Dict dict;

    MediaRendition mediaRendition(dict);

    EXPECT_NE(nullptr, mediaRendition.getFileName());

}



TEST_F(MediaRenditionTest_1244, GetIsEmbedded_ReturnsFalse_1244) {

    Dict dict;

    MediaRendition mediaRendition(dict);

    EXPECT_FALSE(mediaRendition.getIsEmbedded());

}



TEST_F(MediaRenditionTest_1244, GetEmbbededStream_ReturnsNull_1244) {

    Dict dict;

    MediaRendition mediaRendition(dict);

    EXPECT_EQ(nullptr, mediaRendition.getEmbbededStream());

}



TEST_F(MediaRenditionTest_1244, GetEmbbededStreamObject_ReturnsNonNull_1244) {

    Dict dict;

    MediaRendition mediaRendition(dict);

    EXPECT_NE(nullptr, mediaRendition.getEmbbededStreamObject());

}

```


