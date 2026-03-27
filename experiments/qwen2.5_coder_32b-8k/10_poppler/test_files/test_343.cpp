#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Link.h"



using namespace testing;



class LinkUnknownTest_343 : public ::testing::Test {

protected:

    std::string action;

    LinkUnknown* linkUnknown;



    void SetUp() override {

        action = "unknown_action";

        linkUnknown = new LinkUnknown(std::move(action));

    }



    void TearDown() override {

        delete linkUnknown;

    }

};



TEST_F(LinkUnknownTest_343, IsOk_ReturnsTrue_343) {

    EXPECT_TRUE(linkUnknown->isOk());

}



TEST_F(LinkUnknownTest_343, GetAction_ReturnsCorrectAction_343) {

    EXPECT_EQ(linkUnknown->getAction(), action);

}



TEST_F(LinkUnknownTest_343, GetKind_ReturnsExpectedValue_343) {

    EXPECT_EQ(linkUnknown->getKind(), LinkActionKind::Unknown); // Assuming LinkActionKind::Unknown is defined

}
