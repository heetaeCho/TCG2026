// File: test_iptckey_tagdesc_645.cpp
// TEST_ID: 645

#include <gtest/gtest.h>

#include <cstdint>
#include <string>
#include <vector>

#include "exiv2/datasets.hpp"

namespace {

// Helper: search for (tag, record) pairs where IptcDataSets::dataSetDesc is non-null.
// This relies ONLY on the public interface and does not assume which datasets exist.
struct TagRecordPair {
  uint16_t tag;
  uint16_t record;
  const char* desc;  // non-null
};

std::vector<TagRecordPair> findNonNullDescPairs(std::size_t maxWanted) {
  std::vector<TagRecordPair> out;
  out.reserve(maxWanted);

  // Keep the scan modest to avoid long test runtimes.
  // Common IPTC records are small integers; tags are typically <= 0x00FF,
  // but we do not assume that—this is simply a bounded search space.
  for (uint16_t record = 0; record < 64 && out.size() < maxWanted; ++record) {
    for (uint16_t tag = 0; tag < 512 && out.size() < maxWanted; ++tag) {
      const char* desc = Exiv2::IptcDataSets::dataSetDesc(tag, record);
      if (desc != nullptr) {
        out.push_back(TagRecordPair{tag, record, desc});
      }
    }
  }
  return out;
}

class IptcKeyTagDescTest_645 : public ::testing::Test {};

}  // namespace

TEST_F(IptcKeyTagDescTest_645, TagDescMatchesIptcDataSetsForKnownNonNullPair_645) {
  const auto pairs = findNonNullDescPairs(/*maxWanted=*/1);
  ASSERT_FALSE(pairs.empty()) << "No non-null dataset descriptions found in bounded scan; "
                                 "cannot validate tagDesc() mapping.";

  const auto& p = pairs.front();
  Exiv2::IptcKey key(p.tag, p.record);

  // Only compare when dataSetDesc is known to be non-null to avoid UB converting nullptr to std::string.
  EXPECT_EQ(key.tagDesc(), std::string(p.desc));
}

TEST_F(IptcKeyTagDescTest_645, TagDescIsStableAcrossMultipleCalls_645) {
  const auto pairs = findNonNullDescPairs(/*maxWanted=*/1);
  ASSERT_FALSE(pairs.empty()) << "No non-null dataset descriptions found in bounded scan.";

  const auto& p = pairs.front();
  Exiv2::IptcKey key(p.tag, p.record);

  const std::string first = key.tagDesc();
  const std::string second = key.tagDesc();
  EXPECT_EQ(first, second);
}

TEST_F(IptcKeyTagDescTest_645, TagDescMatchesIptcDataSetsForSeveralPairsWhenAvailable_645) {
  const auto pairs = findNonNullDescPairs(/*maxWanted=*/3);
  ASSERT_FALSE(pairs.empty()) << "No non-null dataset descriptions found in bounded scan.";

  for (const auto& p : pairs) {
    Exiv2::IptcKey key(p.tag, p.record);
    EXPECT_EQ(key.tagDesc(), std::string(p.desc)) << "Mismatch for tag=" << p.tag << " record=" << p.record;
  }
}

TEST_F(IptcKeyTagDescTest_645, UnknownOrExtremePairDoesNotThrow_645) {
  // Boundary-ish values for constructor inputs.
  const uint16_t tag = static_cast<uint16_t>(0xFFFF);
  const uint16_t record = static_cast<uint16_t>(0xFFFF);

  Exiv2::IptcKey key(tag, record);

  // We don't assume what string is returned for unknown pairs; we only assert the call is safe/observable.
  EXPECT_NO_THROW({
    const std::string s = key.tagDesc();
    (void)s;
  });
}

TEST_F(IptcKeyTagDescTest_645, ZeroValuesDoNotThrow_645) {
  Exiv2::IptcKey key(/*tag=*/0, /*record=*/0);

  EXPECT_NO_THROW({
    const std::string s = key.tagDesc();
    (void)s;
  });

  // If the underlying dataset description is non-null for (0,0), then the mapping must match.
  // Otherwise, we intentionally do not assert a particular returned value.
  const char* desc = Exiv2::IptcDataSets::dataSetDesc(/*number=*/0, /*recordId=*/0);
  if (desc != nullptr) {
    EXPECT_EQ(key.tagDesc(), std::string(desc));
  }
}