#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/Page.h"

#include "poppler/Object.h"



using namespace testing;



class MockXRef : public XRef {

public:

    MOCK_METHOD2(fetch, Object(Object&, int));

};



class PageTest_725 : public Test {

protected:

    std::unique_ptr<MockXRef> mockXRef;

    Object pageDict;

    Ref pageRef;

    std::unique_ptr<PageAttrs> attrs;

    Page page;



    PageTest_725() 

        : mockXRef(std::make_unique<StrictMock<MockXRef>>()),

          page(nullptr, 1, std::move(pageDict), pageRef, std::move(attrs)) {}

};



TEST_F(PageTest_725, GetThumb_NormalOperation_725) {

    Object expectedThumb;

    EXPECT_CALL(*mockXRef, fetch(_, _)).WillOnce(Return(expectedThumb));



    Object thumb = page.getThumb();

    EXPECT_EQ(thumb.getType(), expectedThumb.getType());

}



TEST_F(PageTest_725, GetThumb_BoundaryCondition_NoMockCall_725) {

    // Assuming that if no XRef is provided, the internal state of 'thumb' is returned directly.

    Object thumb = page.getThumb();

    EXPECT_EQ(thumb.getType(), objNone);  // Default type of an uninitialized Object

}



// Since there are no error cases or exceptional behavior explicitly observable through getThumb,

// and we cannot mock internal behavior, further specific error tests are not possible.



TEST_F(PageTest_725, GetThumb_VerifyExternalInteraction_725) {

    Object expectedThumb;

    EXPECT_CALL(*mockXRef, fetch(_, _)).WillOnce(Return(expectedThumb));



    page.getThumb();

}



// Since there is no observable behavior other than the return value and no external collaborators

// that are not XRef (which we mock), further tests would be redundant.
