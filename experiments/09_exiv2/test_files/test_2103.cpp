#include <gtest/gtest.h>

#include "XMPIterator.hpp"

#include "XMPMeta.hpp"



using namespace std;



class XMPIteratorTest : public ::testing::Test {

protected:

    XMPMeta xmpObj;

    IterInfo info;

    IterPos start, end;



    void SetUp() override {

        // Initialize the XMPMeta object and set up IterInfo

        xmpObj.Initialize();

        info = IterInfo(kXMP_IterProperties, &xmpObj);

        start = IterPos();  // Assuming default constructor sets to a valid starting position

        end = IterPos();    // Assuming default constructor sets to a valid ending position

        info.currPos = start;

        info.endPos = end;

    }



    void TearDown() override {

        xmpObj.Terminate();

    }

};



TEST_F(XMPIteratorTest_2103, GetNextXMPNode_NormalOperation_2103) {

    // Set up a scenario where there is at least one node to iterate over

    XMPMeta* xmp = const_cast<XMPMeta*>(info.xmpObj);

    xmp->SetProperty("http://example.com/schema", "propName", "propValue", 0);



    const XMP_Node *node = GetNextXMPNode(info);

    ASSERT_NE(node, nullptr);

}



TEST_F(XMPIteratorTest_2103, GetNextXMPNode_NoNodes_2103) {

    // Set up a scenario where there are no nodes to iterate over

    const XMP_Node *node = GetNextXMPNode(info);

    ASSERT_EQ(node, nullptr);

}



TEST_F(XMPIteratorTest_2103, GetNextXMPNode_SchemaNode_2103) {

    // Set up a scenario where the current position is a schema node

    XMPMeta* xmp = const_cast<XMPMeta*>(info.xmpObj);

    xmp->RegisterNamespace("http://example.com/schema", "ex");

    xmp->SetProperty("http://example.com/schema", "propName", "propValue", 0);



    info.currPos->fullPath = "ex";

    info.currPos->options = XMP_NodeIsSchema(info.currPos->options); // Mocking the schema node condition



    const XMP_Node *node = GetNextXMPNode(info);

    ASSERT_NE(node, nullptr);

}



TEST_F(XMPIteratorTest_2103, GetNextXMPNode_EndPosition_2103) {

    // Set up a scenario where the current position is at the end position

    info.currPos = info.endPos;



    const XMP_Node *node = GetNextXMPNode(info);

    ASSERT_EQ(node, nullptr);

}



TEST_F(XMPIteratorTest_2103, GetNextXMPNode_JustChildren_2103) {

    // Set up a scenario with the kXMP_IterJustChildren option set

    XMPMeta* xmp = const_cast<XMPMeta*>(info.xmpObj);

    xmp->RegisterNamespace("http://example.com/schema", "ex");

    xmp->SetProperty("http://example.com/schema", "propName", "propValue", 0);



    info.options |= kXMP_IterJustChildren;



    const XMP_Node *node = GetNextXMPNode(info);

    ASSERT_NE(node, nullptr);

}



TEST_F(XMPIteratorTest_2103, GetNextXMPNode_VisitStageBeforeVisit_2103) {

    // Set up a scenario where the visit stage is kIter_BeforeVisit

    XMPMeta* xmp = const_cast<XMPMeta*>(info.xmpObj);

    xmp->SetProperty("http://example.com/schema", "propName", "propValue", 0);



    info.currPos->visitStage = kIter_BeforeVisit;



    const XMP_Node *node = GetNextXMPNode(info);

    ASSERT_NE(node, nullptr);

}



TEST_F(XMPIteratorTest_2103, GetNextXMPNode_VisitStageAfterVisit_2103) {

    // Set up a scenario where the visit stage is not kIter_BeforeVisit

    XMPMeta* xmp = const_cast<XMPMeta*>(info.xmpObj);

    xmp->SetProperty("http://example.com/schema", "propName", "propValue", 0);



    info.currPos->visitStage = kIter_VisitChildren;



    const XMP_Node *node = GetNextXMPNode(info);

    ASSERT_NE(node, nullptr);

}



TEST_F(XMPIteratorTest_2103, GetNextXMPNode_DummySchema_2103) {

    // Set up a scenario where the schema node is not found

    XMPMeta* xmp = const_cast<XMPMeta*>(info.xmpObj);

    xmp->RegisterNamespace("http://example.com/schema", "ex");



    info.currPos->fullPath = "ex";

    info.currPos->options = XMP_NodeIsSchema(info.currPos->options); // Mocking the schema node condition



    const XMP_Node *node = GetNextXMPNode(info);

    ASSERT_EQ(node, sDummySchema);

}
