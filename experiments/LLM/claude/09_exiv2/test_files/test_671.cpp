#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

class IptcdatumTest_671 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with a known IPTC key string and null value
TEST_F(IptcdatumTest_671, ConstructWithKeyStringNullValue_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test that familyName returns "Iptc"
TEST_F(IptcdatumTest_671, FamilyNameReturnsIptc_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test groupName returns the record name
TEST_F(IptcdatumTest_671, GroupNameReturnsRecordName_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test tagName returns the correct tag name
TEST_F(IptcdatumTest_671, TagNameReturnsCorrectName_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test tagLabel returns a non-empty label for a known tag
TEST_F(IptcdatumTest_671, TagLabelReturnsNonEmptyForKnownTag_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    // Known tag should have a label
    EXPECT_FALSE(label.empty());
}

// Test recordName
TEST_F(IptcdatumTest_671, RecordNameReturnsCorrectValue_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.recordName(), "Application2");
}

// Test tag returns correct tag number
TEST_F(IptcdatumTest_671, TagReturnsCorrectNumber_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Caption is tag 120 in Application Record 2
    EXPECT_EQ(datum.tag(), 120);
}

// Test record returns correct record number
TEST_F(IptcdatumTest_671, RecordReturnsCorrectNumber_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Application2 is record 2
    EXPECT_EQ(datum.record(), 2);
}

// Test copy constructor
TEST_F(IptcdatumTest_671, CopyConstructorPreservesData_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test caption");

    Iptcdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.toString(), "Test caption");
}

// Test assignment from string
TEST_F(IptcdatumTest_671, AssignFromString_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Hello World");
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test assignment from uint16_t
TEST_F(IptcdatumTest_671, AssignFromUint16_671) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    uint16_t val = 5;
    datum = val;
    EXPECT_EQ(datum.toString(), "5");
}

// Test copy assignment operator
TEST_F(IptcdatumTest_671, CopyAssignmentOperator_671) {
    IptcKey key1("Iptc.Application2.Caption");
    Iptcdatum datum1(key1, nullptr);
    datum1 = std::string("First");

    IptcKey key2("Iptc.Application2.Headline");
    Iptcdatum datum2(key2, nullptr);
    datum2 = std::string("Second");

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum2.toString(), "First");
}

// Test setValue with string
TEST_F(IptcdatumTest_671, SetValueFromString_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    int result = datum.setValue("Test value");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Test value");
}

// Test setValue with Value pointer
TEST_F(IptcdatumTest_671, SetValueFromValuePtr_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    StringValue val("Some caption");
    datum.setValue(&val);
    EXPECT_EQ(datum.toString(), "Some caption");
}

// Test assignment from Value reference
TEST_F(IptcdatumTest_671, AssignFromValueRef_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    StringValue val("Assigned value");
    datum = val;
    EXPECT_EQ(datum.toString(), "Assigned value");
}

// Test count and size with no value set
TEST_F(IptcdatumTest_671, CountAndSizeWithNoValue_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
    EXPECT_EQ(datum.size(), 0u);
}

// Test count and size after setting a value
TEST_F(IptcdatumTest_671, CountAndSizeAfterSetValue_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Hello");
    EXPECT_GT(datum.count(), 0u);
    EXPECT_GT(datum.size(), 0u);
}

// Test write to ostream
TEST_F(IptcdatumTest_671, WriteToOstream_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Output test");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test tagDesc returns a description for known tag
TEST_F(IptcdatumTest_671, TagDescForKnownTag_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    std::string desc = datum.tagDesc();
    // Known tags typically have a description
    EXPECT_FALSE(desc.empty());
}

// Test construction with tag and record numbers
TEST_F(IptcdatumTest_671, ConstructWithTagAndRecordNumbers_671) {
    IptcKey key(120, 2); // Caption in Application2
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), 120);
    EXPECT_EQ(datum.record(), 2);
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test typeId when no value is set
TEST_F(IptcdatumTest_671, TypeIdWithNoValue_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // When no value is set, typeId behavior is implementation-defined
    // but it should not crash
    TypeId tid = datum.typeId();
    (void)tid; // Just ensure it doesn't crash
}

// Test typeName when value is set
TEST_F(IptcdatumTest_671, TypeNameWithStringValue_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("test");
    const char* tn = datum.typeName();
    EXPECT_NE(tn, nullptr);
}

// Test getValue returns a valid unique_ptr after setting value
TEST_F(IptcdatumTest_671, GetValueReturnsValidPtr_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("getValue test");
    auto val = datum.getValue();
    EXPECT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "getValue test");
}

// Test value() reference after setting value
TEST_F(IptcdatumTest_671, ValueReferenceAfterSet_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("ref test");
    const Value& v = datum.value();
    EXPECT_EQ(v.toString(), "ref test");
}

// Test different IPTC records - Envelope record
TEST_F(IptcdatumTest_671, EnvelopeRecordKey_671) {
    IptcKey key("Iptc.Envelope.CharacterSet");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
    EXPECT_EQ(datum.groupName(), "Envelope");
    EXPECT_EQ(datum.record(), 1);
}

// Test toString with index for single value
TEST_F(IptcdatumTest_671, ToStringWithIndex_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("indexed");
    std::string s = datum.toString(0);
    EXPECT_EQ(s, "indexed");
}

// Test construction with a Value pointer
TEST_F(IptcdatumTest_671, ConstructWithValuePtr_671) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("initial value");
    Iptcdatum datum(key, &val);
    EXPECT_EQ(datum.toString(), "initial value");
    EXPECT_GT(datum.count(), 0u);
}

// Test copy to buffer
TEST_F(IptcdatumTest_671, CopyToBuffer_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("copy test");
    size_t sz = datum.size();
    ASSERT_GT(sz, 0u);
    std::vector<byte> buf(sz);
    size_t copied = datum.copy(buf.data(), bigEndian);
    EXPECT_EQ(copied, sz);
}

// Test Headline tag
TEST_F(IptcdatumTest_671, HeadlineTag_671) {
    IptcKey key("Iptc.Application2.Headline");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Breaking News");
    EXPECT_EQ(datum.tagName(), "Headline");
    EXPECT_EQ(datum.toString(), "Breaking News");
}

// Test Keywords tag
TEST_F(IptcdatumTest_671, KeywordsTag_671) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);
    datum = std::string("nature");
    EXPECT_EQ(datum.tagName(), "Keywords");
    EXPECT_EQ(datum.toString(), "nature");
}

// Test self-assignment
TEST_F(IptcdatumTest_671, SelfAssignment_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("self assign");
    datum = datum;
    EXPECT_EQ(datum.toString(), "self assign");
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test setting value to empty string
TEST_F(IptcdatumTest_671, SetEmptyString_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("");
    EXPECT_EQ(datum.toString(), "");
}

// Test overwriting value
TEST_F(IptcdatumTest_671, OverwriteValue_671) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("first");
    EXPECT_EQ(datum.toString(), "first");
    datum = std::string("second");
    EXPECT_EQ(datum.toString(), "second");
}
