#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-action.cc"

#include "Link.h"

#include "Page.h"

#include "PopplerDocument.h"



using ::testing::_;

using ::testing::Return;

using ::testing::NiceMock;



class MockPopplerDocument : public PopplerDocument {

public:

    MOCK_METHOD1(findPage, int(const Ref&));

};



class MockPopplerPage : public PopplerPage {

public:

    MOCK_CONST_METHOD0(getCropBox, const PDFRectangle*());

};



class MockLinkDest : public LinkDest {

public:

    using LinkDest::LinkDest;

    MOCK_CONST_METHOD0(isOk, bool());

    MOCK_CONST_METHOD0(getKind, LinkDestKind());

    MOCK_CONST_METHOD0(isPageRef, bool());

    MOCK_CONST_METHOD0(getPageNum, int());

    MOCK_CONST_METHOD0(getPageRef, Ref());

    MOCK_CONST_METHOD0(getLeft, double());

    MOCK_CONST_METHOD0(getBottom, double());

    MOCK_CONST_METHOD0(getRight, double());

    MOCK_CONST_METHOD0(getTop, double());

    MOCK_CONST_METHOD0(getZoom, double());

    MOCK_CONST_METHOD0(getChangeLeft, bool());

    MOCK_CONST_METHOD0(getChangeTop, bool());

    MOCK_CONST_METHOD0(getChangeZoom, bool());

};



TEST_F(PopplerDestTest_2289, NullLinkDestReturnsUnknownType_2289) {

    MockPopplerDocument document;

    PopplerDest* dest = dest_new_goto(&document, nullptr);

    EXPECT_EQ(dest->type, POPPLER_DEST_UNKNOWN);

    g_slice_free(PopplerDest, dest);

}



TEST_F(PopplerDestTest_2289, ValidLinkDestSetsCorrectType_2289) {

    MockPopplerDocument document;

    NiceMock<MockLinkDest> link_dest;

    EXPECT_CALL(link_dest, getKind()).WillOnce(Return(destXYZ));



    PopplerDest* dest = dest_new_goto(&document, &link_dest);

    EXPECT_EQ(dest->type, POPPLER_DEST_XYZ);

    g_slice_free(PopplerDest, dest);

}



TEST_F(PopplerDestTest_2289, PageRefWithDocumentSetsCorrectPageNum_2289) {

    MockPopplerDocument document;

    NiceMock<MockLinkDest> link_dest;

    Ref page_ref = {1, 0};

    EXPECT_CALL(link_dest, isPageRef()).WillOnce(Return(true));

    EXPECT_CALL(link_dest, getPageRef()).WillOnce(Return(page_ref));

    EXPECT_CALL(document, findPage(page_ref)).WillOnce(Return(1));



    PopplerDest* dest = dest_new_goto(&document, &link_dest);

    EXPECT_EQ(dest->page_num, 1);

    g_slice_free(PopplerDest, dest);

}



TEST_F(PopplerDestTest_2289, PageRefWithoutDocumentSetsPageNumToZero_2289) {

    NiceMock<MockLinkDest> link_dest;

    Ref page_ref = {1, 0};

    EXPECT_CALL(link_dest, isPageRef()).WillOnce(Return(true));

    EXPECT_CALL(link_dest, getPageRef()).WillOnce(Return(page_ref));



    PopplerDest* dest = dest_new_goto(nullptr, &link_dest);

    EXPECT_EQ(dest->page_num, 0);

    g_slice_free(PopplerDest, dest);

}



TEST_F(PopplerDestTest_2289, InvalidPageRefSetsPageNumToZero_2289) {

    MockPopplerDocument document;

    NiceMock<MockLinkDest> link_dest;

    Ref page_ref = {1, 0};

    EXPECT_CALL(link_dest, isPageRef()).WillOnce(Return(true));

    EXPECT_CALL(link_dest, getPageRef()).WillOnce(Return(page_ref));

    EXPECT_CALL(document, findPage(page_ref)).WillOnce(Return(2)); // Simulate invalid page



    PopplerDest* dest = dest_new_goto(&document, &link_dest);

    EXPECT_EQ(dest->page_num, 0);

    g_slice_free(PopplerDest, dest);

}



TEST_F(PopplerDestTest_2289, NonPageRefSetsCorrectPageNum_2289) {

    NiceMock<MockLinkDest> link_dest;

    EXPECT_CALL(link_dest, isPageRef()).WillOnce(Return(false));

    EXPECT_CALL(link_dest, getPageNum()).WillOnce(Return(3));



    PopplerDest* dest = dest_new_goto(nullptr, &link_dest);

    EXPECT_EQ(dest->page_num, 3);

    g_slice_free(PopplerDest, dest);

}



TEST_F(PopplerDestTest_2289, PageCoordinatesAreAdjustedByCropBox_2289) {

    MockPopplerDocument document;

    NiceMock<MockLinkDest> link_dest;

    Ref page_ref = {1, 0};

    EXPECT_CALL(link_dest, isPageRef()).WillOnce(Return(true));

    EXPECT_CALL(link_dest, getPageRef()).WillOnce(Return(page_ref));

    EXPECT_CALL(document, findPage(page_ref)).WillOnce(Return(1));



    PDFRectangle crop_box(10, 20, 30, 40);

    MockPopplerPage page;

    EXPECT_CALL(page, getCropBox()).WillRepeatedly(Return(&crop_box));



    EXPECT_CALL(link_dest, getLeft()).WillOnce(Return(50));

    EXPECT_CALL(link_dest, getBottom()).WillOnce(Return(60));

    EXPECT_CALL(link_dest, getRight()).WillOnce(Return(70));

    EXPECT_CALL(link_dest, getTop()).WillOnce(Return(80));



    PopplerDest* dest = dest_new_goto(&document, &link_dest);

    EXPECT_EQ(dest->left, 40);   // 50 - 10

    EXPECT_EQ(dest->bottom, 40); // 60 - 20

    g_slice_free(PopplerDest, dest);

}
