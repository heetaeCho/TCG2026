#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <exiv2/datasets.hpp>

namespace {

// ============================================================
// Tests for IptcDataSets static methods
// ============================================================

class IptcDataSetsTest_644 : public ::testing::Test {
protected:
    // Well-known IPTC envelope record datasets
    static constexpr uint16_t envelopeRecord = 1;
    // Well-known IPTC application2 record datasets
    static constexpr uint16_t application2Record = 2;

    // Some known envelope record dataset numbers
    static constexpr uint16_t modelVersion = 0;      // Model Version
    static constexpr uint16_t destination = 5;        // Destination
    static constexpr uint16_t dateSent = 70;          // Date Sent
    static constexpr uint16_t timeSent = 80;          // Time Sent

    // Some known application2 record dataset numbers
    static constexpr uint16_t objectName = 5;         // Object Name
    static constexpr uint16_t keywords = 25;          // Keywords
    static constexpr uint16_t byline = 80;            // By-line
    static constexpr uint16_t city = 90;              // City
    static constexpr uint16_t caption = 120;          // Caption/Abstract
    static constexpr uint16_t copyright = 116;        // Copyright Notice
};

TEST_F(IptcDataSetsTest_644, DataSetName_KnownEnvelopeDataSet_644) {
    std::string name = Exiv2::IptcDataSets::dataSetName(modelVersion, envelopeRecord);
    EXPECT_EQ(name, "ModelVersion");
}

TEST_F(IptcDataSetsTest_644, DataSetName_KnownApplication2DataSet_644) {
    std::string name = Exiv2::IptcDataSets::dataSetName(objectName, application2Record);
    EXPECT_EQ(name, "ObjectName");
}

TEST_F(IptcDataSetsTest_644, DataSetName_Keywords_644) {
    std::string name = Exiv2::IptcDataSets::dataSetName(keywords, application2Record);
    EXPECT_EQ(name, "Keywords");
}

TEST_F(IptcDataSetsTest_644, DataSetName_UnknownDataSet_644) {
    // Unknown dataset number should return something (likely a hex string or "0x...")
    std::string name = Exiv2::IptcDataSets::dataSetName(9999, application2Record);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_644, DataSetTitle_KnownDataSet_644) {
    const char* title = Exiv2::IptcDataSets::dataSetTitle(objectName, application2Record);
    ASSERT_NE(title, nullptr);
    EXPECT_STRNE(title, "");
}

TEST_F(IptcDataSetsTest_644, DataSetTitle_EnvelopeModelVersion_644) {
    const char* title = Exiv2::IptcDataSets::dataSetTitle(modelVersion, envelopeRecord);
    ASSERT_NE(title, nullptr);
}

TEST_F(IptcDataSetsTest_644, DataSetDesc_KnownDataSet_644) {
    const char* desc = Exiv2::IptcDataSets::dataSetDesc(objectName, application2Record);
    ASSERT_NE(desc, nullptr);
}

TEST_F(IptcDataSetsTest_644, DataSetDesc_UnknownDataSet_644) {
    const char* desc = Exiv2::IptcDataSets::dataSetDesc(9999, application2Record);
    ASSERT_NE(desc, nullptr);
}

TEST_F(IptcDataSetsTest_644, DataSetPsName_KnownDataSet_644) {
    const char* psName = Exiv2::IptcDataSets::dataSetPsName(objectName, application2Record);
    ASSERT_NE(psName, nullptr);
}

TEST_F(IptcDataSetsTest_644, DataSetRepeatable_Keywords_644) {
    // Keywords should be repeatable
    bool repeatable = Exiv2::IptcDataSets::dataSetRepeatable(keywords, application2Record);
    EXPECT_TRUE(repeatable);
}

TEST_F(IptcDataSetsTest_644, DataSetRepeatable_ObjectName_644) {
    // ObjectName is typically not repeatable
    bool repeatable = Exiv2::IptcDataSets::dataSetRepeatable(objectName, application2Record);
    EXPECT_FALSE(repeatable);
}

TEST_F(IptcDataSetsTest_644, DataSet_ByName_ObjectName_644) {
    uint16_t ds = Exiv2::IptcDataSets::dataSet("ObjectName", application2Record);
    EXPECT_EQ(ds, objectName);
}

TEST_F(IptcDataSetsTest_644, DataSet_ByName_Keywords_644) {
    uint16_t ds = Exiv2::IptcDataSets::dataSet("Keywords", application2Record);
    EXPECT_EQ(ds, keywords);
}

TEST_F(IptcDataSetsTest_644, DataSet_ByName_Byline_644) {
    uint16_t ds = Exiv2::IptcDataSets::dataSet("By-line", application2Record);
    EXPECT_EQ(ds, byline);
}

TEST_F(IptcDataSetsTest_644, DataSetType_KnownDataSet_644) {
    Exiv2::TypeId type = Exiv2::IptcDataSets::dataSetType(objectName, application2Record);
    // ObjectName is typically a string type
    EXPECT_EQ(type, Exiv2::string);
}

TEST_F(IptcDataSetsTest_644, DataSetType_ModelVersion_644) {
    Exiv2::TypeId type = Exiv2::IptcDataSets::dataSetType(modelVersion, envelopeRecord);
    // Model Version is typically a short
    EXPECT_EQ(type, Exiv2::unsignedShort);
}

TEST_F(IptcDataSetsTest_644, RecordName_Envelope_644) {
    std::string name = Exiv2::IptcDataSets::recordName(envelopeRecord);
    EXPECT_EQ(name, "Envelope");
}

TEST_F(IptcDataSetsTest_644, RecordName_Application2_644) {
    std::string name = Exiv2::IptcDataSets::recordName(application2Record);
    EXPECT_EQ(name, "Application2");
}

TEST_F(IptcDataSetsTest_644, RecordName_UnknownRecord_644) {
    std::string name = Exiv2::IptcDataSets::recordName(255);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_644, RecordDesc_Envelope_644) {
    const char* desc = Exiv2::IptcDataSets::recordDesc(envelopeRecord);
    ASSERT_NE(desc, nullptr);
}

TEST_F(IptcDataSetsTest_644, RecordDesc_Application2_644) {
    const char* desc = Exiv2::IptcDataSets::recordDesc(application2Record);
    ASSERT_NE(desc, nullptr);
}

TEST_F(IptcDataSetsTest_644, RecordId_Envelope_644) {
    uint16_t id = Exiv2::IptcDataSets::recordId("Envelope");
    EXPECT_EQ(id, envelopeRecord);
}

TEST_F(IptcDataSetsTest_644, RecordId_Application2_644) {
    uint16_t id = Exiv2::IptcDataSets::recordId("Application2");
    EXPECT_EQ(id, application2Record);
}

TEST_F(IptcDataSetsTest_644, EnvelopeRecordList_NotNull_644) {
    const Exiv2::DataSet* list = Exiv2::IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_644, Application2RecordList_NotNull_644) {
    const Exiv2::DataSet* list = Exiv2::IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_644, DataSetList_ProducesOutput_644) {
    std::ostringstream os;
    Exiv2::IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    // Should contain known dataset names
    EXPECT_NE(output.find("ObjectName"), std::string::npos);
    EXPECT_NE(output.find("Keywords"), std::string::npos);
}

// ============================================================
// Tests for IptcKey
// ============================================================

class IptcKeyTest_644 : public ::testing::Test {
};

TEST_F(IptcKeyTest_644, ConstructFromString_Key_644) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.key(), "Iptc.Application2.ObjectName");
}

TEST_F(IptcKeyTest_644, ConstructFromString_FamilyName_644) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_STREQ(key.familyName(), "Iptc");
}

TEST_F(IptcKeyTest_644, ConstructFromString_GroupName_644) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.groupName(), "Application2");
}

TEST_F(IptcKeyTest_644, ConstructFromString_TagName_644) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.tagName(), "ObjectName");
}

TEST_F(IptcKeyTest_644, ConstructFromString_Tag_644) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.tag(), 5);
}

TEST_F(IptcKeyTest_644, ConstructFromString_Record_644) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.record(), 2);
}

TEST_F(IptcKeyTest_644, ConstructFromString_RecordName_644) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.recordName(), "Application2");
}

TEST_F(IptcKeyTest_644, ConstructFromTagAndRecord_644) {
    Exiv2::IptcKey key(5, 2);  // ObjectName in Application2
    EXPECT_EQ(key.tag(), 5);
    EXPECT_EQ(key.record(), 2);
    EXPECT_EQ(key.key(), "Iptc.Application2.ObjectName");
}

TEST_F(IptcKeyTest_644, ConstructFromTagAndRecord_FamilyName_644) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_STREQ(key.familyName(), "Iptc");
}

TEST_F(IptcKeyTest_644, ConstructFromTagAndRecord_GroupName_644) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ(key.groupName(), "Application2");
}

TEST_F(IptcKeyTest_644, ConstructFromTagAndRecord_TagName_644) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ(key.tagName(), "ObjectName");
}

TEST_F(IptcKeyTest_644, TagLabel_ObjectName_644) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

TEST_F(IptcKeyTest_644, TagDesc_ObjectName_644) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::string desc = key.tagDesc();
    EXPECT_FALSE(desc.empty());
}

TEST_F(IptcKeyTest_644, Clone_644) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_EQ(cloned->familyName(), key.familyName());
    EXPECT_EQ(cloned->groupName(), key.groupName());
    EXPECT_EQ(cloned->tagName(), key.tagName());
}

TEST_F(IptcKeyTest_644, ConstructFromString_Keywords_644) {
    Exiv2::IptcKey key("Iptc.Application2.Keywords");
    EXPECT_EQ(key.key(), "Iptc.Application2.Keywords");
    EXPECT_EQ(key.tag(), 25);
    EXPECT_EQ(key.record(), 2);
    EXPECT_EQ(key.tagName(), "Keywords");
}

TEST_F(IptcKeyTest_644, ConstructFromString_EnvelopeRecord_644) {
    Exiv2::IptcKey key("Iptc.Envelope.ModelVersion");
    EXPECT_EQ(key.key(), "Iptc.Envelope.ModelVersion");
    EXPECT_EQ(key.tag(), 0);
    EXPECT_EQ(key.record(), 1);
    EXPECT_EQ(key.groupName(), "Envelope");
    EXPECT_EQ(key.tagName(), "ModelVersion");
}

TEST_F(IptcKeyTest_644, ConstructFromTagAndRecord_EnvelopeModelVersion_644) {
    Exiv2::IptcKey key(0, 1);
    EXPECT_EQ(key.key(), "Iptc.Envelope.ModelVersion");
    EXPECT_EQ(key.tag(), 0);
    EXPECT_EQ(key.record(), 1);
}

TEST_F(IptcKeyTest_644, ConstructFromString_Byline_644) {
    Exiv2::IptcKey key("Iptc.Application2.By-line");
    EXPECT_EQ(key.tag(), 80);
    EXPECT_EQ(key.record(), 2);
}

TEST_F(IptcKeyTest_644, ConstructFromTagAndRecord_Caption_644) {
    Exiv2::IptcKey key(120, 2);  // Caption/Abstract
    EXPECT_EQ(key.tag(), 120);
    EXPECT_EQ(key.record(), 2);
    EXPECT_EQ(key.key(), "Iptc.Application2.Caption");
}

TEST_F(IptcKeyTest_644, TagLabel_FromTagAndRecord_644) {
    Exiv2::IptcKey key(25, 2);  // Keywords
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

TEST_F(IptcKeyTest_644, TagDesc_FromTagAndRecord_644) {
    Exiv2::IptcKey key(25, 2);  // Keywords
    std::string desc = key.tagDesc();
    EXPECT_FALSE(desc.empty());
}

TEST_F(IptcKeyTest_644, InvalidKey_ThrowsException_644) {
    EXPECT_THROW(Exiv2::IptcKey("InvalidKey"), Exiv2::Error);
}

TEST_F(IptcKeyTest_644, InvalidKey_WrongFamily_644) {
    EXPECT_THROW(Exiv2::IptcKey("Exif.Application2.ObjectName"), Exiv2::Error);
}

TEST_F(IptcKeyTest_644, ConstructFromString_City_644) {
    Exiv2::IptcKey key("Iptc.Application2.City");
    EXPECT_EQ(key.tag(), 90);
    EXPECT_EQ(key.record(), 2);
    EXPECT_EQ(key.tagName(), "City");
}

TEST_F(IptcKeyTest_644, ConstructFromTagAndRecord_Destination_644) {
    Exiv2::IptcKey key(5, 1);  // Destination in Envelope
    EXPECT_EQ(key.tag(), 5);
    EXPECT_EQ(key.record(), 1);
    EXPECT_EQ(key.groupName(), "Envelope");
}

// ============================================================
// Roundtrip tests: name -> number -> name
// ============================================================

TEST_F(IptcDataSetsTest_644, Roundtrip_DataSetNameAndNumber_Application2_644) {
    uint16_t ds = Exiv2::IptcDataSets::dataSet("ObjectName", application2Record);
    std::string name = Exiv2::IptcDataSets::dataSetName(ds, application2Record);
    EXPECT_EQ(name, "ObjectName");
}

TEST_F(IptcDataSetsTest_644, Roundtrip_RecordNameAndId_644) {
    uint16_t id = Exiv2::IptcDataSets::recordId("Envelope");
    std::string name = Exiv2::IptcDataSets::recordName(id);
    EXPECT_EQ(name, "Envelope");
}

TEST_F(IptcDataSetsTest_644, Roundtrip_RecordNameAndId_Application2_644) {
    uint16_t id = Exiv2::IptcDataSets::recordId("Application2");
    std::string name = Exiv2::IptcDataSets::recordName(id);
    EXPECT_EQ(name, "Application2");
}

// Boundary: record 0 and very high number
TEST_F(IptcDataSetsTest_644, RecordName_ZeroRecord_644) {
    std::string name = Exiv2::IptcDataSets::recordName(0);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_644, DataSetName_ZeroDataSetZeroRecord_644) {
    std::string name = Exiv2::IptcDataSets::dataSetName(0, 0);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_644, DataSetType_UnknownDataSet_644) {
    // Unknown dataset should return some type (likely string as default)
    Exiv2::TypeId type = Exiv2::IptcDataSets::dataSetType(9999, 2);
    // Just verify it returns a valid TypeId
    EXPECT_GE(static_cast<int>(type), 0);
}

TEST_F(IptcDataSetsTest_644, DataSetRepeatable_UnknownDataSet_644) {
    bool repeatable = Exiv2::IptcDataSets::dataSetRepeatable(9999, 2);
    // Just verify it doesn't crash; unknown datasets are typically not repeatable
    (void)repeatable;
}

TEST_F(IptcDataSetsTest_644, DataSetPsName_UnknownDataSet_644) {
    const char* psName = Exiv2::IptcDataSets::dataSetPsName(9999, 2);
    ASSERT_NE(psName, nullptr);
}

TEST_F(IptcDataSetsTest_644, DataSetTitle_UnknownDataSet_644) {
    const char* title = Exiv2::IptcDataSets::dataSetTitle(9999, 2);
    ASSERT_NE(title, nullptr);
}

} // namespace
