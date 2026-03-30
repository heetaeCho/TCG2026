#include <gtest/gtest.h>

#include "Stream.h"

#include <memory>



class MockGooFile : public GooFile {

public:

    MOCK_METHOD(Goffset, read, (unsigned char *buf, Goffset nBytes), (override));

    MOCK_METHOD(void, close, (), (override));

};



class FileStreamTest_153 : public ::testing::Test {

protected:

    void SetUp() override {

        gooFile = std::make_unique<MockGooFile>();

        fileStream = std::make_unique<FileStream>(gooFile.get(), 0, false, 0, Object());

    }



    void TearDown() override {

        fileStream.reset();

        gooFile.reset();

    }



    std::unique_ptr<MockGooFile> gooFile;

    std::unique_ptr<FileStream> fileStream;

};



TEST_F(FileStreamTest_153, GetUnfilteredCharDelegatesToGetChar_153) {

    EXPECT_CALL(*gooFile, read(::testing::_, 1)).WillOnce(::testing::Return(1));

    int result = fileStream->getUnfilteredChar();

    EXPECT_EQ(result, fileStream->getChar());

}



TEST_F(FileStreamTest_153, GetKindIsImplemented_153) {

    StreamKind kind = fileStream->getKind();

    EXPECT_TRUE(kind == streamNone || kind == streamFile);

}



TEST_F(FileStreamTest_153, RewindReturnsTrueOnSuccess_153) {

    EXPECT_CALL(*gooFile, read(::testing::_, ::testing::_)).WillOnce(::testing::Return(1));

    fileStream->getChar();

    bool result = fileStream->rewind();

    EXPECT_TRUE(result);

}



TEST_F(FileStreamTest_153, CloseDelegatesToGooFileClose_153) {

    EXPECT_CALL(*gooFile, close()).Times(1);

    fileStream->close();

}



TEST_F(FileStreamTest_153, SetPosUpdatesPosition_153) {

    Goffset initialPos = fileStream->getPos();

    fileStream->setPos(initialPos + 10, 0);

    EXPECT_EQ(fileStream->getPos(), initialPos + 10);

}



TEST_F(FileStreamTest_153, MoveStartAdjustsStartPosition_153) {

    Goffset initialStart = fileStream->getStart();

    fileStream->moveStart(20);

    EXPECT_EQ(fileStream->getStart(), initialStart + 20);

}



TEST_F(FileStreamTest_153, GetPosReturnsCurrentPosition_153) {

    Goffset pos = fileStream->getPos();

    EXPECT_TRUE(pos >= 0);

}



TEST_F(FileStreamTest_153, GetStartReturnsStartPosition_153) {

    Goffset start = fileStream->getStart();

    EXPECT_TRUE(start == 0); // Assuming default constructor initializes start to 0

}



TEST_F(FileStreamTest_153, UnfilteredRewindCallsRewind_153) {

    EXPECT_CALL(*gooFile, read(::testing::_, ::testing::_)).WillOnce(::testing::Return(1));

    fileStream->getChar();

    bool result = fileStream->unfilteredRewind();

    EXPECT_TRUE(result);

}



TEST_F(FileStreamTest_153, GetNeedsEncryptionOnSaveReturnsSetValue_153) {

    bool initialEncryptionState = fileStream->getNeedsEncryptionOnSave();

    fileStream->setNeedsEncryptionOnSave(!initialEncryptionState);

    EXPECT_EQ(fileStream->getNeedsEncryptionOnSave(), !initialEncryptionState);

}
