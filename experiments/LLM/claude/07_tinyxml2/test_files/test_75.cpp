#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeTest_75 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    XMLAttribute* CreateAttribute(const char* xmlStr) {
        doc.Parse(xmlStr);
        XMLElement* elem = doc.FirstChildElement();
        if (elem) {
            return const_cast<XMLAttribute*>(elem->FirstAttribute());
        }
        return nullptr;
    }
};

// ==================== BoolValue Tests ====================

TEST_F(XMLAttributeTest_75, BoolValueReturnsTrue_75) {
    auto* attr = CreateAttribute("<e a=\"true\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_TRUE(attr->BoolValue());
}

TEST_F(XMLAttributeTest_75, BoolValueReturnsFalse_75) {
    auto* attr = CreateAttribute("<e a=\"false\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_FALSE(attr->BoolValue());
}

TEST_F(XMLAttributeTest_75, BoolValueWith1ReturnsTrue_75) {
    auto* attr = CreateAttribute("<e a=\"1\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_TRUE(attr->BoolValue());
}

TEST_F(XMLAttributeTest_75, BoolValueWith0ReturnsFalse_75) {
    auto* attr = CreateAttribute("<e a=\"0\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_FALSE(attr->BoolValue());
}

TEST_F(XMLAttributeTest_75, BoolValueNonBoolStringReturnsFalse_75) {
    // When QueryBoolValue fails, default bool (false) should be returned
    auto* attr = CreateAttribute("<e a=\"notabool\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_FALSE(attr->BoolValue());
}

// ==================== IntValue Tests ====================

TEST_F(XMLAttributeTest_75, IntValueReturnsCorrectValue_75) {
    auto* attr = CreateAttribute("<e a=\"42\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 42);
}

TEST_F(XMLAttributeTest_75, IntValueNegative_75) {
    auto* attr = CreateAttribute("<e a=\"-100\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), -100);
}

TEST_F(XMLAttributeTest_75, IntValueZero_75) {
    auto* attr = CreateAttribute("<e a=\"0\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 0);
}

// ==================== UnsignedValue Tests ====================

TEST_F(XMLAttributeTest_75, UnsignedValueReturnsCorrectValue_75) {
    auto* attr = CreateAttribute("<e a=\"123\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 123u);
}

TEST_F(XMLAttributeTest_75, UnsignedValueLargeNumber_75) {
    auto* attr = CreateAttribute("<e a=\"4294967295\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 4294967295u);
}

// ==================== Int64Value Tests ====================

TEST_F(XMLAttributeTest_75, Int64ValueReturnsCorrectValue_75) {
    auto* attr = CreateAttribute("<e a=\"9223372036854775807\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), INT64_C(9223372036854775807));
}

TEST_F(XMLAttributeTest_75, Int64ValueNegative_75) {
    auto* attr = CreateAttribute("<e a=\"-9223372036854775807\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), INT64_C(-9223372036854775807));
}

// ==================== Unsigned64Value Tests ====================

TEST_F(XMLAttributeTest_75, Unsigned64ValueReturnsCorrectValue_75) {
    auto* attr = CreateAttribute("<e a=\"18446744073709551615\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), UINT64_C(18446744073709551615));
}

// ==================== DoubleValue Tests ====================

TEST_F(XMLAttributeTest_75, DoubleValueReturnsCorrectValue_75) {
    auto* attr = CreateAttribute("<e a=\"3.14159\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 3.14159);
}

TEST_F(XMLAttributeTest_75, DoubleValueNegative_75) {
    auto* attr = CreateAttribute("<e a=\"-2.718\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), -2.718);
}

// ==================== FloatValue Tests ====================

TEST_F(XMLAttributeTest_75, FloatValueReturnsCorrectValue_75) {
    auto* attr = CreateAttribute("<e a=\"1.5\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 1.5f);
}

TEST_F(XMLAttributeTest_75, FloatValueNegative_75) {
    auto* attr = CreateAttribute("<e a=\"-0.5\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), -0.5f);
}

// ==================== Name and Value Tests ====================

TEST_F(XMLAttributeTest_75, NameReturnsCorrectName_75) {
    auto* attr = CreateAttribute("<e myattr=\"hello\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "myattr");
}

TEST_F(XMLAttributeTest_75, ValueReturnsCorrectValue_75) {
    auto* attr = CreateAttribute("<e a=\"hello world\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "hello world");
}

TEST_F(XMLAttributeTest_75, ValueEmptyString_75) {
    auto* attr = CreateAttribute("<e a=\"\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "");
}

// ==================== QueryIntValue Tests ====================

TEST_F(XMLAttributeTest_75, QueryIntValueSuccess_75) {
    auto* attr = CreateAttribute("<e a=\"42\"/>");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    EXPECT_EQ(attr->QueryIntValue(&val), XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLAttributeTest_75, QueryIntValueNonNumericFails_75) {
    auto* attr = CreateAttribute("<e a=\"abc\"/>");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    EXPECT_NE(attr->QueryIntValue(&val), XML_SUCCESS);
}

// ==================== QueryUnsignedValue Tests ====================

TEST_F(XMLAttributeTest_75, QueryUnsignedValueSuccess_75) {
    auto* attr = CreateAttribute("<e a=\"999\"/>");
    ASSERT_NE(attr, nullptr);
    unsigned int val = 0;
    EXPECT_EQ(attr->QueryUnsignedValue(&val), XML_SUCCESS);
    EXPECT_EQ(val, 999u);
}

TEST_F(XMLAttributeTest_75, QueryUnsignedValueNonNumericFails_75) {
    auto* attr = CreateAttribute("<e a=\"xyz\"/>");
    ASSERT_NE(attr, nullptr);
    unsigned int val = 0;
    EXPECT_NE(attr->QueryUnsignedValue(&val), XML_SUCCESS);
}

// ==================== QueryBoolValue Tests ====================

TEST_F(XMLAttributeTest_75, QueryBoolValueTrueSuccess_75) {
    auto* attr = CreateAttribute("<e a=\"true\"/>");
    ASSERT_NE(attr, nullptr);
    bool val = false;
    EXPECT_EQ(attr->QueryBoolValue(&val), XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLAttributeTest_75, QueryBoolValueFalseSuccess_75) {
    auto* attr = CreateAttribute("<e a=\"false\"/>");
    ASSERT_NE(attr, nullptr);
    bool val = true;
    EXPECT_EQ(attr->QueryBoolValue(&val), XML_SUCCESS);
    EXPECT_FALSE(val);
}

TEST_F(XMLAttributeTest_75, QueryBoolValueNonBoolFails_75) {
    auto* attr = CreateAttribute("<e a=\"maybe\"/>");
    ASSERT_NE(attr, nullptr);
    bool val = false;
    EXPECT_NE(attr->QueryBoolValue(&val), XML_SUCCESS);
}

// ==================== QueryDoubleValue Tests ====================

TEST_F(XMLAttributeTest_75, QueryDoubleValueSuccess_75) {
    auto* attr = CreateAttribute("<e a=\"3.14\"/>");
    ASSERT_NE(attr, nullptr);
    double val = 0.0;
    EXPECT_EQ(attr->QueryDoubleValue(&val), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

TEST_F(XMLAttributeTest_75, QueryDoubleValueNonNumericFails_75) {
    auto* attr = CreateAttribute("<e a=\"notanumber\"/>");
    ASSERT_NE(attr, nullptr);
    double val = 0.0;
    EXPECT_NE(attr->QueryDoubleValue(&val), XML_SUCCESS);
}

// ==================== QueryFloatValue Tests ====================

TEST_F(XMLAttributeTest_75, QueryFloatValueSuccess_75) {
    auto* attr = CreateAttribute("<e a=\"2.5\"/>");
    ASSERT_NE(attr, nullptr);
    float val = 0.0f;
    EXPECT_EQ(attr->QueryFloatValue(&val), XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 2.5f);
}

TEST_F(XMLAttributeTest_75, QueryFloatValueNonNumericFails_75) {
    auto* attr = CreateAttribute("<e a=\"abc\"/>");
    ASSERT_NE(attr, nullptr);
    float val = 0.0f;
    EXPECT_NE(attr->QueryFloatValue(&val), XML_SUCCESS);
}

// ==================== QueryInt64Value Tests ====================

TEST_F(XMLAttributeTest_75, QueryInt64ValueSuccess_75) {
    auto* attr = CreateAttribute("<e a=\"123456789012345\"/>");
    ASSERT_NE(attr, nullptr);
    int64_t val = 0;
    EXPECT_EQ(attr->QueryInt64Value(&val), XML_SUCCESS);
    EXPECT_EQ(val, INT64_C(123456789012345));
}

TEST_F(XMLAttributeTest_75, QueryInt64ValueNonNumericFails_75) {
    auto* attr = CreateAttribute("<e a=\"notint64\"/>");
    ASSERT_NE(attr, nullptr);
    int64_t val = 0;
    EXPECT_NE(attr->QueryInt64Value(&val), XML_SUCCESS);
}

// ==================== QueryUnsigned64Value Tests ====================

TEST_F(XMLAttributeTest_75, QueryUnsigned64ValueSuccess_75) {
    auto* attr = CreateAttribute("<e a=\"123456789012345\"/>");
    ASSERT_NE(attr, nullptr);
    uint64_t val = 0;
    EXPECT_EQ(attr->QueryUnsigned64Value(&val), XML_SUCCESS);
    EXPECT_EQ(val, UINT64_C(123456789012345));
}

TEST_F(XMLAttributeTest_75, QueryUnsigned64ValueNonNumericFails_75) {
    auto* attr = CreateAttribute("<e a=\"notuint64\"/>");
    ASSERT_NE(attr, nullptr);
    uint64_t val = 0;
    EXPECT_NE(attr->QueryUnsigned64Value(&val), XML_SUCCESS);
}

// ==================== SetAttribute Tests ====================

TEST_F(XMLAttributeTest_75, SetAttributeStringValue_75) {
    auto* attr = CreateAttribute("<e a=\"old\"/>");
    ASSERT_NE(attr, nullptr);
    attr->SetAttribute("new_value");
    EXPECT_STREQ(attr->Value(), "new_value");
}

TEST_F(XMLAttributeTest_75, SetAttributeIntValue_75) {
    auto* attr = CreateAttribute("<e a=\"0\"/>");
    ASSERT_NE(attr, nullptr);
    attr->SetAttribute(42);
    EXPECT_EQ(attr->IntValue(), 42);
}

TEST_F(XMLAttributeTest_75, SetAttributeUnsignedValue_75) {
    auto* attr = CreateAttribute("<e a=\"0\"/>");
    ASSERT_NE(attr, nullptr);
    attr->SetAttribute(100u);
    EXPECT_EQ(attr->UnsignedValue(), 100u);
}

TEST_F(XMLAttributeTest_75, SetAttributeInt64Value_75) {
    auto* attr = CreateAttribute("<e a=\"0\"/>");
    ASSERT_NE(attr, nullptr);
    attr->SetAttribute(INT64_C(9876543210));
    EXPECT_EQ(attr->Int64Value(), INT64_C(9876543210));
}

TEST_F(XMLAttributeTest_75, SetAttributeUint64Value_75) {
    auto* attr = CreateAttribute("<e a=\"0\"/>");
    ASSERT_NE(attr, nullptr);
    attr->SetAttribute(UINT64_C(9876543210));
    EXPECT_EQ(attr->Unsigned64Value(), UINT64_C(9876543210));
}

TEST_F(XMLAttributeTest_75, SetAttributeBoolTrue_75) {
    auto* attr = CreateAttribute("<e a=\"false\"/>");
    ASSERT_NE(attr, nullptr);
    attr->SetAttribute(true);
    EXPECT_TRUE(attr->BoolValue());
}

TEST_F(XMLAttributeTest_75, SetAttributeBoolFalse_75) {
    auto* attr = CreateAttribute("<e a=\"true\"/>");
    ASSERT_NE(attr, nullptr);
    attr->SetAttribute(false);
    EXPECT_FALSE(attr->BoolValue());
}

TEST_F(XMLAttributeTest_75, SetAttributeDoubleValue_75) {
    auto* attr = CreateAttribute("<e a=\"0\"/>");
    ASSERT_NE(attr, nullptr);
    attr->SetAttribute(3.14);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 3.14);
}

TEST_F(XMLAttributeTest_75, SetAttributeFloatValue_75) {
    auto* attr = CreateAttribute("<e a=\"0\"/>");
    ASSERT_NE(attr, nullptr);
    attr->SetAttribute(2.5f);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 2.5f);
}

// ==================== Next Tests ====================

TEST_F(XMLAttributeTest_75, NextReturnsNextAttribute_75) {
    auto* attr = CreateAttribute("<e a=\"1\" b=\"2\"/>");
    ASSERT_NE(attr, nullptr);
    const XMLAttribute* next = attr->Next();
    ASSERT_NE(next, nullptr);
    EXPECT_STREQ(next->Name(), "b");
    EXPECT_STREQ(next->Value(), "2");
}

TEST_F(XMLAttributeTest_75, NextReturnsNullWhenNoMore_75) {
    auto* attr = CreateAttribute("<e a=\"1\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Next(), nullptr);
}

TEST_F(XMLAttributeTest_75, NextChainMultipleAttributes_75) {
    auto* attr = CreateAttribute("<e a=\"1\" b=\"2\" c=\"3\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");
    
    const XMLAttribute* second = attr->Next();
    ASSERT_NE(second, nullptr);
    EXPECT_STREQ(second->Name(), "b");
    
    const XMLAttribute* third = second->Next();
    ASSERT_NE(third, nullptr);
    EXPECT_STREQ(third->Name(), "c");
    
    EXPECT_EQ(third->Next(), nullptr);
}

// ==================== GetLineNum Tests ====================

TEST_F(XMLAttributeTest_75, GetLineNumReturnsPositiveValue_75) {
    auto* attr = CreateAttribute("<e a=\"1\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_GE(attr->GetLineNum(), 1);
}

// ==================== Boundary/Edge Cases ====================

TEST_F(XMLAttributeTest_75, AttributeWithSpecialChars_75) {
    auto* attr = CreateAttribute("<e a=\"&amp;&lt;&gt;\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "&<>");
}

TEST_F(XMLAttributeTest_75, SetAttributeEmptyString_75) {
    auto* attr = CreateAttribute("<e a=\"something\"/>");
    ASSERT_NE(attr, nullptr);
    attr->SetAttribute("");
    EXPECT_STREQ(attr->Value(), "");
}

TEST_F(XMLAttributeTest_75, SetAttributeNegativeInt_75) {
    auto* attr = CreateAttribute("<e a=\"0\"/>");
    ASSERT_NE(attr, nullptr);
    attr->SetAttribute(-999);
    EXPECT_EQ(attr->IntValue(), -999);
}

TEST_F(XMLAttributeTest_75, BoolValueWithSetAttributeRoundTrip_75) {
    auto* attr = CreateAttribute("<e a=\"0\"/>");
    ASSERT_NE(attr, nullptr);
    attr->SetAttribute(true);
    bool val = false;
    XMLError err = attr->QueryBoolValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLAttributeTest_75, IntValueWithNonIntStringDefaultsToZero_75) {
    auto* attr = CreateAttribute("<e a=\"notanumber\"/>");
    ASSERT_NE(attr, nullptr);
    // IntValue internally calls QueryIntValue with default 0
    EXPECT_EQ(attr->IntValue(), 0);
}

TEST_F(XMLAttributeTest_75, DoubleValueWithNonNumericDefaultsToZero_75) {
    auto* attr = CreateAttribute("<e a=\"notanumber\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 0.0);
}

TEST_F(XMLAttributeTest_75, FloatValueWithNonNumericDefaultsToZero_75) {
    auto* attr = CreateAttribute("<e a=\"notanumber\"/>");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 0.0f);
}

TEST_F(XMLAttributeTest_75, SetAttributeOverwritesPreviousValue_75) {
    auto* attr = CreateAttribute("<e a=\"initial\"/>");
    ASSERT_NE(attr, nullptr);
    attr->SetAttribute("changed");
    EXPECT_STREQ(attr->Value(), "changed");
    attr->SetAttribute("changed_again");
    EXPECT_STREQ(attr->Value(), "changed_again");
}

TEST_F(XMLAttributeTest_75, SetAttributeIntThenQueryAsString_75) {
    auto* attr = CreateAttribute("<e a=\"hello\"/>");
    ASSERT_NE(attr, nullptr);
    attr->SetAttribute(12345);
    EXPECT_STREQ(attr->Value(), "12345");
}

TEST_F(XMLAttributeTest_75, SetAttributeBoolTrueStringRepresentation_75) {
    auto* attr = CreateAttribute("<e a=\"0\"/>");
    ASSERT_NE(attr, nullptr);
    attr->SetAttribute(true);
    EXPECT_STREQ(attr->Value(), "true");
}

TEST_F(XMLAttributeTest_75, SetAttributeBoolFalseStringRepresentation_75) {
    auto* attr = CreateAttribute("<e a=\"1\"/>");
    ASSERT_NE(attr, nullptr);
    attr->SetAttribute(false);
    EXPECT_STREQ(attr->Value(), "false");
}
