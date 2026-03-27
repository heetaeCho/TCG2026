#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDeclarationTest_203 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(XMLDeclarationTest_203, ShallowEqual_ReturnsTrueForSameValue_203) {

    XMLDocument doc;

    XMLDeclaration decl1(&doc);

    decl1.SetValue("version=\"1.0\" encoding=\"UTF-8\"", false);



    XMLDeclaration decl2(&doc);

    decl2.SetValue("version=\"1.0\" encoding=\"UTF-8\"", false);



    EXPECT_TRUE(decl1.ShallowEqual(&decl2));

}



TEST_F(XMLDeclarationTest_203, ShallowEqual_ReturnsFalseForDifferentValue_203) {

    XMLDocument doc;

    XMLDeclaration decl1(&doc);

    decl1.SetValue("version=\"1.0\" encoding=\"UTF-8\"", false);



    XMLDeclaration decl2(&doc);

    decl2.SetValue("version=\"1.1\" encoding=\"UTF-8\"", false);



    EXPECT_FALSE(decl1.ShallowEqual(&decl2));

}



TEST_F(XMLDeclarationTest_203, ShallowEqual_ReturnsFalseForNullComparison_203) {

    XMLDocument doc;

    XMLDeclaration decl(&doc);

    decl.SetValue("version=\"1.0\" encoding=\"UTF-8\"", false);



    EXPECT_FALSE(decl.ShallowEqual(nullptr));

}



TEST_F(XMLDeclarationTest_203, ShallowEqual_ReturnsFalseForDifferentType_203) {

    XMLDocument doc;

    XMLDeclaration decl(&doc);

    decl.SetValue("version=\"1.0\" encoding=\"UTF-8\"", false);



    XMLElement element(&doc);

    EXPECT_FALSE(decl.ShallowEqual(&element));

}
