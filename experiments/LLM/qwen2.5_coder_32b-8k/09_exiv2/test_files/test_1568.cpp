#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "asfvideo.hpp"

#include "basicio.hpp"

#include "xmp_exiv2.hpp"



using namespace testing;

using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte *data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo &src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte *buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte *buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo &src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(size_t, tell, (), (const override));

    MOCK_METHOD(size_t, size, (), (const override));

    MOCK_METHOD(bool, isopen, (), (const override));

    MOCK_METHOD(int, error, (), (const override));

    MOCK_METHOD(bool, eof, (), (const override));

    MOCK_METHOD(const std::string &, path, (), (const override));

    MOCK_METHOD(void, populateFakeData, (), (override));

};



class AsfVideoTest_1568 : public Test {

protected:

    void SetUp() override {

        mock_io = std::make_unique<StrictMock<MockBasicIo>>();

        asf_video = new AsfVideo(std::move(mock_io));

    }



    void TearDown() override {

        delete asf_video;

    }



    AsfVideo* asf_video;

    std::unique_ptr<MockBasicIo> mock_io;

};



TEST_F(AsfVideoTest_1568, CodecListReadsZeroEntries_1568) {

    EXPECT_CALL(*mock_io, seek(_, _)).Times(2);

    EXPECT_CALL(*mock_io, read(4)).WillOnce(Return(DataBuf(reinterpret_cast<byte*>(&zero_entries), 4)));



    asf_video->codecList();



    EXPECT_EQ(asf_video->xmpData().count(), 0);

}



TEST_F(AsfVideoTest_1568, CodecListReadsOneEntryWithoutNameOrDescription_1568) {

    uint32_t one_entry = 1;

    uint16_t codec_type_audio = 0; // Should map to "Xmp.audio"

    uint16_t zero_length = 0;



    EXPECT_CALL(*mock_io, seek(_, _)).Times(2);

    EXPECT_CALL(*mock_io, read(4)).WillOnce(Return(DataBuf(reinterpret_cast<byte*>(&one_entry), 4)));

    EXPECT_CALL(*mock_io, read(2)).WillOnce(Return(DataBuf(reinterpret_cast<byte*>(&codec_type_audio), 2)))

                                   .WillOnce(Return(DataBuf(reinterpret_cast<byte*>(&zero_length), 2)))

                                   .WillOnce(Return(DataBuf(reinterpret_cast<byte*>(&zero_length), 2)));



    asf_video->codecList();



    EXPECT_EQ(asf_video->xmpData().count(), 1);

    EXPECT_EQ(asf_video->xmpData()["Xmp.audio.CodecInfo"], "");

}



TEST_F(AsfVideoTest_1568, CodecListReadsOneEntryWithCodecNameAndDescription_1568) {

    uint32_t one_entry = 1;

    uint16_t codec_type_video = 1; // Should map to "Xmp.video"

    uint16_t name_length = 4;      // Length of "Test" in wide chars (2 bytes each)

    uint16_t desc_length = 8;     // Length of "Description" in wide chars (2 bytes each)



    char codec_name[] = {'T', '\0', 'e', '\0', 's', '\0', 't', '\0'};

    char codec_desc[] = {'D', '\0', 'e', '\0', 's', '\0', 'c', '\0', 'r', '\0', 'i', '\0', 'p', '\0', 't', '\0', 'i', '\0', 'o', '\0', 'n', '\0'};



    EXPECT_CALL(*mock_io, seek(_, _)).Times(2);

    EXPECT_CALL(*mock_io, read(4)).WillOnce(Return(DataBuf(reinterpret_cast<byte*>(&one_entry), 4)));

    EXPECT_CALL(*mock_io, read(2))

        .WillOnce(Return(DataBuf(reinterpret_cast<byte*>(&codec_type_video), 2))) // codec type

        .WillOnce(Return(DataBuf(reinterpret_cast<byte*>(&name_length), 2)))       // name length

        .WillOnce(Return(DataBuf(reinterpret_cast<byte*>(codec_name), sizeof(codec_name)))) // name data

        .WillOnce(Return(DataBuf(reinterpret_cast<byte*>(&desc_length), 2)))       // description length

        .WillOnce(Return(DataBuf(reinterpret_cast<byte*>(codec_desc), sizeof(codec_desc)))); // description data



    asf_video->codecList();



    EXPECT_EQ(asf_video->xmpData().count(), 3);

    EXPECT_EQ(asf_video->xmpData()["Xmp.video.CodecName"], "Test");

    EXPECT_EQ(asf_video->xmpData()["Xmp.video.CodecDescription"], "Description");

}



TEST_F(AsfVideoTest_1568, CodecListHandlesCorruptedMetadata_1568) {

    uint32_t one_entry = 1;

    uint16_t codec_type_audio = 0; // Should map to "Xmp.audio"

    uint16_t name_length = 4;      // Length of "Test" in wide chars (2 bytes each)

    uint16_t info_length_large = 10000;



    EXPECT_CALL(*mock_io, seek(_, _)).Times(2);

    EXPECT_CALL(*mock_io, read(4)).WillOnce(Return(DataBuf(reinterpret_cast<byte*>(&one_entry), 4)));

    EXPECT_CALL(*mock_io, read(2))

        .WillOnce(Return(DataBuf(reinterpret_cast<byte*>(&codec_type_audio), 2))) // codec type

        .WillOnce(Return(DataBuf(reinterpret_cast<byte*>(&name_length), 2)));       // name length

    EXPECT_CALL(*mock_io, read(name_length * 2)).Times(1); // name data

    EXPECT_CALL(*mock_io, read(2)).WillOnce(Return(DataBuf(reinterpret_cast<byte*>(&info_length_large), 2)));



    EXPECT_THROW(asf_video->codecList(), Exiv2::Error);



    EXPECT_EQ(asf_video->xmpData().count(), 0);

}



TEST_F(AsfVideoTest_1568, CodecListReadsMultipleEntries_1568) {

    uint32_t two_entries = 2;

    uint16_t codec_type_audio = 0; // Should map to "Xmp.audio"

    uint16_t codec_type_video = 1; // Should map to "Xmp.video"

    uint16_t zero_length = 0;



    EXPECT_CALL(*mock_io, seek(_, _)).Times(2);

    EXPECT_CALL(*mock_io, read(4)).WillOnce(Return(DataBuf(reinterpret_cast<byte*>(&two_entries), 4)));

    for (int i = 0; i < two_entries; ++i) {

        uint16_t codec_type = (i == 0) ? codec_type_audio : codec_type_video;

        EXPECT_CALL(*mock_io, read(2)).WillOnce(Return(DataBuf(reinterpret_cast<byte*>(&codec_type), 2)))

                                       .WillOnce(Return(DataBuf(reinterpret_cast<byte*>(&zero_length), 2))) // name length

                                       .WillOnce(Return(DataBuf(reinterpret_cast<byte*>(&zero_length), 2))); // description length

    }



    asf_video->codecList();



    EXPECT_EQ(asf_video->xmpData().count(), two_entries);

}



TEST_F(AsfVideoTest_1568, CodecListHandlesEmptyIoStream_1568) {

    EXPECT_CALL(*mock_io, seek(_, _)).Times(2);

    EXPECT_CALL(*mock_io, read(4)).WillOnce(Return(DataBuf(nullptr, 0)));



    asf_video->codecList();



    EXPECT_EQ(asf_video->xmpData().count(), 0);

}
