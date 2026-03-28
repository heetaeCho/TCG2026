#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Annot.h"



class AnnotTest_786 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Assuming a default constructor or mock setup for PDFDoc and PDFRectangle

        annot = std::make_unique<Annot>(nullptr, nullptr);

    }



    virtual void TearDown() {

        annot.reset();

    }



    std::unique_ptr<Annot> annot;

};



TEST_F(AnnotTest_786, GetName_ReturnsNullPointerWhenNameNotSet_786) {

    EXPECT_EQ(nullptr, annot->getName());

}



TEST_F(AnnotTest_786, SetNameAndGetname_ReturnsCorrectName_786) {

    GooString expectedName("TestAnnotation");

    annot->setName(&expectedName);

    EXPECT_EQ(expectedName.c_str(), annot->getName()->c_str());

}



TEST_F(AnnotTest_786, GetName_IsConsistentAfterMultipleSets_786) {

    GooString name1("FirstAnnotation");

    GooString name2("SecondAnnotation");



    annot->setName(&name1);

    EXPECT_EQ(name1.c_str(), annot->getName()->c_str());



    annot->setName(&name2);

    EXPECT_EQ(name2.c_str(), annot->getName()->c_str());

}



TEST_F(AnnotTest_786, IsOk_ReturnsTrueForDefaultConstructedObject_786) {

    EXPECT_TRUE(annot->isOk());

}
