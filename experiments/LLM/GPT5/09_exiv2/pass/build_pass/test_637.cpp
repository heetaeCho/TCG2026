// =================================================================================================
// TEST_ID: 637
// File: test_iptcdatasets_recorddesc_637.cpp
// Unit tests for Exiv2::IptcDataSets::recordDesc(uint16_t)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include <exiv2/datasets.hpp>

namespace {

class IptcDataSetsTest_637 : public ::testing::Test {
 protected:
  Exiv2::IptcDataSets ds_;
};

TEST_F(IptcDataSetsTest_637, RecordDesc_Envelope_IsNotNullAndIsStable_637) {
  const char* desc1 = ds_.recordDesc(Exiv2::IptcDataSets::envelope);
  const char* desc2 = ds_.recordDesc(Exiv2::IptcDataSets::envelope);

  ASSERT_NE(desc1, nullptr);
  ASSERT_NE(desc2, nullptr);
  EXPECT_STREQ(desc1, desc2);
}

TEST_F(IptcDataSetsTest_637, RecordDesc_Application2_IsNotNullAndIsStable_637) {
  const char* desc1 = ds_.recordDesc(Exiv2::IptcDataSets::application2);
  const char* desc2 = ds_.recordDesc(Exiv2::IptcDataSets::application2);

  ASSERT_NE(desc1, nullptr);
  ASSERT_NE(desc2, nullptr);
  EXPECT_STREQ(desc1, desc2);
}

TEST_F(IptcDataSetsTest_637, RecordDesc_NonSupportedRecordIds_ReturnSameUnknownText_637) {
  // Use a few representative "other" ids, including a boundary value.
  const uint16_t other1 = static_cast<uint16_t>(Exiv2::IptcDataSets::invalidRecord);
  const uint16_t other2 = static_cast<uint16_t>(3u);
  const uint16_t other3 = static_cast<uint16_t>(9999u);
  const uint16_t other4 = std::numeric_limits<uint16_t>::max();

  const char* u1 = ds_.recordDesc(other1);
  const char* u2 = ds_.recordDesc(other2);
  const char* u3 = ds_.recordDesc(other3);
  const char* u4 = ds_.recordDesc(other4);

  ASSERT_NE(u1, nullptr);
  ASSERT_NE(u2, nullptr);
  ASSERT_NE(u3, nullptr);
  ASSERT_NE(u4, nullptr);

  // Observable behavior: all "other" IDs map to the same unknown description text.
  EXPECT_STREQ(u1, u2);
  EXPECT_STREQ(u1, u3);
  EXPECT_STREQ(u1, u4);
}

TEST_F(IptcDataSetsTest_637, RecordDesc_KnownRecords_DifferFromUnknown_637) {
  const char* envelopeDesc = ds_.recordDesc(Exiv2::IptcDataSets::envelope);
  const char* app2Desc = ds_.recordDesc(Exiv2::IptcDataSets::application2);
  const char* unknownDesc = ds_.recordDesc(static_cast<uint16_t>(Exiv2::IptcDataSets::invalidRecord));

  ASSERT_NE(envelopeDesc, nullptr);
  ASSERT_NE(app2Desc, nullptr);
  ASSERT_NE(unknownDesc, nullptr);

  // Compare by content (not pointer identity).
  EXPECT_STRNE(envelopeDesc, unknownDesc);
  EXPECT_STRNE(app2Desc, unknownDesc);

  // Sanity: the two known descriptions should not be identical.
  EXPECT_STRNE(envelopeDesc, app2Desc);
}

}  // namespace