#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(bool, isopen, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

};



class RemoteIoTest : public ::testing::Test {

protected:

    MockBasicIo mockSrc;

    RemoteIo remoteIo;



    void SetUp() override {

        // Common setup code if needed

    }

};



TEST_F(RemoteIoTest_603, WriteReturnsZeroIfSourceNotOpen_603) {

    EXPECT_CALL(mockSrc, isopen()).WillOnce(Return(false));

    EXPECT_EQ(remoteIo.write(mockSrc), 0);

}



TEST_F(RemoteIoTest_603, WriteHandlesBoundaryConditions_603) {

    byte buffer[1] = {0};

    EXPECT_CALL(mockSrc, isopen()).WillOnce(Return(true));

    EXPECT_CALL(mockSrc, size()).WillOnce(Return(1));

    EXPECT_CALL(mockSrc, seek(0, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(mockSrc, read(buffer, 1)).WillOnce(Return(1));

    EXPECT_EQ(remoteIo.write(mockSrc), 1);

}



TEST_F(RemoteIoTest_603, WriteCallsSeekAndReadCorrectly_603) {

    byte buffer[2] = {0};

    EXPECT_CALL(mockSrc, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(mockSrc, size()).WillOnce(Return(2));

    EXPECT_CALL(mockSrc, seek(0, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(mockSrc, read(buffer, 1)).Times(2).WillRepeatedly(Return(1));

    EXPECT_EQ(remoteIo.write(mockSrc), 2);

}



TEST_F(RemoteIoTest_603, WriteHandlesNoDifferenceCase_603) {

    byte buffer[2] = {0, 0};

    EXPECT_CALL(mockSrc, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(mockSrc, size()).WillOnce(Return(2));

    EXPECT_CALL(mockSrc, seek(0, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(mockSrc, read(buffer, 2)).WillOnce(Return(2));

    EXPECT_EQ(remoteIo.write(mockSrc), 2);

}



TEST_F(RemoteIoTest_603, WriteHandlesPartialDifferenceCase_603) {

    byte buffer1[1] = {1};

    byte buffer2[1] = {0};

    EXPECT_CALL(mockSrc, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(mockSrc, size()).WillOnce(Return(2));

    EXPECT_CALL(mockSrc, seek(0, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(mockSrc, read(buffer1, 1)).WillOnce(Return(1));

    EXPECT_CALL(mockSrc, seek(-1 * (1 + 0), BasicIo::end)).WillOnce(Return(0));

    EXPECT_CALL(mockSrc, read(buffer2, 1)).WillOnce(Return(1));

    EXPECT_EQ(remoteIo.write(mockSrc), 2);

}



TEST_F(RemoteIoTest_603, WriteHandlesFullDifferenceCase_603) {

    byte buffer[2] = {1, 2};

    EXPECT_CALL(mockSrc, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(mockSrc, size()).WillOnce(Return(2));

    EXPECT_CALL(mockSrc, seek(0, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(mockSrc, read(buffer, 1)).WillOnce(Return(1));

    EXPECT_CALL(mockSrc, seek(-1 * (1 + 0), BasicIo::end)).WillOnce(Return(0));

    EXPECT_CALL(mockSrc, read(buffer + 1, 1)).WillOnce(Return(1));

    EXPECT_EQ(remoteIo.write(mockSrc), 2);

}



TEST_F(RemoteIoTest_603, WriteHandlesSeekFailures_603) {

    byte buffer[1] = {1};

    EXPECT_CALL(mockSrc, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(mockSrc, size()).WillOnce(Return(2));

    EXPECT_CALL(mockSrc, seek(0, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(mockSrc, read(buffer, 1)).WillOnce(Return(1));

    EXPECT_CALL(mockSrc, seek(-1 * (1 + 0), BasicIo::end)).WillOnce(Return(-1));

    EXPECT_EQ(remoteIo.write(mockSrc), 2);

}
