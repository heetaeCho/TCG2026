#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <exiv2/error.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

// Helper to create IptcKey for common IPTC tags
// Record 2 (Application Record), Dataset 5 (Object Name) is a common IPTC tag
class IptcdatumTest_679 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Default construction with a key and null value pointer
TEST_F(IptcdatumTest_679, ConstructWithKeyAndNullValue_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.key(), "Iptc.Application2.ObjectName");
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
    EXPECT_EQ(datum.groupName(), "Application2");
    EXPECT_EQ(datum.tagName(), "ObjectName");
}

// Test: toString returns empty string when no value is set
TEST_F(IptcdatumTest_679, ToStringReturnsEmptyWhenNoValue_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.toString(), "");
}

// Test: Copy constructor
TEST_F(IptcdatumTest_679, CopyConstructor_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test Value");

    Iptcdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.toString(), "Test Value");
}

// Test: Assignment operator from string
TEST_F(IptcdatumTest_679, AssignFromString_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    datum = std::string("Hello World");
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test: Assignment operator from uint16_t
TEST_F(IptcdatumTest_679, AssignFromUint16_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    uint16_t val = 42;
    datum = val;
    EXPECT_EQ(datum.toString(), "42");
}

// Test: Assignment from another Iptcdatum
TEST_F(IptcdatumTest_679, AssignFromAnotherIptcdatum_679) {
    IptcKey key1("Iptc.Application2.ObjectName");
    Iptcdatum datum1(key1, nullptr);
    datum1 = std::string("Source Value");

    IptcKey key2("Iptc.Application2.Keywords");
    Iptcdatum datum2(key2, nullptr);
    datum2 = datum1;

    EXPECT_EQ(datum2.toString(), "Source Value");
    EXPECT_EQ(datum2.key(), datum1.key());
}

// Test: setValue with string
TEST_F(IptcdatumTest_679, SetValueFromString_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    int result = datum.setValue("Some IPTC data");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Some IPTC data");
}

// Test: setValue with Value pointer
TEST_F(IptcdatumTest_679, SetValueFromValuePointer_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    auto val = Value::create(string);
    val->read("Test from Value");
    datum.setValue(val.get());

    EXPECT_EQ(datum.toString(), "Test from Value");
}

// Test: setValue with nullptr clears the value
TEST_F(IptcdatumTest_679, SetValueWithNullptr_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Non-empty");
    EXPECT_NE(datum.toString(), "");

    datum.setValue(nullptr);
    EXPECT_EQ(datum.toString(), "");
}

// Test: key() returns correct key string
TEST_F(IptcdatumTest_679, KeyReturnsCorrectString_679) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.key(), "Iptc.Application2.Keywords");
}

// Test: recordName returns correct record name
TEST_F(IptcdatumTest_679, RecordNameReturnsCorrect_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.recordName(), "Application2");
}

// Test: record returns correct record number
TEST_F(IptcdatumTest_679, RecordReturnsCorrectNumber_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.record(), 2);
}

// Test: familyName returns "Iptc"
TEST_F(IptcdatumTest_679, FamilyNameReturnsIptc_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test: groupName
TEST_F(IptcdatumTest_679, GroupNameReturnsCorrect_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test: tagName
TEST_F(IptcdatumTest_679, TagNameReturnsCorrect_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.tagName(), "ObjectName");
}

// Test: tag returns correct tag number
TEST_F(IptcdatumTest_679, TagReturnsCorrectNumber_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    // ObjectName is dataset 5
    EXPECT_EQ(datum.tag(), 5);
}

// Test: typeId when no value is set
TEST_F(IptcdatumTest_679, TypeIdWithNoValue_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    // When no value is set, typeId may return a default
    TypeId tid = datum.typeId();
    // Just ensure it doesn't crash; the specific value depends on implementation
    (void)tid;
}

// Test: count when no value is set
TEST_F(IptcdatumTest_679, CountWithNoValue_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.count(), 0u);
}

// Test: size when no value is set
TEST_F(IptcdatumTest_679, SizeWithNoValue_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.size(), 0u);
}

// Test: count after setting a string value
TEST_F(IptcdatumTest_679, CountAfterSetValue_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test");

    EXPECT_GT(datum.count(), 0u);
}

// Test: size after setting a string value
TEST_F(IptcdatumTest_679, SizeAfterSetValue_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test");

    EXPECT_GT(datum.size(), 0u);
}

// Test: getValue returns non-null after setting value
TEST_F(IptcdatumTest_679, GetValueReturnsNonNullAfterSet_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test Value");

    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "Test Value");
}

// Test: getValue returns null when no value is set
TEST_F(IptcdatumTest_679, GetValueReturnsNullWhenNoValue_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    auto val = datum.getValue();
    EXPECT_EQ(val, nullptr);
}

// Test: value() throws when no value is set
TEST_F(IptcdatumTest_679, ValueThrowsWhenNoValueSet_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_THROW(datum.value(), Error);
}

// Test: value() returns reference when value is set
TEST_F(IptcdatumTest_679, ValueReturnsReferenceWhenSet_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Hello");

    EXPECT_NO_THROW({
        const Value& v = datum.value();
        EXPECT_EQ(v.toString(), "Hello");
    });
}

// Test: write to ostream
TEST_F(IptcdatumTest_679, WriteToOstream_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Stream Test");

    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test: Assignment with Value object
TEST_F(IptcdatumTest_679, AssignFromValueObject_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    auto val = Value::create(string);
    val->read("Value Object Test");
    datum = *val;

    EXPECT_EQ(datum.toString(), "Value Object Test");
}

// Test: construct with key and non-null value
TEST_F(IptcdatumTest_679, ConstructWithKeyAndValue_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    auto val = Value::create(string);
    val->read("Initial Value");

    Iptcdatum datum(key, val.get());

    EXPECT_EQ(datum.toString(), "Initial Value");
    EXPECT_EQ(datum.key(), "Iptc.Application2.ObjectName");
}

// Test: toString with index parameter when value is set
TEST_F(IptcdatumTest_679, ToStringWithIndex_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Indexed");

    std::string result = datum.toString(0);
    EXPECT_EQ(result, "Indexed");
}

// Test: tagLabel returns non-empty for known tags
TEST_F(IptcdatumTest_679, TagLabelForKnownTag_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    std::string label = datum.tagLabel();
    // Known IPTC tags should have a label
    EXPECT_FALSE(label.empty());
}

// Test: Envelope record
TEST_F(IptcdatumTest_679, EnvelopeRecord_679) {
    IptcKey key("Iptc.Envelope.CharacterSet");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.record(), 1);
    EXPECT_EQ(datum.recordName(), "Envelope");
    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test: copy to buffer
TEST_F(IptcdatumTest_679, CopyToBuffer_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Copy Test");

    size_t sz = datum.size();
    ASSERT_GT(sz, 0u);

    std::vector<byte> buf(sz);
    size_t copied = datum.copy(buf.data(), bigEndian);
    EXPECT_EQ(copied, sz);
}

// Test: Empty string assignment
TEST_F(IptcdatumTest_679, AssignEmptyString_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    datum = std::string("");
    EXPECT_EQ(datum.toString(), "");
}

// Test: Multiple reassignments
TEST_F(IptcdatumTest_679, MultipleReassignments_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    datum = std::string("First");
    EXPECT_EQ(datum.toString(), "First");

    datum = std::string("Second");
    EXPECT_EQ(datum.toString(), "Second");

    datum = std::string("Third");
    EXPECT_EQ(datum.toString(), "Third");
}

// Test: typeName when value is set as string
TEST_F(IptcdatumTest_679, TypeNameWhenStringValueSet_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum = std::string("typed");

    const char* tn = datum.typeName();
    EXPECT_NE(tn, nullptr);
}

// Test: typeSize when value is set
TEST_F(IptcdatumTest_679, TypeSizeWhenValueSet_679) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum = std::string("size test");

    size_t ts = datum.typeSize();
    EXPECT_GT(ts, 0u);
}
