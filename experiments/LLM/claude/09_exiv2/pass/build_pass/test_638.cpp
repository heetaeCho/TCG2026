#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "exiv2/datasets.hpp"
#include "exiv2/error.hpp"

namespace {

using Exiv2::IptcDataSets;

// ============================================================
// Tests for recordId(const std::string&)
// ============================================================

TEST(IptcDataSetsTest_638, RecordIdEnvelope_638) {
  // "Envelope" should map to the envelope record id (1)
  uint16_t id = IptcDataSets::recordId("Envelope");
  EXPECT_EQ(id, IptcDataSets::envelope);
}

TEST(IptcDataSetsTest_638, RecordIdApplication2_638) {
  // "Application2" should map to the application2 record id (2)
  uint16_t id = IptcDataSets::recordId("Application2");
  EXPECT_EQ(id, IptcDataSets::application2);
}

TEST(IptcDataSetsTest_638, RecordIdHexValid_638) {
  // A valid hex string like "0x0001" should return 1
  uint16_t id = IptcDataSets::recordId("0x0001");
  EXPECT_EQ(id, 1);
}

TEST(IptcDataSetsTest_638, RecordIdHexApplication2_638) {
  // "0x0002" should return 2
  uint16_t id = IptcDataSets::recordId("0x0002");
  EXPECT_EQ(id, 2);
}

TEST(IptcDataSetsTest_638, RecordIdHexArbitrary_638) {
  // "0x00ff" should return 255
  uint16_t id = IptcDataSets::recordId("0x00ff");
  EXPECT_EQ(id, 255);
}

TEST(IptcDataSetsTest_638, RecordIdInvalidNameThrows_638) {
  // An invalid record name that is not a valid hex string should throw
  EXPECT_THROW(IptcDataSets::recordId("NonExistentRecord"), Exiv2::Error);
}

TEST(IptcDataSetsTest_638, RecordIdEmptyStringThrows_638) {
  // An empty string is neither a known name nor a valid hex string
  EXPECT_THROW(IptcDataSets::recordId(""), Exiv2::Error);
}

TEST(IptcDataSetsTest_638, RecordIdHexZero_638) {
  // "0x0000" — hex parse yields 0
  uint16_t id = IptcDataSets::recordId("0x0000");
  EXPECT_EQ(id, 0);
}

// ============================================================
// Tests for recordName(uint16_t)
// ============================================================

TEST(IptcDataSetsTest_638, RecordNameEnvelope_638) {
  std::string name = IptcDataSets::recordName(IptcDataSets::envelope);
  EXPECT_EQ(name, "Envelope");
}

TEST(IptcDataSetsTest_638, RecordNameApplication2_638) {
  std::string name = IptcDataSets::recordName(IptcDataSets::application2);
  EXPECT_EQ(name, "Application2");
}

TEST(IptcDataSetsTest_638, RecordNameUnknownReturnsHexLike_638) {
  // Unknown record id should return some string (likely hex formatted)
  std::string name = IptcDataSets::recordName(0x00FF);
  EXPECT_FALSE(name.empty());
}

// ============================================================
// Tests for recordDesc(uint16_t)
// ============================================================

TEST(IptcDataSetsTest_638, RecordDescEnvelope_638) {
  const char* desc = IptcDataSets::recordDesc(IptcDataSets::envelope);
  ASSERT_NE(desc, nullptr);
  EXPECT_STREQ(desc, "IIM envelope record");
}

TEST(IptcDataSetsTest_638, RecordDescApplication2_638) {
  const char* desc = IptcDataSets::recordDesc(IptcDataSets::application2);
  ASSERT_NE(desc, nullptr);
  EXPECT_STREQ(desc, "IIM application record 2");
}

// ============================================================
// Tests for envelopeRecordList / application2RecordList
// ============================================================

TEST(IptcDataSetsTest_638, EnvelopeRecordListNotNull_638) {
  const Exiv2::DataSet* list = IptcDataSets::envelopeRecordList();
  ASSERT_NE(list, nullptr);
}

TEST(IptcDataSetsTest_638, Application2RecordListNotNull_638) {
  const Exiv2::DataSet* list = IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);
}

// ============================================================
// Tests for dataSetName / dataSetTitle / dataSetDesc
// ============================================================

TEST(IptcDataSetsTest_638, DataSetNameKnownEnvelope_638) {
  // DataSet 0 in envelope record is typically "ModelVersion" or similar
  // We just check it returns a non-empty string for a known dataset
  std::string name = IptcDataSets::dataSetName(0, IptcDataSets::envelope);
  EXPECT_FALSE(name.empty());
}

TEST(IptcDataSetsTest_638, DataSetNameUnknown_638) {
  // Unknown dataset number should still return something (hex string)
  std::string name = IptcDataSets::dataSetName(0xFFFF, IptcDataSets::envelope);
  EXPECT_FALSE(name.empty());
}

TEST(IptcDataSetsTest_638, DataSetTitleReturnsNonNull_638) {
  const char* title = IptcDataSets::dataSetTitle(0, IptcDataSets::envelope);
  ASSERT_NE(title, nullptr);
}

TEST(IptcDataSetsTest_638, DataSetDescReturnsNonNull_638) {
  const char* desc = IptcDataSets::dataSetDesc(0, IptcDataSets::envelope);
  ASSERT_NE(desc, nullptr);
}

TEST(IptcDataSetsTest_638, DataSetPsNameReturnsNonNull_638) {
  const char* psName = IptcDataSets::dataSetPsName(0, IptcDataSets::envelope);
  ASSERT_NE(psName, nullptr);
}

// ============================================================
// Tests for dataSet(const std::string&, uint16_t)
// ============================================================

TEST(IptcDataSetsTest_638, DataSetByNameKnown_638) {
  // Look up a known dataset by name in application2 record
  // "ObjectName" is dataset 5 in application2
  uint16_t ds = IptcDataSets::dataSet("ObjectName", IptcDataSets::application2);
  EXPECT_EQ(ds, 5);
}

TEST(IptcDataSetsTest_638, DataSetByNameUnknownThrows_638) {
  EXPECT_THROW(IptcDataSets::dataSet("CompletelyBogusName", IptcDataSets::application2), Exiv2::Error);
}

// ============================================================
// Tests for dataSetRepeatable
// ============================================================

TEST(IptcDataSetsTest_638, DataSetRepeatableKnown_638) {
  // Keywords (dataset 25, application2) is repeatable
  bool repeatable = IptcDataSets::dataSetRepeatable(25, IptcDataSets::application2);
  EXPECT_TRUE(repeatable);
}

TEST(IptcDataSetsTest_638, DataSetRepeatableNonRepeatable_638) {
  // ObjectName (dataset 5, application2) is typically not repeatable
  bool repeatable = IptcDataSets::dataSetRepeatable(5, IptcDataSets::application2);
  EXPECT_FALSE(repeatable);
}

// ============================================================
// Tests for dataSetType
// ============================================================

TEST(IptcDataSetsTest_638, DataSetTypeKnown_638) {
  Exiv2::TypeId type = IptcDataSets::dataSetType(0, IptcDataSets::envelope);
  // ModelVersion is typically unsignedShort
  EXPECT_EQ(type, Exiv2::unsignedShort);
}

// ============================================================
// Tests for dataSetList
// ============================================================

TEST(IptcDataSetsTest_638, DataSetListProducesOutput_638) {
  std::ostringstream os;
  IptcDataSets::dataSetList(os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
  // It should contain at least some known dataset names
  EXPECT_NE(output.find("Envelope"), std::string::npos);
  EXPECT_NE(output.find("Application2"), std::string::npos);
}

// ============================================================
// Round-trip tests: recordName <-> recordId
// ============================================================

TEST(IptcDataSetsTest_638, RecordNameIdRoundTripEnvelope_638) {
  std::string name = IptcDataSets::recordName(IptcDataSets::envelope);
  uint16_t id = IptcDataSets::recordId(name);
  EXPECT_EQ(id, IptcDataSets::envelope);
}

TEST(IptcDataSetsTest_638, RecordNameIdRoundTripApplication2_638) {
  std::string name = IptcDataSets::recordName(IptcDataSets::application2);
  uint16_t id = IptcDataSets::recordId(name);
  EXPECT_EQ(id, IptcDataSets::application2);
}

// ============================================================
// Round-trip tests: dataSetName <-> dataSet
// ============================================================

TEST(IptcDataSetsTest_638, DataSetNameIdRoundTrip_638) {
  std::string name = IptcDataSets::dataSetName(5, IptcDataSets::application2);
  uint16_t ds = IptcDataSets::dataSet(name, IptcDataSets::application2);
  EXPECT_EQ(ds, 5);
}

}  // namespace
