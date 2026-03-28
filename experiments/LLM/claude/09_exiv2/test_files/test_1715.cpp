#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

// Include necessary headers
#include "exiv2/xmpsidecar.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/image.hpp"

namespace {

class XmpSidecarTest_1715 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<Exiv2::XmpSidecar> createXmpSidecar(const std::string& content = "", bool create = true) {
        auto io = std::make_unique<Exiv2::MemIo>();
        if (!content.empty()) {
            io->write(reinterpret_cast<const Exiv2::byte*>(content.data()), content.size());
            io->seek(0, Exiv2::BasicIo::beg);
        }
        return std::make_unique<Exiv2::XmpSidecar>(std::move(io), create);
    }
};

// Test that mimeType returns the correct MIME type
TEST_F(XmpSidecarTest_1715, MimeTypeReturnsCorrectValue_1715) {
    auto sidecar = createXmpSidecar();
    EXPECT_EQ(sidecar->mimeType(), "application/rdf+xml");
}

// Test that mimeType is consistent across multiple calls
TEST_F(XmpSidecarTest_1715, MimeTypeIsConsistent_1715) {
    auto sidecar = createXmpSidecar();
    std::string first = sidecar->mimeType();
    std::string second = sidecar->mimeType();
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, "application/rdf+xml");
}

// Test creating XmpSidecar with create=true (new file)
TEST_F(XmpSidecarTest_1715, CreateWithCreateFlagTrue_1715) {
    auto io = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW(Exiv2::XmpSidecar(std::move(io), true));
}

// Test creating XmpSidecar with create=false
TEST_F(XmpSidecarTest_1715, CreateWithCreateFlagFalse_1715) {
    auto io = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW(Exiv2::XmpSidecar(std::move(io), false));
}

// Test setComment does not throw
TEST_F(XmpSidecarTest_1715, SetCommentDoesNotThrow_1715) {
    auto sidecar = createXmpSidecar();
    EXPECT_NO_THROW(sidecar->setComment("test comment"));
}

// Test setComment with empty string
TEST_F(XmpSidecarTest_1715, SetCommentWithEmptyString_1715) {
    auto sidecar = createXmpSidecar();
    EXPECT_NO_THROW(sidecar->setComment(""));
}

// Test setComment with long string
TEST_F(XmpSidecarTest_1715, SetCommentWithLongString_1715) {
    auto sidecar = createXmpSidecar();
    std::string longComment(10000, 'x');
    EXPECT_NO_THROW(sidecar->setComment(longComment));
}

// Test readMetadata on empty file created with create=true
TEST_F(XmpSidecarTest_1715, ReadMetadataOnNewlyCreatedFile_1715) {
    auto sidecar = createXmpSidecar("", true);
    EXPECT_NO_THROW(sidecar->readMetadata());
}

// Test writeMetadata on newly created sidecar
TEST_F(XmpSidecarTest_1715, WriteMetadataOnNewlyCreatedFile_1715) {
    auto sidecar = createXmpSidecar("", true);
    EXPECT_NO_THROW(sidecar->writeMetadata());
}

// Test readMetadata with valid XMP content
TEST_F(XmpSidecarTest_1715, ReadMetadataWithValidXmpContent_1715) {
    std::string validXmp =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">\n"
        " <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
        "  <rdf:Description rdf:about=\"\"\n"
        "    xmlns:dc=\"http://purl.org/dc/elements/1.1/\">\n"
        "   <dc:description>Test</dc:description>\n"
        "  </rdf:Description>\n"
        " </rdf:RDF>\n"
        "</x:xmpmeta>\n";
    auto sidecar = createXmpSidecar(validXmp, false);
    EXPECT_NO_THROW(sidecar->readMetadata());
}

// Test write after read round-trip
TEST_F(XmpSidecarTest_1715, ReadThenWriteMetadata_1715) {
    std::string validXmp =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">\n"
        " <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
        "  <rdf:Description rdf:about=\"\"\n"
        "    xmlns:dc=\"http://purl.org/dc/elements/1.1/\">\n"
        "   <dc:description>Test</dc:description>\n"
        "  </rdf:Description>\n"
        " </rdf:RDF>\n"
        "</x:xmpmeta>\n";
    auto sidecar = createXmpSidecar(validXmp, false);
    EXPECT_NO_THROW(sidecar->readMetadata());
    EXPECT_NO_THROW(sidecar->writeMetadata());
}

// Test that mimeType does not change after operations
TEST_F(XmpSidecarTest_1715, MimeTypeUnchangedAfterReadWrite_1715) {
    auto sidecar = createXmpSidecar("", true);
    EXPECT_EQ(sidecar->mimeType(), "application/rdf+xml");
    sidecar->writeMetadata();
    EXPECT_EQ(sidecar->mimeType(), "application/rdf+xml");
}

// Test setComment with special characters
TEST_F(XmpSidecarTest_1715, SetCommentWithSpecialCharacters_1715) {
    auto sidecar = createXmpSidecar();
    EXPECT_NO_THROW(sidecar->setComment("comment with <xml> & \"special\" chars"));
}

// Test setComment with unicode content
TEST_F(XmpSidecarTest_1715, SetCommentWithUnicodeContent_1715) {
    auto sidecar = createXmpSidecar();
    EXPECT_NO_THROW(sidecar->setComment("日本語テスト"));
}

// Test multiple setComment calls
TEST_F(XmpSidecarTest_1715, MultipleSetCommentCalls_1715) {
    auto sidecar = createXmpSidecar();
    EXPECT_NO_THROW(sidecar->setComment("first"));
    EXPECT_NO_THROW(sidecar->setComment("second"));
    EXPECT_NO_THROW(sidecar->setComment("third"));
}

// Test that the object is a valid Image subclass
TEST_F(XmpSidecarTest_1715, IsImageSubclass_1715) {
    auto sidecar = createXmpSidecar();
    Exiv2::Image* imagePtr = sidecar.get();
    ASSERT_NE(imagePtr, nullptr);
    EXPECT_EQ(imagePtr->mimeType(), "application/rdf+xml");
}

}  // namespace
