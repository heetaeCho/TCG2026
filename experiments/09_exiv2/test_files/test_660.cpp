#include <gtest/gtest.h>

#include <gmock/gmock.h>



#include "exiv2/quicktimevideo.hpp"

#include "exiv2/basicio.hpp"



using namespace testing;

using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

};



class QuickTimeVideoTest_660 : public Test {

protected:

    void SetUp() override {

        mock_io = std::make_unique<StrictMock<MockBasicIo>>();

        quick_time_video = new QuickTimeVideo(std::move(mock_io), 10);

    }



    void TearDown() override {

        delete quick_time_video;

    }



    BasicIo::UniquePtr mock_io;

    QuickTimeVideo* quick_time_video;

};



TEST_F(QuickTimeVideoTest_660, TagDecoder_FtypTag_660) {

    DataBuf buf("ftyp", 4);

    EXPECT_CALL(*mock_io, seek(_, _)).Times(AtLeast(1));

    quick_time_video->tagDecoder(buf, 4, 0);

    // Assuming fileTypeDecoder is called internally

}



TEST_F(QuickTimeVideoTest_660, TagDecoder_TrakTag_660) {

    DataBuf buf("trak", 4);

    EXPECT_CALL(*mock_io, seek(_, _)).Times(AtLeast(1));

    quick_time_video->tagDecoder(buf, 4, 0);

    // Assuming setMediaStream is called internally

}



TEST_F(QuickTimeVideoTest_660, TagDecoder_MvhdTag_660) {

    DataBuf buf("mvhd", 4);

    EXPECT_CALL(*mock_io, seek(_, _)).Times(AtLeast(1));

    quick_time_video->tagDecoder(buf, 4, 0);

    // Assuming movieHeaderDecoder is called internally

}



TEST_F(QuickTimeVideoTest_660, TagDecoder_TkhdTag_660) {

    DataBuf buf("tkhd", 4);

    EXPECT_CALL(*mock_io, seek(_, _)).Times(AtLeast(1));

    quick_time_video->tagDecoder(buf, 4, 0);

    // Assuming trackHeaderDecoder is called internally

}



TEST_F(QuickTimeVideoTest_660, TagDecoder_MdhdTag_660) {

    DataBuf buf("mdhd", 4);

    EXPECT_CALL(*mock_io, seek(_, _)).Times(AtLeast(1));

    quick_time_video->tagDecoder(buf, 4, 0);

    // Assuming mediaHeaderDecoder is called internally

}



TEST_F(QuickTimeVideoTest_660, TagDecoder_HdlrTag_660) {

    DataBuf buf("hdlr", 4);

    EXPECT_CALL(*mock_io, seek(_, _)).Times(AtLeast(1));

    quick_time_video->tagDecoder(buf, 4, 0);

    // Assuming handlerDecoder is called internally

}



TEST_F(QuickTimeVideoTest_660, TagDecoder_VmhdTag_660) {

    DataBuf buf("vmhd", 4);

    EXPECT_CALL(*mock_io, seek(_, _)).Times(AtLeast(1));

    quick_time_video->tagDecoder(buf, 4, 0);

    // Assuming videoHeaderDecoder is called internally

}



TEST_F(QuickTimeVideoTest_660, TagDecoder_UdtaTag_660) {

    DataBuf buf("udta", 4);

    EXPECT_CALL(*mock_io, seek(_, _)).Times(AtLeast(1));

    quick_time_video->tagDecoder(buf, 4, 0);

    // Assuming userDataDecoder is called internally

}



TEST_F(QuickTimeVideoTest_660, TagDecoder_DrefTag_660) {

    DataBuf buf("dref", 4);

    EXPECT_CALL(*mock_io, seek(_, _)).Times(AtLeast(1));

    quick_time_video->tagDecoder(buf, 4, 0);

    // Assuming multipleEntriesDecoder is called internally

}



TEST_F(QuickTimeVideoTest_660, TagDecoder_StsdTag_660) {

    DataBuf buf("stsd", 4);

    EXPECT_CALL(*mock_io, seek(_, _)).Times(AtLeast(1));

    quick_time_video->tagDecoder(buf, 4, 0);

    // Assuming sampleDesc is called internally

}



TEST_F(QuickTimeVideoTest_660, TagDecoder_SttsTag_660) {

    DataBuf buf("stts", 4);

    EXPECT_CALL(*mock_io, seek(_, _)).Times(AtLeast(1));

    quick_time_video->tagDecoder(buf, 4, 0);

    // Assuming timeToSampleDecoder is called internally

}



TEST_F(QuickTimeVideoTest_660, TagDecoder_PnotTag_660) {

    DataBuf buf("pnot", 4);

    EXPECT_CALL(*mock_io, seek(_, _)).Times(AtLeast(1));

    quick_time_video->tagDecoder(buf, 4, 0);

    // Assuming previewTagDecoder is called internally

}



TEST_F(QuickTimeVideoTest_660, TagDecoder_TaptTag_660) {

    DataBuf buf("tapt", 4);

    EXPECT_CALL(*mock_io, seek(_, _)).Times(AtLeast(1));

    quick_time_video->tagDecoder(buf, 4, 0);

    // Assuming trackApertureTagDecoder is called internally

}



TEST_F(QuickTimeVideoTest_660, TagDecoder_KeysTag_660) {

    DataBuf buf("keys", 4);

    EXPECT_CALL(*mock_io, seek(_, _)).Times(AtLeast(1));

    quick_time_video->tagDecoder(buf, 4, 0);

    // Assuming keysTagDecoder is called internally

}



TEST_F(QuickTimeVideoTest_660, TagDecoder_UrnTag_660) {

    DataBuf buf("urn ", 4);

    EXPECT_CALL(*mock_io, seek(_, _)).Times(AtLeast(1));

    quick_time_video->tagDecoder(buf, 4, 0);

    // Assuming readOrThrow and setting xmpData is called internally

}



TEST_F(QuickTimeVideoTest_660, TagDecoder_DiscardTag_660) {

    DataBuf buf("disc", 4);

    EXPECT_CALL(*mock_io, seek(_, _)).Times(AtLeast(1));

    quick_time_video->tagDecoder(buf, 4, 0);

    // Assuming discard is called internally

}



TEST_F(QuickTimeVideoTest_660, TagDecoder_MaxRecursionDepthExceeded_660) {

    DataBuf buf("test", 4);

    EXPECT_THROW(quick_time_video->tagDecoder(buf, 4, 11), Error);

}
