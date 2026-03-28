#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementSetAttributeUint64Test_101 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* createElement() {
        XMLElement* elem = doc.NewElement("test");
        doc.InsertFirstChild(elem);
        return elem;
    }
};

// Test setting a uint64_t attribute with a normal value
TEST_F(XMLElementSetAttributeUint64Test_101, SetUint64AttributeNormalValue_101) {
    XMLElement* elem = createElement();
    uint64_t val = 12345ULL;
    elem->SetAttribute("myattr", val);

    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Attribute("myattr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 12345ULL);
}

// Test setting a uint64_t attribute with value zero
TEST_F(XMLElementSetAttributeUint64Test_101, SetUint64AttributeZero_101) {
    XMLElement* elem = createElement();
    uint64_t val = 0ULL;
    elem->SetAttribute("myattr", val);

    uint64_t result = 999;
    XMLError err = elem->QueryUnsigned64Attribute("myattr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 0ULL);
}

// Test setting a uint64_t attribute with maximum value
TEST_F(XMLElementSetAttributeUint64Test_101, SetUint64AttributeMaxValue_101) {
    XMLElement* elem = createElement();
    uint64_t val = UINT64_MAX;
    elem->SetAttribute("myattr", val);

    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Attribute("myattr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, UINT64_MAX);
}

// Test that SetAttribute creates a new attribute when it doesn't exist
TEST_F(XMLElementSetAttributeUint64Test_101, SetUint64AttributeCreatesNew_101) {
    XMLElement* elem = createElement();
    // Initially no attributes
    EXPECT_EQ(elem->FirstAttribute(), nullptr);

    uint64_t val = 42ULL;
    elem->SetAttribute("newattr", val);

    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "newattr");
    EXPECT_EQ(attr->Unsigned64Value(), 42ULL);
}

// Test that SetAttribute overwrites an existing attribute
TEST_F(XMLElementSetAttributeUint64Test_101, SetUint64AttributeOverwritesExisting_101) {
    XMLElement* elem = createElement();
    uint64_t val1 = 100ULL;
    elem->SetAttribute("myattr", val1);

    uint64_t result1 = 0;
    elem->QueryUnsigned64Attribute("myattr", &result1);
    EXPECT_EQ(result1, 100ULL);

    uint64_t val2 = 200ULL;
    elem->SetAttribute("myattr", val2);

    uint64_t result2 = 0;
    elem->QueryUnsigned64Attribute("myattr", &result2);
    EXPECT_EQ(result2, 200ULL);
}

// Test setting multiple different uint64_t attributes
TEST_F(XMLElementSetAttributeUint64Test_101, SetMultipleUint64Attributes_101) {
    XMLElement* elem = createElement();
    uint64_t val1 = 111ULL;
    uint64_t val2 = 222ULL;
    uint64_t val3 = 333ULL;

    elem->SetAttribute("attr1", val1);
    elem->SetAttribute("attr2", val2);
    elem->SetAttribute("attr3", val3);

    EXPECT_EQ(elem->Unsigned64Attribute("attr1", 0), 111ULL);
    EXPECT_EQ(elem->Unsigned64Attribute("attr2", 0), 222ULL);
    EXPECT_EQ(elem->Unsigned64Attribute("attr3", 0), 333ULL);
}

// Test that the attribute value is retrievable via Attribute() as a string
TEST_F(XMLElementSetAttributeUint64Test_101, SetUint64AttributeRetrievableAsString_101) {
    XMLElement* elem = createElement();
    uint64_t val = 9876543210ULL;
    elem->SetAttribute("myattr", val);

    const char* strVal = elem->Attribute("myattr");
    ASSERT_NE(strVal, nullptr);
    EXPECT_STREQ(strVal, "9876543210");
}

// Test that Unsigned64Attribute returns default when attribute doesn't exist
TEST_F(XMLElementSetAttributeUint64Test_101, Unsigned64AttributeReturnsDefaultWhenMissing_101) {
    XMLElement* elem = createElement();
    uint64_t defaultVal = 999ULL;
    uint64_t result = elem->Unsigned64Attribute("nonexistent", defaultVal);
    EXPECT_EQ(result, defaultVal);
}

// Test setting uint64_t attribute with a large value just below max
TEST_F(XMLElementSetAttributeUint64Test_101, SetUint64AttributeLargeValue_101) {
    XMLElement* elem = createElement();
    uint64_t val = UINT64_MAX - 1;
    elem->SetAttribute("myattr", val);

    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Attribute("myattr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, UINT64_MAX - 1);
}

// Test that FindAttribute works after setting uint64 attribute
TEST_F(XMLElementSetAttributeUint64Test_101, FindAttributeAfterSetUint64_101) {
    XMLElement* elem = createElement();
    uint64_t val = 55555ULL;
    elem->SetAttribute("findme", val);

    const XMLAttribute* attr = elem->FindAttribute("findme");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "findme");
    EXPECT_EQ(attr->Unsigned64Value(), 55555ULL);
}

// Test that setting uint64 attribute and then deleting it works
TEST_F(XMLElementSetAttributeUint64Test_101, SetAndDeleteUint64Attribute_101) {
    XMLElement* elem = createElement();
    uint64_t val = 777ULL;
    elem->SetAttribute("todelete", val);

    const XMLAttribute* attr = elem->FindAttribute("todelete");
    ASSERT_NE(attr, nullptr);

    elem->DeleteAttribute("todelete");
    attr = elem->FindAttribute("todelete");
    EXPECT_EQ(attr, nullptr);
}

// Test QueryUnsigned64Attribute returns error for non-existent attribute
TEST_F(XMLElementSetAttributeUint64Test_101, QueryUnsigned64NonExistentAttribute_101) {
    XMLElement* elem = createElement();
    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Attribute("doesnotexist", &result);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test that setting uint64 attribute value of 1
TEST_F(XMLElementSetAttributeUint64Test_101, SetUint64AttributeOne_101) {
    XMLElement* elem = createElement();
    uint64_t val = 1ULL;
    elem->SetAttribute("myattr", val);

    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Attribute("myattr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 1ULL);
}

// Test that printing the document after setting uint64 attribute includes the attribute
TEST_F(XMLElementSetAttributeUint64Test_101, PrintDocumentAfterSetUint64Attribute_101) {
    XMLElement* elem = createElement();
    uint64_t val = 42ULL;
    elem->SetAttribute("count", val);

    XMLPrinter printer;
    doc.Print(&printer);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("count=\"42\""), std::string::npos);
}

// Test round-trip: set uint64, save to string, parse, and read back
TEST_F(XMLElementSetAttributeUint64Test_101, RoundTripUint64Attribute_101) {
    XMLElement* elem = createElement();
    uint64_t val = 18446744073709551615ULL; // UINT64_MAX
    elem->SetAttribute("bignum", val);

    XMLPrinter printer;
    doc.Print(&printer);

    XMLDocument doc2;
    doc2.Parse(printer.CStr());
    ASSERT_EQ(doc2.ErrorID(), XML_SUCCESS);

    XMLElement* root = doc2.FirstChildElement("test");
    ASSERT_NE(root, nullptr);

    uint64_t result = 0;
    XMLError err = root->QueryUnsigned64Attribute("bignum", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, UINT64_MAX);
}
