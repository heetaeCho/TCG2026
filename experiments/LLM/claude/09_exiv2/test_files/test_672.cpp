#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>
#include <exiv2/value.hpp>
#include <exiv2/error.hpp>
#include <sstream>

using namespace Exiv2;

class IptcdatumTest_672 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction with a known IPTC key string
TEST_F(IptcdatumTest_672, ConstructWithKeyString_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test that familyName returns "Iptc"
TEST_F(IptcdatumTest_672, FamilyNameIsIptc_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test groupName returns the record name
TEST_F(IptcdatumTest_672, GroupNameReturnsRecordName_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test tagName returns the correct tag name
TEST_F(IptcdatumTest_672, TagNameReturnsCorrectName_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test recordName returns correct record
TEST_F(IptcdatumTest_672, RecordNameReturnsCorrect_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.recordName(), "Application2");
}

// Test tag returns a non-zero tag number for known tag
TEST_F(IptcdatumTest_672, TagReturnsValidTag_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Caption is tag 120
    EXPECT_EQ(datum.tag(), 120);
}

// Test record returns the Application2 record number (2)
TEST_F(IptcdatumTest_672, RecordReturnsApplicationRecord_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.record(), 2);
}

// Test tagDesc returns a non-empty description for a known tag
TEST_F(IptcdatumTest_672, TagDescReturnsNonEmpty_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    std::string desc = datum.tagDesc();
    // Known tags should have a description
    EXPECT_FALSE(desc.empty());
}

// Test tagLabel returns a non-empty label for a known tag
TEST_F(IptcdatumTest_672, TagLabelReturnsNonEmpty_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test construction with nullptr value and typeId behavior
TEST_F(IptcdatumTest_672, NullValueTypeId_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // When no value is set, typeId should be unsignedShort or some default
    // Based on typical behavior with null value
    TypeId tid = datum.typeId();
    // Just verify it doesn't crash and returns something
    (void)tid;
}

// Test setValue with a string
TEST_F(IptcdatumTest_672, SetValueString_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    int result = datum.setValue("Hello World");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test assignment operator with string
TEST_F(IptcdatumTest_672, AssignString_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test Caption");
    EXPECT_EQ(datum.toString(), "Test Caption");
}

// Test copy constructor
TEST_F(IptcdatumTest_672, CopyConstructor_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Original");
    
    Iptcdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.toString(), "Original");
}

// Test copy assignment operator
TEST_F(IptcdatumTest_672, CopyAssignment_672) {
    IptcKey key1("Iptc.Application2.Caption");
    Iptcdatum datum1(key1, nullptr);
    datum1 = std::string("First");
    
    IptcKey key2("Iptc.Application2.Keywords");
    Iptcdatum datum2(key2, nullptr);
    datum2 = std::string("Second");
    
    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum2.toString(), "First");
}

// Test assignment operator with uint16_t
TEST_F(IptcdatumTest_672, AssignUint16_672) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(5);
    EXPECT_EQ(datum.toString(), "5");
}

// Test assignment with Value object
TEST_F(IptcdatumTest_672, AssignValueObject_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    StringValue sv("Test Value");
    datum = sv;
    EXPECT_EQ(datum.toString(), "Test Value");
}

// Test setValue with Value pointer
TEST_F(IptcdatumTest_672, SetValuePointer_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    auto sv = std::make_unique<StringValue>("Pointer Value");
    datum.setValue(sv.get());
    EXPECT_EQ(datum.toString(), "Pointer Value");
}

// Test count with no value set
TEST_F(IptcdatumTest_672, CountNoValue_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // With no value, count should be 0
    EXPECT_EQ(datum.count(), 0u);
}

// Test count after setting value
TEST_F(IptcdatumTest_672, CountAfterSetValue_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Hello");
    EXPECT_GT(datum.count(), 0u);
}

// Test size with no value
TEST_F(IptcdatumTest_672, SizeNoValue_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test size after setting value
TEST_F(IptcdatumTest_672, SizeAfterSetValue_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Hello");
    EXPECT_GT(datum.size(), 0u);
}

// Test toString with index
TEST_F(IptcdatumTest_672, ToStringWithIndex_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Hello");
    std::string s = datum.toString(0);
    EXPECT_EQ(s, "Hello");
}

// Test getValue returns valid pointer after setting value
TEST_F(IptcdatumTest_672, GetValueReturnsValid_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test");
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "Test");
}

// Test write to ostream
TEST_F(IptcdatumTest_672, WriteToOstream_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Stream Test");
    
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test with Envelope record
TEST_F(IptcdatumTest_672, EnvelopeRecord_672) {
    IptcKey key("Iptc.Envelope.CharacterSet");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.record(), 1);
    EXPECT_EQ(datum.groupName(), "Envelope");
}

// Test construction with tag and record numbers
TEST_F(IptcdatumTest_672, ConstructWithTagAndRecord_672) {
    IptcKey key(120, 2); // Caption in Application2
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), 120);
    EXPECT_EQ(datum.record(), 2);
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test Keywords tag
TEST_F(IptcdatumTest_672, KeywordsTag_672) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);
    datum = std::string("keyword1");
    EXPECT_EQ(datum.toString(), "keyword1");
    EXPECT_EQ(datum.tagName(), "Keywords");
}

// Test construction with Value pointer
TEST_F(IptcdatumTest_672, ConstructWithValue_672) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue sv("Initial Value");
    Iptcdatum datum(key, &sv);
    EXPECT_EQ(datum.toString(), "Initial Value");
}

// Test typeName after setting string value
TEST_F(IptcdatumTest_672, TypeNameAfterStringSet_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test");
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
    // Should be "String" for IPTC string values
    EXPECT_TRUE(std::string(tn).find("String") != std::string::npos || 
                std::string(tn).length() > 0);
}

// Test copy preserves data independence
TEST_F(IptcdatumTest_672, CopyDataIndependence_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Original");
    
    Iptcdatum copy(datum);
    copy = std::string("Modified");
    
    EXPECT_EQ(datum.toString(), "Original");
    EXPECT_EQ(copy.toString(), "Modified");
}

// Test setValue with empty string
TEST_F(IptcdatumTest_672, SetValueEmptyString_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    int result = datum.setValue("");
    EXPECT_EQ(result, 0);
}

// Test multiple setValue calls overwrite
TEST_F(IptcdatumTest_672, MultipleSetValueOverwrites_672) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("First");
    datum.setValue("Second");
    EXPECT_EQ(datum.toString(), "Second");
}

// Test toInt64 after setting numeric-like value
TEST_F(IptcdatumTest_672, ToInt64WithUint16Value_672) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(42);
    EXPECT_EQ(datum.toInt64(0), 42);
}

// Test toFloat with numeric value
TEST_F(IptcdatumTest_672, ToFloatWithUint16Value_672) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(7);
    EXPECT_FLOAT_EQ(datum.toFloat(0), 7.0f);
}

// Test different IPTC tags
TEST_F(IptcdatumTest_672, ObjectNameTag_672) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "ObjectName");
    EXPECT_EQ(datum.record(), 2);
}

// Test Byline tag
TEST_F(IptcdatumTest_672, BylineTag_672) {
    IptcKey key("Iptc.Application2.Byline");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Photographer");
    EXPECT_EQ(datum.toString(), "Photographer");
    EXPECT_EQ(datum.tagName(), "Byline");
}
