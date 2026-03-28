#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// We need to create XMLAttribute instances through XMLDocument since
// XMLAttribute has a private constructor and destructor.
// We'll use XMLDocument/XMLElement to create and access attributes.

class XMLAttributeSetAttributeUint64Test_222 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem;

    void SetUp() override {
        elem = doc.NewElement("test");
        doc.InsertFirstChild(elem);
    }
};

// Test setting a uint64_t value of 0
TEST_F(XMLAttributeSetAttributeUint64Test_222, SetAttributeZero_222) {
    elem->SetAttribute("attr", static_cast<uint64_t>(0));
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    uint64_t result = 0;
    XMLError err = attr->QueryUnsigned64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, static_cast<uint64_t>(0));
}

// Test setting a small uint64_t value
TEST_F(XMLAttributeSetAttributeUint64Test_222, SetAttributeSmallValue_222) {
    elem->SetAttribute("attr", static_cast<uint64_t>(42));
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    uint64_t result = 0;
    XMLError err = attr->QueryUnsigned64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, static_cast<uint64_t>(42));
}

// Test setting a large uint64_t value
TEST_F(XMLAttributeSetAttributeUint64Test_222, SetAttributeLargeValue_222) {
    uint64_t largeVal = 9999999999ULL;
    elem->SetAttribute("attr", largeVal);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    uint64_t result = 0;
    XMLError err = attr->QueryUnsigned64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, largeVal);
}

// Test setting the maximum uint64_t value
TEST_F(XMLAttributeSetAttributeUint64Test_222, SetAttributeMaxUint64_222) {
    uint64_t maxVal = UINT64_MAX;
    elem->SetAttribute("attr", maxVal);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    uint64_t result = 0;
    XMLError err = attr->QueryUnsigned64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, maxVal);
}

// Test setting uint64_t value of 1
TEST_F(XMLAttributeSetAttributeUint64Test_222, SetAttributeOne_222) {
    elem->SetAttribute("attr", static_cast<uint64_t>(1));
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    uint64_t result = 0;
    XMLError err = attr->QueryUnsigned64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, static_cast<uint64_t>(1));
}

// Test that the Value() returns a proper string representation
TEST_F(XMLAttributeSetAttributeUint64Test_222, SetAttributeValueString_222) {
    elem->SetAttribute("attr", static_cast<uint64_t>(12345));
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    const char* val = attr->Value();
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "12345");
}

// Test overwriting an existing attribute value with uint64_t
TEST_F(XMLAttributeSetAttributeUint64Test_222, SetAttributeOverwrite_222) {
    elem->SetAttribute("attr", static_cast<uint64_t>(100));
    elem->SetAttribute("attr", static_cast<uint64_t>(200));
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    uint64_t result = 0;
    XMLError err = attr->QueryUnsigned64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, static_cast<uint64_t>(200));
}

// Test Unsigned64Value() convenience method
TEST_F(XMLAttributeSetAttributeUint64Test_222, Unsigned64ValueMethod_222) {
    uint64_t val = 987654321ULL;
    elem->SetAttribute("attr", val);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), val);
}

// Test setting uint64_t value that's beyond int64_t max
TEST_F(XMLAttributeSetAttributeUint64Test_222, SetAttributeBeyondInt64Max_222) {
    uint64_t beyondInt64 = static_cast<uint64_t>(INT64_MAX) + 1ULL;
    elem->SetAttribute("attr", beyondInt64);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    uint64_t result = 0;
    XMLError err = attr->QueryUnsigned64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, beyondInt64);
}

// Test setting a power-of-two uint64_t value
TEST_F(XMLAttributeSetAttributeUint64Test_222, SetAttributePowerOfTwo_222) {
    uint64_t val = 1ULL << 32;
    elem->SetAttribute("attr", val);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    uint64_t result = 0;
    XMLError err = attr->QueryUnsigned64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, val);
}

// Test that setting uint64_t and then querying as string gives correct representation
TEST_F(XMLAttributeSetAttributeUint64Test_222, SetAttributeMaxValueString_222) {
    elem->SetAttribute("attr", UINT64_MAX);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    const char* val = attr->Value();
    ASSERT_NE(val, nullptr);
    // UINT64_MAX = 18446744073709551615
    EXPECT_STREQ(val, "18446744073709551615");
}

// Test that multiple different attributes can each hold uint64_t values
TEST_F(XMLAttributeSetAttributeUint64Test_222, SetMultipleAttributes_222) {
    elem->SetAttribute("a1", static_cast<uint64_t>(111));
    elem->SetAttribute("a2", static_cast<uint64_t>(222));
    elem->SetAttribute("a3", static_cast<uint64_t>(333));

    const XMLAttribute* a1 = elem->FindAttribute("a1");
    const XMLAttribute* a2 = elem->FindAttribute("a2");
    const XMLAttribute* a3 = elem->FindAttribute("a3");

    ASSERT_NE(a1, nullptr);
    ASSERT_NE(a2, nullptr);
    ASSERT_NE(a3, nullptr);

    EXPECT_EQ(a1->Unsigned64Value(), static_cast<uint64_t>(111));
    EXPECT_EQ(a2->Unsigned64Value(), static_cast<uint64_t>(222));
    EXPECT_EQ(a3->Unsigned64Value(), static_cast<uint64_t>(333));
}
