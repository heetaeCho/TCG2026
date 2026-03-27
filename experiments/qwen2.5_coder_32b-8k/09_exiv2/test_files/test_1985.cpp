#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPUtils.cpp"

#include "XMPCore_Impl.hpp"

#include "XMPMeta.hpp"



using namespace std;



class XMPUtilsTest_1985 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize the XMPMeta object

        xmpMeta = new XMPMeta();

    }



    void TearDown() override {

        // Clean up the XMPMeta object

        delete xmpMeta;

    }



    XMPMeta* xmpMeta;

};



TEST_F(XMPUtilsTest_1985, CreateEstimatedSizeMap_NoChildren_1985) {

    PropSizeMap propSizes;

    CreateEstimatedSizeMap(*xmpMeta, &propSizes);

    EXPECT_TRUE(propSizes.empty());

}



TEST_F(XMPUtilsTest_1985, CreateEstimatedSizeMap_OneChild_1985) {

    XMP_Node* schemaNode = new XMP_Node(nullptr, "http://example.com/schema", 0);

    xmpMeta->tree.children.push_back(schemaNode);



    XMP_Node* propNode = new XMP_Node(schemaNode, "property1", "value1", 0);

    schemaNode->children.push_back(propNode);



    PropSizeMap propSizes;

    CreateEstimatedSizeMap(*xmpMeta, &propSizes);

    EXPECT_EQ(propSizes.size(), 1);



    delete propNode;

    delete schemaNode;

}



TEST_F(XMPUtilsTest_1985, CreateEstimatedSizeMap_MultipleChildren_1985) {

    XMP_Node* schemaNode = new XMP_Node(nullptr, "http://example.com/schema", 0);

    xmpMeta->tree.children.push_back(schemaNode);



    for (int i = 0; i < 3; ++i) {

        std::string propName = "property" + std::to_string(i+1);

        std::string propValue = "value" + std::to_string(i+1);

        XMP_Node* propNode = new XMP_Node(schemaNode, propName.c_str(), propValue.c_str(), 0);

        schemaNode->children.push_back(propNode);

    }



    PropSizeMap propSizes;

    CreateEstimatedSizeMap(*xmpMeta, &propSizes);

    EXPECT_EQ(propSizes.size(), 3);



    for (auto& child : schemaNode->children) {

        delete child;

    }

    delete schemaNode;

}



TEST_F(XMPUtilsTest_1985, CreateEstimatedSizeMap_SkipXmpNoteHasExtendedXMP_1985) {

    XMP_Node* schemaNode = new XMP_Node(nullptr, kXMP_NS_XMP_Note, 0);

    xmpMeta->tree.children.push_back(schemaNode);



    XMP_Node* propNode = new XMP_Node(schemaNode, "xmpNote:HasExtendedXMP", "value1", 0);

    schemaNode->children.push_back(propNode);



    PropSizeMap propSizes;

    CreateEstimatedSizeMap(*xmpMeta, &propSizes);

    EXPECT_TRUE(propSizes.empty());



    delete propNode;

    delete schemaNode;

}
