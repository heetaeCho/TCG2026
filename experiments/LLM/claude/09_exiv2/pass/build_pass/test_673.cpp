#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>

using namespace Exiv2;

class IptcdatumTest_673 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that constructing Iptcdatum with a known key yields correct tag
TEST_F(IptcdatumTest_673, ConstructWithKeyReturnsCorrectTag_673) {
    IptcKey key(5, 2);  // tag=5, record=2
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), 5);
}

// Test that record() returns the correct record number
TEST_F(IptcdatumTest_673, ConstructWithKeyReturnsCorrectRecord_673) {
    IptcKey key(10, 2);
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.record(), 2);
}

// Test familyName returns "Iptc"
TEST_F(IptcdatumTest_673, FamilyNameReturnsIptc_673) {
    IptcKey key(5, 2);
    Iptcdatum datum(key, nullptr);
    std::string family = datum.familyName();
    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test key() returns a non-empty string
TEST_F(IptcdatumTest_673, KeyReturnsNonEmptyString_673) {
    IptcKey key(5, 2);
    Iptcdatum datum(key, nullptr);
    std::string k = datum.key();
    EXPECT_FALSE(k.empty());
}

// Test copy constructor preserves tag
TEST_F(IptcdatumTest_673, CopyConstructorPreservesTag_673) {
    IptcKey key(25, 2);
    Iptcdatum datum(key, nullptr);
    Iptcdatum copy(datum);
    EXPECT_EQ(copy.tag(), 25);
    EXPECT_EQ(copy.record(), 2);
}

// Test copy constructor preserves key string
TEST_F(IptcdatumTest_673, CopyConstructorPreservesKey_673) {
    IptcKey key(25, 2);
    Iptcdatum datum(key, nullptr);
    Iptcdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
}

// Test assignment operator
TEST_F(IptcdatumTest_673, AssignmentOperatorCopiesCorrectly_673) {
    IptcKey key1(10, 2);
    IptcKey key2(20, 2);
    Iptcdatum datum1(key1, nullptr);
    Iptcdatum datum2(key2, nullptr);
    datum2 = datum1;
    EXPECT_EQ(datum2.tag(), 10);
}

// Test assigning a string value
TEST_F(IptcdatumTest_673, AssignStringValue_673) {
    IptcKey key(120, 2); // Keywords tag in Application Record
    Iptcdatum datum(key, nullptr);
    datum = std::string("TestValue");
    EXPECT_EQ(datum.toString(), "TestValue");
    EXPECT_GT(datum.count(), 0u);
}

// Test assigning a uint16_t value
TEST_F(IptcdatumTest_673, AssignUint16Value_673) {
    IptcKey key(0, 1); // envelope record, tag 0 (model version)
    Iptcdatum datum(key, nullptr);
    uint16_t val = 42;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 42);
}

// Test setValue with string
TEST_F(IptcdatumTest_673, SetValueWithString_673) {
    IptcKey key(120, 2);
    Iptcdatum datum(key, nullptr);
    int result = datum.setValue("HelloWorld");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "HelloWorld");
}

// Test setValue with Value pointer
TEST_F(IptcdatumTest_673, SetValueWithValuePointer_673) {
    IptcKey key(120, 2);
    Iptcdatum datum(key, nullptr);
    StringValue val("TestPointerValue");
    datum.setValue(&val);
    EXPECT_EQ(datum.toString(), "TestPointerValue");
}

// Test assigning a Value object
TEST_F(IptcdatumTest_673, AssignValueObject_673) {
    IptcKey key(120, 2);
    Iptcdatum datum(key, nullptr);
    StringValue val("AssignedValue");
    datum = val;
    EXPECT_EQ(datum.toString(), "AssignedValue");
}

// Test size and count for string value
TEST_F(IptcdatumTest_673, SizeAndCountForStringValue_673) {
    IptcKey key(120, 2);
    Iptcdatum datum(key, nullptr);
    datum = std::string("ABCDE");
    EXPECT_EQ(datum.count(), 1u);
    EXPECT_EQ(datum.size(), 5u);
}

// Test that constructing with nullptr value yields count 0
TEST_F(IptcdatumTest_673, NullValueYieldsZeroCount_673) {
    IptcKey key(120, 2);
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
    EXPECT_EQ(datum.size(), 0u);
}

// Test getValue returns valid unique_ptr after setValue
TEST_F(IptcdatumTest_673, GetValueReturnsValidPtr_673) {
    IptcKey key(120, 2);
    Iptcdatum datum(key, nullptr);
    datum = std::string("test");
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "test");
}

// Test typeId when no value is set
TEST_F(IptcdatumTest_673, TypeIdWithNoValue_673) {
    IptcKey key(120, 2);
    Iptcdatum datum(key, nullptr);
    // Without a value, typeId should be some default (unsignedShort or undefined)
    TypeId tid = datum.typeId();
    // Just verify it's callable and returns something
    (void)tid;
}

// Test write to ostream
TEST_F(IptcdatumTest_673, WriteToOstream_673) {
    IptcKey key(120, 2);
    Iptcdatum datum(key, nullptr);
    datum = std::string("StreamTest");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
    EXPECT_NE(os.str().find("StreamTest"), std::string::npos);
}

// Test recordName returns non-empty string
TEST_F(IptcdatumTest_673, RecordNameReturnsNonEmpty_673) {
    IptcKey key(5, 2);
    Iptcdatum datum(key, nullptr);
    std::string rn = datum.recordName();
    EXPECT_FALSE(rn.empty());
}

// Test groupName returns non-empty string
TEST_F(IptcdatumTest_673, GroupNameReturnsNonEmpty_673) {
    IptcKey key(5, 2);
    Iptcdatum datum(key, nullptr);
    std::string gn = datum.groupName();
    EXPECT_FALSE(gn.empty());
}

// Test tagName returns non-empty string
TEST_F(IptcdatumTest_673, TagNameReturnsNonEmpty_673) {
    IptcKey key(5, 2);
    Iptcdatum datum(key, nullptr);
    std::string tn = datum.tagName();
    EXPECT_FALSE(tn.empty());
}

// Test that constructing from a string key works
TEST_F(IptcdatumTest_673, ConstructFromStringKey_673) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Iptc.Application2.Keywords");
    EXPECT_EQ(datum.tag(), key.tag());
    EXPECT_EQ(datum.record(), key.record());
}

// Test copy to buffer
TEST_F(IptcdatumTest_673, CopyToBuffer_673) {
    IptcKey key(120, 2);
    Iptcdatum datum(key, nullptr);
    datum = std::string("BufTest");
    byte buf[64] = {};
    size_t sz = datum.copy(buf, bigEndian);
    EXPECT_GT(sz, 0u);
}

// Test toString with index parameter
TEST_F(IptcdatumTest_673, ToStringWithIndex_673) {
    IptcKey key(120, 2);
    Iptcdatum datum(key, nullptr);
    datum = std::string("indexed");
    std::string s = datum.toString(0);
    EXPECT_EQ(s, "indexed");
}

// Test toFloat
TEST_F(IptcdatumTest_673, ToFloatWithUint16Value_673) {
    IptcKey key(0, 1);
    Iptcdatum datum(key, nullptr);
    uint16_t val = 100;
    datum = val;
    float f = datum.toFloat(0);
    EXPECT_FLOAT_EQ(f, 100.0f);
}

// Test toRational
TEST_F(IptcdatumTest_673, ToRationalWithUint16Value_673) {
    IptcKey key(0, 1);
    Iptcdatum datum(key, nullptr);
    uint16_t val = 50;
    datum = val;
    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, 50);
    EXPECT_EQ(r.second, 1);
}

// Test boundary: tag 0 and record 0
TEST_F(IptcdatumTest_673, BoundaryTagZeroRecordZero_673) {
    IptcKey key(0, 0);
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), 0);
    EXPECT_EQ(datum.record(), 0);
}

// Test boundary: maximum uint16_t values
TEST_F(IptcdatumTest_673, BoundaryMaxUint16Tag_673) {
    IptcKey key(65535, 65535);
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), 65535);
    EXPECT_EQ(datum.record(), 65535);
}

// Test setValue with nullptr resets value
TEST_F(IptcdatumTest_673, SetValueNullptr_673) {
    IptcKey key(120, 2);
    Iptcdatum datum(key, nullptr);
    datum = std::string("SomeValue");
    EXPECT_GT(datum.count(), 0u);
    datum.setValue(nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test self-assignment
TEST_F(IptcdatumTest_673, SelfAssignment_673) {
    IptcKey key(120, 2);
    Iptcdatum datum(key, nullptr);
    datum = std::string("SelfAssign");
    datum = datum;
    EXPECT_EQ(datum.toString(), "SelfAssign");
    EXPECT_EQ(datum.tag(), 120);
}

// Test constructing with a Value pointer
TEST_F(IptcdatumTest_673, ConstructWithValuePointer_673) {
    IptcKey key(120, 2);
    StringValue val("InitialValue");
    Iptcdatum datum(key, &val);
    EXPECT_EQ(datum.toString(), "InitialValue");
    EXPECT_EQ(datum.count(), 1u);
}

// Test empty string assignment
TEST_F(IptcdatumTest_673, EmptyStringAssignment_673) {
    IptcKey key(120, 2);
    Iptcdatum datum(key, nullptr);
    datum = std::string("");
    EXPECT_EQ(datum.toString(), "");
    EXPECT_EQ(datum.size(), 0u);
}

// Test typeName when value is set
TEST_F(IptcdatumTest_673, TypeNameWithStringValue_673) {
    IptcKey key(120, 2);
    Iptcdatum datum(key, nullptr);
    datum = std::string("TypeTest");
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
    // String type should be "String"
    EXPECT_STREQ(tn, "String");
}

// Test typeSize with string value
TEST_F(IptcdatumTest_673, TypeSizeWithStringValue_673) {
    IptcKey key(120, 2);
    Iptcdatum datum(key, nullptr);
    datum = std::string("SizeTest");
    size_t ts = datum.typeSize();
    EXPECT_EQ(ts, 1u);  // String type has typeSize of 1
}
