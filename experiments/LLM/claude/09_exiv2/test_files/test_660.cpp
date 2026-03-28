#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/quicktimevideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <exiv2/error.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <memory>
#include <cstring>
#include <sstream>

using namespace Exiv2;

namespace {

// Helper to create a DataBuf with a specific 4-byte tag at the beginning
DataBuf makeTagBuf(const char* tag) {
    DataBuf buf(8);
    // First 4 bytes can be anything (typically size), next 4 bytes are the tag
    // Based on the code: equalsQTimeTag checks buf content
    // Looking at typical QuickTime parsing, the tag is typically at offset 0 or 4
    // The assert says buf.size() > 4, so we need at least 5 bytes
    // equalsQTimeTag likely compares bytes starting at some offset
    // From typical exiv2 code, the tag bytes are at the start of the buffer
    std::memset(buf.data(0), 0, 8);
    std::memcpy(buf.data(0), tag, 4);
    return buf;
}

// Helper to create a MemIo with some data
std::unique_ptr<BasicIo> createMemIoWithData(const std::vector<uint8_t>& data) {
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    return io;
}

// Helper to create a MemIo with specific size of zero-filled data
std::unique_ptr<BasicIo> createMemIoWithSize(size_t size) {
    std::vector<uint8_t> data(size, 0);
    return createMemIoWithData(data);
}

} // anonymous namespace

class QuickTimeVideoTagDecoderTest_660 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    std::unique_ptr<QuickTimeVideo> createQTV(std::unique_ptr<BasicIo> io, size_t max_depth = 100) {
        return std::make_unique<QuickTimeVideo>(std::move(io), max_depth);
    }
};

// Test that recursion depth exceeding max causes an error
TEST_F(QuickTimeVideoTagDecoderTest_660, RecursionDepthExceedsMax_ThrowsError_660) {
    // Create a QuickTimeVideo with max_recursion_depth = 2
    std::vector<uint8_t> ioData(1024, 0);
    auto io = std::make_unique<MemIo>(ioData.data(), ioData.size());
    io->open();
    auto qtv = createQTV(std::move(io), 2);

    DataBuf buf(8);
    std::memset(buf.data(0), 0, 8);
    // Some unknown tag so it would just discard
    std::memcpy(buf.data(0), "xxxx", 4);

    // recursion_depth >= max_recursion_depth should throw
    EXPECT_THROW(qtv->tagDecoder(buf, 0, 2), Exiv2::Error);
    EXPECT_THROW(qtv->tagDecoder(buf, 0, 3), Exiv2::Error);
    EXPECT_THROW(qtv->tagDecoder(buf, 0, 100), Exiv2::Error);
}

// Test that recursion depth of 0 (within limit) does not throw for unknown tag
TEST_F(QuickTimeVideoTagDecoderTest_660, RecursionDepthZero_UnknownTag_NoThrow_660) {
    std::vector<uint8_t> ioData(1024, 0);
    auto io = std::make_unique<MemIo>(ioData.data(), ioData.size());
    io->open();
    auto qtv = createQTV(std::move(io), 100);

    DataBuf buf(8);
    std::memset(buf.data(0), 0, 8);
    std::memcpy(buf.data(0), "zzzz", 4);

    // Should not throw - unknown tag with size 0 should just discard(0)
    EXPECT_NO_THROW(qtv->tagDecoder(buf, 0, 0));
}

// Test that max_recursion_depth of 1 allows depth 0 but not depth 1
TEST_F(QuickTimeVideoTagDecoderTest_660, MaxRecursionDepthOne_660) {
    std::vector<uint8_t> ioData(1024, 0);
    auto io = std::make_unique<MemIo>(ioData.data(), ioData.size());
    io->open();
    auto qtv = createQTV(std::move(io), 1);

    DataBuf buf(8);
    std::memset(buf.data(0), 0, 8);
    std::memcpy(buf.data(0), "zzzz", 4);

    // depth 0 should be fine
    EXPECT_NO_THROW(qtv->tagDecoder(buf, 0, 0));

    // depth 1 == max should throw
    EXPECT_THROW(qtv->tagDecoder(buf, 0, 1), Exiv2::Error);
}

// Test with max_recursion_depth of 0 - even depth 0 should throw
TEST_F(QuickTimeVideoTagDecoderTest_660, MaxRecursionDepthZero_AlwaysThrows_660) {
    std::vector<uint8_t> ioData(1024, 0);
    auto io = std::make_unique<MemIo>(ioData.data(), ioData.size());
    io->open();
    auto qtv = createQTV(std::move(io), 0);

    DataBuf buf(8);
    std::memset(buf.data(0), 0, 8);
    std::memcpy(buf.data(0), "zzzz", 4);

    EXPECT_THROW(qtv->tagDecoder(buf, 0, 0), Exiv2::Error);
}

// Test with "dcom" tag - should set Xmp.video.Compressor
TEST_F(QuickTimeVideoTagDecoderTest_660, DcomTag_SetsCompressor_660) {
    // Prepare IO data that readString will read
    const std::string compressor = "zlib";
    std::vector<uint8_t> ioData(compressor.begin(), compressor.end());
    // Pad with extra bytes
    ioData.resize(1024, 0);
    auto io = std::make_unique<MemIo>(ioData.data(), ioData.size());
    io->open();
    auto qtv = createQTV(std::move(io), 100);

    DataBuf buf(8);
    std::memset(buf.data(0), 0, 8);
    std::memcpy(buf.data(0), "dcom", 4);

    EXPECT_NO_THROW(qtv->tagDecoder(buf, 4, 0));

    // Check that xmpData has the compressor entry
    auto& xmp = qtv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.Compressor"));
    EXPECT_NE(it, xmp.end());
    if (it != xmp.end()) {
        EXPECT_EQ(it->toString(), compressor);
    }
}

// Test with "smhd" tag - should set Xmp.audio.Balance
TEST_F(QuickTimeVideoTagDecoderTest_660, SmhdTag_SetsAudioBalance_660) {
    // smhd reads 4 bytes (skip), then reads 4 bytes and interprets uint16 at offset 0
    std::vector<uint8_t> ioData(1024, 0);
    // First 4 bytes read (skipped version/flags)
    ioData[0] = 0; ioData[1] = 0; ioData[2] = 0; ioData[3] = 0;
    // Next 4 bytes: balance at offset 0 as big-endian uint16
    ioData[4] = 0x00; ioData[5] = 0x42; // balance = 0x0042 = 66
    ioData[6] = 0x00; ioData[7] = 0x00;

    auto io = std::make_unique<MemIo>(ioData.data(), ioData.size());
    io->open();
    auto qtv = createQTV(std::move(io), 100);

    DataBuf buf(8);
    std::memset(buf.data(0), 0, 8);
    std::memcpy(buf.data(0), "smhd", 4);

    EXPECT_NO_THROW(qtv->tagDecoder(buf, 8, 0));

    auto& xmp = qtv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.audio.Balance"));
    EXPECT_NE(it, xmp.end());
    if (it != xmp.end()) {
        EXPECT_EQ(it->toInt64(0), 0x0042);
    }
}

// Test that buf with size <= 4 would trigger the assert (undefined behavior in debug)
// We can't really test assert in release mode, but we can ensure buf.size() > 4 is needed
// This is more of a documentation test

// Test unknown tag with non-zero size - should discard
TEST_F(QuickTimeVideoTagDecoderTest_660, UnknownTag_DiscardsData_660) {
    std::vector<uint8_t> ioData(1024, 0);
    auto io = std::make_unique<MemIo>(ioData.data(), ioData.size());
    io->open();
    
    size_t posBefore = io->tell();
    auto qtv = createQTV(std::move(io), 100);

    DataBuf buf(8);
    std::memset(buf.data(0), 0, 8);
    std::memcpy(buf.data(0), "????", 4);

    // discard(10) should advance the io position by 10
    EXPECT_NO_THROW(qtv->tagDecoder(buf, 10, 0));
    
    // We can verify the io position moved
    EXPECT_EQ(qtv->io().tell(), 10u);
}

// Test "url " tag when currentStream is not Video or Audio (default is Null)
// Should discard
TEST_F(QuickTimeVideoTagDecoderTest_660, UrlTag_NullStream_Discards_660) {
    std::vector<uint8_t> ioData(1024, 0);
    auto io = std::make_unique<MemIo>(ioData.data(), ioData.size());
    io->open();
    auto qtv = createQTV(std::move(io), 100);

    DataBuf buf(8);
    std::memset(buf.data(0), 0, 8);
    std::memcpy(buf.data(0), "url ", 4);

    // currentStream_ is Null by default, so url should discard
    EXPECT_NO_THROW(qtv->tagDecoder(buf, 5, 0));

    // Should not have any URL in xmpData
    auto& xmp = qtv->xmpData();
    auto itVideo = xmp.findKey(XmpKey("Xmp.video.URL"));
    auto itAudio = xmp.findKey(XmpKey("Xmp.audio.URL"));
    EXPECT_EQ(itVideo, xmp.end());
    EXPECT_EQ(itAudio, xmp.end());
}

// Test "urn " tag when currentStream is not Video or Audio (default is Null)
// Should discard
TEST_F(QuickTimeVideoTagDecoderTest_660, UrnTag_NullStream_Discards_660) {
    std::vector<uint8_t> ioData(1024, 0);
    auto io = std::make_unique<MemIo>(ioData.data(), ioData.size());
    io->open();
    auto qtv = createQTV(std::move(io), 100);

    DataBuf buf(8);
    std::memset(buf.data(0), 0, 8);
    std::memcpy(buf.data(0), "urn ", 4);

    EXPECT_NO_THROW(qtv->tagDecoder(buf, 5, 0));

    auto& xmp = qtv->xmpData();
    auto itVideo = xmp.findKey(XmpKey("Xmp.video.URN"));
    auto itAudio = xmp.findKey(XmpKey("Xmp.audio.URN"));
    EXPECT_EQ(itVideo, xmp.end());
    EXPECT_EQ(itAudio, xmp.end());
}

// Test multiple calls to tagDecoder with unknown tags - IO position should advance correctly
TEST_F(QuickTimeVideoTagDecoderTest_660, MultipleUnknownTags_IOPositionAdvances_660) {
    std::vector<uint8_t> ioData(2048, 0);
    auto io = std::make_unique<MemIo>(ioData.data(), ioData.size());
    io->open();
    auto qtv = createQTV(std::move(io), 100);

    DataBuf buf(8);
    std::memset(buf.data(0), 0, 8);
    std::memcpy(buf.data(0), "XXXX", 4);

    qtv->tagDecoder(buf, 100, 0);
    EXPECT_EQ(qtv->io().tell(), 100u);

    qtv->tagDecoder(buf, 200, 0);
    EXPECT_EQ(qtv->io().tell(), 300u);
}

// Test with size 0 for unknown tag
TEST_F(QuickTimeVideoTagDecoderTest_660, UnknownTag_ZeroSize_660) {
    std::vector<uint8_t> ioData(1024, 0);
    auto io = std::make_unique<MemIo>(ioData.data(), ioData.size());
    io->open();
    auto qtv = createQTV(std::move(io), 100);

    DataBuf buf(8);
    std::memset(buf.data(0), 0, 8);
    std::memcpy(buf.data(0), "YYYY", 4);

    EXPECT_NO_THROW(qtv->tagDecoder(buf, 0, 0));
    EXPECT_EQ(qtv->io().tell(), 0u);
}

// Test recursion depth exactly at max-1 (boundary)
TEST_F(QuickTimeVideoTagDecoderTest_660, RecursionDepthAtMaxMinusOne_NoThrow_660) {
    std::vector<uint8_t> ioData(1024, 0);
    auto io = std::make_unique<MemIo>(ioData.data(), ioData.size());
    io->open();
    auto qtv = createQTV(std::move(io), 5);

    DataBuf buf(8);
    std::memset(buf.data(0), 0, 8);
    std::memcpy(buf.data(0), "zzzz", 4);

    // depth 4 < max 5, should be fine
    EXPECT_NO_THROW(qtv->tagDecoder(buf, 0, 4));
}

// Test "dcom" tag with empty data (size=0)
TEST_F(QuickTimeVideoTagDecoderTest_660, DcomTag_EmptySize_660) {
    std::vector<uint8_t> ioData(1024, 0);
    auto io = std::make_unique<MemIo>(ioData.data(), ioData.size());
    io->open();
    auto qtv = createQTV(std::move(io), 100);

    DataBuf buf(8);
    std::memset(buf.data(0), 0, 8);
    std::memcpy(buf.data(0), "dcom", 4);

    EXPECT_NO_THROW(qtv->tagDecoder(buf, 0, 0));

    auto& xmp = qtv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.Compressor"));
    // With size 0, readString should return empty string
    if (it != xmp.end()) {
        EXPECT_TRUE(it->toString().empty());
    }
}

// Test mimeType returns video/quicktime
TEST_F(QuickTimeVideoTagDecoderTest_660, MimeType_ReturnsQuickTime_660) {
    std::vector<uint8_t> ioData(1024, 0);
    auto io = std::make_unique<MemIo>(ioData.data(), ioData.size());
    io->open();
    auto qtv = createQTV(std::move(io), 100);

    EXPECT_EQ(qtv->mimeType(), "video/quicktime");
}

// Test that large recursion depth value triggers error
TEST_F(QuickTimeVideoTagDecoderTest_660, VeryLargeRecursionDepth_ThrowsError_660) {
    std::vector<uint8_t> ioData(1024, 0);
    auto io = std::make_unique<MemIo>(ioData.data(), ioData.size());
    io->open();
    auto qtv = createQTV(std::move(io), 100);

    DataBuf buf(8);
    std::memset(buf.data(0), 0, 8);
    std::memcpy(buf.data(0), "zzzz", 4);

    EXPECT_THROW(qtv->tagDecoder(buf, 0, 999999), Exiv2::Error);
}
