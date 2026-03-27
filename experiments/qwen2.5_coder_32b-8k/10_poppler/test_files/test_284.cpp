#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Link.h"



using namespace testing;



class LinkGoToTest_284 : public ::testing::Test {

protected:

    MockObject mockDestObj;

    std::unique_ptr<LinkGoTo> linkGoTo;



    class MockObject {

    public:

        MOCK_METHOD(void, fetch, (), (const));

    };



    virtual void SetUp() {

        ON_CALL(mockDestObj, fetch()).WillByDefault(Return());

        linkGoTo = std::make_unique<LinkGoTo>(&mockDestObj);

    }

};



TEST_F(LinkGoToTest_284, GetDest_ReturnsNonNullPointer_284) {

    EXPECT_NE(linkGoTo->getDest(), nullptr);

}



TEST_F(LinkGoToTest_284, IsOk_ReturnsTrue_WhenValid_284) {

    EXPECT_TRUE(linkGoTo->isOk());

}



TEST_F(LinkGoToTest_284, GetKind_ReturnsExpectedValue_284) {

    EXPECT_EQ(linkGoTo->getKind(), LinkActionKind::gotoDest);

}



TEST_F(LinkGoToTest_284, GetNamedDest_ReturnsNullPointer_ByDefault_284) {

    EXPECT_EQ(linkGoTo->getNamedDest(), nullptr);

}
