#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>
#include <exiv2/value.hpp>
#include <sstream>
#include <memory>

using namespace Exiv2;

// Test fixture for Iptcdatum tests
class IptcdatumTest_2161 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction with IptcKey and null value
TEST_F(IptcdatumTest_2161, ConstructWithKeyAndNullValue_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test construction with tag and record
TEST_F(IptcdatumTest_2161, ConstructWithTagAndRecord_2161) {
    IptcKey key(120, 2); // Caption tag in Application2 record
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.tag(), 120);
    EXPECT_EQ(datum.record(), 2);
}

// Test copy constructor
TEST_F(IptcdatumTest_2161, CopyConstructor_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum original(key, nullptr);
    original.setValue("Test caption");
    
    Iptcdatum copy(original);
    
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.tag(), original.tag());
    EXPECT_EQ(copy.record(), original.record());
    EXPECT_EQ(copy.toString(), original.toString());
}

// Test copy constructor with no value set
TEST_F(IptcdatumTest_2161, CopyConstructorNoValue_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum original(key, nullptr);
    
    Iptcdatum copy(original);
    
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.familyName(), original.familyName());
}

// Test copy assignment operator
TEST_F(IptcdatumTest_2161, CopyAssignment_2161) {
    IptcKey key1("Iptc.Application2.Caption");
    Iptcdatum datum1(key1, nullptr);
    datum1.setValue("Caption text");
    
    IptcKey key2("Iptc.Application2.Headline");
    Iptcdatum datum2(key2, nullptr);
    
    datum2 = datum1;
    
    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.toString(), "Caption text");
}

// Test assignment from string
TEST_F(IptcdatumTest_2161, AssignFromString_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    datum = std::string("Hello World");
    
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test assignment from uint16_t
TEST_F(IptcdatumTest_2161, AssignFromUint16_2161) {
    IptcKey key("Iptc.Envelope.FileFormat");
    Iptcdatum datum(key, nullptr);
    
    uint16_t val = 42;
    datum = val;
    
    EXPECT_EQ(datum.toInt64(0), 42);
}

// Test assignment from Value object
TEST_F(IptcdatumTest_2161, AssignFromValue_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    auto value = Value::create(string);
    value->read("Test Value");
    datum = *value;
    
    EXPECT_EQ(datum.toString(), "Test Value");
}

// Test setValue with string
TEST_F(IptcdatumTest_2161, SetValueString_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    int result = datum.setValue("Some caption");
    
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Some caption");
}

// Test setValue with Value pointer
TEST_F(IptcdatumTest_2161, SetValuePointer_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    auto value = Value::create(string);
    value->read("Pointer value");
    datum.setValue(value.get());
    
    EXPECT_EQ(datum.toString(), "Pointer value");
}

// Test setValue with null Value pointer
TEST_F(IptcdatumTest_2161, SetValueNullPointer_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("initial");
    
    datum.setValue(nullptr);
    
    // After setting null, getValue should return empty/null
    EXPECT_EQ(datum.count(), 0u);
}

// Test key method
TEST_F(IptcdatumTest_2161, KeyMethod_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test familyName method
TEST_F(IptcdatumTest_2161, FamilyName_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test groupName method
TEST_F(IptcdatumTest_2161, GroupName_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test tagName method
TEST_F(IptcdatumTest_2161, TagName_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test tag method
TEST_F(IptcdatumTest_2161, Tag_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.tag(), key.tag());
}

// Test record and recordName
TEST_F(IptcdatumTest_2161, RecordAndRecordName_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.record(), key.record());
    EXPECT_EQ(datum.recordName(), "Application2");
}

// Test typeId when no value set
TEST_F(IptcdatumTest_2161, TypeIdNoValue_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    // When no value is set, typeId should be some default
    TypeId tid = datum.typeId();
    // Just verify it doesn't crash and returns something
    (void)tid;
}

// Test typeId after setting string value
TEST_F(IptcdatumTest_2161, TypeIdWithStringValue_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("test");
    
    EXPECT_EQ(datum.typeId(), string);
}

// Test count method
TEST_F(IptcdatumTest_2161, CountMethod_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("test string");
    
    EXPECT_GE(datum.count(), 1u);
}

// Test size method
TEST_F(IptcdatumTest_2161, SizeMethod_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("hello");
    
    EXPECT_GT(datum.size(), 0u);
}

// Test toString method
TEST_F(IptcdatumTest_2161, ToStringMethod_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("my caption");
    
    EXPECT_EQ(datum.toString(), "my caption");
}

// Test toString with index
TEST_F(IptcdatumTest_2161, ToStringWithIndex_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("my caption");
    
    std::string result = datum.toString(0);
    EXPECT_EQ(result, "my caption");
}

// Test getValue returns valid unique_ptr
TEST_F(IptcdatumTest_2161, GetValue_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("test");
    
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "test");
}

// Test value() reference
TEST_F(IptcdatumTest_2161, ValueReference_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("reference test");
    
    const Value& val = datum.value();
    EXPECT_EQ(val.toString(), "reference test");
}

// Test write method
TEST_F(IptcdatumTest_2161, WriteMethod_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("write test");
    
    std::ostringstream oss;
    datum.write(oss, nullptr);
    
    EXPECT_FALSE(oss.str().empty());
}

// Test copy method
TEST_F(IptcdatumTest_2161, CopyMethod_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("copy test");
    
    size_t sz = datum.size();
    std::vector<byte> buf(sz);
    size_t copied = datum.copy(buf.data(), bigEndian);
    
    EXPECT_GT(copied, 0u);
}

// Test construction with a Value
TEST_F(IptcdatumTest_2161, ConstructWithValue_2161) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Initial value");
    
    Iptcdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toString(), "Initial value");
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test deep copy - modifying original doesn't affect copy
TEST_F(IptcdatumTest_2161, DeepCopyIndependence_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum original(key, nullptr);
    original.setValue("original text");
    
    Iptcdatum copy(original);
    original.setValue("modified text");
    
    EXPECT_EQ(copy.toString(), "original text");
    EXPECT_EQ(original.toString(), "modified text");
}

// Test deep copy assignment independence
TEST_F(IptcdatumTest_2161, DeepCopyAssignmentIndependence_2161) {
    IptcKey key1("Iptc.Application2.Caption");
    Iptcdatum datum1(key1, nullptr);
    datum1.setValue("first");
    
    IptcKey key2("Iptc.Application2.Headline");
    Iptcdatum datum2(key2, nullptr);
    datum2.setValue("second");
    
    datum2 = datum1;
    datum1.setValue("changed");
    
    EXPECT_EQ(datum2.toString(), "first");
    EXPECT_EQ(datum1.toString(), "changed");
}

// Test tagLabel
TEST_F(IptcdatumTest_2161, TagLabel_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    std::string label = datum.tagLabel();
    // Just verify it returns something without crashing
    EXPECT_FALSE(label.empty());
}

// Test tagDesc
TEST_F(IptcdatumTest_2161, TagDesc_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    std::string desc = datum.tagDesc();
    // Verify it doesn't crash
    (void)desc;
}

// Test Envelope record
TEST_F(IptcdatumTest_2161, EnvelopeRecord_2161) {
    IptcKey key("Iptc.Envelope.CharacterSet");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.groupName(), "Envelope");
    EXPECT_EQ(datum.record(), 1);
}

// Test with numeric value type (unsigned short)
TEST_F(IptcdatumTest_2161, NumericValueType_2161) {
    IptcKey key("Iptc.Envelope.FileFormat");
    auto value = Value::create(unsignedShort);
    value->read("4");
    Iptcdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toInt64(0), 4);
    EXPECT_EQ(datum.typeId(), unsignedShort);
}

// Test toFloat
TEST_F(IptcdatumTest_2161, ToFloat_2161) {
    IptcKey key("Iptc.Envelope.FileFormat");
    auto value = Value::create(unsignedShort);
    value->read("7");
    Iptcdatum datum(key, value.get());
    
    EXPECT_FLOAT_EQ(datum.toFloat(0), 7.0f);
}

// Test toRational
TEST_F(IptcdatumTest_2161, ToRational_2161) {
    IptcKey key("Iptc.Envelope.FileFormat");
    auto value = Value::create(unsignedShort);
    value->read("10");
    Iptcdatum datum(key, value.get());
    
    Rational r = datum.toRational(0);
    // The rational should represent the value 10
    EXPECT_NE(r.second, 0);
    if (r.second != 0) {
        EXPECT_FLOAT_EQ(static_cast<float>(r.first) / r.second, 10.0f);
    }
}

// Test typeName
TEST_F(IptcdatumTest_2161, TypeName_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("type name test");
    
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
    EXPECT_EQ(std::string(tn), "String");
}

// Test typeSize
TEST_F(IptcdatumTest_2161, TypeSize_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("test");
    
    size_t ts = datum.typeSize();
    EXPECT_EQ(ts, 1u); // String type size is 1
}

// Test self-assignment
TEST_F(IptcdatumTest_2161, SelfAssignment_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("self assign test");
    
    datum = datum;
    
    EXPECT_EQ(datum.toString(), "self assign test");
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test count when no value is set
TEST_F(IptcdatumTest_2161, CountNoValue_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.count(), 0u);
}

// Test size when no value is set
TEST_F(IptcdatumTest_2161, SizeNoValue_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.size(), 0u);
}

// Test empty string value
TEST_F(IptcdatumTest_2161, EmptyStringValue_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("");
    
    EXPECT_EQ(datum.toString(), "");
}

// Test multiple setValue calls
TEST_F(IptcdatumTest_2161, MultipleSetValue_2161) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    datum.setValue("first");
    EXPECT_EQ(datum.toString(), "first");
    
    datum.setValue("second");
    EXPECT_EQ(datum.toString(), "second");
    
    datum.setValue("third");
    EXPECT_EQ(datum.toString(), "third");
}
