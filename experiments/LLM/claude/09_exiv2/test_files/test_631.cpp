#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "exiv2/datasets.hpp"

using namespace Exiv2;

// Known record IDs from IPTC standard
static constexpr uint16_t IptcEnvelopeRecord = 1;
static constexpr uint16_t IptcApplication2Record = 2;

// ============================================================
// Tests for dataSetTitle
// ============================================================

TEST(IptcDataSetsTest_631, DataSetTitleKnownEnvelopeRecord_631) {
  // Dataset 0 in envelope record (1) is "ModelVersion"
  const char* title = IptcDataSets::dataSetTitle(0, IptcEnvelopeRecord);
  ASSERT_NE(title, nullptr);
  EXPECT_STRNE(title, "");
}

TEST(IptcDataSetsTest_631, DataSetTitleKnownApplication2Record_631) {
  // Dataset 0 in application2 record (2) is "RecordVersion"
  const char* title = IptcDataSets::dataSetTitle(0, IptcApplication2Record);
  ASSERT_NE(title, nullptr);
  EXPECT_STRNE(title, "");
}

TEST(IptcDataSetsTest_631, DataSetTitleUnknownDataSet_631) {
  // Use a dataset number unlikely to exist
  const char* title = IptcDataSets::dataSetTitle(65535, IptcEnvelopeRecord);
  ASSERT_NE(title, nullptr);
  EXPECT_STREQ(title, "Unknown dataset");
}

TEST(IptcDataSetsTest_631, DataSetTitleUnknownRecordId_631) {
  // Use an invalid record ID
  const char* title = IptcDataSets::dataSetTitle(0, 255);
  ASSERT_NE(title, nullptr);
  EXPECT_STREQ(title, "Unknown dataset");
}

// ============================================================
// Tests for dataSetName
// ============================================================

TEST(IptcDataSetsTest_631, DataSetNameKnownEnvelope_631) {
  std::string name = IptcDataSets::dataSetName(0, IptcEnvelopeRecord);
  EXPECT_FALSE(name.empty());
  // Known: dataset 0 in record 1 should be "ModelVersion"
  EXPECT_EQ(name, "ModelVersion");
}

TEST(IptcDataSetsTest_631, DataSetNameKnownApplication2_631) {
  std::string name = IptcDataSets::dataSetName(0, IptcApplication2Record);
  EXPECT_FALSE(name.empty());
  EXPECT_EQ(name, "RecordVersion");
}

TEST(IptcDataSetsTest_631, DataSetNameUnknown_631) {
  std::string name = IptcDataSets::dataSetName(65535, IptcEnvelopeRecord);
  EXPECT_FALSE(name.empty());
}

TEST(IptcDataSetsTest_631, DataSetNameUnknownRecord_631) {
  std::string name = IptcDataSets::dataSetName(0, 255);
  EXPECT_FALSE(name.empty());
}

// ============================================================
// Tests for dataSetDesc
// ============================================================

TEST(IptcDataSetsTest_631, DataSetDescKnown_631) {
  const char* desc = IptcDataSets::dataSetDesc(0, IptcEnvelopeRecord);
  ASSERT_NE(desc, nullptr);
  EXPECT_STRNE(desc, "");
}

TEST(IptcDataSetsTest_631, DataSetDescUnknown_631) {
  const char* desc = IptcDataSets::dataSetDesc(65535, IptcEnvelopeRecord);
  ASSERT_NE(desc, nullptr);
  EXPECT_STREQ(desc, "Unknown dataset");
}

// ============================================================
// Tests for dataSetPsName
// ============================================================

TEST(IptcDataSetsTest_631, DataSetPsNameKnown_631) {
  const char* psName = IptcDataSets::dataSetPsName(0, IptcEnvelopeRecord);
  ASSERT_NE(psName, nullptr);
}

TEST(IptcDataSetsTest_631, DataSetPsNameUnknown_631) {
  const char* psName = IptcDataSets::dataSetPsName(65535, IptcEnvelopeRecord);
  ASSERT_NE(psName, nullptr);
  EXPECT_STREQ(psName, "Unknown dataset");
}

// ============================================================
// Tests for dataSetRepeatable
// ============================================================

TEST(IptcDataSetsTest_631, DataSetRepeatableKnown_631) {
  // ModelVersion (0, 1) is typically not repeatable
  bool repeatable = IptcDataSets::dataSetRepeatable(0, IptcEnvelopeRecord);
  EXPECT_FALSE(repeatable);
}

TEST(IptcDataSetsTest_631, DataSetRepeatableUnknownReturnsTrue_631) {
  // Unknown dataset should return true (from unknownDataSet.repeatable_ = true)
  bool repeatable = IptcDataSets::dataSetRepeatable(65535, IptcEnvelopeRecord);
  EXPECT_TRUE(repeatable);
}

TEST(IptcDataSetsTest_631, DataSetRepeatableKeywords_631) {
  // Keywords (25, 2) should be repeatable
  bool repeatable = IptcDataSets::dataSetRepeatable(25, IptcApplication2Record);
  EXPECT_TRUE(repeatable);
}

// ============================================================
// Tests for dataSetType
// ============================================================

TEST(IptcDataSetsTest_631, DataSetTypeKnown_631) {
  TypeId type = IptcDataSets::dataSetType(0, IptcEnvelopeRecord);
  // ModelVersion is typically unsignedShort
  EXPECT_EQ(type, unsignedShort);
}

TEST(IptcDataSetsTest_631, DataSetTypeUnknown_631) {
  TypeId type = IptcDataSets::dataSetType(65535, IptcEnvelopeRecord);
  EXPECT_EQ(type, string);
}

// ============================================================
// Tests for dataSet (lookup by name)
// ============================================================

TEST(IptcDataSetsTest_631, DataSetLookupByNameEnvelope_631) {
  uint16_t number = IptcDataSets::dataSet("ModelVersion", IptcEnvelopeRecord);
  EXPECT_EQ(number, 0);
}

TEST(IptcDataSetsTest_631, DataSetLookupByNameApplication2_631) {
  uint16_t number = IptcDataSets::dataSet("RecordVersion", IptcApplication2Record);
  EXPECT_EQ(number, 0);
}

TEST(IptcDataSetsTest_631, DataSetLookupByNameKeywords_631) {
  uint16_t number = IptcDataSets::dataSet("Keywords", IptcApplication2Record);
  EXPECT_EQ(number, 25);
}

TEST(IptcDataSetsTest_631, DataSetLookupByUnknownName_631) {
  uint16_t number = IptcDataSets::dataSet("NonExistentDataSet", IptcEnvelopeRecord);
  EXPECT_EQ(number, 0xffff);
}

// ============================================================
// Tests for recordName
// ============================================================

TEST(IptcDataSetsTest_631, RecordNameEnvelope_631) {
  std::string name = IptcDataSets::recordName(IptcEnvelopeRecord);
  EXPECT_EQ(name, "Envelope");
}

TEST(IptcDataSetsTest_631, RecordNameApplication2_631) {
  std::string name = IptcDataSets::recordName(IptcApplication2Record);
  EXPECT_EQ(name, "Application2");
}

TEST(IptcDataSetsTest_631, RecordNameUnknown_631) {
  std::string name = IptcDataSets::recordName(255);
  EXPECT_FALSE(name.empty());
}

// ============================================================
// Tests for recordDesc
// ============================================================

TEST(IptcDataSetsTest_631, RecordDescEnvelope_631) {
  const char* desc = IptcDataSets::recordDesc(IptcEnvelopeRecord);
  ASSERT_NE(desc, nullptr);
  EXPECT_STRNE(desc, "");
}

TEST(IptcDataSetsTest_631, RecordDescApplication2_631) {
  const char* desc = IptcDataSets::recordDesc(IptcApplication2Record);
  ASSERT_NE(desc, nullptr);
  EXPECT_STRNE(desc, "");
}

TEST(IptcDataSetsTest_631, RecordDescUnknown_631) {
  const char* desc = IptcDataSets::recordDesc(255);
  ASSERT_NE(desc, nullptr);
}

// ============================================================
// Tests for recordId
// ============================================================

TEST(IptcDataSetsTest_631, RecordIdEnvelope_631) {
  uint16_t id = IptcDataSets::recordId("Envelope");
  EXPECT_EQ(id, IptcEnvelopeRecord);
}

TEST(IptcDataSetsTest_631, RecordIdApplication2_631) {
  uint16_t id = IptcDataSets::recordId("Application2");
  EXPECT_EQ(id, IptcApplication2Record);
}

TEST(IptcDataSetsTest_631, RecordIdUnknown_631) {
  uint16_t id = IptcDataSets::recordId("NonExistentRecord");
  // Should return some invalid/unknown value
  EXPECT_NE(id, IptcEnvelopeRecord);
  EXPECT_NE(id, IptcApplication2Record);
}

// ============================================================
// Tests for envelopeRecordList and application2RecordList
// ============================================================

TEST(IptcDataSetsTest_631, EnvelopeRecordListNotNull_631) {
  const DataSet* list = IptcDataSets::envelopeRecordList();
  ASSERT_NE(list, nullptr);
}

TEST(IptcDataSetsTest_631, Application2RecordListNotNull_631) {
  const DataSet* list = IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);
}

TEST(IptcDataSetsTest_631, EnvelopeRecordListFirstEntry_631) {
  const DataSet* list = IptcDataSets::envelopeRecordList();
  ASSERT_NE(list, nullptr);
  // First entry should be ModelVersion with number 0
  EXPECT_EQ(list[0].number_, 0);
}

TEST(IptcDataSetsTest_631, Application2RecordListFirstEntry_631) {
  const DataSet* list = IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);
  // First entry should be RecordVersion with number 0
  EXPECT_EQ(list[0].number_, 0);
}

// ============================================================
// Tests for dataSetList
// ============================================================

TEST(IptcDataSetsTest_631, DataSetListProducesOutput_631) {
  std::ostringstream os;
  IptcDataSets::dataSetList(os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST(IptcDataSetsTest_631, DataSetListContainsKnownDataSet_631) {
  std::ostringstream os;
  IptcDataSets::dataSetList(os);
  std::string output = os.str();
  // Should contain some known dataset names
  EXPECT_NE(output.find("ModelVersion"), std::string::npos);
}

TEST(IptcDataSetsTest_631, DataSetListContainsApplication2DataSet_631) {
  std::ostringstream os;
  IptcDataSets::dataSetList(os);
  std::string output = os.str();
  EXPECT_NE(output.find("Keywords"), std::string::npos);
}

// ============================================================
// Boundary tests
// ============================================================

TEST(IptcDataSetsTest_631, DataSetTitleMaxNumber_631) {
  const char* title = IptcDataSets::dataSetTitle(0xFFFF, IptcApplication2Record);
  ASSERT_NE(title, nullptr);
  EXPECT_STREQ(title, "Unknown dataset");
}

TEST(IptcDataSetsTest_631, DataSetTitleZeroRecordId_631) {
  const char* title = IptcDataSets::dataSetTitle(0, 0);
  ASSERT_NE(title, nullptr);
  // Record 0 is not a standard IPTC record, should return unknown
  EXPECT_STREQ(title, "Unknown dataset");
}

TEST(IptcDataSetsTest_631, DataSetNameConsistencyWithLookup_631) {
  // Looking up by name should return the correct number, and vice versa
  std::string name = IptcDataSets::dataSetName(25, IptcApplication2Record);
  EXPECT_EQ(name, "Keywords");
  uint16_t number = IptcDataSets::dataSet(name, IptcApplication2Record);
  EXPECT_EQ(number, 25);
}

TEST(IptcDataSetsTest_631, RecordIdAndNameRoundTrip_631) {
  std::string name = IptcDataSets::recordName(IptcEnvelopeRecord);
  uint16_t id = IptcDataSets::recordId(name);
  EXPECT_EQ(id, IptcEnvelopeRecord);
}

TEST(IptcDataSetsTest_631, RecordIdAndNameRoundTripApplication2_631) {
  std::string name = IptcDataSets::recordName(IptcApplication2Record);
  uint16_t id = IptcDataSets::recordId(name);
  EXPECT_EQ(id, IptcApplication2Record);
}

// ============================================================
// Additional known datasets in Application2
// ============================================================

TEST(IptcDataSetsTest_631, DataSetBylineTitle_631) {
  // Byline is dataset 80 in Application2
  std::string name = IptcDataSets::dataSetName(80, IptcApplication2Record);
  EXPECT_EQ(name, "Byline");
}

TEST(IptcDataSetsTest_631, DataSetCaptionAbstract_631) {
  // Caption/Abstract is dataset 120 in Application2
  std::string name = IptcDataSets::dataSetName(120, IptcApplication2Record);
  EXPECT_EQ(name, "Caption");
}

TEST(IptcDataSetsTest_631, DataSetCity_631) {
  // City is dataset 90 in Application2
  std::string name = IptcDataSets::dataSetName(90, IptcApplication2Record);
  EXPECT_EQ(name, "City");
}

TEST(IptcDataSetsTest_631, DataSetCountry_631) {
  // Country/Primary Location Name is dataset 101 in Application2
  std::string name = IptcDataSets::dataSetName(101, IptcApplication2Record);
  EXPECT_EQ(name, "CountryName");
}
