#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <exiv2/properties.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

// Helper to create an IptcKey for testing
// Using well-known IPTC keys like "Iptc.Application2.Caption"

class IptcdatumTest_678 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Constructing an Iptcdatum with a key and no value (nullptr)
TEST_F(IptcdatumTest_678, ConstructWithKeyAndNullValue_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum.size(), 0u);
}

// Test: Key returns correct key string
TEST_F(IptcdatumTest_678, KeyReturnsCorrectString_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test: familyName returns "Iptc"
TEST_F(IptcdatumTest_678, FamilyNameReturnsIptc_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test: groupName returns the record name
TEST_F(IptcdatumTest_678, GroupNameReturnsRecordName_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test: tagName returns the tag name
TEST_F(IptcdatumTest_678, TagNameReturnsCorrectName_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test: recordName returns the record name
TEST_F(IptcdatumTest_678, RecordNameReturnsCorrectName_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.recordName(), "Application2");
}

// Test: size returns 0 when no value is set
TEST_F(IptcdatumTest_678, SizeReturnsZeroWhenNoValue_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.size(), 0u);
}

// Test: count returns 0 when no value is set
TEST_F(IptcdatumTest_678, CountReturnsZeroWhenNoValue_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.count(), 0u);
}

// Test: setValue with string value
TEST_F(IptcdatumTest_678, SetValueWithString_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    int result = datum.setValue("Hello World");
    EXPECT_EQ(result, 0);
    EXPECT_GT(datum.size(), 0u);
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test: Assign string value using operator=
TEST_F(IptcdatumTest_678, AssignStringValue_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    datum = std::string("Test Caption");
    EXPECT_EQ(datum.toString(), "Test Caption");
    EXPECT_GT(datum.size(), 0u);
}

// Test: Copy constructor
TEST_F(IptcdatumTest_678, CopyConstructor_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Copy Test");

    Iptcdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.toString(), datum.toString());
    EXPECT_EQ(copy.size(), datum.size());
}

// Test: Assignment operator from another Iptcdatum
TEST_F(IptcdatumTest_678, AssignmentOperatorFromIptcdatum_678) {
    IptcKey key1("Iptc.Application2.Caption");
    Iptcdatum datum1(key1, nullptr);
    datum1.setValue("First");

    IptcKey key2("Iptc.Application2.Keywords");
    Iptcdatum datum2(key2, nullptr);
    datum2.setValue("Second");

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.toString(), "First");
}

// Test: setValue with Value pointer (nullptr)
TEST_F(IptcdatumTest_678, SetValueWithNullptr_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Non empty");
    EXPECT_GT(datum.size(), 0u);

    datum.setValue(static_cast<const Value*>(nullptr));
    EXPECT_EQ(datum.size(), 0u);
}

// Test: setValue with a concrete Value object
TEST_F(IptcdatumTest_678, SetValueWithValueObject_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    auto val = Value::create(string);
    val->read("Value Object Test");
    datum.setValue(val.get());

    EXPECT_EQ(datum.toString(), "Value Object Test");
    EXPECT_GT(datum.size(), 0u);
}

// Test: Assign Value using operator=(const Value&)
TEST_F(IptcdatumTest_678, AssignValueObject_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    auto val = Value::create(string);
    val->read("Assigned Value");
    datum = *val;

    EXPECT_EQ(datum.toString(), "Assigned Value");
}

// Test: tag returns a valid tag number
TEST_F(IptcdatumTest_678, TagReturnsValidTag_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    // Caption/Abstract is tag 120 in Application Record
    EXPECT_EQ(datum.tag(), 120u);
}

// Test: record returns valid record number
TEST_F(IptcdatumTest_678, RecordReturnsValidNumber_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    // Application Record is record 2
    EXPECT_EQ(datum.record(), 2u);
}

// Test: typeId when value is set
TEST_F(IptcdatumTest_678, TypeIdWithValue_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Test");

    TypeId tid = datum.typeId();
    // After setting a string value, typeId should be valid (string type)
    EXPECT_NE(tid, invalidTypeId);
}

// Test: getValue returns non-null after setting value
TEST_F(IptcdatumTest_678, GetValueReturnsNonNullAfterSet_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("GetValue Test");

    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "GetValue Test");
}

// Test: getValue returns null when no value set
TEST_F(IptcdatumTest_678, GetValueReturnsNullWhenNoValue_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    auto val = datum.getValue();
    EXPECT_EQ(val, nullptr);
}

// Test: value() throws when no value is set
TEST_F(IptcdatumTest_678, ValueThrowsWhenNoValueSet_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_THROW(datum.value(), Error);
}

// Test: toString returns empty when no value set
TEST_F(IptcdatumTest_678, ToStringReturnsEmptyWhenNoValue_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.toString(), "");
}

// Test: write to ostream
TEST_F(IptcdatumTest_678, WriteToOstream_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Stream Test");

    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test: Assign uint16_t value
TEST_F(IptcdatumTest_678, AssignUint16Value_678) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);

    uint16_t val = 5;
    datum = val;
    EXPECT_GT(datum.size(), 0u);
}

// Test: copy to buffer when value is set
TEST_F(IptcdatumTest_678, CopyToBuffer_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Buffer Test");

    size_t sz = datum.size();
    ASSERT_GT(sz, 0u);

    std::vector<byte> buf(sz);
    size_t copied = datum.copy(buf.data(), bigEndian);
    EXPECT_EQ(copied, sz);
}

// Test: Different IPTC key - Envelope record
TEST_F(IptcdatumTest_678, EnvelopeRecordKey_678) {
    IptcKey key("Iptc.Envelope.CharacterSet");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
    EXPECT_EQ(datum.groupName(), "Envelope");
    EXPECT_EQ(datum.record(), 1u);
}

// Test: Keywords tag
TEST_F(IptcdatumTest_678, KeywordsTag_678) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);

    datum.setValue("keyword1");
    EXPECT_EQ(datum.toString(), "keyword1");
    EXPECT_EQ(datum.tagName(), "Keywords");
}

// Test: tagLabel returns non-empty for known tag
TEST_F(IptcdatumTest_678, TagLabelNonEmpty_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test: typeName when value is set
TEST_F(IptcdatumTest_678, TypeNameWhenValueSet_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Type Test");

    const char* tn = datum.typeName();
    EXPECT_NE(tn, nullptr);
}

// Test: toString(n) with index 0
TEST_F(IptcdatumTest_678, ToStringWithIndex_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Indexed String");

    std::string result = datum.toString(0);
    EXPECT_EQ(result, "Indexed String");
}

// Test: Constructing Iptcdatum with a Value pointer
TEST_F(IptcdatumTest_678, ConstructWithValue_678) {
    IptcKey key("Iptc.Application2.Caption");
    auto val = Value::create(string);
    val->read("Initial Value");

    Iptcdatum datum(key, val.get());
    EXPECT_EQ(datum.toString(), "Initial Value");
    EXPECT_GT(datum.size(), 0u);
}

// Test: Multiple setValue calls overwrite previous
TEST_F(IptcdatumTest_678, SetValueOverwritesPrevious_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    datum.setValue("First Value");
    EXPECT_EQ(datum.toString(), "First Value");

    datum.setValue("Second Value");
    EXPECT_EQ(datum.toString(), "Second Value");
}

// Test: count after setting string value
TEST_F(IptcdatumTest_678, CountAfterSettingValue_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    datum.setValue("Count Test");
    EXPECT_GT(datum.count(), 0u);
}

// Test: Empty string value
TEST_F(IptcdatumTest_678, EmptyStringValue_678) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    datum.setValue("");
    // Size may or may not be 0 for empty string, but should not crash
    EXPECT_EQ(datum.toString(), "");
}
