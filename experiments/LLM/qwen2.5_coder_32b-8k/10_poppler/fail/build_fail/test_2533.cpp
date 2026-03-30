#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "StructElement.h"



class PopplerStructureElementTest_2533 : public ::testing::Test {

protected:

    struct _PopplerStructureElement pse;

    std::unique_ptr<StructElement> mock_elem;



    void SetUp() override {

        mock_elem = std::make_unique<StructElement>();

        pse.elem = mock_elem.get();

    }

};



TEST_F(PopplerStructureElementTest_2533, GetActualText_ReturnsNullptrWhenNoActualText_2533) {

    EXPECT_CALL(*mock_elem, getActualText()).WillOnce(::testing::Return(static_cast<const GooString*>(nullptr)));

    gchar* result = poppler_structure_element_get_actual_text(&pse);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerStructureElementTest_2533, GetActualText_ReturnsUtf8StringWhenActualTextExists_2533) {

    const GooString goo_string("Sample Text");

    EXPECT_CALL(*mock_elem, getActualText()).WillOnce(::testing::Return(&goo_string));

    gchar* result = poppler_structure_element_get_actual_text(&pse);

    ASSERT_NE(result, nullptr);

    EXPECT_STREQ(result, "Sample Text");

    g_free(result);

}



TEST_F(PopplerStructureElementTest_2533, GetActualText_HandlesNullPopplerStructureElement_2533) {

    gchar* result = poppler_structure_element_get_actual_text(nullptr);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerStructureElementTest_2533, GetActualText_HandlesStructElementWithNullElem_2533) {

    pse.elem = nullptr;

    gchar* result = poppler_structure_element_get_actual_text(&pse);

    EXPECT_EQ(result, nullptr);

}
