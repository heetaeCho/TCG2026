#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"

#include "XMP_Const.h"



using namespace std;



class AppendSubtreeTest_1923 : public ::testing::Test {

protected:

    XMP_Node* sourceNode;

    XMP_Node* destParent;

    XMP_Node* destNode;



    void SetUp() override {

        sourceNode = new XMP_Node(nullptr, "sourceName", 0);

        destParent = new XMP_Node(nullptr, "destParentName", 0);

        destNode = nullptr;

    }



    void TearDown() override {

        delete sourceNode;

        delete destParent;

        if (destNode) {

            delete destNode;

        }

    }



    void appendSubtreeWithDeleteEmpty(bool replaceOld, bool deleteEmpty) {

        AppendSubtree(sourceNode, destParent, replaceOld, deleteEmpty);

        if (!destNode) {

            destNode = FindChildNode(destParent, sourceNode->name.c_str(), kXMP_ExistingOnly, nullptr);

        }

    }



    XMP_Node* FindChildNode(XMP_Node* parent, const char* name, XMP_OptionBits options, XMP_NodePtrPos* pos) {

        for (size_t i = 0; i < parent->children.size(); ++i) {

            if (parent->children[i]->name == name) {

                if (pos) *pos = i;

                return parent->children[i];

            }

        }

        return nullptr;

    }



    void CloneSubtree(const XMP_Node* source, XMP_Node* dest) {

        // Mock implementation for testing purposes

        XMP_Node* newNode = new XMP_Node(dest, source->name, source->value, source->options);

        dest->children.push_back(newNode);

    }



    void CloneOffspring(const XMP_Node* source, XMP_Node* dest) {

        // Mock implementation for testing purposes

        for (const auto& child : source->children) {

            CloneSubtree(child, dest);

        }

    }



    bool ItemValuesMatch(const XMP_Node* sourceItem, const XMP_Node* destItem) {

        // Mock implementation for testing purposes

        return sourceItem->value == destItem->value;

    }



    XMP_Index LookupLangItem(XMP_Node* node, const std::string& lang) {

        // Mock implementation for testing purposes

        for (size_t i = 0; i < node->children.size(); ++i) {

            if (!node->children[i]->qualifiers.empty() && 

                node->children[i]->qualifiers[0]->value == lang) {

                return i;

            }

        }

        return -1;

    }

};



TEST_F(AppendSubtreeTest_1923, NormalOperation_ReplaceOldFalse_DeleteEmptyTrue_1923) {

    sourceNode->value = "sourceValue";

    destParent->children.push_back(new XMP_Node(destParent, "sourceName", "destValue", 0));

    appendSubtreeWithDeleteEmpty(false, true);

    EXPECT_EQ(destNode->value, "destValue");

}



TEST_F(AppendSubtreeTest_1923, NormalOperation_ReplaceOldTrue_DeleteEmptyFalse_1923) {

    sourceNode->value = "sourceValue";

    destParent->children.push_back(new XMP_Node(destParent, "sourceName", "destValue", 0));

    appendSubtreeWithDeleteEmpty(true, false);

    EXPECT_EQ(destNode->value, "sourceValue");

}



TEST_F(AppendSubtreeTest_1923, BoundaryCondition_EmptySourceValue_DeleteEmptyTrue_1923) {

    sourceNode->options = kXMP_PropIsSimple;

    appendSubtreeWithDeleteEmpty(false, true);

    EXPECT_EQ(destParent->children.size(), 0u);

}



TEST_F(AppendSubtreeTest_1923, BoundaryCondition_EmptySourceChildren_DeleteEmptyTrue_1923) {

    sourceNode->options = kXMP_PropValueIsStruct;

    appendSubtreeWithDeleteEmpty(false, true);

    EXPECT_EQ(destParent->children.size(), 0u);

}



TEST_F(AppendSubtreeTest_1923, ExceptionalCase_DifferentForm_ReturnsEarly_1923) {

    sourceNode->options = kXMP_PropValueIsStruct;

    destParent->children.push_back(new XMP_Node(destParent, "sourceName", "", 0));

    appendSubtreeWithDeleteEmpty(false, false);

    EXPECT_EQ(destNode->value, "");

}



TEST_F(AppendSubtreeTest_1923, ExternalInteraction_CloneOffspringCalled_1923) {

    sourceNode->options = kXMP_PropValueIsStruct;

    XMP_Node* child = new XMP_Node(sourceNode, "childName", "childValue", 0);

    sourceNode->children.push_back(child);



    EXPECT_CALL(*this, CloneOffspring).Times(1);

    appendSubtreeWithDeleteEmpty(false, false);

}



TEST_F(AppendSubtreeTest_1923, ExternalInteraction_CloneSubtreeCalled_1923) {

    EXPECT_CALL(*this, CloneSubtree).Times(1);

    appendSubtreeWithDeleteEmpty(false, false);

}

```



**Note:** The above test cases assume that the mock functions `CloneOffspring` and `CloneSubtree` are part of the test fixture for demonstration purposes. Since Google Mock is not being used to simulate internal behavior, these methods are provided as mocks to allow testing without changing the existing codebase structure significantly. 


