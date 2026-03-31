#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/xmpsidecar.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <cstring>
#include <sstream>

using namespace Exiv2;

class XmpSidecarTest_2204 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<BasicIo> createMemIo() {
        return std::make_unique<MemIo>();
    }

    std::unique_ptr<BasicIo> createMemIoWithData(const std::string& data) {
        auto io = std::make_unique<MemIo>();
        io->open();
        io->write(reinterpret_cast<const byte*>(data.c_str()), data.size());
        io->seek(0, BasicIo::beg);
        io->close();
        return io;
    }
};

// Test that XmpSidecar can be constructed with create=false
TEST_F(XmpSidecarTest_2204, ConstructWithCreateFalse_2204) {
    auto io = createMemIo();
    ASSERT_NO_THROW(XmpSidecar sidecar(std::move(io), false));
}

// Test that XmpSidecar can be constructed with create=true
TEST_F(XmpSidecarTest_2204, ConstructWithCreateTrue_2204) {
    auto io = createMemIo();
    ASSERT_NO_THROW(XmpSidecar sidecar(std::move(io), true));
}

// Test that when create=true, the IO contains the XML header
TEST_F(XmpSidecarTest_2204, CreateTrueWritesXmlHeader_2204) {
    auto io = std::make_unique<MemIo>();
    XmpSidecar sidecar(std::move(io), true);

    const BasicIo& sidecarIo = sidecar.io();
    // When create is true, the io should have data written to it (the XML header)
    EXPECT_GT(sidecarIo.size(), 0u);
}

// Test that when create=false, the IO remains empty
TEST_F(XmpSidecarTest_2204, CreateFalseDoesNotWriteHeader_2204) {
    auto io = std::make_unique<MemIo>();
    XmpSidecar sidecar(std::move(io), false);

    const BasicIo& sidecarIo = sidecar.io();
    EXPECT_EQ(sidecarIo.size(), 0u);
}

// Test that mimeType returns the expected XMP mime type
TEST_F(XmpSidecarTest_2204, MimeTypeReturnsCorrectType_2204) {
    auto io = createMemIo();
    XmpSidecar sidecar(std::move(io), false);

    std::string mime = sidecar.mimeType();
    EXPECT_EQ(mime, "application/rdf+xml");
}

// Test that good() returns true after construction with create=false on empty MemIo
TEST_F(XmpSidecarTest_2204, GoodAfterConstruction_2204) {
    auto io = std::make_unique<MemIo>();
    XmpSidecar sidecar(std::move(io), false);

    // MemIo should be in a good state
    EXPECT_TRUE(sidecar.good());
}

// Test that imageType returns xmp
TEST_F(XmpSidecarTest_2204, ImageTypeIsXmp_2204) {
    auto io = createMemIo();
    XmpSidecar sidecar(std::move(io), false);

    EXPECT_EQ(sidecar.imageType(), ImageType::xmp);
}

// Test that XmpData can be set and retrieved
TEST_F(XmpSidecarTest_2204, SetAndGetXmpData_2204) {
    auto io = createMemIo();
    XmpSidecar sidecar(std::move(io), false);

    XmpData xmpData;
    sidecar.setXmpData(xmpData);
    EXPECT_TRUE(sidecar.xmpData().empty());
}

// Test that clearXmpData works
TEST_F(XmpSidecarTest_2204, ClearXmpData_2204) {
    auto io = createMemIo();
    XmpSidecar sidecar(std::move(io), false);

    sidecar.clearXmpData();
    EXPECT_TRUE(sidecar.xmpData().empty());
}

// Test setComment override
TEST_F(XmpSidecarTest_2204, SetCommentDoesNotThrow_2204) {
    auto io = createMemIo();
    XmpSidecar sidecar(std::move(io), false);

    ASSERT_NO_THROW(sidecar.setComment("test comment"));
}

// Test that comment returns empty by default
TEST_F(XmpSidecarTest_2204, DefaultCommentIsEmpty_2204) {
    auto io = createMemIo();
    XmpSidecar sidecar(std::move(io), false);

    EXPECT_TRUE(sidecar.comment().empty());
}

// Test the XML header content written when create=true
TEST_F(XmpSidecarTest_2204, CreateTrueWritesCorrectHeaderContent_2204) {
    auto io = std::make_unique<MemIo>();
    XmpSidecar sidecar(std::move(io), true);

    const BasicIo& sidecarIo = sidecar.io();
    // The header is: <?xpacket begin="\xef\xbb\xbf" id="W5M0MpCehiHzreSzNTczkc9d"?>\n
    // which is 54 bytes (55 - 1 for null terminator)
    EXPECT_EQ(sidecarIo.size(), 54u);
}

// Test reading the written header data
TEST_F(XmpSidecarTest_2204, CreateTrueHeaderDataIsReadable_2204) {
    auto memIo = std::make_unique<MemIo>();
    MemIo* rawPtr = memIo.get();
    XmpSidecar sidecar(std::move(memIo), true);

    // Open and read back the data
    rawPtr->open();
    rawPtr->seek(0, BasicIo::beg);
    DataBuf buf = rawPtr->read(rawPtr->size());
    rawPtr->close();

    EXPECT_GT(buf.size(), 0u);

    // Check it starts with "<?xpacket"
    std::string content(reinterpret_cast<const char*>(buf.c_data()), buf.size());
    EXPECT_TRUE(content.find("<?xpacket") == 0);
}

// Test clearMetadata
TEST_F(XmpSidecarTest_2204, ClearMetadata_2204) {
    auto io = createMemIo();
    XmpSidecar sidecar(std::move(io), false);

    ASSERT_NO_THROW(sidecar.clearMetadata());
    EXPECT_TRUE(sidecar.xmpData().empty());
    EXPECT_TRUE(sidecar.exifData().empty());
    EXPECT_TRUE(sidecar.iptcData().empty());
}

// Test that xmpPacket is accessible
TEST_F(XmpSidecarTest_2204, XmpPacketAccessible_2204) {
    auto io = createMemIo();
    XmpSidecar sidecar(std::move(io), false);

    std::string& packet = sidecar.xmpPacket();
    EXPECT_TRUE(packet.empty());
}

// Test supportsMetadata for XMP
TEST_F(XmpSidecarTest_2204, SupportsXmpMetadata_2204) {
    auto io = createMemIo();
    XmpSidecar sidecar(std::move(io), false);

    EXPECT_TRUE(sidecar.supportsMetadata(mdXmp));
}

// Test that pixelWidth and pixelHeight default to 0
TEST_F(XmpSidecarTest_2204, DefaultPixelDimensionsAreZero_2204) {
    auto io = createMemIo();
    XmpSidecar sidecar(std::move(io), false);

    EXPECT_EQ(sidecar.pixelWidth(), 0u);
    EXPECT_EQ(sidecar.pixelHeight(), 0u);
}

// Test readMetadata on valid XMP content
TEST_F(XmpSidecarTest_2204, ReadMetadataOnValidXmp_2204) {
    std::string xmpContent =
        "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>\n"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">\n"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
        "</rdf:RDF>\n"
        "</x:xmpmeta>\n"
        "<?xpacket end=\"w\"?>";

    auto io = std::make_unique<MemIo>(
        reinterpret_cast<const byte*>(xmpContent.c_str()), xmpContent.size());

    XmpSidecar sidecar(std::move(io), false);
    ASSERT_NO_THROW(sidecar.readMetadata());
}

// Test readMetadata on empty IO
TEST_F(XmpSidecarTest_2204, ReadMetadataOnEmptyIo_2204) {
    auto io = std::make_unique<MemIo>();
    XmpSidecar sidecar(std::move(io), false);

    // Reading metadata from empty io - behavior depends on implementation
    // but should not crash
    try {
        sidecar.readMetadata();
    } catch (const Error&) {
        // Expected - empty IO may throw
    }
}

// Test writeMetadata on empty sidecar
TEST_F(XmpSidecarTest_2204, WriteMetadataOnEmptySidecar_2204) {
    auto io = std::make_unique<MemIo>();
    XmpSidecar sidecar(std::move(io), true);

    // Writing empty metadata should not crash
    ASSERT_NO_THROW(sidecar.writeMetadata());
}

// Test the dates_ dictionary is accessible
TEST_F(XmpSidecarTest_2204, DatesDictionaryIsAccessible_2204) {
    auto io = createMemIo();
    XmpSidecar sidecar(std::move(io), false);

    // dates_ is a public member
    EXPECT_TRUE(sidecar.dates_.empty());
}

// Test that writeXmpFromPacket flag can be set
TEST_F(XmpSidecarTest_2204, WriteXmpFromPacketFlag_2204) {
    auto io = createMemIo();
    XmpSidecar sidecar(std::move(io), false);

    sidecar.writeXmpFromPacket(true);
    EXPECT_TRUE(sidecar.writeXmpFromPacket());

    sidecar.writeXmpFromPacket(false);
    EXPECT_FALSE(sidecar.writeXmpFromPacket());
}

// Test io() accessor returns valid reference
TEST_F(XmpSidecarTest_2204, IoAccessorReturnsValidReference_2204) {
    auto io = std::make_unique<MemIo>();
    XmpSidecar sidecar(std::move(io), false);

    const BasicIo& ref = sidecar.io();
    EXPECT_EQ(ref.size(), 0u);
}

// Test clearXmpPacket
TEST_F(XmpSidecarTest_2204, ClearXmpPacket_2204) {
    auto io = createMemIo();
    XmpSidecar sidecar(std::move(io), false);

    sidecar.setXmpPacket("<some_xmp_data/>");
    EXPECT_FALSE(sidecar.xmpPacket().empty());

    sidecar.clearXmpPacket();
    EXPECT_TRUE(sidecar.xmpPacket().empty());
}

// Test nativePreviews is accessible and empty by default
TEST_F(XmpSidecarTest_2204, NativePreviewsEmptyByDefault_2204) {
    auto io = createMemIo();
    XmpSidecar sidecar(std::move(io), false);

    EXPECT_TRUE(sidecar.nativePreviews().empty());
}
