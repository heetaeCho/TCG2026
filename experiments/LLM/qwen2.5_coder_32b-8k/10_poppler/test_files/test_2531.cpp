#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "StructElement.h"



using namespace testing;



class PopplerStructureElementTest : public ::testing::Test {

protected:

    void SetUp() override {

        mock_struct_element = std::make_unique<StrictMock<MockStructElement>>();

        poppler_structure_element.elem = mock_struct_element.get();

    }



    struct _PopplerStructureElement poppler_structure_element;

    std::unique_ptr<MockStructElement> mock_struct_element;



    class MockStructElement : public StructElement {

    public:

        MOCK_METHOD(const GooString *, getLanguage, (), (const, override));

        MOCK_METHOD(bool, isOk, (), (const, override));

    };

};



TEST_F(PopplerStructureElementTest_2531, GetLanguage_ReturnsNonNullString_2531) {

    const char* expected_language = "en-US";

    EXPECT_CALL(*mock_struct_element, getLanguage()).WillOnce(Return(new GooString(expected_language)));



    gchar* result = poppler_structure_element_get_language(&poppler_structure_element);



    ASSERT_NE(result, nullptr);

    EXPECT_STREQ(result, expected_language);

    g_free(result); // Free the allocated memory

}



TEST_F(PopplerStructureElementTest_2531, GetLanguage_ReturnsNullString_2531) {

    EXPECT_CALL(*mock_struct_element, getLanguage()).WillOnce(Return(static_cast<GooString*>(nullptr)));



    gchar* result = poppler_structure_element_get_language(&poppler_structure_element);



    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerStructureElementTest_2531, GetLanguage_StructElementNotOk_ReturnsNull_2531) {

    EXPECT_CALL(*mock_struct_element, isOk()).WillOnce(Return(false));

    EXPECT_CALL(*mock_struct_element, getLanguage()).Times(0);



    gchar* result = poppler_structure_element_get_language(&poppler_structure_element);



    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerStructureElementTest_2531, GetLanguage_StructElementNull_ReturnsNull_2531) {

    poppler_structure_element.elem = nullptr;



    gchar* result = poppler_structure_element_get_language(&poppler_structure_element);



    ASSERT_EQ(result, nullptr);

}
