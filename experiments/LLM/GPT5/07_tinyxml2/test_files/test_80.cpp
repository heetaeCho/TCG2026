// TEST_ID: 80
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

class XMLElementToElementTest_80 : public ::testing::Test {
protected:
    tinyxml2::XMLDocument doc_;
};

TEST_F(XMLElementToElementTest_80, ToElementReturnsSamePointer_80) {
    tinyxml2::XMLElement* elem = doc_.NewElement("root");
    ASSERT_NE(elem, nullptr);

    tinyxml2::XMLElement* asElem = elem->ToElement();
    EXPECT_EQ(asElem, elem);
}

TEST_F(XMLElementToElementTest_80, ToElementViaBasePointerReturnsSamePointer_80) {
    tinyxml2::XMLElement* elem = doc_.NewElement("root");
    ASSERT_NE(elem, nullptr);

    tinyxml2::XMLNode* node = elem;
    ASSERT_NE(node, nullptr);

    tinyxml2::XMLElement* asElem = node->ToElement();
    EXPECT_EQ(asElem, elem);
}

}  // namespace
