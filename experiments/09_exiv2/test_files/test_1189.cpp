#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "psdimage.cpp"



using namespace Exiv2;



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

};



class PsdTypeTest : public ::testing::Test {

protected:

    MockBasicIo mockIo;

};



TEST_F(PsdTypeTest_1189, ValidPsdHeader_AdvanceTrue_1189) {

    const int32_t len = 6;

    std::array<byte, len> psdHeader{'8', 'B', 'P', 'S', 0, 1};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::SetArrayArgument<0>(psdHeader.begin(), psdHeader.end())).WillOnce(::testing::Return(len));

    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));

    EXPECT_CALL(mockIo, seek(-len, BasicIo::cur)).Times(0);



    bool result = isPsdType(mockIo, true);

    EXPECT_TRUE(result);

}



TEST_F(PsdTypeTest_1189, ValidPsdHeader_AdvanceFalse_1189) {

    const int32_t len = 6;

    std::array<byte, len> psdHeader{'8', 'B', 'P', 'S', 0, 1};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::SetArrayArgument<0>(psdHeader.begin(), psdHeader.end())).WillOnce(::testing::Return(len));

    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));

    EXPECT_CALL(mockIo, seek(-len, BasicIo::cur)).Times(1);



    bool result = isPsdType(mockIo, false);

    EXPECT_TRUE(result);

}



TEST_F(PsdTypeTest_1189, InvalidPsdHeader_AdvanceTrue_1189) {

    const int32_t len = 6;

    std::array<byte, len> invalidHeader{'N', 'O', 'T', 'P', 'S', 0};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::SetArrayArgument<0>(invalidHeader.begin(), invalidHeader.end())).WillOnce(::testing::Return(len));

    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));

    EXPECT_CALL(mockIo, seek(-len, BasicIo::cur)).Times(1);



    bool result = isPsdType(mockIo, true);

    EXPECT_FALSE(result);

}



TEST_F(PsdTypeTest_1189, IoError_AdvanceTrue_1189) {

    const int32_t len = 6;

    std::array<byte, len> psdHeader{'8', 'B', 'P', 'S', 0, 1};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::SetArrayArgument<0>(psdHeader.begin(), psdHeader.end())).WillOnce(::testing::Return(len));

    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(1));



    bool result = isPsdType(mockIo, true);

    EXPECT_FALSE(result);

}



TEST_F(PsdTypeTest_1189, EofEncountered_AdvanceTrue_1189) {

    const int32_t len = 6;

    std::array<byte, len> psdHeader{'8', 'B', 'P', 'S', 0, 1};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::SetArrayArgument<0>(psdHeader.begin(), psdHeader.end())).WillOnce(::testing::Return(len));

    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(true));



    bool result = isPsdType(mockIo, true);

    EXPECT_FALSE(result);

}



TEST_F(PsdTypeTest_1189, PartialRead_AdvanceTrue_1189) {

    const int32_t len = 6;

    std::array<byte, len> partialHeader{'8', 'B', 'P', 'S'};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::SetArrayArgument<0>(partialHeader.begin(), partialHeader.end())).WillOnce(::testing::Return(4));

    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(true));



    bool result = isPsdType(mockIo, true);

    EXPECT_FALSE(result);

}
