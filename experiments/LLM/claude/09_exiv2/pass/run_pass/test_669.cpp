#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>
#include <exiv2/value.hpp>
#include <sstream>

using namespace Exiv2;

class IptcdatumTest_669 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction with a string key
TEST_F(IptcdatumTest_669, ConstructWithStringKey_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test groupName returns correct group
TEST_F(IptcdatumTest_669, GroupNameReturnsCorrectGroup_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test familyName returns "Iptc"
TEST_F(IptcdatumTest_669, FamilyNameReturnsIptc_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test tagName returns correct tag name
TEST_F(IptcdatumTest_669, TagNameReturnsCorrectTag_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test recordName returns correct record
TEST_F(IptcdatumTest_669, RecordNameReturnsCorrectRecord_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.recordName(), "Application2");
}

// Test tag returns correct tag number
TEST_F(IptcdatumTest_669, TagReturnsCorrectNumber_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Caption tag is 120
    EXPECT_EQ(datum.tag(), 120);
}

// Test record returns correct record number
TEST_F(IptcdatumTest_669, RecordReturnsCorrectNumber_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Application2 record is 2
    EXPECT_EQ(datum.record(), 2);
}

// Test construction with tag and record numbers
TEST_F(IptcdatumTest_669, ConstructWithTagAndRecord_669) {
    IptcKey key(120, 2);  // Caption in Application2
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), 120);
    EXPECT_EQ(datum.record(), 2);
}

// Test copy constructor
TEST_F(IptcdatumTest_669, CopyConstructor_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    Iptcdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.groupName(), datum.groupName());
    EXPECT_EQ(copy.tagName(), datum.tagName());
}

// Test assignment operator
TEST_F(IptcdatumTest_669, AssignmentOperator_669) {
    IptcKey key1("Iptc.Application2.Caption");
    IptcKey key2("Iptc.Application2.Keywords");
    Iptcdatum datum1(key1, nullptr);
    Iptcdatum datum2(key2, nullptr);
    datum2 = datum1;
    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.groupName(), datum1.groupName());
}

// Test setValue with string value
TEST_F(IptcdatumTest_669, SetValueWithString_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    int result = datum.setValue("Test Caption");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Test Caption");
}

// Test assignment with string
TEST_F(IptcdatumTest_669, AssignString_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Hello World");
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test count and size with no value
TEST_F(IptcdatumTest_669, CountAndSizeWithNoValue_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
    EXPECT_EQ(datum.size(), 0u);
}

// Test count after setting value
TEST_F(IptcdatumTest_669, CountAfterSetValue_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Test");
    EXPECT_GT(datum.count(), 0u);
}

// Test size after setting value
TEST_F(IptcdatumTest_669, SizeAfterSetValue_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Test");
    EXPECT_GT(datum.size(), 0u);
}

// Test setValue with Value pointer (nullptr)
TEST_F(IptcdatumTest_669, SetValueWithNullptr_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue(static_cast<const Value*>(nullptr));
    EXPECT_EQ(datum.count(), 0u);
}

// Test setValue with actual Value
TEST_F(IptcdatumTest_669, SetValueWithValueObject_669) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Test Value");
    Iptcdatum datum(key, &val);
    EXPECT_EQ(datum.toString(), "Test Value");
}

// Test assignment with Value object
TEST_F(IptcdatumTest_669, AssignValueObject_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    StringValue val("Assigned Value");
    datum = val;
    EXPECT_EQ(datum.toString(), "Assigned Value");
}

// Test getValue returns non-null after setting value
TEST_F(IptcdatumTest_669, GetValueAfterSet_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Some Value");
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "Some Value");
}

// Test write to ostream
TEST_F(IptcdatumTest_669, WriteToStream_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Stream Test");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test with Envelope record
TEST_F(IptcdatumTest_669, EnvelopeRecord_669) {
    IptcKey key("Iptc.Envelope.CharacterSet");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Envelope");
    EXPECT_EQ(datum.record(), 1);
}

// Test different Application2 tags
TEST_F(IptcdatumTest_669, Application2Keywords_669) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Keywords");
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test tagLabel returns non-empty for known tags
TEST_F(IptcdatumTest_669, TagLabelNonEmpty_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test typeId with no value set
TEST_F(IptcdatumTest_669, TypeIdWithNoValue_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // When no value is set, typeId should return unsignedShort (default) or similar
    TypeId typeId = datum.typeId();
    // Just ensure it doesn't crash and returns a valid value
    (void)typeId;
}

// Test typeId with value set
TEST_F(IptcdatumTest_669, TypeIdWithValueSet_669) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("test");
    Iptcdatum datum(key, &val);
    EXPECT_EQ(datum.typeId(), string);
}

// Test typeName with value set
TEST_F(IptcdatumTest_669, TypeNameWithValueSet_669) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("test");
    Iptcdatum datum(key, &val);
    EXPECT_NE(datum.typeName(), nullptr);
}

// Test toString with index
TEST_F(IptcdatumTest_669, ToStringWithIndex_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Indexed");
    std::string result = datum.toString(0);
    EXPECT_EQ(result, "Indexed");
}

// Test assignment with uint16_t
TEST_F(IptcdatumTest_669, AssignUint16_669) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    uint16_t val = 5;
    datum = val;
    // After assignment, the datum should have a value
    EXPECT_GT(datum.count(), 0u);
}

// Test copy to buffer
TEST_F(IptcdatumTest_669, CopyToBuffer_669) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("buf");
    Iptcdatum datum(key, &val);
    byte buf[64] = {0};
    size_t copied = datum.copy(buf, bigEndian);
    EXPECT_GT(copied, 0u);
}

// Test self-assignment
TEST_F(IptcdatumTest_669, SelfAssignment_669) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("Self");
    datum = datum;
    EXPECT_EQ(datum.toString(), "Self");
}
