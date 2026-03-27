#include <gtest/gtest.h>

#include "Stream.h"



class FileStreamTest : public ::testing::Test {

protected:

    std::unique_ptr<FileStream> fileStream;



    void SetUp() override {

        // Mock GooFile and Object for constructor

        GooFile* mockGooFile = nullptr; // Assuming GooFile can be null in this context

        Object dictA; // Default constructed Object



        fileStream = std::make_unique<FileStream>(mockGooFile, 0, false, 0, std::move(dictA));

    }

};



TEST_F(FileStreamTest_156, SetNeedsEncryptionOnSave_True_156) {

    fileStream->setNeedsEncryptionOnSave(true);

    EXPECT_TRUE(fileStream->getNeedsEncryptionOnSave());

}



TEST_F(FileStreamTest_156, SetNeedsEncryptionOnSave_False_156) {

    fileStream->setNeedsEncryptionOnSave(false);

    EXPECT_FALSE(fileStream->getNeedsEncryptionOnSave());

}



TEST_F(FileStreamTest_156, SetNeedsEncryptionOnSave_DefaultValue_156) {

    // Default value should be false as per typical behavior of bool in C++

    EXPECT_FALSE(fileStream->getNeedsEncryptionOnSave());

}
