// TEST_ID: 67
#include <gtest/gtest.h>

#include "tinyxml2.h"

namespace {

class XMLDeclarationTest_67 : public ::testing::Test {
protected:
    tinyxml2::XMLDocument doc_;
};

TEST_F(XMLDeclarationTest_67, ToDeclarationReturnsSelf_67) {
    tinyxml2::XMLDeclaration* decl = doc_.NewDeclaration();
    ASSERT_NE(decl, nullptr);

    EXPECT_EQ(decl->ToDeclaration(), decl);
}

TEST_F(XMLDeclarationTest_67, ToDeclarationViaXMLNodePointerReturnsSamePointer_67) {
    tinyxml2::XMLDeclaration* decl = doc_.NewDeclaration();
    ASSERT_NE(decl, nullptr);

    tinyxml2::XMLNode* asNode = decl;
    EXPECT_EQ(asNode->ToDeclaration(), decl);
}

TEST_F(XMLDeclarationTest_67, ToDeclarationIsStableAcrossMultipleCalls_67) {
    tinyxml2::XMLDeclaration* decl = doc_.NewDeclaration();
    ASSERT_NE(decl, nullptr);

    tinyxml2::XMLDeclaration* first = decl->ToDeclaration();
    tinyxml2::XMLDeclaration* second = decl->ToDeclaration();
    EXPECT_EQ(first, decl);
    EXPECT_EQ(second, decl);
    EXPECT_EQ(first, second);
}

}  // namespace
