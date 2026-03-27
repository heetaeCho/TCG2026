#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/riffvideo.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(size_t, tell, (), (const, override));

    MOCK_METHOD(int64_t, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));

};



class RiffVideoTest_2152 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io;



    void SetUp() override {

        mock_io = std::make_unique<MockBasicIo>();

    }

};



TEST_F(RiffVideoTest_2152, ConstructorReadsCorrectIdAndSize_2152) {

    const std::string expected_id = "EXMP";

    uint64_t expected_size = 1024;

    byte data[] = {'E', 'X', 'M', 'P', 0x00, 0x04, 0x00, 0x00}; // Little-endian for size



    EXPECT_CALL(*mock_io, tell()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mock_io, size()).WillOnce(::testing::Return(12));

    EXPECT_CALL(*mock_io, readOrThrow(::testing::_ , DWORD, ErrorCode::kerInputDataReadFailed))

        .WillOnce([data](byte* buf, size_t rcount, ErrorCode) {

            memcpy(buf, data, rcount);

        });



    RiffVideo::HeaderReader header_reader(mock_io);



    EXPECT_EQ(header_reader.getId(), expected_id);

    EXPECT_EQ(header_reader.getSize(), expected_size);

}



TEST_F(RiffVideoTest_2152, ConstructorThrowsOnInsufficientData_2152) {

    EXPECT_CALL(*mock_io, tell()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mock_io, size()).WillOnce(::testing::Return(7));



    EXPECT_THROW(RiffVideo::HeaderReader(mock_io), Error);

}



TEST_F(RiffVideoTest_2152, ConstructorThrowsOnNegativeSeek_2152) {

    EXPECT_CALL(*mock_io, tell()).WillOnce(::testing::Return(-1));

    EXPECT_CALL(*mock_io, size()).WillOnce(::testing::Return(12));



    EXPECT_THROW(RiffVideo::HeaderReader(mock_io), Error);

}



TEST_F(RiffVideoTest_2152, ConstructorThrowsOnInsufficientDataForSize_2152) {

    const std::string expected_id = "EXMP";

    byte data[] = {'E', 'X', 'M', 'P'};



    EXPECT_CALL(*mock_io, tell()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mock_io, size()).WillOnce(::testing::Return(4));

    EXPECT_CALL(*mock_io, readOrThrow(::testing::_ , DWORD, ErrorCode::kerInputDataReadFailed))

        .WillOnce([data](byte* buf, size_t rcount, ErrorCode) {

            memcpy(buf, data, rcount);

        });



    EXPECT_THROW(RiffVideo::HeaderReader(mock_io), Error);

}



TEST_F(RiffVideoTest_2152, ConstructorHandlesBoundarySizeCondition_2152) {

    const std::string expected_id = "EXMP";

    uint64_t expected_size = 0;

    byte data[] = {'E', 'X', 'M', 'P', 0x00, 0x00, 0x00, 0x00}; // Little-endian for size



    EXPECT_CALL(*mock_io, tell()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mock_io, size()).WillOnce(::testing::Return(8));

    EXPECT_CALL(*mock_io, readOrThrow(::testing::_ , DWORD, ErrorCode::kerInputDataReadFailed))

        .WillOnce([data](byte* buf, size_t rcount, ErrorCode) {

            memcpy(buf, data, rcount);

        });



    RiffVideo::HeaderReader header_reader(mock_io);



    EXPECT_EQ(header_reader.getId(), expected_id);

    EXPECT_EQ(header_reader.getSize(), expected_size);

}
