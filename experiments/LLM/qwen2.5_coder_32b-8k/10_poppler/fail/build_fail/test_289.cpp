#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Link.h"



using namespace testing;



class LinkGoToRTest : public ::testing::Test {

protected:

    MockObject fileSpecObj;

    MockObject destObj;

    std::unique_ptr<LinkGoToR> linkGoToR;



    virtual void SetUp() {

        linkGoToR = std::make_unique<LinkGoToR>(&fileSpecObj, &destObj);

    }

};



TEST_F(LinkGoToRTest_289, IsOkReturnsTrue_289) {

    EXPECT_CALL(fileSpecObj, isDict()).WillOnce(Return(true));

    EXPECT_CALL(destObj, isDict()).WillOnce(Return(true));



    EXPECT_TRUE(linkGoToR->isOk());

}



TEST_F(LinkGoToRTest_289, IsOkReturnsFalseIfFileSpecNotDict_289) {

    EXPECT_CALL(fileSpecObj, isDict()).WillOnce(Return(false));

    EXPECT_CALL(destObj, isDict()).WillOnce(Return(true));



    EXPECT_FALSE(linkGoToR->isOk());

}



TEST_F(LinkGoToRTest_289, IsOkReturnsFalseIfDestNotDict_289) {

    EXPECT_CALL(fileSpecObj, isDict()).WillOnce(Return(true));

    EXPECT_CALL(destObj, isDict()).WillOnce(Return(false));



    EXPECT_FALSE(linkGoToR->isOk());

}



TEST_F(LinkGoToRTest_289, GetKindReturnsCorrectValue_289) {

    EXPECT_EQ(linkGoToR->getKind(), LinkActionKind::goToR);

}



TEST_F(LinkGoToRTest_289, GetFileNameReturnsNonNullPointer_289) {

    EXPECT_NE(linkGoToR->getFileName(), nullptr);

}



TEST_F(LinkGoToRTest_289, GetNamedDestReturnsNonNullPointer_289) {

    EXPECT_NE(linkGoToR->getNamedDest(), nullptr);

}



TEST_F(LinkGoToRTest_289, GetDestReturnsNonNullPointer_289) {

    EXPECT_NE(linkGoToR->getDest(), nullptr);

}
