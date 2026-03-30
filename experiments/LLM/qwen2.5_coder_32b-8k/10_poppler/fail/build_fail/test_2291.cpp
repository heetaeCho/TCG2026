#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock classes for LinkGoTo and GooString

class MockLinkGoTo : public LinkGoTo {

public:

    MOCK_CONST_METHOD0(isOk, bool());

    MOCK_CONST_METHOD0(getDest, const LinkDest*());

    MOCK_CONST_METHOD0(getNamedDest, const GooString*());



    MockLinkGoTo() : LinkGoTo(nullptr) {}

};



// Mock classes for LinkDest and GooString

class MockLinkDest : public LinkDest {

public:

    MockLinkDest() : LinkDest() {}

};



class MockGooString : public GooString {

public:

    MockGooString() : GooString() {}

};



// Test fixture class

class PopplerActionTest_2291 : public ::testing::Test {

protected:

    void SetUp() override {

        document = new _PopplerDocument();

        action = new PopplerAction();

    }



    void TearDown() override {

        delete document;

        delete action;

    }



    _PopplerDocument* document;

    PopplerAction* action;

};



// Test cases

TEST_F(PopplerActionTest_2291, PutIncreasesCount_NormalOperation_2291) {

    MockLinkGoTo mock_link;

    const MockLinkDest mock_dest;



    EXPECT_CALL(mock_link, isOk()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mock_link, getDest()).WillOnce(::testing::Return(&mock_dest));

    EXPECT_CALL(mock_link, getNamedDest()).WillOnce(::testing::Return(nullptr));



    build_goto_dest(document, action, &mock_link);



    ASSERT_NE(action->goto_dest.dest, nullptr);

}



TEST_F(PopplerActionTest_2291, PutIncreasesCount_NamedDest_2291) {

    MockLinkGoTo mock_link;

    const MockGooString mock_named_dest;



    EXPECT_CALL(mock_link, isOk()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mock_link, getDest()).WillOnce(::testing::Return(nullptr));

    EXPECT_CALL(mock_link, getNamedDest()).WillOnce(::testing::Return(&mock_named_dest));



    build_goto_dest(document, action, &mock_link);



    ASSERT_NE(action->goto_dest.dest, nullptr);

}



TEST_F(PopplerActionTest_2291, PutIncreasesCount_NoDestOrNamedDest_2291) {

    MockLinkGoTo mock_link;



    EXPECT_CALL(mock_link, isOk()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mock_link, getDest()).WillOnce(::testing::Return(nullptr));

    EXPECT_CALL(mock_link, getNamedDest()).WillOnce(::testing::Return(nullptr));



    build_goto_dest(document, action, &mock_link);



    ASSERT_NE(action->goto_dest.dest, nullptr);

}



TEST_F(PopplerActionTest_2291, PutIncreasesCount_IsNotOk_2291) {

    MockLinkGoTo mock_link;



    EXPECT_CALL(mock_link, isOk()).WillOnce(::testing::Return(false));

    EXPECT_CALL(mock_link, getDest()).Times(0);

    EXPECT_CALL(mock_link, getNamedDest()).Times(0);



    build_goto_dest(document, action, &mock_link);



    ASSERT_EQ(action->goto_dest.dest, nullptr);

}
