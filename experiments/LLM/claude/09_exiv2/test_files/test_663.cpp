#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

class IptcdatumTest_663 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Constructing an Iptcdatum with a valid key and no value
TEST_F(IptcdatumTest_663, ConstructWithKeyNoValue_663) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
    EXPECT_EQ(datum.groupName(), "Application2");
    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test: Constructing an Iptcdatum with a valid key and a string value
TEST_F(IptcdatumTest_663, ConstructWithKeyAndValue_663) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Hello World");
    Iptcdatum datum(key, &val);

    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum.toString(), "Hello World");
    EXPECT_EQ(datum.count(), 1u);
    EXPECT_GT(datum.size(), 0u);
}

// Test: Copy constructor
TEST_F(IptcdatumTest_663, CopyConstructor_663) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Test Copy");
    Iptcdatum original(key, &val);
    Iptcdatum copy(original);

    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.toString(), original.toString());
    EXPECT_EQ(copy.tag(), original.tag());
    EXPECT_EQ(copy.record(), original.record());
}

// Test: Assignment operator from another Iptcdatum
TEST_F(IptcdatumTest_663, AssignmentOperator_663) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue val1("First");
    Iptcdatum datum1(key1, &val1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue val2("Second");
    Iptcdatum datum2(key2, &val2);

    datum1 = datum2;
    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
}

// Test: Assignment operator from uint16_t
TEST_F(IptcdatumTest_663, AssignUint16Value_663) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);

    uint16_t val = 42;
    datum = val;

    EXPECT_EQ(datum.toString(), "42");
}

// Test: Assignment operator from string
TEST_F(IptcdatumTest_663, AssignStringValue_663) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    datum = std::string("New Caption");
    EXPECT_EQ(datum.toString(), "New Caption");
}

// Test: Assignment operator from Value
TEST_F(IptcdatumTest_663, AssignValueObject_663) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    StringValue val("Assigned Value");
    datum = val;

    EXPECT_EQ(datum.toString(), "Assigned Value");
}

// Test: setValue with a Value pointer
TEST_F(IptcdatumTest_663, SetValuePointer_663) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    StringValue val("Set by pointer");
    datum.setValue(&val);

    EXPECT_EQ(datum.toString(), "Set by pointer");
    EXPECT_GT(datum.size(), 0u);
}

// Test: setValue with nullptr
TEST_F(IptcdatumTest_663, SetValueNullptr_663) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Initial");
    Iptcdatum datum(key, &val);

    datum.setValue(nullptr);
    EXPECT_EQ(datum.count(), 0u);
    EXPECT_EQ(datum.size(), 0u);
}

// Test: setValue with string
TEST_F(IptcdatumTest_663, SetValueString_663) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Initial");
    Iptcdatum datum(key, &val);

    int result = datum.setValue("Updated Caption");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Updated Caption");
}

// Test: copy method with a valid value
TEST_F(IptcdatumTest_663, CopyToBuffer_663) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("CopyMe");
    Iptcdatum datum(key, &val);

    byte buf[256];
    std::memset(buf, 0, sizeof(buf));
    size_t copied = datum.copy(buf, bigEndian);

    EXPECT_GT(copied, 0u);
}

// Test: copy method with no value set (nullptr)
TEST_F(IptcdatumTest_663, CopyToBufferNoValue_663) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    byte buf[256];
    std::memset(buf, 0, sizeof(buf));
    size_t copied = datum.copy(buf, bigEndian);

    EXPECT_EQ(copied, 0u);
}

// Test: Record name
TEST_F(IptcdatumTest_663, RecordName_663) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.recordName(), "Application2");
}

// Test: Record number
TEST_F(IptcdatumTest_663, RecordNumber_663) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    // Application2 record is typically record 2
    EXPECT_EQ(datum.record(), 2u);
}

// Test: Tag number
TEST_F(IptcdatumTest_663, TagNumber_663) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    // Caption tag number is 120
    EXPECT_EQ(datum.tag(), 120u);
}

// Test: Family name
TEST_F(IptcdatumTest_663, FamilyName_663) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(std::string(datum.familyName()), "Iptc");
}

// Test: Group name
TEST_F(IptcdatumTest_663, GroupName_663) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test: Tag label
TEST_F(IptcdatumTest_663, TagLabel_663) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    // tagLabel should return a non-empty human-readable label
    EXPECT_FALSE(datum.tagLabel().empty());
}

// Test: typeId when value is set
TEST_F(IptcdatumTest_663, TypeIdWithValue_663) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Test");
    Iptcdatum datum(key, &val);

    EXPECT_EQ(datum.typeId(), string);
}

// Test: typeName when value is set
TEST_F(IptcdatumTest_663, TypeNameWithValue_663) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Test");
    Iptcdatum datum(key, &val);

    EXPECT_NE(datum.typeName(), nullptr);
}

// Test: count when value is not set
TEST_F(IptcdatumTest_663, CountNoValue_663) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.count(), 0u);
}

// Test: size when value is not set
TEST_F(IptcdatumTest_663, SizeNoValue_663) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.size(), 0u);
}

// Test: toString when no value is set
TEST_F(IptcdatumTest_663, ToStringNoValue_663) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.toString(), "");
}

// Test: toString(n) with valid index
TEST_F(IptcdatumTest_663, ToStringWithIndex_663) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Indexed");
    Iptcdatum datum(key, &val);

    EXPECT_EQ(datum.toString(0), "Indexed");
}

// Test: getValue when value is set
TEST_F(IptcdatumTest_663, GetValueWithValue_663) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("GetMe");
    Iptcdatum datum(key, &val);

    auto retrieved = datum.getValue();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toString(), "GetMe");
}

// Test: write to ostream
TEST_F(IptcdatumTest_663, WriteToStream_663) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("StreamWrite");
    Iptcdatum datum(key, &val);

    std::ostringstream os;
    datum.write(os, nullptr);

    EXPECT_FALSE(os.str().empty());
    EXPECT_NE(os.str().find("StreamWrite"), std::string::npos);
}

// Test: Different IPTC records - Envelope record
TEST_F(IptcdatumTest_663, EnvelopeRecord_663) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.record(), 1u);
    EXPECT_EQ(datum.recordName(), "Envelope");
    EXPECT_EQ(datum.groupName(), "Envelope");
}

// Test: Keywords tag
TEST_F(IptcdatumTest_663, KeywordsTag_663) {
    IptcKey key("Iptc.Application2.Keywords");
    StringValue val("keyword1");
    Iptcdatum datum(key, &val);

    EXPECT_EQ(datum.tagName(), "Keywords");
    EXPECT_EQ(datum.toString(), "keyword1");
}

// Test: toInt64 with a numeric value
TEST_F(IptcdatumTest_663, ToInt64_663) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);

    datum = std::string("5");
    // This may or may not parse as int depending on implementation
    // Testing that it doesn't crash
    datum.toInt64(0);
}

// Test: toFloat
TEST_F(IptcdatumTest_663, ToFloat_663) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    datum = std::string("3");

    datum.toFloat(0);
}

// Test: toRational
TEST_F(IptcdatumTest_663, ToRational_663) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    datum = std::string("7");

    Rational r = datum.toRational(0);
    // Just ensure it doesn't crash; verify it returns something
    (void)r;
}

// Test: copy byte order - littleEndian
TEST_F(IptcdatumTest_663, CopyLittleEndian_663) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("LE");
    Iptcdatum datum(key, &val);

    byte buf[256];
    std::memset(buf, 0, sizeof(buf));
    size_t copied = datum.copy(buf, littleEndian);

    EXPECT_GT(copied, 0u);
}

// Test: copy byte order - bigEndian
TEST_F(IptcdatumTest_663, CopyBigEndian_663) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("BE");
    Iptcdatum datum(key, &val);

    byte buf[256];
    std::memset(buf, 0, sizeof(buf));
    size_t copied = datum.copy(buf, bigEndian);

    EXPECT_GT(copied, 0u);
}

// Test: typeSize with string value
TEST_F(IptcdatumTest_663, TypeSize_663) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("SizeTest");
    Iptcdatum datum(key, &val);

    size_t ts = datum.typeSize();
    EXPECT_GT(ts, 0u);
}

// Test: Self-assignment
TEST_F(IptcdatumTest_663, SelfAssignment_663) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("SelfAssign");
    Iptcdatum datum(key, &val);

    datum = datum;

    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum.toString(), "SelfAssign");
}

// Test: Multiple setValue calls
TEST_F(IptcdatumTest_663, MultipleSetValue_663) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    datum.setValue("First");
    EXPECT_EQ(datum.toString(), "First");

    datum.setValue("Second");
    EXPECT_EQ(datum.toString(), "Second");

    datum.setValue("Third");
    EXPECT_EQ(datum.toString(), "Third");
}

// Test: Empty string value
TEST_F(IptcdatumTest_663, EmptyStringValue_663) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    datum = std::string("");
    EXPECT_EQ(datum.toString(), "");
}

// Test: value() throws when no value set
TEST_F(IptcdatumTest_663, ValueThrowsWhenNoValue_663) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_THROW(datum.value(), Exiv2::Error);
}

// Test: tagDesc returns something
TEST_F(IptcdatumTest_663, TagDesc_663) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    // tagDesc should return a description string (may be empty for some tags)
    std::string desc = datum.tagDesc();
    // Just ensure it doesn't crash
    (void)desc;
}
