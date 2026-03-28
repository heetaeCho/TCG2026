#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <memory>
#include <string>
#include <sstream>

using namespace Exiv2;

class IptcdatumTest_690 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with a key and null value
TEST_F(IptcdatumTest_690, ConstructWithKeyAndNullValue_690) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ("Iptc.Application2.Caption", datum.key());
    EXPECT_EQ("Iptc", std::string(datum.familyName()));
    EXPECT_EQ("Application2", datum.groupName());
    EXPECT_EQ("Caption", datum.tagName());
}

// Test construction with a key and a valid value
TEST_F(IptcdatumTest_690, ConstructWithKeyAndValue_690) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Hello World");
    Iptcdatum datum(key, &val);

    EXPECT_EQ("Iptc.Application2.Caption", datum.key());
    EXPECT_EQ("Hello World", datum.toString());
    EXPECT_EQ(1u, datum.count());
}

// Test copy constructor
TEST_F(IptcdatumTest_690, CopyConstructor_690) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Test Copy");
    Iptcdatum original(key, &val);
    Iptcdatum copy(original);

    EXPECT_EQ(original.key(), copy.key());
    EXPECT_EQ(original.toString(), copy.toString());
    EXPECT_EQ(original.tag(), copy.tag());
    EXPECT_EQ(original.record(), copy.record());
}

// Test assignment operator from another Iptcdatum
TEST_F(IptcdatumTest_690, AssignmentOperatorIptcdatum_690) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue val1("First");
    Iptcdatum datum1(key1, &val1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue val2("Second");
    Iptcdatum datum2(key2, &val2);

    datum1 = datum2;

    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.toString(), datum1.toString());
}

// Test assignment operator from uint16_t
TEST_F(IptcdatumTest_690, AssignmentOperatorUint16_690) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);

    uint16_t val = 5;
    datum = val;

    EXPECT_EQ("5", datum.toString());
}

// Test assignment operator from string
TEST_F(IptcdatumTest_690, AssignmentOperatorString_690) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    std::string val = "Assigned String";
    datum = val;

    EXPECT_EQ("Assigned String", datum.toString());
}

// Test assignment operator from Value
TEST_F(IptcdatumTest_690, AssignmentOperatorValue_690) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    StringValue val("Value Assignment");
    datum = val;

    EXPECT_EQ("Value Assignment", datum.toString());
}

// Test setValue with a valid Value pointer
TEST_F(IptcdatumTest_690, SetValueWithValidPointer_690) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    StringValue val("Set via pointer");
    datum.setValue(&val);

    EXPECT_EQ("Set via pointer", datum.toString());
    EXPECT_GT(datum.count(), 0u);
}

// Test setValue with nullptr resets value
TEST_F(IptcdatumTest_690, SetValueWithNullptr_690) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Initial");
    Iptcdatum datum(key, &val);

    EXPECT_EQ("Initial", datum.toString());

    datum.setValue(nullptr);

    // After setting nullptr, getValue should return nullptr or accessing value should throw
    auto ptr = datum.getValue();
    EXPECT_EQ(nullptr, ptr.get());
}

// Test setValue with string
TEST_F(IptcdatumTest_690, SetValueWithString_690) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Initial");
    Iptcdatum datum(key, &val);

    int result = datum.setValue("Updated String");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Updated String", datum.toString());
}

// Test key-related accessors
TEST_F(IptcdatumTest_690, KeyAccessors_690) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ("Iptc.Application2.Caption", datum.key());
    EXPECT_EQ("Iptc", std::string(datum.familyName()));
    EXPECT_EQ("Application2", datum.groupName());
    EXPECT_EQ("Application2", datum.recordName());
    EXPECT_EQ("Caption", datum.tagName());
}

// Test record number
TEST_F(IptcdatumTest_690, RecordNumber_690) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    uint16_t record = datum.record();
    EXPECT_EQ(2u, record);
}

// Test tag number for Caption
TEST_F(IptcdatumTest_690, TagNumber_690) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    uint16_t tag = datum.tag();
    // Caption/Abstract tag is 120 in IPTC Application2
    EXPECT_EQ(120u, tag);
}

// Test typeId when value is set
TEST_F(IptcdatumTest_690, TypeIdWithValue_690) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Test");
    Iptcdatum datum(key, &val);

    EXPECT_EQ(string, datum.typeId());
}

// Test typeName when value is set
TEST_F(IptcdatumTest_690, TypeNameWithValue_690) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Test");
    Iptcdatum datum(key, &val);

    EXPECT_NE(nullptr, datum.typeName());
}

// Test size and count with a string value
TEST_F(IptcdatumTest_690, SizeAndCountWithStringValue_690) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Hello");
    Iptcdatum datum(key, &val);

    EXPECT_GT(datum.size(), 0u);
    EXPECT_GT(datum.count(), 0u);
}

// Test toString with index
TEST_F(IptcdatumTest_690, ToStringWithIndex_690) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Indexed");
    Iptcdatum datum(key, &val);

    std::string result = datum.toString(0);
    EXPECT_EQ("Indexed", result);
}

// Test getValue returns a clone
TEST_F(IptcdatumTest_690, GetValueReturnsClone_690) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Clone Test");
    Iptcdatum datum(key, &val);

    auto cloned = datum.getValue();
    ASSERT_NE(nullptr, cloned.get());
    EXPECT_EQ("Clone Test", cloned->toString());
}

// Test value() reference access
TEST_F(IptcdatumTest_690, ValueReferenceAccess_690) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Reference Test");
    Iptcdatum datum(key, &val);

    const Value& ref = datum.value();
    EXPECT_EQ("Reference Test", ref.toString());
}

// Test value() throws when no value is set
TEST_F(IptcdatumTest_690, ValueReferenceThrowsWhenNoValue_690) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_THROW(datum.value(), Error);
}

// Test write to ostream
TEST_F(IptcdatumTest_690, WriteToOstream_690) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Stream Test");
    Iptcdatum datum(key, &val);

    std::ostringstream os;
    datum.write(os, nullptr);

    EXPECT_FALSE(os.str().empty());
}

// Test copy to buffer
TEST_F(IptcdatumTest_690, CopyToBuffer_690) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Buffer");
    Iptcdatum datum(key, &val);

    size_t sz = datum.size();
    std::vector<byte> buf(sz + 10, 0);
    size_t copied = datum.copy(buf.data(), bigEndian);

    EXPECT_GT(copied, 0u);
}

// Test with different IPTC record - Envelope
TEST_F(IptcdatumTest_690, EnvelopeRecordKey_690) {
    IptcKey key("Iptc.Envelope.CharacterSet");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ("Iptc.Envelope.CharacterSet", datum.key());
    EXPECT_EQ("Envelope", datum.recordName());
    EXPECT_EQ(1u, datum.record());
}

// Test tagLabel returns non-empty for known tags
TEST_F(IptcdatumTest_690, TagLabelNonEmpty_690) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test Keywords tag
TEST_F(IptcdatumTest_690, KeywordsTag_690) {
    IptcKey key("Iptc.Application2.Keywords");
    StringValue val("keyword1");
    Iptcdatum datum(key, &val);

    EXPECT_EQ("Keywords", datum.tagName());
    EXPECT_EQ("keyword1", datum.toString());
}

// Test overwriting value with setValue pointer
TEST_F(IptcdatumTest_690, OverwriteValueWithSetValue_690) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val1("First");
    Iptcdatum datum(key, &val1);

    EXPECT_EQ("First", datum.toString());

    StringValue val2("Second");
    datum.setValue(&val2);

    EXPECT_EQ("Second", datum.toString());
}

// Test toInt64 with numeric string value
TEST_F(IptcdatumTest_690, ToInt64WithUrgency_690) {
    IptcKey key("Iptc.Application2.Urgency");
    StringValue val("5");
    Iptcdatum datum(key, &val);

    // StringValue may not convert to int64 well, but we test the interface
    // Using uint16_t assignment instead for numeric
    IptcKey key2("Iptc.Application2.Urgency");
    Iptcdatum datum2(key2, nullptr);
    datum2 = static_cast<uint16_t>(7);

    EXPECT_EQ(7, datum2.toInt64(0));
}

// Test self-assignment
TEST_F(IptcdatumTest_690, SelfAssignment_690) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("SelfTest");
    Iptcdatum datum(key, &val);

    datum = datum;

    EXPECT_EQ("Iptc.Application2.Caption", datum.key());
    EXPECT_EQ("SelfTest", datum.toString());
}

// Test empty string value
TEST_F(IptcdatumTest_690, EmptyStringValue_690) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("");
    Iptcdatum datum(key, &val);

    EXPECT_EQ("", datum.toString());
    EXPECT_EQ(0u, datum.size());
}
