#include <gtest/gtest.h>

#include "poppler-structure-element.h"

#include "StructElement.h"

#include "StructTreeRoot.h"



class PopplerStructureElementIterTest : public ::testing::Test {

protected:

    StructTreeRoot* mockRoot;

    StructElement* mockChild1;

    StructElement* mockChild2;



    void SetUp() override {

        mockRoot = new StructTreeRoot(nullptr, Dict());

        mockChild1 = new StructElement(nullptr, mockRoot, nullptr);

        mockChild2 = new StructElement(nullptr, mockRoot, nullptr);



        EXPECT_CALL(*mockRoot, getNumChildren()).WillRepeatedly(testing::Return(2));

        EXPECT_CALL(*mockRoot, getChild(0)).WillOnce(testing::Return(mockChild1));

        EXPECT_CALL(*mockRoot, getChild(1)).WillOnce(testing::Return(mockChild2));



        mockChild1->index = 0;

        mockChild2->index = 1;

    }



    void TearDown() override {

        delete mockChild2;

        delete mockChild1;

        delete mockRoot;

    }

};



TEST_F(PopplerStructureElementIterTest_2538, IterStartAtRoot_2538) {

    PopplerStructureElementIter iter = { true, 0 };

    EXPECT_TRUE(poppler_structure_element_iter_next(&iter));

}



TEST_F(PopplerStructureElementIterTest_2538, IterNextSuccess_2538) {

    PopplerStructureElementIter iter = { false, 0 };

    iter.root = mockRoot;

    EXPECT_TRUE(poppler_structure_element_iter_next(&iter));

}



TEST_F(PopplerStructureElementIterTest_2538, IterEndReached_2538) {

    PopplerStructureElementIter iter = { false, 1 };

    iter.root = mockRoot;

    EXPECT_FALSE(poppler_structure_element_iter_next(&iter));

}



TEST_F(PopplerStructureElementIterTest_2538, IterNullPointer_2538) {

    PopplerStructureElementIter* nullIter = nullptr;

    EXPECT_FALSE(poppler_structure_element_iter_next(nullIter));

}



TEST_F(PopplerStructureElementIterTest_2538, IterBoundaryCondition_2538) {

    PopplerStructureElementIter iter = { false, 0 };

    iter.root = mockRoot;

    EXPECT_TRUE(poppler_structure_element_iter_next(&iter));

    EXPECT_FALSE(poppler_structure_element_iter_next(&iter));

}



TEST_F(PopplerStructureElementIterTest_2538, IterBoundaryConditionStartAtEnd_2538) {

    PopplerStructureElementIter iter = { false, 2 };

    iter.root = mockRoot;

    EXPECT_FALSE(poppler_structure_element_iter_next(&iter));

}
