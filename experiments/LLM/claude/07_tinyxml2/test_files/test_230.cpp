#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementInt64AttributeTest_230 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that Int64Attribute returns the attribute value when attribute exists
TEST_F(XMLElementInt64AttributeTest_230, ReturnsAttributeValue_WhenAttributeExists_230) {
    doc.Parse("<root val=\"12345678901234\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t result = elem->Int64Attribute("val", 0);
    EXPECT_EQ(result, 12345678901234LL);
}

// Test that Int64Attribute returns default value when attribute does not exist
TEST_F(XMLElementInt64AttributeTest_230, ReturnsDefaultValue_WhenAttributeDoesNotExist_230) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t result = elem->Int64Attribute("nonexistent", 42);
    EXPECT_EQ(result, 42);
}

// Test that Int64Attribute returns default value when attribute name is different
TEST_F(XMLElementInt64AttributeTest_230, ReturnsDefaultValue_WhenDifferentAttributeName_230) {
    doc.Parse("<root other=\"100\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t result = elem->Int64Attribute("val", -1);
    EXPECT_EQ(result, -1);
}

// Test with a negative int64 attribute value
TEST_F(XMLElementInt64AttributeTest_230, ReturnsNegativeValue_WhenAttributeIsNegative_230) {
    doc.Parse("<root val=\"-9876543210\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t result = elem->Int64Attribute("val", 0);
    EXPECT_EQ(result, -9876543210LL);
}

// Test with zero attribute value
TEST_F(XMLElementInt64AttributeTest_230, ReturnsZero_WhenAttributeIsZero_230) {
    doc.Parse("<root val=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t result = elem->Int64Attribute("val", 999);
    EXPECT_EQ(result, 0);
}

// Test with large positive int64 value
TEST_F(XMLElementInt64AttributeTest_230, ReturnsLargePositiveValue_230) {
    doc.Parse("<root val=\"9223372036854775807\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t result = elem->Int64Attribute("val", 0);
    EXPECT_EQ(result, INT64_MAX);
}

// Test with large negative int64 value
TEST_F(XMLElementInt64AttributeTest_230, ReturnsLargeNegativeValue_230) {
    doc.Parse("<root val=\"-9223372036854775808\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t result = elem->Int64Attribute("val", 0);
    EXPECT_EQ(result, INT64_MIN);
}

// Test with non-numeric attribute value — should return default
TEST_F(XMLElementInt64AttributeTest_230, ReturnsDefaultValue_WhenAttributeIsNotNumeric_230) {
    doc.Parse("<root val=\"abc\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t result = elem->Int64Attribute("val", -5);
    EXPECT_EQ(result, -5);
}

// Test with empty attribute value — should return default
TEST_F(XMLElementInt64AttributeTest_230, ReturnsDefaultValue_WhenAttributeIsEmpty_230) {
    doc.Parse("<root val=\"\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t result = elem->Int64Attribute("val", 77);
    EXPECT_EQ(result, 77);
}

// Test with default value of zero
TEST_F(XMLElementInt64AttributeTest_230, DefaultValueZero_WhenAttributeMissing_230) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t result = elem->Int64Attribute("missing", 0);
    EXPECT_EQ(result, 0);
}

// Test with multiple attributes, querying one
TEST_F(XMLElementInt64AttributeTest_230, ReturnsCorrectValue_WhenMultipleAttributes_230) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->Int64Attribute("a", 0), 1);
    EXPECT_EQ(elem->Int64Attribute("b", 0), 2);
    EXPECT_EQ(elem->Int64Attribute("c", 0), 3);
}

// Test with attribute set programmatically
TEST_F(XMLElementInt64AttributeTest_230, ReturnsValue_WhenAttributeSetProgrammatically_230) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("myattr", (int64_t)1234567890123LL);

    int64_t result = elem->Int64Attribute("myattr", 0);
    EXPECT_EQ(result, 1234567890123LL);
}

// Test default value is negative
TEST_F(XMLElementInt64AttributeTest_230, ReturnsNegativeDefault_WhenAttributeMissing_230) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t result = elem->Int64Attribute("nope", -999999999999LL);
    EXPECT_EQ(result, -999999999999LL);
}

// Test with attribute value that has leading/trailing spaces (implementation dependent)
TEST_F(XMLElementInt64AttributeTest_230, HandlesWhitespaceInValue_230) {
    doc.Parse("<root val=\" 123 \"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    // Behavior depends on implementation; the value might parse or return default
    int64_t result = elem->Int64Attribute("val", -1);
    // We just verify it doesn't crash; the exact result depends on parser behavior
    (void)result;
}

// Test that querying after deleting attribute returns default
TEST_F(XMLElementInt64AttributeTest_230, ReturnsDefault_AfterAttributeDeleted_230) {
    doc.Parse("<root val=\"500\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->Int64Attribute("val", 0), 500);
    elem->DeleteAttribute("val");
    EXPECT_EQ(elem->Int64Attribute("val", -1), -1);
}

// Test with a value of 1
TEST_F(XMLElementInt64AttributeTest_230, ReturnsOne_WhenAttributeIsOne_230) {
    doc.Parse("<root val=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t result = elem->Int64Attribute("val", 0);
    EXPECT_EQ(result, 1);
}

// Test with a value of -1
TEST_F(XMLElementInt64AttributeTest_230, ReturnsNegativeOne_WhenAttributeIsNegativeOne_230) {
    doc.Parse("<root val=\"-1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t result = elem->Int64Attribute("val", 0);
    EXPECT_EQ(result, -1);
}
