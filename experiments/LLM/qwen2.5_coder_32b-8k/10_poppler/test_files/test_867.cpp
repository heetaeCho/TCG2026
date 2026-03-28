#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Annot.h"



using namespace testing;



class AnnotsTest : public ::testing::Test {

protected:

    PDFDoc* mock_doc;

    int page_number = 1;

    Object* mock_annotsObj;

    std::shared_ptr<Annot> mock_annot1;

    std::shared_ptr<Annot> mock_annot2;



    Annots* annots_instance;



    void SetUp() override {

        mock_doc = static_cast<PDFDoc*>(mock());

        mock_annotsObj = static_cast<Object*>(mock());

        mock_annot1 = std::make_shared<Annot>();

        mock_annot2 = std::make_shared<Annot>();

        annots_instance = new Annots(mock_doc, page_number, mock_annotsObj);

    }



    void TearDown() override {

        delete annots_instance;

    }

};



TEST_F(AnnotsTest_867, GetAnnotsInitiallyEmpty_867) {

    EXPECT_TRUE(annots_instance->getAnnots().empty());

}



TEST_F(AnnotsTest_867, AppendAnnotIncreasesCount_867) {

    annots_instance->appendAnnot(mock_annot1);

    EXPECT_EQ(annots_instance->getAnnots().size(), 1);



    annots_instance->appendAnnot(mock_annot2);

    EXPECT_EQ(annots_instance->getAnnots().size(), 2);

}



TEST_F(AnnotsTest_867, RemoveExistingAnnotDecreasesCount_867) {

    annots_instance->appendAnnot(mock_annot1);

    annots_instance->appendAnnot(mock_annot2);

    EXPECT_EQ(annots_instance->getAnnots().size(), 2);



    annots_instance->removeAnnot(mock_annot1);

    EXPECT_EQ(annots_instance->getAnnots().size(), 1);



    annots_instance->removeAnnot(mock_annot2);

    EXPECT_TRUE(annots_instance->getAnnots().empty());

}



TEST_F(AnnotsTest_867, RemoveNonExistingAnnotDoesNothing_867) {

    annots_instance->appendAnnot(mock_annot1);

    EXPECT_EQ(annots_instance->getAnnots().size(), 1);



    std::shared_ptr<Annot> non_existing_annot = std::make_shared<Annot>();

    bool result = annots_instance->removeAnnot(non_existing_annot);

    EXPECT_FALSE(result);

    EXPECT_EQ(annots_instance->getAnnots().size(), 1);

}



TEST_F(AnnotsTest_867, BoundaryConditionEmptyList_867) {

    EXPECT_TRUE(annots_instance->getAnnots().empty());

    bool result = annots_instance->removeAnnot(mock_annot1);

    EXPECT_FALSE(result);

}
