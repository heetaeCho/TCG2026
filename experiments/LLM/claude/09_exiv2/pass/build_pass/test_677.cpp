#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <exiv2/error.hpp>
#include <string>
#include <memory>

using namespace Exiv2;

class IptcdatumTest_677 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Default constructed Iptcdatum (with no value) should have count() == 0
TEST_F(IptcdatumTest_677, CountReturnsZeroWhenNoValue_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test: Iptcdatum constructed with a value should return correct count
TEST_F(IptcdatumTest_677, CountReturnsNonZeroWhenValueSet_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Hello World");
    EXPECT_GT(datum.count(), 0u);
}

// Test: key() returns the correct key string
TEST_F(IptcdatumTest_677, KeyReturnsCorrectString_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test: familyName() returns "Iptc"
TEST_F(IptcdatumTest_677, FamilyNameReturnsIptc_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    std::string family = datum.familyName();
    EXPECT_EQ(family, "Iptc");
}

// Test: groupName() returns the record name
TEST_F(IptcdatumTest_677, GroupNameReturnsRecordName_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test: tagName() returns the tag name portion
TEST_F(IptcdatumTest_677, TagNameReturnsCorrectTag_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test: recordName() returns the record name
TEST_F(IptcdatumTest_677, RecordNameReturnsCorrectRecord_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.recordName(), "Application2");
}

// Test: Copy constructor produces equivalent datum
TEST_F(IptcdatumTest_677, CopyConstructorCopiesData_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Test value");

    Iptcdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.toString(), datum.toString());
    EXPECT_EQ(copy.count(), datum.count());
}

// Test: Assignment operator copies data correctly
TEST_F(IptcdatumTest_677, AssignmentOperatorCopiesData_677) {
    IptcKey key1("Iptc.Application2.Caption");
    Iptcdatum datum1(key1, nullptr);
    datum1.setValue("Value1");

    IptcKey key2("Iptc.Application2.Keywords");
    Iptcdatum datum2(key2, nullptr);
    datum2.setValue("Value2");

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.toString(), datum1.toString());
}

// Test: Assignment from string sets value
TEST_F(IptcdatumTest_677, AssignmentFromStringSetsValue_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("assigned string");
    EXPECT_EQ(datum.toString(), "assigned string");
}

// Test: Assignment from uint16_t sets value
TEST_F(IptcdatumTest_677, AssignmentFromUint16SetsValue_677) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(42);
    EXPECT_NE(datum.count(), 0u);
}

// Test: setValue with string sets value and count
TEST_F(IptcdatumTest_677, SetValueStringSetsCountAndValue_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    int result = datum.setValue("test");
    EXPECT_EQ(result, 0);
    EXPECT_GT(datum.count(), 0u);
    EXPECT_EQ(datum.toString(), "test");
}

// Test: setValue with nullptr resets value
TEST_F(IptcdatumTest_677, SetValueNullptrResetsValue_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("something");
    EXPECT_GT(datum.count(), 0u);

    datum.setValue(nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test: size() returns 0 when no value is set
TEST_F(IptcdatumTest_677, SizeReturnsZeroWhenNoValue_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test: size() returns non-zero after setting value
TEST_F(IptcdatumTest_677, SizeReturnsNonZeroAfterSetValue_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Hello");
    EXPECT_GT(datum.size(), 0u);
}

// Test: toString returns empty when no value
TEST_F(IptcdatumTest_677, ToStringReturnsEmptyWhenNoValue_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.toString(), "");
}

// Test: toString(n) with n=0 after setting value
TEST_F(IptcdatumTest_677, ToStringWithIndexReturnsValue_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("indexed value");
    EXPECT_EQ(datum.toString(0), "indexed value");
}

// Test: typeId() returns expected type
TEST_F(IptcdatumTest_677, TypeIdReturnsCorrectType_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("test");
    TypeId tid = datum.typeId();
    EXPECT_NE(tid, invalidTypeId);
}

// Test: getValue returns nullptr when no value set
TEST_F(IptcdatumTest_677, GetValueReturnsNullWhenNoValue_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    auto val = datum.getValue();
    EXPECT_EQ(val.get(), nullptr);
}

// Test: getValue returns non-null when value is set
TEST_F(IptcdatumTest_677, GetValueReturnsNonNullWhenValueSet_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("has value");
    auto val = datum.getValue();
    EXPECT_NE(val.get(), nullptr);
}

// Test: value() throws when no value set
TEST_F(IptcdatumTest_677, ValueThrowsWhenNoValueSet_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_THROW(datum.value(), Error);
}

// Test: value() returns reference when value is set
TEST_F(IptcdatumTest_677, ValueReturnsReferenceWhenSet_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("test");
    EXPECT_NO_THROW({
        const Value& v = datum.value();
        (void)v;
    });
}

// Test: tag() returns expected IPTC tag number
TEST_F(IptcdatumTest_677, TagReturnsCorrectTagNumber_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Caption/Abstract is tag 120 in IPTC Application2
    EXPECT_EQ(datum.tag(), 120u);
}

// Test: record() returns expected record number
TEST_F(IptcdatumTest_677, RecordReturnsCorrectRecordNumber_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Application2 is record 2
    EXPECT_EQ(datum.record(), 2u);
}

// Test: Assigning a Value object directly
TEST_F(IptcdatumTest_677, AssignValueObjectSetsCorrectly_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    auto val = Value::create(string);
    val->read("Direct value assignment");
    datum = *val;
    
    EXPECT_EQ(datum.toString(), "Direct value assignment");
    EXPECT_GT(datum.count(), 0u);
}

// Test: Setting value with a Value pointer
TEST_F(IptcdatumTest_677, SetValueWithValuePointer_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    auto val = Value::create(string);
    val->read("Pointer value");
    datum.setValue(val.get());
    
    EXPECT_EQ(datum.toString(), "Pointer value");
}

// Test: write() to ostream produces output
TEST_F(IptcdatumTest_677, WriteToOstream_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("write test");
    
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test: tagLabel returns non-empty for known tags
TEST_F(IptcdatumTest_677, TagLabelReturnsNonEmpty_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test: copy to buffer works when value is set
TEST_F(IptcdatumTest_677, CopyToBufferWorks_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("buffer test");
    
    size_t sz = datum.size();
    EXPECT_GT(sz, 0u);
    
    std::vector<byte> buf(sz);
    size_t copied = datum.copy(buf.data(), bigEndian);
    EXPECT_GT(copied, 0u);
}

// Test: Multiple setValue calls overwrite previous value
TEST_F(IptcdatumTest_677, MultipleSetValueOverwrites_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    datum.setValue("first");
    EXPECT_EQ(datum.toString(), "first");
    
    datum.setValue("second");
    EXPECT_EQ(datum.toString(), "second");
}

// Test: Empty string setValue
TEST_F(IptcdatumTest_677, SetValueEmptyString_677) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    int result = datum.setValue("");
    EXPECT_EQ(result, 0);
}

// Test: Keywords tag (different record)
TEST_F(IptcdatumTest_677, KeywordsTagWorks_677) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);
    datum.setValue("keyword1");
    EXPECT_EQ(datum.tagName(), "Keywords");
    EXPECT_EQ(datum.toString(), "keyword1");
}

// Test: Envelope record tag
TEST_F(IptcdatumTest_677, EnvelopeRecordTag_677) {
    IptcKey key("Iptc.Envelope.CharacterSet");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.recordName(), "Envelope");
    EXPECT_EQ(datum.record(), 1u);
}
