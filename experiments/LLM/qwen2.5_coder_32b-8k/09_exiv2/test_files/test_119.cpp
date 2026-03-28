#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(size_t, tell, (), (const, override));

    MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));

};



class ReadStringWcharTagTest_119 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io;

    const size_t buffer_size = 1024;



    void SetUp() override {

        mock_io = std::make_unique<MockBasicIo>();

    }



    std::string callReadStringWcharTag(size_t length) {

        return readStringWcharTag(BasicIo::UniquePtr(mock_io.release()), length);

    }

};



TEST_F(ReadStringWcharTagTest_119, NormalOperation_119) {

    const size_t length = 8;

    byte buffer[length] = {0x48, 0x00, 0x65, 0x00, 0x6C, 0x00, 0x6C, 0x00}; // "Hell" in UCS-2LE



    EXPECT_CALL(*mock_io, size()).WillRepeatedly(Return(length + 3));

    EXPECT_CALL(*mock_io, tell()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, readOrThrow(_, length, ErrorCode::kerFailedToReadImageData))

        .WillOnce([buffer](byte* buf, size_t rcount, ErrorCode) {

            std::memcpy(buf, buffer, rcount);

        });



    std::string result = callReadStringWcharTag(length);

    EXPECT_EQ(result, "Hell");

}



TEST_F(ReadStringWcharTagTest_119, BoundaryCondition_ZeroLength_119) {

    const size_t length = 0;



    EXPECT_CALL(*mock_io, size()).WillRepeatedly(Return(3));

    EXPECT_CALL(*mock_io, tell()).WillOnce(Return(0));



    std::string result = callReadStringWcharTag(length);

    EXPECT_EQ(result, "");

}



TEST_F(ReadStringWcharTagTest_119, BoundaryCondition_MaxLength_119) {

    const size_t length = 1024;

    byte buffer[length] = {0};



    EXPECT_CALL(*mock_io, size()).WillRepeatedly(Return(length + 3));

    EXPECT_CALL(*mock_io, tell()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, readOrThrow(_, length, ErrorCode::kerFailedToReadImageData))

        .WillOnce([buffer](byte* buf, size_t rcount, ErrorCode) {

            std::memcpy(buf, buffer, rcount);

        });



    std::string result = callReadStringWcharTag(length);

    EXPECT_EQ(result, "");

}



TEST_F(ReadStringWcharTagTest_119, ErrorCondition_LengthExceedsSize_119) {

    const size_t length = 8;



    EXPECT_CALL(*mock_io, size()).WillRepeatedly(Return(length - 1));

    EXPECT_CALL(*mock_io, tell()).WillOnce(Return(0));



    EXPECT_THROW(callReadStringWcharTag(length), Exiv2::Error);

}



TEST_F(ReadStringWcharTagTest_119, ErrorCondition_ReadThrows_119) {

    const size_t length = 8;



    EXPECT_CALL(*mock_io, size()).WillRepeatedly(Return(length + 3));

    EXPECT_CALL(*mock_io, tell()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, readOrThrow(_, length, ErrorCode::kerFailedToReadImageData))

        .WillOnce([](byte*, size_t, ErrorCode) {

            throw Exiv2::Error(Exiv2::ErrorCode::kerFailedToReadImageData);

        });



    EXPECT_THROW(callReadStringWcharTag(length), Exiv2::Error);

}



TEST_F(ReadStringWcharTagTest_119, OddLengthBuffer_119) {

    const size_t length = 7;

    byte buffer[length] = {0x48, 0x00, 0x65, 0x00, 0x6C, 0x00, 0x6C}; // "Hell" in UCS-2LE with odd length



    EXPECT_CALL(*mock_io, size()).WillRepeatedly(Return(length + 3));

    EXPECT_CALL(*mock_io, tell()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, readOrThrow(_, length, ErrorCode::kerFailedToReadImageData))

        .WillOnce([buffer](byte* buf, size_t rcount, ErrorCode) {

            std::memcpy(buf, buffer, rcount);

        });



    std::string result = callReadStringWcharTag(length);

    EXPECT_EQ(result, "Hell");

}
