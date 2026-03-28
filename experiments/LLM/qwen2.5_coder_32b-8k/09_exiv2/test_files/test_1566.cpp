#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "asfvideo.hpp"

#include "basicio.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

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

    MOCK_METHOD(size_t, tell, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(bool, isopen, (), (const, override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

    MOCK_METHOD(const std::string&, path, (), (const, override));

    MOCK_METHOD(void, populateFakeData, (), (override));

};



class AsfVideoTest_1566 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_io = std::make_unique<MockBasicIo>();

        asf_video = std::make_unique<AsfVideo>(std::move(mock_io));

    }



    std::unique_ptr<MockBasicIo> mock_io;

    std::unique_ptr<AsfVideo> asf_video;

};



TEST_F(AsfVideoTest_1566, DegradableJPEGMedia_ReadsWidthAndHeight_1566) {

    const uint32_t expected_width = 1920;

    const uint32_t expected_height = 1080;



    EXPECT_CALL(*mock_io, read(sizeof(uint32_t)))

        .WillOnce([](size_t rcount) -> DataBuf { return DataBuf(reinterpret_cast<byte*>(&expected_width), sizeof(expected_width)); })

        .WillOnce([](size_t rcount) -> DataBuf { return DataBuf(reinterpret_cast<byte*>(&expected_height), sizeof(expected_height)); });



    asf_video->DegradableJPEGMedia();



    EXPECT_EQ(asf_video->xmpData_["Xmp.video.Width"].toInt64(), expected_width);

    EXPECT_EQ(asf_video->xmpData_["Xmp.video.Height"].toInt64(), expected_height);

}



TEST_F(AsfVideoTest_1566, DegradableJPEGMedia_SeeksCorrectlyAfterReadingWidthAndHeight_1566) {

    const uint32_t width = 1920;

    const uint32_t height = 1080;



    EXPECT_CALL(*mock_io, read(sizeof(uint32_t)))

        .WillOnce([](size_t rcount) -> DataBuf { return DataBuf(reinterpret_cast<byte*>(&width), sizeof(width)); })

        .WillOnce([](size_t rcount) -> DataBuf { return DataBuf(reinterpret_cast<byte*>(&height), sizeof(height)); });



    EXPECT_CALL(*mock_io, seek(_, BasicIo::beg)).Times(2);



    asf_video->DegradableJPEGMedia();

}



TEST_F(AsfVideoTest_1566, DegradableJPEGMedia_ReadsInterchangeDataLengthAndSeeksCorrectly_1566) {

    const uint32_t width = 1920;

    const uint32_t height = 1080;

    const uint16_t interchange_data_length = 42;



    EXPECT_CALL(*mock_io, read(sizeof(uint32_t)))

        .WillOnce([](size_t rcount) -> DataBuf { return DataBuf(reinterpret_cast<byte*>(&width), sizeof(width)); })

        .WillOnce([](size_t rcount) -> DataBuf { return DataBuf(reinterpret_cast<byte*>(&height), sizeof(height)); });



    EXPECT_CALL(*mock_io, seek(_, BasicIo::beg)).Times(2);



    EXPECT_CALL(*mock_io, read(sizeof(uint16_t)))

        .WillOnce([interchange_data_length](size_t rcount) -> DataBuf {

            return DataBuf(reinterpret_cast<byte*>(&interchange_data_length), sizeof(interchange_data_length));

        });



    EXPECT_CALL(*mock_io, seek(_, BasicIo::beg)).Times(3);



    asf_video->DegradableJPEGMedia();

}



TEST_F(AsfVideoTest_1566, DegradableJPEGMedia_HandlesZeroWidthAndHeight_1566) {

    const uint32_t width = 0;

    const uint32_t height = 0;



    EXPECT_CALL(*mock_io, read(sizeof(uint32_t)))

        .WillOnce([](size_t rcount) -> DataBuf { return DataBuf(reinterpret_cast<byte*>(&width), sizeof(width)); })

        .WillOnce([](size_t rcount) -> DataBuf { return DataBuf(reinterpret_cast<byte*>(&height), sizeof(height)); });



    asf_video->DegradableJPEGMedia();



    EXPECT_EQ(asf_video->xmpData_["Xmp.video.Width"].toInt64(), width);

    EXPECT_EQ(asf_video->xmpData_["Xmp.video.Height"].toInt64(), height);

}



TEST_F(AsfVideoTest_1566, DegradableJPEGMedia_HandlesMaximumWidthAndHeight_1566) {

    const uint32_t max_width = UINT32_MAX;

    const uint32_t max_height = UINT32_MAX;



    EXPECT_CALL(*mock_io, read(sizeof(uint32_t)))

        .WillOnce([](size_t rcount) -> DataBuf { return DataBuf(reinterpret_cast<byte*>(&max_width), sizeof(max_width)); })

        .WillOnce([](size_t rcount) -> DataBuf { return DataBuf(reinterpret_cast<byte*>(&max_height), sizeof(max_height)); });



    asf_video->DegradableJPEGMedia();



    EXPECT_EQ(asf_video->xmpData_["Xmp.video.Width"].toInt64(), max_width);

    EXPECT_EQ(asf_video->xmpData_["Xmp.video.Height"].toInt64(), max_height);

}
