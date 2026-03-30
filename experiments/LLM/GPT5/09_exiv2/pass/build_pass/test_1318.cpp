// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_xmp_parser_encode_1318.cpp
//
// Unit tests for Exiv2::XmpParser::encode (black-box; interface-based).
//
// Constraints followed:
// - No re-implementation / inference of internal logic.
// - Only observable behavior via public API (return code, output string, exceptions).
// - No private state access.
// - Boundary + error/exception cases where observable.

#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include "exiv2/error.hpp"
#include "exiv2/xmp_exiv2.hpp"

namespace {

class XmpParserEncodeTest_1318 : public ::testing::Test {
 protected:
  static Exiv2::XmpData MakeEmptyXmpData() { return Exiv2::XmpData{}; }

  static Exiv2::XmpData MakeSimpleTextXmpData() {
    Exiv2::XmpData xmp;
    // Use a commonly-supported simple text property.
    // We don't assume toolkit availability; tests handle both outcomes.
    int rc = xmp["Xmp.xmp.CreatorTool"].setValue("Exiv2Test");
    (void)rc;  // If this fails in some builds, encode() should still be robust.
    return xmp;
  }
};

TEST_F(XmpParserEncodeTest_1318, EncodeEmptyDataClearsPacketAndReturnsZero_1318) {
  Exiv2::XmpData xmpData = MakeEmptyXmpData();

  std::string xmpPacket = "SENTINEL_NONEMPTY";
  const int rc = Exiv2::XmpParser::encode(xmpPacket, xmpData, /*formatFlags*/ 0, /*padding*/ 0);

  EXPECT_EQ(0, rc);
  EXPECT_TRUE(xmpPacket.empty());
}

TEST_F(XmpParserEncodeTest_1318, EncodeEmptyDataIgnoresNonZeroFlagsAndPadding_1318) {
  Exiv2::XmpData xmpData = MakeEmptyXmpData();

  std::string xmpPacket = "SENTINEL_NONEMPTY";
  const uint16_t formatFlags = static_cast<uint16_t>(0xFFFF);
  const uint32_t padding = static_cast<uint32_t>(0xFFFFFFFFu);

  const int rc = Exiv2::XmpParser::encode(xmpPacket, xmpData, formatFlags, padding);

  EXPECT_EQ(0, rc);
  EXPECT_TRUE(xmpPacket.empty());
}

TEST_F(XmpParserEncodeTest_1318, EncodeNonEmptyEitherSucceedsOrLeavesPacketUnchangedOnFailure_1318) {
  Exiv2::XmpData xmpData = MakeSimpleTextXmpData();

  // Start with a sentinel so we can observe whether encode replaced it.
  std::string xmpPacket = "SENTINEL_PACKET";
  const int rc = Exiv2::XmpParser::encode(xmpPacket, xmpData, /*formatFlags*/ 0, /*padding*/ 0);

  // Observed outcomes through the interface (toolkit may/may-not be available):
  // - 0 on success (packet produced)
  // - 2 if initialization fails
  // - 3 if XMP toolkit reports an error (caught internally)
  EXPECT_TRUE(rc == 0 || rc == 2 || rc == 3);

  if (rc == 0) {
    // On success, we expect encode to produce some packet content.
    EXPECT_FALSE(xmpPacket.empty());
    EXPECT_NE("SENTINEL_PACKET", xmpPacket);
  } else {
    // On failure paths (init/toolkit error), observable behavior should be that
    // the provided string is not replaced by a successfully serialized packet.
    EXPECT_EQ("SENTINEL_PACKET", xmpPacket);
  }
}

TEST_F(XmpParserEncodeTest_1318, EncodeNonEmptyWithLargePaddingDoesNotCrashAndFollowsSameContract_1318) {
  Exiv2::XmpData xmpData = MakeSimpleTextXmpData();

  std::string xmpPacket = "SENTINEL_PACKET";
  const uint16_t formatFlags = 0;
  const uint32_t padding = static_cast<uint32_t>(1024u * 1024u);  // 1 MiB padding (boundary-ish)

  const int rc = Exiv2::XmpParser::encode(xmpPacket, xmpData, formatFlags, padding);

  EXPECT_TRUE(rc == 0 || rc == 2 || rc == 3);

  if (rc == 0) {
    EXPECT_FALSE(xmpPacket.empty());
    EXPECT_NE("SENTINEL_PACKET", xmpPacket);
  } else {
    EXPECT_EQ("SENTINEL_PACKET", xmpPacket);
  }
}

TEST_F(XmpParserEncodeTest_1318, EncodeThrowsForUnsupportedXmpTypeWhenRepresentable_1318) {
  // The encode implementation (as provided) explicitly throws on unhandled Xmpdatum types.
  // We try to create a non-text XMP datum (commonly: date). If the build's property tables
  // or parsing do not support this key/value, we skip rather than guessing.
  Exiv2::XmpData xmpData;
  const int setRc = xmpData["Xmp.xmp.CreateDate"].setValue("2020-01-01T00:00:00Z");
  if (setRc != 0) {
    GTEST_SKIP() << "Could not set Xmp.xmp.CreateDate to a date value in this build (setValue rc="
                 << setRc << "); skipping unhandled-type exception observation test.";
  }

  std::string xmpPacket = "SENTINEL_PACKET";

  // If toolkit init fails first, encode may return 2 instead of reaching the throw.
  // To keep the test strictly interface-based and robust, we accept either:
  // - throwing Exiv2::Error (unhandled type reached)
  // - returning 2/3 without modifying packet (toolkit not available)
  try {
    const int rc = Exiv2::XmpParser::encode(xmpPacket, xmpData, /*formatFlags*/ 0, /*padding*/ 0);
    EXPECT_TRUE(rc == 2 || rc == 3)
        << "If no exception is thrown, encode is expected to fail early in environments without "
           "a usable XMP toolkit (rc 2/3). Got rc="
        << rc;
    EXPECT_EQ("SENTINEL_PACKET", xmpPacket);
  } catch (const Exiv2::Error&) {
    // Expected observable exceptional case.
    EXPECT_EQ("SENTINEL_PACKET", xmpPacket)
        << "When encode throws before successful serialization, the output packet should not be "
           "replaced by a serialized packet.";
  }
}

}  // namespace