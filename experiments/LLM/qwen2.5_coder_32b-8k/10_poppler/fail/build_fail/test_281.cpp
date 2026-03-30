#include <gtest/gtest.h>

#include "Link.h"



class LinkDestTest_281 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Assuming a valid Array constructor for LinkDest is available

        // Here we use a mock or dummy array for testing purposes

        Array mockArray;

        linkDest = new LinkDest(mockArray);

    }



    virtual void TearDown() {

        delete linkDest;

    }



    LinkDest* linkDest;

};



// Test normal operation of getChangeZoom

TEST_F(LinkDestTest_281, GetChangeZoom_ReturnsTrue_281) {

    // Assuming the mockArray is set up to make changeZoom true

    EXPECT_TRUE(linkDest->getChangeZoom());

}



TEST_F(LinkDestTest_281, GetChangeZoom_ReturnsFalse_281) {

    // Assuming the mockArray is set up to make changeZoom false

    EXPECT_FALSE(linkDest->getChangeZoom());

}



// Test boundary conditions (if any specific values are expected)

// For boolean values, there are no additional boundary conditions beyond true/false



// Test exceptional or error cases

// Since getChangeZoom() does not throw exceptions and only returns a bool,

// there are no exceptional cases to test for this method.



// No external interactions to verify as getChangeZoom does not depend on any handlers/callbacks
