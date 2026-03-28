#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLTextTest_194 : public ::testing::Test {

protected:

    XMLDocument doc;

    std::unique_ptr<XMLText> xmlText;



    void SetUp() override {

        xmlText = std::make_unique<XMLText>(&doc);

        xmlText->SetValue("Sample Text", false);

    }

};



TEST_F(XMLTextTest_194, ShallowClone_ReturnsNewInstanceWithSameValue_194) {

    XMLDocument newDoc;

    auto clonedNode = xmlText->ShallowClone(&newDoc);



    ASSERT_NE(clonedNode, nullptr);

    EXPECT_STREQ(clonedNode->Value(), "Sample Text");

}



TEST_F(XMLTextTest_194, ShallowClone_WithNullDocument_ReturnsNewInstanceInSameDocument_194) {

    auto clonedNode = xmlText->ShallowClone(nullptr);



    ASSERT_NE(clonedNode, nullptr);

    EXPECT_STREQ(clonedNode->Value(), "Sample Text");

    EXPECT_EQ(clonedNode->GetDocument(), &doc);

}



TEST_F(XMLTextTest_194, ShallowClone_PreservesCDataFlag_194) {

    xmlText->SetCData(true);

    XMLDocument newDoc;

    auto clonedNode = xmlText->ShallowClone(&newDoc);



    ASSERT_NE(clonedNode, nullptr);

    EXPECT_TRUE(static_cast<XMLText*>(clonedNode)->CData());

}



TEST_F(XMLTextTest_194, ShallowClone_PreservesNonCDataFlag_194) {

    XMLDocument newDoc;

    auto clonedNode = xmlText->ShallowClone(&newDoc);



    ASSERT_NE(clonedNode, nullptr);

    EXPECT_FALSE(static_cast<XMLText*>(clonedNode)->CData());

}



TEST_F(XMLTextTest_194, ShallowClone_DifferentDocuments_ReturnsSeparateInstances_194) {

    XMLDocument newDoc;

    auto clonedNode = xmlText->ShallowClone(&newDoc);



    ASSERT_NE(clonedNode, nullptr);

    EXPECT_NE(clonedNode->GetDocument(), xmlText->GetDocument());

}
