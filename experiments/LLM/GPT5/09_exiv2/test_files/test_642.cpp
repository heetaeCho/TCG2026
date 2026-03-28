// File: test_iptckey_groupname_642.cpp
// TEST_ID: 642

#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include "exiv2/datasets.hpp"

namespace {

// Fixture name includes TEST_ID per requirement.
class IptcKeyTest_642 : public ::testing::Test {};

TEST_F(IptcKeyTest_642, GroupNameEqualsRecordName_ForTagRecordCtor_CommonValues_642) {
  const Exiv2::IptcKey k1(/*tag=*/0u, /*record=*/0u);
  EXPECT_EQ(k1.groupName(), k1.recordName());

  const Exiv2::IptcKey k2(/*tag=*/1u, /*record=*/1u);
  EXPECT_EQ(k2.groupName(), k2.recordName());

  const Exiv2::IptcKey k3(/*tag=*/42u, /*record=*/2u);
  EXPECT_EQ(k3.groupName(), k3.recordName());
}

TEST_F(IptcKeyTest_642, GroupNameEqualsRecordName_ForTagRecordCtor_BoundaryValues_642) {
  const Exiv2::IptcKey kMin(/*tag=*/0u, /*record=*/0u);
  EXPECT_EQ(kMin.groupName(), kMin.recordName());

  const Exiv2::IptcKey kMax(/*tag=*/static_cast<uint16_t>(0xFFFF),
                           /*record=*/static_cast<uint16_t>(0xFFFF));
  EXPECT_EQ(kMax.groupName(), kMax.recordName());

  const Exiv2::IptcKey kMixed1(/*tag=*/static_cast<uint16_t>(0xFFFF), /*record=*/0u);
  EXPECT_EQ(kMixed1.groupName(), kMixed1.recordName());

  const Exiv2::IptcKey kMixed2(/*tag=*/0u, /*record=*/static_cast<uint16_t>(0xFFFF));
  EXPECT_EQ(kMixed2.groupName(), kMixed2.recordName());
}

TEST_F(IptcKeyTest_642, GroupNameEqualsRecordName_ForStringCtor_ValidLookingKeys_642) {
  // We do NOT assume any specific parsed values; only that groupName() mirrors recordName().
  const Exiv2::IptcKey k1(std::string("Iptc.Application2.Headline"));
  EXPECT_EQ(k1.groupName(), k1.recordName());

  const Exiv2::IptcKey k2(std::string("Iptc.Envelope.ModelVersion"));
  EXPECT_EQ(k2.groupName(), k2.recordName());

  const Exiv2::IptcKey k3(std::string("Iptc.Application2.ObjectName"));
  EXPECT_EQ(k3.groupName(), k3.recordName());
}

TEST_F(IptcKeyTest_642, GroupNameIsStableAcrossRepeatedCalls_642) {
  const Exiv2::IptcKey k(/*tag=*/5u, /*record=*/7u);

  const std::string g1 = k.groupName();
  const std::string r1 = k.recordName();
  EXPECT_EQ(g1, r1);

  const std::string g2 = k.groupName();
  const std::string r2 = k.recordName();
  EXPECT_EQ(g2, r2);

  // Stability: repeated calls return the same observable values.
  EXPECT_EQ(g1, g2);
  EXPECT_EQ(r1, r2);
}

TEST_F(IptcKeyTest_642, GroupNameDoesNotModifyObject_ConstUsage_642) {
  const Exiv2::IptcKey k(/*tag=*/9u, /*record=*/3u);

  // Ensure callable on const object and consistent with recordName().
  const Exiv2::IptcKey& ck = k;
  EXPECT_EQ(ck.groupName(), ck.recordName());
}

}  // namespace