#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Link.h"



class LinkNamedTest_299 : public ::testing::Test {

protected:

    std::unique_ptr<LinkNamed> linkNamed;



    void SetUp() override {

        // Assuming Object is a mockable or testable class

        const Object* nameObj = nullptr; // This should be replaced with actual object creation if necessary

        linkNamed = std::make_unique<LinkNamed>(nameObj);

    }

};



TEST_F(LinkNamedTest_299, GetKindReturnsActionNamed_299) {

    EXPECT_EQ(linkNamed->getKind(), actionNamed);

}



TEST_F(LinkNamedTest_299, IsOkReturnsTrue_299) {

    EXPECT_TRUE(linkNamed->isOk());

}



TEST_F(LinkNamedTest_299, GetNameReturnsValidString_299) {

    EXPECT_FALSE(linkNamed->getName().empty()); // Assuming getName should not return an empty string if isOk() returns true

}
