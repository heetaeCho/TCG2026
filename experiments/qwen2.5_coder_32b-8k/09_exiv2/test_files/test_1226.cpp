#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "exiv2/jpgimage.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;

using ::testing::Eq;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte * buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo & src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string &, path, (), (const override));

};



class ExvImageTest_1226 : public ::testing::Test {

protected:

    MockBasicIo mockBasicIo;

    ExvImage exvImage{std::make_unique<MockBasicIo>(mockBasicIo), false};

};



TEST_F(ExvImageTest_1226, WriteHeader_Success_1226) {

    std::array<byte, 7> expectedData = {0xff, 0x01, 'E', 'x', 'i', 'v', 0};

    EXPECT_CALL(mockBasicIo, write(Eq(expectedData.data()), Eq(7))).WillOnce(Return(7));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(Return(0));



    int result = exvImage.writeHeader(mockBasicIo);



    EXPECT_EQ(result, 0);

}



TEST_F(ExvImageTest_1226, WriteHeader_WriteFails_1226) {

    std::array<byte, 7> expectedData = {0xff, 0x01, 'E', 'x', 'i', 'v', 0};

    EXPECT_CALL(mockBasicIo, write(Eq(expectedData.data()), Eq(7))).WillOnce(Return(3));



    int result = exvImage.writeHeader(mockBasicIo);



    EXPECT_EQ(result, 4);

}



TEST_F(ExvImageTest_1226, WriteHeader_ErrorAfterWrite_1226) {

    std::array<byte, 7> expectedData = {0xff, 0x01, 'E', 'x', 'i', 'v', 0};

    EXPECT_CALL(mockBasicIo, write(Eq(expectedData.data()), Eq(7))).WillOnce(Return(7));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(Return(-1));



    int result = exvImage.writeHeader(mockBasicIo);



    EXPECT_EQ(result, 4);

}
