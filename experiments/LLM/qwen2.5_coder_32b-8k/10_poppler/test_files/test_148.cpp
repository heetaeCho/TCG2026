#include <gtest/gtest.h>

#include "Stream.h"



class FileStreamTest : public ::testing::Test {

protected:

    GooFile* mockGooFile;

    std::unique_ptr<FileStream> fileStream;



    void SetUp() override {

        mockGooFile = new GooFile();

        fileStream = std::make_unique<FileStream>(mockGooFile, 0, false, 0, Object());

    }



    void TearDown() override {

        delete mockGooFile;

    }

};



TEST_F(FileStreamTest_148, GetKind_ReturnsStrFile_148) {

    EXPECT_EQ(fileStream->getKind(), strFile);

}



TEST_F(FileStreamTest_148, Rewind_ReturnsTrue_148) {

    EXPECT_TRUE(fileStream->rewind());

}



TEST_F(FileStreamTest_148, Close_DoesNotThrow_148) {

    EXPECT_NO_THROW(fileStream->close());

}



TEST_F(FileStreamTest_148, SetPos_NoExceptionOnValidInput_148) {

    EXPECT_NO_THROW(fileStream->setPos(0, 0));

}



TEST_F(FileStreamTest_148, MoveStart_NoExceptionOnValidInput_148) {

    EXPECT_NO_THROW(fileStream->moveStart(0));

}



TEST_F(FileStreamTest_148, GetUnfilteredChar_ReturnsInt_148) {

    int result = fileStream->getUnfilteredChar();

    EXPECT_TRUE(result >= -1); // Assuming getUnfilteredChar returns -1 on EOF or error

}



TEST_F(FileStreamTest_148, UnfilteredRewind_ReturnsTrue_148) {

    EXPECT_TRUE(fileStream->unfilteredRewind());

}



TEST_F(FileStreamTest_148, GetNeedsEncryptionOnSave_DefaultValue_148) {

    EXPECT_FALSE(fileStream->getNeedsEncryptionOnSave());

}



TEST_F(FileStreamTest_148, SetAndGetNeedsEncryptionOnSave_148) {

    fileStream->setNeedsEncryptionOnSave(true);

    EXPECT_TRUE(fileStream->getNeedsEncryptionOnSave());



    fileStream->setNeedsEncryptionOnSave(false);

    EXPECT_FALSE(fileStream->getNeedsEncryptionOnSave());

}
