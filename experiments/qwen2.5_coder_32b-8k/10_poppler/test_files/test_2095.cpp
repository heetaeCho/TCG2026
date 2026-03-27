#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"



using namespace testing;



// Mocking external collaborators if necessary

class MockAnnotTextMarkup : public AnnotTextMarkup {

public:

    MOCK_METHOD(const AnnotQuadrilaterals*, getQuadrilaterals, (), (const, override));

};



TEST_F(PopplerAnnotTest_2095, GetQuadrilaterals_NormalOperation_2095) {

    // Arrange

    MockAnnotTextMarkup mockAnnot;

    PopplerAnnotTextMarkup popplerAnnot = { /* Initialization if needed */ };

    PDFRectangle cropBox = {/* Proper initialization of cropBox */};

    AnnotQuadrilaterals expectedQuads = {/* Proper initialization of expectedQuads */};



    EXPECT_CALL(mockAnnot, getQuadrilaterals()).WillOnce(Return(&expectedQuads));



    // Act

    GArray* result = poppler_annot_text_markup_get_quadrilaterals(reinterpret_cast<PopplerAnnotTextMarkup*>(&popplerAnnot));



    // Assert

    ASSERT_NE(result, nullptr);

    // Further assertions based on the observable behavior of the returned GArray



    g_array_free(result, TRUE);

}



TEST_F(PopplerAnnotTest_2095, GetQuadrilaterals_EmptyQuads_2095) {

    // Arrange

    MockAnnotTextMarkup mockAnnot;

    PopplerAnnotTextMarkup popplerAnnot = { /* Initialization if needed */ };

    PDFRectangle cropBox = {/* Proper initialization of cropBox */};

    AnnotQuadrilaterals expectedQuads = {}; // Empty quadrilaterals



    EXPECT_CALL(mockAnnot, getQuadrilaterals()).WillOnce(Return(&expectedQuads));



    // Act

    GArray* result = poppler_annot_text_markup_get_quadrilaterals(reinterpret_cast<PopplerAnnotTextMarkup*>(&popplerAnnot));



    // Assert

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->len, 0); // Check if the returned array is empty



    g_array_free(result, TRUE);

}



TEST_F(PopplerAnnotTest_2095, GetQuadrilaterals_NullPointer_2095) {

    // Arrange

    PopplerAnnotTextMarkup* popplerAnnot = nullptr;



    // Act & Assert

    EXPECT_EQ(poppler_annot_text_markup_get_quadrilaterals(popplerAnnot), nullptr);

}



TEST_F(PopplerAnnotTest_2095, GetQuadrilaterals_InvalidType_2095) {

    // Arrange

    struct _PopplerAnnotTextMarkup popplerAnnot = { /* Initialization if needed */ };

    PopplerAnnot* invalidAnnot = reinterpret_cast<PopplerAnnot*>(&popplerAnnot);



    // Act & Assert

    EXPECT_EQ(poppler_annot_text_markup_get_quadrilaterals(reinterpret_cast<PopplerAnnotTextMarkup*>(invalidAnnot)), nullptr);

}
