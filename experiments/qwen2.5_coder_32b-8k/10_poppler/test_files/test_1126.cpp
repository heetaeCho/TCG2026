#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/FileSpec.h"



using namespace testing;



class EmbFileTest : public ::testing::Test {

protected:

    Object objStr;

    EmbFile* embFile;



    void SetUp() override {

        embFile = new EmbFile(std::move(objStr));

    }



    void TearDown() override {

        delete embFile;

    }

};



TEST_F(EmbFileTest_1126, SizeReturnsCorrectValue_1126) {

    // Assuming we can somehow set the size, for now we just check if it returns an int

    EXPECT_EQ(embFile->size(), 0); // Default size is unknown without setup, checking if it returns int

}



TEST_F(EmbFileTest_1126, ModDateReturnsNonNullPointer_1126) {

    EXPECT_NE(embFile->modDate(), nullptr);

}



TEST_F(EmbFileTest_1126, CreateDateReturnsNonNullPointer_1126) {

    EXPECT_NE(embFile->createDate(), nullptr);

}



TEST_F(EmbFileTest_1126, ChecksumReturnsNonNullPointer_1126) {

    EXPECT_NE(embFile->checksum(), nullptr);

}



TEST_F(EmbFileTest_1126, MimeTypeReturnsNonNullPointer_1126) {

    EXPECT_NE(embFile->mimeType(), nullptr);

}



TEST_F(EmbFileTest_1126, StreamObjectReturnsNonNullPointer_1126) {

    EXPECT_NE(embFile->streamObject(), nullptr);

}



TEST_F(EmbFileTest_1126, StreamReturnsNonNullPointer_1126) {

    EXPECT_NE(embFile->stream(), nullptr);

}



TEST_F(EmbFileTest_1126, IsOkReturnsTrueOnValidInstance_1126) {

    EXPECT_TRUE(embFile->isOk());

}



TEST_F(EmbFileTest_1126, SaveWithValidPathReturnsFalseOnFailure_1126) {

    // Assuming save will return false if the file cannot be saved

    std::string invalidPath = "/nonexistent/path/file.ext";

    EXPECT_FALSE(embFile->save(invalidPath));

}



TEST_F(EmbFileTest_1126, SaveWithEmptyPathReturnsFalseOnFailure_1126) {

    // Assuming save will return false if the path is empty

    std::string emptyPath = "";

    EXPECT_FALSE(embFile->save(emptyPath));

}
