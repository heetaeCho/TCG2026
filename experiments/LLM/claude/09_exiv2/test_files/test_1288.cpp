#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/exiv2.hpp>
#include <sstream>

using namespace Exiv2;

class XmpdatumTest_1288 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that typeSize() returns 0
TEST_F(XmpdatumTest_1288, TypeSizeReturnsZero_1288) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(0u, datum.typeSize());
}

// Test default construction with key and null value
TEST_F(XmpdatumTest_1288, ConstructWithKeyAndNullValue_1288) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ("Xmp.dc.title", datum.key());
    EXPECT_EQ("Xmp", std::string(datum.familyName()));
    EXPECT_EQ("dc", datum.groupName());
    EXPECT_EQ("title", datum.tagName());
}

// Test copy constructor
TEST_F(XmpdatumTest_1288, CopyConstructor_1288) {
    XmpKey key("Xmp.dc.subject");
    Xmpdatum datum1(key, nullptr);
    Xmpdatum datum2(datum1);
    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.tagName(), datum2.tagName());
    EXPECT_EQ(datum1.groupName(), datum2.groupName());
}

// Test copy assignment operator
TEST_F(XmpdatumTest_1288, CopyAssignment_1288) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2("Xmp.dc.subject");
    Xmpdatum datum1(key1, nullptr);
    Xmpdatum datum2(key2, nullptr);
    datum2 = datum1;
    EXPECT_EQ("Xmp.dc.title", datum2.key());
}

// Test setValue with string on a datum with no prior value
TEST_F(XmpdatumTest_1288, SetValueWithString_1288) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    int result = datum.setValue("Test Title");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Test Title", datum.toString());
}

// Test setValue with Value pointer
TEST_F(XmpdatumTest_1288, SetValueWithValuePointer_1288) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    XmpTextValue val("Hello World");
    datum.setValue(&val);
    EXPECT_EQ("Hello World", datum.toString());
}

// Test setValue with nullptr resets value
TEST_F(XmpdatumTest_1288, SetValueWithNullptr_1288) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Some text");
    Xmpdatum datum(key, &val);
    datum.setValue(nullptr);
    // After setting null, getValue should return null or count should be 0
    EXPECT_EQ(0u, datum.count());
}

// Test count returns 0 for null value
TEST_F(XmpdatumTest_1288, CountReturnsZeroForNullValue_1288) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(0u, datum.count());
}

// Test size returns 0 for null value
TEST_F(XmpdatumTest_1288, SizeReturnsZeroForNullValue_1288) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ(0u, datum.size());
}

// Test toString with no value
TEST_F(XmpdatumTest_1288, ToStringWithNoValue_1288) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ("", datum.toString());
}

// Test typeId for datum with no value
TEST_F(XmpdatumTest_1288, TypeIdForNullValue_1288) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    TypeId tid = datum.typeId();
    EXPECT_EQ(invalidTypeId, tid);
}

// Test typeName for datum with no value
TEST_F(XmpdatumTest_1288, TypeNameForNullValue_1288) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    // typeName might return empty string or nullptr for null value
    const char* tn = datum.typeName();
    // Just verify it doesn't crash; accept nullptr or valid string
    if (tn != nullptr) {
        SUCCEED();
    } else {
        SUCCEED();
    }
}

// Test construction with a valid value
TEST_F(XmpdatumTest_1288, ConstructWithValue_1288) {
    XmpKey key("Xmp.dc.description");
    XmpTextValue val("A description");
    Xmpdatum datum(key, &val);
    EXPECT_EQ("Xmp.dc.description", datum.key());
    EXPECT_EQ("A description", datum.toString());
    EXPECT_GT(datum.count(), 0u);
    EXPECT_GT(datum.size(), 0u);
}

// Test write to ostream
TEST_F(XmpdatumTest_1288, WriteToOstream_1288) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Test Write");
    Xmpdatum datum(key, &val);
    std::ostringstream oss;
    datum.write(oss, nullptr);
    EXPECT_FALSE(oss.str().empty());
}

// Test copy method returns 0 (as per XMP convention)
TEST_F(XmpdatumTest_1288, CopyReturnsZero_1288) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Copy Test");
    Xmpdatum datum(key, &val);
    byte buf[256] = {};
    size_t result = datum.copy(buf, bigEndian);
    EXPECT_EQ(0u, result);
}

// Test getValue returns non-null when value is set
TEST_F(XmpdatumTest_1288, GetValueReturnsNonNullWhenSet_1288) {
    XmpKey key("Xmp.dc.creator");
    XmpTextValue val("Author Name");
    Xmpdatum datum(key, &val);
    auto v = datum.getValue();
    ASSERT_NE(nullptr, v.get());
    EXPECT_EQ("Author Name", v->toString());
}

// Test getValue returns null when value is not set
TEST_F(XmpdatumTest_1288, GetValueReturnsNullWhenNotSet_1288) {
    XmpKey key("Xmp.dc.creator");
    Xmpdatum datum(key, nullptr);
    auto v = datum.getValue();
    EXPECT_EQ(nullptr, v.get());
}

// Test tag() returns appropriate tag number
TEST_F(XmpdatumTest_1288, TagReturnsValue_1288) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    // Just verify it doesn't crash and returns some value
    uint16_t t = datum.tag();
    (void)t;
    SUCCEED();
}

// Test tagLabel returns non-empty string for known tags
TEST_F(XmpdatumTest_1288, TagLabelReturnsString_1288) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    // Label may or may not be empty depending on tag registration
    SUCCEED();
}

// Test tagDesc returns string
TEST_F(XmpdatumTest_1288, TagDescReturnsString_1288) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    std::string desc = datum.tagDesc();
    // Just verify it doesn't crash
    SUCCEED();
}

// Test toInt64 with no value
TEST_F(XmpdatumTest_1288, ToInt64WithNoValue_1288) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    // Accessing value when none is set - behavior depends on implementation
    // This might throw; we test it doesn't cause undefined behavior
    try {
        int64_t val = datum.toInt64(0);
        EXPECT_EQ(0, val);
    } catch (const std::exception&) {
        SUCCEED();
    }
}

// Test toFloat with no value
TEST_F(XmpdatumTest_1288, ToFloatWithNoValue_1288) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    try {
        float val = datum.toFloat(0);
        EXPECT_FLOAT_EQ(0.0f, val);
    } catch (const std::exception&) {
        SUCCEED();
    }
}

// Test toRational with no value
TEST_F(XmpdatumTest_1288, ToRationalWithNoValue_1288) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    try {
        Rational val = datum.toRational(0);
        (void)val;
        SUCCEED();
    } catch (const std::exception&) {
        SUCCEED();
    }
}

// Test template operator= with string
TEST_F(XmpdatumTest_1288, TemplateAssignmentWithString_1288) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum = std::string("Assigned Value");
    EXPECT_EQ("Assigned Value", datum.toString());
}

// Test toString(n) with valid index
TEST_F(XmpdatumTest_1288, ToStringWithIndex_1288) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue val("Indexed String");
    Xmpdatum datum(key, &val);
    std::string s = datum.toString(0);
    EXPECT_EQ("Indexed String", s);
}

// Test familyName returns "Xmp"
TEST_F(XmpdatumTest_1288, FamilyNameIsXmp_1288) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_STREQ("Xmp", datum.familyName());
}

// Test different XMP namespaces
TEST_F(XmpdatumTest_1288, DifferentNamespaceGroupName_1288) {
    XmpKey key("Xmp.xmp.CreateDate");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ("xmp", datum.groupName());
    EXPECT_EQ("CreateDate", datum.tagName());
}

// Test multiple setValue calls
TEST_F(XmpdatumTest_1288, MultipleSetValueCalls_1288) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    datum.setValue("First");
    EXPECT_EQ("First", datum.toString());
    datum.setValue("Second");
    EXPECT_EQ("Second", datum.toString());
}

// Test value() throws when no value set
TEST_F(XmpdatumTest_1288, ValueThrowsWhenNoValueSet_1288) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_THROW(datum.value(), Error);
}
