#include <gtest/gtest.h>

#include "poppler/glib/poppler-structure-element.h"

#include "poppler/Object.h"



// Mock class for testing purposes

class MockPopplerStructureElement {

public:

    bool is_block() const { return mock_is_block; }

    const Object* attr_value_or_default(const Attribute& attr) const { return mock_attr_value_or_default(attr); }



    void set_mock_is_block(bool value) { mock_is_block = value; }

    void set_mock_attr_value_or_default(Object* obj) { mock_obj = obj; }



private:

    bool mock_is_block = false;

    Object* mock_obj = nullptr;



    const Object* mock_attr_value_or_default(const Attribute& attr) const {

        return mock_obj;

    }

};



// Helper function to convert MockPopplerStructureElement to PopplerStructureElement*

PopplerStructureElement* to_poppler_structure_element(MockPopplerStructureElement* mock_elem) {

    return reinterpret_cast<PopplerStructureElement*>(mock_elem);

}



TEST_F(PopplerStructureElementTest_2564, GetSpaceAfter_ReturnsDefaultWhenNotBlock_2564) {

    MockPopplerStructureElement mock_elem;

    mock_elem.set_mock_is_block(false);

    PopplerStructureElement* elem = to_poppler_structure_element(&mock_elem);



    gdouble result = poppler_structure_element_get_space_after(elem);



    EXPECT_EQ(result, NAN);

}



TEST_F(PopplerStructureElementTest_2564, GetSpaceAfter_ReturnsCorrectValueWhenBlock_2564) {

    MockPopplerStructureElement mock_elem;

    mock_elem.set_mock_is_block(true);

    Object space_after_value(3.14);

    mock_elem.set_mock_attr_value_or_default(&space_after_value);

    PopplerStructureElement* elem = to_poppler_structure_element(&mock_elem);



    gdouble result = poppler_structure_element_get_space_after(elem);



    EXPECT_EQ(result, 3.14);

}



TEST_F(PopplerStructureElementTest_2564, GetSpaceAfter_ReturnsZeroWhenAttrValueIsMissing_2564) {

    MockPopplerStructureElement mock_elem;

    mock_elem.set_mock_is_block(true);

    Object space_after_value(Object::null());

    mock_elem.set_mock_attr_value_or_default(&space_after_value);

    PopplerStructureElement* elem = to_poppler_structure_element(&mock_elem);



    gdouble result = poppler_structure_element_get_space_after(elem);



    EXPECT_EQ(result, 0.0);

}
