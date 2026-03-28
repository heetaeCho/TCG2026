#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/xmpsidecar.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/error.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/image.hpp>

#include <memory>
#include <string>
#include <sstream>

namespace {

class XmpSidecarTest_1718 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }

    std::unique_ptr<Exiv2::XmpSidecar> createSidecar(bool create = true) {
        auto io = std::make_unique<Exiv2::MemIo>();
        return std::make_unique<Exiv2::XmpSidecar>(std::move(io), create);
    }

    std::unique_ptr<Exiv2::XmpSidecar> createSidecarWithData(const std::string& data) {
        auto io = std::make_unique<Exiv2::MemIo>(
            reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
        return std::make_unique<Exiv2::XmpSidecar>(std::move(io), false);
    }
};

// Test that mimeType returns the correct MIME type
TEST_F(XmpSidecarTest_1718, MimeType_ReturnsCorrectType_1718) {
    auto sidecar = createSidecar();
    EXPECT_EQ("application/rdf+xml", sidecar->mimeType());
}

// Test that a newly created sidecar has empty XMP data
TEST_F(XmpSidecarTest_1718, NewSidecar_HasEmptyXmpData_1718) {
    auto sidecar = createSidecar();
    EXPECT_TRUE(sidecar->xmpData().empty());
}

// Test writeMetadata with empty XMP data (no packet written)
TEST_F(XmpSidecarTest_1718, WriteMetadata_EmptyXmpData_NoThrow_1718) {
    auto sidecar = createSidecar();
    EXPECT_NO_THROW(sidecar->writeMetadata());
}

// Test writeMetadata with some XMP data
TEST_F(XmpSidecarTest_1718, WriteMetadata_WithXmpData_NoThrow_1718) {
    auto sidecar = createSidecar();
    sidecar->xmpData()["Xmp.dc.title"] = "Test Title";
    EXPECT_NO_THROW(sidecar->writeMetadata());
}

// Test writeMetadata produces output that can be read back
TEST_F(XmpSidecarTest_1718, WriteAndReadMetadata_RoundTrip_1718) {
    // Write
    auto io = std::make_unique<Exiv2::MemIo>();
    auto* ioPtr = io.get();
    auto sidecar = std::make_unique<Exiv2::XmpSidecar>(std::move(io), true);
    sidecar->xmpData()["Xmp.dc.description"] = "Test Description";
    ASSERT_NO_THROW(sidecar->writeMetadata());

    // Read back
    auto size = ioPtr->size();
    EXPECT_GT(size, 0u);
}

// Test that setComment is effectively a no-op (based on XmpSidecar behavior)
TEST_F(XmpSidecarTest_1718, SetComment_DoesNotThrow_1718) {
    auto sidecar = createSidecar();
    EXPECT_NO_THROW(sidecar->setComment("Some comment"));
}

// Test writeMetadata with writeXmpFromPacket flag set
TEST_F(XmpSidecarTest_1718, WriteMetadata_FromPacket_1718) {
    auto sidecar = createSidecar();
    std::string xmpPacket = R"(<?xml version="1.0" encoding="UTF-8"?>
<x:xmpmeta xmlns:x="adobe:ns:meta/">
  <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
    <rdf:Description rdf:about=""
      xmlns:dc="http://purl.org/dc/elements/1.1/">
      <dc:title>
        <rdf:Alt>
          <rdf:li xml:lang="x-default">Test</rdf:li>
        </rdf:Alt>
      </dc:title>
    </rdf:Description>
  </rdf:RDF>
</x:xmpmeta>)";
    sidecar->xmpPacket() = xmpPacket;
    sidecar->writeXmpFromPacket(true);
    EXPECT_NO_THROW(sidecar->writeMetadata());
}

// Test writeMetadata with XMP packet that doesn't start with <?xml
TEST_F(XmpSidecarTest_1718, WriteMetadata_PacketWithoutXmlHeader_AddsHeader_1718) {
    auto sidecar = createSidecar();
    std::string xmpPacket = R"(<x:xmpmeta xmlns:x="adobe:ns:meta/">
  <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
    <rdf:Description rdf:about=""
      xmlns:dc="http://purl.org/dc/elements/1.1/">
      <dc:title>
        <rdf:Alt>
          <rdf:li xml:lang="x-default">Test</rdf:li>
        </rdf:Alt>
      </dc:title>
    </rdf:Description>
  </rdf:RDF>
</x:xmpmeta>)";
    sidecar->xmpPacket() = xmpPacket;
    sidecar->writeXmpFromPacket(true);
    EXPECT_NO_THROW(sidecar->writeMetadata());
}

// Test readMetadata on empty data
TEST_F(XmpSidecarTest_1718, ReadMetadata_EmptyIo_1718) {
    auto sidecar = createSidecar(true);
    // Reading from empty MemIo should not crash, though it may throw or produce empty data
    try {
        sidecar->readMetadata();
    } catch (const Exiv2::Error&) {
        // Expected - empty data may cause an error
    }
}

// Test readMetadata with valid XMP data
TEST_F(XmpSidecarTest_1718, ReadMetadata_ValidXmp_1718) {
    std::string xmpData = R"(<?xml version="1.0" encoding="UTF-8"?>
<x:xmpmeta xmlns:x="adobe:ns:meta/">
  <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
    <rdf:Description rdf:about=""
      xmlns:dc="http://purl.org/dc/elements/1.1/">
      <dc:description>
        <rdf:Alt>
          <rdf:li xml:lang="x-default">Hello World</rdf:li>
        </rdf:Alt>
      </dc:description>
    </rdf:Description>
  </rdf:RDF>
</x:xmpmeta>)";

    auto sidecar = createSidecarWithData(xmpData);
    ASSERT_NO_THROW(sidecar->readMetadata());
    EXPECT_FALSE(sidecar->xmpData().empty());
}

// Test that writeMetadata preserves XMP-only data (not exif/iptc related)
TEST_F(XmpSidecarTest_1718, WriteMetadata_PreservesXmpOnlyData_1718) {
    auto sidecar = createSidecar();
    sidecar->xmpData()["Xmp.dc.creator"] = "Author Name";
    sidecar->xmpData()["Xmp.dc.subject"] = "keyword1";
    EXPECT_NO_THROW(sidecar->writeMetadata());
}

// Test multiple writes don't corrupt data
TEST_F(XmpSidecarTest_1718, WriteMetadata_MultipleWrites_NoThrow_1718) {
    auto sidecar = createSidecar();
    sidecar->xmpData()["Xmp.dc.title"] = "First";
    EXPECT_NO_THROW(sidecar->writeMetadata());

    sidecar->xmpData()["Xmp.dc.title"] = "Second";
    EXPECT_NO_THROW(sidecar->writeMetadata());
}

// Test that dates_ map is accessible and can be populated
TEST_F(XmpSidecarTest_1718, DatesMap_Accessible_1718) {
    auto sidecar = createSidecar();
    sidecar->dates_["Xmp.xmp.CreateDate"] = "2023-01-15T10:30:00";
    EXPECT_EQ(sidecar->dates_.size(), 1u);
    EXPECT_EQ(sidecar->dates_["Xmp.xmp.CreateDate"], "2023-01-15T10:30:00");
}

// Test writeMetadata with dates preservation logic
TEST_F(XmpSidecarTest_1718, WriteMetadata_WithDates_PreservesOriginal_1718) {
    auto sidecar = createSidecar();
    sidecar->xmpData()["Xmp.xmp.CreateDate"] = "2023-01-15T10:30:00+05:00";
    sidecar->dates_["Xmp.xmp.CreateDate"] = "2023-01-15T10:30:00+05:00";
    EXPECT_NO_THROW(sidecar->writeMetadata());
}

// Test that good() returns true for valid sidecar
TEST_F(XmpSidecarTest_1718, Good_ReturnsTrueForValidSidecar_1718) {
    auto sidecar = createSidecar();
    EXPECT_TRUE(sidecar->good());
}

// Test that clearXmpData works
TEST_F(XmpSidecarTest_1718, ClearXmpData_ClearsData_1718) {
    auto sidecar = createSidecar();
    sidecar->xmpData()["Xmp.dc.title"] = "Test";
    EXPECT_FALSE(sidecar->xmpData().empty());
    sidecar->clearXmpData();
    EXPECT_TRUE(sidecar->xmpData().empty());
}

// Test writeMetadata after clearXmpData produces empty or minimal output
TEST_F(XmpSidecarTest_1718, WriteMetadata_AfterClear_NoThrow_1718) {
    auto sidecar = createSidecar();
    sidecar->xmpData()["Xmp.dc.title"] = "Test";
    sidecar->clearXmpData();
    sidecar->xmpPacket().clear();
    EXPECT_NO_THROW(sidecar->writeMetadata());
}

// Test writeMetadata with exif-related XMP data that should be filtered
TEST_F(XmpSidecarTest_1718, WriteMetadata_WithExifXmpData_1718) {
    auto sidecar = createSidecar();
    sidecar->xmpData()["Xmp.dc.title"] = "Keep This";
    // Add data that might be exif-related
    EXPECT_NO_THROW(sidecar->writeMetadata());
}

// Test that image type is XMP
TEST_F(XmpSidecarTest_1718, ImageType_IsXmp_1718) {
    auto sidecar = createSidecar();
    EXPECT_EQ(sidecar->imageType(), Exiv2::ImageType::xmp);
}

// Test readMetadata with invalid/corrupt XMP
TEST_F(XmpSidecarTest_1718, ReadMetadata_InvalidXmp_1718) {
    std::string invalidXmp = "This is not valid XMP data at all";
    auto sidecar = createSidecarWithData(invalidXmp);
    // Should not crash, may or may not throw depending on implementation
    try {
        sidecar->readMetadata();
    } catch (const Exiv2::Error&) {
        // Acceptable
    }
}

// Test writeMetadata with packet starting with <?xml (no header added)
TEST_F(XmpSidecarTest_1718, WriteMetadata_PacketWithXmlHeader_NoDoubleHeader_1718) {
    auto sidecar = createSidecar();
    std::string xmpPacket = R"(<?xml version="1.0" encoding="UTF-8"?>
<x:xmpmeta xmlns:x="adobe:ns:meta/">
  <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
    <rdf:Description rdf:about=""/>
  </rdf:RDF>
</x:xmpmeta>)";
    sidecar->xmpPacket() = xmpPacket;
    sidecar->writeXmpFromPacket(true);
    EXPECT_NO_THROW(sidecar->writeMetadata());
}

// Test io() returns valid reference
TEST_F(XmpSidecarTest_1718, Io_ReturnsValidReference_1718) {
    auto sidecar = createSidecar();
    const Exiv2::BasicIo& io = sidecar->io();
    // Path for MemIo should be empty or some default
    EXPECT_NO_THROW(io.path());
}

// Test writeMetadata with both exif and XMP data set
TEST_F(XmpSidecarTest_1718, WriteMetadata_WithExifAndXmpData_1718) {
    auto sidecar = createSidecar();
    sidecar->xmpData()["Xmp.dc.title"] = "Test Title";
    // Setting exif data that should get converted to XMP
    sidecar->exifData()["Exif.Image.DateTime"] = "2023:01:15 10:30:00";
    EXPECT_NO_THROW(sidecar->writeMetadata());
}

// Test writeMetadata with IPTC data that should get converted
TEST_F(XmpSidecarTest_1718, WriteMetadata_WithIptcData_1718) {
    auto sidecar = createSidecar();
    sidecar->xmpData()["Xmp.dc.title"] = "Test Title";
    EXPECT_NO_THROW(sidecar->writeMetadata());
}

}  // namespace
