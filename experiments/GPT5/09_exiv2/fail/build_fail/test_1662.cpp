// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_tiffdecoder_decodeTiffEntry_1662.cpp

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>

// Internal headers (as provided by the codebase)
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

namespace {

using ::testing::_;
using ::testing::Eq;
using ::testing::StrEq;

using Exiv2::ByteOrder;
using Exiv2::ExifData;
using Exiv2::IptcData;
using Exiv2::XmpData;

using Exiv2::Internal::FindDecoderFct;
using Exiv2::Internal::TiffDecoder;
using Exiv2::Internal::TiffEntryBase;

// Create any non-null Exiv2::Value. The content is not important for these tests;
// we only need pValue() to be non-null to pass the early-return guard.
static Exiv2::Value::UniquePtr makeNonNullValue() {
  // Use a common Value factory path (works broadly across Exiv2).
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedByte);
  if (v) {
    // Best-effort: ensure it's "initialized"; behavior is not asserted.
    (void)v->read("1");
  }
  return v;
}

class TiffDecoderTest_1662 : public ::testing::Test {
 protected:
  ExifData exif_;
  IptcData iptc_;
  XmpData xmp_;

  // Helper to construct a minimal TiffEntryBase.
  static TiffEntryBase makeEntry(uint16_t tag, Exiv2::IfdId group) {
    // Avoid assuming any particular enumerator exists for TiffType; cast from 0.
    auto tiffType = static_cast<Exiv2::Internal::TiffType>(0);
    return TiffEntryBase(tag, group, tiffType);
  }
};

TEST_F(TiffDecoderTest_1662, ReturnsEarlyWhenPValueIsNull_DoesNotCallFindDecoder_1662) {
  int find_calls = 0;

  FindDecoderFct find = [&](const std::string& /*make*/, uint16_t /*tag*/, Exiv2::IfdId /*group*/) {
    ++find_calls;

    // Return "no decoder". We deliberately do not assume the exact return type;
    // default construction should represent "empty"/null in typical implementations.
    using Ret = std::invoke_result_t<FindDecoderFct, const std::string&, uint16_t, Exiv2::IfdId>;
    return Ret{};
  };

  TiffDecoder decoder(exif_, iptc_, xmp_, /*pRoot=*/nullptr, find);

  auto entry = makeEntry(/*tag=*/0x1234, static_cast<Exiv2::IfdId>(0));
  entry.setValue(Exiv2::Value::UniquePtr{});  // ensure pValue() == nullptr

  decoder.decodeTiffEntry(&entry);

  EXPECT_EQ(find_calls, 0) << "findDecoderFct must not be called when pValue() is null";
}

TEST_F(TiffDecoderTest_1662, CallsFindDecoderWithMakeTagGroup_WhenPValueIsNonNull_1662) {
  int find_calls = 0;

  const uint16_t kTag = 0x00AA;
  const Exiv2::IfdId kGroup = static_cast<Exiv2::IfdId>(0);

  FindDecoderFct find = [&](const std::string& make, uint16_t tag, Exiv2::IfdId group) {
    ++find_calls;
    // make_ is an internal detail, but it's observable here as a parameter.
    // In typical flows, make_ may be empty unless set elsewhere; this test only checks consistency.
    EXPECT_THAT(tag, Eq(kTag));
    EXPECT_THAT(group, Eq(kGroup));
    EXPECT_THAT(make, StrEq(""));  // best-effort expectation for a fresh decoder

    using Ret = std::invoke_result_t<FindDecoderFct, const std::string&, uint16_t, Exiv2::IfdId>;
    return Ret{};  // "no decoder": we only verify the external interaction
  };

  TiffDecoder decoder(exif_, iptc_, xmp_, /*pRoot=*/nullptr, find);

  auto entry = makeEntry(kTag, kGroup);
  entry.setValue(makeNonNullValue());  // ensure pValue() != nullptr

  decoder.decodeTiffEntry(&entry);

  EXPECT_EQ(find_calls, 1);
}

TEST_F(TiffDecoderTest_1662, BoundaryTags_AreForwardedToFindDecoder_1662) {
  struct Call {
    uint16_t tag{};
    Exiv2::IfdId group{};
    std::string make;
  };
  std::vector<Call> calls;

  FindDecoderFct find = [&](const std::string& make, uint16_t tag, Exiv2::IfdId group) {
    calls.push_back(Call{tag, group, make});
    using Ret = std::invoke_result_t<FindDecoderFct, const std::string&, uint16_t, Exiv2::IfdId>;
    return Ret{};
  };

  TiffDecoder decoder(exif_, iptc_, xmp_, /*pRoot=*/nullptr, find);

  const Exiv2::IfdId kGroup = static_cast<Exiv2::IfdId>(0);

  auto e0 = makeEntry(/*tag=*/0x0000, kGroup);
  e0.setValue(makeNonNullValue());
  decoder.decodeTiffEntry(&e0);

  auto eMax = makeEntry(/*tag=*/0xFFFF, kGroup);
  eMax.setValue(makeNonNullValue());
  decoder.decodeTiffEntry(&eMax);

  ASSERT_EQ(calls.size(), 2u);
  EXPECT_EQ(calls[0].tag, 0x0000);
  EXPECT_EQ(calls[1].tag, 0xFFFF);
}

TEST_F(TiffDecoderTest_1662, PropagatesExceptionFromFindDecoderFct_WhenInvoked_1662) {
  FindDecoderFct find = [&](const std::string& /*make*/, uint16_t /*tag*/, Exiv2::IfdId /*group*/) {
    throw std::runtime_error("findDecoderFct failure");
    using Ret = std::invoke_result_t<FindDecoderFct, const std::string&, uint16_t, Exiv2::IfdId>;
    return Ret{};
  };

  TiffDecoder decoder(exif_, iptc_, xmp_, /*pRoot=*/nullptr, find);

  auto entry = makeEntry(/*tag=*/0x0100, static_cast<Exiv2::IfdId>(0));
  entry.setValue(makeNonNullValue());

  EXPECT_THROW(decoder.decodeTiffEntry(&entry), std::runtime_error);
}

}  // namespace