#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementUnsigned64AttributeTest_231 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test that when the attribute exists with a valid uint64 value, it returns that value
TEST_F(XMLElementUnsigned64AttributeTest_231, ReturnsAttributeValueWhenPresent_231) {
    doc.Parse("<root val=\"12345\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    uint64_t result = elem->Unsigned64Attribute("val", 0);
    EXPECT_EQ(result, 12345ULL);
}

// Test that when the attribute does not exist, it returns the default value
TEST_F(XMLElementUnsigned64AttributeTest_231, ReturnsDefaultValueWhenAttributeMissing_231) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    uint64_t result = elem->Unsigned64Attribute("nonexistent", 99999ULL);
    EXPECT_EQ(result, 99999ULL);
}

// Test with default value of 0 when attribute is missing
TEST_F(XMLElementUnsigned64AttributeTest_231, ReturnsDefaultZeroWhenAttributeMissing_231) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    uint64_t result = elem->Unsigned64Attribute("missing", 0);
    EXPECT_EQ(result, 0ULL);
}

// Test with a very large uint64 value
TEST_F(XMLElementUnsigned64AttributeTest_231, HandlesLargeUint64Value_231) {
    doc.Parse("<root val=\"18446744073709551615\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    uint64_t result = elem->Unsigned64Attribute("val", 0);
    EXPECT_EQ(result, UINT64_MAX);
}

// Test with zero value attribute
TEST_F(XMLElementUnsigned64AttributeTest_231, HandlesZeroValue_231) {
    doc.Parse("<root val=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    uint64_t result = elem->Unsigned64Attribute("val", 42);
    EXPECT_EQ(result, 0ULL);
}

// Test with non-numeric attribute value returns default
TEST_F(XMLElementUnsigned64AttributeTest_231, ReturnsDefaultForNonNumericAttribute_231) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    uint64_t result = elem->Unsigned64Attribute("val", 777ULL);
    EXPECT_EQ(result, 777ULL);
}

// Test with multiple attributes, retrieving the correct one
TEST_F(XMLElementUnsigned64AttributeTest_231, RetrievesCorrectAttributeAmongMultiple_231) {
    doc.Parse("<root a=\"100\" b=\"200\" c=\"300\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_EQ(elem->Unsigned64Attribute("a", 0), 100ULL);
    EXPECT_EQ(elem->Unsigned64Attribute("b", 0), 200ULL);
    EXPECT_EQ(elem->Unsigned64Attribute("c", 0), 300ULL);
}

// Test with a large default value when attribute is missing
TEST_F(XMLElementUnsigned64AttributeTest_231, ReturnsLargeDefaultWhenMissing_231) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    uint64_t result = elem->Unsigned64Attribute("missing", UINT64_MAX);
    EXPECT_EQ(result, UINT64_MAX);
}

// Test with attribute set programmatically
TEST_F(XMLElementUnsigned64AttributeTest_231, WorksWithSetAttribute_231) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetAttribute("myattr", (uint64_t)987654321ULL);
    uint64_t result = elem->Unsigned64Attribute("myattr", 0);
    EXPECT_EQ(result, 987654321ULL);
}

// Test with empty attribute value returns default
TEST_F(XMLElementUnsigned64AttributeTest_231, ReturnsDefaultForEmptyAttribute_231) {
    doc.Parse("<root val=\"\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    uint64_t result = elem->Unsigned64Attribute("val", 555ULL);
    EXPECT_EQ(result, 555ULL);
}

// Test with value 1
TEST_F(XMLElementUnsigned64AttributeTest_231, HandlesValueOne_231) {
    doc.Parse("<root val=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    uint64_t result = elem->Unsigned64Attribute("val", 0);
    EXPECT_EQ(result, 1ULL);
}

// Test that the correct attribute name is matched (case-sensitive)
TEST_F(XMLElementUnsigned64AttributeTest_231, AttributeNameIsCaseSensitive_231) {
    doc.Parse("<root Val=\"100\" val=\"200\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_EQ(elem->Unsigned64Attribute("Val", 0), 100ULL);
    EXPECT_EQ(elem->Unsigned64Attribute("val", 0), 200ULL);
    EXPECT_EQ(elem->Unsigned64Attribute("VAL", 50), 50ULL);
}

// Test with attribute containing whitespace around the number
TEST_F(XMLElementUnsigned64AttributeTest_231, HandlesWhitespaceInAttribute_231) {
    doc.Parse("<root val=\" 42 \"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    // Behavior depends on implementation; just verify it doesn't crash
    uint64_t result = elem->Unsigned64Attribute("val", 0);
    // The result might be 42 or default depending on parsing behavior
    (void)result;
}

// Test with programmatically set large uint64 value
TEST_F(XMLElementUnsigned64AttributeTest_231, SetAndGetMaxUint64_231) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetAttribute("big", (uint64_t)UINT64_MAX);
    uint64_t result = elem->Unsigned64Attribute("big", 0);
    EXPECT_EQ(result, UINT64_MAX);
}

// Test that querying a different attribute name returns default
TEST_F(XMLElementUnsigned64AttributeTest_231, WrongNameReturnsDefault_231) {
    doc.Parse("<root foo=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    uint64_t result = elem->Unsigned64Attribute("bar", 123ULL);
    EXPECT_EQ(result, 123ULL);
}
