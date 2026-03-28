#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_97 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be done here if needed in future tests

    }



    void TearDown() override {

        // Teardown can be done here if needed in future tests

    }

};



TEST_F(ObjectTest_97, TakeString_NormalOperation_97) {

    std::unique_ptr<GooString> testString = std::make_unique<GooString>("test");

    Object obj(std::move(testString));

    

    auto result = obj.takeString();

    EXPECT_NE(result.get(), nullptr);

    EXPECT_STREQ(result->getCString(), "test");

    EXPECT_EQ(obj.getType(), objNull);

}



TEST_F(ObjectTest_97, TakeString_SecondCallReturnsNull_97) {

    std::unique_ptr<GooString> testString = std::make_unique<GooString>("test");

    Object obj(std::move(testString));

    

    obj.takeString();

    auto result = obj.takeString();

    EXPECT_EQ(result.get(), nullptr);

}



TEST_F(ObjectTest_97, TakeString_OnNonStringObject_ReturnsNull_97) {

    Object obj(42); // Assuming 42 is an int and not a string

    auto result = obj.takeString();

    EXPECT_EQ(result.get(), nullptr);

    EXPECT_EQ(obj.getType(), objInt);

}



TEST_F(ObjectTest_97, TakeString_StringObject_ReturnsValidString_97) {

    std::unique_ptr<GooString> testString = std::make_unique<GooString>("valid_string");

    Object obj(std::move(testString));

    

    auto result = obj.takeString();

    EXPECT_NE(result.get(), nullptr);

    EXPECT_STREQ(result->getCString(), "valid_string");

}



TEST_F(ObjectTest_97, TakeString_EmptyString_ReturnsEmptyGooString_97) {

    std::unique_ptr<GooString> testString = std::make_unique<GooString>("");

    Object obj(std::move(testString));

    

    auto result = obj.takeString();

    EXPECT_NE(result.get(), nullptr);

    EXPECT_STREQ(result->getCString(), "");

}
