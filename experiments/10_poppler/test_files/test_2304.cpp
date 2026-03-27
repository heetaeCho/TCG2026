#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Forward declarations for necessary types

struct _PopplerDocument;

class LinkDest;

extern "C" PopplerDest *_poppler_dest_new_goto(_PopplerDocument *document, LinkDest *link_dest);



// Mock class for LinkDest to verify interactions

class MockLinkDest : public LinkDest {

public:

    MOCK_CONST_METHOD0(isOk, bool());

    MOCK_CONST_METHOD0(getKind, LinkDestKind());

    MOCK_CONST_METHOD0(isPageRef, bool());

    MOCK_CONST_METHOD0(getPageNum, int());

    MOCK_CONST_METHOD0(getLeft, double());

    MOCK_CONST_METHOD0(getBottom, double());

    MOCK_CONST_METHOD0(getRight, double());

    MOCK_CONST_METHOD0(getTop, double());

    MOCK_CONST_METHOD0(getZoom, double());

    MOCK_CONST_METHOD0(getChangeLeft, bool());

    MOCK_CONST_METHOD0(getChangeTop, bool());

    MOCK_CONST_METHOD0(getChangeZoom, bool());

};



// Test fixture for PopplerDest creation

class PopplerDestTest_2304 : public ::testing::Test {

protected:

    MockLinkDest mock_link_dest;

    _PopplerDocument document;



    void SetUp() override {

        // Initialize necessary setup if needed

    }

};



TEST_F(PopplerDestTest_2304, NormalOperation_2304) {

    EXPECT_CALL(mock_link_dest, isOk()).WillOnce(::testing::Return(true));



    PopplerDest *dest = _poppler_dest_new_goto(&document, &mock_link_dest);

    ASSERT_NE(dest, nullptr);

}



TEST_F(PopplerDestTest_2304, InvalidLinkDest_2304) {

    EXPECT_CALL(mock_link_dest, isOk()).WillOnce(::testing::Return(false));



    PopplerDest *dest = _poppler_dest_new_goto(&document, &mock_link_dest);

    ASSERT_EQ(dest, nullptr);

}



TEST_F(PopplerDestTest_2304, BoundaryConditions_2304) {

    // Assuming boundary conditions might involve specific values for LinkDest properties

    EXPECT_CALL(mock_link_dest, isOk()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mock_link_dest, getLeft()).WillRepeatedly(::testing::Return(0.0));

    EXPECT_CALL(mock_link_dest, getBottom()).WillRepeatedly(::testing::Return(0.0));

    EXPECT_CALL(mock_link_dest, getRight()).WillRepeatedly(::testing::Return(1.0));

    EXPECT_CALL(mock_link_dest, getTop()).WillRepeatedly(::testing::Return(1.0));



    PopplerDest *dest = _poppler_dest_new_goto(&document, &mock_link_dest);

    ASSERT_NE(dest, nullptr);

}



// Assuming no direct exception handling in the interface, but testing invalid states

TEST_F(PopplerDestTest_2304, ExceptionalCase_2304) {

    // No exceptions expected from _poppler_dest_new_goto based on provided information

    EXPECT_CALL(mock_link_dest, isOk()).WillOnce(::testing::Return(false));



    PopplerDest *dest = _poppler_dest_new_goto(&document, &mock_link_dest);

    ASSERT_EQ(dest, nullptr);

}
