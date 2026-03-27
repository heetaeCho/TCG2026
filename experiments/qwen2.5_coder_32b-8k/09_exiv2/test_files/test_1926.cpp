#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPMeta-GetSet.cpp"

#include "XMPCore_Impl.hpp"



using namespace std;



class XMP_Node_Mock : public XMP_Node {

public:

    MOCK_METHOD(void, SetNode, (XMP_StringPtr itemValue, XMP_OptionBits options), (override));

};



class DoSetArrayItemTest_1926 : public ::testing::Test {

protected:

    XMP_Node arrayNode;

    XMP_Node_Mock* mockChildNode;



    DoSetArrayItemTest_1926() : arrayNode(nullptr, "arrayName", 0) {

        mockChildNode = new XMP_Node_Mock(&arrayNode, "childName", 0);

        arrayNode.children.push_back(mockChildNode);

    }



    ~DoSetArrayItemTest_1926() {

        delete mockChildNode;

    }

};



TEST_F(DoSetArrayItemTest_1926, InsertAtLastPosition_1926) {

    EXPECT_CALL(*mockChildNode, SetNode("newValue", 0)).Times(1);

    DoSetArrayItem(&arrayNode, kXMP_ArrayLastItem, "newValue", 0);

}



TEST_F(DoSetArrayItemTest_1926, InsertAfterLastPosition_1926) {

    EXPECT_CALL(*mockChildNode, SetNode(_, _)).Times(0); // Ensure no existing node is modified

    EXPECT_EQ(arrayNode.children.size(), 1);



    XMP_Node_Mock* newChild = nullptr;

    EXPECT_CALL(*newChild, SetNode("newValue", 0)).WillOnce(testing::Invoke([&](XMP_StringPtr itemValue, XMP_OptionBits options) {

        newChild = new XMP_Node_Mock(&arrayNode, "childName", itemValue, options);

        arrayNode.children.push_back(newChild);

    }));



    DoSetArrayItem(&arrayNode, kXMP_ArrayLastItem + 1, "newValue", kXMP_InsertAfterItem);



    EXPECT_EQ(arrayNode.children.size(), 2);

}



TEST_F(DoSetArrayItemTest_1926, InsertBeforeFirstPosition_1926) {

    EXPECT_CALL(*mockChildNode, SetNode(_, _)).Times(0); // Ensure no existing node is modified

    EXPECT_EQ(arrayNode.children.size(), 1);



    XMP_Node_Mock* newChild = nullptr;

    EXPECT_CALL(*newChild, SetNode("newValue", 0)).WillOnce(testing::Invoke([&](XMP_StringPtr itemValue, XMP_OptionBits options) {

        newChild = new XMP_Node_Mock(&arrayNode, "childName", itemValue, options);

        arrayNode.children.insert(arrayNode.children.begin(), newChild);

    }));



    DoSetArrayItem(&arrayNode, 1, "newValue", kXMP_InsertBeforeItem);



    EXPECT_EQ(arrayNode.children.size(), 2);

}



TEST_F(DoSetArrayItemTest_1926, ReplaceExistingAtFirstPosition_1926) {

    EXPECT_CALL(*mockChildNode, SetNode("newValue", 0)).Times(1);

    DoSetArrayItem(&arrayNode, 1, "newValue", kXMP_DeleteExisting);

}



TEST_F(DoSetArrayItemTest_1926, InsertBeforeImplicitNewItem_1926) {

    EXPECT_THROW({

        XMP_Node_Mock* newChild = nullptr;

        EXPECT_CALL(*newChild, SetNode("newValue", 0)).WillOnce(testing::Invoke([&](XMP_StringPtr itemValue, XMP_OptionBits options) {

            newChild = new XMP_Node_Mock(&arrayNode, "childName", itemValue, options);

            arrayNode.children.insert(arrayNode.children.begin() + 1, newChild);

        }));

        DoSetArrayItem(&arrayNode, kXMP_ArrayLastItem + 2, "newValue", kXMP_InsertBeforeItem);

    }, XMP_Error);



    EXPECT_EQ(arrayNode.children.size(), 1); // No change in size

}



TEST_F(DoSetArrayItemTest_1926, OutOfBoundsIndex_1926) {

    EXPECT_THROW({

        DoSetArrayItem(&arrayNode, 3, "newValue", 0);

    }, XMP_Error);



    EXPECT_EQ(arrayNode.children.size(), 1); // No change in size

}



TEST_F(DoSetArrayItemTest_1926, ZeroIndexInsertionError_1926) {

    EXPECT_THROW({

        DoSetArrayItem(&arrayNode, 0, "newValue", kXMP_InsertAfterItem);

    }, XMP_Error);



    EXPECT_EQ(arrayNode.children.size(), 1); // No change in size

}



TEST_F(DoSetArrayItemTest_1926, InsertionAtPositionOne_1926) {

    EXPECT_CALL(*mockChildNode, SetNode(_, _)).Times(0); // Ensure no existing node is modified



    XMP_Node_Mock* newChild = nullptr;

    EXPECT_CALL(*newChild, SetNode("newValue", 0)).WillOnce(testing::Invoke([&](XMP_StringPtr itemValue, XMP_OptionBits options) {

        newChild = new XMP_Node_Mock(&arrayNode, "childName", itemValue, options);

        arrayNode.children.insert(arrayNode.children.begin() + 1, newChild);

    }));



    DoSetArrayItem(&arrayNode, 2, "newValue", kXMP_InsertAfterItem);



    EXPECT_EQ(arrayNode.children.size(), 2); // New child is inserted

}



TEST_F(DoSetArrayItemTest_1926, ModifyExistingAtPositionOne_1926) {

    EXPECT_CALL(*mockChildNode, SetNode("newValue", 0)).Times(1);

    DoSetArrayItem(&arrayNode, 1, "newValue", kXMP_InsertBeforeItem);

}
