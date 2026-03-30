#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-structure-element.h"

#include "./TestProjects/poppler/poppler/StructElement.h"



using ::testing::Return;

using ::testing::Eq;



class MockStructElement : public StructElement {

public:

    MOCK_METHOD(Type, getType, (), (const));

    MOCK_METHOD(const GooString*, getExpandedAbbr, (), (const));

};



class PopplerStructureElementTest_2530 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_elem = new MockStructElement();

        poppler_structure_element = new _PopplerStructureElement{mock_elem};

    }



    void TearDown() override {

        delete poppler_structure_element;

        delete mock_elem;

    }



    MockStructElement* mock_elem;

    _PopplerStructureElement* poppler_structure_element;

};



TEST_F(PopplerStructureElementTest_2530, GetAbbreviationReturnsNullIfTypeNotSpan_2530) {

    EXPECT_CALL(*mock_elem, getType()).WillOnce(Return(StructElement::Title));

    gchar *result = poppler_structure_element_get_abbreviation(reinterpret_cast<PopplerStructureElement*>(poppler_structure_element));

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerStructureElementTest_2530, GetAbbreviationReturnsNullIfExpandedAbbrIsNull_2530) {

    EXPECT_CALL(*mock_elem, getType()).WillOnce(Return(StructElement::Span));

    EXPECT_CALL(*mock_elem, getExpandedAbbr()).WillOnce(Return(nullptr));

    gchar *result = poppler_structure_element_get_abbreviation(reinterpret_cast<PopplerStructureElement*>(poppler_structure_element));

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerStructureElementTest_2530, GetAbbreviationReturnsValidStringIfTypeIsSpanAndExpandedAbbrIsNotNull_2530) {

    const GooString expected("test");

    EXPECT_CALL(*mock_elem, getType()).WillOnce(Return(StructElement::Span));

    EXPECT_CALL(*mock_elem, getExpandedAbbr()).WillOnce(Return(&expected));

    gchar *result = poppler_structure_element_get_abbreviation(reinterpret_cast<PopplerStructureElement*>(poppler_structure_element));

    ASSERT_STREQ(result, "test");

    g_free(result);

}



TEST_F(PopplerStructureElementTest_2530, GetAbbreviationHandlesNullPointerGracefully_2530) {

    gchar *result = poppler_structure_element_get_abbreviation(nullptr);

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerStructureElementTest_2530, GetAbbreviationHandlesNullElemGracefully_2530) {

    poppler_structure_element->elem = nullptr;

    gchar *result = poppler_structure_element_get_abbreviation(reinterpret_cast<PopplerStructureElement*>(poppler_structure_element));

    ASSERT_EQ(result, nullptr);

}
