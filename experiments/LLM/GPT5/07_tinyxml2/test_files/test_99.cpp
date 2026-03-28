#include "tinyxml2.h"
#include "gtest/gtest.h"

using namespace tinyxml2;

class XMLElementTest_99 : public ::testing::Test {
protected:
    XMLElementTest_99() {
        doc = new XMLDocument();
        element = doc->NewElement("TestElement");
    }

    ~XMLElementTest_99() override {
        delete doc;
    }

    XMLDocument* doc;
    XMLElement* element;
};

// Test normal operation: setting a single unsigned attribute
TEST_F(XMLElementTest_99, SetAttribute_Normal_99) {
    unsigned value = 42;
    element->SetAttribute("attr", value);

    const XMLAttribute* attr = element->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    unsigned queriedValue = 0;
    EXPECT_EQ(attr->QueryUnsignedValue(&queriedValue), XML_SUCCESS);
    EXPECT_EQ(queriedValue, value);
}

// Test boundary value: zero
TEST_F(XMLElementTest_99, SetAttribute_ZeroValue_99) {
    unsigned value = 0;
    element->SetAttribute("zeroAttr", value);

    const XMLAttribute* attr = element->FindAttribute("zeroAttr");
    ASSERT_NE(attr, nullptr);
    unsigned queriedValue = 1; // initialize with non-zero
    EXPECT_EQ(attr->QueryUnsignedValue(&queriedValue), XML_SUCCESS);
    EXPECT_EQ(queriedValue, value);
}

// Test boundary value: maximum unsigned int
TEST_F(XMLElementTest_99, SetAttribute_MaxValue_99) {
    unsigned value = std::numeric_limits<unsigned>::max();
    element->SetAttribute("maxAttr", value);

    const XMLAttribute* attr = element->FindAttribute("maxAttr");
    ASSERT_NE(attr, nullptr);
    unsigned queriedValue = 0;
    EXPECT_EQ(attr->QueryUnsignedValue(&queriedValue), XML_SUCCESS);
    EXPECT_EQ(queriedValue, value);
}

// Test overwriting an existing attribute
TEST_F(XMLElementTest_99, SetAttribute_Overwrite_99) {
    element->SetAttribute("attr", 1u);
    element->SetAttribute("attr", 100u);

    const XMLAttribute* attr = element->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    unsigned queriedValue = 0;
    EXPECT_EQ(attr->QueryUnsignedValue(&queriedValue), XML_SUCCESS);
    EXPECT_EQ(queriedValue, 100u);
}

// Test multiple attributes
TEST_F(XMLElementTest_99, SetAttribute_MultipleAttributes_99) {
    element->SetAttribute("first", 1u);
    element->SetAttribute("second", 2u);
    element->SetAttribute("third", 3u);

    unsigned val1 = 0, val2 = 0, val3 = 0;

    const XMLAttribute* a1 = element->FindAttribute("first");
    const XMLAttribute* a2 = element->FindAttribute("second");
    const XMLAttribute* a3 = element->FindAttribute("third");

    ASSERT_NE(a1, nullptr);
    ASSERT_NE(a2, nullptr);
    ASSERT_NE(a3, nullptr);

    EXPECT_EQ(a1->QueryUnsignedValue(&val1), XML_SUCCESS);
    EXPECT_EQ(a2->QueryUnsignedValue(&val2), XML_SUCCESS);
    EXPECT_EQ(a3->QueryUnsignedValue(&val3), XML_SUCCESS);

    EXPECT_EQ(val1, 1u);
    EXPECT_EQ(val2, 2u);
    EXPECT_EQ(val3, 3u);
}

// Test behavior with empty attribute name
TEST_F(XMLElementTest_99, SetAttribute_EmptyName_99) {
    unsigned value = 10u;
    element->SetAttribute("", value);

    const XMLAttribute* attr = element->FindAttribute("");
    // Depending on tinyxml2 behavior, empty name may or may not create an attribute
    // We check that the attribute pointer is either null or correctly set
    if (attr) {
        unsigned queriedValue = 0;
        EXPECT_EQ(attr->QueryUnsignedValue(&queriedValue), XML_SUCCESS);
        EXPECT_EQ(queriedValue, value);
    }
}

// Test behavior with very long attribute name
TEST_F(XMLElementTest_99, SetAttribute_LongName_99) {
    std::string longName(1024, 'a');
    unsigned value = 123u;
    element->SetAttribute(longName.c_str(), value);

    const XMLAttribute* attr = element->FindAttribute(longName.c_str());
    ASSERT_NE(attr, nullptr);
    unsigned queriedValue = 0;
    EXPECT_EQ(attr->QueryUnsignedValue(&queriedValue), XML_SUCCESS);
    EXPECT_EQ(queriedValue, value);
}
