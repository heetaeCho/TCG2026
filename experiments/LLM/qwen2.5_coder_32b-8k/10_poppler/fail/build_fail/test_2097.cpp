#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"

#include "Annot.h"



using namespace testing;



// Mock class for AnnotFreeText to control its behavior in tests

class MockAnnotFreeText : public AnnotFreeText {

public:

    MOCK_METHOD(AnnotCalloutLine*, getCalloutLine, (), (const, override));

};



TEST_F(PopplerAnnotFreeTextTest_2097, GetCalloutLine_ReturnsNullptr_WhenNoCalloutLineExists_2097) {

    MockAnnotFreeText mockAnnot;

    EXPECT_CALL(mockAnnot, getCalloutLine()).WillOnce(Return(nullptr));



    PopplerAnnotFreeText popplerAnnot;

    EXPECT_EQ(poppler_annot_free_text_get_callout_line(&popplerAnnot), nullptr);

}



TEST_F(PopplerAnnotFreeTextTest_2097, GetCalloutLine_ReturnsValidSingleLine_WhenSingleCalloutLineExists_2097) {

    MockAnnotFreeText mockAnnot;

    auto* singleLine = new AnnotCalloutLine(1.0, 2.0, 3.0, 4.0);

    EXPECT_CALL(mockAnnot, getCalloutLine()).WillOnce(Return(singleLine));



    PopplerAnnotFreeText popplerAnnot;

    PopplerAnnotCalloutLine* result = poppler_annot_free_text_get_callout_line(&popplerAnnot);

    ASSERT_NE(result, nullptr);

    EXPECT_FALSE(result->multiline);

    EXPECT_EQ(result->x1, 1.0);

    EXPECT_EQ(result->y1, 2.0);

    EXPECT_EQ(result->x2, 3.0);

    EXPECT_EQ(result->y2, 4.0);



    g_free(result); // Clean up the allocated memory

}



TEST_F(PopplerAnnotFreeTextTest_2097, GetCalloutLine_ReturnsValidMultiLine_WhenMultiCalloutLineExists_2097) {

    MockAnnotFreeText mockAnnot;

    auto* multiLine = new AnnotCalloutMultiLine(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    EXPECT_CALL(mockAnnot, getCalloutLine()).WillOnce(Return(multiLine));



    PopplerAnnotFreeText popplerAnnot;

    PopplerAnnotCalloutLine* result = poppler_annot_free_text_get_callout_line(&popplerAnnot);

    ASSERT_NE(result, nullptr);

    EXPECT_TRUE(result->multiline);

    EXPECT_EQ(result->x1, 1.0);

    EXPECT_EQ(result->y1, 2.0);

    EXPECT_EQ(result->x2, 3.0);

    EXPECT_EQ(result->y2, 4.0);

    EXPECT_EQ(result->x3, 5.0);

    EXPECT_EQ(result->y3, 6.0);



    g_free(result); // Clean up the allocated memory

}
