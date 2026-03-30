#include <gtest/gtest.h>

#include "Link.h"

#include <gmock/gmock-matchers.h>



using namespace testing;



class LinkGoToRTest : public ::testing::Test {

protected:

    std::unique_ptr<LinkGoToR> link;



    virtual void SetUp() {

        // Assuming Object is a placeholder for actual object creation

        link = std::make_unique<LinkGoToR>(nullptr, nullptr);

    }

};



TEST_F(LinkGoToRTest_288, GetFileNameReturnsNonNullPointer_288) {

    EXPECT_NE(link->getFileName(), nullptr);

}



TEST_F(LinkGoToRTest_288, IsOkReturnsTrueForValidObject_288) {

    EXPECT_TRUE(link->isOk());

}



TEST_F(LinkGoToRTest_288, GetKindReturnsExpectedValue_288) {

    // Assuming LinkActionKind is an enum and we know the expected value for LinkGoToR

    EXPECT_EQ(link->getKind(), LinkActionKind::goto_remote);

}



TEST_F(LinkGoToRTest_288, GetDestReturnsNonNullPointer_288) {

    EXPECT_NE(link->getDest(), nullptr);

}



TEST_F(LinkGoToRTest_288, GetNamedDestReturnsNullForNonNamedDestination_288) {

    EXPECT_EQ(link->getNamedDest(), nullptr);

}

```



**Notes:**

- `Object` is assumed to be a placeholder for actual object creation which might require specific parameters. This would need adjustment based on the actual implementation details.

- `LinkActionKind::goto_remote` is an assumption based on typical usage in similar libraries, and it should match the expected kind for `LinkGoToR`.
