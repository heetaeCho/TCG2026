// TEST_ID: 90
#include <gtest/gtest.h>

#include <limits>
#include <string>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class QueryAttributeUnsignedTest_90 : public ::testing::Test {
protected:
    XMLDocument doc_;

    XMLElement* ParseSingleElement(const char* xml) {
        doc_.Clear();
        EXPECT_EQ(doc_.Parse(xml), XML_SUCCESS);
        XMLElement* e = doc_.RootElement();
        EXPECT_NE(e, nullptr);
        return e;
    }

    static void CallBothAndCompare(XMLElement* elem,
                                   const char* name,
                                   unsigned int* outA,
                                   unsigned int* outB,
                                   XMLError* errA,
                                   XMLError* errB) {
        ASSERT_NE(elem, nullptr);
        ASSERT_NE(errA, nullptr);
        ASSERT_NE(errB, nullptr);

        *errA = elem->QueryAttribute(name, outA);
        *errB = elem->QueryUnsignedAttribute(name, outB);
    }
};

TEST_F(QueryAttributeUnsignedTest_90, ParsesValidUnsigned_SameAsQueryUnsignedAttribute_90) {
    XMLElement* e = ParseSingleElement("<root a='123'/>");

    unsigned int v_attr = 0;
    unsigned int v_unsigned = 0;
    XMLError err_attr = XML_ERROR_PARSING;
    XMLError err_unsigned = XML_ERROR_PARSING;

    CallBothAndCompare(e, "a", &v_attr, &v_unsigned, &err_attr, &err_unsigned);

    EXPECT_EQ(err_attr, err_unsigned);
    EXPECT_EQ(v_attr, v_unsigned);
}

TEST_F(QueryAttributeUnsignedTest_90, MissingAttribute_SameAsQueryUnsignedAttribute_90) {
    XMLElement* e = ParseSingleElement("<root />");

    unsigned int v_attr = 777;
    unsigned int v_unsigned = 888;
    XMLError err_attr = XML_ERROR_PARSING;
    XMLError err_unsigned = XML_ERROR_PARSING;

    CallBothAndCompare(e, "missing", &v_attr, &v_unsigned, &err_attr, &err_unsigned);

    EXPECT_EQ(err_attr, err_unsigned);
    EXPECT_EQ(v_attr, v_unsigned);  // ensure both have same observable effect on output
}

TEST_F(QueryAttributeUnsignedTest_90, NonNumericAttribute_SameAsQueryUnsignedAttribute_90) {
    XMLElement* e = ParseSingleElement("<root a='not_a_number'/>");

    unsigned int v_attr = 11;
    unsigned int v_unsigned = 22;
    XMLError err_attr = XML_ERROR_PARSING;
    XMLError err_unsigned = XML_ERROR_PARSING;

    CallBothAndCompare(e, "a", &v_attr, &v_unsigned, &err_attr, &err_unsigned);

    EXPECT_EQ(err_attr, err_unsigned);
    EXPECT_EQ(v_attr, v_unsigned);
}

TEST_F(QueryAttributeUnsignedTest_90, BoundaryMaxUnsigned_SameAsQueryUnsignedAttribute_90) {
    const unsigned int umax = (std::numeric_limits<unsigned int>::max)();
    const std::string xml = std::string("<root a='") + std::to_string(umax) + "'/>";
    XMLElement* e = ParseSingleElement(xml.c_str());

    unsigned int v_attr = 0;
    unsigned int v_unsigned = 0;
    XMLError err_attr = XML_ERROR_PARSING;
    XMLError err_unsigned = XML_ERROR_PARSING;

    CallBothAndCompare(e, "a", &v_attr, &v_unsigned, &err_attr, &err_unsigned);

    EXPECT_EQ(err_attr, err_unsigned);
    EXPECT_EQ(v_attr, v_unsigned);
}

TEST_F(QueryAttributeUnsignedTest_90, OverflowValueString_SameAsQueryUnsignedAttribute_90) {
    // Construct a value that is very likely to exceed unsigned int range.
    const std::string huge = "999999999999999999999999999999999999";
    const std::string xml = std::string("<root a='") + huge + "'/>";
    XMLElement* e = ParseSingleElement(xml.c_str());

    unsigned int v_attr = 1234;
    unsigned int v_unsigned = 5678;
    XMLError err_attr = XML_ERROR_PARSING;
    XMLError err_unsigned = XML_ERROR_PARSING;

    CallBothAndCompare(e, "a", &v_attr, &v_unsigned, &err_attr, &err_unsigned);

    EXPECT_EQ(err_attr, err_unsigned);
    EXPECT_EQ(v_attr, v_unsigned);
}

TEST_F(QueryAttributeUnsignedTest_90, LeadingAndTrailingWhitespace_SameAsQueryUnsignedAttribute_90) {
    XMLElement* e = ParseSingleElement("<root a='  42  '/>");

    unsigned int v_attr = 0;
    unsigned int v_unsigned = 0;
    XMLError err_attr = XML_ERROR_PARSING;
    XMLError err_unsigned = XML_ERROR_PARSING;

    CallBothAndCompare(e, "a", &v_attr, &v_unsigned, &err_attr, &err_unsigned);

    EXPECT_EQ(err_attr, err_unsigned);
    EXPECT_EQ(v_attr, v_unsigned);
}
