#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "jpgimage.cpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class BasicIoMock : public BasicIo {

public:

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(int, error, (), (const override));

    MOCK_METHOD(bool, eof, (), (const override));

};



class JpgImageTest_1224 : public ::testing::Test {

protected:

    BasicIoMock ioMock;

};



TEST_F(JpgImageTest_1224, ValidJpegHeader_1224) {

    byte buffer[] = {0xff, static_cast<byte>(soi_)};

    EXPECT_CALL(ioMock, read(_, 2)).WillOnce(::testing::DoAll(::testing::SetArgReferee<0>(buffer), Return(2)));

    EXPECT_CALL(ioMock, seek(-2, BasicIo::cur)).Times(1);

    EXPECT_CALL(ioMock, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(ioMock, eof()).WillOnce(Return(false));



    bool result = isJpegType(ioMock, true);



    EXPECT_TRUE(result);

}



TEST_F(JpgImageTest_1224, InvalidFirstByte_1224) {

    byte buffer[] = {0xfe, static_cast<byte>(soi_)};

    EXPECT_CALL(ioMock, read(_, 2)).WillOnce(::testing::DoAll(::testing::SetArgReferee<0>(buffer), Return(2)));

    EXPECT_CALL(ioMock, seek(-2, BasicIo::cur)).Times(1);

    EXPECT_CALL(ioMock, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(ioMock, eof()).WillOnce(Return(false));



    bool result = isJpegType(ioMock, true);



    EXPECT_FALSE(result);

}



TEST_F(JpgImageTest_1224, InvalidSecondByte_1224) {

    byte buffer[] = {0xff, 0xe0};

    EXPECT_CALL(ioMock, read(_, 2)).WillOnce(::testing::DoAll(::testing::SetArgReferee<0>(buffer), Return(2)));

    EXPECT_CALL(ioMock, seek(-2, BasicIo::cur)).Times(1);

    EXPECT_CALL(ioMock, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(ioMock, eof()).WillOnce(Return(false));



    bool result = isJpegType(ioMock, true);



    EXPECT_FALSE(result);

}



TEST_F(JpgImageTest_1224, ReadError_1224) {

    byte buffer[] = {0xff, static_cast<byte>(soi_)};

    EXPECT_CALL(ioMock, read(_, 2)).WillOnce(Return(1));

    EXPECT_CALL(ioMock, error()).WillRepeatedly(Return(1));



    bool result = isJpegType(ioMock, true);



    EXPECT_FALSE(result);

}



TEST_F(JpgImageTest_1224, EndOfFile_1224) {

    byte buffer[] = {0xff, static_cast<byte>(soi_)};

    EXPECT_CALL(ioMock, read(_, 2)).WillOnce(Return(1));

    EXPECT_CALL(ioMock, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(ioMock, eof()).WillOnce(Return(true));



    bool result = isJpegType(ioMock, true);



    EXPECT_FALSE(result);

}



TEST_F(JpgImageTest_1224, DoNotAdvance_1224) {

    byte buffer[] = {0xff, static_cast<byte>(soi_)};

    EXPECT_CALL(ioMock, read(_, 2)).WillOnce(::testing::DoAll(::testing::SetArgReferee<0>(buffer), Return(2)));

    EXPECT_CALL(ioMock, seek(-2, BasicIo::cur)).Times(1);

    EXPECT_CALL(ioMock, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(ioMock, eof()).WillOnce(Return(false));



    bool result = isJpegType(ioMock, false);



    EXPECT_TRUE(result);

}



TEST_F(JpgImageTest_1224, AdvanceOnFalseResult_1224) {

    byte buffer[] = {0xff, 0xe0};

    EXPECT_CALL(ioMock, read(_, 2)).WillOnce(::testing::DoAll(::testing::SetArgReferee<0>(buffer), Return(2)));

    EXPECT_CALL(ioMock, seek(-2, BasicIo::cur)).Times(1);

    EXPECT_CALL(ioMock, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(ioMock, eof()).WillOnce(Return(false));



    bool result = isJpegType(ioMock, true);



    EXPECT_FALSE(result);

}



TEST_F(JpgImageTest_1224, AdvanceOnTrueResult_1224) {

    byte buffer[] = {0xff, static_cast<byte>(soi_)};

    EXPECT_CALL(ioMock, read(_, 2)).WillOnce(::testing::DoAll(::testing::SetArgReferee<0>(buffer), Return(2)));

    EXPECT_CALL(ioMock, seek(-2, BasicIo::cur)).Times(1);

    EXPECT_CALL(ioMock, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(ioMock, eof()).WillOnce(Return(false));



    bool result = isJpegType(ioMock, true);



    EXPECT_TRUE(result);

}
