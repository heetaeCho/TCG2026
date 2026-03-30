// File: test_IptcDataSets_dataSetPsName_633.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <string>

#include "exiv2/datasets.hpp"

namespace {

constexpr const char* kUnknown = "Unknown dataset";

// Finds any (number, recordId) pair where dataSetPsName() does NOT return the
// "Unknown dataset" string, by probing a small bounded space.
// This treats the implementation as a black box and relies only on observable behavior.
struct KnownPair {
  uint16_t number{0};
  uint16_t recordId{0};
  const char* psName{nullptr};
};

KnownPair FindAnyKnownPairOrSkip(Exiv2::IptcDataSets& ds) {
  // Keep bounded to avoid long-running tests.
  for (uint16_t recordId = 0; recordId <= 25; ++recordId) {
    for (uint16_t number = 0; number <= 255; ++number) {
      const char* ps = ds.dataSetPsName(number, recordId);
      if (ps != nullptr && std::string(ps) != kUnknown) {
        return KnownPair{number, recordId, ps};
      }
    }
  }

  // If the library is built without any dataset tables (or format differs),
  // we still validate unknown/boundary behavior in other tests.
  GTEST_SKIP() << "No known IPTC dataset pair found in probed range; "
                  "skipping known-pair tests.";
  return KnownPair{};
}

}  // namespace

class IptcDataSetsTest_633 : public ::testing::Test {
protected:
  Exiv2::IptcDataSets ds_;
};

TEST_F(IptcDataSetsTest_633, UnknownPairReturnsUnknownString_633) {
  const char* ps = ds_.dataSetPsName(/*number*/ 0, /*recordId*/ 0);

  ASSERT_NE(ps, nullptr);
  EXPECT_STREQ(ps, kUnknown);
}

TEST_F(IptcDataSetsTest_633, UnknownPairWithMaxValuesReturnsUnknownString_633) {
  const uint16_t max16 = std::numeric_limits<uint16_t>::max();

  const char* ps = ds_.dataSetPsName(/*number*/ max16, /*recordId*/ max16);

  ASSERT_NE(ps, nullptr);
  EXPECT_STREQ(ps, kUnknown);
}

TEST_F(IptcDataSetsTest_633, UnknownPairIsDeterministicAcrossCalls_633) {
  const uint16_t number = 123;
  const uint16_t recordId = 456;

  const char* ps1 = ds_.dataSetPsName(number, recordId);
  const char* ps2 = ds_.dataSetPsName(number, recordId);

  ASSERT_NE(ps1, nullptr);
  ASSERT_NE(ps2, nullptr);
  EXPECT_STREQ(ps1, ps2);
}

TEST_F(IptcDataSetsTest_633, KnownPairReturnsNonUnknownNonEmptyString_633) {
  const KnownPair kp = FindAnyKnownPairOrSkip(ds_);

  const char* ps = ds_.dataSetPsName(kp.number, kp.recordId);

  ASSERT_NE(ps, nullptr);
  EXPECT_STRNE(ps, kUnknown);
  EXPECT_FALSE(std::string(ps).empty());
}

TEST_F(IptcDataSetsTest_633, KnownPairIsDeterministicAcrossCalls_633) {
  const KnownPair kp = FindAnyKnownPairOrSkip(ds_);

  const char* ps1 = ds_.dataSetPsName(kp.number, kp.recordId);
  const char* ps2 = ds_.dataSetPsName(kp.number, kp.recordId);

  ASSERT_NE(ps1, nullptr);
  ASSERT_NE(ps2, nullptr);

  // Deterministic observable behavior: same C-string content for the same inputs.
  EXPECT_STREQ(ps1, ps2);
  EXPECT_STRNE(ps1, kUnknown);
}

TEST_F(IptcDataSetsTest_633, NeighboringNumberOftenDiffersOrFallsBackToUnknown_633) {
  const KnownPair kp = FindAnyKnownPairOrSkip(ds_);

  const uint16_t neighborNumber = static_cast<uint16_t>(kp.number + 1u);
  const char* psKnown = ds_.dataSetPsName(kp.number, kp.recordId);
  const char* psNeighbor = ds_.dataSetPsName(neighborNumber, kp.recordId);

  ASSERT_NE(psKnown, nullptr);
  ASSERT_NE(psNeighbor, nullptr);

  // Boundary-ish behavior around an existing entry: either a different dataset exists,
  // or it falls back to unknown. We don't assume table layout.
  const std::string sKnown(psKnown);
  const std::string sNeighbor(psNeighbor);

  EXPECT_STRNE(psKnown, kUnknown);
  EXPECT_TRUE(sNeighbor == kUnknown || sNeighbor != sKnown);
}