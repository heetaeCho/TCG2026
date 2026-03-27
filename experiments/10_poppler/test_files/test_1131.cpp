#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "FileSpec.h"

#include <string>



using namespace testing;



class EmbFileTest_1131 : public ::testing::Test {

protected:

    Object mockObject;

    std::unique_ptr<EmbFile> embFile;



    void SetUp() override {

        mockObject.initNull();

        embFile = std::make_unique<EmbFile>(std::move(mockObject));

    }

};



TEST_F(EmbFileTest_1131, StreamObject_ReturnsValidPointer_1131) {

    EXPECT_NE(embFile->streamObject(), nullptr);

}



TEST_F(EmbFileTest_1131, Save_ReturnsFalseForInvalidPath_1131) {

    EXPECT_FALSE(embFile->save("nonexistent/path/invalidfile.txt"));

}



TEST_F(EmbFileTest_1131, Size_ReturnsNonNegativeValue_1131) {

    EXPECT_GE(embFile->size(), 0);

}



TEST_F(EmbFileTest_1131, ModDate_ReturnsNullWhenNotSet_1131) {

    EXPECT_EQ(embFile->modDate(), nullptr);

}



TEST_F(EmbFileTest_1131, CreateDate_ReturnsNullWhenNotSet_1131) {

    EXPECT_EQ(embFile->createDate(), nullptr);

}



TEST_F(EmbFileTest_1131, Checksum_ReturnsNullWhenNotSet_1131) {

    EXPECT_EQ(embFile->checksum(), nullptr);

}



TEST_F(EmbFileTest_1131, MimeType_ReturnsNullWhenNotSet_1131) {

    EXPECT_EQ(embFile->mimeType(), nullptr);

}



TEST_F(EmbFileTest_1131, Stream_ReturnsValidPointer_1131) {

    EXPECT_NE(embFile->stream(), nullptr);

}



TEST_F(EmbFileTest_1131, IsOk_ReturnsTrueWhenObjectIsValid_1131) {

    EXPECT_TRUE(embFile->isOk());

}
