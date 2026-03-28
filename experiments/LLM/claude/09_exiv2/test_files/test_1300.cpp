#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>
#include <memory>

using namespace Exiv2;

class XmpdatumTest_1300 : public ::testing::Test {
protected:
    void SetUp() override {
        // Enable XMP support
        XmpParser::initialize();
    }

    void TearDown() override {
        XmpParser::terminate();
    }
};

// Test construction with key and null value
TEST_F(XmpdatumTest_1300, ConstructWithKeyAndNullValue_1300) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    EXPECT_EQ("Xmp.dc.title", datum.key());
    EXPECT_EQ("Xmp", std::string(datum.familyName()));
    EXPECT_EQ("dc", datum.groupName());
    EXPECT_EQ("title", datum.tagName());
}

// Test construction with key and a value
TEST_F(XmpdatumTest_1300, ConstructWithKeyAndValue_1300) {
    XmpKey key("Xmp.dc.subject");
    XmpTextValue val("TestSubject");
    Xmpdatum datum(key, &val);

    EXPECT_EQ("Xmp.dc.subject", datum.key());
    EXPECT_EQ("TestSubject", datum.toString());
}

// Test copy constructor
TEST_F(XmpdatumTest_1300, CopyConstructor_1300) {
    XmpKey key("Xmp.dc.description");
    XmpTextValue val("A description");
    Xmpdatum original(key, &val);
    Xmpdatum copy(original);

    EXPECT_EQ(original.key(), copy.key());
    EXPECT_EQ(original.toString(), copy.toString());
}

// Test assignment operator
TEST_F(XmpdatumTest_1300, AssignmentOperator_1300) {
    XmpKey key1("Xmp.dc.title");
    XmpTextValue val1("Title1");
    Xmpdatum datum1(key1, &val1);

    XmpKey key2("Xmp.dc.description");
    XmpTextValue val2("Desc2");
    Xmpdatum datum2(key2, &val2);

    datum2 = datum1;
    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
}

// Test setValue with pointer to Value
TEST_F(XmpdatumTest_1300, SetValueWithPointer_1300) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    XmpTextValue val("NewTitle");
    datum.setValue(&val);

    EXPECT_EQ("NewTitle", datum.toString());
}

// Test setValue with nullptr resets value
TEST_F(XmpdatumTest_1300, SetValueWithNullptrResetsValue_1300) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("InitialValue");
    Xmpdatum datum(key, &val);

    EXPECT_EQ("InitialValue", datum.toString());

    datum.setValue(static_cast<const Value*>(nullptr));

    // After setting to null, count should be 0
    EXPECT_EQ(0u, datum.count());
}

// Test setValue with string
TEST_F(XmpdatumTest_1300, SetValueWithString_1300) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("OldValue");
    Xmpdatum datum(key, &val);

    int result = datum.setValue("NewStringValue");
    EXPECT_EQ(0, result);
    EXPECT_EQ("NewStringValue", datum.toString());
}

// Test key components
TEST_F(XmpdatumTest_1300, KeyComponents_1300) {
    XmpKey key("Xmp.dc.creator");
    Xmpdatum datum(key, nullptr);

    EXPECT_EQ("Xmp.dc.creator", datum.key());
    EXPECT_STREQ("Xmp", datum.familyName());
    EXPECT_EQ("dc", datum.groupName());
    EXPECT_EQ("creator", datum.tagName());
}

// Test tagLabel returns a non-empty string for known properties
TEST_F(XmpdatumTest_1300, TagLabelReturnsValue_1300) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    std::string label = datum.tagLabel();
    // tagLabel should return something (may be empty for unknown props, but "title" is well known)
    EXPECT_FALSE(label.empty());
}

// Test typeId for XmpTextValue
TEST_F(XmpdatumTest_1300, TypeIdForXmpTextValue_1300) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Test");
    Xmpdatum datum(key, &val);

    EXPECT_EQ(xmpText, datum.typeId());
}

// Test typeName for XmpTextValue
TEST_F(XmpdatumTest_1300, TypeNameForXmpTextValue_1300) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Test");
    Xmpdatum datum(key, &val);

    const char* tn = datum.typeName();
    ASSERT_NE(nullptr, tn);
    EXPECT_EQ(std::string("XmpText"), std::string(tn));
}

// Test count for a single XmpTextValue
TEST_F(XmpdatumTest_1300, CountForSingleValue_1300) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("SingleValue");
    Xmpdatum datum(key, &val);

    EXPECT_EQ(1u, datum.count());
}

// Test size for XmpTextValue
TEST_F(XmpdatumTest_1300, SizeForXmpTextValue_1300) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Hello");
    Xmpdatum datum(key, &val);

    EXPECT_EQ(5u, datum.size());
}

// Test toString with index
TEST_F(XmpdatumTest_1300, ToStringWithIndex_1300) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("IndexedValue");
    Xmpdatum datum(key, &val);

    EXPECT_EQ("IndexedValue", datum.toString(0));
}

// Test getValue returns a clone
TEST_F(XmpdatumTest_1300, GetValueReturnsClone_1300) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("CloneTest");
    Xmpdatum datum(key, &val);

    auto clonedValue = datum.getValue();
    ASSERT_NE(nullptr, clonedValue);
    EXPECT_EQ("CloneTest", clonedValue->toString());
}

// Test value() reference
TEST_F(XmpdatumTest_1300, ValueReferenceAccess_1300) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("RefTest");
    Xmpdatum datum(key, &val);

    const Value& v = datum.value();
    EXPECT_EQ("RefTest", v.toString());
}

// Test value() throws when no value is set
TEST_F(XmpdatumTest_1300, ValueThrowsWhenNoValue_1300) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    EXPECT_THROW(datum.value(), Error);
}

// Test write to ostream
TEST_F(XmpdatumTest_1300, WriteToOstream_1300) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("WriteTest");
    Xmpdatum datum(key, &val);

    std::ostringstream oss;
    datum.write(oss, nullptr);
    EXPECT_FALSE(oss.str().empty());
    EXPECT_NE(std::string::npos, oss.str().find("WriteTest"));
}

// Test setValue replaces existing value
TEST_F(XmpdatumTest_1300, SetValueReplacesExisting_1300) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val1("First");
    Xmpdatum datum(key, &val1);
    EXPECT_EQ("First", datum.toString());

    XmpTextValue val2("Second");
    datum.setValue(&val2);
    EXPECT_EQ("Second", datum.toString());
}

// Test template assignment operator with string
TEST_F(XmpdatumTest_1300, TemplateAssignmentWithString_1300) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Initial");
    Xmpdatum datum(key, &val);

    datum = std::string("Assigned");
    EXPECT_EQ("Assigned", datum.toString());
}

// Test copy does not return error for null-value datum
TEST_F(XmpdatumTest_1300, CopyWithNullBuffer_1300) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    // copy with null value should return 0
    size_t copied = datum.copy(nullptr, bigEndian);
    EXPECT_EQ(0u, copied);
}

// Test empty string value
TEST_F(XmpdatumTest_1300, EmptyStringValue_1300) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("");
    Xmpdatum datum(key, &val);

    EXPECT_EQ("", datum.toString());
    EXPECT_EQ(0u, datum.size());
}

// Test count when no value set
TEST_F(XmpdatumTest_1300, CountWhenNoValueSet_1300) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    EXPECT_EQ(0u, datum.count());
}

// Test size when no value set
TEST_F(XmpdatumTest_1300, SizeWhenNoValueSet_1300) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    EXPECT_EQ(0u, datum.size());
}

// Test typeId when no value set
TEST_F(XmpdatumTest_1300, TypeIdWhenNoValueSet_1300) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    // With no value, typeId should be invalidTypeId or some default
    TypeId tid = datum.typeId();
    EXPECT_EQ(invalidTypeId, tid);
}

// Test getValue returns null when no value set
TEST_F(XmpdatumTest_1300, GetValueReturnsNullWhenNoValue_1300) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);

    auto v = datum.getValue();
    EXPECT_EQ(nullptr, v);
}

// Test setting value then clearing with nullptr
TEST_F(XmpdatumTest_1300, SetThenClearValue_1300) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("TempValue");
    Xmpdatum datum(key, &val);

    EXPECT_EQ("TempValue", datum.toString());
    EXPECT_EQ(1u, datum.count());

    datum.setValue(static_cast<const Value*>(nullptr));
    EXPECT_EQ(0u, datum.count());
    EXPECT_EQ(nullptr, datum.getValue());
}

// Test self-assignment
TEST_F(XmpdatumTest_1300, SelfAssignment_1300) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("SelfAssign");
    Xmpdatum datum(key, &val);

    datum = datum;
    EXPECT_EQ("SelfAssign", datum.toString());
    EXPECT_EQ("Xmp.dc.title", datum.key());
}

// Test with different XMP namespaces
TEST_F(XmpdatumTest_1300, DifferentNamespaces_1300) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2("Xmp.xmp.CreateDate");

    Xmpdatum datum1(key1, nullptr);
    Xmpdatum datum2(key2, nullptr);

    EXPECT_EQ("dc", datum1.groupName());
    EXPECT_EQ("xmp", datum2.groupName());
    EXPECT_EQ("title", datum1.tagName());
    EXPECT_EQ("CreateDate", datum2.tagName());
}

// Test toInt64 with numeric string value
TEST_F(XmpdatumTest_1300, ToInt64WithNumericValue_1300) {
    XmpKey key("Xmp.xmp.Rating");
    XmpTextValue val("42");
    Xmpdatum datum(key, &val);

    EXPECT_EQ(42, datum.toInt64(0));
}

// Test toFloat with float string value
TEST_F(XmpdatumTest_1300, ToFloatWithFloatValue_1300) {
    XmpKey key("Xmp.xmp.Rating");
    XmpTextValue val("3.14");
    Xmpdatum datum(key, &val);

    EXPECT_NEAR(3.14f, datum.toFloat(0), 0.01f);
}
