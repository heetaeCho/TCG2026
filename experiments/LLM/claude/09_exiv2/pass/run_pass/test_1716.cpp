#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/xmpsidecar.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/image.hpp>
#include <memory>
#include <fstream>
#include <cstdio>
#include <string>

using namespace Exiv2;

namespace {

// Helper to create a temporary file with given content
class TempFile {
public:
    explicit TempFile(const std::string& filename, const std::string& content = "")
        : filename_(filename) {
        std::ofstream ofs(filename_, std::ios::binary);
        if (!content.empty()) {
            ofs.write(content.data(), content.size());
        }
        ofs.close();
    }
    ~TempFile() {
        std::remove(filename_.c_str());
    }
    const std::string& path() const { return filename_; }
private:
    std::string filename_;
};

// A minimal valid XMP sidecar content
const std::string kValidXmpContent =
    "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>\n"
    "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">\n"
    " <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
    "  <rdf:Description rdf:about=\"\"\n"
    "    xmlns:xmp=\"http://ns.adobe.com/xap/1.0/\"\n"
    "    xmp:CreateDate=\"2023-01-15T10:30:00\"/>\n"
    " </rdf:RDF>\n"
    "</x:xmpmeta>\n"
    "<?xpacket end=\"w\"?>";

const std::string kMinimalXmpContent =
    "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>\n"
    "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">\n"
    " <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
    "  <rdf:Description rdf:about=\"\"/>\n"
    " </rdf:RDF>\n"
    "</x:xmpmeta>\n"
    "<?xpacket end=\"w\"?>";

} // anonymous namespace

class XmpSidecarTest_1716 : public ::testing::Test {
protected:
    void SetUp() override {
        XmpParser::initialize();
    }
    void TearDown() override {
        XmpParser::terminate();
    }
};

// Test: mimeType returns the correct MIME type for XMP sidecar
TEST_F(XmpSidecarTest_1716, MimeTypeReturnsCorrectType_1716) {
    TempFile tmp("test_mime_1716.xmp", kMinimalXmpContent);
    auto io = std::make_unique<FileIo>(tmp.path());
    XmpSidecar sidecar(std::move(io), false);
    EXPECT_EQ(sidecar.mimeType(), "application/rdf+xml");
}

// Test: Reading metadata from a valid XMP file succeeds
TEST_F(XmpSidecarTest_1716, ReadMetadataValidXmpFile_1716) {
    TempFile tmp("test_valid_1716.xmp", kValidXmpContent);
    auto io = std::make_unique<FileIo>(tmp.path());
    XmpSidecar sidecar(std::move(io), false);
    EXPECT_NO_THROW(sidecar.readMetadata());
    // After reading, xmpData should not be empty for valid XMP with content
    EXPECT_FALSE(sidecar.xmpData().empty());
}

// Test: Reading metadata from a minimal valid XMP file succeeds
TEST_F(XmpSidecarTest_1716, ReadMetadataMinimalXmpFile_1716) {
    TempFile tmp("test_minimal_1716.xmp", kMinimalXmpContent);
    auto io = std::make_unique<FileIo>(tmp.path());
    XmpSidecar sidecar(std::move(io), false);
    EXPECT_NO_THROW(sidecar.readMetadata());
}

// Test: Reading metadata from a non-existent file throws an error
TEST_F(XmpSidecarTest_1716, ReadMetadataNonExistentFileThrows_1716) {
    auto io = std::make_unique<FileIo>("nonexistent_file_1716.xmp");
    XmpSidecar sidecar(std::move(io), false);
    EXPECT_THROW(sidecar.readMetadata(), Error);
}

// Test: Reading metadata from a file with non-XMP content throws
TEST_F(XmpSidecarTest_1716, ReadMetadataNotXmpContentThrows_1716) {
    TempFile tmp("test_notxmp_1716.xmp", "This is not XMP content at all");
    auto io = std::make_unique<FileIo>(tmp.path());
    XmpSidecar sidecar(std::move(io), false);
    EXPECT_THROW(sidecar.readMetadata(), Error);
}

// Test: Reading metadata from an empty file throws
TEST_F(XmpSidecarTest_1716, ReadMetadataEmptyFileThrows_1716) {
    TempFile tmp("test_empty_1716.xmp", "");
    auto io = std::make_unique<FileIo>(tmp.path());
    XmpSidecar sidecar(std::move(io), false);
    EXPECT_THROW(sidecar.readMetadata(), Error);
}

// Test: XMP with date fields populates the dates_ dictionary
TEST_F(XmpSidecarTest_1716, ReadMetadataPopulatesDates_1716) {
    TempFile tmp("test_dates_1716.xmp", kValidXmpContent);
    auto io = std::make_unique<FileIo>(tmp.path());
    XmpSidecar sidecar(std::move(io), false);
    sidecar.readMetadata();

    // The valid XMP content contains xmp:CreateDate, so dates_ should have entries
    // with keys containing "Date"
    bool foundDate = false;
    for (const auto& entry : sidecar.dates_) {
        if (entry.first.find("Date") != std::string::npos) {
            foundDate = true;
            break;
        }
    }
    EXPECT_TRUE(foundDate);
}

// Test: setComment is a no-op (or at least doesn't crash)
TEST_F(XmpSidecarTest_1716, SetCommentDoesNotThrow_1716) {
    TempFile tmp("test_comment_1716.xmp", kMinimalXmpContent);
    auto io = std::make_unique<FileIo>(tmp.path());
    XmpSidecar sidecar(std::move(io), false);
    EXPECT_NO_THROW(sidecar.setComment("Some comment"));
}

// Test: Reading metadata clears previous metadata
TEST_F(XmpSidecarTest_1716, ReadMetadataClearsPreviousData_1716) {
    TempFile tmp("test_clear_1716.xmp", kMinimalXmpContent);
    auto io = std::make_unique<FileIo>(tmp.path());
    XmpSidecar sidecar(std::move(io), false);

    // Read twice to verify it clears and re-reads
    EXPECT_NO_THROW(sidecar.readMetadata());
    EXPECT_NO_THROW(sidecar.readMetadata());
}

// Test: Writing metadata to a valid file
TEST_F(XmpSidecarTest_1716, WriteMetadataValidFile_1716) {
    TempFile tmp("test_write_1716.xmp", kMinimalXmpContent);
    auto io = std::make_unique<FileIo>(tmp.path());
    XmpSidecar sidecar(std::move(io), false);
    sidecar.readMetadata();
    EXPECT_NO_THROW(sidecar.writeMetadata());
}

// Test: Create XmpSidecar with create=true
TEST_F(XmpSidecarTest_1716, CreateNewXmpSidecar_1716) {
    std::string filename = "test_create_1716.xmp";
    // Remove if exists
    std::remove(filename.c_str());
    auto io = std::make_unique<FileIo>(filename);
    XmpSidecar sidecar(std::move(io), true);
    // Should be able to write to create a new file
    EXPECT_NO_THROW(sidecar.writeMetadata());
    std::remove(filename.c_str());
}

// Test: XMP packet is populated after reading
TEST_F(XmpSidecarTest_1716, XmpPacketPopulatedAfterRead_1716) {
    TempFile tmp("test_packet_1716.xmp", kValidXmpContent);
    auto io = std::make_unique<FileIo>(tmp.path());
    XmpSidecar sidecar(std::move(io), false);
    sidecar.readMetadata();
    EXPECT_FALSE(sidecar.xmpPacket().empty());
}

// Test: good() returns true for a properly initialized sidecar
TEST_F(XmpSidecarTest_1716, GoodReturnsTrueForValidIo_1716) {
    TempFile tmp("test_good_1716.xmp", kMinimalXmpContent);
    auto io = std::make_unique<FileIo>(tmp.path());
    XmpSidecar sidecar(std::move(io), false);
    EXPECT_TRUE(sidecar.good());
}

// Test: Reading a binary/garbage file that starts with something that
// looks like it might be detected as non-XMP
TEST_F(XmpSidecarTest_1716, ReadMetadataBinaryGarbageThrows_1716) {
    std::string garbage(256, '\0');
    for (int i = 0; i < 256; ++i) garbage[i] = static_cast<char>(i);
    TempFile tmp("test_garbage_1716.xmp", garbage);
    auto io = std::make_unique<FileIo>(tmp.path());
    XmpSidecar sidecar(std::move(io), false);
    EXPECT_THROW(sidecar.readMetadata(), Error);
}

// Test: Large XMP file (beyond single 64K buffer read)
TEST_F(XmpSidecarTest_1716, ReadMetadataLargeXmpFile_1716) {
    // Create a large XMP file with lots of padding
    std::string largeXmp =
        "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>\n"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">\n"
        " <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
        "  <rdf:Description rdf:about=\"\"/>\n"
        " </rdf:RDF>\n"
        "</x:xmpmeta>\n";
    // Add whitespace padding to exceed 64K
    largeXmp += std::string(70000, ' ');
    largeXmp += "\n<?xpacket end=\"w\"?>";

    TempFile tmp("test_large_1716.xmp", largeXmp);
    auto io = std::make_unique<FileIo>(tmp.path());
    XmpSidecar sidecar(std::move(io), false);
    EXPECT_NO_THROW(sidecar.readMetadata());
}

// Test: XMP with multiple date fields
TEST_F(XmpSidecarTest_1716, ReadMetadataMultipleDateFields_1716) {
    std::string xmpMultiDates =
        "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>\n"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">\n"
        " <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
        "  <rdf:Description rdf:about=\"\"\n"
        "    xmlns:xmp=\"http://ns.adobe.com/xap/1.0/\"\n"
        "    xmp:CreateDate=\"2023-01-15T10:30:00\"\n"
        "    xmp:ModifyDate=\"2023-06-20T15:45:00\"/>\n"
        " </rdf:RDF>\n"
        "</x:xmpmeta>\n"
        "<?xpacket end=\"w\"?>";

    TempFile tmp("test_multidates_1716.xmp", xmpMultiDates);
    auto io = std::make_unique<FileIo>(tmp.path());
    XmpSidecar sidecar(std::move(io), false);
    sidecar.readMetadata();

    // Should have at least 2 date entries
    int dateCount = 0;
    for (const auto& entry : sidecar.dates_) {
        if (entry.first.find("Date") != std::string::npos) {
            dateCount++;
        }
    }
    EXPECT_GE(dateCount, 2);
}

// Test: MemIo-based XMP sidecar with valid content
TEST_F(XmpSidecarTest_1716, ReadMetadataFromMemIo_1716) {
    const byte* data = reinterpret_cast<const byte*>(kValidXmpContent.data());
    auto io = std::make_unique<MemIo>(data, kValidXmpContent.size());
    XmpSidecar sidecar(std::move(io), false);
    EXPECT_NO_THROW(sidecar.readMetadata());
    EXPECT_FALSE(sidecar.xmpData().empty());
}

// Test: MemIo-based XMP sidecar with empty content throws
TEST_F(XmpSidecarTest_1716, ReadMetadataFromEmptyMemIoThrows_1716) {
    auto io = std::make_unique<MemIo>();
    XmpSidecar sidecar(std::move(io), false);
    EXPECT_THROW(sidecar.readMetadata(), Error);
}

// Test: After reading valid XMP, exifData may be populated via XMP-to-Exif conversion
TEST_F(XmpSidecarTest_1716, ReadMetadataExifDataMayBePopulated_1716) {
    TempFile tmp("test_exif_1716.xmp", kValidXmpContent);
    auto io = std::make_unique<FileIo>(tmp.path());
    XmpSidecar sidecar(std::move(io), false);
    sidecar.readMetadata();
    // Just verify the method doesn't crash; exifData may or may not have entries
    // depending on XMP-to-Exif mapping
    sidecar.exifData();
}

// Test: After reading valid XMP, iptcData is accessible
TEST_F(XmpSidecarTest_1716, ReadMetadataIptcDataAccessible_1716) {
    TempFile tmp("test_iptc_1716.xmp", kValidXmpContent);
    auto io = std::make_unique<FileIo>(tmp.path());
    XmpSidecar sidecar(std::move(io), false);
    sidecar.readMetadata();
    // Just verify the method doesn't crash
    sidecar.iptcData();
}
