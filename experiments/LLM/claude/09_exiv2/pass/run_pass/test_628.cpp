#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "exiv2/datasets.hpp"

using namespace Exiv2;

class IptcDataSetsTest_628 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Tests for application2RecordList()
// ============================================================

TEST_F(IptcDataSetsTest_628, Application2RecordListIsNotNull_628) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_628, Application2RecordListFirstEntryIsRecordVersion_628) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
    EXPECT_EQ(list[0].number_, IptcDataSets::RecordVersion);
}

TEST_F(IptcDataSetsTest_628, Application2RecordListLastEntryIsInvalid_628) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
    // Find the sentinel entry (number_ == 65535)
    int i = 0;
    while (list[i].number_ != 65535) {
        ++i;
    }
    EXPECT_EQ(list[i].number_, 65535);
}

// ============================================================
// Tests for envelopeRecordList()
// ============================================================

TEST_F(IptcDataSetsTest_628, EnvelopeRecordListIsNotNull_628) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
}

// ============================================================
// Tests for dataSetName()
// ============================================================

TEST_F(IptcDataSetsTest_628, DataSetNameRecordVersion_628) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::RecordVersion, IptcDataSets::application2);
    EXPECT_EQ(name, "RecordVersion");
}

TEST_F(IptcDataSetsTest_628, DataSetNameObjectName_628) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::ObjectName, IptcDataSets::application2);
    EXPECT_EQ(name, "ObjectName");
}

TEST_F(IptcDataSetsTest_628, DataSetNameKeywords_628) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::Keywords, IptcDataSets::application2);
    EXPECT_EQ(name, "Keywords");
}

TEST_F(IptcDataSetsTest_628, DataSetNameCaption_628) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::Caption, IptcDataSets::application2);
    EXPECT_EQ(name, "Caption");
}

TEST_F(IptcDataSetsTest_628, DataSetNameDateCreated_628) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::DateCreated, IptcDataSets::application2);
    EXPECT_EQ(name, "DateCreated");
}

TEST_F(IptcDataSetsTest_628, DataSetNameByline_628) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::Byline, IptcDataSets::application2);
    EXPECT_EQ(name, "Byline");
}

TEST_F(IptcDataSetsTest_628, DataSetNameCopyright_628) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::Copyright, IptcDataSets::application2);
    EXPECT_EQ(name, "Copyright");
}

TEST_F(IptcDataSetsTest_628, DataSetNameCity_628) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::City, IptcDataSets::application2);
    EXPECT_EQ(name, "City");
}

TEST_F(IptcDataSetsTest_628, DataSetNameUnknownDataSet_628) {
    // An unknown dataset number should return some default/fallback name
    std::string name = IptcDataSets::dataSetName(0xFFFE, IptcDataSets::application2);
    EXPECT_FALSE(name.empty());
}

// ============================================================
// Tests for dataSetTitle()
// ============================================================

TEST_F(IptcDataSetsTest_628, DataSetTitleRecordVersion_628) {
    const char* title = IptcDataSets::dataSetTitle(IptcDataSets::RecordVersion, IptcDataSets::application2);
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title, "Record Version");
}

TEST_F(IptcDataSetsTest_628, DataSetTitleKeywords_628) {
    const char* title = IptcDataSets::dataSetTitle(IptcDataSets::Keywords, IptcDataSets::application2);
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title, "Keywords");
}

TEST_F(IptcDataSetsTest_628, DataSetTitleHeadline_628) {
    const char* title = IptcDataSets::dataSetTitle(IptcDataSets::Headline, IptcDataSets::application2);
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title, "Headline");
}

// ============================================================
// Tests for dataSetDesc()
// ============================================================

TEST_F(IptcDataSetsTest_628, DataSetDescRecordVersion_628) {
    const char* desc = IptcDataSets::dataSetDesc(IptcDataSets::RecordVersion, IptcDataSets::application2);
    ASSERT_NE(desc, nullptr);
    EXPECT_TRUE(std::string(desc).find("binary number") != std::string::npos);
}

TEST_F(IptcDataSetsTest_628, DataSetDescCaption_628) {
    const char* desc = IptcDataSets::dataSetDesc(IptcDataSets::Caption, IptcDataSets::application2);
    ASSERT_NE(desc, nullptr);
    EXPECT_TRUE(std::string(desc).length() > 0);
}

// ============================================================
// Tests for dataSetPsName()
// ============================================================

TEST_F(IptcDataSetsTest_628, DataSetPsNameObjectName_628) {
    const char* psName = IptcDataSets::dataSetPsName(IptcDataSets::ObjectName, IptcDataSets::application2);
    ASSERT_NE(psName, nullptr);
    EXPECT_STREQ(psName, "Document Title");
}

TEST_F(IptcDataSetsTest_628, DataSetPsNameUrgency_628) {
    const char* psName = IptcDataSets::dataSetPsName(IptcDataSets::Urgency, IptcDataSets::application2);
    ASSERT_NE(psName, nullptr);
    EXPECT_STREQ(psName, "Urgency");
}

TEST_F(IptcDataSetsTest_628, DataSetPsNameCategory_628) {
    const char* psName = IptcDataSets::dataSetPsName(IptcDataSets::Category, IptcDataSets::application2);
    ASSERT_NE(psName, nullptr);
    EXPECT_STREQ(psName, "Category");
}

TEST_F(IptcDataSetsTest_628, DataSetPsNameCaption_628) {
    const char* psName = IptcDataSets::dataSetPsName(IptcDataSets::Caption, IptcDataSets::application2);
    ASSERT_NE(psName, nullptr);
    EXPECT_STREQ(psName, "Description");
}

TEST_F(IptcDataSetsTest_628, DataSetPsNameByline_628) {
    const char* psName = IptcDataSets::dataSetPsName(IptcDataSets::Byline, IptcDataSets::application2);
    ASSERT_NE(psName, nullptr);
    EXPECT_STREQ(psName, "Author");
}

TEST_F(IptcDataSetsTest_628, DataSetPsNameEmptyForRecordVersion_628) {
    const char* psName = IptcDataSets::dataSetPsName(IptcDataSets::RecordVersion, IptcDataSets::application2);
    ASSERT_NE(psName, nullptr);
    EXPECT_STREQ(psName, "");
}

// ============================================================
// Tests for dataSetRepeatable()
// ============================================================

TEST_F(IptcDataSetsTest_628, DataSetRepeatableRecordVersionIsFalse_628) {
    EXPECT_FALSE(IptcDataSets::dataSetRepeatable(IptcDataSets::RecordVersion, IptcDataSets::application2));
}

TEST_F(IptcDataSetsTest_628, DataSetRepeatableKeywordsIsTrue_628) {
    EXPECT_TRUE(IptcDataSets::dataSetRepeatable(IptcDataSets::Keywords, IptcDataSets::application2));
}

TEST_F(IptcDataSetsTest_628, DataSetRepeatableBylineIsTrue_628) {
    EXPECT_TRUE(IptcDataSets::dataSetRepeatable(IptcDataSets::Byline, IptcDataSets::application2));
}

TEST_F(IptcDataSetsTest_628, DataSetRepeatableObjectAttributeIsTrue_628) {
    EXPECT_TRUE(IptcDataSets::dataSetRepeatable(IptcDataSets::ObjectAttribute, IptcDataSets::application2));
}

TEST_F(IptcDataSetsTest_628, DataSetRepeatableSuppCategoryIsTrue_628) {
    EXPECT_TRUE(IptcDataSets::dataSetRepeatable(IptcDataSets::SuppCategory, IptcDataSets::application2));
}

TEST_F(IptcDataSetsTest_628, DataSetRepeatableContactIsTrue_628) {
    EXPECT_TRUE(IptcDataSets::dataSetRepeatable(IptcDataSets::Contact, IptcDataSets::application2));
}

TEST_F(IptcDataSetsTest_628, DataSetRepeatableCaptionIsFalse_628) {
    EXPECT_FALSE(IptcDataSets::dataSetRepeatable(IptcDataSets::Caption, IptcDataSets::application2));
}

// ============================================================
// Tests for dataSet() (lookup by name)
// ============================================================

TEST_F(IptcDataSetsTest_628, DataSetLookupByNameRecordVersion_628) {
    uint16_t number = IptcDataSets::dataSet("RecordVersion", IptcDataSets::application2);
    EXPECT_EQ(number, IptcDataSets::RecordVersion);
}

TEST_F(IptcDataSetsTest_628, DataSetLookupByNameKeywords_628) {
    uint16_t number = IptcDataSets::dataSet("Keywords", IptcDataSets::application2);
    EXPECT_EQ(number, IptcDataSets::Keywords);
}

TEST_F(IptcDataSetsTest_628, DataSetLookupByNameCaption_628) {
    uint16_t number = IptcDataSets::dataSet("Caption", IptcDataSets::application2);
    EXPECT_EQ(number, IptcDataSets::Caption);
}

TEST_F(IptcDataSetsTest_628, DataSetLookupByNameByline_628) {
    uint16_t number = IptcDataSets::dataSet("Byline", IptcDataSets::application2);
    EXPECT_EQ(number, IptcDataSets::Byline);
}

TEST_F(IptcDataSetsTest_628, DataSetLookupByNameCity_628) {
    uint16_t number = IptcDataSets::dataSet("City", IptcDataSets::application2);
    EXPECT_EQ(number, IptcDataSets::City);
}

TEST_F(IptcDataSetsTest_628, DataSetLookupByNameCopyright_628) {
    uint16_t number = IptcDataSets::dataSet("Copyright", IptcDataSets::application2);
    EXPECT_EQ(number, IptcDataSets::Copyright);
}

// ============================================================
// Tests for dataSetType()
// ============================================================

TEST_F(IptcDataSetsTest_628, DataSetTypeRecordVersionIsUnsignedShort_628) {
    TypeId type = IptcDataSets::dataSetType(IptcDataSets::RecordVersion, IptcDataSets::application2);
    EXPECT_EQ(type, Exiv2::unsignedShort);
}

TEST_F(IptcDataSetsTest_628, DataSetTypeKeywordsIsString_628) {
    TypeId type = IptcDataSets::dataSetType(IptcDataSets::Keywords, IptcDataSets::application2);
    EXPECT_EQ(type, Exiv2::string);
}

TEST_F(IptcDataSetsTest_628, DataSetTypeDateCreatedIsDate_628) {
    TypeId type = IptcDataSets::dataSetType(IptcDataSets::DateCreated, IptcDataSets::application2);
    EXPECT_EQ(type, Exiv2::date);
}

TEST_F(IptcDataSetsTest_628, DataSetTypeTimeCreatedIsTime_628) {
    TypeId type = IptcDataSets::dataSetType(IptcDataSets::TimeCreated, IptcDataSets::application2);
    EXPECT_EQ(type, Exiv2::time);
}

TEST_F(IptcDataSetsTest_628, DataSetTypePreviewIsUndefined_628) {
    TypeId type = IptcDataSets::dataSetType(IptcDataSets::Preview, IptcDataSets::application2);
    EXPECT_EQ(type, Exiv2::undefined);
}

TEST_F(IptcDataSetsTest_628, DataSetTypeRasterizedCaptionIsUndefined_628) {
    TypeId type = IptcDataSets::dataSetType(IptcDataSets::RasterizedCaption, IptcDataSets::application2);
    EXPECT_EQ(type, Exiv2::undefined);
}

// ============================================================
// Tests for recordName()
// ============================================================

TEST_F(IptcDataSetsTest_628, RecordNameApplication2_628) {
    std::string name = IptcDataSets::recordName(IptcDataSets::application2);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_628, RecordNameEnvelope_628) {
    std::string name = IptcDataSets::recordName(IptcDataSets::envelope);
    EXPECT_FALSE(name.empty());
}

// ============================================================
// Tests for recordDesc()
// ============================================================

TEST_F(IptcDataSetsTest_628, RecordDescApplication2_628) {
    const char* desc = IptcDataSets::recordDesc(IptcDataSets::application2);
    ASSERT_NE(desc, nullptr);
}

TEST_F(IptcDataSetsTest_628, RecordDescEnvelope_628) {
    const char* desc = IptcDataSets::recordDesc(IptcDataSets::envelope);
    ASSERT_NE(desc, nullptr);
}

// ============================================================
// Tests for recordId()
// ============================================================

TEST_F(IptcDataSetsTest_628, RecordIdApplication2_628) {
    std::string recName = IptcDataSets::recordName(IptcDataSets::application2);
    uint16_t id = IptcDataSets::recordId(recName);
    EXPECT_EQ(id, IptcDataSets::application2);
}

TEST_F(IptcDataSetsTest_628, RecordIdEnvelope_628) {
    std::string recName = IptcDataSets::recordName(IptcDataSets::envelope);
    uint16_t id = IptcDataSets::recordId(recName);
    EXPECT_EQ(id, IptcDataSets::envelope);
}

// ============================================================
// Tests for dataSetList()
// ============================================================

TEST_F(IptcDataSetsTest_628, DataSetListProducesOutput_628) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(IptcDataSetsTest_628, DataSetListContainsKeywords_628) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_TRUE(output.find("Keywords") != std::string::npos);
}

TEST_F(IptcDataSetsTest_628, DataSetListContainsCaption_628) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_TRUE(output.find("Caption") != std::string::npos);
}

TEST_F(IptcDataSetsTest_628, DataSetListContainsRecordVersion_628) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_TRUE(output.find("RecordVersion") != std::string::npos);
}

// ============================================================
// Roundtrip tests: name -> number -> name
// ============================================================

TEST_F(IptcDataSetsTest_628, RoundtripNameToNumberRecordVersion_628) {
    uint16_t number = IptcDataSets::dataSet("RecordVersion", IptcDataSets::application2);
    std::string name = IptcDataSets::dataSetName(number, IptcDataSets::application2);
    EXPECT_EQ(name, "RecordVersion");
}

TEST_F(IptcDataSetsTest_628, RoundtripNameToNumberKeywords_628) {
    uint16_t number = IptcDataSets::dataSet("Keywords", IptcDataSets::application2);
    std::string name = IptcDataSets::dataSetName(number, IptcDataSets::application2);
    EXPECT_EQ(name, "Keywords");
}

TEST_F(IptcDataSetsTest_628, RoundtripNameToNumberHeadline_628) {
    uint16_t number = IptcDataSets::dataSet("Headline", IptcDataSets::application2);
    std::string name = IptcDataSets::dataSetName(number, IptcDataSets::application2);
    EXPECT_EQ(name, "Headline");
}

// ============================================================
// Boundary / edge case tests
// ============================================================

TEST_F(IptcDataSetsTest_628, DataSetNameForInvalidNumber_628) {
    // 65535 is the sentinel invalid entry
    std::string name = IptcDataSets::dataSetName(65535, IptcDataSets::application2);
    // Should return something (the invalid sentinel name)
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_628, DataSetTitleForInvalidNumber_628) {
    const char* title = IptcDataSets::dataSetTitle(65535, IptcDataSets::application2);
    ASSERT_NE(title, nullptr);
}

TEST_F(IptcDataSetsTest_628, DataSetDescForInvalidNumber_628) {
    const char* desc = IptcDataSets::dataSetDesc(65535, IptcDataSets::application2);
    ASSERT_NE(desc, nullptr);
}

TEST_F(IptcDataSetsTest_628, DataSetTypeForPreviewFormat_628) {
    TypeId type = IptcDataSets::dataSetType(IptcDataSets::PreviewFormat, IptcDataSets::application2);
    EXPECT_EQ(type, Exiv2::unsignedShort);
}

TEST_F(IptcDataSetsTest_628, DataSetTypeForPreviewVersion_628) {
    TypeId type = IptcDataSets::dataSetType(IptcDataSets::PreviewVersion, IptcDataSets::application2);
    EXPECT_EQ(type, Exiv2::unsignedShort);
}

// ============================================================
// Test various datasets that have specific psName values
// ============================================================

TEST_F(IptcDataSetsTest_628, DataSetPsNameWriter_628) {
    const char* psName = IptcDataSets::dataSetPsName(IptcDataSets::Writer, IptcDataSets::application2);
    ASSERT_NE(psName, nullptr);
    EXPECT_STREQ(psName, "Description writer");
}

TEST_F(IptcDataSetsTest_628, DataSetPsNameCredit_628) {
    const char* psName = IptcDataSets::dataSetPsName(IptcDataSets::Credit, IptcDataSets::application2);
    ASSERT_NE(psName, nullptr);
    EXPECT_STREQ(psName, "Credit");
}

TEST_F(IptcDataSetsTest_628, DataSetPsNameSource_628) {
    const char* psName = IptcDataSets::dataSetPsName(IptcDataSets::Source, IptcDataSets::application2);
    ASSERT_NE(psName, nullptr);
    EXPECT_STREQ(psName, "Source");
}

TEST_F(IptcDataSetsTest_628, DataSetPsNameCopyrightNotice_628) {
    const char* psName = IptcDataSets::dataSetPsName(IptcDataSets::Copyright, IptcDataSets::application2);
    ASSERT_NE(psName, nullptr);
    EXPECT_STREQ(psName, "Copyright Notice");
}

TEST_F(IptcDataSetsTest_628, DataSetPsNameCountry_628) {
    const char* psName = IptcDataSets::dataSetPsName(IptcDataSets::CountryName, IptcDataSets::application2);
    ASSERT_NE(psName, nullptr);
    EXPECT_STREQ(psName, "Country");
}

TEST_F(IptcDataSetsTest_628, DataSetPsNameStateProvince_628) {
    const char* psName = IptcDataSets::dataSetPsName(IptcDataSets::ProvinceState, IptcDataSets::application2);
    ASSERT_NE(psName, nullptr);
    EXPECT_STREQ(psName, "State/Province");
}

TEST_F(IptcDataSetsTest_628, DataSetPsNameTransmissionReference_628) {
    const char* psName = IptcDataSets::dataSetPsName(IptcDataSets::TransmissionReference, IptcDataSets::application2);
    ASSERT_NE(psName, nullptr);
    EXPECT_STREQ(psName, "Transmission Reference");
}

// ============================================================
// Test for multiple datasets that are not repeatable
// ============================================================

TEST_F(IptcDataSetsTest_628, DataSetRepeatableCityIsFalse_628) {
    EXPECT_FALSE(IptcDataSets::dataSetRepeatable(IptcDataSets::City, IptcDataSets::application2));
}

TEST_F(IptcDataSetsTest_628, DataSetRepeatableHeadlineIsFalse_628) {
    EXPECT_FALSE(IptcDataSets::dataSetRepeatable(IptcDataSets::Headline, IptcDataSets::application2));
}

TEST_F(IptcDataSetsTest_628, DataSetRepeatableCopyrightIsFalse_628) {
    EXPECT_FALSE(IptcDataSets::dataSetRepeatable(IptcDataSets::Copyright, IptcDataSets::application2));
}

TEST_F(IptcDataSetsTest_628, DataSetRepeatableWriterIsTrue_628) {
    EXPECT_TRUE(IptcDataSets::dataSetRepeatable(IptcDataSets::Writer, IptcDataSets::application2));
}

TEST_F(IptcDataSetsTest_628, DataSetRepeatableSubjectIsTrue_628) {
    EXPECT_TRUE(IptcDataSets::dataSetRepeatable(IptcDataSets::Subject, IptcDataSets::application2));
}
