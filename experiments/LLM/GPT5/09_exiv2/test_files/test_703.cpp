// File: test_iptc_parser_decode_703.cpp
// Unit tests for Exiv2::IptcParser::decode (black-box)
// TEST_ID: 703

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "exiv2/iptc.hpp"
#include "exiv2/error.hpp"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::HasSubstr;
using ::testing::Mock;
using ::testing::StrEq;

namespace {

// IPTC IIM marker is commonly 0x1c. The decoder skips bytes until it sees marker_.
constexpr Exiv2::byte kIptcMarker = static_cast<Exiv2::byte>(0x1c);

std::vector<Exiv2::byte> MakeHeaderNonExtended(uint8_t record, uint8_t dataset, uint16_t sizeBE) {
  // marker, record, dataset, extTest(=0), size(2 bytes big-endian)
  std::vector<Exiv2::byte> v;
  v.push_back(kIptcMarker);
  v.push_back(static_cast<Exiv2::byte>(record));
  v.push_back(static_cast<Exiv2::byte>(dataset));
  v.push_back(static_cast<Exiv2::byte>(0x00));  // extTest, high bit not set
  v.push_back(static_cast<Exiv2::byte>((sizeBE >> 8) & 0xFF));
  v.push_back(static_cast<Exiv2::byte>(sizeBE & 0xFF));
  return v;
}

std::vector<Exiv2::byte> MakeHeaderExtended(uint8_t record, uint8_t dataset, uint16_t sizeOfSizeBE) {
  // marker, record, dataset, extTest(with 0x80 set), sizeOfSize (2 bytes big-endian)
  std::vector<Exiv2::byte> v;
  v.push_back(kIptcMarker);
  v.push_back(static_cast<Exiv2::byte>(record));
  v.push_back(static_cast<Exiv2::byte>(dataset));
  v.push_back(static_cast<Exiv2::byte>(0x80));  // extTest, high bit set
  v.push_back(static_cast<Exiv2::byte>((sizeOfSizeBE >> 8) & 0xFF));
  v.push_back(static_cast<Exiv2::byte>(sizeOfSizeBE & 0xFF));
  return v;
}

// ---- Log handler capture (for verifying warning emissions when enabled) ----

class MockLogHandler {
public:
  MOCK_METHOD(void, Handle, (int level, const char* msg), ());
};

// Exiv2::LogMsg::Handler is typically a function pointer: void(*)(int, const char*)
static MockLogHandler* g_mockHandler = nullptr;

static void TestLogHandlerThunk(int level, const char* s) {
  if (g_mockHandler) {
    g_mockHandler->Handle(level, s);
  }
}

struct ScopedLogHandler {
  explicit ScopedLogHandler(MockLogHandler* mock) : prev_(Exiv2::LogMsg::handler()), prevLevel_(Exiv2::LogMsg::level()) {
    g_mockHandler = mock;
    Exiv2::LogMsg::setHandler(&TestLogHandlerThunk);
    // Ensure warnings are not muted, in case global state is changed elsewhere.
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
  }

  ~ScopedLogHandler() {
    Exiv2::LogMsg::setHandler(prev_);
    Exiv2::LogMsg::setLevel(prevLevel_);
    g_mockHandler = nullptr;
  }

private:
  Exiv2::LogMsg::Handler prev_;
  Exiv2::LogMsg::Level prevLevel_;
};

}  // namespace

class IptcParserTest_703 : public ::testing::Test {
protected:
  Exiv2::IptcData iptc_;
};

TEST_F(IptcParserTest_703, DecodeClearsExistingDataEvenWhenSizeIsZero_703) {
  // Populate with something via the public operator[]; exact internal behavior is not assumed,
  // but the entry should exist if operator[] inserts on access.
  iptc_["Iptc.Application2.ObjectName"] = "preexisting";
  ASSERT_FALSE(iptc_.empty());

  const Exiv2::byte* data = nullptr;
  const size_t size = 0;

  const int rc = Exiv2::IptcParser::decode(iptc_, data, size);

  EXPECT_EQ(0, rc);
  EXPECT_TRUE(iptc_.empty());
  EXPECT_EQ(0u, iptc_.count());
}

TEST_F(IptcParserTest_703, DecodeSkipsNonMarkerBytesAndStillClearsData_703) {
  iptc_["Iptc.Application2.ObjectName"] = "preexisting";
  ASSERT_FALSE(iptc_.empty());

  // No 0x1c marker present => decoder should not parse any dataset.
  const std::vector<Exiv2::byte> bytes = {0x00, 0x11, 0x22, 0x33, 0x44};

  const int rc = Exiv2::IptcParser::decode(iptc_, bytes.data(), bytes.size());

  EXPECT_EQ(0, rc);
  EXPECT_TRUE(iptc_.empty());
  EXPECT_EQ(0u, iptc_.count());
}

TEST_F(IptcParserTest_703, DecodeReturnsZeroForOneValidHeaderWithZeroDataSize_703) {
  // One dataset header with sizeData = 0; no payload.
  std::vector<Exiv2::byte> bytes = MakeHeaderNonExtended(/*record*/ 2, /*dataset*/ 5, /*sizeBE*/ 0);

  const int rc = Exiv2::IptcParser::decode(iptc_, bytes.data(), bytes.size());

  EXPECT_EQ(0, rc);
  // We do NOT assert a specific metadata insertion; black-box.
  // At minimum, decode should be safe and produce a well-formed IptcData.
  EXPECT_GE(iptc_.count(), 0u);
}

TEST_F(IptcParserTest_703, DecodeReturnsZeroForMultipleZeroSizedDatasets_703) {
  std::vector<Exiv2::byte> bytes;
  const auto h1 = MakeHeaderNonExtended(/*record*/ 2, /*dataset*/ 5, /*sizeBE*/ 0);
  const auto h2 = MakeHeaderNonExtended(/*record*/ 2, /*dataset*/ 120, /*sizeBE*/ 0);
  bytes.insert(bytes.end(), h1.begin(), h1.end());
  bytes.insert(bytes.end(), h2.begin(), h2.end());

  const int rc = Exiv2::IptcParser::decode(iptc_, bytes.data(), bytes.size());

  EXPECT_EQ(0, rc);
  EXPECT_GE(iptc_.count(), 0u);
}

TEST_F(IptcParserTest_703, DecodeExtendedSizeOfSizeGreaterThanFourReturnsFive_703) {
  // extTest high-bit set and sizeOfSize = 5 (>4) => rc 5 per interface behavior.
  std::vector<Exiv2::byte> bytes = MakeHeaderExtended(/*record*/ 2, /*dataset*/ 5, /*sizeOfSizeBE*/ 5);

  const int rc = Exiv2::IptcParser::decode(iptc_, bytes.data(), bytes.size());

  EXPECT_EQ(5, rc);
  // decode() clears iptcData at entry.
  EXPECT_TRUE(iptc_.empty());
}

TEST_F(IptcParserTest_703, DecodeExtendedSizeOfSizeBeyondRemainingReturnsSix_703) {
  // extTest high-bit set, sizeOfSize=4 but buffer ends right after the 2-byte sizeOfSize field,
  // leaving 0 bytes for the size bytes => rc 6.
  std::vector<Exiv2::byte> bytes = MakeHeaderExtended(/*record*/ 2, /*dataset*/ 5, /*sizeOfSizeBE*/ 4);
  ASSERT_EQ(6u, bytes.size());  // exactly header length, no size bytes follow

  const int rc = Exiv2::IptcParser::decode(iptc_, bytes.data(), bytes.size());

  EXPECT_EQ(6, rc);
  EXPECT_TRUE(iptc_.empty());
}

TEST_F(IptcParserTest_703, DecodeInvalidDeclaredSizeReturnsSeven_703) {
  // Non-extended sizeData=16 but only 5 bytes of payload remain => rc 7.
  std::vector<Exiv2::byte> bytes = MakeHeaderNonExtended(/*record*/ 2, /*dataset*/ 5, /*sizeBE*/ 16);
  bytes.insert(bytes.end(), {0xAA, 0xBB, 0xCC, 0xDD, 0xEE});  // only 5 bytes payload

  ASSERT_LT(static_cast<size_t>(5), static_cast<size_t>(16));
  ASSERT_EQ(static_cast<size_t>(6 + 5), bytes.size());

#ifndef SUPPRESS_WARNINGS
  MockLogHandler mock;
  ScopedLogHandler scoped(&mock);

  // For invalid size, implementation logs a warning (when warnings are not suppressed).
  // We don't depend on exact message text; just that a warn-level handler is invoked.
  EXPECT_CALL(mock, Handle(static_cast<int>(Exiv2::LogMsg::warn), _)).Times(AtLeast(1));
#endif

  const int rc = Exiv2::IptcParser::decode(iptc_, bytes.data(), bytes.size());

  EXPECT_EQ(7, rc);
  EXPECT_TRUE(iptc_.empty());
}