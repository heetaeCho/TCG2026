#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>
#include <exiv2/value.hpp>
#include <exiv2/error.hpp>
#include <sstream>

using namespace Exiv2;

class IptcdatumTest_666 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction with a string key
TEST_F(IptcdatumTest_666, ConstructWithStringKey_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test recordName returns expected record name
TEST_F(IptcdatumTest_666, RecordNameReturnsCorrectValue_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    std::string recordName = datum.recordName();
    EXPECT_EQ(recordName, "Application2");
}

// Test familyName returns "Iptc"
TEST_F(IptcdatumTest_666, FamilyNameReturnsIptc_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test groupName returns the record/group name
TEST_F(IptcdatumTest_666, GroupNameReturnsCorrectValue_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test tagName returns expected tag name
TEST_F(IptcdatumTest_666, TagNameReturnsCorrectValue_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test tag() returns correct tag number
TEST_F(IptcdatumTest_666, TagReturnsCorrectValue_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Caption is tag 120 in Application2 record
    EXPECT_EQ(datum.tag(), 120);
}

// Test record() returns correct record number
TEST_F(IptcdatumTest_666, RecordReturnsCorrectValue_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Application2 is record 2
    EXPECT_EQ(datum.record(), 2);
}

// Test construction with tag and record numbers
TEST_F(IptcdatumTest_666, ConstructWithTagAndRecord_666) {
    IptcKey key(120, 2); // Caption in Application2
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), 120);
    EXPECT_EQ(datum.record(), 2);
}

// Test copy constructor
TEST_F(IptcdatumTest_666, CopyConstructor_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum1(key, nullptr);
    Iptcdatum datum2(datum1);
    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.tag(), datum1.tag());
    EXPECT_EQ(datum2.record(), datum1.record());
    EXPECT_EQ(datum2.recordName(), datum1.recordName());
}

// Test copy assignment operator
TEST_F(IptcdatumTest_666, CopyAssignment_666) {
    IptcKey key1("Iptc.Application2.Caption");
    IptcKey key2("Iptc.Application2.Keywords");
    Iptcdatum datum1(key1, nullptr);
    Iptcdatum datum2(key2, nullptr);
    datum2 = datum1;
    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.tag(), datum1.tag());
}

// Test setValue with a string value
TEST_F(IptcdatumTest_666, SetValueWithString_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    int result = datum.setValue("Test caption");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Test caption");
}

// Test assignment with string
TEST_F(IptcdatumTest_666, AssignString_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Hello World");
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test count after setting a value
TEST_F(IptcdatumTest_666, CountAfterSetValue_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Some text");
    EXPECT_GT(datum.count(), 0u);
}

// Test size after setting a value
TEST_F(IptcdatumTest_666, SizeAfterSetValue_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Some text");
    EXPECT_GT(datum.size(), 0u);
}

// Test assignment with Value object
TEST_F(IptcdatumTest_666, AssignValueObject_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    StringValue val("Test value");
    datum = val;
    EXPECT_EQ(datum.toString(), "Test value");
}

// Test setValue with Value pointer
TEST_F(IptcdatumTest_666, SetValueWithPointer_666) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Pointer value");
    Iptcdatum datum(key, &val);
    EXPECT_EQ(datum.toString(), "Pointer value");
}

// Test write to output stream
TEST_F(IptcdatumTest_666, WriteToStream_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Stream test");
    std::ostringstream oss;
    datum.write(oss, nullptr);
    EXPECT_FALSE(oss.str().empty());
}

// Test getValue returns valid pointer after setValue
TEST_F(IptcdatumTest_666, GetValueAfterSet_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("get value test");
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "get value test");
}

// Test with Envelope record
TEST_F(IptcdatumTest_666, EnvelopeRecord_666) {
    IptcKey key("Iptc.Envelope.CharacterSet");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.recordName(), "Envelope");
    EXPECT_EQ(datum.record(), 1);
}

// Test tagLabel returns non-empty string for known tag
TEST_F(IptcdatumTest_666, TagLabelNonEmpty_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test typeId when value is set
TEST_F(IptcdatumTest_666, TypeIdWithValue_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("type test");
    TypeId tid = datum.typeId();
    // String type expected for caption
    EXPECT_EQ(tid, string);
}

// Test typeName when value is set
TEST_F(IptcdatumTest_666, TypeNameWithValue_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("typename test");
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
}

// Test assignment with uint16_t
TEST_F(IptcdatumTest_666, AssignUint16_666) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    uint16_t val = 5;
    datum = val;
    EXPECT_EQ(datum.toString(), "5");
}

// Test toString with index n=0
TEST_F(IptcdatumTest_666, ToStringWithIndex_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("indexed test");
    std::string s = datum.toString(0);
    EXPECT_EQ(s, "indexed test");
}

// Test toInt64 after setting numeric value
TEST_F(IptcdatumTest_666, ToInt64_666) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    datum.setValue("42");
    int64_t v = datum.toInt64(0);
    EXPECT_EQ(v, 42);
}

// Test toFloat after setting numeric value
TEST_F(IptcdatumTest_666, ToFloat_666) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    datum.setValue("3");
    float f = datum.toFloat(0);
    EXPECT_FLOAT_EQ(f, 3.0f);
}

// Test copy to buffer
TEST_F(IptcdatumTest_666, CopyToBuffer_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("buf test");
    byte buf[256] = {};
    size_t copied = datum.copy(buf, bigEndian);
    EXPECT_GT(copied, 0u);
}

// Test that construction with nullptr value doesn't crash on key accessors
TEST_F(IptcdatumTest_666, NullValueKeyAccessors_666) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Iptc.Application2.Keywords");
    EXPECT_EQ(datum.tagName(), "Keywords");
    EXPECT_EQ(datum.recordName(), "Application2");
    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test different Application2 tags
TEST_F(IptcdatumTest_666, DifferentTags_666) {
    IptcKey key1("Iptc.Application2.ObjectName");
    Iptcdatum datum1(key1, nullptr);
    EXPECT_EQ(datum1.tag(), 5);

    IptcKey key2("Iptc.Application2.Keywords");
    Iptcdatum datum2(key2, nullptr);
    EXPECT_EQ(datum2.tag(), 25);
}

// Test self-assignment
TEST_F(IptcdatumTest_666, SelfAssignment_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("self assign");
    datum = datum;
    EXPECT_EQ(datum.toString(), "self assign");
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test replacing value with setValue pointer (nullptr to clear)
TEST_F(IptcdatumTest_666, SetValuePointerNull_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("initial");
    datum.setValue(static_cast<const Value*>(nullptr));
    // After setting nullptr, the key should still be valid
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test tagDesc returns a string (may be empty for some tags)
TEST_F(IptcdatumTest_666, TagDescReturnsString_666) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Just ensure it doesn't throw
    std::string desc = datum.tagDesc();
    // desc may or may not be empty, just ensure it's a valid string
    SUCCEED();
}
