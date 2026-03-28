#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementQueryInt64Attribute_83 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }
};

// Test: QueryInt64Attribute returns XML_NO_ATTRIBUTE when attribute does not exist
TEST_F(XMLElementQueryInt64Attribute_83, NonExistentAttribute_83) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t value = 0;
    XMLError result = elem->QueryInt64Attribute("nonexistent", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
}

// Test: QueryInt64Attribute returns XML_SUCCESS for a valid integer attribute
TEST_F(XMLElementQueryInt64Attribute_83, ValidInt64Attribute_83) {
    doc.Parse("<root myattr=\"12345\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t value = 0;
    XMLError result = elem->QueryInt64Attribute("myattr", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_EQ(value, 12345);
}

// Test: QueryInt64Attribute with a negative value
TEST_F(XMLElementQueryInt64Attribute_83, NegativeInt64Attribute_83) {
    doc.Parse("<root myattr=\"-9876543210\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t value = 0;
    XMLError result = elem->QueryInt64Attribute("myattr", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_EQ(value, -9876543210LL);
}

// Test: QueryInt64Attribute with zero
TEST_F(XMLElementQueryInt64Attribute_83, ZeroAttribute_83) {
    doc.Parse("<root myattr=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t value = -1;
    XMLError result = elem->QueryInt64Attribute("myattr", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_EQ(value, 0);
}

// Test: QueryInt64Attribute with a large positive int64 value
TEST_F(XMLElementQueryInt64Attribute_83, LargePositiveInt64_83) {
    doc.Parse("<root myattr=\"9223372036854775807\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t value = 0;
    XMLError result = elem->QueryInt64Attribute("myattr", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_EQ(value, INT64_MAX);
}

// Test: QueryInt64Attribute with the most negative int64 value
TEST_F(XMLElementQueryInt64Attribute_83, LargeNegativeInt64_83) {
    doc.Parse("<root myattr=\"-9223372036854775808\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t value = 0;
    XMLError result = elem->QueryInt64Attribute("myattr", &value);
    // This should either succeed or fail depending on implementation; 
    // we just check it doesn't crash. If success, check the value.
    if (result == XML_SUCCESS) {
        EXPECT_EQ(value, INT64_MIN);
    }
}

// Test: QueryInt64Attribute with non-numeric string returns error
TEST_F(XMLElementQueryInt64Attribute_83, NonNumericAttribute_83) {
    doc.Parse("<root myattr=\"notanumber\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t value = 42;
    XMLError result = elem->QueryInt64Attribute("myattr", &value);
    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: QueryInt64Attribute with empty string attribute
TEST_F(XMLElementQueryInt64Attribute_83, EmptyStringAttribute_83) {
    doc.Parse("<root myattr=\"\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t value = 42;
    XMLError result = elem->QueryInt64Attribute("myattr", &value);
    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: QueryInt64Attribute with floating point string
TEST_F(XMLElementQueryInt64Attribute_83, FloatingPointAttribute_83) {
    doc.Parse("<root myattr=\"3.14\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t value = 0;
    XMLError result = elem->QueryInt64Attribute("myattr", &value);
    // Floating point strings are not valid int64; expect wrong type
    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: QueryInt64Attribute with multiple attributes, querying specific one
TEST_F(XMLElementQueryInt64Attribute_83, MultipleAttributes_83) {
    doc.Parse("<root a=\"100\" b=\"200\" c=\"300\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t value = 0;
    XMLError result = elem->QueryInt64Attribute("b", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_EQ(value, 200);
}

// Test: QueryInt64Attribute with attribute set via SetAttribute
TEST_F(XMLElementQueryInt64Attribute_83, SetAttributeThenQuery_83) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetAttribute("val", (int64_t)1234567890123LL);
    int64_t value = 0;
    XMLError result = elem->QueryInt64Attribute("val", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_EQ(value, 1234567890123LL);
}

// Test: QueryInt64Attribute on wrong attribute name among many
TEST_F(XMLElementQueryInt64Attribute_83, WrongNameAmongMany_83) {
    doc.Parse("<root x=\"1\" y=\"2\" z=\"3\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t value = 0;
    XMLError result = elem->QueryInt64Attribute("w", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
}

// Test: QueryInt64Attribute with positive sign prefix
TEST_F(XMLElementQueryInt64Attribute_83, PositiveSignPrefix_83) {
    doc.Parse("<root myattr=\"+42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t value = 0;
    XMLError result = elem->QueryInt64Attribute("myattr", &value);
    // Some implementations may or may not accept '+' prefix
    // Just verify no crash and check if accepted
    if (result == XML_SUCCESS) {
        EXPECT_EQ(value, 42);
    } else {
        EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);
    }
}

// Test: QueryInt64Attribute with small integer value (fits in int as well)
TEST_F(XMLElementQueryInt64Attribute_83, SmallIntegerValue_83) {
    doc.Parse("<root myattr=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t value = 0;
    XMLError result = elem->QueryInt64Attribute("myattr", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_EQ(value, 1);
}

// Test: QueryInt64Attribute after deleting the attribute
TEST_F(XMLElementQueryInt64Attribute_83, DeletedAttribute_83) {
    doc.Parse("<root myattr=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->DeleteAttribute("myattr");

    int64_t value = 0;
    XMLError result = elem->QueryInt64Attribute("myattr", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
}
