#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <exiv2/datasets.hpp>

namespace {

// ============================================================
// IptcDataSets tests
// ============================================================

class IptcDataSetsTest_645 : public ::testing::Test {};

// --- dataSetName ---

TEST_F(IptcDataSetsTest_645, DataSetName_KnownEnvelopeRecord_645) {
  // Record 1 (envelope), dataset 0 is "ModelVersion"
  std::string name = Exiv2::IptcDataSets::dataSetName(0, 1);
  EXPECT_EQ(name, "ModelVersion");
}

TEST_F(IptcDataSetsTest_645, DataSetName_KnownApplication2Record_645) {
  // Record 2 (application2), dataset 5 is "ObjectName"
  std::string name = Exiv2::IptcDataSets::dataSetName(5, 2);
  EXPECT_EQ(name, "ObjectName");
}

TEST_F(IptcDataSetsTest_645, DataSetName_UnknownDataSet_645) {
  // An unknown dataset number should return something (typically "0x00ff" style)
  std::string name = Exiv2::IptcDataSets::dataSetName(0xFF, 1);
  EXPECT_FALSE(name.empty());
}

// --- dataSetTitle ---

TEST_F(IptcDataSetsTest_645, DataSetTitle_KnownEnvelope_645) {
  const char* title = Exiv2::IptcDataSets::dataSetTitle(0, 1);
  ASSERT_NE(title, nullptr);
  EXPECT_STRNE(title, "");
}

TEST_F(IptcDataSetsTest_645, DataSetTitle_KnownApplication2_645) {
  const char* title = Exiv2::IptcDataSets::dataSetTitle(5, 2);
  ASSERT_NE(title, nullptr);
}

TEST_F(IptcDataSetsTest_645, DataSetTitle_UnknownDataSet_645) {
  const char* title = Exiv2::IptcDataSets::dataSetTitle(0xFF, 1);
  ASSERT_NE(title, nullptr);
}

// --- dataSetDesc ---

TEST_F(IptcDataSetsTest_645, DataSetDesc_KnownEnvelope_645) {
  const char* desc = Exiv2::IptcDataSets::dataSetDesc(0, 1);
  ASSERT_NE(desc, nullptr);
}

TEST_F(IptcDataSetsTest_645, DataSetDesc_KnownApplication2_645) {
  const char* desc = Exiv2::IptcDataSets::dataSetDesc(5, 2);
  ASSERT_NE(desc, nullptr);
}

TEST_F(IptcDataSetsTest_645, DataSetDesc_UnknownDataSet_645) {
  const char* desc = Exiv2::IptcDataSets::dataSetDesc(0xFF, 2);
  ASSERT_NE(desc, nullptr);
}

// --- dataSetPsName ---

TEST_F(IptcDataSetsTest_645, DataSetPsName_KnownDataSet_645) {
  const char* psName = Exiv2::IptcDataSets::dataSetPsName(5, 2);
  ASSERT_NE(psName, nullptr);
}

TEST_F(IptcDataSetsTest_645, DataSetPsName_UnknownDataSet_645) {
  const char* psName = Exiv2::IptcDataSets::dataSetPsName(0xFF, 2);
  ASSERT_NE(psName, nullptr);
}

// --- dataSetRepeatable ---

TEST_F(IptcDataSetsTest_645, DataSetRepeatable_KnownNonRepeatable_645) {
  // ModelVersion (0, 1) is typically not repeatable
  bool rep = Exiv2::IptcDataSets::dataSetRepeatable(0, 1);
  EXPECT_FALSE(rep);
}

TEST_F(IptcDataSetsTest_645, DataSetRepeatable_Keywords_645) {
  // Keywords (25, 2) is repeatable
  bool rep = Exiv2::IptcDataSets::dataSetRepeatable(25, 2);
  EXPECT_TRUE(rep);
}

// --- dataSet (name lookup) ---

TEST_F(IptcDataSetsTest_645, DataSet_KnownName_645) {
  uint16_t ds = Exiv2::IptcDataSets::dataSet("ObjectName", 2);
  EXPECT_EQ(ds, 5);
}

TEST_F(IptcDataSetsTest_645, DataSet_KnownEnvelopeName_645) {
  uint16_t ds = Exiv2::IptcDataSets::dataSet("ModelVersion", 1);
  EXPECT_EQ(ds, 0);
}

TEST_F(IptcDataSetsTest_645, DataSet_UnknownNameThrows_645) {
  EXPECT_THROW(Exiv2::IptcDataSets::dataSet("NonExistentDataSet", 2), Exiv2::Error);
}

// --- dataSetType ---

TEST_F(IptcDataSetsTest_645, DataSetType_Known_645) {
  Exiv2::TypeId type = Exiv2::IptcDataSets::dataSetType(0, 1);
  // ModelVersion is unsignedShort
  EXPECT_EQ(type, Exiv2::unsignedShort);
}

TEST_F(IptcDataSetsTest_645, DataSetType_StringType_645) {
  Exiv2::TypeId type = Exiv2::IptcDataSets::dataSetType(5, 2);
  EXPECT_EQ(type, Exiv2::string);
}

// --- recordName ---

TEST_F(IptcDataSetsTest_645, RecordName_Envelope_645) {
  std::string name = Exiv2::IptcDataSets::recordName(1);
  EXPECT_EQ(name, "Envelope");
}

TEST_F(IptcDataSetsTest_645, RecordName_Application2_645) {
  std::string name = Exiv2::IptcDataSets::recordName(2);
  EXPECT_EQ(name, "Application2");
}

TEST_F(IptcDataSetsTest_645, RecordName_UnknownRecord_645) {
  std::string name = Exiv2::IptcDataSets::recordName(0xFF);
  EXPECT_FALSE(name.empty());
}

// --- recordDesc ---

TEST_F(IptcDataSetsTest_645, RecordDesc_Envelope_645) {
  const char* desc = Exiv2::IptcDataSets::recordDesc(1);
  ASSERT_NE(desc, nullptr);
  EXPECT_STRNE(desc, "");
}

TEST_F(IptcDataSetsTest_645, RecordDesc_Application2_645) {
  const char* desc = Exiv2::IptcDataSets::recordDesc(2);
  ASSERT_NE(desc, nullptr);
}

// --- recordId ---

TEST_F(IptcDataSetsTest_645, RecordId_Envelope_645) {
  uint16_t id = Exiv2::IptcDataSets::recordId("Envelope");
  EXPECT_EQ(id, 1);
}

TEST_F(IptcDataSetsTest_645, RecordId_Application2_645) {
  uint16_t id = Exiv2::IptcDataSets::recordId("Application2");
  EXPECT_EQ(id, 2);
}

TEST_F(IptcDataSetsTest_645, RecordId_UnknownThrows_645) {
  EXPECT_THROW(Exiv2::IptcDataSets::recordId("NonExistentRecord"), Exiv2::Error);
}

// --- envelopeRecordList / application2RecordList ---

TEST_F(IptcDataSetsTest_645, EnvelopeRecordListNotNull_645) {
  const Exiv2::DataSet* list = Exiv2::IptcDataSets::envelopeRecordList();
  ASSERT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_645, Application2RecordListNotNull_645) {
  const Exiv2::DataSet* list = Exiv2::IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);
}

// --- dataSetList ---

TEST_F(IptcDataSetsTest_645, DataSetListProducesOutput_645) {
  std::ostringstream oss;
  Exiv2::IptcDataSets::dataSetList(oss);
  std::string output = oss.str();
  EXPECT_FALSE(output.empty());
  // Should contain known dataset names
  EXPECT_NE(output.find("ModelVersion"), std::string::npos);
  EXPECT_NE(output.find("ObjectName"), std::string::npos);
}

// ============================================================
// IptcKey tests
// ============================================================

class IptcKeyTest_645 : public ::testing::Test {};

// --- Construction from string ---

TEST_F(IptcKeyTest_645, ConstructFromString_ValidKey_645) {
  Exiv2::IptcKey key("Iptc.Application2.ObjectName");
  EXPECT_EQ(key.tag(), 5);
  EXPECT_EQ(key.record(), 2);
}

TEST_F(IptcKeyTest_645, ConstructFromString_EnvelopeKey_645) {
  Exiv2::IptcKey key("Iptc.Envelope.ModelVersion");
  EXPECT_EQ(key.tag(), 0);
  EXPECT_EQ(key.record(), 1);
}

TEST_F(IptcKeyTest_645, ConstructFromString_InvalidKeyThrows_645) {
  EXPECT_THROW(Exiv2::IptcKey("Invalid.Key.String"), Exiv2::Error);
}

TEST_F(IptcKeyTest_645, ConstructFromString_WrongFamilyThrows_645) {
  EXPECT_THROW(Exiv2::IptcKey("Exif.Application2.ObjectName"), Exiv2::Error);
}

// --- Construction from tag and record ---

TEST_F(IptcKeyTest_645, ConstructFromTagRecord_645) {
  Exiv2::IptcKey key(5, 2);
  EXPECT_EQ(key.tag(), 5);
  EXPECT_EQ(key.record(), 2);
}

TEST_F(IptcKeyTest_645, ConstructFromTagRecord_Envelope_645) {
  Exiv2::IptcKey key(0, 1);
  EXPECT_EQ(key.tag(), 0);
  EXPECT_EQ(key.record(), 1);
}

// --- key() ---

TEST_F(IptcKeyTest_645, Key_CorrectFormat_645) {
  Exiv2::IptcKey key(5, 2);
  std::string k = key.key();
  EXPECT_EQ(k, "Iptc.Application2.ObjectName");
}

TEST_F(IptcKeyTest_645, Key_EnvelopeFormat_645) {
  Exiv2::IptcKey key(0, 1);
  std::string k = key.key();
  EXPECT_EQ(k, "Iptc.Envelope.ModelVersion");
}

// --- familyName() ---

TEST_F(IptcKeyTest_645, FamilyName_645) {
  Exiv2::IptcKey key(5, 2);
  EXPECT_STREQ(key.familyName(), "Iptc");
}

// --- groupName() ---

TEST_F(IptcKeyTest_645, GroupName_Application2_645) {
  Exiv2::IptcKey key(5, 2);
  EXPECT_EQ(key.groupName(), "Application2");
}

TEST_F(IptcKeyTest_645, GroupName_Envelope_645) {
  Exiv2::IptcKey key(0, 1);
  EXPECT_EQ(key.groupName(), "Envelope");
}

// --- tagName() ---

TEST_F(IptcKeyTest_645, TagName_ObjectName_645) {
  Exiv2::IptcKey key(5, 2);
  EXPECT_EQ(key.tagName(), "ObjectName");
}

TEST_F(IptcKeyTest_645, TagName_ModelVersion_645) {
  Exiv2::IptcKey key(0, 1);
  EXPECT_EQ(key.tagName(), "ModelVersion");
}

// --- tagLabel() ---

TEST_F(IptcKeyTest_645, TagLabel_NotEmpty_645) {
  Exiv2::IptcKey key(5, 2);
  std::string label = key.tagLabel();
  EXPECT_FALSE(label.empty());
}

// --- tagDesc() ---

TEST_F(IptcKeyTest_645, TagDesc_NotEmpty_645) {
  Exiv2::IptcKey key(5, 2);
  std::string desc = key.tagDesc();
  EXPECT_FALSE(desc.empty());
}

TEST_F(IptcKeyTest_645, TagDesc_ConsistentWithDataSets_645) {
  Exiv2::IptcKey key(5, 2);
  const char* expected = Exiv2::IptcDataSets::dataSetDesc(5, 2);
  EXPECT_EQ(key.tagDesc(), std::string(expected));
}

// --- recordName() ---

TEST_F(IptcKeyTest_645, RecordName_645) {
  Exiv2::IptcKey key(5, 2);
  EXPECT_EQ(key.recordName(), "Application2");
}

// --- record() ---

TEST_F(IptcKeyTest_645, Record_645) {
  Exiv2::IptcKey key(5, 2);
  EXPECT_EQ(key.record(), 2);
}

// --- clone() ---

TEST_F(IptcKeyTest_645, Clone_ReturnsSameValues_645) {
  Exiv2::IptcKey key(5, 2);
  auto cloned = key.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->key(), key.key());
  EXPECT_EQ(cloned->tag(), key.tag());
  EXPECT_EQ(cloned->record(), key.record());
  EXPECT_STREQ(cloned->familyName(), key.familyName());
  EXPECT_EQ(cloned->groupName(), key.groupName());
  EXPECT_EQ(cloned->tagName(), key.tagName());
}

TEST_F(IptcKeyTest_645, Clone_IsIndependentCopy_645) {
  Exiv2::IptcKey key(25, 2);
  auto cloned = key.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->tag(), 25);
  EXPECT_EQ(cloned->record(), 2);
}

// --- Boundary: unknown dataset via tag/record ---

TEST_F(IptcKeyTest_645, UnknownDataSet_TagRecord_645) {
  Exiv2::IptcKey key(0xFF, 2);
  // Should still produce a key string; tagName may be hex
  std::string k = key.key();
  EXPECT_FALSE(k.empty());
  EXPECT_EQ(key.tag(), 0xFF);
  EXPECT_EQ(key.record(), 2);
}

// --- Keywords dataset (repeatable) ---

TEST_F(IptcKeyTest_645, Keywords_Key_645) {
  Exiv2::IptcKey key("Iptc.Application2.Keywords");
  EXPECT_EQ(key.tag(), 25);
  EXPECT_EQ(key.record(), 2);
  EXPECT_EQ(key.tagName(), "Keywords");
}

// --- Round-trip: string -> IptcKey -> key() ---

TEST_F(IptcKeyTest_645, RoundTrip_StringConstruction_645) {
  std::string original = "Iptc.Application2.Caption";
  Exiv2::IptcKey key(original);
  EXPECT_EQ(key.key(), original);
}

TEST_F(IptcKeyTest_645, RoundTrip_TagRecordConstruction_645) {
  Exiv2::IptcKey key1(120, 2);
  std::string keyStr = key1.key();
  Exiv2::IptcKey key2(keyStr);
  EXPECT_EQ(key2.tag(), key1.tag());
  EXPECT_EQ(key2.record(), key1.record());
  EXPECT_EQ(key2.key(), key1.key());
}

}  // namespace
