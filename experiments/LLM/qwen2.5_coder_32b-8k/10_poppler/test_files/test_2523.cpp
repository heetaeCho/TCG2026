#include <gtest/gtest.h>

#include "poppler-structure-element.h"

#include "Object.h"



class PopplerStructureElementTest : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Initialize any necessary resources or objects here.

        poppler_structure_element = new PopplerStructureElement();

        mock_struct_element = new testing::NiceMock<MockStructElement>();

        poppler_structure_element->elem = mock_struct_element;

    }



    virtual void TearDown() {

        // Clean up any resources or objects here.

        delete poppler_structure_element;

        delete mock_struct_element;

    }



    PopplerStructureElement* poppler_structure_element;

    MockStructElement* mock_struct_element;



    struct Ref ref_valid { 1, 0 };

    struct Ref ref_invalid = Ref::INVALID();

};



class MockStructElement : public StructElement {

public:

    MOCK_CONST_METHOD1(getPageRef, bool(Ref&));

};



TEST_F(PopplerStructureElementTest_2523, GetPageValidRef_2523) {

    EXPECT_CALL(*mock_struct_element, getPageRef(testing::_)).WillOnce(testing::DoAll(testing::SetArgReferee<0>(ref_valid), testing::Return(true)));



    int page = poppler_structure_element_get_page(poppler_structure_element);

    EXPECT_EQ(page, 0); // Assuming the first page is 1 in the document and 0-based index is returned.

}



TEST_F(PopplerStructureElementTest_2523, GetPageInvalidRef_2523) {

    EXPECT_CALL(*mock_struct_element, getPageRef(testing::_)).WillOnce(testing::DoAll(testing::SetArgReferee<0>(ref_invalid), testing::Return(false)));



    int page = poppler_structure_element_get_page(poppler_structure_element);

    EXPECT_EQ(page, -1); // Invalid ref should return -1.

}



TEST_F(PopplerStructureElementTest_2523, GetPageNullStructElement_2523) {

    poppler_structure_element->elem = nullptr;



    int page = poppler_structure_element_get_page(poppler_structure_element);

    EXPECT_EQ(page, -1); // Null struct element should return -1.

}



TEST_F(PopplerStructureElementTest_2523, GetPageInvalidPopplerStructureElement_2523) {

    delete poppler_structure_element;

    poppler_structure_element = nullptr;



    int page = poppler_structure_element_get_page(poppler_structure_element);

    EXPECT_EQ(page, -1); // Invalid PopplerStructureElement pointer should return -1.

}
