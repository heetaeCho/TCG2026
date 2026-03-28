#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "ImageEmbeddingUtils.cc"

#include "XRef.h"

#include "GooFile.h"



using namespace ImageEmbeddingUtils;

using namespace testing;



class ImageEmbeddingUtilsTest_1867 : public Test {

protected:

    XRef* xref;

    std::string imagePath;



    void SetUp() override {

        xref = new XRef();

        imagePath = "test_image_path";

    }



    void TearDown() override {

        delete xref;

    }

};



TEST_F(ImageEmbeddingUtilsTest_1867, EmbedReturnsInvalidRefWhenFileOpenFails_1867) {

    EXPECT_CALL(GooFile::open(imagePath), Times(1)).WillOnce(Return(nullptr));

    Ref result = embed(xref, imagePath);

    EXPECT_EQ(result.num, Ref::INVALID().num);

    EXPECT_EQ(result.gen, Ref::INVALID().gen);

}



TEST_F(ImageEmbeddingUtilsTest_1867, EmbedCallsGooFileOpenWithCorrectPath_1867) {

    std::unique_ptr<GooFile> mockGooFile = std::make_unique<GooFile>(0);

    EXPECT_CALL(GooFile::open(imagePath), Times(1)).WillOnce(Return(ByMove(std::move(mockGooFile))));

    embed(xref, imagePath);

}



TEST_F(ImageEmbeddingUtilsTest_1867, EmbedReturnsValidRefWhenFileOpenSucceeds_1867) {

    std::unique_ptr<GooFile> mockGooFile = std::make_unique<GooFile>(0);

    EXPECT_CALL(GooFile::open(imagePath), Times(1)).WillOnce(Return(ByMove(std::move(mockGooFile))));

    Ref result = embed(xref, imagePath);

    EXPECT_NE(result.num, Ref::INVALID().num);

    EXPECT_NE(result.gen, Ref::INVALID().gen);

}



TEST_F(ImageEmbeddingUtilsTest_1867, EmbedHandlesEmptyImagePath_1867) {

    std::string emptyPath = "";

    EXPECT_CALL(GooFile::open(emptyPath), Times(1)).WillOnce(Return(nullptr));

    Ref result = embed(xref, emptyPath);

    EXPECT_EQ(result.num, Ref::INVALID().num);

    EXPECT_EQ(result.gen, Ref::INVALID().gen);

}



TEST_F(ImageEmbeddingUtilsTest_1867, EmbedHandlesTooLongImagePath_1867) {

    std::string longPath(PATH_MAX + 1, 'a');

    EXPECT_CALL(GooFile::open(longPath), Times(1)).WillOnce(Return(nullptr));

    Ref result = embed(xref, longPath);

    EXPECT_EQ(result.num, Ref::INVALID().num);

    EXPECT_EQ(result.gen, Ref::INVALID().gen);

}
