#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-action.cc"

#include "Link.h"



using namespace testing;



// Mocking LinkGoToR class to control its behavior for testing.

class MockLinkGoToR : public LinkGoToR {

public:

    MOCK_CONST_METHOD0(isOk, bool());

    MOCK_CONST_METHOD0(getFileName, const GooString*());

    MOCK_CONST_METHOD0(getDest, const LinkDest*());

    MOCK_CONST_METHOD0(getNamedDest, const GooString*());



    MockLinkGoToR(Object *fileSpecObj, Object *destObj) : LinkGoToR(fileSpecObj, destObj) {}

};



// Test fixture for PopplerAction tests.

class PopplerActionTest_2292 : public ::testing::Test {

protected:

    PopplerAction action;

    MockLinkGoToR mock_link{nullptr, nullptr};

};



// Test case: Normal operation with valid LinkDest

TEST_F(PopplerActionTest_2292, BuildGotoRemoteWithValidLinkDest_2292) {

    const LinkDest* link_dest = new LinkDest();

    EXPECT_CALL(mock_link, isOk()).WillOnce(Return(true));

    EXPECT_CALL(mock_link, getFileName()).WillOnce(Return(new GooString("test.pdf")));

    EXPECT_CALL(mock_link, getDest()).WillOnce(Return(link_dest));



    build_goto_remote(&action, &mock_link);



    ASSERT_NE(action.goto_remote.dest, nullptr);

    delete action.goto_remote.file_name;

    delete link_dest;

}



// Test case: Normal operation with valid NamedDest

TEST_F(PopplerActionTest_2292, BuildGotoRemoteWithValidNamedDest_2292) {

    const GooString* named_dest = new GooString("named_dest");

    EXPECT_CALL(mock_link, isOk()).WillOnce(Return(true));

    EXPECT_CALL(mock_link, getFileName()).WillOnce(Return(new GooString("test.pdf")));

    EXPECT_CALL(mock_link, getDest()).WillOnce(Return(nullptr));

    EXPECT_CALL(mock_link, getNamedDest()).WillOnce(Return(named_dest));



    build_goto_remote(&action, &mock_link);



    ASSERT_NE(action.goto_remote.dest, nullptr);

    delete action.goto_remote.file_name;

    delete named_dest;

}



// Test case: Normal operation with no LinkDest or NamedDest

TEST_F(PopplerActionTest_2292, BuildGotoRemoteWithNoDestination_2292) {

    EXPECT_CALL(mock_link, isOk()).WillOnce(Return(true));

    EXPECT_CALL(mock_link, getFileName()).WillOnce(Return(new GooString("test.pdf")));

    EXPECT_CALL(mock_link, getDest()).WillOnce(Return(nullptr));

    EXPECT_CALL(mock_link, getNamedDest()).WillOnce(Return(nullptr));



    build_goto_remote(&action, &mock_link);



    ASSERT_EQ(action.goto_remote.dest, nullptr);

    delete action.goto_remote.file_name;

}



// Test case: Boundary condition with empty file name

TEST_F(PopplerActionTest_2292, BuildGotoRemoteWithEmptyFileName_2292) {

    EXPECT_CALL(mock_link, isOk()).WillOnce(Return(true));

    EXPECT_CALL(mock_link, getFileName()).WillOnce(Return(new GooString("")));

    EXPECT_CALL(mock_link, getDest()).WillOnce(Return(nullptr));

    EXPECT_CALL(mock_link, getNamedDest()).WillOnce(Return(nullptr));



    build_goto_remote(&action, &mock_link);



    ASSERT_EQ(action.goto_remote.dest, nullptr);

    delete action.goto_remote.file_name;

}



// Test case: Exceptional case with isOk() returning false

TEST_F(PopplerActionTest_2292, BuildGotoRemoteWithIsOkFalse_2292) {

    EXPECT_CALL(mock_link, isOk()).WillOnce(Return(false));



    build_goto_remote(&action, &mock_link);



    ASSERT_EQ(action.goto_remote.dest, nullptr);

    ASSERT_EQ(action.goto_remote.file_name, nullptr);

}
