#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Link.h"



class LinkOCGStateTest_327 : public ::testing::Test {

protected:

    std::unique_ptr<LinkOCGState> linkOCGState;



    void SetUp() override {

        // Assuming Object* is a mockable or constructible object for testing purposes

        Object obj;

        linkOCGState = std::make_unique<LinkOCGState>(&obj);

    }

};



TEST_F(LinkOCGStateTest_327, IsOk_ReturnsTrue_327) {

    EXPECT_TRUE(linkOCGState->isOk());

}



TEST_F(LinkOCGStateTest_327, GetKind_ReturnsLinkActionKind_327) {

    // Assuming LinkActionKind is an enum and we know one of its values

    EXPECT_EQ(linkOCGState->getKind(), LinkActionKind::SomeKnownValue);

}



TEST_F(LinkOCGStateTest_327, GetStateList_ReturnsEmptyVector_327) {

    const std::vector<StateList>& stateList = linkOCGState->getStateList();

    EXPECT_TRUE(stateList.empty());

}



TEST_F(LinkOCGStateTest_327, GetPreserveRB_ReturnsFalseByDefault_327) {

    EXPECT_FALSE(linkOCGState->getPreserveRB());

}

```


