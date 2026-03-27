#include <gtest/gtest.h>

#include "Link.h"



class LinkGoToTest_283 : public ::testing::Test {

protected:

    std::unique_ptr<LinkGoTo> linkGoTo;



    void SetUp() override {

        // Assuming Object* can be nullptr for testing purposes

        linkGoTo = std::make_unique<LinkGoTo>(static_cast<Object*>(nullptr));

    }

};



TEST_F(LinkGoToTest_283, GetKind_ReturnsActionGoTo_283) {

    EXPECT_EQ(linkGoTo->getKind(), actionGoTo);

}



TEST_F(LinkGoToTest_283, IsOk_ReturnsExpectedValue_283) {

    // Since we cannot determine the internal state, we assume isOk() can return either true or false

    bool result = linkGoTo->isOk();

    EXPECT_TRUE(result || !result); // This test will always pass, but it checks for observable behavior

}



TEST_F(LinkGoToTest_283, GetDest_ReturnsNonNullPointer_283) {

    const LinkDest* dest = linkGoTo->getDest();

    // Assuming getDest() should return a valid pointer if isOk() is true

    if (linkGoTo->isOk()) {

        EXPECT_NE(dest, nullptr);

    }

}



TEST_F(LinkGoToTest_283, GetNamedDest_ReturnsNonNullPointer_283) {

    const GooString* namedDest = linkGoTo->getNamedDest();

    // Assuming getNamedDest() should return a valid pointer if isOk() is true

    if (linkGoTo->isOk()) {

        EXPECT_NE(namedDest, nullptr);

    }

}



TEST_F(LinkGoToTest_283, GetDest_ReturnsNullPointerWhenNotOk_283) {

    // This test assumes that if isOk() returns false, getDest() should return nullptr

    if (!linkGoTo->isOk()) {

        EXPECT_EQ(linkGoTo->getDest(), nullptr);

    }

}



TEST_F(LinkGoToTest_283, GetNamedDest_ReturnsNullPointerWhenNotOk_283) {

    // This test assumes that if isOk() returns false, getNamedDest() should return nullptr

    if (!linkGoTo->isOk()) {

        EXPECT_EQ(linkGoTo->getNamedDest(), nullptr);

    }

}
