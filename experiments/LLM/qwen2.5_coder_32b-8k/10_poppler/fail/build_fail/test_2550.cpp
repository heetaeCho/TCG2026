#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "StructElement.h"



using namespace testing;



class PopplerStructureElementTest : public ::testing::Test {

protected:

    struct _PopplerStructureElement *element;

    StructElement *internalElement;



    void SetUp() override {

        element = new _PopplerStructureElement();

        internalElement = new StructElement(nullptr, nullptr, nullptr);

        element->elem = internalElement;

    }



    void TearDown() override {

        delete element->elem;

        delete element;

    }

};



TEST_F(PopplerStructureElementTest_2550, GetTextSpans_NormalOperation_2550) {

    TextSpanArray spans = {TextSpan(), TextSpan()};

    EXPECT_CALL(*internalElement, getTextSpans()).WillOnce(Return(spans));



    guint n_text_spans;

    PopplerTextSpan **text_spans = poppler_structure_element_get_text_spans(element, &n_text_spans);



    ASSERT_EQ(n_text_spans, 2U);

    g_free(text_spans);

}



TEST_F(PopplerStructureElementTest_2550, GetTextSpans_NoContent_2550) {

    EXPECT_CALL(*internalElement, isContent()).WillOnce(Return(false));



    guint n_text_spans;

    PopplerTextSpan **text_spans = poppler_structure_element_get_text_spans(element, &n_text_spans);



    ASSERT_EQ(text_spans, nullptr);

    ASSERT_EQ(n_text_spans, 0U);

}



TEST_F(PopplerStructureElementTest_2550, GetTextSpans_EmptySpans_2550) {

    TextSpanArray spans = {};

    EXPECT_CALL(*internalElement, getTextSpans()).WillOnce(Return(spans));



    guint n_text_spans;

    PopplerTextSpan **text_spans = poppler_structure_element_get_text_spans(element, &n_text_spans);



    ASSERT_EQ(n_text_spans, 0U);

    g_free(text_spans);

}



TEST_F(PopplerStructureElementTest_2550, GetTextSpans_NullNTextSpans_2550) {

    TextSpanArray spans = {TextSpan(), TextSpan()};

    EXPECT_CALL(*internalElement, getTextSpans()).WillOnce(Return(spans));



    PopplerTextSpan **text_spans = poppler_structure_element_get_text_spans(element, nullptr);



    ASSERT_EQ(text_spans, nullptr);

}



TEST_F(PopplerStructureElementTest_2550, GetTextSpans_NullElement_2550) {

    element->elem = nullptr;



    guint n_text_spans;

    PopplerTextSpan **text_spans = poppler_structure_element_get_text_spans(element, &n_text_spans);



    ASSERT_EQ(text_spans, nullptr);

    ASSERT_EQ(n_text_spans, 0U);

}



TEST_F(PopplerStructureElementTest_2550, GetTextSpans_NullStructElement_2550) {

    element = nullptr;



    guint n_text_spans;

    PopplerTextSpan **text_spans = poppler_structure_element_get_text_spans(element, &n_text_spans);



    ASSERT_EQ(text_spans, nullptr);

    ASSERT_EQ(n_text_spans, 0U);

}
