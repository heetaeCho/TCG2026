#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class QueryDoubleTextTest_249 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* NewElemWithTextNode(const char* text) {
        XMLElement* e = doc.NewElement("root");
        doc.InsertEndChild(e);
        if (text) {
            e->InsertNewText(text);  // ensures FirstChild()->ToText() is true
        }
        return e;
    }

    XMLElement* NewElemWithNonTextChild() {
        XMLElement* e = doc.NewElement("root");
        doc.InsertEndChild(e);
        // FirstChild exists, but ToText() should be null (child is an element)
        e->InsertNewChildElement("child");
        return e;
    }

    XMLElement* NewEmptyElem() {
        XMLElement* e = doc.NewElement("root");
        doc.InsertEndChild(e);
        return e;
    }
};

TEST_F(QueryDoubleTextTest_249, ReturnsSuccessAndParsesSimpleNumber_249) {
    XMLElement* e = NewElemWithTextNode("3.5");
    double v = 0.0;

    XMLError err = e->QueryDoubleText(&v);

    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(3.5, v);
}

TEST_F(QueryDoubleTextTest_249, ReturnsSuccessAndParsesNegativeNumber_249) {
    XMLElement* e = NewElemWithTextNode("-2.25");
    double v = 1.0;

    XMLError err = e->QueryDoubleText(&v);

    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(-2.25, v);
}

TEST_F(QueryDoubleTextTest_249, ReturnsCanNotConvertTextForNonNumericText_249) {
    XMLElement* e = NewElemWithTextNode("not_a_number");
    double v = 123.0;

    XMLError err = e->QueryDoubleText(&v);

    EXPECT_EQ(XML_CAN_NOT_CONVERT_TEXT, err);
    // Do not assert v unchanged: behavior is not specified by the interface.
}

TEST_F(QueryDoubleTextTest_249, ReturnsNoTextNodeWhenElementHasNoChildren_249) {
    XMLElement* e = NewEmptyElem();
    double v = 0.0;

    XMLError err = e->QueryDoubleText(&v);

    EXPECT_EQ(XML_NO_TEXT_NODE, err);
}

TEST_F(QueryDoubleTextTest_249, ReturnsNoTextNodeWhenFirstChildIsNotText_249) {
    XMLElement* e = NewElemWithNonTextChild();
    double v = 0.0;

    XMLError err = e->QueryDoubleText(&v);

    EXPECT_EQ(XML_NO_TEXT_NODE, err);
}

TEST_F(QueryDoubleTextTest_249, ReturnsCanNotConvertTextForEmptyString_249) {
    XMLElement* e = NewElemWithTextNode("");
    double v = 0.0;

    XMLError err = e->QueryDoubleText(&v);

    EXPECT_EQ(XML_CAN_NOT_CONVERT_TEXT, err);
}

TEST_F(QueryDoubleTextTest_249, ReturnsSuccessForWhitespacePaddedNumber_249) {
    XMLElement* e = NewElemWithTextNode("   42.0 \t\n");
    double v = 0.0;

    XMLError err = e->QueryDoubleText(&v);

    // XMLUtil::ToDouble typically tolerates whitespace; verify observable behavior.
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(42.0, v);
}

TEST_F(QueryDoubleTextTest_249, ReturnsCanNotConvertTextForTrailingGarbage_249) {
    XMLElement* e = NewElemWithTextNode("1.0xyz");
    double v = 0.0;

    XMLError err = e->QueryDoubleText(&v);

    EXPECT_EQ(XML_CAN_NOT_CONVERT_TEXT, err);
}

}  // namespace
