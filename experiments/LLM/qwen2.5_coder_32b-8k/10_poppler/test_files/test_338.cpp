#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Link.h"



using namespace testing;



class LinkSubmitFormTest_338 : public Test {

protected:

    std::unique_ptr<LinkSubmitForm> linkSubmitForm;

};



TEST_F(LinkSubmitFormTest_338, IsOk_ReturnsTrueForNonEmptyUrl_338) {

    // Arrange

    Object submitObj;  // Assuming Object is default constructible and suitable for this test

    linkSubmitForm = std::make_unique<LinkSubmitForm>(&submitObj);

    EXPECT_CALL(submitObj, getString()).WillOnce(Return("http://example.com"));



    // Act & Assert

    EXPECT_TRUE(linkSubmitForm->isOk());

}



TEST_F(LinkSubmitFormTest_338, IsOk_ReturnsFalseForEmptyUrl_338) {

    // Arrange

    Object submitObj;  // Assuming Object is default constructible and suitable for this test

    linkSubmitForm = std::make_unique<LinkSubmitForm>(&submitObj);

    EXPECT_CALL(submitObj, getString()).WillOnce(Return(""));



    // Act & Assert

    EXPECT_FALSE(linkSubmitForm->isOk());

}



TEST_F(LinkSubmitFormTest_338, GetUrl_ReturnsCorrectUrl_338) {

    // Arrange

    Object submitObj;  // Assuming Object is default constructible and suitable for this test

    linkSubmitForm = std::make_unique<LinkSubmitForm>(&submitObj);

    EXPECT_CALL(submitObj, getString()).WillOnce(Return("http://example.com"));



    // Act & Assert

    EXPECT_EQ(linkSubmitForm->getUrl(), "http://example.com");

}



TEST_F(LinkSubmitFormTest_338, GetFlags_ReturnsCorrectFlags_338) {

    // Arrange

    Object submitObj;  // Assuming Object is default constructible and suitable for this test

    linkSubmitForm = std::make_unique<LinkSubmitForm>(&submitObj);



    // Act & Assert

    EXPECT_EQ(linkSubmitForm->getFlags(), 0);

}



TEST_F(LinkSubmitFormTest_338, GetFields_ReturnsEmptyVectorByDefault_338) {

    // Arrange

    Object submitObj;  // Assuming Object is default constructible and suitable for this test

    linkSubmitForm = std::make_unique<LinkSubmitForm>(&submitObj);



    // Act & Assert

    EXPECT_TRUE(linkSubmitForm->getFields().empty());

}



TEST_F(LinkSubmitFormTest_338, GetKind_ReturnsLinkActionKindForSubmitForm_338) {

    // Arrange

    Object submitObj;  // Assuming Object is default constructible and suitable for this test

    linkSubmitForm = std::make_unique<LinkSubmitForm>(&submitObj);



    // Act & Assert

    EXPECT_EQ(linkSubmitForm->getKind(), LinkActionKind::SubmitForm);

}

```


