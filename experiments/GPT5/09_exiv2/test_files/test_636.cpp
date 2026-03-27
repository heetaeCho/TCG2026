// File: datasets_recordname_test.cpp
// TEST_ID: 636

#include <gtest/gtest.h>

#include <exiv2/datasets.hpp>

#include <cstdint>
#include <iomanip>
#include <regex>
#include <sstream>
#include <string>

namespace {

std::string FormatHex4(uint16_t v) {
  std::ostringstream os;
  os << "0x" << std::hex << std::nouppercase << std::setfill('0') << std::setw(4)
     << static_cast<unsigned>(v);
  return os.str();
}

bool LooksLike0x4HexDigits(const std::string& s) {
  static const std::regex kRe("^0x[0-9a-f]{4}$");
  return std::regex_match(s, kRe);
}

}  // namespace

class IptcDataSetsTest_636 : public ::testing::Test {
 protected:
  Exiv2::IptcDataSets sut_;
};

TEST_F(IptcDataSetsTest_636, RecordName_EnvelopeReturnsEnvelope_636) {
  const std::string name = sut_.recordName(Exiv2::IptcDataSets::envelope);
  EXPECT_EQ("Envelope", name);
}

TEST_F(IptcDataSetsTest_636, RecordName_Application2ReturnsApplication2_636) {
  const std::string name = sut_.recordName(Exiv2::IptcDataSets::application2);
  EXPECT_EQ("Application2", name);
}

TEST_F(IptcDataSetsTest_636, RecordName_UnknownRecordReturns0xFormattedLowercase_636) {
  const uint16_t unknown = 0x1234;
  const std::string name = sut_.recordName(unknown);

  EXPECT_EQ(FormatHex4(unknown), name);
  EXPECT_TRUE(LooksLike0x4HexDigits(name));
}

TEST_F(IptcDataSetsTest_636, RecordName_BoundaryMaxUint16Returns0xFFFFFormatted_636) {
  const uint16_t maxv = static_cast<uint16_t>(0xFFFF);
  const std::string name = sut_.recordName(maxv);

  EXPECT_EQ(FormatHex4(maxv), name);
  EXPECT_TRUE(LooksLike0x4HexDigits(name));
}

TEST_F(IptcDataSetsTest_636, RecordName_InvalidRecordDoesNotCrashAndReturnsNonEmpty_636) {
  const uint16_t invalid = Exiv2::IptcDataSets::invalidRecord;
  const std::string name = sut_.recordName(invalid);

  EXPECT_FALSE(name.empty());
  // Observable behavior from interface: only Envelope and Application2 are special-cased.
  // For other record IDs, expect either a hex-formatted string or a non-empty fallback.
  EXPECT_TRUE(LooksLike0x4HexDigits(name) || name == "(invalid)");
}