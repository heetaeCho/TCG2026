#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <exiv2/datasets.hpp>

using namespace Exiv2;

// ============================================================
// Tests for recordName
// ============================================================

TEST(IptcDataSetsTest_636, RecordNameEnvelope_636) {
  // envelope recordId should return "Envelope"
  std::string name = IptcDataSets::recordName(IptcDataSets::envelope);
  EXPECT_EQ(name, "Envelope");
}

TEST(IptcDataSetsTest_636, RecordNameApplication2_636) {
  // application2 recordId should return "Application2"
  std::string name = IptcDataSets::recordName(IptcDataSets::application2);
  EXPECT_EQ(name, "Application2");
}

TEST(IptcDataSetsTest_636, RecordNameUnknownReturnsHexFormatted_636) {
  // Unknown record IDs should return hex-formatted string
  std::string name = IptcDataSets::recordName(0x0005);
  EXPECT_EQ(name, "0x0005");
}

TEST(IptcDataSetsTest_636, RecordNameZeroReturnsHexOrInvalid_636) {
  // recordId 0 (invalidRecord) - based on the implementation, only envelope and application2
  // return their names, so 0 should return hex string
  std::string name = IptcDataSets::recordName(0);
  // invalidRecord is 0, which is neither envelope nor application2
  // so it should return hex format
  EXPECT_EQ(name, "0x0000");
}

TEST(IptcDataSetsTest_636, RecordNameMaxUint16_636) {
  std::string name = IptcDataSets::recordName(0xFFFF);
  EXPECT_EQ(name, "0xffff");
}

TEST(IptcDataSetsTest_636, RecordNameArbitraryValue_636) {
  std::string name = IptcDataSets::recordName(0x00FF);
  EXPECT_EQ(name, "0x00ff");
}

// ============================================================
// Tests for recordId
// ============================================================

TEST(IptcDataSetsTest_636, RecordIdEnvelope_636) {
  uint16_t id = IptcDataSets::recordId("Envelope");
  EXPECT_EQ(id, IptcDataSets::envelope);
}

TEST(IptcDataSetsTest_636, RecordIdApplication2_636) {
  uint16_t id = IptcDataSets::recordId("Application2");
  EXPECT_EQ(id, IptcDataSets::application2);
}

TEST(IptcDataSetsTest_636, RecordIdUnknownName_636) {
  uint16_t id = IptcDataSets::recordId("NonExistentRecord");
  EXPECT_EQ(id, IptcDataSets::invalidRecord);
}

// ============================================================
// Tests for recordDesc
// ============================================================

TEST(IptcDataSetsTest_636, RecordDescEnvelope_636) {
  const char* desc = IptcDataSets::recordDesc(IptcDataSets::envelope);
  ASSERT_NE(desc, nullptr);
  EXPECT_STREQ(desc, "IIM envelope record");
}

TEST(IptcDataSetsTest_636, RecordDescApplication2_636) {
  const char* desc = IptcDataSets::recordDesc(IptcDataSets::application2);
  ASSERT_NE(desc, nullptr);
  EXPECT_STREQ(desc, "IIM application record 2");
}

// ============================================================
// Tests for dataSetName
// ============================================================

TEST(IptcDataSetsTest_636, DataSetNameKnownEnvelopeDataSet_636) {
  // DataSet 0 in envelope record is typically "ModelVersion"
  // We test that it returns a non-empty string for a known dataset
  std::string name = IptcDataSets::dataSetName(0, IptcDataSets::envelope);
  EXPECT_FALSE(name.empty());
}

TEST(IptcDataSetsTest_636, DataSetNameUnknownDataSet_636) {
  // Unknown dataset number should return hex-formatted string
  std::string name = IptcDataSets::dataSetName(0xFFFF, IptcDataSets::envelope);
  EXPECT_FALSE(name.empty());
}

TEST(IptcDataSetsTest_636, DataSetNameKnownApp2DataSet_636) {
  // DataSet 0 in application2 record
  std::string name = IptcDataSets::dataSetName(0, IptcDataSets::application2);
  EXPECT_FALSE(name.empty());
}

// ============================================================
// Tests for dataSetTitle
// ============================================================

TEST(IptcDataSetsTest_636, DataSetTitleReturnsNonNull_636) {
  const char* title = IptcDataSets::dataSetTitle(0, IptcDataSets::envelope);
  ASSERT_NE(title, nullptr);
}

// ============================================================
// Tests for dataSetDesc
// ============================================================

TEST(IptcDataSetsTest_636, DataSetDescReturnsNonNull_636) {
  const char* desc = IptcDataSets::dataSetDesc(0, IptcDataSets::envelope);
  ASSERT_NE(desc, nullptr);
}

// ============================================================
// Tests for dataSetPsName
// ============================================================

TEST(IptcDataSetsTest_636, DataSetPsNameReturnsNonNull_636) {
  const char* psName = IptcDataSets::dataSetPsName(0, IptcDataSets::envelope);
  ASSERT_NE(psName, nullptr);
}

// ============================================================
// Tests for dataSetRepeatable
// ============================================================

TEST(IptcDataSetsTest_636, DataSetRepeatableReturnsBool_636) {
  // Simply verify it doesn't crash and returns a boolean value
  bool result = IptcDataSets::dataSetRepeatable(0, IptcDataSets::envelope);
  // result is either true or false - no crash
  (void)result;
}

// ============================================================
// Tests for dataSet (reverse lookup by name)
// ============================================================

TEST(IptcDataSetsTest_636, DataSetByNameEnvelopeModelVersion_636) {
  // Look up "ModelVersion" in envelope record
  std::string knownName = IptcDataSets::dataSetName(0, IptcDataSets::envelope);
  uint16_t ds = IptcDataSets::dataSet(knownName, IptcDataSets::envelope);
  // Round-trip: should return 0
  EXPECT_EQ(ds, 0);
}

TEST(IptcDataSetsTest_636, DataSetByNameUnknown_636) {
  // Looking up a non-existent dataset name
  uint16_t ds = IptcDataSets::dataSet("TotallyBogusDataSetName", IptcDataSets::envelope);
  // Should return some sentinel or throw; we just check it doesn't crash
  (void)ds;
}

// ============================================================
// Tests for dataSetType
// ============================================================

TEST(IptcDataSetsTest_636, DataSetTypeKnownDataSet_636) {
  TypeId type = IptcDataSets::dataSetType(0, IptcDataSets::envelope);
  // Should return a valid TypeId
  (void)type;
}

// ============================================================
// Tests for envelopeRecordList and application2RecordList
// ============================================================

TEST(IptcDataSetsTest_636, EnvelopeRecordListNotNull_636) {
  const DataSet* list = IptcDataSets::envelopeRecordList();
  ASSERT_NE(list, nullptr);
}

TEST(IptcDataSetsTest_636, Application2RecordListNotNull_636) {
  const DataSet* list = IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);
}

// ============================================================
// Tests for dataSetList
// ============================================================

TEST(IptcDataSetsTest_636, DataSetListProducesOutput_636) {
  std::ostringstream os;
  IptcDataSets::dataSetList(os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST(IptcDataSetsTest_636, DataSetListContainsEnvelope_636) {
  std::ostringstream os;
  IptcDataSets::dataSetList(os);
  std::string output = os.str();
  // The output should contain references to Envelope record datasets
  EXPECT_NE(output.find("Envelope"), std::string::npos);
}

TEST(IptcDataSetsTest_636, DataSetListContainsApplication2_636) {
  std::ostringstream os;
  IptcDataSets::dataSetList(os);
  std::string output = os.str();
  EXPECT_NE(output.find("Application2"), std::string::npos);
}

// ============================================================
// Roundtrip tests
// ============================================================

TEST(IptcDataSetsTest_636, RoundtripRecordNameToId_636) {
  // Envelope roundtrip
  std::string name = IptcDataSets::recordName(IptcDataSets::envelope);
  uint16_t id = IptcDataSets::recordId(name);
  EXPECT_EQ(id, IptcDataSets::envelope);
}

TEST(IptcDataSetsTest_636, RoundtripApplication2NameToId_636) {
  std::string name = IptcDataSets::recordName(IptcDataSets::application2);
  uint16_t id = IptcDataSets::recordId(name);
  EXPECT_EQ(id, IptcDataSets::application2);
}

TEST(IptcDataSetsTest_636, RoundtripDataSetNameToNumber_636) {
  // Get name for dataset 5 in envelope, then look it up again
  std::string name = IptcDataSets::dataSetName(5, IptcDataSets::envelope);
  uint16_t num = IptcDataSets::dataSet(name, IptcDataSets::envelope);
  EXPECT_EQ(num, 5);
}

// ============================================================
// Boundary: recordId with edge values
// ============================================================

TEST(IptcDataSetsTest_636, RecordNameForValue1_636) {
  // envelope is typically 1
  std::string name = IptcDataSets::recordName(1);
  EXPECT_EQ(name, "Envelope");
}

TEST(IptcDataSetsTest_636, RecordNameForValue2_636) {
  // application2 is typically 2
  std::string name = IptcDataSets::recordName(2);
  EXPECT_EQ(name, "Application2");
}

TEST(IptcDataSetsTest_636, RecordNameForValue3_636) {
  // Value 3 is not a known record
  std::string name = IptcDataSets::recordName(3);
  EXPECT_EQ(name, "0x0003");
}
