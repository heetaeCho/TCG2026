// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_image_setxmppacket_1078.cpp
//
// Unit tests for Exiv2::Image::setXmpPacket
// TEST_ID: 1078

#include <gtest/gtest.h>

#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/xmp_exiv2.hpp>

#include <cstdint>
#include <memory>
#include <string>

namespace {

class ImageSetXmpPacketTest_1078 : public ::testing::Test {
public:
  static void SetUpTestSuite() {
    // XMP decode may require toolkit initialization in some builds.
    // If initialize fails/returns false, the subsequent tests may still pass
    // depending on build configuration; we keep behavior black-box.
    (void)Exiv2::XmpParser::initialize(nullptr, nullptr);
  }

  static void TearDownTestSuite() { Exiv2::XmpParser::terminate(); }

protected:
  void SetUp() override {
    // Use an in-memory IO backend.
    // Many Exiv2 builds provide MemIo as a concrete BasicIo implementation.
    io_ = std::make_unique<Exiv2::MemIo>();
    image_ = std::make_unique<Exiv2::Image>(Exiv2::ImageType::none, /*supportedMetadata=*/0, std::move(io_));
  }

  static std::string ValidXmpPacket() {
    // Minimal, commonly accepted XMP packet with x:xmpmeta + rdf:RDF root.
    // (Kept small to reduce risk of toolkit differences.)
    return std::string(
        "<?xpacket begin=\"\xEF\xBB\xBF\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description xmlns:dc=\"http://purl.org/dc/elements/1.1/\" dc:format=\"image/jpeg\"/>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>");
  }

  static std::string ClearlyInvalidXmpPacket() {
    return "this is not xml and not an xmp packet";
  }

  std::unique_ptr<Exiv2::BasicIo> io_;
  std::unique_ptr<Exiv2::Image> image_;
};

TEST_F(ImageSetXmpPacketTest_1078, ValidPacketStoresPacketString_1078) {
  const std::string packet = ValidXmpPacket();

  ASSERT_NO_THROW(image_->setXmpPacket(packet));
  EXPECT_EQ(image_->xmpPacket(), packet);
}

TEST_F(ImageSetXmpPacketTest_1078, InvalidPacketThrowsKerInvalidXMP_1078) {
  const std::string bad = ClearlyInvalidXmpPacket();

  try {
    image_->setXmpPacket(bad);
    FAIL() << "Expected Exiv2::Error to be thrown for invalid XMP packet";
  } catch (const Exiv2::Error& e) {
    // Observable error classification through public ErrorCode.
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerInvalidXMP);
  } catch (...) {
    FAIL() << "Expected Exiv2::Error, but caught a different exception type";
  }
}

TEST_F(ImageSetXmpPacketTest_1078, InvalidPacketDoesNotOverwritePreviousPacket_1078) {
  const std::string good = ValidXmpPacket();
  const std::string bad = ClearlyInvalidXmpPacket();

  ASSERT_NO_THROW(image_->setXmpPacket(good));
  ASSERT_EQ(image_->xmpPacket(), good);

  EXPECT_THROW(image_->setXmpPacket(bad), Exiv2::Error);

  // Since setXmpPacket assigns xmpPacket_ only after successful decode,
  // the previously stored packet should remain observable via xmpPacket().
  EXPECT_EQ(image_->xmpPacket(), good);
}

}  // namespace