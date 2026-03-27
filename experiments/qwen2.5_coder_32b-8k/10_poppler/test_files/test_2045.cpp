#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"

#include "poppler-private.h"



// Mock class for PopplerDocument to simulate its behavior in tests

class MockPopplerDocument : public _PopplerDocument {

public:

    MOCK_METHOD(void, doc_method, (), (const));

};



TEST_F(PopplerAnnotTest_2045, NormalOperation_2045) {

    MockPopplerDocument mockDoc;

    PopplerRectangle rect = {10, 20, 30, 40};

    PopplerAnnot* annot = poppler_annot_free_text_new(&mockDoc, &rect);

    EXPECT_NE(annot, nullptr);

}



TEST_F(PopplerAnnotTest_2045, BoundaryConditions_ZeroAreaRectangle_2045) {

    MockPopplerDocument mockDoc;

    PopplerRectangle rect = {10, 20, 10, 20};

    PopplerAnnot* annot = poppler_annot_free_text_new(&mockDoc, &rect);

    EXPECT_NE(annot, nullptr);

}



TEST_F(PopplerAnnotTest_2045, BoundaryConditions_NegativeDimensions_2045) {

    MockPopplerDocument mockDoc;

    PopplerRectangle rect = {30, 40, 10, 20};

    PopplerAnnot* annot = poppler_annot_free_text_new(&mockDoc, &rect);

    EXPECT_NE(annot, nullptr);

}



TEST_F(PopplerAnnotTest_2045, BoundaryConditions_LargeValues_2045) {

    MockPopplerDocument mockDoc;

    PopplerRectangle rect = {1000000, 2000000, 3000000, 4000000};

    PopplerAnnot* annot = poppler_annot_free_text_new(&mockDoc, &rect);

    EXPECT_NE(annot, nullptr);

}



TEST_F(PopplerAnnotTest_2045, BoundaryConditions_NegativeValues_2045) {

    MockPopplerDocument mockDoc;

    PopplerRectangle rect = {-10, -20, -30, -40};

    PopplerAnnot* annot = poppler_annot_free_text_new(&mockDoc, &rect);

    EXPECT_NE(annot, nullptr);

}



TEST_F(PopplerAnnotTest_2045, NullDocumentPointer_2045) {

    PopplerRectangle rect = {10, 20, 30, 40};

    PopplerAnnot* annot = poppler_annot_free_text_new(nullptr, &rect);

    EXPECT_EQ(annot, nullptr);

}



TEST_F(PopplerAnnotTest_2045, NullRectanglePointer_2045) {

    MockPopplerDocument mockDoc;

    PopplerAnnot* annot = poppler_annot_free_text_new(&mockDoc, nullptr);

    EXPECT_EQ(annot, nullptr);

}
