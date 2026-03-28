#include <gtest/gtest.h>

#include "exiv2/asfvideo.hpp"

#include "exiv2/basicio.hpp"

#include <gmock/gmock.h>



using namespace testing;



namespace {



class MockBasicIo : public Exiv2::BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

};



class AsfVideoTest : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io = std::make_unique<MockBasicIo>();

    Exiv2::AsfVideo asf_video{std::move(mock_io)};

};



TEST_F(AsfVideoTest_1565, ExtendedStreamProperties_SetsStartTimecodeAndEndTimecode_1565) {

    // Arrange

    const byte data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};

    EXPECT_CALL(*mock_io, read(A<const byte*>(), Eq(Exiv2::DWORD)))

        .WillOnce(Return(data + 0)) // Start Timecode (QWORD)

        .WillOnce(Return(data + 8)); // End Timecode (WORD)

    EXPECT_CALL(*mock_io, seek(Eq(0), Eq(Exiv2::BasicIo::beg))).Times(9); // Ignore fields

    EXPECT_CALL(*mock_io, tell()).WillRepeatedly(Return(0));



    // Act

    asf_video.extendedStreamProperties();



    // Assert

    auto xmp_data = asf_video.xmpData();

    EXPECT_EQ(xmp_data["Xmp.video.StartTimecode"].toString(), "752469139813888"); // 0x0706050403020100

    EXPECT_EQ(xmp_data["Xmp.video.EndTimecode"].toString(), "2337"); // 0x0908

}



TEST_F(AsfVideoTest_1565, ExtendedStreamProperties_SetsFrameRate_1565) {

    // Arrange

    const byte data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B};

    EXPECT_CALL(*mock_io, read(A<const byte*>(), Eq(Exiv2::DWORD)))

        .WillOnce(Return(data + 0)) // Start Timecode (QWORD)

        .WillOnce(Return(data + 8)); // End Timecode (WORD)

    EXPECT_CALL(*mock_io, seek(Eq(0), Eq(Exiv2::BasicIo::beg))).Times(9); // Ignore fields

    EXPECT_CALL(*mock_io, tell()).WillRepeatedly(Return(0));

    EXPECT_CALL(*mock_io, read(A<const byte*>(), Eq(Exiv2::WORD)))

        .WillOnce(Return(data + 10)); // Frame Rate (WORD)



    // Act

    asf_video.extendedStreamProperties();



    // Assert

    auto xmp_data = asf_video.xmpData();

    EXPECT_EQ(xmp_data["Xmp.video.FrameRate"].toString(), "2674"); // 0x0B0A

}



TEST_F(AsfVideoTest_1565, ExtendedStreamProperties_IgnoresStreamNames_1565) {

    // Arrange

    const byte data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D};

    EXPECT_CALL(*mock_io, read(A<const byte*>(), Eq(Exiv2::DWORD)))

        .WillOnce(Return(data + 0)) // Start Timecode (QWORD)

        .WillOnce(Return(data + 8)); // End Timecode (WORD)

    EXPECT_CALL(*mock_io, seek(Eq(0), Eq(Exiv2::BasicIo::beg))).Times(9); // Ignore fields

    EXPECT_CALL(*mock_io, tell()).WillRepeatedly(Return(0));

    EXPECT_CALL(*mock_io, read(A<const byte*>(), Eq(Exiv2::WORD)))

        .WillOnce(Return(data + 10)) // Frame Rate (WORD)

        .WillOnce(Return(data + 12)) // Stream Name Count (WORD)

        .WillOnce(Return(data + 14)); // Payload Ext Sys Count (WORD)



    EXPECT_CALL(*mock_io, read(A<const byte*>(), Eq(Exiv2::WORD)))

        .WillOnce(Return(data + 0)) // Language ID Index

        .WillOnce(Return(data + 2)) // Stream Length



    EXPECT_CALL(*mock_io, seek(Eq(2), Eq(Exiv2::BasicIo::beg))); // Ignore Stream Name



    // Act

    asf_video.extendedStreamProperties();



    // Assert

    auto xmp_data = asf_video.xmpData();

    EXPECT_EQ(xmp_data.count(), 3); // Start Timecode, End Timecode, Frame Rate

}



TEST_F(AsfVideoTest_1565, ExtendedStreamProperties_IgnoresPayloadExtSys_1565) {

    // Arrange

    const byte data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

    EXPECT_CALL(*mock_io, read(A<const byte*>(), Eq(Exiv2::DWORD)))

        .WillOnce(Return(data + 0)) // Start Timecode (QWORD)

        .WillOnce(Return(data + 8)); // End Timecode (WORD)

    EXPECT_CALL(*mock_io, seek(Eq(0), Eq(Exiv2::BasicIo::beg))).Times(9); // Ignore fields

    EXPECT_CALL(*mock_io, tell()).WillRepeatedly(Return(0));

    EXPECT_CALL(*mock_io, read(A<const byte*>(), Eq(Exiv2::WORD)))

        .WillOnce(Return(data + 10)) // Frame Rate (WORD)

        .WillOnce(Return(data + 12)) // Stream Name Count (WORD)

        .WillOnce(Return(data + 14)); // Payload Ext Sys Count (WORD)



    EXPECT_CALL(*mock_io, read(A<const byte*>(), Eq(Exiv2::WORD)))

        .WillOnce(Return(data + 0)) // Language ID Index

        .WillOnce(Return(data + 2)) // Stream Length



    EXPECT_CALL(*mock_io, seek(Eq(2), Eq(Exiv2::BasicIo::beg))); // Ignore Stream Name



    EXPECT_CALL(*mock_io, read(A<const byte*>(), Eq(Exiv2::GUID)))

        .WillOnce(Return(data)); // Extension System ID

    EXPECT_CALL(*mock_io, read(A<const byte*>(), Eq(Exiv2::WORD)))

        .WillOnce(Return(data + 16)) // Extension Data Size

        .WillOnce(Return(data + 18)) // Extension Sys Info Length



    EXPECT_CALL(*mock_io, seek(Eq(2), Eq(Exiv2::BasicIo::beg))); // Ignore Extension System Info



    // Act

    asf_video.extendedStreamProperties();



    // Assert

    auto xmp_data = asf_video.xmpData();

    EXPECT_EQ(xmp_data.count(), 3); // Start Timecode, End Timecode, Frame Rate

}



TEST_F(AsfVideoTest_1565, ExtendedStreamProperties_HandlesZeroStreamNamesAndPayloadExtSys_1565) {

    // Arrange

    const byte data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B};

    EXPECT_CALL(*mock_io, read(A<const byte*>(), Eq(Exiv2::DWORD)))

        .WillOnce(Return(data + 0)) // Start Timecode (QWORD)

        .WillOnce(Return(data + 8)); // End Timecode (WORD)

    EXPECT_CALL(*mock_io, seek(Eq(0), Eq(Exiv2::BasicIo::beg))).Times(9); // Ignore fields

    EXPECT_CALL(*mock_io, tell()).WillRepeatedly(Return(0));

    EXPECT_CALL(*mock_io, read(A<const byte*>(), Eq(Exiv2::WORD)))

        .WillOnce(Return(data + 10)) // Frame Rate (WORD)

        .WillOnce(Return(data + 12)) // Stream Name Count (WORD)

        .WillOnce(Return(data + 14)); // Payload Ext Sys Count (WORD)



    // Act

    asf_video.extendedStreamProperties();



    // Assert

    auto xmp_data = asf_video.xmpData();

    EXPECT_EQ(xmp_data.count(), 3); // Start Timecode, End Timecode, Frame Rate

}



TEST_F(AsfVideoTest_1565, ExtendedStreamProperties_FailsOnReadErrors_1565) {

    // Arrange

    EXPECT_CALL(*mock_io, read(A<const byte*>(), Eq(Exiv2::DWORD)))

        .WillOnce(Return(nullptr)); // Simulate error reading Start Timecode



    // Act & Assert

    EXPECT_THROW(asf_video.extendedStreamProperties(), Exiv2::Error);

}



}  // namespace
