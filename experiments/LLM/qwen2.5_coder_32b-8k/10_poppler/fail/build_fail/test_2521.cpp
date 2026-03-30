#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.cc"

#include "StructElement.h"



using namespace testing;



class PopplerStructureElementTest : public ::testing::Test {

protected:

    MockAttribute mockAttr;

    MockStructElement mockElem;

    _PopplerStructureElement poppler_structure_element;



    void SetUp() override {

        ON_CALL(mockElem, findAttribute(_, _, _)).WillByDefault(Return(&mockAttr));

        poppler_structure_element.elem = &mockElem;

    }

};



// Test normal operation

TEST_F(PopplerStructureElementTest_2521, NormalOperation_ReturnsCorrectEnum_2521) {

    EXPECT_CALL(mockAttr, getValue()).WillOnce(Return(new Object("ExpectedValue")));

    EnumType expectedEnum = name_to_enum<EnumType>("ExpectedValue");

    EXPECT_EQ(attr_to_enum<EnumType>(&poppler_structure_element), expectedEnum);

}



// Test boundary condition: No attribute found

TEST_F(PopplerStructureElementTest_2521, NoAttributeFound_ReturnsDefault_2521) {

    ON_CALL(mockElem, findAttribute(_, _, _)).WillByDefault(Return(nullptr));

    EXPECT_CALL(Attribute::getDefaultValue(_)).WillOnce(Return(new Object("DefaultValue")));

    EnumType expectedEnum = name_to_enum<EnumType>("DefaultValue");

    EXPECT_EQ(attr_to_enum<EnumType>(&poppler_structure_element), expectedEnum);

}



// Test exceptional case: Attribute is not OK

TEST_F(PopplerStructureElementTest_2521, AttributeNotOK_ReturnsDefault_2521) {

    ON_CALL(mockAttr, isOk()).WillByDefault(Return(false));

    EXPECT_CALL(Attribute::getDefaultValue(_)).WillOnce(Return(new Object("DefaultValue")));

    EnumType expectedEnum = name_to_enum<EnumType>("DefaultValue");

    EXPECT_EQ(attr_to_enum<EnumType>(&poppler_structure_element), expectedEnum);

}



// Test external interaction: Verify that findAttribute is called with correct parameters

TEST_F(PopplerStructureElementTest_2521, ExternalInteraction_FindAttributeCalled_2521) {

    EXPECT_CALL(mockElem, findAttribute(EnumNameValue<EnumType>::attribute_type, true, _));

    attr_to_enum<EnumType>(&poppler_structure_element);

}



// Test external interaction: Verify that getDefaultValue is called when attribute not found

TEST_F(PopplerStructureElementTest_2521, ExternalInteraction_GetDefaultValueCalled_2521) {

    ON_CALL(mockElem, findAttribute(_, _, _)).WillByDefault(Return(nullptr));

    EXPECT_CALL(Attribute::getDefaultValue(EnumNameValue<EnumType>::attribute_type));

    attr_to_enum<EnumType>(&poppler_structure_element);

}



// Mock class definitions

class MockAttribute : public Attribute {

public:

    MOCK_METHOD(bool, isOk, (), (const override));

    MOCK_METHOD(const Object*, getValue, (), (const override));

};



class MockStructElement : public StructElement {

public:

    MOCK_METHOD(const Attribute*, findAttribute, (Attribute::Type, bool, Attribute::Owner), (const override));

};
