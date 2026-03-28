#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Link.h"



using namespace testing;



class LinkLaunchTest : public ::testing::Test {

protected:

    std::unique_ptr<LinkLaunch> linkLaunch;

};



TEST_F(LinkLaunchTest_293, GetFileName_ReturnsNonNulptrOnSuccess_293) {

    // Arrange

    MockObject mockActionObj;  // Assuming Object is a class that can be mocked

    LinkLaunch testLinkLaunch(&mockActionObj);

    

    // Act

    const GooString* fileName = testLinkLaunch.getFileName();



    // Assert

    EXPECT_NE(fileName, nullptr);

}



TEST_F(LinkLaunchTest_293, GetParams_ReturnsNonNulptrOnSuccess_293) {

    // Arrange

    MockObject mockActionObj;  // Assuming Object is a class that can be mocked

    LinkLaunch testLinkLaunch(&mockActionObj);



    // Act

    const GooString* params = testLinkLaunch.getParams();



    // Assert

    EXPECT_NE(params, nullptr);

}



TEST_F(LinkLaunchTest_293, IsOk_ReturnsTrueForValidObject_293) {

    // Arrange

    MockObject mockActionObj;  // Assuming Object is a class that can be mocked

    LinkLaunch testLinkLaunch(&mockActionObj);



    // Act

    bool isOkay = testLinkLaunch.isOk();



    // Assert

    EXPECT_TRUE(isOkay);

}



TEST_F(LinkLaunchTest_293, GetKind_ReturnsCorrectEnumValue_293) {

    // Arrange

    MockObject mockActionObj;  // Assuming Object is a class that can be mocked

    LinkLaunch testLinkLaunch(&mockActionObj);



    // Act

    LinkActionKind kind = testLinkLaunch.getKind();



    // Assert

    EXPECT_EQ(kind, link_launch);

}



// Assuming there are error cases or boundary conditions that can be tested.

TEST_F(LinkLaunchTest_293, IsOk_ReturnsFalseForInvalidObject_293) {

    // Arrange

    MockObject mockActionObj;  // Assuming Object is a class that can be mocked

    ON_CALL(mockActionObj, isValid()).WillByDefault(Return(false));

    LinkLaunch testLinkLaunch(&mockActionObj);



    // Act

    bool isOkay = testLinkLaunch.isOk();



    // Assert

    EXPECT_FALSE(isOkay);

}

```


