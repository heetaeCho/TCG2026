#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLElementSetNameTest_79 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        // XMLElement ctor is private; create via XMLDocument factory.
        elem = doc.NewElement("root");
        ASSERT_NE(elem, nullptr);
    }
};

TEST_F(XMLElementSetNameTest_79, SetNameUpdatesName_79) {
    elem->SetName("newName");
    EXPECT_STREQ("newName", elem->Name());
}

TEST_F(XMLElementSetNameTest_79, SetNameUpdatesValueAsWell_79) {
    elem->SetName("tag");
    EXPECT_STREQ("tag", elem->Name());
    EXPECT_STREQ("tag", elem->Value());  // SetName delegates to SetValue(...)
}

TEST_F(XMLElementSetNameTest_79, SetNameEmptyString_79) {
    elem->SetName("");
    EXPECT_STREQ("", elem->Name());
    EXPECT_STREQ("", elem->Value());
}

TEST_F(XMLElementSetNameTest_79, SetNameCanBeCalledMultipleTimes_LastWins_79) {
    elem->SetName("a");
    EXPECT_STREQ("a", elem->Name());

    elem->SetName("b");
    EXPECT_STREQ("b", elem->Name());

    elem->SetName("c");
    EXPECT_STREQ("c", elem->Name());
    EXPECT_STREQ("c", elem->Value());
}

TEST_F(XMLElementSetNameTest_79, SetNameWithStaticMemTrueUpdatesName_79) {
    elem->SetName("staticName", /*staticMem=*/true);
    EXPECT_STREQ("staticName", elem->Name());
    EXPECT_STREQ("staticName", elem->Value());
}

TEST_F(XMLElementSetNameTest_79, SetNameWithStaticMemFalseUpdatesName_79) {
    elem->SetName("dynamicName", /*staticMem=*/false);
    EXPECT_STREQ("dynamicName", elem->Name());
    EXPECT_STREQ("dynamicName", elem->Value());
}

TEST_F(XMLElementSetNameTest_79, SetNameLongString_79) {
    std::string longName(1024, 'x');
    elem->SetName(longName.c_str());
    EXPECT_STREQ(longName.c_str(), elem->Name());
    EXPECT_STREQ(longName.c_str(), elem->Value());
}

TEST_F(XMLElementSetNameTest_79, SetNameAfterInsertionAffectsLookupByName_79) {
    // Observable behavior through other public APIs: lookup by element name.
    doc.InsertFirstChild(elem);
    ASSERT_EQ(doc.FirstChildElement("root"), elem);

    elem->SetName("renamed");
    EXPECT_EQ(doc.FirstChildElement("renamed"), elem);
    EXPECT_EQ(doc.FirstChildElement("root"), nullptr);
}

TEST_F(XMLElementSetNameTest_79, SetNameDoesNotChangeElementType_79) {
    // Ensure element remains an element and ToElement still returns itself.
    elem->SetName("stillElement");
    EXPECT_EQ(elem->ToElement(), elem);
}
