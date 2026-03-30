#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(bool, isopen, (), (const, override));

};



class FileIoTest : public ::testing::Test {

protected:

    MockBasicIo mockSrc;

    std::string testPath = "test_file";

    FileIo fileIo{testPath};

};



TEST_F(FileIoTest_553, WriteReturnsZeroWhenSameObjectPassed_553) {

    EXPECT_EQ(fileIo.write(fileIo), 0U);

}



TEST_F(FileIoTest_553, WriteReturnsZeroWhenSourceNotOpen_553) {

    EXPECT_CALL(mockSrc, isopen()).WillOnce(::testing::Return(false));

    EXPECT_EQ(fileIo.write(mockSrc), 0U);

}



TEST_F(FileIoTest_553, WriteReturnsZeroWhenSwitchModeFails_553) {

    EXPECT_CALL(mockSrc, isopen()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*reinterpret_cast<FileIo::Impl*>(fileIo.p_.get()), switchMode(FileIo::Impl::opWrite)).WillOnce(::testing::Return(1));

    EXPECT_EQ(fileIo.write(mockSrc), 0U);

}



TEST_F(FileIoTest_553, WriteTransfersDataCorrectly_553) {

    byte buffer[4096] = {1};

    size_t bytesRead = 4096;

    size_t bytesWritten = 4096;



    EXPECT_CALL(mockSrc, isopen()).WillRepeatedly(::testing::Return(true));

    EXPECT_CALL(*reinterpret_cast<FileIo::Impl*>(fileIo.p_.get()), switchMode(FileIo::Impl::opWrite)).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockSrc, read(buffer, 4096))

        .WillOnce(::testing::DoAll(

            ::testing::SetArrayArgument<0>(buffer, buffer + bytesRead),

            ::testing::Return(bytesRead)))

        .WillOnce(::testing::Return(0U));



    EXPECT_CALL(*reinterpret_cast<FileIo::Impl*>(fileIo.p_.get()), fp_)

        .WillRepeatedly(::testing::Return(reinterpret_cast<FILE*>(stdout)));



    EXPECT_CALL(mockSrc, seek(::testing::_ , BasicIo::cur)).Times(0);



    EXPECT_EQ(fileIo.write(mockSrc), bytesWritten);

}



TEST_F(FileIoTest_553, WriteHandlesPartialWriteCorrectly_553) {

    byte buffer[4096] = {1};

    size_t bytesRead = 4096;

    size_t partialBytesWritten = 2048;



    EXPECT_CALL(mockSrc, isopen()).WillRepeatedly(::testing::Return(true));

    EXPECT_CALL(*reinterpret_cast<FileIo::Impl*>(fileIo.p_.get()), switchMode(FileIo::Impl::opWrite)).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockSrc, read(buffer, 4096))

        .WillOnce(::testing::DoAll(

            ::testing::SetArrayArgument<0>(buffer, buffer + bytesRead),

            ::testing::Return(bytesRead)));



    EXPECT_CALL(*reinterpret_cast<FileIo::Impl*>(fileIo.p_.get()), fp_)

        .WillRepeatedly(::testing::Return(reinterpret_cast<FILE*>(stdout)));



    EXPECT_CALL(mockSrc, seek(partialBytesWritten - bytesRead, BasicIo::cur)).Times(1);



    EXPECT_CALL(*reinterpret_cast<FileIo::Impl*>(fileIo.p_.get()), write(_, _))

        .WillOnce(::testing::Return(partialBytesWritten));



    EXPECT_EQ(fileIo.write(mockSrc), partialBytesWritten);

}



TEST_F(FileIoTest_553, WriteHandlesEmptySourceCorrectly_553) {

    byte buffer[4096] = {1};

    size_t bytesRead = 0;



    EXPECT_CALL(mockSrc, isopen()).WillRepeatedly(::testing::Return(true));

    EXPECT_CALL(*reinterpret_cast<FileIo::Impl*>(fileIo.p_.get()), switchMode(FileIo::Impl::opWrite)).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockSrc, read(buffer, 4096))

        .WillOnce(::testing::DoAll(

            ::testing::SetArrayArgument<0>(buffer, buffer + bytesRead),

            ::testing::Return(bytesRead)));



    EXPECT_EQ(fileIo.write(mockSrc), 0U);

}
