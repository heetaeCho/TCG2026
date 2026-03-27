#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPCore_Impl.hpp"

#include "XMP_Const.h"



using namespace testing;



class DetectAltTextTest_1905 : public ::testing::Test {

protected:

    void SetUp() override {

        xmpParent = new XMP_Node(nullptr, "testNode", kXMP_PropArrayIsAlternate);

    }



    void TearDown() override {

        delete xmpParent;

    }



    XMP_Node* xmpParent;

};



TEST_F(DetectAltTextTest_1905, NoChildren_DoesNotSetAltTextFlag_1905) {

    DetectAltText(xmpParent);

    EXPECT_EQ((xmpParent->options & kXMP_PropArrayIsAltText), 0);

}



TEST_F(DetectAltTextTest_1905, AllChildrenHaveLang_SetAltTextFlagAndNormalizeLangArray_1905) {

    xmpParent->children.push_back(new XMP_Node(xmpParent, "child1", kXMP_PropHasLang));

    xmpParent->children.push_back(new XMP_Node(xmpParent, "child2", kXMP_PropHasLang));



    DetectAltText(xmpParent);



    EXPECT_NE((xmpParent->options & kXMP_PropArrayIsAltText), 0);

}



TEST_F(DetectAltTextTest_1905, OneChildWithoutLang_DoesNotSetAltTextFlag_1905) {

    xmpParent->children.push_back(new XMP_Node(xmpParent, "child1", kXMP_PropHasLang));

    xmpParent->children.push_back(new XMP_Node(xmpParent, "child2", 0));



    DetectAltText(xmpParent);



    EXPECT_EQ((xmpParent->options & kXMP_PropArrayIsAltText), 0);

}



TEST_F(DetectAltTextTest_1905, OneChildWithCompositeMask_DoesNotSetAltTextFlag_1905) {

    xmpParent->children.push_back(new XMP_Node(xmpParent, "child1", kXMP_PropHasLang));

    xmpParent->children.push_back(new XMP_Node(xmpParent, "child2", kXMP_PropCompositeMask));



    DetectAltText(xmpParent);



    EXPECT_EQ((xmpParent->options & kXMP_PropArrayIsAltText), 0);

}



TEST_F(DetectAltTextTest_1905, AllChildrenHaveLangAndCompositeMask_SetAltTextFlagAndNormalizeLangArray_1905) {

    xmpParent->children.push_back(new XMP_Node(xmpParent, "child1", kXMP_PropHasLang | kXMP_PropCompositeMask));

    xmpParent->children.push_back(new XMP_Node(xmpParent, "child2", kXMP_PropHasLang | kXMP_PropCompositeMask));



    DetectAltText(xmpParent);



    EXPECT_NE((xmpParent->options & kXMP_PropArrayIsAltText), 0);

}



TEST_F(DetectAltTextTest_1905, BoundarySingleChildWithLang_SetAltTextFlagAndNormalizeLangArray_1905) {

    xmpParent->children.push_back(new XMP_Node(xmpParent, "child1", kXMP_PropHasLang));



    DetectAltText(xmpParent);



    EXPECT_NE((xmpParent->options & kXMP_PropArrayIsAltText), 0);

}



TEST_F(DetectAltTextTest_1905, BoundarySingleChildWithoutLang_DoesNotSetAltTextFlag_1905) {

    xmpParent->children.push_back(new XMP_Node(xmpParent, "child1", 0));



    DetectAltText(xmpParent);



    EXPECT_EQ((xmpParent->options & kXMP_PropArrayIsAltText), 0);

}
