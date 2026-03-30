#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"

#include "XMP_Const.h"



class XMPCoreTest_1897 : public ::testing::Test {

protected:

    XMP_Node parent;

    XMP_Node child1, child2;

    XMP_Node field1_1, field1_2, field2_1;



    void SetUp() override {

        // Setting up test nodes

        parent = XMP_Node(nullptr, "Parent", kXMP_PropValueIsArray);

        

        child1 = XMP_Node(&parent, "Child1", kXMP_PropValueIsStruct);

        field1_1 = XMP_Node(&child1, "FieldName", "FieldValue1", 0);

        field1_2 = XMP_Node(&child1, "OtherField", "OtherValue", 0);

        

        child2 = XMP_Node(&parent, "Child2", kXMP_PropValueIsStruct);

        field2_1 = XMP_Node(&child2, "FieldName", "FieldValue2", 0);



        parent.children.push_back(&child1);

        parent.children.push_back(&child2);

    }



    void TearDown() override {

        // Clean up if needed

    }

};



TEST_F(XMPCoreTest_1897, LookupFieldSelector_NormalOperation_1897) {

    XMP_Index index = LookupFieldSelector(&parent, "FieldName", "FieldValue1");

    EXPECT_EQ(index, 0);

}



TEST_F(XMPCoreTest_1897, LookupFieldSelector_FieldNotFound_1897) {

    XMP_Index index = LookupFieldSelector(&parent, "FieldName", "NonExistentValue");

    EXPECT_EQ(index, -1);

}



TEST_F(XMPCoreTest_1897, LookupFieldSelector_EmptyArray_1897) {

    XMP_Node emptyParent(nullptr, "EmptyParent", kXMP_PropValueIsArray);

    XMP_Index index = LookupFieldSelector(&emptyParent, "FieldName", "FieldValue1");

    EXPECT_EQ(index, -1);

}



TEST_F(XMPCoreTest_1897, LookupFieldSelector_NoStructChild_1897) {

    XMP_Node nonStructChild(&parent, "NonStructChild", 0);

    parent.children.push_back(&nonStructChild);



    EXPECT_THROW(LookupFieldSelector(&parent, "FieldName", "FieldValue1"), XMP_Error);

}



TEST_F(XMPCoreTest_1897, LookupFieldSelector_FieldNameMismatch_1897) {

    XMP_Index index = LookupFieldSelector(&parent, "NonExistentField", "FieldValue1");

    EXPECT_EQ(index, -1);

}



TEST_F(XMPCoreTest_1897, LookupFieldSelector_BoundaryConditionFirstElement_1897) {

    XMP_Index index = LookupFieldSelector(&parent, "FieldName", "FieldValue1");

    EXPECT_EQ(index, 0);

}



TEST_F(XMPCoreTest_1897, LookupFieldSelector_BoundaryConditionLastElement_1897) {

    XMP_Index index = LookupFieldSelector(&parent, "FieldName", "FieldValue2");

    EXPECT_EQ(index, 1);

}
