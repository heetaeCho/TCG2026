#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "bmffimage.cpp"



using namespace Exiv2;

using testing::_;

using testing::InSequence;

using testing::Return;

using testing::SetArgReferee;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo & src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte * buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo & src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string &, path, (), (const override));

    MOCK_METHOD(void, populateFakeData, (), (override));

};



class IsBmffTypeTest_1204 : public ::testing::Test {

protected:

    MockBasicIo mock_io;

};



TEST_F(IsBmffTypeTest_1204, ValidFtypSignature_1204) {

    byte buffer[12] = { 0x00, 0x00, 0x00, 0x20, 'f', 't', 'y', 'p', 0x00, 0x00, 0x00, 0x00 };

    EXPECT_CALL(mock_io, read(_, 12)).WillOnce(SetArgReferee<0>(buffer));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, seek(0, BasicIo::beg));



    bool result = isBmffType(mock_io, true);

    EXPECT_TRUE(result);

}



TEST_F(IsBmffTypeTest_1204, ValidJxlSignature_1204) {

    byte buffer[12] = { 0x00, 0x00, 0x00, 0x20, 'J', 'X', 'L', ' ', 0x00, 0x00, 0x00, 0x00 };

    EXPECT_CALL(mock_io, read(_, 12)).WillOnce(SetArgReferee<0>(buffer));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, seek(0, BasicIo::beg));



    bool result = isBmffType(mock_io, true);

    EXPECT_TRUE(result);

}



TEST_F(IsBmffTypeTest_1204, InvalidSignature_1204) {

    byte buffer[12] = { 0x00, 0x00, 0x00, 0x20, 'f', 't', 'y', 'x', 0x00, 0x00, 0x00, 0x00 };

    EXPECT_CALL(mock_io, read(_, 12)).WillOnce(SetArgReferee<0>(buffer));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, seek(0, BasicIo::beg));



    bool result = isBmffType(mock_io, true);

    EXPECT_FALSE(result);

}



TEST_F(IsBmffTypeTest_1204, ErrorOnRead_1204) {

    byte buffer[12] = { 0x00, 0x00, 0x00, 0x20, 'f', 't', 'y', 'p', 0x00, 0x00, 0x00, 0x00 };

    EXPECT_CALL(mock_io, read(_, 12)).WillOnce(SetArgReferee<0>(buffer));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(1));



    bool result = isBmffType(mock_io, true);

    EXPECT_FALSE(result);

}



TEST_F(IsBmffTypeTest_1204, EofOnRead_1204) {

    byte buffer[12] = { 0x00, 0x00, 0x00, 0x20, 'f', 't', 'y', 'p', 0x00, 0x00, 0x00, 0x00 };

    EXPECT_CALL(mock_io, read(_, 12)).WillOnce(SetArgReferee<0>(buffer));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(true));



    bool result = isBmffType(mock_io, true);

    EXPECT_FALSE(result);

}



TEST_F(IsBmffTypeTest_1204, AdvanceFalse_1204) {

    byte buffer[12] = { 0x00, 0x00, 0x00, 0x20, 'f', 't', 'y', 'p', 0x00, 0x00, 0x00, 0x00 };

    EXPECT_CALL(mock_io, read(_, 12)).WillOnce(SetArgReferee<0>(buffer));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, seek(0, BasicIo::beg));



    bool result = isBmffType(mock_io, false);

    EXPECT_TRUE(result);

}



TEST_F(IsBmffTypeTest_1204, AdvanceTrueNoMatch_1204) {

    byte buffer[12] = { 0x00, 0x00, 0x00, 0x20, 'f', 't', 'y', 'x', 0x00, 0x00, 0x00, 0x00 };

    EXPECT_CALL(mock_io, read(_, 12)).WillOnce(SetArgReferee<0>(buffer));

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, seek(0, BasicIo::beg));



    bool result = isBmffType(mock_io, true);

    EXPECT_FALSE(result);

}
