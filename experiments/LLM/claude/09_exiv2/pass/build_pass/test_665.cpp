#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>
#include <exiv2/value.hpp>
#include <sstream>

using namespace Exiv2;

class IptcdatumTest_665 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that constructing an Iptcdatum with a valid key returns the correct key string
TEST_F(IptcdatumTest_665, ConstructWithKeyReturnsCorrectKey_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test that familyName returns "Iptc"
TEST_F(IptcdatumTest_665, FamilyNameReturnsIptc_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test groupName returns expected record name
TEST_F(IptcdatumTest_665, GroupNameReturnsRecordName_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test tagName returns expected tag name
TEST_F(IptcdatumTest_665, TagNameReturnsExpected_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test recordName returns expected record name
TEST_F(IptcdatumTest_665, RecordNameReturnsExpected_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.recordName(), "Application2");
}

// Test tag() returns a non-zero value for a known tag
TEST_F(IptcdatumTest_665, TagReturnsNonZeroForKnownTag_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Caption tag number should be > 0
    EXPECT_GT(datum.tag(), static_cast<uint16_t>(0));
}

// Test record() returns the expected record number for Application2
TEST_F(IptcdatumTest_665, RecordReturnsExpectedForApplication2_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Application2 record is typically 2
    EXPECT_EQ(datum.record(), static_cast<uint16_t>(2));
}

// Test constructing with nullptr Value and checking count/size
TEST_F(IptcdatumTest_665, NullValueCountAndSizeAreZero_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), static_cast<size_t>(0));
    EXPECT_EQ(datum.size(), static_cast<size_t>(0));
}

// Test setValue with string sets value correctly
TEST_F(IptcdatumTest_665, SetValueStringWorks_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    int result = datum.setValue("Hello World");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test assignment operator with string
TEST_F(IptcdatumTest_665, AssignStringValue_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test Caption");
    EXPECT_EQ(datum.toString(), "Test Caption");
}

// Test assignment operator with uint16_t
TEST_F(IptcdatumTest_665, AssignUint16Value_665) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(5);
    EXPECT_EQ(datum.toString(), "5");
}

// Test copy constructor produces equivalent datum
TEST_F(IptcdatumTest_665, CopyConstructorWorks_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Copy Test");
    
    Iptcdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.toString(), datum.toString());
    EXPECT_EQ(copy.tag(), datum.tag());
    EXPECT_EQ(copy.record(), datum.record());
}

// Test copy assignment operator
TEST_F(IptcdatumTest_665, CopyAssignmentWorks_665) {
    IptcKey key1("Iptc.Application2.Caption");
    Iptcdatum datum1(key1, nullptr);
    datum1 = std::string("Original");

    IptcKey key2("Iptc.Application2.Headline");
    Iptcdatum datum2(key2, nullptr);
    datum2 = std::string("Other");

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.toString(), "Original");
}

// Test setValue with Value object
TEST_F(IptcdatumTest_665, SetValueWithValueObject_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    StringValue val("Value Object Test");
    datum = val;
    EXPECT_EQ(datum.toString(), "Value Object Test");
}

// Test setValue with Value pointer
TEST_F(IptcdatumTest_665, SetValueWithValuePointer_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    auto val = std::make_unique<StringValue>("Pointer Test");
    datum.setValue(val.get());
    EXPECT_EQ(datum.toString(), "Pointer Test");
}

// Test getValue returns a valid unique_ptr when value is set
TEST_F(IptcdatumTest_665, GetValueReturnsValidPtr_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Get Value Test");
    
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "Get Value Test");
}

// Test toString with index
TEST_F(IptcdatumTest_665, ToStringWithIndex_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Indexed");
    EXPECT_EQ(datum.toString(0), "Indexed");
}

// Test constructing with IptcKey from tag and record
TEST_F(IptcdatumTest_665, ConstructWithTagAndRecord_665) {
    // Caption is tag 120 in record 2 (Application2)
    IptcKey key(120, 2);
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.record(), static_cast<uint16_t>(2));
    EXPECT_EQ(datum.tag(), static_cast<uint16_t>(120));
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
}

// Test typeId when no value is set (should still work without crash)
TEST_F(IptcdatumTest_665, TypeIdWithNoValue_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // When no value is set, typeId might return unsignedByte or some default
    // Just verify it doesn't crash
    TypeId id = datum.typeId();
    (void)id; // suppress unused warning
}

// Test typeName when no value is set
TEST_F(IptcdatumTest_665, TypeNameWithNoValue_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Should not crash
    const char* name = datum.typeName();
    (void)name;
}

// Test write to ostream
TEST_F(IptcdatumTest_665, WriteToStream_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Stream Test");
    
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test constructing datum with a Value
TEST_F(IptcdatumTest_665, ConstructWithValue_665) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Initial Value");
    Iptcdatum datum(key, &val);
    EXPECT_EQ(datum.toString(), "Initial Value");
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test count after setting value
TEST_F(IptcdatumTest_665, CountAfterSettingValue_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Count Test");
    EXPECT_GT(datum.count(), static_cast<size_t>(0));
}

// Test size after setting value
TEST_F(IptcdatumTest_665, SizeAfterSettingValue_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Size Test");
    EXPECT_GT(datum.size(), static_cast<size_t>(0));
}

// Test tagLabel returns a non-empty string for known tags
TEST_F(IptcdatumTest_665, TagLabelNonEmptyForKnownTag_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    // Known tags should have a label
    EXPECT_FALSE(label.empty());
}

// Test with Envelope record
TEST_F(IptcdatumTest_665, EnvelopeRecordWorks_665) {
    IptcKey key("Iptc.Envelope.CharacterSet");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Envelope");
    EXPECT_EQ(datum.record(), static_cast<uint16_t>(1));
}

// Test overwriting value
TEST_F(IptcdatumTest_665, OverwriteValue_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("First");
    EXPECT_EQ(datum.toString(), "First");
    datum = std::string("Second");
    EXPECT_EQ(datum.toString(), "Second");
}

// Test setting nullptr value after having a value
TEST_F(IptcdatumTest_665, SetNullValuePtr_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Has Value");
    EXPECT_GT(datum.count(), static_cast<size_t>(0));
    
    datum.setValue(nullptr);
    EXPECT_EQ(datum.count(), static_cast<size_t>(0));
    EXPECT_EQ(datum.size(), static_cast<size_t>(0));
}

// Test empty string value
TEST_F(IptcdatumTest_665, EmptyStringValue_665) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("");
    EXPECT_EQ(datum.toString(), "");
}
