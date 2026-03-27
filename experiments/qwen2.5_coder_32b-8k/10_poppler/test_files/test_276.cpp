#include <gtest/gtest.h>

#include "Link.h"



class LinkDestTest_276 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Initialize any necessary objects or variables here.

        // Since we don't have a constructor that takes parameters, we'll assume default initialization is sufficient for basic tests.

        // In practice, you might need to mock or set up dependencies if the class had them.

    }



    virtual void TearDown() {

        // Clean up any resources after each test, if necessary.

    }

};



TEST_F(LinkDestTest_276, GetRightReturnsDefaultValue_276) {

    LinkDest linkDest = LinkDest(Array());  // Assuming Array is a valid type and default constructor works

    EXPECT_DOUBLE_EQ(0.0, linkDest.getRight());

}



// Additional test cases for other functions



TEST_F(LinkDestTest_276, IsOkReturnsFalseForDefaultConstructedObject_276) {

    LinkDest linkDest = LinkDest(Array());  // Assuming Array is a valid type and default constructor works

    EXPECT_FALSE(linkDest.isOk());

}



TEST_F(LinkDestTest_276, GetKindReturnsDefaultValue_276) {

    LinkDest linkDest = LinkDest(Array());  // Assuming Array is a valid type and default constructor works

    EXPECT_EQ(static_cast<LinkDestKind>(0), linkDest.getKind());

}



TEST_F(LinkDestTest_276, IsPageRefReturnsFalseForDefaultConstructedObject_276) {

    LinkDest linkDest = LinkDest(Array());  // Assuming Array is a valid type and default constructor works

    EXPECT_FALSE(linkDest.isPageRef());

}



TEST_F(LinkDestTest_276, GetPageNumReturnsDefaultValue_276) {

    LinkDest linkDest = LinkDest(Array());  // Assuming Array is a valid type and default constructor works

    EXPECT_EQ(0, linkDest.getPageNum());

}



TEST_F(LinkDestTest_276, GetLeftReturnsDefaultValue_276) {

    LinkDest linkDest = LinkDest(Array());  // Assuming Array is a valid type and default constructor works

    EXPECT_DOUBLE_EQ(0.0, linkDest.getLeft());

}



TEST_F(LinkDestTest_276, GetBottomReturnsDefaultValue_276) {

    LinkDest linkDest = LinkDest(Array());  // Assuming Array is a valid type and default constructor works

    EXPECT_DOUBLE_EQ(0.0, linkDest.getBottom());

}



TEST_F(LinkDestTest_276, GetTopReturnsDefaultValue_276) {

    LinkDest linkDest = LinkDest(Array());  // Assuming Array is a valid type and default constructor works

    EXPECT_DOUBLE_EQ(0.0, linkDest.getTop());

}



TEST_F(LinkDestTest_276, GetZoomReturnsDefaultValue_276) {

    LinkDest linkDest = LinkDest(Array());  // Assuming Array is a valid type and default constructor works

    EXPECT_DOUBLE_EQ(0.0, linkDest.getZoom());

}



TEST_F(LinkDestTest_276, GetChangeLeftReturnsDefaultValue_276) {

    LinkDest linkDest = LinkDest(Array());  // Assuming Array is a valid type and default constructor works

    EXPECT_FALSE(linkDest.getChangeLeft());

}



TEST_F(LinkDestTest_276, GetChangeTopReturnsDefaultValue_276) {

    LinkDest linkDest = LinkDest(Array());  // Assuming Array is a valid type and default constructor works

    EXPECT_FALSE(linkDest.getChangeTop());

}



TEST_F(LinkDestTest_276, GetChangeZoomReturnsDefaultValue_276) {

    LinkDest linkDest = LinkDest(Array());  // Assuming Array is a valid type and default constructor works

    EXPECT_FALSE(linkDest.getChangeZoom());

}

```


