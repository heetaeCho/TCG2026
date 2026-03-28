// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 1071
//
// Unit tests for Exiv2::Image::xmpPacket()
// Focus: observable behavior of packet generation/retention based on public interface.

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/xmp_exiv2.hpp>

#include <cstdint>
#include <memory>
#include <string>
#include <utility>

namespace {

class ImageXmpPacketTest_1071 : public ::testing::Test {
protected:
  static Exiv2::XmpData makeNonEmptyXmpDataFromPacket() {
    // A small, valid XMP packet that should decode into non-empty XmpData.
    const std::string pkt =
        "<?xpacket begin=\"\xEF\xBB\xBF\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
        "<dc:title><rdf:Alt><rdf:li xml:lang=\"x-default\">Test</rdf:li></rdf:Alt></dc:title>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    Exiv2::XmpData xd;
    const int rc = Exiv2::XmpParser::decode(xd, pkt);
    EXPECT_EQ(0, rc) << "XmpParser::decode failed; test requires XMP decode support";
    EXPECT_FALSE(xd.empty());
    return xd;
  }

  static std::unique_ptr<Exiv2::Image> makeImage() {
    // Avoid assumptions about concrete ImageType enum values: use 0.
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::Image>(static_cast<Exiv2::ImageType>(0), /*supportedMetadata=*/0,
                                          std::move(io));
  }
};

}  // namespace

TEST_F(ImageXmpPacketTest_1071, ReturnsEmptyWhenPacketAndDataEmpty_1071) {
  auto img = makeImage();

  // Ensure both are empty through public interface.
  img->clearXmpPacket();
  img->clearXmpData();

  std::string& pkt = img->xmpPacket();
  EXPECT_TRUE(pkt.empty());
}

TEST_F(ImageXmpPacketTest_1071, ReturnsExistingPacketUnchangedWhenXmpDataEmpty_1071) {
  auto img = makeImage();

  const std::string original = "already-present-xmp-packet";
  img->clearXmpData();           // empty data
  img->setXmpPacket(original);   // set packet

  std::string& pkt1 = img->xmpPacket();
  EXPECT_EQ(original, pkt1);

  // Repeated calls should not change it (observable behavior).
  std::string& pkt2 = img->xmpPacket();
  EXPECT_EQ(original, pkt2);

  // Also check that we are getting a reference to the same underlying object.
  EXPECT_EQ(&pkt1, &pkt2);
}

TEST_F(ImageXmpPacketTest_1071, GeneratesPacketFromNonEmptyXmpDataWhenNotWritingFromPacket_1071) {
  auto img = makeImage();

  // Arrange: non-empty XmpData, empty packet.
  Exiv2::XmpData xd = makeNonEmptyXmpDataFromPacket();
  img->setXmpData(xd);
  img->clearXmpPacket();

  // Ensure generation path is allowed.
  img->writeXmpFromPacket(false);

  std::string& pkt = img->xmpPacket();

  // Observable expectations: packet becomes non-empty and looks like XMP.
  EXPECT_FALSE(pkt.empty());
  EXPECT_NE(std::string::npos, pkt.find("xmpmeta")) << "Encoded packet should resemble XMP content";
  EXPECT_NE(std::string::npos, pkt.find("rdf:RDF")) << "Encoded packet should contain RDF content";
}

TEST_F(ImageXmpPacketTest_1071, DoesNotGeneratePacketWhenWriteXmpFromPacketIsTrue_1071) {
  auto img = makeImage();

  // Arrange: non-empty XmpData, but packet cleared.
  Exiv2::XmpData xd = makeNonEmptyXmpDataFromPacket();
  img->setXmpData(xd);
  img->clearXmpPacket();

  // When enabled, xmpPacket() should not encode from xmpData (per interface behavior).
  img->writeXmpFromPacket(true);

  std::string& pkt = img->xmpPacket();
  EXPECT_TRUE(pkt.empty()) << "Packet should remain unchanged (empty) when writeXmpFromPacket() is true";
}

TEST_F(ImageXmpPacketTest_1071, LeavesExistingPacketAsIsWhenWriteXmpFromPacketIsTrue_1071) {
  auto img = makeImage();

  // Arrange: packet already set, XmpData non-empty, and writeXmpFromPacket enabled.
  const std::string original = "preexisting-packet-content";
  img->setXmpPacket(original);

  Exiv2::XmpData xd = makeNonEmptyXmpDataFromPacket();
  img->setXmpData(xd);

  img->writeXmpFromPacket(true);

  std::string& pkt = img->xmpPacket();
  EXPECT_EQ(original, pkt) << "Existing packet should be returned unchanged when writeXmpFromPacket() is true";
}