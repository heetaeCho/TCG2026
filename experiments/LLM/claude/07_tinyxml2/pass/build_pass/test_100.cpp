#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementSetAttributeTest_100 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem;

    void SetUp() override {
        elem = doc.NewElement("TestElement");
        doc.InsertFirstChild(elem);
    }
};

// ==================== SetAttribute with int64_t ====================

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64Positive_100) {
    elem->SetAttribute("myattr", (int64_t)1234567890123LL);
    int64_t val = elem->Int64Attribute("myattr", 0);
    EXPECT_EQ(val, 1234567890123LL);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64Negative_100) {
    elem->SetAttribute("myattr", (int64_t)-9876543210LL);
    int64_t val = elem->Int64Attribute("myattr", 0);
    EXPECT_EQ(val, -9876543210LL);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64Zero_100) {
    elem->SetAttribute("myattr", (int64_t)0);
    int64_t val = elem->Int64Attribute("myattr", -1);
    EXPECT_EQ(val, 0);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64Max_100) {
    int64_t maxVal = INT64_MAX;
    elem->SetAttribute("myattr", maxVal);
    int64_t val = elem->Int64Attribute("myattr", 0);
    EXPECT_EQ(val, maxVal);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64Min_100) {
    int64_t minVal = INT64_MIN;
    elem->SetAttribute("myattr", minVal);
    int64_t val = elem->Int64Attribute("myattr", 0);
    EXPECT_EQ(val, minVal);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64OverwriteExisting_100) {
    elem->SetAttribute("myattr", (int64_t)100);
    EXPECT_EQ(elem->Int64Attribute("myattr", 0), 100);
    elem->SetAttribute("myattr", (int64_t)200);
    EXPECT_EQ(elem->Int64Attribute("myattr", 0), 200);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64MultipleAttributes_100) {
    elem->SetAttribute("attr1", (int64_t)111);
    elem->SetAttribute("attr2", (int64_t)222);
    elem->SetAttribute("attr3", (int64_t)333);
    EXPECT_EQ(elem->Int64Attribute("attr1", 0), 111);
    EXPECT_EQ(elem->Int64Attribute("attr2", 0), 222);
    EXPECT_EQ(elem->Int64Attribute("attr3", 0), 333);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64QueryReturnsSuccess_100) {
    elem->SetAttribute("myattr", (int64_t)42);
    int64_t val = 0;
    XMLError err = elem->QueryInt64Attribute("myattr", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64AttributeVisibleViaFindAttribute_100) {
    elem->SetAttribute("myattr", (int64_t)999);
    const XMLAttribute* attr = elem->FindAttribute("myattr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "myattr");
    EXPECT_EQ(attr->Int64Value(), 999);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64ValueVisibleAsString_100) {
    elem->SetAttribute("myattr", (int64_t)12345);
    const char* strVal = elem->Attribute("myattr");
    ASSERT_NE(strVal, nullptr);
    EXPECT_STREQ(strVal, "12345");
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64NegativeValueVisibleAsString_100) {
    elem->SetAttribute("myattr", (int64_t)-12345);
    const char* strVal = elem->Attribute("myattr");
    ASSERT_NE(strVal, nullptr);
    EXPECT_STREQ(strVal, "-12345");
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64FirstAttributeCheck_100) {
    elem->SetAttribute("first", (int64_t)1);
    const XMLAttribute* first = elem->FirstAttribute();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Name(), "first");
    EXPECT_EQ(first->Int64Value(), 1);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64OverwriteDifferentType_100) {
    // Set as string first, then overwrite with int64_t
    elem->SetAttribute("myattr", "hello");
    EXPECT_STREQ(elem->Attribute("myattr"), "hello");
    elem->SetAttribute("myattr", (int64_t)42);
    EXPECT_EQ(elem->Int64Attribute("myattr", 0), 42);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64ThenDeleteAttribute_100) {
    elem->SetAttribute("myattr", (int64_t)42);
    EXPECT_NE(elem->FindAttribute("myattr"), nullptr);
    elem->DeleteAttribute("myattr");
    EXPECT_EQ(elem->FindAttribute("myattr"), nullptr);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64QueryNonexistentReturnsError_100) {
    int64_t val = 0;
    XMLError err = elem->QueryInt64Attribute("nonexistent", &val);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64DefaultValueWhenMissing_100) {
    int64_t val = elem->Int64Attribute("missing", 999);
    EXPECT_EQ(val, 999);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64PreservedAfterPrintAndReparse_100) {
    elem->SetAttribute("bignum", (int64_t)9223372036854775807LL); // INT64_MAX
    
    XMLPrinter printer;
    doc.Print(&printer);
    
    XMLDocument doc2;
    XMLError err = doc2.Parse(printer.CStr());
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc2.FirstChildElement("TestElement");
    ASSERT_NE(root, nullptr);
    int64_t val = root->Int64Attribute("bignum", 0);
    EXPECT_EQ(val, 9223372036854775807LL);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64MultipleOverwrites_100) {
    for (int64_t i = 0; i < 10; ++i) {
        elem->SetAttribute("counter", i);
    }
    EXPECT_EQ(elem->Int64Attribute("counter", -1), 9);
}

// ==================== Other SetAttribute overloads for completeness ====================

TEST_F(XMLElementSetAttributeTest_100, SetAttributeString_100) {
    elem->SetAttribute("name", "value");
    EXPECT_STREQ(elem->Attribute("name"), "value");
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt_100) {
    elem->SetAttribute("intattr", 42);
    EXPECT_EQ(elem->IntAttribute("intattr", 0), 42);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeUnsigned_100) {
    elem->SetAttribute("uattr", (unsigned)4000000000u);
    EXPECT_EQ(elem->UnsignedAttribute("uattr", 0), 4000000000u);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeUint64_100) {
    elem->SetAttribute("u64attr", (uint64_t)18446744073709551615ULL);
    EXPECT_EQ(elem->Unsigned64Attribute("u64attr", 0), 18446744073709551615ULL);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeBool_100) {
    elem->SetAttribute("boolattr", true);
    EXPECT_EQ(elem->BoolAttribute("boolattr", false), true);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeDouble_100) {
    elem->SetAttribute("dblattr", 3.14159);
    EXPECT_NEAR(elem->DoubleAttribute("dblattr", 0.0), 3.14159, 1e-5);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeFloat_100) {
    elem->SetAttribute("fltattr", 2.718f);
    EXPECT_NEAR(elem->FloatAttribute("fltattr", 0.0f), 2.718f, 1e-3f);
}

// ==================== Attribute iteration ====================

TEST_F(XMLElementSetAttributeTest_100, AttributeIterationAfterInt64Set_100) {
    elem->SetAttribute("a", (int64_t)1);
    elem->SetAttribute("b", (int64_t)2);
    elem->SetAttribute("c", (int64_t)3);
    
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");
    EXPECT_EQ(attr->Int64Value(), 1);
    
    attr = attr->Next();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "b");
    EXPECT_EQ(attr->Int64Value(), 2);
    
    attr = attr->Next();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "c");
    EXPECT_EQ(attr->Int64Value(), 3);
    
    attr = attr->Next();
    EXPECT_EQ(attr, nullptr);
}

// ==================== QueryAttribute overloads ====================

TEST_F(XMLElementSetAttributeTest_100, QueryAttributeInt64_100) {
    elem->SetAttribute("val", (int64_t)-5555555555LL);
    int64_t result = 0;
    XMLError err = elem->QueryAttribute("val", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, -5555555555LL);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64One_100) {
    elem->SetAttribute("one", (int64_t)1);
    EXPECT_EQ(elem->Int64Attribute("one", 0), 1);
}

TEST_F(XMLElementSetAttributeTest_100, SetAttributeInt64NegativeOne_100) {
    elem->SetAttribute("negone", (int64_t)-1);
    EXPECT_EQ(elem->Int64Attribute("negone", 0), -1);
}
