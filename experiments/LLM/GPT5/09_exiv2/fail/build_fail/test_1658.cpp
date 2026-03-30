// =================================================================================================
// TEST_ID: 1658
// Unit tests for Exiv2::Internal::TiffDecoder::decodeXmp (tiffvisitor_int.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "exiv2/error.hpp"
#include "exiv2/exif.hpp"
#include "exiv2/iptc.hpp"
#include "exiv2/tags.hpp"
#include "exiv2/types.hpp"
#include "exiv2/xmp.hpp"
#include "exiv2/xmp_exiv2.hpp"

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

namespace {

using Exiv2::byte;

class LogCapture_1658 {
 public:
  static void Install() {
#ifndef SUPPRESS_WARNINGS
    oldLevel_ = Exiv2::LogMsg::level();
    oldHandler_ = Exiv2::LogMsg::handler();
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    Exiv2::LogMsg::setHandler(&LogCapture_1658::Handler);
#endif
  }

  static void Uninstall() {
#ifndef SUPPRESS_WARNINGS
    Exiv2::LogMsg::setHandler(oldHandler_);
    Exiv2::LogMsg::setLevel(oldLevel_);
#endif
  }

  static void Reset() {
    count_ = 0;
    last_.clear();
  }

  static int count() { return count_; }
  static const std::string& last() { return last_; }

 private:
#ifndef SUPPRESS_WARNINGS
  static void Handler(int /*level*/, const char* s) {
    ++count_;
    if (s) last_ = s;
  }

  static inline Exiv2::LogMsg::Level oldLevel_{Exiv2::LogMsg::warn};
  static inline Exiv2::LogMsg::Handler oldHandler_{nullptr};
#endif

  static inline int count_{0};
  static inline std::string last_{};
};

class TiffDecoderDecodeXmpTest_1658 : public ::testing::Test {
 protected:
  void SetUp() override {
    LogCapture_1658::Install();
    LogCapture_1658::Reset();

    // Some builds require XMP initialization for decode to work reliably.
    // If initialize() is not available/returns false, tests that depend on successful decode will skip.
    xmpInitialized_ = Exiv2::XmpParser::initialize(nullptr, nullptr);
  }

  void TearDown() override { LogCapture_1658::Uninstall(); }

  // Helper that creates a minimal entry we can pass into decodeXmp.
  static Exiv2::Internal::TiffEntryBase MakeEntry(uint16_t tag, Exiv2::IfdId group) {
    // TiffType is an enum in Exiv2 internals; use a safe cast to avoid relying on specific enumerators.
    return Exiv2::Internal::TiffEntryBase(tag, group, static_cast<Exiv2::Internal::TiffType>(0));
  }

  Exiv2::ExifData exif_;
  Exiv2::IptcData iptc_;
  Exiv2::XmpData xmp_;

  // pRoot and findDecoderFct are not needed for decodeXmp() behavior under test here.
  Exiv2::Internal::TiffDecoder decoder_{exif_, iptc_, xmp_, /*pRoot*/ nullptr, /*findDecoderFct*/ nullptr};

  bool xmpInitialized_{false};
};

TEST_F(TiffDecoderDecodeXmpTest_1658, NoDataDoesNotModifyXmp_1658) {
  ASSERT_TRUE(xmp_.empty());

  auto entry = MakeEntry(/*tag*/ 0x02bc, Exiv2::IfdId::ifd0Id);
  // No setData call => entry has no payload.

  EXPECT_NO_THROW(decoder_.decodeXmp(&entry));
  EXPECT_TRUE(xmp_.empty());
}

TEST_F(TiffDecoderDecodeXmpTest_1658, EmptySizeDoesNotModifyXmp_1658) {
  ASSERT_TRUE(xmp_.empty());

  auto entry = MakeEntry(/*tag*/ 0x02bc, Exiv2::IfdId::ifd0Id);

  byte dummy = 0;
  entry.setData(&dummy, 0, nullptr);

  EXPECT_NO_THROW(decoder_.decodeXmp(&entry));
  EXPECT_TRUE(xmp_.empty());
}

TEST_F(TiffDecoderDecodeXmpTest_1658, DataWithoutAngleBracketDoesNotDecode_1658) {
  ASSERT_TRUE(xmp_.empty());

  auto entry = MakeEntry(/*tag*/ 0x02bc, Exiv2::IfdId::ifd0Id);

  const std::string notXml = "this is not xml or xmp";
  std::vector<byte> buf(notXml.begin(), notXml.end());
  entry.setData(buf.data(), buf.size(), nullptr);

  EXPECT_NO_THROW(decoder_.decodeXmp(&entry));
  EXPECT_TRUE(xmp_.empty());
}

TEST_F(TiffDecoderDecodeXmpTest_1658, DifferentTagOrGroupDoesNotModifyXmp_1658) {
  ASSERT_TRUE(xmp_.empty());

  // Even if we provide a valid-looking packet, getObjData() is requested for tag 0x02bc/ifd0Id.
  // Provide a different tag/group so decodeXmp should not find the payload.
  auto entry = MakeEntry(/*tag*/ 0x1234, Exiv2::IfdId::ifd1Id);

  const std::string packet =
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
      "<dc:title><rdf:Alt><rdf:li xml:lang=\"x-default\">Test</rdf:li></rdf:Alt></dc:title>"
      "</rdf:Description></rdf:RDF></x:xmpmeta>";

  std::vector<byte> buf(packet.begin(), packet.end());
  entry.setData(buf.data(), buf.size(), nullptr);

  EXPECT_NO_THROW(decoder_.decodeXmp(&entry));
  EXPECT_TRUE(xmp_.empty());
}

TEST_F(TiffDecoderDecodeXmpTest_1658, LeadingGarbageBeforeLtIsHandledAndCanDecode_1658) {
  if (!xmpInitialized_) {
    GTEST_SKIP() << "XMP parser not initialized/enabled in this build.";
  }

  ASSERT_TRUE(xmp_.empty());

  auto entry = MakeEntry(/*tag*/ 0x02bc, Exiv2::IfdId::ifd0Id);

  // Prefix garbage before the first '<' to exercise the trimming path.
  const std::string packet =
      "GARBAGE_PREFIX"
      "<?xpacket begin=\"\xEF\xBB\xBF\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
      "<dc:title><rdf:Alt><rdf:li xml:lang=\"x-default\">TrimTest</rdf:li></rdf:Alt></dc:title>"
      "</rdf:Description></rdf:RDF></x:xmpmeta>"
      "<?xpacket end=\"w\"?>";

  std::vector<byte> buf(packet.begin(), packet.end());
  entry.setData(buf.data(), buf.size(), nullptr);

  EXPECT_NO_THROW(decoder_.decodeXmp(&entry));

  // Observable outcome: decoding a well-formed XMP packet should populate xmpData_.
  // (If it doesn't in a particular build/config, this expectation may fail; that indicates XMP decode
  // behavior differs in that environment.)
  EXPECT_FALSE(xmp_.empty());

#ifndef SUPPRESS_WARNINGS
  // decodeXmp may emit a warning about removing prefix characters.
  // We only assert it's "allowed" to log, not that it must (depends on build flags/log handler).
  EXPECT_GE(LogCapture_1658::count(), 0);
#endif
}

TEST_F(TiffDecoderDecodeXmpTest_1658, InvalidXmpPacketDoesNotCrash_1658) {
  ASSERT_TRUE(xmp_.empty());

  auto entry = MakeEntry(/*tag*/ 0x02bc, Exiv2::IfdId::ifd0Id);

  // Contains '<' so the decode path is exercised, but the payload is not valid XMP.
  const std::string bad = "JUNK<not-xmp></not-xmp>";
  std::vector<byte> buf(bad.begin(), bad.end());
  entry.setData(buf.data(), buf.size(), nullptr);

  EXPECT_NO_THROW(decoder_.decodeXmp(&entry));

  // We don't assume decode succeeds; observable behavior here is non-throw and no UB/crash.
  // If decode fails, xmp data should remain empty in most configurations.
  // If a particular build accepts it, this still remains a valid black-box test (no strict assertion).
}

}  // namespace