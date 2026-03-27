#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeNextTest_70 : public ::testing::Test {
protected:
    XMLDocument doc;

    const XMLElement* ParseElement(const char* xml) {
        XMLError err = doc.Parse(xml);
        EXPECT_EQ(err, XML_SUCCESS);
        return doc.RootElement();
    }
};

/**
 * TEST_ID = 70
 * Normal operation: Next() should return the next attribute
 */
TEST_F(XMLAttributeNextTest_70, NextReturnsFollowingAttribute_70) {
    const XMLElement* elem =
        ParseElement("<root a=\"1\" b=\"2\" c=\"3\" />");

    const XMLAttribute* attrA = elem->FirstAttribute();
    ASSERT_NE(attrA, nullptr);
    EXPECT_STREQ(attrA->Name(), "a");

    const XMLAttribute* attrB = attrA->Next();
    ASSERT_NE(attrB, nullptr);
    EXPECT_STREQ(attrB->Name(), "b");

    const XMLAttribute* attrC = attrB->Next();
    ASSERT_NE(attrC, nullptr);
    EXPECT_STREQ(attrC->Name(), "c");
}

/**
 * TEST_ID = 70
 * Boundary condition: Next() on the last attribute should return nullptr
 */
TEST_F(XMLAttributeNextTest_70, NextOnLastAttributeReturnsNull_70) {
    const XMLElement* elem =
        ParseElement("<root a=\"1\" b=\"2\" />");

    const XMLAttribute* first = elem->FirstAttribute();
    ASSERT_NE(first, nullptr);

    const XMLAttribute* second = first->Next();
    ASSERT_NE(second, nullptr);

    const XMLAttribute* end = second->Next();
    EXPECT_EQ(end, nullptr);
}

/**
 * TEST_ID = 70
 * Boundary condition: Single attribute should have no next attribute
 */
TEST_F(XMLAttributeNextTest_70, NextOnSingleAttributeReturnsNull_70) {
    const XMLElement* elem =
        ParseElement("<root only=\"true\" />");

    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);

    const XMLAttribute* next = attr->Next();
    EXPECT_EQ(next, nullptr);
}

/**
 * TEST_ID = 70
 * Const correctness: Next() should be callable on const XMLAttribute*
 */
TEST_F(XMLAttributeNextTest_70, NextCallableOnConstAttribute_70) {
    const XMLElement* elem =
        ParseElement("<root x=\"1\" y=\"2\" />");

    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);

    const XMLAttribute* next = attr->Next();
    ASSERT_NE(next, nullptr);
}
