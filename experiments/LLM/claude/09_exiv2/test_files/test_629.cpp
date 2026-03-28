#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "exiv2/datasets.hpp"

using namespace Exiv2;

// Record IDs commonly used in IPTC
static const uint16_t envelopeRecord = 1;
static const uint16_t application2Record = 2;

// ==================== dataSetType tests ====================

TEST(IptcDataSetsTest_629, DataSetTypeKnownEnvelopeRecord_629) {
  // DataSet 0 in envelope record (ModelVersion) should have a type
  TypeId type = IptcDataSets::dataSetType(0, envelopeRecord);
  EXPECT_NE(type, Exiv2::string);  // ModelVersion is unsignedShort typically
}

TEST(IptcDataSetsTest_629, DataSetTypeUnknownDataSet_629) {
  // An unknown dataset number should return the unknownDataSet type (string)
  TypeId type = IptcDataSets::dataSetType(65535, envelopeRecord);
  EXPECT_EQ(type, Exiv2::string);
}

TEST(IptcDataSetsTest_629, DataSetTypeKnownApplication2Record_629) {
  // DataSet 5 in application2 record (ObjectName/Title) should be string type
  TypeId type = IptcDataSets::dataSetType(5, application2Record);
  EXPECT_EQ(type, Exiv2::string);
}

TEST(IptcDataSetsTest_629, DataSetTypeInvalidRecord_629) {
  // An invalid record ID should return unknown type
  TypeId type = IptcDataSets::dataSetType(0, 255);
  EXPECT_EQ(type, Exiv2::string);
}

// ==================== dataSetName tests ====================

TEST(IptcDataSetsTest_629, DataSetNameKnownEnvelope_629) {
  std::string name = IptcDataSets::dataSetName(0, envelopeRecord);
  EXPECT_FALSE(name.empty());
  EXPECT_NE(name, "Unknown dataset");
}

TEST(IptcDataSetsTest_629, DataSetNameKnownApplication2_629) {
  // ObjectName is dataset 5 in record 2
  std::string name = IptcDataSets::dataSetName(5, application2Record);
  EXPECT_EQ(name, "ObjectName");
}

TEST(IptcDataSetsTest_629, DataSetNameUnknown_629) {
  std::string name = IptcDataSets::dataSetName(999, application2Record);
  // For unknown datasets, typically returns a hex string or "Unknown dataset"
  EXPECT_FALSE(name.empty());
}

TEST(IptcDataSetsTest_629, DataSetNameInvalidRecord_629) {
  std::string name = IptcDataSets::dataSetName(0, 255);
  EXPECT_FALSE(name.empty());
}

// ==================== dataSetTitle tests ====================

TEST(IptcDataSetsTest_629, DataSetTitleKnown_629) {
  const char* title = IptcDataSets::dataSetTitle(5, application2Record);
  ASSERT_NE(title, nullptr);
  EXPECT_GT(strlen(title), 0u);
}

TEST(IptcDataSetsTest_629, DataSetTitleUnknown_629) {
  const char* title = IptcDataSets::dataSetTitle(999, application2Record);
  ASSERT_NE(title, nullptr);
  EXPECT_STREQ(title, "Unknown dataset");
}

// ==================== dataSetDesc tests ====================

TEST(IptcDataSetsTest_629, DataSetDescKnown_629) {
  const char* desc = IptcDataSets::dataSetDesc(5, application2Record);
  ASSERT_NE(desc, nullptr);
  EXPECT_GT(strlen(desc), 0u);
}

TEST(IptcDataSetsTest_629, DataSetDescUnknown_629) {
  const char* desc = IptcDataSets::dataSetDesc(999, application2Record);
  ASSERT_NE(desc, nullptr);
  EXPECT_STREQ(desc, "Unknown dataset");
}

// ==================== dataSetPsName tests ====================

TEST(IptcDataSetsTest_629, DataSetPsNameKnown_629) {
  const char* psName = IptcDataSets::dataSetPsName(5, application2Record);
  ASSERT_NE(psName, nullptr);
}

TEST(IptcDataSetsTest_629, DataSetPsNameUnknown_629) {
  const char* psName = IptcDataSets::dataSetPsName(999, application2Record);
  ASSERT_NE(psName, nullptr);
  EXPECT_STREQ(psName, "Unknown dataset");
}

// ==================== dataSetRepeatable tests ====================

TEST(IptcDataSetsTest_629, DataSetRepeatableKnownNonRepeatable_629) {
  // ObjectName (5, app2) is typically not repeatable
  bool rep = IptcDataSets::dataSetRepeatable(5, application2Record);
  EXPECT_FALSE(rep);
}

TEST(IptcDataSetsTest_629, DataSetRepeatableKnownRepeatable_629) {
  // Keywords (25, app2) is typically repeatable
  bool rep = IptcDataSets::dataSetRepeatable(25, application2Record);
  EXPECT_TRUE(rep);
}

TEST(IptcDataSetsTest_629, DataSetRepeatableUnknown_629) {
  // Unknown dataset has repeatable = true based on unknownDataSet definition
  bool rep = IptcDataSets::dataSetRepeatable(999, application2Record);
  EXPECT_TRUE(rep);
}

// ==================== dataSet (name lookup) tests ====================

TEST(IptcDataSetsTest_629, DataSetByNameKnown_629) {
  uint16_t number = IptcDataSets::dataSet("ObjectName", application2Record);
  EXPECT_EQ(number, 5);
}

TEST(IptcDataSetsTest_629, DataSetByNameUnknown_629) {
  uint16_t number = IptcDataSets::dataSet("NonExistentDataSet", application2Record);
  EXPECT_EQ(number, 0xffff);
}

TEST(IptcDataSetsTest_629, DataSetByNameEnvelope_629) {
  uint16_t number = IptcDataSets::dataSet("ModelVersion", envelopeRecord);
  EXPECT_EQ(number, 0);
}

// ==================== recordName tests ====================

TEST(IptcDataSetsTest_629, RecordNameEnvelope_629) {
  std::string name = IptcDataSets::recordName(envelopeRecord);
  EXPECT_EQ(name, "Envelope");
}

TEST(IptcDataSetsTest_629, RecordNameApplication2_629) {
  std::string name = IptcDataSets::recordName(application2Record);
  EXPECT_EQ(name, "Application2");
}

TEST(IptcDataSetsTest_629, RecordNameUnknown_629) {
  std::string name = IptcDataSets::recordName(255);
  EXPECT_FALSE(name.empty());
}

// ==================== recordDesc tests ====================

TEST(IptcDataSetsTest_629, RecordDescEnvelope_629) {
  const char* desc = IptcDataSets::recordDesc(envelopeRecord);
  ASSERT_NE(desc, nullptr);
  EXPECT_GT(strlen(desc), 0u);
}

TEST(IptcDataSetsTest_629, RecordDescApplication2_629) {
  const char* desc = IptcDataSets::recordDesc(application2Record);
  ASSERT_NE(desc, nullptr);
  EXPECT_GT(strlen(desc), 0u);
}

// ==================== recordId tests ====================

TEST(IptcDataSetsTest_629, RecordIdEnvelope_629) {
  uint16_t id = IptcDataSets::recordId("Envelope");
  EXPECT_EQ(id, envelopeRecord);
}

TEST(IptcDataSetsTest_629, RecordIdApplication2_629) {
  uint16_t id = IptcDataSets::recordId("Application2");
  EXPECT_EQ(id, application2Record);
}

TEST(IptcDataSetsTest_629, RecordIdUnknown_629) {
  uint16_t id = IptcDataSets::recordId("NonExistentRecord");
  // Unknown record should return some error value
  EXPECT_NE(id, envelopeRecord);
  EXPECT_NE(id, application2Record);
}

// ==================== envelopeRecordList tests ====================

TEST(IptcDataSetsTest_629, EnvelopeRecordListNotNull_629) {
  const DataSet* list = IptcDataSets::envelopeRecordList();
  ASSERT_NE(list, nullptr);
}

TEST(IptcDataSetsTest_629, EnvelopeRecordListFirstEntry_629) {
  const DataSet* list = IptcDataSets::envelopeRecordList();
  ASSERT_NE(list, nullptr);
  // First entry should be ModelVersion (number 0)
  EXPECT_EQ(list[0].number_, 0);
}

// ==================== application2RecordList tests ====================

TEST(IptcDataSetsTest_629, Application2RecordListNotNull_629) {
  const DataSet* list = IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);
}

TEST(IptcDataSetsTest_629, Application2RecordListContainsObjectName_629) {
  const DataSet* list = IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);
  // Look for ObjectName (number 5)
  bool found = false;
  for (int i = 0; list[i].number_ != 0xffff; ++i) {
    if (list[i].number_ == 5) {
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// ==================== dataSetList tests ====================

TEST(IptcDataSetsTest_629, DataSetListOutputsData_629) {
  std::ostringstream os;
  IptcDataSets::dataSetList(os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST(IptcDataSetsTest_629, DataSetListContainsKnownName_629) {
  std::ostringstream os;
  IptcDataSets::dataSetList(os);
  std::string output = os.str();
  // Should contain known dataset names
  EXPECT_NE(output.find("ObjectName"), std::string::npos);
}

// ==================== Boundary / edge case tests ====================

TEST(IptcDataSetsTest_629, DataSetTypeZeroRecordZero_629) {
  // Record 0 is not standard, test boundary
  TypeId type = IptcDataSets::dataSetType(0, 0);
  // Should return unknown type since record 0 is not defined
  EXPECT_EQ(type, Exiv2::string);
}

TEST(IptcDataSetsTest_629, DataSetTypeMaxValues_629) {
  TypeId type = IptcDataSets::dataSetType(0xFFFF, 0xFFFF);
  EXPECT_EQ(type, Exiv2::string);
}

TEST(IptcDataSetsTest_629, DataSetNameMaxValues_629) {
  std::string name = IptcDataSets::dataSetName(0xFFFF, 0xFFFF);
  EXPECT_FALSE(name.empty());
}

TEST(IptcDataSetsTest_629, ConsistencyBetweenNameAndNumber_629) {
  // dataSet("ObjectName", app2) should return 5
  // dataSetName(5, app2) should return "ObjectName"
  uint16_t number = IptcDataSets::dataSet("ObjectName", application2Record);
  EXPECT_EQ(number, 5);
  std::string name = IptcDataSets::dataSetName(number, application2Record);
  EXPECT_EQ(name, "ObjectName");
}

TEST(IptcDataSetsTest_629, ConsistencyBetweenRecordNameAndId_629) {
  // recordId("Envelope") should return 1
  // recordName(1) should return "Envelope"
  uint16_t id = IptcDataSets::recordId("Envelope");
  EXPECT_EQ(id, 1);
  std::string name = IptcDataSets::recordName(id);
  EXPECT_EQ(name, "Envelope");
}

TEST(IptcDataSetsTest_629, KeywordsDataSetProperties_629) {
  // Keywords is dataset 25 in application2
  std::string name = IptcDataSets::dataSetName(25, application2Record);
  EXPECT_EQ(name, "Keywords");
  
  TypeId type = IptcDataSets::dataSetType(25, application2Record);
  EXPECT_EQ(type, Exiv2::string);
  
  bool rep = IptcDataSets::dataSetRepeatable(25, application2Record);
  EXPECT_TRUE(rep);
}

TEST(IptcDataSetsTest_629, ModelVersionProperties_629) {
  // ModelVersion is dataset 0 in envelope record
  std::string name = IptcDataSets::dataSetName(0, envelopeRecord);
  EXPECT_EQ(name, "ModelVersion");
  
  TypeId type = IptcDataSets::dataSetType(0, envelopeRecord);
  EXPECT_EQ(type, Exiv2::unsignedShort);
}
