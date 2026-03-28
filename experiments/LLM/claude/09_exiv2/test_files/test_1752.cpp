#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/epsimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <fstream>
#include <cstdio>
#include <memory>

namespace {

// Helper to create a minimal valid EPS file content
std::string getMinimalEpsContent() {
    return "%!PS-Adobe-3.0 EPSF-3.0\n"
           "%%BoundingBox: 0 0 100 100\n"
           "%%EndComments\n"
           "%%EOF\n";
}

// Helper to create a temporary file with given content and return its path
std::string createTempFile(const std::string& content, const std::string& suffix = ".eps") {
    std::string path = std::tmpnam(nullptr);
    path += suffix;
    std::ofstream ofs(path, std::ios::binary);
    ofs << content;
    ofs.close();
    return path;
}

class EpsImageTest_1752 : public ::testing::Test {
protected:
    void TearDown() override {
        for (const auto& f : tempFiles_) {
            std::remove(f.c_str());
        }
    }

    void trackFile(const std::string& path) {
        tempFiles_.push_back(path);
    }

    std::vector<std::string> tempFiles_;
};

// Test that mimeType returns the correct MIME type for EPS
TEST_F(EpsImageTest_1752, MimeTypeReturnsPostscript_1752) {
    std::string content = getMinimalEpsContent();
    std::string path = createTempFile(content);
    trackFile(path);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    EXPECT_EQ(img.mimeType(), "application/postscript");
}

// Test creating an EpsImage with create=false on valid EPS content
TEST_F(EpsImageTest_1752, ConstructWithExistingFile_1752) {
    std::string content = getMinimalEpsContent();
    std::string path = createTempFile(content);
    trackFile(path);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    EXPECT_NO_THROW(Exiv2::EpsImage img(std::move(io), false));
}

// Test creating an EpsImage with create=true
TEST_F(EpsImageTest_1752, ConstructWithCreateTrue_1752) {
    std::string path = std::tmpnam(nullptr);
    path += ".eps";
    trackFile(path);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    EXPECT_NO_THROW(Exiv2::EpsImage img(std::move(io), true));
}

// Test that setComment throws (EPS typically doesn't support comments this way)
TEST_F(EpsImageTest_1752, SetCommentThrows_1752) {
    std::string content = getMinimalEpsContent();
    std::string path = createTempFile(content);
    trackFile(path);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    EXPECT_THROW(img.setComment("test comment"), Exiv2::Error);
}

// Test readMetadata on a minimal valid EPS file
TEST_F(EpsImageTest_1752, ReadMetadataOnMinimalEps_1752) {
    std::string content = getMinimalEpsContent();
    std::string path = createTempFile(content);
    trackFile(path);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    EXPECT_NO_THROW(img.readMetadata());
}

// Test readMetadata on an empty file (should throw or error)
TEST_F(EpsImageTest_1752, ReadMetadataOnEmptyFile_1752) {
    std::string path = createTempFile("");
    trackFile(path);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test readMetadata on invalid content (not EPS)
TEST_F(EpsImageTest_1752, ReadMetadataOnInvalidContent_1752) {
    std::string content = "This is not an EPS file at all.";
    std::string path = createTempFile(content);
    trackFile(path);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test writeMetadata on a minimal valid EPS file
TEST_F(EpsImageTest_1752, WriteMetadataOnMinimalEps_1752) {
    std::string content = getMinimalEpsContent();
    std::string path = createTempFile(content);
    trackFile(path);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    img.readMetadata();
    EXPECT_NO_THROW(img.writeMetadata());
}

// Test writeMetadata on empty/invalid file
TEST_F(EpsImageTest_1752, WriteMetadataOnEmptyFileThrows_1752) {
    std::string path = createTempFile("");
    trackFile(path);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    EXPECT_THROW(img.writeMetadata(), Exiv2::Error);
}

// Test that mimeType is consistent across multiple calls
TEST_F(EpsImageTest_1752, MimeTypeConsistency_1752) {
    std::string content = getMinimalEpsContent();
    std::string path = createTempFile(content);
    trackFile(path);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    std::string mt1 = img.mimeType();
    std::string mt2 = img.mimeType();
    EXPECT_EQ(mt1, mt2);
    EXPECT_EQ(mt1, "application/postscript");
}

// Test with MemIo containing valid EPS data
TEST_F(EpsImageTest_1752, ConstructWithMemIo_1752) {
    std::string content = getMinimalEpsContent();
    auto io = std::make_unique<Exiv2::MemIo>(
        reinterpret_cast<const uint8_t*>(content.data()), content.size());

    Exiv2::EpsImage img(std::move(io), false);
    EXPECT_EQ(img.mimeType(), "application/postscript");
}

// Test readMetadata with MemIo containing valid EPS
TEST_F(EpsImageTest_1752, ReadMetadataWithMemIo_1752) {
    std::string content = getMinimalEpsContent();
    auto io = std::make_unique<Exiv2::MemIo>(
        reinterpret_cast<const uint8_t*>(content.data()), content.size());

    Exiv2::EpsImage img(std::move(io), false);
    EXPECT_NO_THROW(img.readMetadata());
}

// Test readMetadata with MemIo containing invalid data
TEST_F(EpsImageTest_1752, ReadMetadataWithInvalidMemIo_1752) {
    std::string content = "INVALID DATA";
    auto io = std::make_unique<Exiv2::MemIo>(
        reinterpret_cast<const uint8_t*>(content.data()), content.size());

    Exiv2::EpsImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test with EPS content that has XMP metadata embedded
TEST_F(EpsImageTest_1752, ReadMetadataWithXmp_1752) {
    std::string content =
        "%!PS-Adobe-3.0 EPSF-3.0\n"
        "%%BoundingBox: 0 0 100 100\n"
        "%%EndComments\n"
        "%begin_xml_packet: 100\n"
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>\n"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
        "</x:xmpmeta>\n"
        "<?xpacket end='w'?>\n"
        "%end_xml_packet\n"
        "%%EOF\n";

    std::string path = createTempFile(content);
    trackFile(path);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    EXPECT_NO_THROW(img.readMetadata());
}

// Test that setComment with empty string also throws
TEST_F(EpsImageTest_1752, SetEmptyCommentThrows_1752) {
    std::string content = getMinimalEpsContent();
    std::string path = createTempFile(content);
    trackFile(path);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::EpsImage img(std::move(io), false);

    EXPECT_THROW(img.setComment(""), Exiv2::Error);
}

}  // namespace
