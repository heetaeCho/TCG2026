#include <gtest/gtest.h>

#include "Link.h"



class LinkGoToTest_282 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any necessary preconditions before each test.

    }



    void TearDown() override {

        // Clean up after each test if necessary.

    }



    std::unique_ptr<LinkGoTo> createLinkGoToWithDest() {

        return std::make_unique<LinkGoTo>(new Object());

    }

};



TEST_F(LinkGoToTest_282, IsOk_ReturnsTrue_WhenDestIsSet_282) {

    auto link = createLinkGoToWithDest();

    EXPECT_TRUE(link->isOk());

}



TEST_F(LinkGoToTest_282, IsOk_ReturnsFalse_WhenNeitherDestNorNamedDestAreSet_282) {

    // Assuming the default constructor initializes both dest and namedDest to nullptr or invalid state.

    LinkGoTo link(nullptr);

    EXPECT_FALSE(link->isOk());

}



// Boundary condition test: Check if isOk returns true when only one of the destinations is set.

TEST_F(LinkGoToTest_282, IsOk_ReturnsTrue_WhenNamedDestIsSetAndDestIsNull_282) {

    // Assuming there's a way to create an object with namedDest set and dest null.

    // This test case is hypothetical as the constructor only takes one argument.

    // If there's another way to set namedDest, you would need to implement that here.

}



TEST_F(LinkGoToTest_282, IsOk_ReturnsTrue_WhenDestIsSetAndNamedDestIsNull_282) {

    auto link = createLinkGoToWithDest();

    EXPECT_TRUE(link->isOk());

}

```


