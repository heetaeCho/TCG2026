#include <gtest/gtest.h>

#include "Link.h"

#include <vector>



// Test fixture for LinkOCGState class tests

class LinkOCGStateTest_326 : public ::testing::Test {

protected:

    // Create a mock Object to pass to the constructor of LinkOCGState

    MockObject mockObj;



    // Instance of LinkOCGState to be used in tests

    std::unique_ptr<LinkOCGState> linkOCGState;



    void SetUp() override {

        // Initialize the LinkOCGState with the mock object

        linkOCGState = std::make_unique<LinkOCGState>(&mockObj);

    }

};



// Test case for normal operation of getKind()

TEST_F(LinkOCGStateTest_326, GetKind_ReturnsActionOCGState_326) {

    EXPECT_EQ(linkOCGState->getKind(), actionOCGState);

}



// Test case for isOk() returning true

TEST_F(LinkOCGStateTest_326, IsOk_ReturnsTrue_326) {

    EXPECT_TRUE(linkOCGState->isOk());

}



// Test case for getStateList() returns an empty vector by default

TEST_F(LinkOCGStateTest_326, GetStateList_ReturnsEmptyVectorByDefault_326) {

    EXPECT_TRUE(linkOCGState->getStateList().empty());

}



// Test case for getPreserveRB() returning false by default

TEST_F(LinkOCGStateTest_326, GetPreserveRB_ReturnsFalseByDefault_326) {

    EXPECT_FALSE(linkOCGState->getPreserveRB());

}

```


