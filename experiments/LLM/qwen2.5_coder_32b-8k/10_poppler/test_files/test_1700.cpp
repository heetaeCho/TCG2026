#include <gtest/gtest.h>

#include "poppler/StructElement.h"



class StructElementTest : public ::testing::Test {

protected:

    StructElement* element;

    StructElement* parentElement;



    void SetUp() override {

        parentElement = new StructElement(/*args*/);

        element = new StructElement(/*args*/);

        element->parent = parentElement;

    }



    void TearDown() override {

        delete element;

        delete parentElement;

    }

};



TEST_F(StructElementTest_1700, GetLanguage_ReturnsParentLanguageWhenNotContent_1700) {

    auto mockParentLanguage = new GooString("en-US");

    parentElement->s->language.reset(mockParentLanguage);



    EXPECT_EQ(element->getLanguage(), mockParentLanguage);

}



TEST_F(StructElementTest_1700, GetLanguage_ReturnsNullWhenNoParentAndNotContent_1700) {

    element->parent = nullptr;



    EXPECT_EQ(element->getLanguage(), nullptr);

}



TEST_F(StructElementTest_1700, GetLanguage_ReturnsOwnLanguageWhenContent_1700) {

    auto mockLanguage = new GooString("fr-FR");

    element->s->language.reset(mockLanguage);



    ON_CALL(*element, isContent()).WillByDefault(::testing::Return(true));



    EXPECT_EQ(element->getLanguage(), mockLanguage);

}



TEST_F(StructElementTest_1700, GetLanguage_ReturnsNullWhenNoOwnLanguageAndNotContent_1700) {

    element->parent = nullptr;



    EXPECT_EQ(element->getLanguage(), nullptr);

}
