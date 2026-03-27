#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Rendition.h"

#include "Object.h"



using namespace testing;



// Mocking Stream for verification purposes.

class MockStream : public Stream {

public:

    MOCK_METHOD(void, close, (), (override));

};



TEST_F(MediaRenditionTest_1248, GetEmbeddedStream_ReturnsNullptrWhenNotEmbedded_1248) {

    MediaRendition rendition(Dict{});

    EXPECT_FALSE(rendition.getIsEmbedded());

    EXPECT_EQ(rendition.getEmbbededStream(), nullptr);

}



TEST_F(MediaRenditionTest_1248, GetEmbeddedStream_ReturnsValidStreamWhenEmbedded_1248) {

    Dict mockDict;

    Object mockObject(std::make_unique<GooString>("dummy content"));

    mockDict.dictAdd("Embedded", std::move(mockObject));

    MediaRendition rendition(mockDict);

    EXPECT_TRUE(rendition.getIsEmbedded());

    EXPECT_NE(rendition.getEmbbededStream(), nullptr);

}



TEST_F(MediaRenditionTest_1248, GetContentType_ReturnsNullptrWhenNotSet_1248) {

    MediaRendition rendition(Dict{});

    EXPECT_EQ(rendition.getContentType(), nullptr);

}



TEST_F(MediaRenditionTest_1248, GetContentType_ReturnsValidGooStringWhenSet_1248) {

    Dict mockDict;

    Object mockObject(std::make_unique<GooString>("video/mp4"));

    mockDict.dictAdd("ContentType", std::move(mockObject));

    MediaRendition rendition(mockDict);

    EXPECT_STREQ(rendition.getContentType()->c_str(), "video/mp4");

}



TEST_F(MediaRenditionTest_1248, GetFileName_ReturnsNullptrWhenNotSet_1248) {

    MediaRendition rendition(Dict{});

    EXPECT_EQ(rendition.getFileName(), nullptr);

}



TEST_F(MediaRenditionTest_1248, GetFileName_ReturnsValidGooStringWhenSet_1248) {

    Dict mockDict;

    Object mockObject(std::make_unique<GooString>("example.mp4"));

    mockDict.dictAdd("FileName", std::move(mockObject));

    MediaRendition rendition(mockDict);

    EXPECT_STREQ(rendition.getFileName()->c_str(), "example.mp4");

}



TEST_F(MediaRenditionTest_1248, IsOk_ReturnsFalseWhenEmbeddedStreamNotSet_1248) {

    MediaRendition rendition(Dict{});

    EXPECT_FALSE(rendition.isOk());

}



TEST_F(MediaRenditionTest_1248, IsOk_ReturnsTrueWhenEmbeddedStreamSet_1248) {

    Dict mockDict;

    Object mockObject(std::make_unique<GooString>("dummy content"));

    mockDict.dictAdd("Embedded", std::move(mockObject));

    MediaRendition rendition(mockDict);

    EXPECT_TRUE(rendition.isOk());

}
