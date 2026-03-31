#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/xmpsidecar.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>

#include <memory>
#include <string>
#include <sstream>

namespace {

class NewXmpInstanceTest_1719 : public ::testing::Test {
 protected:
  void SetUp() override {
    Exiv2::XmpParser::initialize();
  }

  void TearDown() override {
    Exiv2::XmpParser::terminate();
  }
};

// Test: Creating an XMP sidecar image with create=true using MemIo should succeed
TEST_F(NewXmpInstanceTest_1719, CreateNewXmpFromMemIo_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  ASSERT_NE(image, nullptr);
  EXPECT_TRUE(image->good());
}

// Test: Creating from an empty MemIo with create=false should return nullptr
// because there's no valid XMP data to read
TEST_F(NewXmpInstanceTest_1719, OpenEmptyMemIoWithoutCreate_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), false);
  // An empty MemIo with create=false may or may not be good depending on implementation
  // The function returns nullptr if !good()
  // With an empty buffer and no create, it might still be "good" since XMP sidecar
  // can handle empty content, or it might not. We test the observable behavior.
  // Based on the code: if (!image->good()) return nullptr;
  // We just check it doesn't crash and returns a valid or null pointer
  if (image) {
    EXPECT_TRUE(image->good());
  }
}

// Test: Creating XMP sidecar with valid XMP content in MemIo
TEST_F(NewXmpInstanceTest_1719, CreateFromValidXmpContent_1719) {
  const std::string xmpContent =
      "<?xpacket begin='\xef\xbb\xbf' id='W5M0MpCehiHzreSzNTczkc9d'?>\n"
      "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
      " <rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>\n"
      "  <rdf:Description rdf:about=''\n"
      "   xmlns:dc='http://purl.org/dc/elements/1.1/'>\n"
      "   <dc:description>Test</dc:description>\n"
      "  </rdf:Description>\n"
      " </rdf:RDF>\n"
      "</x:xmpmeta>\n"
      "<?xpacket end='w'?>";

  auto io = std::make_unique<Exiv2::MemIo>(
      reinterpret_cast<const uint8_t*>(xmpContent.data()), xmpContent.size());
  auto image = Exiv2::newXmpInstance(std::move(io), false);
  ASSERT_NE(image, nullptr);
  EXPECT_TRUE(image->good());
}

// Test: The returned image should have the correct MIME type for XMP sidecar
TEST_F(NewXmpInstanceTest_1719, MimeTypeIsCorrect_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  ASSERT_NE(image, nullptr);
  EXPECT_EQ(image->mimeType(), "application/rdf+xml");
}

// Test: Read metadata from a newly created (empty) XMP sidecar
TEST_F(NewXmpInstanceTest_1719, ReadMetadataOnNewInstance_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  ASSERT_NE(image, nullptr);
  EXPECT_NO_THROW(image->readMetadata());
}

// Test: Write metadata to a newly created XMP sidecar
TEST_F(NewXmpInstanceTest_1719, WriteMetadataOnNewInstance_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  ASSERT_NE(image, nullptr);
  EXPECT_NO_THROW(image->writeMetadata());
}

// Test: Set and retrieve XMP data on XMP sidecar
TEST_F(NewXmpInstanceTest_1719, SetAndGetXmpData_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  ASSERT_NE(image, nullptr);

  Exiv2::XmpData xmpData;
  xmpData["Xmp.dc.description"] = "Test description";
  image->setXmpData(xmpData);

  EXPECT_FALSE(image->xmpData().empty());
}

// Test: Clear XMP data
TEST_F(NewXmpInstanceTest_1719, ClearXmpData_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  ASSERT_NE(image, nullptr);

  Exiv2::XmpData xmpData;
  xmpData["Xmp.dc.description"] = "Test";
  image->setXmpData(xmpData);
  image->clearXmpData();

  EXPECT_TRUE(image->xmpData().empty());
}

// Test: Set comment on XMP sidecar
TEST_F(NewXmpInstanceTest_1719, SetComment_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  ASSERT_NE(image, nullptr);

  image->setComment("Hello XMP");
  EXPECT_EQ(image->comment(), "Hello XMP");
}

// Test: Clear comment
TEST_F(NewXmpInstanceTest_1719, ClearComment_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  ASSERT_NE(image, nullptr);

  image->setComment("To be cleared");
  image->clearComment();
  EXPECT_TRUE(image->comment().empty());
}

// Test: XMP sidecar supports XMP metadata
TEST_F(NewXmpInstanceTest_1719, SupportsXmpMetadata_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  ASSERT_NE(image, nullptr);

  EXPECT_TRUE(image->supportsMetadata(Exiv2::MetadataId::mdXmp));
}

// Test: Clear all metadata
TEST_F(NewXmpInstanceTest_1719, ClearMetadata_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  ASSERT_NE(image, nullptr);

  Exiv2::XmpData xmpData;
  xmpData["Xmp.dc.title"] = "Test";
  image->setXmpData(xmpData);
  image->setComment("comment");

  image->clearMetadata();
  EXPECT_TRUE(image->xmpData().empty());
  EXPECT_TRUE(image->comment().empty());
}

// Test: Set XMP packet string
TEST_F(NewXmpInstanceTest_1719, SetXmpPacket_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  ASSERT_NE(image, nullptr);

  const std::string packet = "<x:xmpmeta xmlns:x='adobe:ns:meta/'/>";
  image->setXmpPacket(packet);
  EXPECT_EQ(image->xmpPacket(), packet);
}

// Test: Clear XMP packet
TEST_F(NewXmpInstanceTest_1719, ClearXmpPacket_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  ASSERT_NE(image, nullptr);

  image->setXmpPacket("<x:xmpmeta xmlns:x='adobe:ns:meta/'/>");
  image->clearXmpPacket();
  EXPECT_TRUE(image->xmpPacket().empty());
}

// Test: Pixel dimensions should be 0 for XMP sidecar (not an image format with pixels)
TEST_F(NewXmpInstanceTest_1719, PixelDimensionsAreZero_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  ASSERT_NE(image, nullptr);

  EXPECT_EQ(image->pixelWidth(), 0u);
  EXPECT_EQ(image->pixelHeight(), 0u);
}

// Test: Read and then write round-trip with valid XMP content
TEST_F(NewXmpInstanceTest_1719, ReadWriteRoundTrip_1719) {
  const std::string xmpContent =
      "<?xpacket begin='\xef\xbb\xbf' id='W5M0MpCehiHzreSzNTczkc9d'?>\n"
      "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
      " <rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>\n"
      "  <rdf:Description rdf:about=''\n"
      "   xmlns:dc='http://purl.org/dc/elements/1.1/'>\n"
      "   <dc:description>Round trip test</dc:description>\n"
      "  </rdf:Description>\n"
      " </rdf:RDF>\n"
      "</x:xmpmeta>\n"
      "<?xpacket end='w'?>";

  auto io = std::make_unique<Exiv2::MemIo>(
      reinterpret_cast<const uint8_t*>(xmpContent.data()), xmpContent.size());
  auto image = Exiv2::newXmpInstance(std::move(io), false);
  ASSERT_NE(image, nullptr);

  EXPECT_NO_THROW(image->readMetadata());
  EXPECT_NO_THROW(image->writeMetadata());
}

// Test: IO reference is accessible
TEST_F(NewXmpInstanceTest_1719, IoAccessible_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  ASSERT_NE(image, nullptr);

  const Exiv2::BasicIo& ioRef = image->io();
  // Just verify we can access it without crash
  (void)ioRef;
}

// Test: writeXmpFromPacket flag default and setting
TEST_F(NewXmpInstanceTest_1719, WriteXmpFromPacketFlag_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  ASSERT_NE(image, nullptr);

  // Set the flag
  image->writeXmpFromPacket(true);
  EXPECT_TRUE(image->writeXmpFromPacket());

  image->writeXmpFromPacket(false);
  EXPECT_FALSE(image->writeXmpFromPacket());
}

// Test: Setting Exif data on XMP sidecar
TEST_F(NewXmpInstanceTest_1719, SetExifData_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  ASSERT_NE(image, nullptr);

  Exiv2::ExifData exifData;
  image->setExifData(exifData);
  // Should not crash; exif data access should work
  EXPECT_TRUE(image->exifData().empty());
}

// Test: Setting IPTC data on XMP sidecar
TEST_F(NewXmpInstanceTest_1719, SetIptcData_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  ASSERT_NE(image, nullptr);

  Exiv2::IptcData iptcData;
  image->setIptcData(iptcData);
  EXPECT_TRUE(image->iptcData().empty());
}

// Test: Creating XMP sidecar from file path that doesn't exist with create=true
TEST_F(NewXmpInstanceTest_1719, CreateFromNonExistentFileWithCreate_1719) {
  auto io = std::make_unique<Exiv2::FileIo>("__nonexistent_test_file_1719.xmp");
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  // The image might or might not be created depending on file system permissions
  // We just check it doesn't crash
  if (image) {
    EXPECT_TRUE(image->good());
  }
}

// Test: Native previews should be empty for XMP sidecar
TEST_F(NewXmpInstanceTest_1719, NativePreviewsEmpty_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  ASSERT_NE(image, nullptr);

  EXPECT_TRUE(image->nativePreviews().empty());
}

// Test: ICC profile should not be defined initially
TEST_F(NewXmpInstanceTest_1719, IccProfileNotDefined_1719) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::newXmpInstance(std::move(io), true);
  ASSERT_NE(image, nullptr);

  EXPECT_FALSE(image->iccProfileDefined());
}

}  // namespace
