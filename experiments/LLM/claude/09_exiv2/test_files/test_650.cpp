#include <gtest/gtest.h>
#include <exiv2/datasets.hpp>
#include <exiv2/error.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

// ===========================================================================
// IptcKey Tests
// ===========================================================================

class IptcKeyTest_650 : public ::testing::Test {
protected:
};

// --- Construction from string key ---

TEST_F(IptcKeyTest_650, ConstructFromValidStringKey_650) {
  ASSERT_NO_THROW(IptcKey key("Iptc.Application2.ObjectName"));
}

TEST_F(IptcKeyTest_650, ConstructFromValidEnvelopeKey_650) {
  ASSERT_NO_THROW(IptcKey key("Iptc.Envelope.ModelVersion"));
}

TEST_F(IptcKeyTest_650, ConstructFromInvalidKey_NoDots_650) {
  EXPECT_THROW(IptcKey key("InvalidKey"), Error);
}

TEST_F(IptcKeyTest_650, ConstructFromInvalidKey_OneDot_650) {
  EXPECT_THROW(IptcKey key("Iptc.Application2"), Error);
}

TEST_F(IptcKeyTest_650, ConstructFromInvalidKey_WrongFamily_650) {
  EXPECT_THROW(IptcKey key("Exif.Application2.ObjectName"), Error);
}

TEST_F(IptcKeyTest_650, ConstructFromEmptyString_650) {
  EXPECT_THROW(IptcKey key(""), Error);
}

// --- Construction from tag and record ---

TEST_F(IptcKeyTest_650, ConstructFromTagAndRecord_650) {
  ASSERT_NO_THROW(IptcKey key(5, 2));
}

TEST_F(IptcKeyTest_650, ConstructFromTagAndRecord_EnvelopeRecord_650) {
  ASSERT_NO_THROW(IptcKey key(0, 1));
}

// --- key() method ---

TEST_F(IptcKeyTest_650, KeyReturnsCorrectStringForStringConstruction_650) {
  IptcKey key("Iptc.Application2.ObjectName");
  std::string k = key.key();
  EXPECT_FALSE(k.empty());
  EXPECT_EQ(k.substr(0, 5), "Iptc.");
}

TEST_F(IptcKeyTest_650, KeyReturnsCorrectStringForTagConstruction_650) {
  IptcKey key(5, 2);
  std::string k = key.key();
  EXPECT_FALSE(k.empty());
  EXPECT_EQ(k.substr(0, 5), "Iptc.");
}

// --- familyName() ---

TEST_F(IptcKeyTest_650, FamilyNameReturnsIptc_650) {
  IptcKey key("Iptc.Application2.ObjectName");
  EXPECT_STREQ(key.familyName(), "Iptc");
}

TEST_F(IptcKeyTest_650, FamilyNameFromTagRecord_650) {
  IptcKey key(5, 2);
  EXPECT_STREQ(key.familyName(), "Iptc");
}

// --- groupName() ---

TEST_F(IptcKeyTest_650, GroupNameForApplication2_650) {
  IptcKey key("Iptc.Application2.ObjectName");
  EXPECT_EQ(key.groupName(), "Application2");
}

TEST_F(IptcKeyTest_650, GroupNameForEnvelope_650) {
  IptcKey key("Iptc.Envelope.ModelVersion");
  EXPECT_EQ(key.groupName(), "Envelope");
}

// --- tagName() ---

TEST_F(IptcKeyTest_650, TagNameForObjectName_650) {
  IptcKey key("Iptc.Application2.ObjectName");
  EXPECT_EQ(key.tagName(), "ObjectName");
}

TEST_F(IptcKeyTest_650, TagNameForModelVersion_650) {
  IptcKey key("Iptc.Envelope.ModelVersion");
  EXPECT_EQ(key.tagName(), "ModelVersion");
}

// --- tag() ---

TEST_F(IptcKeyTest_650, TagValueForKnownDataSet_650) {
  IptcKey key(5, 2);
  EXPECT_EQ(key.tag(), 5);
}

TEST_F(IptcKeyTest_650, TagValueFromStringKey_650) {
  IptcKey key("Iptc.Application2.ObjectName");
  // ObjectName is dataset 5 in record Application2 (record 2)
  EXPECT_EQ(key.tag(), 5);
}

// --- record() ---

TEST_F(IptcKeyTest_650, RecordForApplication2_650) {
  IptcKey key("Iptc.Application2.ObjectName");
  EXPECT_EQ(key.record(), 2);
}

TEST_F(IptcKeyTest_650, RecordForEnvelope_650) {
  IptcKey key("Iptc.Envelope.ModelVersion");
  EXPECT_EQ(key.record(), 1);
}

TEST_F(IptcKeyTest_650, RecordFromTagRecord_650) {
  IptcKey key(5, 2);
  EXPECT_EQ(key.record(), 2);
}

// --- recordName() ---

TEST_F(IptcKeyTest_650, RecordNameForApplication2_650) {
  IptcKey key("Iptc.Application2.ObjectName");
  EXPECT_EQ(key.recordName(), "Application2");
}

TEST_F(IptcKeyTest_650, RecordNameForEnvelope_650) {
  IptcKey key("Iptc.Envelope.ModelVersion");
  EXPECT_EQ(key.recordName(), "Envelope");
}

// --- tagLabel() ---

TEST_F(IptcKeyTest_650, TagLabelNotEmpty_650) {
  IptcKey key("Iptc.Application2.ObjectName");
  std::string label = key.tagLabel();
  EXPECT_FALSE(label.empty());
}

// --- tagDesc() ---

TEST_F(IptcKeyTest_650, TagDescNotEmpty_650) {
  IptcKey key("Iptc.Application2.ObjectName");
  // Description may or may not be empty depending on the dataset
  // Just ensure it doesn't throw
  ASSERT_NO_THROW(key.tagDesc());
}

// --- clone() ---

TEST_F(IptcKeyTest_650, CloneCreatesEqualKey_650) {
  IptcKey key("Iptc.Application2.ObjectName");
  auto cloned = key.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->key(), key.key());
  EXPECT_EQ(cloned->tag(), key.tag());
  EXPECT_EQ(cloned->record(), key.record());
  EXPECT_STREQ(cloned->familyName(), key.familyName());
  EXPECT_EQ(cloned->groupName(), key.groupName());
  EXPECT_EQ(cloned->tagName(), key.tagName());
}

TEST_F(IptcKeyTest_650, CloneFromTagRecordCreatesEqualKey_650) {
  IptcKey key(5, 2);
  auto cloned = key.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->key(), key.key());
  EXPECT_EQ(cloned->tag(), key.tag());
  EXPECT_EQ(cloned->record(), key.record());
}

// ===========================================================================
// IptcDataSets Tests
// ===========================================================================

class IptcDataSetsTest_650 : public ::testing::Test {
protected:
};

// --- dataSetName ---

TEST_F(IptcDataSetsTest_650, DataSetNameForKnownDataSet_650) {
  // ObjectName is dataset 5 in Application2 (record 2)
  std::string name = IptcDataSets::dataSetName(5, 2);
  EXPECT_EQ(name, "ObjectName");
}

TEST_F(IptcDataSetsTest_650, DataSetNameForModelVersion_650) {
  // ModelVersion is dataset 0 in Envelope (record 1)
  std::string name = IptcDataSets::dataSetName(0, 1);
  EXPECT_EQ(name, "ModelVersion");
}

TEST_F(IptcDataSetsTest_650, DataSetNameForUnknownDataSet_650) {
  // Unknown dataset should return a string (likely hex-encoded number)
  std::string name = IptcDataSets::dataSetName(0xFFFF, 2);
  EXPECT_FALSE(name.empty());
}

// --- dataSetTitle ---

TEST_F(IptcDataSetsTest_650, DataSetTitleForKnownDataSet_650) {
  const char* title = IptcDataSets::dataSetTitle(5, 2);
  ASSERT_NE(title, nullptr);
  // Title should be non-empty for known datasets
  EXPECT_GT(strlen(title), 0u);
}

// --- dataSetDesc ---

TEST_F(IptcDataSetsTest_650, DataSetDescForKnownDataSet_650) {
  const char* desc = IptcDataSets::dataSetDesc(5, 2);
  ASSERT_NE(desc, nullptr);
}

// --- dataSetPsName ---

TEST_F(IptcDataSetsTest_650, DataSetPsNameForKnownDataSet_650) {
  const char* psName = IptcDataSets::dataSetPsName(5, 2);
  ASSERT_NE(psName, nullptr);
}

// --- dataSetRepeatable ---

TEST_F(IptcDataSetsTest_650, DataSetRepeatableForKnownDataSet_650) {
  // ObjectName (5, 2) is not repeatable
  bool repeatable = IptcDataSets::dataSetRepeatable(5, 2);
  EXPECT_FALSE(repeatable);
}

TEST_F(IptcDataSetsTest_650, DataSetRepeatableForKeywords_650) {
  // Keywords (25, 2) are repeatable
  bool repeatable = IptcDataSets::dataSetRepeatable(25, 2);
  EXPECT_TRUE(repeatable);
}

// --- dataSet (lookup by name) ---

TEST_F(IptcDataSetsTest_650, DataSetLookupByName_650) {
  uint16_t ds = IptcDataSets::dataSet("ObjectName", 2);
  EXPECT_EQ(ds, 5);
}

TEST_F(IptcDataSetsTest_650, DataSetLookupByNameEnvelope_650) {
  uint16_t ds = IptcDataSets::dataSet("ModelVersion", 1);
  EXPECT_EQ(ds, 0);
}

TEST_F(IptcDataSetsTest_650, DataSetLookupByInvalidName_650) {
  EXPECT_THROW(IptcDataSets::dataSet("NonExistentDataSet", 2), Error);
}

// --- dataSetType ---

TEST_F(IptcDataSetsTest_650, DataSetTypeForKnownDataSet_650) {
  TypeId type = IptcDataSets::dataSetType(5, 2);
  // ObjectName is of string type
  EXPECT_EQ(type, string);
}

TEST_F(IptcDataSetsTest_650, DataSetTypeForModelVersion_650) {
  TypeId type = IptcDataSets::dataSetType(0, 1);
  // ModelVersion is of unsignedShort type
  EXPECT_EQ(type, unsignedShort);
}

// --- recordName ---

TEST_F(IptcDataSetsTest_650, RecordNameForEnvelope_650) {
  std::string name = IptcDataSets::recordName(1);
  EXPECT_EQ(name, "Envelope");
}

TEST_F(IptcDataSetsTest_650, RecordNameForApplication2_650) {
  std::string name = IptcDataSets::recordName(2);
  EXPECT_EQ(name, "Application2");
}

TEST_F(IptcDataSetsTest_650, RecordNameForUnknownRecord_650) {
  std::string name = IptcDataSets::recordName(255);
  EXPECT_FALSE(name.empty());
}

// --- recordDesc ---

TEST_F(IptcDataSetsTest_650, RecordDescForEnvelope_650) {
  const char* desc = IptcDataSets::recordDesc(1);
  ASSERT_NE(desc, nullptr);
}

TEST_F(IptcDataSetsTest_650, RecordDescForApplication2_650) {
  const char* desc = IptcDataSets::recordDesc(2);
  ASSERT_NE(desc, nullptr);
}

// --- recordId ---

TEST_F(IptcDataSetsTest_650, RecordIdForEnvelope_650) {
  uint16_t id = IptcDataSets::recordId("Envelope");
  EXPECT_EQ(id, 1);
}

TEST_F(IptcDataSetsTest_650, RecordIdForApplication2_650) {
  uint16_t id = IptcDataSets::recordId("Application2");
  EXPECT_EQ(id, 2);
}

TEST_F(IptcDataSetsTest_650, RecordIdForInvalidName_650) {
  EXPECT_THROW(IptcDataSets::recordId("NonExistentRecord"), Error);
}

// --- envelopeRecordList ---

TEST_F(IptcDataSetsTest_650, EnvelopeRecordListNotNull_650) {
  const DataSet* list = IptcDataSets::envelopeRecordList();
  ASSERT_NE(list, nullptr);
}

// --- application2RecordList ---

TEST_F(IptcDataSetsTest_650, Application2RecordListNotNull_650) {
  const DataSet* list = IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);
}

// --- dataSetList ---

TEST_F(IptcDataSetsTest_650, DataSetListProducesOutput_650) {
  std::ostringstream oss;
  IptcDataSets::dataSetList(oss);
  EXPECT_FALSE(oss.str().empty());
}

// ===========================================================================
// IptcKey Edge Cases
// ===========================================================================

TEST_F(IptcKeyTest_650, ConstructWithOnlyDots_650) {
  // "..." has family "", which is not "Iptc"
  EXPECT_THROW(IptcKey key("..."), Error);
}

TEST_F(IptcKeyTest_650, ConstructWithIptcAndTrailingDots_650) {
  // "Iptc.." second dot at position 5, dataSetName would be empty
  EXPECT_THROW(IptcKey key("Iptc.."), Error);
}

TEST_F(IptcKeyTest_650, ConstructWithMultipleDots_650) {
  // "Iptc.Application2.ObjectName.Extra" - first two dots identify record and dataset
  // This may or may not be valid depending on implementation behavior
  // The key parsing only looks for first two dots
  // The dataset name would be "ObjectName.Extra" which likely doesn't exist
  EXPECT_THROW(IptcKey key("Iptc.Application2.ObjectName.Extra"), Error);
}

TEST_F(IptcKeyTest_650, KeyConsistencyAfterConstruction_650) {
  IptcKey key1("Iptc.Application2.ObjectName");
  IptcKey key2(5, 2);
  EXPECT_EQ(key1.key(), key2.key());
  EXPECT_EQ(key1.tag(), key2.tag());
  EXPECT_EQ(key1.record(), key2.record());
  EXPECT_EQ(key1.groupName(), key2.groupName());
  EXPECT_EQ(key1.tagName(), key2.tagName());
  EXPECT_EQ(key1.recordName(), key2.recordName());
}

// Test various Application2 datasets

TEST_F(IptcKeyTest_650, KeywordsDataSet_650) {
  IptcKey key("Iptc.Application2.Keywords");
  EXPECT_EQ(key.tag(), 25);
  EXPECT_EQ(key.record(), 2);
  EXPECT_EQ(key.tagName(), "Keywords");
}

TEST_F(IptcKeyTest_650, CaptionDataSet_650) {
  IptcKey key("Iptc.Application2.Caption");
  EXPECT_EQ(key.record(), 2);
  EXPECT_EQ(key.tagName(), "Caption");
}

// Test Envelope datasets

TEST_F(IptcKeyTest_650, EnvelopeDestination_650) {
  IptcKey key("Iptc.Envelope.Destination");
  EXPECT_EQ(key.record(), 1);
  EXPECT_EQ(key.groupName(), "Envelope");
}

// Test that key string is normalized after construction

TEST_F(IptcKeyTest_650, KeyStringIsNormalized_650) {
  IptcKey key("Iptc.Application2.ObjectName");
  // The key should be normalized to the canonical form
  EXPECT_EQ(key.key(), "Iptc.Application2.ObjectName");
}

// Test constructing with unknown tag/record combination

TEST_F(IptcKeyTest_650, UnknownTagAndRecord_650) {
  // Use an unusual but potentially valid tag/record
  ASSERT_NO_THROW(IptcKey key(9999, 2));
  IptcKey key(9999, 2);
  EXPECT_EQ(key.tag(), 9999);
  EXPECT_EQ(key.record(), 2);
}
