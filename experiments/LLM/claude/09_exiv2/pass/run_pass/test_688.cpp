#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <exiv2/error.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

class IptcdatumTest_688 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with a valid IptcKey and null value
TEST_F(IptcdatumTest_688, ConstructWithKeyAndNullValue_688) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ("Iptc.Application2.Caption", datum.key());
    EXPECT_EQ("Iptc", std::string(datum.familyName()));
    EXPECT_EQ("Application2", datum.groupName());
    EXPECT_EQ("Caption", datum.tagName());
}

// Test construction with a valid IptcKey and a value
TEST_F(IptcdatumTest_688, ConstructWithKeyAndValue_688) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Test caption");
    Iptcdatum datum(key, &val);
    EXPECT_EQ("Test caption", datum.toString());
    EXPECT_EQ(1u, datum.count());
}

// Test copy constructor
TEST_F(IptcdatumTest_688, CopyConstructor_688) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Copy test");
    Iptcdatum original(key, &val);
    Iptcdatum copy(original);
    EXPECT_EQ(original.key(), copy.key());
    EXPECT_EQ(original.toString(), copy.toString());
}

// Test copy assignment operator
TEST_F(IptcdatumTest_688, CopyAssignmentOperator_688) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue val1("First");
    Iptcdatum datum1(key1, &val1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue val2("Second");
    Iptcdatum datum2(key2, &val2);

    datum2 = datum1;
    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
}

// Test assignment from string
TEST_F(IptcdatumTest_688, AssignFromString_688) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Hello IPTC");
    EXPECT_EQ("Hello IPTC", datum.toString());
}

// Test assignment from uint16_t
TEST_F(IptcdatumTest_688, AssignFromUint16_688) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);
    uint16_t val = 42;
    datum = val;
    EXPECT_EQ("42", datum.toString());
}

// Test assignment from Value object
TEST_F(IptcdatumTest_688, AssignFromValue_688) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    StringValue val("Value assignment");
    datum = val;
    EXPECT_EQ("Value assignment", datum.toString());
}

// Test setValue with string
TEST_F(IptcdatumTest_688, SetValueFromString_688) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue initial("initial");
    Iptcdatum datum(key, &initial);
    int result = datum.setValue("new value");
    EXPECT_EQ(0, result);
    EXPECT_EQ("new value", datum.toString());
}

// Test setValue with Value pointer
TEST_F(IptcdatumTest_688, SetValueFromPointer_688) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    StringValue val("pointer value");
    datum.setValue(&val);
    EXPECT_EQ("pointer value", datum.toString());
}

// Test setValue with null pointer
TEST_F(IptcdatumTest_688, SetValueWithNullPointer_688) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("something");
    Iptcdatum datum(key, &val);
    datum.setValue(nullptr);
    // After setting null, getValue should return null or value() should throw
    EXPECT_EQ(nullptr, datum.getValue().get());
}

// Test key() returns correct key string
TEST_F(IptcdatumTest_688, KeyReturnsCorrectString_688) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ("Iptc.Application2.Keywords", datum.key());
}

// Test familyName()
TEST_F(IptcdatumTest_688, FamilyNameReturnsIptc_688) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_STREQ("Iptc", datum.familyName());
}

// Test groupName()
TEST_F(IptcdatumTest_688, GroupNameReturnsCorrectRecord_688) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ("Application2", datum.groupName());
}

// Test recordName()
TEST_F(IptcdatumTest_688, RecordNameReturnsCorrectRecord_688) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ("Application2", datum.recordName());
}

// Test tagName()
TEST_F(IptcdatumTest_688, TagNameReturnsCorrectTag_688) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ("Caption", datum.tagName());
}

// Test tag() returns correct tag number
TEST_F(IptcdatumTest_688, TagReturnsCorrectNumber_688) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Caption tag is 120
    EXPECT_EQ(120u, datum.tag());
}

// Test record() returns correct record number
TEST_F(IptcdatumTest_688, RecordReturnsCorrectNumber_688) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Application2 record is 2
    EXPECT_EQ(2u, datum.record());
}

// Test typeId with string value
TEST_F(IptcdatumTest_688, TypeIdForStringValue_688) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("test");
    Iptcdatum datum(key, &val);
    EXPECT_EQ(string, datum.typeId());
}

// Test typeName with string value
TEST_F(IptcdatumTest_688, TypeNameForStringValue_688) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("test");
    Iptcdatum datum(key, &val);
    EXPECT_STREQ("String", datum.typeName());
}

// Test size() with string value
TEST_F(IptcdatumTest_688, SizeReturnsValueSize_688) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Hello");
    Iptcdatum datum(key, &val);
    EXPECT_EQ(5u, datum.size());
}

// Test count() with string value
TEST_F(IptcdatumTest_688, CountReturnsValueCount_688) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Hello");
    Iptcdatum datum(key, &val);
    EXPECT_EQ(1u, datum.count());
}

// Test toString with index
TEST_F(IptcdatumTest_688, ToStringWithIndex_688) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("indexed");
    Iptcdatum datum(key, &val);
    EXPECT_EQ("indexed", datum.toString(0));
}

// Test write to ostream
TEST_F(IptcdatumTest_688, WriteToOstream_688) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("stream test");
    Iptcdatum datum(key, &val);
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test getValue() returns a valid unique_ptr
TEST_F(IptcdatumTest_688, GetValueReturnsValidPtr_688) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("get value");
    Iptcdatum datum(key, &val);
    auto retrieved = datum.getValue();
    EXPECT_NE(nullptr, retrieved.get());
    EXPECT_EQ("get value", retrieved->toString());
}

// Test value() returns reference
TEST_F(IptcdatumTest_688, ValueReturnsReference_688) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("ref value");
    Iptcdatum datum(key, &val);
    const Value& ref = datum.value();
    EXPECT_EQ("ref value", ref.toString());
}

// Test value() throws when no value set
TEST_F(IptcdatumTest_688, ValueThrowsWhenNoValue_688) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_THROW(datum.value(), Error);
}

// Test copy to buffer
TEST_F(IptcdatumTest_688, CopyToBuffer_688) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("buf");
    Iptcdatum datum(key, &val);
    byte buf[64] = {};
    size_t copied = datum.copy(buf, bigEndian);
    EXPECT_GT(copied, 0u);
}

// Test tagLabel
TEST_F(IptcdatumTest_688, TagLabelReturnsNonEmpty_688) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test empty string assignment
TEST_F(IptcdatumTest_688, AssignEmptyString_688) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("");
    EXPECT_EQ("", datum.toString());
}

// Test Envelope record
TEST_F(IptcdatumTest_688, EnvelopeRecord_688) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ("Envelope", datum.recordName());
    EXPECT_EQ(1u, datum.record());
}

// Test self-assignment
TEST_F(IptcdatumTest_688, SelfAssignment_688) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("self");
    Iptcdatum datum(key, &val);
    datum = datum;
    EXPECT_EQ("self", datum.toString());
    EXPECT_EQ("Iptc.Application2.Caption", datum.key());
}

// Test toInt64
TEST_F(IptcdatumTest_688, ToInt64_688) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);
    uint16_t val = 100;
    datum = val;
    EXPECT_EQ(100, datum.toInt64(0));
}

// Test toFloat
TEST_F(IptcdatumTest_688, ToFloat_688) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);
    uint16_t val = 50;
    datum = val;
    EXPECT_FLOAT_EQ(50.0f, datum.toFloat(0));
}

// Test multiple setValue calls
TEST_F(IptcdatumTest_688, MultipleSetValueCalls_688) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val1("first");
    Iptcdatum datum(key, &val1);
    EXPECT_EQ("first", datum.toString());

    StringValue val2("second");
    datum.setValue(&val2);
    EXPECT_EQ("second", datum.toString());

    datum.setValue("third");
    EXPECT_EQ("third", datum.toString());
}

// Test Keywords tag
TEST_F(IptcdatumTest_688, KeywordsTag_688) {
    IptcKey key("Iptc.Application2.Keywords");
    StringValue val("keyword1");
    Iptcdatum datum(key, &val);
    EXPECT_EQ("Iptc.Application2.Keywords", datum.key());
    EXPECT_EQ("Keywords", datum.tagName());
    EXPECT_EQ("keyword1", datum.toString());
}

// Test typeSize
TEST_F(IptcdatumTest_688, TypeSizeForStringValue_688) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("test");
    Iptcdatum datum(key, &val);
    // String type size is 1
    EXPECT_EQ(1u, datum.typeSize());
}
