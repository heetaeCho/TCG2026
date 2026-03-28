#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>
#include <memory>

using namespace Exiv2;

class XmpdatumTest_1286 : public ::testing::Test {
protected:
    void SetUp() override {
        // XMP properties need to be registered
        XmpParser::initialize();
    }

    void TearDown() override {
        XmpParser::terminate();
    }
};

// Test that typeId returns invalidTypeId when no value is set
TEST_F(XmpdatumTest_1286, TypeIdReturnsInvalidWhenNoValue_1286) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.typeId(), invalidTypeId);
}

// Test that typeId returns correct type when a value is set
TEST_F(XmpdatumTest_1286, TypeIdReturnsCorrectTypeWhenValueSet_1286) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("test string");
    // After setting a value via string, typeId should not be invalidTypeId
    EXPECT_NE(datum.typeId(), invalidTypeId);
}

// Test construction with a key and null value
TEST_F(XmpdatumTest_1286, ConstructWithKeyAndNullValue_1286) {
    XmpKey key("Xmp.dc.subject");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Xmp.dc.subject");
    EXPECT_EQ(datum.typeId(), invalidTypeId);
}

// Test construction with a key and actual value
TEST_F(XmpdatumTest_1286, ConstructWithKeyAndValue_1286) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("Hello World");
    Xmpdatum datum(key, value.get());
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
    EXPECT_EQ(datum.typeId(), xmpText);
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test copy constructor
TEST_F(XmpdatumTest_1286, CopyConstructor_1286) {
    XmpKey key("Xmp.dc.creator");
    auto value = Value::create(xmpText);
    value->read("Author Name");
    Xmpdatum original(key, value.get());
    Xmpdatum copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.typeId(), original.typeId());
    EXPECT_EQ(copy.toString(), original.toString());
}

// Test assignment operator
TEST_F(XmpdatumTest_1286, AssignmentOperator_1286) {
    XmpKey key1("Xmp.dc.title");
    auto val1 = Value::create(xmpText);
    val1->read("First");
    Xmpdatum datum1(key1, val1.get());

    XmpKey key2("Xmp.dc.creator");
    auto val2 = Value::create(xmpText);
    val2->read("Second");
    Xmpdatum datum2(key2, val2.get());

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
    EXPECT_EQ(datum2.toString(), "First");
}

// Test key() method
TEST_F(XmpdatumTest_1286, KeyReturnsCorrectKey_1286) {
    XmpKey key("Xmp.dc.description");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Xmp.dc.description");
}

// Test familyName() method
TEST_F(XmpdatumTest_1286, FamilyNameReturnsXmp_1286) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    std::string family = datum.familyName();
    EXPECT_EQ(family, "Xmp");
}

// Test groupName() method
TEST_F(XmpdatumTest_1286, GroupNameReturnsCorrectGroup_1286) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "dc");
}

// Test tagName() method
TEST_F(XmpdatumTest_1286, TagNameReturnsCorrectTag_1286) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "title");
}

// Test count() when no value is set
TEST_F(XmpdatumTest_1286, CountWhenNoValue_1286) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test size() when no value is set
TEST_F(XmpdatumTest_1286, SizeWhenNoValue_1286) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test setValue with a string
TEST_F(XmpdatumTest_1286, SetValueWithString_1286) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    int result = datum.setValue("Test Value");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Test Value");
}

// Test setValue with a Value pointer
TEST_F(XmpdatumTest_1286, SetValueWithPointer_1286) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    auto value = Value::create(xmpText);
    value->read("Pointer Value");
    datum.setValue(value.get());
    EXPECT_EQ(datum.toString(), "Pointer Value");
    EXPECT_EQ(datum.typeId(), xmpText);
}

// Test setValue with nullptr clears the value
TEST_F(XmpdatumTest_1286, SetValueWithNullptr_1286) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("Some Value");
    Xmpdatum datum(key, value.get());
    EXPECT_NE(datum.typeId(), invalidTypeId);
    datum.setValue(nullptr);
    EXPECT_EQ(datum.typeId(), invalidTypeId);
}

// Test getValue returns a valid unique_ptr when value is set
TEST_F(XmpdatumTest_1286, GetValueReturnsValidPtr_1286) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("GetValue Test");
    Xmpdatum datum(key, value.get());
    auto retrieved = datum.getValue();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toString(), "GetValue Test");
}

// Test getValue returns nullptr when no value is set
TEST_F(XmpdatumTest_1286, GetValueReturnsNullWhenNoValue_1286) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    auto retrieved = datum.getValue();
    EXPECT_EQ(retrieved, nullptr);
}

// Test write to ostream
TEST_F(XmpdatumTest_1286, WriteToOstream_1286) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("Write Test");
    Xmpdatum datum(key, value.get());
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test typeName returns valid name when value is set
TEST_F(XmpdatumTest_1286, TypeNameWhenValueSet_1286) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("TypeName Test");
    Xmpdatum datum(key, value.get());
    const char* name = datum.typeName();
    EXPECT_NE(name, nullptr);
}

// Test toString with index parameter
TEST_F(XmpdatumTest_1286, ToStringWithIndex_1286) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("Index Test");
    Xmpdatum datum(key, value.get());
    std::string result = datum.toString(0);
    EXPECT_EQ(result, "Index Test");
}

// Test template operator= with string
TEST_F(XmpdatumTest_1286, TemplateAssignmentString_1286) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum = std::string("Template Assign");
    EXPECT_EQ(datum.toString(), "Template Assign");
}

// Test that copy returns 0 when no value is set
TEST_F(XmpdatumTest_1286, CopyReturnsZeroWhenNoValue_1286) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    byte buf[256];
    size_t result = datum.copy(buf, littleEndian);
    EXPECT_EQ(result, 0u);
}

// Test with xmpBag type
TEST_F(XmpdatumTest_1286, XmpBagType_1286) {
    XmpKey key("Xmp.dc.subject");
    auto value = Value::create(xmpBag);
    value->read("tag1");
    Xmpdatum datum(key, value.get());
    EXPECT_EQ(datum.typeId(), xmpBag);
}

// Test with xmpSeq type
TEST_F(XmpdatumTest_1286, XmpSeqType_1286) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpSeq);
    value->read("item1");
    Xmpdatum datum(key, value.get());
    EXPECT_EQ(datum.typeId(), xmpSeq);
}

// Test with langAlt type
TEST_F(XmpdatumTest_1286, LangAltType_1286) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(langAlt);
    value->read("lang=\"x-default\" Test Title");
    Xmpdatum datum(key, value.get());
    EXPECT_EQ(datum.typeId(), langAlt);
}

// Test value() throws when no value is set
TEST_F(XmpdatumTest_1286, ValueThrowsWhenNoValueSet_1286) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_THROW(datum.value(), Error);
}

// Test tag() returns a valid tag number
TEST_F(XmpdatumTest_1286, TagReturnsValue_1286) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    // tag() should return some value; we just check it doesn't throw
    uint16_t tag = datum.tag();
    (void)tag; // Just verifying no exception
}

// Test count() when value is set
TEST_F(XmpdatumTest_1286, CountWhenValueSet_1286) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("Count Test");
    Xmpdatum datum(key, value.get());
    EXPECT_GE(datum.count(), 1u);
}

// Test size() when value is set
TEST_F(XmpdatumTest_1286, SizeWhenValueSet_1286) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("Size Test");
    Xmpdatum datum(key, value.get());
    EXPECT_GT(datum.size(), 0u);
}

// Test typeSize() when value is set
TEST_F(XmpdatumTest_1286, TypeSizeWhenValueSet_1286) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("TypeSize Test");
    Xmpdatum datum(key, value.get());
    size_t ts = datum.typeSize();
    (void)ts; // Just verify it doesn't throw
}

// Test that modifying the original after copy construction doesn't affect the copy
TEST_F(XmpdatumTest_1286, CopyConstructorIndependence_1286) {
    XmpKey key("Xmp.dc.title");
    auto value = Value::create(xmpText);
    value->read("Original");
    Xmpdatum original(key, value.get());
    Xmpdatum copy(original);

    original.setValue("Modified");
    EXPECT_EQ(copy.toString(), "Original");
    EXPECT_EQ(original.toString(), "Modified");
}
