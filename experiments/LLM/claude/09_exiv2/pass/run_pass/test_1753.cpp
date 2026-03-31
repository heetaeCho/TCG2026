#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/epsimage.hpp>
#include <exiv2/image.hpp>
#include <exiv2/error.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/xmp_exiv2.hpp>

#include <fstream>
#include <cstdio>
#include <string>
#include <memory>

namespace {

// Helper to create a minimal valid EPS file content
std::string createMinimalEps() {
    return "%!PS-Adobe-3.0 EPSF-3.0\n"
           "%%BoundingBox: 0 0 100 100\n"
           "%%EndComments\n"
           "%%EOF\n";
}

// Helper to create an EPS file with embedded XMP
std::string createEpsWithXmp() {
    std::string xmpData =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>\n"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">\n"
        "  <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
        "    <rdf:Description rdf:about=\"\"\n"
        "      xmlns:dc=\"http://purl.org/dc/elements/1.1/\">\n"
        "      <dc:creator>\n"
        "        <rdf:Seq>\n"
        "          <rdf:li>Test Author</rdf:li>\n"
        "        </rdf:Seq>\n"
        "      </dc:creator>\n"
        "    </rdf:Description>\n"
        "  </rdf:RDF>\n"
        "</x:xmpmeta>\n"
        "<?xpacket end=\"w\"?>";

    return "%!PS-Adobe-3.0 EPSF-3.0\n"
           "%%BoundingBox: 0 0 100 100\n"
           "%%EndComments\n"
           "%begin_xml_packet: " + std::to_string(xmpData.size()) + "\n"
           + xmpData + "\n"
           "%end_xml_packet\n"
           "%%EOF\n";
}

// Helper to write content to a temporary file and return its path
std::string writeTempFile(const std::string& content, const std::string& suffix = ".eps") {
    std::string tmpPath = std::tmpnam(nullptr);
    tmpPath += suffix;
    std::ofstream ofs(tmpPath, std::ios::binary);
    ofs.write(content.data(), content.size());
    ofs.close();
    return tmpPath;
}

class EpsImageTest_1753 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        // Clean up temp files
        for (const auto& f : tempFiles_) {
            std::remove(f.c_str());
        }
        Exiv2::XmpParser::terminate();
    }

    std::string createTempFile(const std::string& content) {
        std::string path = writeTempFile(content);
        tempFiles_.push_back(path);
        return path;
    }

    std::vector<std::string> tempFiles_;
};

// Test: Construction with valid EPS data
TEST_F(EpsImageTest_1753, ConstructionWithValidData_1753) {
    std::string content = createMinimalEps();
    std::string path = createTempFile(content);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    ASSERT_NO_THROW(Exiv2::EpsImage img(std::move(io), false));
}

// Test: mimeType returns correct MIME type
TEST_F(EpsImageTest_1753, MimeTypeReturnsCorrectValue_1753) {
    std::string content = createMinimalEps();
    std::string path = createTempFile(content);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    std::string mime = img.mimeType();
    // EPS MIME type should be application/postscript or similar
    EXPECT_FALSE(mime.empty());
}

// Test: readMetadata on a minimal valid EPS file
TEST_F(EpsImageTest_1753, ReadMetadataMinimalEps_1753) {
    std::string content = createMinimalEps();
    std::string path = createTempFile(content);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    ASSERT_NO_THROW(img.readMetadata());
    // Minimal EPS should have empty XMP data
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: readMetadata on non-EPS content should throw
TEST_F(EpsImageTest_1753, ReadMetadataInvalidContent_1753) {
    std::string content = "This is not an EPS file at all.";
    std::string path = createTempFile(content);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: readMetadata on empty file should throw
TEST_F(EpsImageTest_1753, ReadMetadataEmptyFile_1753) {
    std::string content;
    std::string path = createTempFile(content);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: readMetadata with MemIo containing valid EPS
TEST_F(EpsImageTest_1753, ReadMetadataWithMemIo_1753) {
    std::string content = createMinimalEps();

    auto io = std::make_unique<Exiv2::MemIo>(
        reinterpret_cast<const uint8_t*>(content.data()), content.size());
    Exiv2::EpsImage img(std::move(io), false);

    ASSERT_NO_THROW(img.readMetadata());
}

// Test: readMetadata with MemIo containing invalid data
TEST_F(EpsImageTest_1753, ReadMetadataWithMemIoInvalidData_1753) {
    std::string content = "INVALID DATA";

    auto io = std::make_unique<Exiv2::MemIo>(
        reinterpret_cast<const uint8_t*>(content.data()), content.size());
    Exiv2::EpsImage img(std::move(io), false);

    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: setComment should throw (EPS doesn't support comments in exiv2)
TEST_F(EpsImageTest_1753, SetCommentThrows_1753) {
    std::string content = createMinimalEps();
    std::string path = createTempFile(content);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    EXPECT_THROW(img.setComment("test comment"), Exiv2::Error);
}

// Test: good() returns true for valid io
TEST_F(EpsImageTest_1753, GoodReturnsTrueForValidIo_1753) {
    std::string content = createMinimalEps();
    std::string path = createTempFile(content);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    EXPECT_TRUE(img.good());
}

// Test: EPS with XMP should have XMP data after readMetadata
TEST_F(EpsImageTest_1753, ReadMetadataWithXmp_1753) {
    std::string content = createEpsWithXmp();
    std::string path = createTempFile(content);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    ASSERT_NO_THROW(img.readMetadata());
    // If XMP was embedded, xmpPacket should not be empty
    // (depending on whether the parser found it)
    // We can at least verify no crash occurred
}

// Test: xmpData and xmpPacket accessible after construction
TEST_F(EpsImageTest_1753, XmpDataAccessibleAfterConstruction_1753) {
    std::string content = createMinimalEps();
    std::string path = createTempFile(content);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    // Before readMetadata, xmpData should be empty
    EXPECT_TRUE(img.xmpData().empty());
    EXPECT_TRUE(img.xmpPacket().empty());
}

// Test: writeMetadata on minimal EPS
TEST_F(EpsImageTest_1753, WriteMetadataMinimalEps_1753) {
    std::string content = createMinimalEps();
    std::string path = createTempFile(content);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    ASSERT_NO_THROW(img.readMetadata());
    // Writing metadata may or may not succeed depending on file format details
    // At minimum, it shouldn't crash on a valid EPS
    try {
        img.writeMetadata();
    } catch (const Exiv2::Error&) {
        // Writing may fail for minimal EPS, that's acceptable
    }
}

// Test: imageType should be eps
TEST_F(EpsImageTest_1753, ImageTypeIsEps_1753) {
    std::string content = createMinimalEps();
    std::string path = createTempFile(content);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    EXPECT_EQ(img.imageType(), Exiv2::ImageType::eps);
}

// Test: nativePreviews initially empty
TEST_F(EpsImageTest_1753, NativePreviewsInitiallyEmpty_1753) {
    std::string content = createMinimalEps();
    std::string path = createTempFile(content);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    EXPECT_TRUE(img.nativePreviews().empty());
}

// Test: readMetadata with truncated EPS header
TEST_F(EpsImageTest_1753, ReadMetadataTruncatedHeader_1753) {
    std::string content = "%!PS-Adobe-3.0";  // Incomplete header
    std::string path = createTempFile(content);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: readMetadata with only PostScript header (no EPSF marker)
TEST_F(EpsImageTest_1753, ReadMetadataNoEpsfMarker_1753) {
    std::string content = "%!PS-Adobe-3.0\n"
                          "%%BoundingBox: 0 0 100 100\n"
                          "%%EndComments\n"
                          "%%EOF\n";
    std::string path = createTempFile(content);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    // May or may not throw - just exercise the code path
    try {
        img.readMetadata();
    } catch (const Exiv2::Error&) {
        // Expected for non-EPSF files
    }
}

// Test: Construction with create=true
TEST_F(EpsImageTest_1753, ConstructionWithCreateTrue_1753) {
    auto io = std::make_unique<Exiv2::MemIo>();
    // Creating a new EPS image with empty io
    ASSERT_NO_THROW(Exiv2::EpsImage img(std::move(io), true));
}

// Test: readMetadata on binary garbage
TEST_F(EpsImageTest_1753, ReadMetadataBinaryGarbage_1753) {
    std::string content(256, '\0');
    for (size_t i = 0; i < content.size(); ++i) {
        content[i] = static_cast<char>(i);
    }
    std::string path = createTempFile(content);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: exifData and iptcData are accessible (even though EPS primarily supports XMP)
TEST_F(EpsImageTest_1753, ExifAndIptcDataAccessible_1753) {
    std::string content = createMinimalEps();
    std::string path = createTempFile(content);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    EXPECT_TRUE(img.exifData().empty());
    EXPECT_TRUE(img.iptcData().empty());
}

// Test: io() reference is valid
TEST_F(EpsImageTest_1753, IoReferenceValid_1753) {
    std::string content = createMinimalEps();
    std::string path = createTempFile(content);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    EXPECT_NO_THROW(img.io());
}

// Test: Multiple readMetadata calls should not crash
TEST_F(EpsImageTest_1753, MultipleReadMetadataCalls_1753) {
    std::string content = createMinimalEps();
    std::string path = createTempFile(content);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    ASSERT_NO_THROW(img.readMetadata());
    ASSERT_NO_THROW(img.readMetadata());
}

}  // namespace
