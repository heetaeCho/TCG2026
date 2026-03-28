// ============================================================================
// Copyright ...
// Unit tests for Exiv2::Iptcdatum::groupName()
// File: ./TestProjects/exiv2/src/iptcdatum_groupname_test.cpp
// TEST_ID: 669
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include <exiv2/datasets.hpp>
#include <exiv2/iptc.hpp>

namespace {

class IptcdatumGroupNameTest_669 : public ::testing::Test {
 protected:
  static Exiv2::Iptcdatum MakeDatumFromKeyString(const std::string& keyStr) {
    Exiv2::IptcKey key(keyStr);
    // Value is not needed for groupName(); pass nullptr to avoid assuming any Value implementation.
    return Exiv2::Iptcdatum(key, nullptr);
  }

  static Exiv2::Iptcdatum MakeDatumFromTagRecord(uint16_t tag, uint16_t record) {
    Exiv2::IptcKey key(tag, record);
    return Exiv2::Iptcdatum(key, nullptr);
  }
};

TEST_F(IptcdatumGroupNameTest_669, GroupNameMatchesKeyGroupName_FromKeyString_669) {
  const std::string keyStr = "Iptc.Application2.ObjectName";

  Exiv2::IptcKey key(keyStr);
  Exiv2::Iptcdatum datum(key, nullptr);

  EXPECT_EQ(datum.groupName(), key.groupName());
}

TEST_F(IptcdatumGroupNameTest_669, GroupNameMatchesKeyGroupName_FromTagRecordTypical_669) {
  const uint16_t tag = 5;
  const uint16_t record = 2;

  Exiv2::IptcKey key(tag, record);
  Exiv2::Iptcdatum datum(key, nullptr);

  EXPECT_EQ(datum.groupName(), key.groupName());
}

TEST_F(IptcdatumGroupNameTest_669, GroupNameMatchesKeyGroupName_FromTagRecordBoundaryZero_669) {
  const uint16_t tag = 0;
  const uint16_t record = 0;

  Exiv2::IptcKey key(tag, record);
  Exiv2::Iptcdatum datum(key, nullptr);

  EXPECT_EQ(datum.groupName(), key.groupName());
}

TEST_F(IptcdatumGroupNameTest_669, GroupNameMatchesKeyGroupName_FromTagRecordBoundaryMax_669) {
  const uint16_t tag = static_cast<uint16_t>(0xFFFF);
  const uint16_t record = static_cast<uint16_t>(0xFFFF);

  Exiv2::IptcKey key(tag, record);
  Exiv2::Iptcdatum datum(key, nullptr);

  EXPECT_EQ(datum.groupName(), key.groupName());
}

TEST_F(IptcdatumGroupNameTest_669, CopyConstructedDatumPreservesGroupName_669) {
  Exiv2::Iptcdatum original = MakeDatumFromKeyString("Iptc.Application2.Caption");
  const std::string originalGroup = original.groupName();

  Exiv2::Iptcdatum copied(original);

  EXPECT_EQ(copied.groupName(), originalGroup);
  EXPECT_EQ(copied.groupName(), original.groupName());
}

TEST_F(IptcdatumGroupNameTest_669, CopyAssignedDatumPreservesGroupName_669) {
  Exiv2::Iptcdatum a = MakeDatumFromKeyString("Iptc.Application2.Keywords");
  Exiv2::Iptcdatum b = MakeDatumFromKeyString("Iptc.Application2.ObjectName");

  const std::string aGroup = a.groupName();

  b = a;

  EXPECT_EQ(b.groupName(), aGroup);
  EXPECT_EQ(b.groupName(), a.groupName());
}

TEST_F(IptcdatumGroupNameTest_669, SelfAssignmentDoesNotChangeGroupName_669) {
  Exiv2::Iptcdatum datum = MakeDatumFromKeyString("Iptc.Application2.Byline");
  const std::string before = datum.groupName();

  datum = datum;  // observable behavior: should remain valid and stable

  EXPECT_EQ(datum.groupName(), before);
}

TEST_F(IptcdatumGroupNameTest_669, GroupNameUnaffectedByAssigningStringValue_669) {
  Exiv2::Iptcdatum datum = MakeDatumFromKeyString("Iptc.Application2.City");
  const std::string before = datum.groupName();

  // Do not assume anything about parsing/validation of value strings; just ensure groupName is stable.
  (void)(datum = std::string("Seoul"));

  EXPECT_EQ(datum.groupName(), before);
}

TEST_F(IptcdatumGroupNameTest_669, GroupNameUnaffectedByAssigningUint16Value_669) {
  Exiv2::Iptcdatum datum = MakeDatumFromKeyString("Iptc.Application2.ProvinceState");
  const std::string before = datum.groupName();

  (void)(datum = static_cast<uint16_t>(123));

  EXPECT_EQ(datum.groupName(), before);
}

}  // namespace