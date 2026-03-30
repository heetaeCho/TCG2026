// File: test_iptckey_makekey_651.cpp
// The TEST_ID is 651

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <string>

#include "exiv2/datasets.hpp"

namespace {

class IptcKeyTest_651 : public ::testing::Test {
 protected:
  static std::string ExpectedComposedKey(const Exiv2::IptcKey& k) {
    // Based strictly on the provided interface and the visible makeKey() composition pattern:
    // familyName + "." + IptcDataSets::recordName(record) + "." + IptcDataSets::dataSetName(tag, record)
    const std::string fam = k.familyName() ? std::string(k.familyName()) : std::string();
    const uint16_t rec = k.record();
    const uint16_t tag = k.tag();
    return fam + "." + Exiv2::IptcDataSets::recordName(rec) + "." + Exiv2::IptcDataSets::dataSetName(tag, rec);
  }
};

TEST_F(IptcKeyTest_651, KeyFromTagRecord_ComposesExpected_651) {
  const uint16_t tag = 5;
  const uint16_t record = 2;

  Exiv2::IptcKey k(tag, record);

  std::string keyStr;
  EXPECT_NO_THROW(keyStr = k.key());
  EXPECT_FALSE(keyStr.empty());

  // Verify exact composition using only public, observable collaborators.
  EXPECT_EQ(keyStr, ExpectedComposedKey(k));

  // Also verify getters preserve constructor inputs.
  EXPECT_EQ(k.tag(), tag);
  EXPECT_EQ(k.record(), record);
  EXPECT_STREQ(k.familyName(), "Iptc");
}

TEST_F(IptcKeyTest_651, KeyIsStableAcrossMultipleCalls_651) {
  Exiv2::IptcKey k(/*tag*/ 25, /*record*/ 2);

  const std::string k1 = k.key();
  const std::string k2 = k.key();
  const std::string k3 = k.key();

  EXPECT_EQ(k1, k2);
  EXPECT_EQ(k2, k3);
  EXPECT_EQ(k1, ExpectedComposedKey(k));
}

TEST_F(IptcKeyTest_651, Boundary_ZeroTagZeroRecord_651) {
  Exiv2::IptcKey k(/*tag*/ 0, /*record*/ 0);

  std::string keyStr;
  EXPECT_NO_THROW(keyStr = k.key());
  EXPECT_FALSE(keyStr.empty());

  EXPECT_EQ(keyStr, ExpectedComposedKey(k));
  EXPECT_EQ(k.tag(), 0);
  EXPECT_EQ(k.record(), 0);
}

TEST_F(IptcKeyTest_651, Boundary_MaxUint16TagAndRecord_651) {
  const uint16_t tag = static_cast<uint16_t>(0xFFFF);
  const uint16_t record = static_cast<uint16_t>(0xFFFF);

  Exiv2::IptcKey k(tag, record);

  std::string keyStr;
  EXPECT_NO_THROW(keyStr = k.key());
  EXPECT_FALSE(keyStr.empty());

  EXPECT_EQ(keyStr, ExpectedComposedKey(k));
  EXPECT_EQ(k.tag(), tag);
  EXPECT_EQ(k.record(), record);
}

TEST_F(IptcKeyTest_651, ConstructorFromString_PreservesProvidedKey_651) {
  const std::string raw = "Iptc.Application2.ObjectName";
  Exiv2::IptcKey k(raw);

  std::string keyStr;
  EXPECT_NO_THROW(keyStr = k.key());
  EXPECT_EQ(keyStr, raw);

  // Family name is part of the Key interface; ensure it remains the IPTC family.
  EXPECT_STREQ(k.familyName(), "Iptc");
}

TEST_F(IptcKeyTest_651, Clone_ProducesIndependentKeyWithSameObservableProperties_651) {
  Exiv2::IptcKey original(/*tag*/ 5, /*record*/ 2);
  const std::string originalKey = original.key();

  Exiv2::IptcKey::UniquePtr clone;
  ASSERT_NO_THROW(clone = original.clone());
  ASSERT_NE(clone.get(), nullptr);

  EXPECT_EQ(clone->key(), originalKey);
  EXPECT_EQ(clone->tag(), original.tag());
  EXPECT_EQ(clone->record(), original.record());
  EXPECT_STREQ(clone->familyName(), original.familyName());

  // Basic "independence" check: clone is a distinct object.
  EXPECT_NE(clone.get(), &original);
}

}  // namespace