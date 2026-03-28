// TEST_ID 693
// Unit tests for Exiv2::IptcData::size() based on observable behavior via public API.

#include <gtest/gtest.h>

#include <string>

#include <exiv2/iptc.hpp>

namespace {

class IptcDataSizeTest_693 : public ::testing::Test {
 protected:
  static std::string MakeStringOfSize(size_t n, char c = 'A') { return std::string(n, c); }

  static size_t DatumContribution_693(const Exiv2::Iptcdatum& d) {
    const size_t dataSize = d.size();
    // Based on the provided partial implementation of IptcData::size().
    return 5u + dataSize + (dataSize > 32767u ? 4u : 0u);
  }
};

TEST_F(IptcDataSizeTest_693, EmptyHasSizeZero_693) {
  Exiv2::IptcData data;
  EXPECT_EQ(0u, data.size());
}

TEST_F(IptcDataSizeTest_693, SingleDatumAddsFixedHeaderPlusDatumSize_693) {
  Exiv2::IptcData data;

  Exiv2::Iptcdatum& d1 = data["Iptc.Application2.ObjectName"];
  d1 = std::string("abc");

  const size_t expected = DatumContribution_693(d1);
  EXPECT_EQ(expected, data.size());
}

TEST_F(IptcDataSizeTest_693, MultipleDataSumContributions_693) {
  Exiv2::IptcData data;

  Exiv2::Iptcdatum& d1 = data["Iptc.Application2.ObjectName"];
  d1 = std::string("hello");

  Exiv2::Iptcdatum& d2 = data["Iptc.Application2.Caption"];
  d2 = std::string("world!");

  const size_t expected = DatumContribution_693(d1) + DatumContribution_693(d2);
  EXPECT_EQ(expected, data.size());
}

TEST_F(IptcDataSizeTest_693, BoundaryAt32767DoesNotIncludeExtendedLengthOverhead_693) {
  Exiv2::IptcData data;

  Exiv2::Iptcdatum& d = data["Iptc.Application2.Caption"];
  d = MakeStringOfSize(32767);

  ASSERT_EQ(32767u, d.size()) << "Precondition failed: datum.size() should reflect the stored value size.";
  EXPECT_EQ(5u + 32767u, data.size());
}

TEST_F(IptcDataSizeTest_693, BoundaryAbove32767IncludesExtendedLengthOverhead_693) {
  Exiv2::IptcData data;

  Exiv2::Iptcdatum& d = data["Iptc.Application2.Caption"];
  d = MakeStringOfSize(32768);

  ASSERT_EQ(32768u, d.size()) << "Precondition failed: datum.size() should reflect the stored value size.";
  EXPECT_EQ(5u + 32768u + 4u, data.size());
}

TEST_F(IptcDataSizeTest_693, CrossingThresholdFrom32767To32768IncreasesTotalBy5_693) {
  Exiv2::IptcData data;

  Exiv2::Iptcdatum& d = data["Iptc.Application2.Caption"];
  d = MakeStringOfSize(32767);
  ASSERT_EQ(32767u, d.size());
  const size_t sizeAt32767 = data.size();

  d = MakeStringOfSize(32768);
  ASSERT_EQ(32768u, d.size());
  const size_t sizeAt32768 = data.size();

  // One extra byte in the data + the additional 4 bytes once dataSize > 32767.
  EXPECT_EQ(sizeAt32767 + 5u, sizeAt32768);
}

TEST_F(IptcDataSizeTest_693, VeryLargeDatumStillAccountsForExtendedLengthOnce_693) {
  Exiv2::IptcData data;

  Exiv2::Iptcdatum& d = data["Iptc.Application2.Keywords"];
  d = MakeStringOfSize(40000);

  ASSERT_GT(d.size(), 32767u);
  EXPECT_EQ(DatumContribution_693(d), data.size());
}

TEST_F(IptcDataSizeTest_693, OperatorBracketWithInvalidKeyThrows_693) {
  Exiv2::IptcData data;

  // Invalid IPTC key format should be observable as an exception (exact type is not required here).
  EXPECT_ANY_THROW((void)data["NotAReal.Key.Format"]);
}

}  // namespace