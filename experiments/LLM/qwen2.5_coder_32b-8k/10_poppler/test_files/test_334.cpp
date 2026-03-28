#include <gtest/gtest.h>

#include "Link.h"

#include <vector>

#include <string>



using namespace testing;



class LinkResetFormTest_334 : public Test {

protected:

    std::unique_ptr<LinkResetForm> linkResetForm;

};



TEST_F(LinkResetFormTest_334, IsOk_ReturnsTrue_334) {

    // Arrange

    linkResetForm = std::make_unique<LinkResetForm>(nullptr);



    // Act & Assert

    EXPECT_TRUE(linkResetForm->isOk());

}



TEST_F(LinkResetFormTest_334, GetFields_ReturnsEmptyVectorByDefault_334) {

    // Arrange

    linkResetForm = std::make_unique<LinkResetForm>(nullptr);



    // Act

    const auto& fields = linkResetForm->getFields();



    // Assert

    EXPECT_TRUE(fields.empty());

}



TEST_F(LinkResetFormTest_334, GetExclude_ReturnsFalseByDefault_334) {

    // Arrange

    linkResetForm = std::make_unique<LinkResetForm>(nullptr);



    // Act & Assert

    EXPECT_FALSE(linkResetForm->getExclude());

}
