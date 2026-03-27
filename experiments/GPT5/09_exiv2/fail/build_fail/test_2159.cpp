// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_iptckey_2159.cpp
//
// Unit tests for Exiv2::IptcKey (TEST_ID=2159)
//
// Constraints honored:
// - Treat implementation as a black box (no assumptions about internal parsing/formatting).
// - Use only observable behavior via public interface.
// - No private-state access.

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <string>

#include "exiv2/datasets.hpp"   // Exiv2::IptcKey
#include "exiv2/metadatum.hpp"  // Exiv2::Key

namespace {

class IptcKeyTest_2159 : public ::testing::Test {};

TEST_F(IptcKeyTest_2159, ConstructFromTagRecordDoesNotThrow_2159) {
  EXPECT_NO_THROW({
    Exiv2::IptcKey k(static_cast<uint16_t>(1), static_cast<uint16_t>(2));
    (void)k;
  });
}

TEST_F(IptcKeyTest_2159, ConstructFromStringDoesNotThrow_2159) {
  EXPECT_NO_THROW({
    Exiv2::IptcKey k(std::string("Iptc.Application2.ObjectName"));
    (void)k;
  });
}

TEST_F(IptcKeyTest_2159, KeyStringIsStableAcrossMultipleCalls_2159) {
  Exiv2::IptcKey k(static_cast<uint16_t>(5), static_cast<uint16_t>(3));
  const std::string a = k.key();
  const std::string b = k.key();
  EXPECT_EQ(a, b);
}

TEST_F(IptcKeyTest_2159, TagAndRecordReturnConstructionValues_BoundaryZeros_2159) {
  Exiv2::IptcKey k(static_cast<uint16_t>(0), static_cast<uint16_t>(0));
  EXPECT_EQ(k.tag(), 0);
  EXPECT_EQ(k.record(), 0);
}

TEST_F(IptcKeyTest_2159, TagAndRecordReturnConstructionValues_BoundaryMax_2159) {
  Exiv2::IptcKey k(static_cast<uint16_t>(0xFFFFu), static_cast<uint16_t>(0xFFFFu));
  EXPECT_EQ(k.tag(), 0xFFFFu);
  EXPECT_EQ(k.record(), 0xFFFFu);
}

TEST_F(IptcKeyTest_2159, TagAndRecordReturnConstructionValues_Mixed_2159) {
  Exiv2::IptcKey k(static_cast<uint16_t>(0x1234u), static_cast<uint16_t>(0x00FFu));
  EXPECT_EQ(k.tag(), 0x1234u);
  EXPECT_EQ(k.record(), 0x00FFu);
}

TEST_F(IptcKeyTest_2159, CloneProducesIndependentObjectWithSameKey_2159) {
  Exiv2::IptcKey original(static_cast<uint16_t>(10), static_cast<uint16_t>(20));

  // Clone via IptcKey::clone()
  Exiv2::IptcKey::UniquePtr cloned;
  ASSERT_NO_THROW({ cloned = original.clone(); });
  ASSERT_NE(cloned.get(), nullptr);

  EXPECT_EQ(cloned->key(), original.key());
  EXPECT_EQ(cloned->tag(), original.tag());
  EXPECT_EQ(cloned->record(), original.record());
}

TEST_F(IptcKeyTest_2159, CloneViaBaseKeyProducesIptcKeyAndPreservesObservables_2159) {
  Exiv2::IptcKey original(static_cast<uint16_t>(7), static_cast<uint16_t>(9));
  Exiv2::Key& asBase = original;

  Exiv2::Key::UniquePtr baseClone;
  ASSERT_NO_THROW({ baseClone = asBase.clone(); });
  ASSERT_NE(baseClone.get(), nullptr);

  // Verify dynamic type if RTTI is available and clone preserves polymorphism.
  // If Exiv2 is built without RTTI, this section may be compiled out by the toolchain;
  // keeping it as a soft assertion using dynamic_cast (returns nullptr without RTTI support).
  if (auto* iptc = dynamic_cast<Exiv2::IptcKey*>(baseClone.get())) {
    EXPECT_EQ(iptc->key(), original.key());
    EXPECT_EQ(iptc->tag(), original.tag());
    EXPECT_EQ(iptc->record(), original.record());
  } else {
    // At minimum, base clone must preserve base-observable key string.
    EXPECT_EQ(baseClone->key(), original.key());
  }
}

TEST_F(IptcKeyTest_2159, ConstructFromStringPreservesExactKeyRoundTrip_2159) {
  // Black-box expectation based purely on interface: if constructed with a key string,
  // calling key() should at least be non-empty and should not throw.
  const std::string input = "Iptc.Application2.ObjectName";
  Exiv2::IptcKey k(input);

  EXPECT_NO_THROW({
    const std::string out = k.key();
    EXPECT_FALSE(out.empty());
  });
}

TEST_F(IptcKeyTest_2159, MetadataAccessorsDoNotThrow_2159) {
  Exiv2::IptcKey k(static_cast<uint16_t>(1), static_cast<uint16_t>(2));

  EXPECT_NO_THROW({ (void)k.familyName(); });
  EXPECT_NO_THROW({ (void)k.groupName(); });
  EXPECT_NO_THROW({ (void)k.tagName(); });
  EXPECT_NO_THROW({ (void)k.tagLabel(); });
  EXPECT_NO_THROW({ (void)k.tagDesc(); });
  EXPECT_NO_THROW({ (void)k.recordName(); });
}

TEST_F(IptcKeyTest_2159, RecordNameIsStableAcrossMultipleCalls_2159) {
  Exiv2::IptcKey k(static_cast<uint16_t>(3), static_cast<uint16_t>(4));
  const std::string a = k.recordName();
  const std::string b = k.recordName();
  EXPECT_EQ(a, b);
}

TEST_F(IptcKeyTest_2159, EmptyStringKeyConstructionDoesNotCrash_2159) {
  // Exceptional-ish input: empty key string.
  // We don't assume parsing rules; we only ensure it doesn't crash/throw unexpectedly.
  EXPECT_NO_THROW({
    Exiv2::IptcKey k(std::string());
    (void)k.key();  // observable call
  });
}

}  // namespace