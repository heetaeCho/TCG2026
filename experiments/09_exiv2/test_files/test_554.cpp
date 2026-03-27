#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using ::testing::NiceMock;



// Mock class for BasicIo to simulate interactions with the source object

class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo& src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo& src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string&, path, (), (const override));

};



class FileIoTest : public ::testing::Test {

protected:

    NiceMock<MockBasicIo> mockSrc;

    std::unique_ptr<FileIo> fileIo;



    void SetUp() override {

        fileIo = std::make_unique<FileIo>("testfile");

    }



    void TearDown() override {

        // Cleanup if necessary

    }

};



TEST_F(FileIoTest, TransferFromSameType_554) {

    EXPECT_CALL(mockSrc, isopen()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockSrc, path()).WillOnce(::testing::Return("sourcefile"));

    EXPECT_CALL(mockSrc, close());

    EXPECT_CALL(*fileIo, open("a+b")).WillOnce(::testing::Return(0));

    EXPECT_CALL(*fileIo, close());



    fileIo->transfer(mockSrc);

}



TEST_F(FileIoTest, TransferFromDifferentType_554) {

    EXPECT_CALL(mockSrc, isopen()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockSrc, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockSrc, close());

    EXPECT_CALL(*fileIo, open("w+b")).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockSrc, write(::testing::_)).WillOnce(::testing::Return(10));

    EXPECT_CALL(mockSrc, error()).WillOnce(::testing::Return(0));



    fileIo->transfer(mockSrc);

}



TEST_F(FileIoTest, TransferErrorOnOpen_554) {

    EXPECT_CALL(mockSrc, isopen()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*fileIo, open("a+b")).WillOnce(::testing::Return(-1));



    EXPECT_THROW(fileIo->transfer(mockSrc), Error);

}



TEST_F(FileIoTest, TransferErrorOnWrite_554) {

    EXPECT_CALL(mockSrc, isopen()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockSrc, path()).WillOnce(::testing::Return("sourcefile"));

    EXPECT_CALL(mockSrc, close());

    EXPECT_CALL(*fileIo, open("a+b")).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockSrc, write(::testing::_)).WillOnce(::testing::Return(0));



    EXPECT_THROW(fileIo->transfer(mockSrc), Error);

}



TEST_F(FileIoTest, TransferErrorOnSourceOpen_554) {

    EXPECT_CALL(mockSrc, isopen()).WillOnce(::testing::Return(false));

    EXPECT_CALL(mockSrc, open()).WillOnce(::testing::Return(-1));



    EXPECT_THROW(fileIo->transfer(mockSrc), Error);

}



TEST_F(FileIoTest, TransferPreserveOriginalMode_554) {

    EXPECT_CALL(mockSrc, isopen()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*fileIo, open("a+b")).WillOnce(::testing::Return(0)).WillOnce(::testing::Return(-1));



    EXPECT_THROW(fileIo->transfer(mockSrc), Error);

}



TEST_F(FileIoTest, TransferErrorOnTransfer_554) {

    EXPECT_CALL(mockSrc, isopen()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*fileIo, open("a+b")).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockSrc, write(::testing::_)).WillOnce(::testing::Return(10));

    EXPECT_CALL(mockSrc, error()).WillOnce(::testing::Return(-1));



    EXPECT_THROW(fileIo->transfer(mockSrc), Error);

}
