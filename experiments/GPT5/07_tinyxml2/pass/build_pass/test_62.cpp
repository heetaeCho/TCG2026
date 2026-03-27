// TEST_ID: 62
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace tinyxml2 {

class XMLNodeGetUserDataTest_62 : public ::testing::Test {
protected:
    XMLDocument doc_;
};

TEST_F(XMLNodeGetUserDataTest_62, DefaultUserDataIsNullptr_62) {
    XMLElement* elem = doc_.NewElement("root");
    ASSERT_NE(elem, nullptr);

    // Newly created nodes should have no user data.
    EXPECT_EQ(elem->GetUserData(), nullptr);
}

TEST_F(XMLNodeGetUserDataTest_62, SetUserDataThenGetReturnsSamePointer_62) {
    XMLElement* elem = doc_.NewElement("root");
    ASSERT_NE(elem, nullptr);

    int payload = 123;
    void* ptr = &payload;

    elem->SetUserData(ptr);
    EXPECT_EQ(elem->GetUserData(), ptr);
}

TEST_F(XMLNodeGetUserDataTest_62, SetUserDataToNullptrClears_62) {
    XMLElement* elem = doc_.NewElement("root");
    ASSERT_NE(elem, nullptr);

    int payload = 7;
    elem->SetUserData(&payload);
    ASSERT_EQ(elem->GetUserData(), &payload);

    elem->SetUserData(nullptr);
    EXPECT_EQ(elem->GetUserData(), nullptr);
}

TEST_F(XMLNodeGetUserDataTest_62, GetUserDataWorksThroughConstPointer_62) {
    XMLElement* elem = doc_.NewElement("root");
    ASSERT_NE(elem, nullptr);

    int payload = 999;
    elem->SetUserData(&payload);

    const XMLNode* constNode = elem;
    ASSERT_NE(constNode, nullptr);

    EXPECT_EQ(constNode->GetUserData(), &payload);
}

}  // namespace tinyxml2
