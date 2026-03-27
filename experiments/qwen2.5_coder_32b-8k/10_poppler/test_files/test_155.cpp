#include <gtest/gtest.h>

#include "Stream.h"



class FileStreamTest_155 : public ::testing::Test {

protected:

    GooFile* mockGooFile;

    std::unique_ptr<FileStream> fileStream;



    void SetUp() override {

        mockGooFile = new GooFile();

        fileStream = std::make_unique<FileStream>(mockGooFile, 0, false, 1024, Object());

    }



    void TearDown() override {

        delete mockGooFile;

    }

};



TEST_F(FileStreamTest_155, GetNeedsEncryptionOnSave_DefaultValue_155) {

    EXPECT_FALSE(fileStream->getNeedsEncryptionOnSave());

}



TEST_F(FileStreamTest_155, SetAndGetNeedsEncryptionOnSave_True_155) {

    fileStream->setNeedsEncryptionOnSave(true);

    EXPECT_TRUE(fileStream->getNeedsEncryptionOnSave());

}



TEST_F(FileStreamTest_155, SetAndGetNeedsEncryptionOnSave_False_155) {

    fileStream->setNeedsEncryptionOnSave(false);

    EXPECT_FALSE(fileStream->getNeedsEncryptionOnSave());

}
