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

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(size_t, tell, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

};



class AsfVideoTest_1572 : public ::testing::Test {

protected:

    MockBasicIo mock_io;

    std::unique_ptr<BasicIo> io_ptr = std::make_unique<MockBasicIo>(mock_io);

    AsfVideo asf_video{std::move(io_ptr)};

};



TEST_F(AsfVideoTest_1572, FilePropertiesReadsGUID_1572) {

    uint8_t guid_bytes[GUID] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};

    EXPECT_CALL(mock_io, readOrThrow(guid_bytes, GUID, ErrorCode::kerCorruptedMetadata));



    uint64_t dummy_qword = 123456;

    for (int i = 0; i < 6; ++i) {

        EXPECT_CALL(mock_io, readQWORDTag(_)).WillOnce(Return(dummy_qword));

    }

    mock_io.seek(0, BasicIo::beg);

    EXPECT_CALL(mock_io, seek(28, BasicIo::beg));



    uint32_t dummy_dword = 789;

    EXPECT_CALL(mock_io, readDWORDTag(_)).WillOnce(Return(dummy_dword));



    asf_video.fileProperties();



    const auto& xmp_data = asf_video.xmpData();

    EXPECT_EQ(xmp_data["Xmp.video.FileID"].toString(), "12345678-9abc-def0-1122-334455667788");

}



TEST_F(AsfVideoTest_1572, FilePropertiesReadsFileLength_1572) {

    uint8_t guid_bytes[GUID] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};

    EXPECT_CALL(mock_io, readOrThrow(guid_bytes, GUID, ErrorCode::kerCorruptedMetadata));



    uint64_t file_length = 987654321;

    EXPECT_CALL(mock_io, readQWORDTag(_)).WillOnce(Return(file_length));

    

    for (int i = 0; i < 5; ++i) {

        EXPECT_CALL(mock_io, readQWORDTag(_)).WillOnce(Return(123456)); // Dummy values

    }

    mock_io.seek(0, BasicIo::beg);

    EXPECT_CALL(mock_io, seek(28, BasicIo::beg));



    uint32_t dummy_dword = 789;

    EXPECT_CALL(mock_io, readDWORDTag(_)).WillOnce(Return(dummy_dword));



    asf_video.fileProperties();



    const auto& xmp_data = asf_video.xmpData();

    EXPECT_EQ(xmp_data["Xmp.video.FileLength"].toString(), std::to_string(file_length));

}



TEST_F(AsfVideoTest_1572, FilePropertiesReadsCreationDate_1572) {

    uint8_t guid_bytes[GUID] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};

    EXPECT_CALL(mock_io, readOrThrow(guid_bytes, GUID, ErrorCode::kerCorruptedMetadata));



    uint64_t dummy_qword = 123456;

    for (int i = 0; i < 2; ++i) {

        EXPECT_CALL(mock_io, readQWORDTag(_)).WillOnce(Return(dummy_qword));

    }

    

    uint64_t creation_date = 9876543210;

    EXPECT_CALL(mock_io, readQWORDTag(_)).WillOnce(Return(creation_date));



    for (int i = 0; i < 4; ++i) {

        EXPECT_CALL(mock_io, readQWORDTag(_)).WillOnce(Return(dummy_qword)); // Dummy values

    }

    mock_io.seek(0, BasicIo::beg);

    EXPECT_CALL(mock_io, seek(28, BasicIo::beg));



    uint32_t dummy_dword = 789;

    EXPECT_CALL(mock_io, readDWORDTag(_)).WillOnce(Return(dummy_dword));



    asf_video.fileProperties();



    const auto& xmp_data = asf_video.xmpData();

    EXPECT_EQ(xmp_data["Xmp.video.CreationDate"].toString(), std::to_string(creation_date));

}



TEST_F(AsfVideoTest_1572, FilePropertiesReadsMaxBitRate_1572) {

    uint8_t guid_bytes[GUID] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};

    EXPECT_CALL(mock_io, readOrThrow(guid_bytes, GUID, ErrorCode::kerCorruptedMetadata));



    uint64_t dummy_qword = 123456;

    for (int i = 0; i < 5; ++i) {

        EXPECT_CALL(mock_io, readQWORDTag(_)).WillOnce(Return(dummy_qword));

    }

    mock_io.seek(0, BasicIo::beg);

    EXPECT_CALL(mock_io, seek(28, BasicIo::beg));



    uint32_t max_bit_rate = 1024;

    EXPECT_CALL(mock_io, readDWORDTag(_)).WillOnce(Return(max_bit_rate));



    asf_video.fileProperties();



    const auto& xmp_data = asf_video.xmpData();

    EXPECT_EQ(xmp_data["Xmp.video.MaxBitRate"].toString(), std::to_string(max_bit_rate));

}



TEST_F(AsfVideoTest_1572, FilePropertiesThrowsOnCorruptedMetadata_1572) {

    uint8_t guid_bytes[GUID] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};

    EXPECT_CALL(mock_io, readOrThrow(guid_bytes, GUID, ErrorCode::kerCorruptedMetadata)).WillOnce(testing::Throw(std::runtime_error("Mocked error")));



    EXPECT_THROW(asf_video.fileProperties(), std::runtime_error);

}
