#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "webpimage.cpp"

#include "basicio.hpp"



using namespace Exiv2;

using ::testing::Return;

using ::testing::_;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, readOrThrow, (void* buf, long n, ErrorCode error), (override));

    MOCK_METHOD(void, seek, (long offset, Position pos), (override));

};



class WebPTypeTest_73 : public ::testing::Test {

protected:

    MockBasicIo mockIo;

};



TEST_F(WebPTypeTest_73, IsWebPType_ReturnsFalseForSmallInput_73) {

    EXPECT_CALL(mockIo, size()).WillOnce(Return(10));

    EXPECT_FALSE(isWebPType(mockIo, true));

}



TEST_F(WebPTypeTest_73, IsWebPType_ReturnsTrueForValidWebPMarker_73) {

    std::array<byte, 4> riffData{'R', 'I', 'F', 'F'};

    std::array<byte, 4> webpData{'W', 'E', 'B', 'P'};

    std::array<byte, 4> data;



    EXPECT_CALL(mockIo, size()).WillOnce(Return(12));

    EXPECT_CALL(mockIo, readOrThrow(riffData.data(), 4, Exiv2::ErrorCode::kerCorruptedMetadata)).Times(1);

    EXPECT_CALL(mockIo, readOrThrow(data.data(), 4, Exiv2::ErrorCode::kerCorruptedMetadata)).Times(1);

    EXPECT_CALL(mockIo, readOrThrow(webpData.data(), 4, Exiv2::ErrorCode::kerCorruptedMetadata)).Times(1);

    EXPECT_CALL(mockIo, seek(-12, BasicIo::cur)).Times(1);



    EXPECT_TRUE(isWebPType(mockIo, true));

}



TEST_F(WebPTypeTest_73, IsWebPType_ReturnsFalseForInvalidRiffMarker_73) {

    std::array<byte, 4> riffData{'N', 'O', 'T', 'R'};

    std::array<byte, 4> webpData{'W', 'E', 'B', 'P'};

    std::array<byte, 4> data;



    EXPECT_CALL(mockIo, size()).WillOnce(Return(12));

    EXPECT_CALL(mockIo, readOrThrow(riffData.data(), 4, Exiv2::ErrorCode::kerCorruptedMetadata)).Times(1);

    EXPECT_CALL(mockIo, readOrThrow(data.data(), 4, Exiv2::ErrorCode::kerCorruptedMetadata)).Times(1);

    EXPECT_CALL(mockIo, readOrThrow(webpData.data(), 4, Exiv2::ErrorCode::kerCorruptedMetadata)).Times(1);

    EXPECT_CALL(mockIo, seek(-12, BasicIo::cur)).Times(1);



    EXPECT_FALSE(isWebPType(mockIo, true));

}



TEST_F(WebPTypeTest_73, IsWebPType_ReturnsFalseForInvalidWebPMarker_73) {

    std::array<byte, 4> riffData{'R', 'I', 'F', 'F'};

    std::array<byte, 4> webpData{'N', 'O', 'T', 'W'};

    std::array<byte, 4> data;



    EXPECT_CALL(mockIo, size()).WillOnce(Return(12));

    EXPECT_CALL(mockIo, readOrThrow(riffData.data(), 4, Exiv2::ErrorCode::kerCorruptedMetadata)).Times(1);

    EXPECT_CALL(mockIo, readOrThrow(data.data(), 4, Exiv2::ErrorCode::kerCorruptedMetadata)).Times(1);

    EXPECT_CALL(mockIo, readOrThrow(webpData.data(), 4, Exiv2::ErrorCode::kerCorruptedMetadata)).Times(1);

    EXPECT_CALL(mockIo, seek(-12, BasicIo::cur)).Times(1);



    EXPECT_FALSE(isWebPType(mockIo, true));

}



TEST_F(WebPTypeTest_73, IsWebPType_SeekIsCalledAfterReading_73) {

    std::array<byte, 4> riffData{'R', 'I', 'F', 'F'};

    std::array<byte, 4> webpData{'W', 'E', 'B', 'P'};

    std::array<byte, 4> data;



    EXPECT_CALL(mockIo, size()).WillOnce(Return(12));

    EXPECT_CALL(mockIo, readOrThrow(riffData.data(), 4, Exiv2::ErrorCode::kerCorruptedMetadata)).Times(1);

    EXPECT_CALL(mockIo, readOrThrow(data.data(), 4, Exiv2::ErrorCode::kerCorruptedMetadata)).Times(1);

    EXPECT_CALL(mockIo, readOrThrow(webpData.data(), 4, Exiv2::ErrorCode::kerCorruptedMetadata)).Times(1);

    EXPECT_CALL(mockIo, seek(-12, BasicIo::cur)).Times(1);



    isWebPType(mockIo, true);

}
