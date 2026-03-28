#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

class IptcdatumTest_687 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create an IptcKey for testing
    // Using a known IPTC key like "Iptc.Application2.Caption"
    IptcKey makeKey(const std::string& keyStr = "Iptc.Application2.Caption") {
        return IptcKey(keyStr);
    }
};

// Test: Construction with key and null value
TEST_F(IptcdatumTest_687, ConstructWithKeyAndNullValue_687) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ("Iptc.Application2.Caption", datum.key());
    EXPECT_EQ("Iptc", std::string(datum.familyName()));
    EXPECT_EQ("Application2", datum.groupName());
    EXPECT_EQ("Caption", datum.tagName());
}

// Test: Construction with key and a value
TEST_F(IptcdatumTest_687, ConstructWithKeyAndValue_687) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Hello World");
    Iptcdatum datum(key, &val);

    EXPECT_EQ("Iptc.Application2.Caption", datum.key());
    EXPECT_EQ("Hello World", datum.toString());
}

// Test: Copy constructor
TEST_F(IptcdatumTest_687, CopyConstructor_687) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Test Copy");
    Iptcdatum original(key, &val);
    Iptcdatum copy(original);

    EXPECT_EQ(original.key(), copy.key());
    EXPECT_EQ(original.toString(), copy.toString());
    EXPECT_EQ(original.tag(), copy.tag());
    EXPECT_EQ(original.record(), copy.record());
}

// Test: Assignment operator from another Iptcdatum
TEST_F(IptcdatumTest_687, AssignmentFromIptcdatum_687) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue val1("Value1");
    Iptcdatum datum1(key1, &val1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue val2("Value2");
    Iptcdatum datum2(key2, &val2);

    datum1 = datum2;
    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.toString(), datum1.toString());
}

// Test: Assignment operator with uint16_t value
TEST_F(IptcdatumTest_687, AssignUint16Value_687) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);

    uint16_t testVal = 42;
    datum = testVal;

    EXPECT_EQ(1u, datum.count());
    EXPECT_EQ(42, datum.toInt64(0));
    EXPECT_EQ("42", datum.toString());
}

// Test: Assignment operator with uint16_t zero value
TEST_F(IptcdatumTest_687, AssignUint16ZeroValue_687) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);

    uint16_t testVal = 0;
    datum = testVal;

    EXPECT_EQ(1u, datum.count());
    EXPECT_EQ(0, datum.toInt64(0));
}

// Test: Assignment operator with uint16_t max value
TEST_F(IptcdatumTest_687, AssignUint16MaxValue_687) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);

    uint16_t testVal = 65535;
    datum = testVal;

    EXPECT_EQ(1u, datum.count());
    EXPECT_EQ(65535, datum.toInt64(0));
}

// Test: Assignment operator with string value
TEST_F(IptcdatumTest_687, AssignStringValue_687) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    std::string testStr = "Hello IPTC";
    datum = testStr;

    EXPECT_EQ("Hello IPTC", datum.toString());
}

// Test: Assignment operator with empty string value
TEST_F(IptcdatumTest_687, AssignEmptyStringValue_687) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    std::string testStr;
    datum = testStr;

    EXPECT_EQ("", datum.toString());
}

// Test: Assignment operator with Value object
TEST_F(IptcdatumTest_687, AssignValueObject_687) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    StringValue val("Assigned via Value");
    datum = val;

    EXPECT_EQ("Assigned via Value", datum.toString());
}

// Test: setValue with Value pointer
TEST_F(IptcdatumTest_687, SetValueWithPointer_687) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    StringValue val("SetValue Pointer");
    datum.setValue(&val);

    EXPECT_EQ("SetValue Pointer", datum.toString());
}

// Test: setValue with nullptr
TEST_F(IptcdatumTest_687, SetValueWithNullptr_687) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Initial");
    Iptcdatum datum(key, &val);

    datum.setValue(nullptr);
    // After setting null value, count should be 0
    EXPECT_EQ(0u, datum.count());
}

// Test: setValue with string
TEST_F(IptcdatumTest_687, SetValueWithString_687) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Initial");
    Iptcdatum datum(key, &val);

    int result = datum.setValue("New String Value");
    EXPECT_EQ(0, result);
    EXPECT_EQ("New String Value", datum.toString());
}

// Test: key() method
TEST_F(IptcdatumTest_687, KeyMethod_687) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ("Iptc.Application2.Keywords", datum.key());
}

// Test: familyName() returns "Iptc"
TEST_F(IptcdatumTest_687, FamilyNameMethod_687) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_STREQ("Iptc", datum.familyName());
}

// Test: groupName() method
TEST_F(IptcdatumTest_687, GroupNameMethod_687) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ("Application2", datum.groupName());
}

// Test: tagName() method
TEST_F(IptcdatumTest_687, TagNameMethod_687) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ("Caption", datum.tagName());
}

// Test: recordName() method
TEST_F(IptcdatumTest_687, RecordNameMethod_687) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ("Application2", datum.recordName());
}

// Test: tag() method
TEST_F(IptcdatumTest_687, TagMethod_687) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    // Caption tag number is 120
    EXPECT_EQ(120u, datum.tag());
}

// Test: record() method
TEST_F(IptcdatumTest_687, RecordMethod_687) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    // Application2 record is 2
    EXPECT_EQ(2u, datum.record());
}

// Test: Envelope record
TEST_F(IptcdatumTest_687, EnvelopeRecord_687) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(1u, datum.record());
    EXPECT_EQ("Envelope", datum.recordName());
    EXPECT_EQ("Envelope", datum.groupName());
}

// Test: typeId after setting uint16_t
TEST_F(IptcdatumTest_687, TypeIdAfterUint16Assignment_687) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);

    uint16_t val = 100;
    datum = val;

    EXPECT_EQ(unsignedShort, datum.typeId());
}

// Test: typeId after setting string
TEST_F(IptcdatumTest_687, TypeIdAfterStringAssignment_687) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    StringValue val("test");
    datum = val;

    EXPECT_EQ(string, datum.typeId());
}

// Test: count() with no value
TEST_F(IptcdatumTest_687, CountWithNoValue_687) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(0u, datum.count());
}

// Test: size() with no value
TEST_F(IptcdatumTest_687, SizeWithNoValue_687) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(0u, datum.size());
}

// Test: count() with string value
TEST_F(IptcdatumTest_687, CountWithStringValue_687) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Hello");
    Iptcdatum datum(key, &val);

    EXPECT_EQ(1u, datum.count());
}

// Test: size() with string value
TEST_F(IptcdatumTest_687, SizeWithStringValue_687) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Hello");
    Iptcdatum datum(key, &val);

    EXPECT_EQ(5u, datum.size());
}

// Test: getValue() returns valid unique_ptr
TEST_F(IptcdatumTest_687, GetValueReturnsClone_687) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Cloneable");
    Iptcdatum datum(key, &val);

    auto cloned = datum.getValue();
    ASSERT_NE(nullptr, cloned);
    EXPECT_EQ("Cloneable", cloned->toString());
}

// Test: value() reference
TEST_F(IptcdatumTest_687, ValueReferenceMethod_687) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Reference");
    Iptcdatum datum(key, &val);

    const Value& ref = datum.value();
    EXPECT_EQ("Reference", ref.toString());
}

// Test: write to ostream
TEST_F(IptcdatumTest_687, WriteToOstream_687) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("StreamTest");
    Iptcdatum datum(key, &val);

    std::ostringstream oss;
    datum.write(oss, nullptr);
    EXPECT_FALSE(oss.str().empty());
}

// Test: copy to buffer
TEST_F(IptcdatumTest_687, CopyToBuffer_687) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);

    uint16_t val = 256;
    datum = val;

    byte buf[16] = {0};
    size_t copied = datum.copy(buf, bigEndian);
    EXPECT_GT(copied, 0u);
}

// Test: toString with index
TEST_F(IptcdatumTest_687, ToStringWithIndex_687) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);

    uint16_t val = 55;
    datum = val;

    EXPECT_EQ("55", datum.toString(0));
}

// Test: toInt64
TEST_F(IptcdatumTest_687, ToInt64_687) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);

    uint16_t val = 1234;
    datum = val;

    EXPECT_EQ(1234, datum.toInt64(0));
}

// Test: toFloat
TEST_F(IptcdatumTest_687, ToFloat_687) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);

    uint16_t val = 42;
    datum = val;

    EXPECT_FLOAT_EQ(42.0f, datum.toFloat(0));
}

// Test: toRational
TEST_F(IptcdatumTest_687, ToRational_687) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);

    uint16_t val = 10;
    datum = val;

    Rational r = datum.toRational(0);
    EXPECT_EQ(10, r.first);
    EXPECT_EQ(1, r.second);
}

// Test: tagLabel returns non-empty for known tag
TEST_F(IptcdatumTest_687, TagLabelMethod_687) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test: Reassignment overwrites value
TEST_F(IptcdatumTest_687, ReassignmentOverwritesValue_687) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);

    uint16_t val1 = 100;
    datum = val1;
    EXPECT_EQ(100, datum.toInt64(0));

    uint16_t val2 = 200;
    datum = val2;
    EXPECT_EQ(200, datum.toInt64(0));
    EXPECT_EQ(1u, datum.count());
}

// Test: Assign uint16 then string
TEST_F(IptcdatumTest_687, AssignUint16ThenString_687) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    uint16_t val = 999;
    datum = val;
    EXPECT_EQ(unsignedShort, datum.typeId());

    std::string strVal = "Overwritten";
    datum = strVal;
    EXPECT_EQ("Overwritten", datum.toString());
}

// Test: Self-assignment
TEST_F(IptcdatumTest_687, SelfAssignment_687) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("SelfTest");
    Iptcdatum datum(key, &val);

    datum = datum;
    EXPECT_EQ("Iptc.Application2.Caption", datum.key());
    EXPECT_EQ("SelfTest", datum.toString());
}

// Test: Keywords tag
TEST_F(IptcdatumTest_687, KeywordsTag_687) {
    IptcKey key("Iptc.Application2.Keywords");
    StringValue val("keyword1");
    Iptcdatum datum(key, &val);

    EXPECT_EQ("Keywords", datum.tagName());
    EXPECT_EQ(25u, datum.tag());
    EXPECT_EQ("keyword1", datum.toString());
}

// Test: typeName after uint16 assignment
TEST_F(IptcdatumTest_687, TypeNameAfterUint16_687) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);

    uint16_t val = 1;
    datum = val;

    const char* tn = datum.typeName();
    ASSERT_NE(nullptr, tn);
    EXPECT_STREQ("Short", tn);
}

// Test: typeSize after uint16 assignment
TEST_F(IptcdatumTest_687, TypeSizeAfterUint16_687) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);

    uint16_t val = 1;
    datum = val;

    EXPECT_EQ(2u, datum.typeSize());
}
