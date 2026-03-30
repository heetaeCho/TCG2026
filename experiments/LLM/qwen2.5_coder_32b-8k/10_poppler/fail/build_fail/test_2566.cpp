#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the necessary headers for PopplerStructureElement and Object are included



extern "C" {

    gdouble poppler_structure_element_get_end_indent(PopplerStructureElement *poppler_structure_element);

}



class MockObject : public Object {

public:

    MOCK_METHOD(double, getNum, (), (const));

};



class MockStructElement {

public:

    MOCK_METHOD(MockObject*, attr_value_or_default, (Attribute), ());

};



class PopplerStructureElementMock {

public:

    MockStructElement* elem;

};



TEST_F(PopplerStructureElementTest_2566, NormalOperation_ReturnsValidEndIndent_2566) {

    PopplerStructureElementMock mock_element;

    MockStructElement mock_struct_element;

    MockObject mock_object;



    EXPECT_CALL(mock_struct_element, attr_value_or_default(Attribute::EndIndent))

        .WillOnce(::testing::Return(&mock_object));

    EXPECT_CALL(mock_object, getNum())

        .WillOnce(::testing::Return(10.5));



    mock_element.elem = &mock_struct_element;

    PopplerStructureElement* element = reinterpret_cast<PopplerStructureElement*>(&mock_element);



    gdouble result = poppler_structure_element_get_end_indent(element);

    EXPECT_EQ(result, 10.5);

}



TEST_F(PopplerStructureElementTest_2566, BlockElement_ReturnsDefaultEndIndent_2566) {

    PopplerStructureElementMock mock_element;

    MockStructElement mock_struct_element;

    MockObject mock_object;



    EXPECT_CALL(mock_struct_element, attr_value_or_default(Attribute::EndIndent))

        .WillOnce(::testing::Return(&mock_object));

    EXPECT_CALL(mock_object, getNum())

        .WillOnce(::testing::Return(0.0));



    mock_element.elem = &mock_struct_element;

    PopplerStructureElement* element = reinterpret_cast<PopplerStructureElement*>(&mock_element);



    gdouble result = poppler_structure_element_get_end_indent(element);

    EXPECT_EQ(result, 0.0);

}



TEST_F(PopplerStructureElementTest_2566, NonBlockElement_ReturnsNAN_2566) {

    PopplerStructureElementMock mock_element;

    MockStructElement mock_struct_element;



    mock_element.elem = &mock_struct_element;

    PopplerStructureElement* element = reinterpret_cast<PopplerStructureElement*>(&mock_element);



    gdouble result = poppler_structure_element_get_end_indent(element);

    EXPECT_EQ(result, NAN);

}
