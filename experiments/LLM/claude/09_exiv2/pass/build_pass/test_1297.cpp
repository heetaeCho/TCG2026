#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/error.hpp>
#include <exiv2/value.hpp>
#include <exiv2/properties.hpp>
#include <sstream>

namespace {

class XmpdatumTest_1297 : public ::testing::Test {
protected:
    void SetUp() override {
        // Register XMP namespaces if needed
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test constructing an Xmpdatum with a key and no value
TEST_F(XmpdatumTest_1297, ConstructWithKeyNoValue_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
    EXPECT_EQ(datum.familyName(), std::string("Xmp"));
    EXPECT_EQ(datum.groupName(), "dc");
    EXPECT_EQ(datum.tagName(), "title");
}

// Test that value() throws when no value is set
TEST_F(XmpdatumTest_1297, ValueThrowsWhenNotSet_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_THROW(datum.value(), Exiv2::Error);
}

// Test that value() throws the correct error code
TEST_F(XmpdatumTest_1297, ValueThrowsCorrectErrorCode_1297) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    try {
        datum.value();
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerValueNotSet);
    }
}

// Test constructing Xmpdatum with a value
TEST_F(XmpdatumTest_1297, ConstructWithKeyAndValue_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::XmpTextValue val("Test Title");
    Exiv2::Xmpdatum datum(key, &val);
    
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
    EXPECT_NO_THROW(datum.value());
    EXPECT_EQ(datum.toString(), "Test Title");
}

// Test copy constructor
TEST_F(XmpdatumTest_1297, CopyConstructor_1297) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::XmpTextValue val("A description");
    Exiv2::Xmpdatum original(key, &val);
    
    Exiv2::Xmpdatum copy(original);
    
    EXPECT_EQ(copy.key(), "Xmp.dc.description");
    EXPECT_EQ(copy.toString(), "A description");
}

// Test copy constructor with no value
TEST_F(XmpdatumTest_1297, CopyConstructorNoValue_1297) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    Exiv2::Xmpdatum original(key, nullptr);
    
    Exiv2::Xmpdatum copy(original);
    
    EXPECT_EQ(copy.key(), "Xmp.dc.subject");
    EXPECT_THROW(copy.value(), Exiv2::Error);
}

// Test assignment operator
TEST_F(XmpdatumTest_1297, AssignmentOperator_1297) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::XmpTextValue val1("Title 1");
    Exiv2::Xmpdatum datum1(key1, &val1);
    
    Exiv2::XmpKey key2("Xmp.dc.description");
    Exiv2::XmpTextValue val2("Desc 2");
    Exiv2::Xmpdatum datum2(key2, &val2);
    
    datum2 = datum1;
    
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
    EXPECT_EQ(datum2.toString(), "Title 1");
}

// Test setValue with a string
TEST_F(XmpdatumTest_1297, SetValueString_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    int result = datum.setValue("New Value");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "New Value");
}

// Test setValue with a Value pointer
TEST_F(XmpdatumTest_1297, SetValuePointer_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    Exiv2::XmpTextValue val("Pointer Value");
    datum.setValue(&val);
    
    EXPECT_NO_THROW(datum.value());
    EXPECT_EQ(datum.toString(), "Pointer Value");
}

// Test setValue with nullptr resets value
TEST_F(XmpdatumTest_1297, SetValueNullptrResetsValue_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::XmpTextValue val("Initial");
    Exiv2::Xmpdatum datum(key, &val);
    
    EXPECT_NO_THROW(datum.value());
    
    datum.setValue(static_cast<const Exiv2::Value*>(nullptr));
    
    EXPECT_THROW(datum.value(), Exiv2::Error);
}

// Test toString
TEST_F(XmpdatumTest_1297, ToString_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::XmpTextValue val("Hello World");
    Exiv2::Xmpdatum datum(key, &val);
    
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test toString with index
TEST_F(XmpdatumTest_1297, ToStringWithIndex_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::XmpTextValue val("Hello World");
    Exiv2::Xmpdatum datum(key, &val);
    
    EXPECT_EQ(datum.toString(0), "Hello World");
}

// Test count when value is set
TEST_F(XmpdatumTest_1297, CountWithValue_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::XmpTextValue val("Test");
    Exiv2::Xmpdatum datum(key, &val);
    
    EXPECT_GT(datum.count(), static_cast<size_t>(0));
}

// Test count when no value
TEST_F(XmpdatumTest_1297, CountWithoutValue_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.count(), static_cast<size_t>(0));
}

// Test size when no value
TEST_F(XmpdatumTest_1297, SizeWithoutValue_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.size(), static_cast<size_t>(0));
}

// Test getValue returns a valid unique_ptr when value is set
TEST_F(XmpdatumTest_1297, GetValueReturnsClone_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::XmpTextValue val("Cloned");
    Exiv2::Xmpdatum datum(key, &val);
    
    auto cloned = datum.getValue();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->toString(), "Cloned");
}

// Test getValue returns nullptr when value is not set
TEST_F(XmpdatumTest_1297, GetValueReturnsNullWhenNotSet_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    auto result = datum.getValue();
    EXPECT_EQ(result, nullptr);
}

// Test typeId when value is set
TEST_F(XmpdatumTest_1297, TypeIdWithValue_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::XmpTextValue val("Test");
    Exiv2::Xmpdatum datum(key, &val);
    
    EXPECT_EQ(datum.typeId(), Exiv2::xmpText);
}

// Test typeId when no value set
TEST_F(XmpdatumTest_1297, TypeIdWithoutValue_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.typeId(), Exiv2::invalidTypeId);
}

// Test familyName returns "Xmp"
TEST_F(XmpdatumTest_1297, FamilyName_1297) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_STREQ(datum.familyName(), "Xmp");
}

// Test write to output stream
TEST_F(XmpdatumTest_1297, WriteToStream_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::XmpTextValue val("Stream Test");
    Exiv2::Xmpdatum datum(key, &val);
    
    std::ostringstream oss;
    datum.write(oss, nullptr);
    
    EXPECT_FALSE(oss.str().empty());
}

// Test write to output stream with no value
TEST_F(XmpdatumTest_1297, WriteToStreamNoValue_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    std::ostringstream oss;
    datum.write(oss, nullptr);
    
    // Should handle gracefully (empty or some default output)
    // Just ensure no crash
    SUCCEED();
}

// Test template assignment operator with string
TEST_F(XmpdatumTest_1297, TemplateAssignmentString_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    datum = std::string("Assigned Value");
    
    EXPECT_EQ(datum.toString(), "Assigned Value");
}

// Test tag() returns a valid tag number
TEST_F(XmpdatumTest_1297, TagNumber_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    // Just ensure it doesn't throw and returns some value
    uint16_t tag = datum.tag();
    (void)tag;
    SUCCEED();
}

// Test tagLabel returns a non-empty string for known properties
TEST_F(XmpdatumTest_1297, TagLabel_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    std::string label = datum.tagLabel();
    // For known XMP properties, label should be non-empty
    EXPECT_FALSE(label.empty());
}

// Test copy method
TEST_F(XmpdatumTest_1297, CopyMethod_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::XmpTextValue val("Copy Test");
    Exiv2::Xmpdatum datum(key, &val);
    
    // copy for XMP returns 0 (not implemented for XMP)
    Exiv2::byte buf[256];
    size_t result = datum.copy(buf, Exiv2::bigEndian);
    EXPECT_EQ(result, static_cast<size_t>(0));
}

// Test toInt64 with a numeric value
TEST_F(XmpdatumTest_1297, ToInt64_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::XmpTextValue val("42");
    Exiv2::Xmpdatum datum(key, &val);
    
    EXPECT_EQ(datum.toInt64(0), 42);
}

// Test toFloat with a numeric value
TEST_F(XmpdatumTest_1297, ToFloat_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::XmpTextValue val("3.14");
    Exiv2::Xmpdatum datum(key, &val);
    
    EXPECT_NEAR(datum.toFloat(0), 3.14f, 0.01f);
}

// Test overwriting value with setValue string
TEST_F(XmpdatumTest_1297, OverwriteValue_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::XmpTextValue val("Original");
    Exiv2::Xmpdatum datum(key, &val);
    
    EXPECT_EQ(datum.toString(), "Original");
    
    datum.setValue("Updated");
    EXPECT_EQ(datum.toString(), "Updated");
}

// Test groupName
TEST_F(XmpdatumTest_1297, GroupName_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.groupName(), "dc");
}

// Test tagName
TEST_F(XmpdatumTest_1297, TagName_1297) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.tagName(), "title");
}

// Test with different XMP namespaces
TEST_F(XmpdatumTest_1297, DifferentNamespace_1297) {
    Exiv2::XmpKey key("Xmp.xmp.CreateDate");
    Exiv2::XmpTextValue val("2023-01-01");
    Exiv2::Xmpdatum datum(key, &val);
    
    EXPECT_EQ(datum.groupName(), "xmp");
    EXPECT_EQ(datum.tagName(), "CreateDate");
    EXPECT_EQ(datum.toString(), "2023-01-01");
}

} // namespace
