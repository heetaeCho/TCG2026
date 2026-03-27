// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_quicktimevideo_ignorelist_654.cpp
//
// Unit tests for: Exiv2::Internal::ignoreList(Exiv2::DataBuf&)
// Source under test: ./TestProjects/exiv2/src/quicktimevideo.cpp
//
// NOTE:
// - ignoreList is declared `static` in quicktimevideo.cpp (internal linkage).
// - To test it as a black box via its provided signature, we include the .cpp
//   so the function is available within this translation unit.

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "exiv2/types.hpp"

// Include the implementation file to access the `static` function in this TU.
// Adjust include path if your build uses a different include root.
#include "quicktimevideo.cpp"

namespace {

class QuickTimeIgnoreListTest_654 : public ::testing::Test {
protected:
  static Exiv2::DataBuf MakeBufWithFourCC(const char* fourcc, std::size_t extraBytes = 0) {
    Exiv2::DataBuf buf(4 + extraBytes);
    // Write the 4-byte QuickTime tag at the beginning.
    for (std::size_t i = 0; i < 4; ++i) {
      buf.write_uint8(i, static_cast<uint8_t>(fourcc[i]));
    }
    // Fill any extra bytes with a known pattern (not required by the interface,
    // but makes the buffer deterministic).
    for (std::size_t i = 4; i < 4 + extraBytes; ++i) {
      buf.write_uint8(i, static_cast<uint8_t>('x'));
    }
    return buf;
  }

  static Exiv2::DataBuf MakeShortBuf(const char* bytes, std::size_t n) {
    Exiv2::DataBuf buf(n);
    for (std::size_t i = 0; i < n; ++i) {
      buf.write_uint8(i, static_cast<uint8_t>(bytes[i]));
    }
    return buf;
  }
};

TEST_F(QuickTimeIgnoreListTest_654, ReturnsTrueForAllKnownIgnoredTags_654) {
  const std::vector<std::string> ignored = {
      "mdat", "edts", "junk", "iods", "alis", "stsc", "stsz",
      "stco", "ctts", "stss", "skip", "wide", "cmvd",
  };

  for (const auto& tag : ignored) {
    Exiv2::DataBuf buf = MakeBufWithFourCC(tag.c_str());
    EXPECT_TRUE(Exiv2::Internal::ignoreList(buf)) << "Expected true for tag: " << tag;
  }
}

TEST_F(QuickTimeIgnoreListTest_654, ReturnsFalseForNonIgnoredTags_654) {
  const std::vector<std::string> notIgnored = {
      "moov", "ftyp", "free", "uuid", "trak", "meta", "udta", "mvhd",
  };

  for (const auto& tag : notIgnored) {
    Exiv2::DataBuf buf = MakeBufWithFourCC(tag.c_str());
    EXPECT_FALSE(Exiv2::Internal::ignoreList(buf)) << "Expected false for tag: " << tag;
  }
}

TEST_F(QuickTimeIgnoreListTest_654, ReturnsTrueWhenIgnoredTagHasExtraTrailingBytes_654) {
  Exiv2::DataBuf buf = MakeBufWithFourCC("mdat", /*extraBytes=*/8);
  EXPECT_TRUE(Exiv2::Internal::ignoreList(buf));
}

TEST_F(QuickTimeIgnoreListTest_654, IsCaseSensitiveForTags_654) {
  Exiv2::DataBuf upper = MakeBufWithFourCC("MDAT");
  EXPECT_FALSE(Exiv2::Internal::ignoreList(upper));
}

TEST_F(QuickTimeIgnoreListTest_654, ShortBufferDoesNotCrashAndReturnsFalse_654) {
  // Boundary condition: fewer than 4 bytes available.
  // Observable requirement here is limited to "no crash"; result is expected false.
  Exiv2::DataBuf short3 = MakeShortBuf("mda", 3);

  bool result = true;
  EXPECT_NO_THROW({ result = Exiv2::Internal::ignoreList(short3); });
  EXPECT_FALSE(result);
}

}  // namespace