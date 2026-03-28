#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <sstream>

using namespace Exiv2;

class IptcdatumTest_667 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that record() returns the correct record number from the key
TEST_F(IptcdatumTest_667, RecordReturnsCorrectValue_667) {
    IptcKey key(0x0005, 0x0002);  // tag=5, record=2
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.record(), key.record());
}

// Test that record() returns envelope record
TEST_F(IptcdatumTest_667, RecordReturnsEnvelopeRecord_667) {
    // Record 1 is envelope record
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.record(), 1);
}

// Test that record() returns application2 record
TEST_F(IptcdatumTest_667, RecordReturnsApplication2Record_667) {
    // Record 2 is application record 2
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.record(), 2);
}

// Test key() returns correct key string
TEST_F(IptcdatumTest_667, KeyReturnsCorrectString_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Iptc.Application2.ObjectName");
}

// Test familyName() returns "Iptc"
TEST_F(IptcdatumTest_667, FamilyNameReturnsIptc_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test groupName() returns correct group
TEST_F(IptcdatumTest_667, GroupNameReturnsCorrectGroup_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test tagName() returns correct tag name
TEST_F(IptcdatumTest_667, TagNameReturnsCorrectName_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "ObjectName");
}

// Test recordName() returns correct record name
TEST_F(IptcdatumTest_667, RecordNameReturnsCorrectName_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.recordName(), "Application2");
}

// Test copy constructor
TEST_F(IptcdatumTest_667, CopyConstructorWorks_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    Iptcdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.record(), datum.record());
    EXPECT_EQ(copy.tag(), datum.tag());
}

// Test copy assignment operator
TEST_F(IptcdatumTest_667, CopyAssignmentWorks_667) {
    IptcKey key1("Iptc.Application2.ObjectName");
    Iptcdatum datum1(key1, nullptr);

    IptcKey key2("Iptc.Envelope.ModelVersion");
    Iptcdatum datum2(key2, nullptr);

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.record(), datum1.record());
}

// Test setValue with string and then toString
TEST_F(IptcdatumTest_667, SetValueStringAndToString_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Hello World");
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test assignment from string
TEST_F(IptcdatumTest_667, AssignFromString_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test Value");
    EXPECT_EQ(datum.toString(), "Test Value");
}

// Test count after setting value
TEST_F(IptcdatumTest_667, CountAfterSetValue_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum.setValue("test");
    EXPECT_GT(datum.count(), static_cast<size_t>(0));
}

// Test size after setting value
TEST_F(IptcdatumTest_667, SizeAfterSetValue_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum.setValue("test");
    EXPECT_GT(datum.size(), static_cast<size_t>(0));
}

// Test that tag() returns the correct tag number
TEST_F(IptcdatumTest_667, TagReturnsCorrectValue_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), key.tag());
}

// Test creating Iptcdatum with nullptr value
TEST_F(IptcdatumTest_667, ConstructWithNullptrValue_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    // Should be constructable without crashing
    EXPECT_EQ(datum.key(), "Iptc.Application2.ObjectName");
}

// Test creating Iptcdatum with an actual Value
TEST_F(IptcdatumTest_667, ConstructWithValue_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    StringValue val("InitialValue");
    Iptcdatum datum(key, &val);
    EXPECT_EQ(datum.toString(), "InitialValue");
}

// Test setValue with Value pointer
TEST_F(IptcdatumTest_667, SetValueWithValuePointer_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    StringValue val("FromPointer");
    datum.setValue(&val);
    EXPECT_EQ(datum.toString(), "FromPointer");
}

// Test assignment from Value
TEST_F(IptcdatumTest_667, AssignFromValue_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    StringValue val("FromValue");
    datum = val;
    EXPECT_EQ(datum.toString(), "FromValue");
}

// Test getValue returns non-null after setting value
TEST_F(IptcdatumTest_667, GetValueReturnsNonNull_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum.setValue("some value");
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "some value");
}

// Test write to ostream
TEST_F(IptcdatumTest_667, WriteToOstream_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum.setValue("output test");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test typeId after setting a string value
TEST_F(IptcdatumTest_667, TypeIdAfterStringValue_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum.setValue("test");
    // After setting a string, typeId should be a valid type
    TypeId tid = datum.typeId();
    // The type should be string-related
    EXPECT_NE(tid, invalidTypeId);
}

// Test typeName after setting a string value
TEST_F(IptcdatumTest_667, TypeNameAfterStringValue_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum.setValue("test");
    const char* tn = datum.typeName();
    EXPECT_NE(tn, nullptr);
}

// Test toString(n) for n=0
TEST_F(IptcdatumTest_667, ToStringWithIndex_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum.setValue("indexed");
    std::string result = datum.toString(0);
    EXPECT_EQ(result, "indexed");
}

// Test with Envelope record entries
TEST_F(IptcdatumTest_667, EnvelopeRecordEntries_667) {
    IptcKey key("Iptc.Envelope.CharacterSet");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.record(), 1);
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
}

// Test assignment from uint16_t
TEST_F(IptcdatumTest_667, AssignFromUint16_667) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);
    uint16_t val = 42;
    datum = val;
    EXPECT_EQ(datum.toString(), "42");
}

// Test copy to buffer
TEST_F(IptcdatumTest_667, CopyToBuffer_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    StringValue val("buftest");
    Iptcdatum datum(key, &val);
    
    std::vector<byte> buf(256, 0);
    size_t copied = datum.copy(buf.data(), bigEndian);
    EXPECT_GT(copied, static_cast<size_t>(0));
}

// Test toInt64
TEST_F(IptcdatumTest_667, ToInt64AfterUint16Assignment_667) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);
    uint16_t val = 100;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 100);
}

// Test toFloat
TEST_F(IptcdatumTest_667, ToFloatAfterUint16Assignment_667) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);
    uint16_t val = 50;
    datum = val;
    EXPECT_FLOAT_EQ(datum.toFloat(0), 50.0f);
}

// Test toRational
TEST_F(IptcdatumTest_667, ToRationalAfterUint16Assignment_667) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);
    uint16_t val = 25;
    datum = val;
    Rational r = datum.toRational(0);
    // The rational should represent value 25
    EXPECT_NE(r.second, 0);
    if (r.second != 0) {
        EXPECT_EQ(static_cast<int64_t>(r.first) / static_cast<int64_t>(r.second), 25);
    }
}

// Test tagLabel returns non-empty for known tags
TEST_F(IptcdatumTest_667, TagLabelNonEmpty_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test creating datum with tag and record numbers
TEST_F(IptcdatumTest_667, ConstructWithTagAndRecord_667) {
    IptcKey key(5, 2);  // tag=5, record=2 (Application2)
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.record(), 2);
    EXPECT_EQ(datum.tag(), 5);
}

// Test self-assignment
TEST_F(IptcdatumTest_667, SelfAssignment_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum.setValue("self");
    datum = datum;
    EXPECT_EQ(datum.toString(), "self");
}

// Test typeSize after setting a value
TEST_F(IptcdatumTest_667, TypeSizeAfterSetValue_667) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum.setValue("test");
    size_t ts = datum.typeSize();
    EXPECT_GT(ts, static_cast<size_t>(0));
}
