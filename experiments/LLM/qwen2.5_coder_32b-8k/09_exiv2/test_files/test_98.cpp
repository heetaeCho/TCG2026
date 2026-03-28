#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "matroskavideo.hpp"

#include "image.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class MatroskaVideoTest_98 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = BasicIo::autoPtr();

    MatroskaVideo* matroskaVideo = new MatroskaVideo(std::move(io));



    ~MatroskaVideoTest_98() override {

        delete matroskaVideo;

    }



    const byte* createBuffer(uint64_t value, ByteOrder order) {

        static byte buffer[sizeof(uint64_t)];

        byteSwap(value, buffer, sizeof(uint64_t), order);

        return buffer;

    }



    void byteSwap(uint64_t value, byte* buf, size_t size, ByteOrder order) {

        if (order == bigEndian) {

            for (size_t i = 0; i < size; ++i)

                buf[i] = static_cast<byte>((value >> ((size - i - 1) * 8)) & 0xFF);

        } else {

            for (size_t i = 0; i < size; ++i)

                buf[i] = static_cast<byte>((value >> (i * 8)) & 0xFF);

        }

    }



    MatroskaTag tag(uint64_t id, const std::string& label) {

        return MatroskaTag(id, label);

    }

};



TEST_F(MatroskaVideoTest_98, PutIncreasesCount_98) {

    uint64_t key = 1;

    const byte* buf = createBuffer(key, bigEndian);

    matroskaVideo->decodeInternalTags(&tag(Xmp_video_VideoScanTpye, ""), buf);



    EXPECT_EQ(matroskaVideo->xmpData_.count(), 1);

}



TEST_F(MatroskaVideoTest_98, KeyZeroDoesNothing_98) {

    uint64_t key = 0;

    const byte* buf = createBuffer(key, bigEndian);

    matroskaVideo->decodeInternalTags(&tag(Xmp_video_VideoScanTpye, ""), buf);



    EXPECT_EQ(matroskaVideo->xmpData_.count(), 0);

}



TEST_F(MatroskaVideoTest_98, UnknownIdDoesNothing_98) {

    uint64_t key = 1;

    const byte* buf = createBuffer(key, bigEndian);

    matroskaVideo->decodeInternalTags(&tag(999, ""), buf);



    EXPECT_EQ(matroskaVideo->xmpData_.count(), 0);

}



TEST_F(MatroskaVideoTest_98, KnownIdWithKnownKeySetsLabel_98) {

    uint64_t key = 1;

    const byte* buf = createBuffer(key, bigEndian);

    matroskaVideo->decodeInternalTags(&tag(Xmp_video_VideoScanTpye, ""), buf);



    EXPECT_EQ(matroskaVideo->xmpData_.begin()->second, "Interlaced");

}



TEST_F(MatroskaVideoTest_98, KnownIdWithUnknownKeySetsValue_98) {

    uint64_t key = 99; // Not defined in videoScanType

    const byte* buf = createBuffer(key, bigEndian);

    matroskaVideo->decodeInternalTags(&tag(Xmp_video_VideoScanTpye, ""), buf);



    EXPECT_EQ(matroskaVideo->xmpData_.begin()->second, "1");

}



TEST_F(MatroskaVideoTest_98, LittleEndianKeyIsCorrectlyParsed_98) {

    uint64_t key = 2;

    const byte* buf = createBuffer(key, littleEndian);

    matroskaVideo->decodeInternalTags(&tag(Xmp_audio_ChannelType, ""), buf);



    EXPECT_EQ(matroskaVideo->xmpData_.begin()->second, "Stereo");

}
