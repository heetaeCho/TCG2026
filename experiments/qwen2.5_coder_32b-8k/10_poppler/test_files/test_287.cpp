#include <gtest/gtest.h>

#include "Link.h"

#include <gmock/gmock.h>



using namespace testing;



// Mock classes and dependencies if needed



class LinkGoToRTest : public ::testing::Test {

protected:

    std::unique_ptr<LinkGoToR> linkGoToR;



    void SetUp() override {

        // Assuming a way to create a valid instance of LinkGoToR

        Object fileSpecObj; // Placeholder, actual initialization needed

        Object destObj;     // Placeholder, actual initialization needed

        linkGoToR = std::make_unique<LinkGoToR>(&fileSpecObj, &destObj);

    }

};



TEST_F(LinkGoToRTest_287, GetKind_ReturnsActionGoToR_287) {

    EXPECT_EQ(linkGoToR->getKind(), actionGoToR);

}



TEST_F(LinkGoToRTest_287, IsOk_ReturnsExpectedValue_287) {

    // Assuming isOk() returns true for a valid object

    EXPECT_TRUE(linkGoToR->isOk());

}



TEST_F(LinkGoToRTest_287, GetFileName_ReturnsValidPointer_287) {

    EXPECT_NE(linkGoToR->getFileName(), nullptr);

}



TEST_F(LinkGoToRTest_287, GetDest_ReturnsValidPointer_287) {

    EXPECT_NE(linkGoToR->getDest(), nullptr);

}



TEST_F(LinkGoToRTest_287, GetNamedDest_ReturnsNullptrWhenNotSet_287) {

    EXPECT_EQ(linkGoToR->getNamedDest(), nullptr);

}

```


