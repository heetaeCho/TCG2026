#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"

#include <memory>



class ObjectTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(ObjectTest_2757, ConstructorWithUniquePtrString_NormalOperation_2757) {

    auto stringA = std::make_unique<GooString>("test");

    Object obj(std::move(stringA));

    EXPECT_TRUE(obj.isString());

    EXPECT_EQ(strcmp(obj.getString()->c_str(), "test"), 0);

}



TEST_F(ObjectTest_2757, ConstructorWithUniquePtrString_EmptyString_NormalOperation_2757) {

    auto stringA = std::make_unique<GooString>("");

    Object obj(std::move(stringA));

    EXPECT_TRUE(obj.isString());

    EXPECT_EQ(strcmp(obj.getString()->c_str(), ""), 0);

}



TEST_F(ObjectTest_2757, ConstructorWithUniquePtrString_NullPointer_ExceptionalCase_2757) {

    EXPECT_THROW({

        std::unique_ptr<GooString> stringA = nullptr;

        Object obj(std::move(stringA));

    }, std::exception);

}



TEST_F(ObjectTest_2757, getType_ReturnsCorrectType_NormalOperation_2757) {

    auto stringA = std::make_unique<GooString>("test");

    Object obj(std::move(stringA));

    EXPECT_EQ(obj.getType(), objString);

}



TEST_F(ObjectTest_2757, isString_ReturnsTrueForStringObject_NormalOperation_2757) {

    auto stringA = std::make_unique<GooString>("test");

    Object obj(std::move(stringA));

    EXPECT_TRUE(obj.isString());

}



TEST_F(ObjectTest_2757, getString_ReturnsCorrectString_NormalOperation_2757) {

    auto stringA = std::make_unique<GooString>("test");

    Object obj(std::move(stringA));

    EXPECT_EQ(strcmp(obj.getString()->c_str(), "test"), 0);

}



TEST_F(ObjectTest_2757, takeString_ReturnsAndReleasesString_NormalOperation_2757) {

    auto stringA = std::make_unique<GooString>("test");

    Object obj(std::move(stringA));

    auto takenString = obj.takeString();

    EXPECT_EQ(strcmp(takenString->c_str(), "test"), 0);

    EXPECT_FALSE(obj.isString());

}



TEST_F(ObjectTest_2757, isNone_ReturnsTrueForDefaultConstructedObject_NormalOperation_2757) {

    Object obj;

    EXPECT_TRUE(obj.isNone());

}
