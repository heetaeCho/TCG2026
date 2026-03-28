#include <gtest/gtest.h>

#include "poppler-annot.h"

#include "poppler-private.h"



// Mock class for Annot

class MockAnnot : public Annot {

public:

    MOCK_METHOD(int, getPageNum, (), (const));

};



TEST_F(PopplerAnnotTest_2070, GetPageIndex_NormalOperation_2070) {

    auto mock_annot = std::make_shared<MockAnnot>();

    EXPECT_CALL(*mock_annot, getPageNum()).WillOnce(testing::Return(5));



    PopplerAnnot poppler_annot;

    poppler_annot.annot = mock_annot;



    EXPECT_EQ(poppler_annot_get_page_index(&poppler_annot), 4);

}



TEST_F(PopplerAnnotTest_2070, GetPageIndex_PageNumZero_2070) {

    auto mock_annot = std::make_shared<MockAnnot>();

    EXPECT_CALL(*mock_annot, getPageNum()).WillOnce(testing::Return(0));



    PopplerAnnot poppler_annot;

    poppler_annot.annot = mock_annot;



    EXPECT_EQ(poppler_annot_get_page_index(&poppler_annot), -1);

}



TEST_F(PopplerAnnotTest_2070, GetPageIndex_PageNumNegative_2070) {

    auto mock_annot = std::make_shared<MockAnnot>();

    EXPECT_CALL(*mock_annot, getPageNum()).WillOnce(testing::Return(-3));



    PopplerAnnot poppler_annot;

    poppler_annot.annot = mock_annot;



    EXPECT_EQ(poppler_annot_get_page_index(&poppler_annot), -1);

}



TEST_F(PopplerAnnotTest_2070, GetPageIndex_NullPointer_2070) {

    PopplerAnnot* null_poppler_annot = nullptr;

    EXPECT_EQ(poppler_annot_get_page_index(null_poppler_annot), -1);

}
