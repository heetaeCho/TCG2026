#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "TestProjects/exiv2/src/jpgimage.cpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;

using ::testing::SetArrayArgument;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

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

};



class IsExvTypeTest : public ::testing::Test {

protected:

    MockBasicIo mock_io;

};



TEST_F(IsExvTypeTest_NormalOperation_1229, ValidExiv2HeaderAdvancesPosition_1229) {

    byte data[] = {0xff, 0x01, 'E', 'x', 'i', 'v', 0};

    EXPECT_CALL(mock_io, read(_, 7)).WillOnce(SetArrayArgument<0>(data, data + sizeof(data)));

    EXPECT_CALL(mock_io, seek(-7, BasicIo::cur)).Times(0);



    EXPECT_TRUE(isExvType(mock_io, true));

}



TEST_F(IsExvTypeTest_NormalOperation_1229, ValidExiv2HeaderDoesNotAdvancePosition_1229) {

    byte data[] = {0xff, 0x01, 'E', 'x', 'i', 'v', 0};

    EXPECT_CALL(mock_io, read(_, 7)).WillOnce(SetArrayArgument<0>(data, data + sizeof(data)));

    EXPECT_CALL(mock_io, seek(-7, BasicIo::cur));



    EXPECT_TRUE(isExvType(mock_io, false));

}



TEST_F(IsExvTypeTest_BoundaryConditions_1229, EmptyBufferReturnsFalse_1229) {

    EXPECT_CALL(mock_io, read(_, 7)).WillOnce(Return(0));

    EXPECT_CALL(mock_io, seek(-7, BasicIo::cur));



    EXPECT_FALSE(isExvType(mock_io, true));

}



TEST_F(IsExvTypeTest_BoundaryConditions_1229, IncompleteHeaderReturnsFalse_1229) {

    byte data[] = {0xff, 0x01};

    EXPECT_CALL(mock_io, read(_, 7)).WillOnce(SetArrayArgument<0>(data, data + sizeof(data)));

    EXPECT_CALL(mock_io, seek(-7, BasicIo::cur));



    EXPECT_FALSE(isExvType(mock_io, true));

}



TEST_F(IsExvTypeTest_ExceptionalCases_1229, IoErrorReturnsFalseAndDoesNotAdvancePosition_1229) {

    byte data[] = {0xff, 0x01};

    EXPECT_CALL(mock_io, read(_, 7)).WillOnce(SetArrayArgument<0>(data, data + sizeof(data)));

    EXPECT_CALL(mock_io, error()).WillOnce(Return(1));

    EXPECT_CALL(mock_io, seek(-7, BasicIo::cur));



    EXPECT_FALSE(isExvType(mock_io, true));

}



TEST_F(IsExvTypeTest_ExceptionalCases_1229, EofReturnsFalseAndDoesNotAdvancePosition_1229) {

    byte data[] = {0xff, 0x01};

    EXPECT_CALL(mock_io, read(_, 7)).WillOnce(SetArrayArgument<0>(data, data + sizeof(data)));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(true));

    EXPECT_CALL(mock_io, seek(-7, BasicIo::cur));



    EXPECT_FALSE(isExvType(mock_io, true));

}



TEST_F(IsExvTypeTest_ExceptionalCases_1229, InvalidHeaderReturnsFalseAndAdvancesPosition_1229) {

    byte data[] = {0xff, 0x02, 'E', 'x', 'i', 'v', 0};

    EXPECT_CALL(mock_io, read(_, 7)).WillOnce(SetArrayArgument<0>(data, data + sizeof(data)));

    EXPECT_CALL(mock_io, seek(-7, BasicIo::cur));



    EXPECT_FALSE(isExvType(mock_io, true));

}
