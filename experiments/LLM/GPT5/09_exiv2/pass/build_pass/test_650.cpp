// File: test_650_iptckey_decomposekey.cpp
// TEST_ID: 650

#include <gtest/gtest.h>

#include <exiv2/datasets.hpp>
#include <exiv2/error.hpp>

#include <string>
#include <vector>

namespace {

class IptcKeyTest_650 : public ::testing::Test {
 protected:
  // Expose protected API through inheritance (part of the class interface for derived classes).
  struct TestableIptcKey : public Exiv2::IptcKey {
    using Exiv2::IptcKey::IptcKey;
    using Exiv2::IptcKey::decomposeKey;
  };

  // Pick a likely-valid IPTC key without relying on internal tables.
  // We do NOT assume any candidate is valid; we just try a small set and require at least one works.
  static std::string FindAnyValidKeyOrEmpty() {
    const std::vector<std::string> candidates = {
        "Iptc.Envelope.ModelVersion",
        "Iptc.Application2.ObjectName",
        "Iptc.Application2.Caption",
        "Iptc.Application2.Keywords",
    };

    for (const auto& k : candidates) {
      try {
        TestableIptcKey key(k);
        key.decomposeKey();
        // If decomposeKey succeeds, we consider it valid.
        return k;
      } catch (const Exiv2::Error&) {
        // try next candidate
      } catch (...) {
        // Any other exception means this candidate isn't usable here.
      }
    }
    return {};
  }
};

TEST_F(IptcKeyTest_650, DecomposeKey_ValidKeyNormalizesAndIsSelfConsistent_650) {
  const std::string anyValid = FindAnyValidKeyOrEmpty();
  ASSERT_FALSE(anyValid.empty()) << "No valid IPTC key candidate succeeded; test cannot proceed.";

  TestableIptcKey key(anyValid);
  EXPECT_NO_THROW(key.decomposeKey());

  const std::string family = key.familyName();
  const std::string recName = key.recordName();
  const std::string dsName = key.tagName();
  const uint16_t rec = key.record();
  const uint16_t tag = key.tag();

  EXPECT_EQ(family, "Iptc");
  EXPECT_FALSE(recName.empty());
  EXPECT_FALSE(dsName.empty());

  // The interface should be internally consistent after decomposition/canonicalization.
  EXPECT_EQ(recName, Exiv2::IptcDataSets::recordName(rec));
  EXPECT_EQ(dsName, Exiv2::IptcDataSets::dataSetName(tag, rec));
  EXPECT_EQ(key.key(), std::string("Iptc.") + recName + "." + dsName);

  // Basic shape check: exactly two dots in the canonical key.
  const std::string kk = key.key();
  const auto dot1 = kk.find('.');
  const auto dot2 = kk.find('.', dot1 == std::string::npos ? 0 : dot1 + 1);
  EXPECT_NE(dot1, std::string::npos);
  EXPECT_NE(dot2, std::string::npos);
  EXPECT_EQ(kk.find('.', dot2 + 1), std::string::npos);
}

TEST_F(IptcKeyTest_650, DecomposeKey_ThrowsWhenNoDotsPresent_650) {
  TestableIptcKey key("IptcEnvelopeModelVersion");
  EXPECT_THROW(key.decomposeKey(), Exiv2::Error);
}

TEST_F(IptcKeyTest_650, DecomposeKey_ThrowsWhenOnlyOneDotPresent_650) {
  TestableIptcKey key("Iptc.EnvelopeModelVersion");
  EXPECT_THROW(key.decomposeKey(), Exiv2::Error);
}

TEST_F(IptcKeyTest_650, DecomposeKey_ThrowsWhenFamilyNameMismatches_650) {
  // Family must match the IPTC family ("Iptc").
  TestableIptcKey key("Exif.Envelope.ModelVersion");
  EXPECT_THROW(key.decomposeKey(), Exiv2::Error);
}

TEST_F(IptcKeyTest_650, DecomposeKey_ThrowsWhenRecordNameIsEmpty_650) {
  // Boundary: empty record segment between dots.
  TestableIptcKey key("Iptc..ModelVersion");
  EXPECT_THROW(key.decomposeKey(), Exiv2::Error);
}

TEST_F(IptcKeyTest_650, DecomposeKey_ThrowsWhenDataSetNameIsEmpty_650) {
  // Boundary: empty dataset segment after second dot.
  TestableIptcKey key("Iptc.Envelope.");
  EXPECT_THROW(key.decomposeKey(), Exiv2::Error);
}

TEST_F(IptcKeyTest_650, DecomposeKey_ThrowsWhenRecordAndDataSetAreBothEmpty_650) {
  // Boundary: both segments empty.
  TestableIptcKey key("Iptc..");
  EXPECT_THROW(key.decomposeKey(), Exiv2::Error);
}

TEST_F(IptcKeyTest_650, DecomposeKey_ThrowsWhenDataSetContainsExtraDot_650) {
  // Boundary: extra dot makes dataset name include a dot; should be rejected by dataset lookup.
  TestableIptcKey key("Iptc.Envelope.Model.Version");
  EXPECT_THROW(key.decomposeKey(), Exiv2::Error);
}

}  // namespace