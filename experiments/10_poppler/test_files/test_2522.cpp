#include <gtest/gtest.h>

#include "poppler-private.h"

#include "StructElement.h"



using namespace testing;



class PopplerStructureElementTest_2522 : public ::testing::Test {

protected:

    MockAttribute* mockAttr;

    MockStructElement* mockElem;

    _PopplerStructureElement poppler_structure_element;



    void SetUp() override {

        mockAttr = new NiceMock<MockAttribute>();

        mockElem = new NiceMock<MockStructElement>();



        ON_CALL(*mockElem, findAttribute(_, _, _))

            .WillByDefault(Return(static_cast<const Attribute*>(nullptr)));



        poppler_structure_element.elem = mockElem;

    }



    void TearDown() override {

        delete mockAttr;

        delete mockElem;

    }

};



// Mock classes for testing

class MockAttribute : public Attribute {

public:

    MOCK_METHOD0(getValue, const Object*());

    MOCK_CONST_METHOD1(findAttribute, const Attribute*(Attribute::Type, bool));

    MOCK_STATIC_METHOD1(getDefaultValue, Object*(Attribute::Type));

};



class MockStructElement : public StructElement {

public:

    using StructElement::findAttribute;

    MOCK_CONST_METHOD3(findAttribute, const Attribute*(Attribute::Type, bool, Attribute::Owner));

};





// Test normal operation

TEST_F(PopplerStructureElementTest_2522, AttrValueOrDefault_ReturnsDefaultValue_2522) {

    EXPECT_CALL(*mockElem, findAttribute(_, _, _))

        .WillOnce(Return(static_cast<const Attribute*>(nullptr)));



    EXPECT_NE(attr_value_or_default(&poppler_structure_element, Attribute::Type::Unknown), nullptr);

}



// Test boundary conditions

TEST_F(PopplerStructureElementTest_2522, AttrValueOrDefault_ReturnsFoundAttribute_2522) {

    ON_CALL(*mockElem, findAttribute(_, _, _))

        .WillByDefault(Return(mockAttr));



    EXPECT_CALL(*mockAttr, getValue())

        .WillOnce(Return(static_cast<Object*>(nullptr)));



    EXPECT_EQ(attr_value_or_default(&poppler_structure_element, Attribute::Type::Unknown), nullptr);

}



// Test exceptional or error cases

TEST_F(PopplerStructureElementTest_2522, AttrValueOrDefault_ReturnsNullptrForInvalidAttribute_2522) {

    ON_CALL(*mockElem, findAttribute(_, _, _))

        .WillByDefault(Return(static_cast<const Attribute*>(nullptr)));



    EXPECT_EQ(attr_value_or_default(&poppler_structure_element, static_cast<Attribute::Type>(-1)), nullptr);

}



// Test verification of external interactions

TEST_F(PopplerStructureElementTest_2522, AttrValueOrDefault_VerifiesFindAttributeCall_2522) {

    EXPECT_CALL(*mockElem, findAttribute(Attribute::Type::Unknown, true, _));



    attr_value_or_default(&poppler_structure_element, Attribute::Type::Unknown);

}
