#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(ObjectTest_2747, NormalStringConstruction_2747) {

    std::string testString = "test";

    Object obj(std::move(testString));

    EXPECT_EQ(obj.getType(), objString);

    EXPECT_TRUE(obj.isString());

}



TEST_F(ObjectTest_2747, EmptyStringConstruction_2747) {

    std::string emptyString = "";

    Object obj(std::move(emptyString));

    EXPECT_EQ(obj.getType(), objString);

    EXPECT_TRUE(obj.isString());

}



TEST_F(ObjectTest_2747, LongStringConstruction_2747) {

    std::string longString(1000, 'a');

    Object obj(std::move(longString));

    EXPECT_EQ(obj.getType(), objString);

    EXPECT_TRUE(obj.isString());

}



TEST_F(ObjectTest_2747, StringValueRetrieval_2747) {

    std::string testString = "test";

    Object obj(std::move(testString));

    const GooString* retrievedString = obj.getString();

    ASSERT_NE(retrievedString, nullptr);

    EXPECT_EQ(retrievedString->c_str(), "test");

}



TEST_F(ObjectTest_2747, StringMoveRetrieval_2747) {

    std::string testString = "test";

    Object obj(std::move(testString));

    std::unique_ptr<GooString> movedString = obj.takeString();

    ASSERT_NE(movedString.get(), nullptr);

    EXPECT_EQ(movedString->c_str(), "test");

    EXPECT_FALSE(obj.isString());

}



TEST_F(ObjectTest_2747, ObjectTypeInitialization_2747) {

    Object boolObj(true);

    Object intObj(10);

    Object realObj(3.14);

    Object int64Obj(static_cast<long long>(1234567890));

    EXPECT_EQ(boolObj.getType(), objBool);

    EXPECT_EQ(intObj.getType(), objInt);

    EXPECT_EQ(realObj.getType(), objReal);

    EXPECT_EQ(int64Obj.getType(), objInt64);

}



TEST_F(ObjectTest_2747, StaticObjectCreation_2747) {

    Object nullObj = Object::null();

    Object eofObj = Object::eof();

    Object errorObj = Object::error();

    EXPECT_EQ(nullObj.getType(), objNull);

    EXPECT_EQ(eofObj.getType(), objEOF);

    EXPECT_EQ(errorObj.getType(), objError);

}
