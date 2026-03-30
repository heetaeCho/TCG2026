// TEST_ID: 78
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLElementNameTest_78 : public ::testing::Test {
protected:
    XMLDocument doc_;
};

TEST_F(XMLElementNameTest_78, NewElementNameMatchesProvidedName_78) {
    XMLElement* elem = doc_.NewElement("root");
    ASSERT_NE(elem, nullptr);

    // Name() is specified to return Value() (observable via returned string).
    ASSERT_STREQ(elem->Name(), "root");
}

TEST_F(XMLElementNameTest_78, SetNameUpdatesName_78) {
    XMLElement* elem = doc_.NewElement("old");
    ASSERT_NE(elem, nullptr);
    ASSERT_STREQ(elem->Name(), "old");

    elem->SetName("newName");
    ASSERT_STREQ(elem->Name(), "newName");
}

TEST_F(XMLElementNameTest_78, NameReflectsXMLNodeSetValue_78) {
    XMLElement* elem = doc_.NewElement("initial");
    ASSERT_NE(elem, nullptr);
    ASSERT_STREQ(elem->Name(), "initial");

    // Since Name() returns Value(), changing Value() via SetValue should change Name().
    elem->SetValue("viaSetValue", /*staticMem=*/false);
    ASSERT_STREQ(elem->Name(), "viaSetValue");
}

TEST_F(XMLElementNameTest_78, EmptyNameIsReturnedAsEmptyString_78) {
    XMLElement* elem = doc_.NewElement("");
    ASSERT_NE(elem, nullptr);

    ASSERT_STREQ(elem->Name(), "");
}
