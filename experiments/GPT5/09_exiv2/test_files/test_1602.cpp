// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>

// Internal header (class under test)
#include "sonymn_int.hpp"

#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace {

using Exiv2::ExifData;
using Exiv2::Value;

class SonyMakerNotePrintPixelShiftInfoTest_1602 : public ::testing::Test {
 protected:
  Exiv2::Internal::SonyMakerNote mn_;

  static Exiv2::Value::UniquePtr makeUndefinedValue(const std::vector<Exiv2::byte>& bytes) {
    auto v = Exiv2::Value::create(Exiv2::undefined);
    v->read(bytes.data(), static_cast<long>(bytes.size()));
    return v;
  }

  static std::string streamValue(const Value& v) {
    std::ostringstream os;
    os << v;
    return os.str();
  }
};

TEST_F(SonyMakerNotePrintPixelShiftInfoTest_1602, ReturnsParenthesizedValueWhenCountNotSix_1602) {
  auto v = makeUndefinedValue({0, 0, 0, 0, 0});  // count != 6
  std::ostringstream os;

  mn_.printPixelShiftInfo(os, *v, nullptr);

  const std::string inner = streamValue(*v);
  EXPECT_EQ(os.str(), "(" + inner + ")");
}

TEST_F(SonyMakerNotePrintPixelShiftInfoTest_1602, ReturnsParenthesizedValueWhenTypeIsNotUndefined_1602) {
  // Any non-undefined type should trigger the parenthesized fallback.
  auto v = Exiv2::Value::create(Exiv2::unsignedByte);
  v->read("1 2 3 4 5 6");  // ensure count is non-zero and stable via public API
  std::ostringstream os;

  mn_.printPixelShiftInfo(os, *v, nullptr);

  const std::string inner = streamValue(*v);
  EXPECT_EQ(os.str(), "(" + inner + ")");
}

TEST_F(SonyMakerNotePrintPixelShiftInfoTest_1602, PrintsNaWhenAllSixUndefinedBytesAreZero_1602) {
  auto v = makeUndefinedValue({0, 0, 0, 0, 0, 0});
  std::ostringstream os;

  mn_.printPixelShiftInfo(os, *v, nullptr);

  EXPECT_EQ(os.str(), "n/a");
}

TEST_F(SonyMakerNotePrintPixelShiftInfoTest_1602, PrintsGroupAndShotInfoForNonZeroUndefinedValue_1602) {
  // Bytes 0..3 contribute to groupID, bytes 4..5 are shot counters (via toUint32()).
  auto v = makeUndefinedValue({1, 2, 3, 4, 5, 6});
  std::ostringstream os;

  ExifData exif;  // should be safe even if unused
  mn_.printPixelShiftInfo(os, *v, &exif);

  const std::string out = os.str();

  // Build expectations using only the publicly-visible formatting contract.
  const std::uint32_t b0 = 1, b1 = 2, b2 = 3, b3 = 4;
  const std::uint32_t groupID = (b3 << 24) + (b2 << 16) + (b1 << 8) + b0;

  const std::uint32_t g1 = (groupID >> 17) & 0x1f;
  const std::uint32_t g2 = (groupID >> 12) & 0x1f;
  const std::uint32_t g3 = (groupID >> 6) & 0x3f;
  const std::uint32_t g4 = groupID & 0x3f;

  std::ostringstream expectedPrefix;
  expectedPrefix << "Group " << std::setfill('0') << std::setw(2) << g1 << std::setw(2) << g2
                 << std::setw(2) << g3 << std::setw(2) << g4 << ", Shot 5/6 (0x";

  // Hex part: lowercase, no padding (matches "{:x}" style).
  std::ostringstream expectedHex;
  expectedHex << std::hex << std::nouppercase << (groupID >> 22);

  EXPECT_TRUE(out.rfind(expectedPrefix.str(), 0) == 0) << "Output was: " << out;
  EXPECT_NE(out.find(expectedHex.str()), std::string::npos) << "Output was: " << out;
  EXPECT_EQ(out.back(), ')') << "Output was: " << out;
}

}  // namespace