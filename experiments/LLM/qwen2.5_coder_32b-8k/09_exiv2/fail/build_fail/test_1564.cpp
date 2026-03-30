#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/asfvideo.hpp"

#include "exiv2/basicio.hpp"

#include "exiv2/types.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;

using ::testing::Throw;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

};



class AsfVideoTest_1564 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io_;

    std::unique_ptr<AsfVideo> asf_video_;



    void SetUp() override {

        mock_io_ = std::make_unique<MockBasicIo>();

        asf_video_ = std::make_unique<AsfVideo>(std::move(mock_io_));

    }

};



TEST_F(AsfVideoTest_1564, DecodeHeader_ReadsNumberOfHeadersCorrectly_1564) {

    byte data[DWORD] = {0x02, 0x00, 0x00, 0x00}; // little-endian representation of 2

    EXPECT_CALL(*mock_io_, readOrThrow(_, DWORD, ErrorCode::kerCorruptedMetadata)).WillOnce(testing::SetArrayArgument<0>(data, data + DWORD));

    EXPECT_CALL(*mock_io_, seekOrThrow(2, BasicIo::beg, ErrorCode::kerFailedToReadImageData));



    // Mock decodeBlock to be called exactly 2 times

    EXPECT_CALL(*mock_io_, read(_, _)).Times(2);



    asf_video_->decodeHeader();

}



TEST_F(AsfVideoTest_1564, DecodeHeader_SkipsTwoReservedTags_1564) {

    byte data[DWORD] = {0x01, 0x00, 0x00, 0x00}; // little-endian representation of 1

    EXPECT_CALL(*mock_io_, readOrThrow(_, DWORD, ErrorCode::kerCorruptedMetadata)).WillOnce(testing::SetArrayArgument<0>(data, data + DWORD));

    EXPECT_CALL(*mock_io_, seekOrThrow(2, BasicIo::beg, ErrorCode::kerFailedToReadImageData));



    // Mock decodeBlock to be called exactly 1 time

    EXPECT_CALL(*mock_io_, read(_, _)).Times(1);



    asf_video_->decodeHeader();

}



TEST_F(AsfVideoTest_1564, DecodeHeader_MaxNumberOfHeaders_1564) {

    byte data[DWORD] = {0xFF, 0xFF, 0xFF, 0x7F}; // little-endian representation of max uint32_t

    EXPECT_CALL(*mock_io_, readOrThrow(_, DWORD, ErrorCode::kerCorruptedMetadata)).WillOnce(testing::SetArrayArgument<0>(data, data + DWORD));

    EXPECT_THROW(asf_video_->decodeHeader(), Error);

}



TEST_F(AsfVideoTest_1564, DecodeHeader_ReadFails_1564) {

    EXPECT_CALL(*mock_io_, readOrThrow(_, DWORD, ErrorCode::kerCorruptedMetadata)).WillOnce(Throw(Error(ErrorCode::kerFailedToReadImageData)));



    EXPECT_THROW(asf_video_->decodeHeader(), Error);

}



TEST_F(AsfVideoTest_1564, DecodeHeader_SeekFails_1564) {

    byte data[DWORD] = {0x01, 0x00, 0x00, 0x00}; // little-endian representation of 1

    EXPECT_CALL(*mock_io_, readOrThrow(_, DWORD, ErrorCode::kerCorruptedMetadata)).WillOnce(testing::SetArrayArgument<0>(data, data + DWORD));

    EXPECT_CALL(*mock_io_, seekOrThrow(2, BasicIo::beg, ErrorCode::kerFailedToReadImageData)).WillOnce(Throw(Error(ErrorCode::kerFailedToReadImageData)));



    EXPECT_THROW(asf_video_->decodeHeader(), Error);

}
