#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "TestProjects/exiv2/src/orfimage.cpp"



using namespace Exiv2;

using namespace testing;



class BasicIoMock : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo& src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo& src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const, override));

    MOCK_METHOD(const size_t, size, (), (const, override));

    MOCK_METHOD(const bool, isopen, (), (const, override));

    MOCK_METHOD(const int, error, (), (const, override));

    MOCK_METHOD(const bool, eof, (), (const, override));

    MOCK_METHOD(const std::string&, path, (), (const, override));

};



class IsOrfTypeTest : public Test {

protected:

    NiceMock<BasicIoMock> mock_io;

};



TEST_F(IsOrfTypeTest, ValidOrfHeader_1556) {

    const byte valid_orf_header[] = {0x49, 0x49, 0x2a, 0x00, 0x08, 0x00, 0x00, 0x00};

    EXPECT_CALL(mock_io, read(NotNull(), Eq(8))).WillOnce(DoAll(SetArrayElementsArgument<0>(valid_orf_header), Return(8)));

    EXPECT_TRUE(isOrfType(mock_io, true));

}



TEST_F(IsOrfTypeTest, InvalidOrfHeader_1556) {

    const byte invalid_orf_header[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    EXPECT_CALL(mock_io, read(NotNull(), Eq(8))).WillOnce(DoAll(SetArrayElementsArgument<0>(invalid_orf_header), Return(8)));

    EXPECT_FALSE(isOrfType(mock_io, true));

}



TEST_F(IsOrfTypeTest, ReadError_1556) {

    EXPECT_CALL(mock_io, read(NotNull(), Eq(8))).WillOnce(Return(0)); // Simulate a read error

    EXPECT_CALL(mock_io, error()).WillOnce(Return(-1)); // Indicate an error occurred

    EXPECT_FALSE(isOrfType(mock_io, true));

}



TEST_F(IsOrfTypeTest, EndOfFile_1556) {

    EXPECT_CALL(mock_io, read(NotNull(), Eq(8))).WillOnce(Return(0)); // Simulate a read error

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(true)); // Indicate end of file

    EXPECT_FALSE(isOrfType(mock_io, true));

}



TEST_F(IsOrfTypeTest, AdvanceFalseValidHeader_1556) {

    const byte valid_orf_header[] = {0x49, 0x49, 0x2a, 0x00, 0x08, 0x00, 0x00, 0x00};

    EXPECT_CALL(mock_io, read(NotNull(), Eq(8))).WillOnce(DoAll(SetArrayElementsArgument<0>(valid_orf_header), Return(8)));

    EXPECT_CALL(mock_io, seek(-8, BasicIo::cur)).Times(1);

    EXPECT_TRUE(isOrfType(mock_io, false));

}



TEST_F(IsOrfTypeTest, AdvanceFalseInvalidHeader_1556) {

    const byte invalid_orf_header[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    EXPECT_CALL(mock_io, read(NotNull(), Eq(8))).WillOnce(DoAll(SetArrayElementsArgument<0>(invalid_orf_header), Return(8)));

    EXPECT_FALSE(isOrfType(mock_io, false));

}



TEST_F(IsOrfTypeTest, AdvanceFalseReadError_1556) {

    EXPECT_CALL(mock_io, read(NotNull(), Eq(8))).WillOnce(Return(0)); // Simulate a read error

    EXPECT_CALL(mock_io, error()).WillOnce(Return(-1)); // Indicate an error occurred

    EXPECT_FALSE(isOrfType(mock_io, false));

}



TEST_F(IsOrfTypeTest, AdvanceFalseEndOfFile_1556) {

    EXPECT_CALL(mock_io, read(NotNull(), Eq(8))).WillOnce(Return(0)); // Simulate a read error

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(true)); // Indicate end of file

    EXPECT_FALSE(isOrfType(mock_io, false));

}
