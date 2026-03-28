#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>
#include <exiv2/value.hpp>
#include <sstream>

using namespace Exiv2;

class IptcdatumTest_670 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction with a valid IptcKey and null Value pointer
TEST_F(IptcdatumTest_670, ConstructWithKeyAndNullValue_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test tagName() returns the correct tag name
TEST_F(IptcdatumTest_670, TagNameReturnsCorrectName_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    std::string tagName = datum.tagName();
    EXPECT_EQ(tagName, "Caption");
}

// Test familyName() returns "Iptc"
TEST_F(IptcdatumTest_670, FamilyNameReturnsIptc_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test groupName() returns the correct group
TEST_F(IptcdatumTest_670, GroupNameReturnsCorrectGroup_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test recordName() returns correct record name
TEST_F(IptcdatumTest_670, RecordNameReturnsCorrectRecord_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.recordName(), "Application2");
}

// Test tag() returns correct tag number
TEST_F(IptcdatumTest_670, TagReturnsCorrectTagNumber_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Caption is tag 120 in Application2
    EXPECT_EQ(datum.tag(), 120);
}

// Test record() returns correct record number
TEST_F(IptcdatumTest_670, RecordReturnsCorrectRecordNumber_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Application2 record is 2
    EXPECT_EQ(datum.record(), 2);
}

// Test copy constructor
TEST_F(IptcdatumTest_670, CopyConstructor_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test caption");
    
    Iptcdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.tagName(), datum.tagName());
    EXPECT_EQ(copy.toString(), "Test caption");
}

// Test assignment operator from another Iptcdatum
TEST_F(IptcdatumTest_670, AssignmentOperatorFromIptcdatum_670) {
    IptcKey key1("Iptc.Application2.Caption");
    Iptcdatum datum1(key1, nullptr);
    datum1 = std::string("First caption");

    IptcKey key2("Iptc.Application2.Keywords");
    Iptcdatum datum2(key2, nullptr);
    datum2 = std::string("keyword");

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum2.toString(), "First caption");
}

// Test assignment from string
TEST_F(IptcdatumTest_670, AssignStringValue_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Hello World");
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test assignment from uint16_t
TEST_F(IptcdatumTest_670, AssignUint16Value_670) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    uint16_t val = 5;
    datum = val;
    EXPECT_EQ(datum.toString(), "5");
}

// Test setValue with string
TEST_F(IptcdatumTest_670, SetValueString_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("initial");
    int result = datum.setValue("updated value");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "updated value");
}

// Test setValue with Value pointer
TEST_F(IptcdatumTest_670, SetValueWithValuePointer_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    auto val = Value::create(string);
    val->read("test value");
    datum.setValue(val.get());
    
    EXPECT_EQ(datum.toString(), "test value");
}

// Test assignment from Value object
TEST_F(IptcdatumTest_670, AssignFromValueObject_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    StringValue val("from value");
    datum = val;
    
    EXPECT_EQ(datum.toString(), "from value");
}

// Test count() and size() after setting value
TEST_F(IptcdatumTest_670, CountAndSizeAfterSetValue_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Hello");
    
    EXPECT_GT(datum.count(), static_cast<size_t>(0));
    EXPECT_GT(datum.size(), static_cast<size_t>(0));
}

// Test typeId and typeName after setting string value
TEST_F(IptcdatumTest_670, TypeInfoAfterStringAssignment_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("test");
    
    EXPECT_NE(datum.typeId(), invalidTypeId);
    EXPECT_NE(datum.typeName(), nullptr);
}

// Test getValue() returns a valid value
TEST_F(IptcdatumTest_670, GetValueReturnsValidPtr_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("test value");
    
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "test value");
}

// Test value() reference
TEST_F(IptcdatumTest_670, ValueReferenceIsValid_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("reference test");
    
    const Value& val = datum.value();
    EXPECT_EQ(val.toString(), "reference test");
}

// Test write to ostream
TEST_F(IptcdatumTest_670, WriteToStream_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("stream test");
    
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test with Envelope record
TEST_F(IptcdatumTest_670, EnvelopeRecord_670) {
    IptcKey key("Iptc.Envelope.CharacterSet");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.recordName(), "Envelope");
    EXPECT_EQ(datum.record(), 1);
}

// Test construction with tag and record numbers
TEST_F(IptcdatumTest_670, ConstructWithTagAndRecordNumbers_670) {
    IptcKey key(120, 2); // Caption in Application2
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), 120);
    EXPECT_EQ(datum.record(), 2);
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
}

// Test tagLabel returns non-empty for known tags
TEST_F(IptcdatumTest_670, TagLabelForKnownTag_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test tagDesc for known tag
TEST_F(IptcdatumTest_670, TagDescForKnownTag_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // tagDesc may or may not be empty depending on tag, just ensure no crash
    std::string desc = datum.tagDesc();
    // Just verify it doesn't throw
    SUCCEED();
}

// Test copy to buffer
TEST_F(IptcdatumTest_670, CopyToBuffer_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("buf test");
    
    byte buf[256] = {};
    size_t copied = datum.copy(buf, bigEndian);
    EXPECT_GT(copied, static_cast<size_t>(0));
}

// Test toString with index
TEST_F(IptcdatumTest_670, ToStringWithIndex_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("indexed");
    
    std::string str = datum.toString(0);
    EXPECT_EQ(str, "indexed");
}

// Test toInt64 conversion
TEST_F(IptcdatumTest_670, ToInt64Conversion_670) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    datum = std::string("5");
    
    int64_t val = datum.toInt64(0);
    EXPECT_EQ(val, 5);
}

// Test toFloat conversion
TEST_F(IptcdatumTest_670, ToFloatConversion_670) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    datum = std::string("3");
    
    float val = datum.toFloat(0);
    EXPECT_FLOAT_EQ(val, 3.0f);
}

// Test Keywords tag (Application2 record, tag 25)
TEST_F(IptcdatumTest_670, KeywordsTag_670) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);
    datum = std::string("nature");
    
    EXPECT_EQ(datum.tagName(), "Keywords");
    EXPECT_EQ(datum.toString(), "nature");
    EXPECT_EQ(datum.tag(), 25);
}

// Test self-assignment
TEST_F(IptcdatumTest_670, SelfAssignment_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("self assign");
    
    datum = datum;
    EXPECT_EQ(datum.toString(), "self assign");
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test construction with Value pointer
TEST_F(IptcdatumTest_670, ConstructWithValuePointer_670) {
    IptcKey key("Iptc.Application2.Caption");
    auto val = Value::create(string);
    val->read("constructed value");
    
    Iptcdatum datum(key, val.get());
    EXPECT_EQ(datum.toString(), "constructed value");
}

// Test empty string value
TEST_F(IptcdatumTest_670, EmptyStringValue_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("");
    
    EXPECT_EQ(datum.toString(), "");
}

// Test typeSize for string type
TEST_F(IptcdatumTest_670, TypeSizeForStringType_670) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("test");
    
    // typeSize should return a valid value
    size_t ts = datum.typeSize();
    EXPECT_GE(ts, static_cast<size_t>(1));
}
