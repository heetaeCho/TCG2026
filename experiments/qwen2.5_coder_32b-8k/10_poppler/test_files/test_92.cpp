#include <gtest/gtest.h>

#include "Object.h"



class ObjectTest_92 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(ObjectTest_92, IntInitializationAndRetrieval_92) {

    Object obj(42);

    EXPECT_TRUE(obj.isInt());

    EXPECT_EQ(obj.getInt(), 42);

}



TEST_F(ObjectTest_92, Int64InitializationAndRetrieval_92) {

    long long int64Value = 1234567890123;

    Object obj(int64Value);

    EXPECT_TRUE(obj.isInt64());

    EXPECT_EQ(obj.getIntOrInt64(), int64Value);

}



TEST_F(ObjectTest_92, RealInitializationAndRetrieval_92) {

    double realValue = 3.14159;

    Object obj(realValue);

    EXPECT_TRUE(obj.isReal());

    EXPECT_DOUBLE_EQ(obj.getReal(), realValue);

}



TEST_F(ObjectTest_92, StringInitializationAndRetrieval_92) {

    std::string stringValue = "Hello, World!";

    Object obj(stringValue);

    EXPECT_TRUE(obj.isString());

    EXPECT_STREQ(obj.getString()->c_str(), stringValue.c_str());

}



TEST_F(ObjectTest_92, NameInitializationAndRetrieval_92) {

    const char* nameValue = "exampleName";

    Object obj(nameValue);

    EXPECT_TRUE(obj.isName());

    EXPECT_STREQ(obj.getName(), nameValue);

}



TEST_F(ObjectTest_92, NullObjectCreation_92) {

    Object obj = Object::null();

    EXPECT_TRUE(obj.isNull());

}



TEST_F(ObjectTest_92, EOFObjectCreation_92) {

    Object obj = Object::eof();

    EXPECT_TRUE(obj.isEOF());

}



TEST_F(ObjectTest_92, ErrorObjectCreation_92) {

    Object obj = Object::error();

    EXPECT_TRUE(obj.isError());

}



TEST_F(ObjectTest_92, BoolInitializationAndRetrieval_92) {

    bool boolValue = true;

    Object obj(boolValue);

    EXPECT_TRUE(obj.isBool());

    EXPECT_EQ(obj.getBool(), boolValue);

}



TEST_F(ObjectTest_92, BoundaryCondition_Int64Min_92) {

    long long int64MinValue = std::numeric_limits<long long>::min();

    Object obj(int64MinValue);

    EXPECT_TRUE(obj.isInt64());

    EXPECT_EQ(obj.getIntOrInt64(), int64MinValue);

}



TEST_F(ObjectTest_92, BoundaryCondition_Int64Max_92) {

    long long int64MaxValue = std::numeric_limits<long long>::max();

    Object obj(int64MaxValue);

    EXPECT_TRUE(obj.isInt64());

    EXPECT_EQ(obj.getIntOrInt64(), int64MaxValue);

}



TEST_F(ObjectTest_92, BoundaryCondition_RealMin_92) {

    double realMinValue = std::numeric_limits<double>::lowest();

    Object obj(realMinValue);

    EXPECT_TRUE(obj.isReal());

    EXPECT_DOUBLE_EQ(obj.getReal(), realMinValue);

}



TEST_F(ObjectTest_92, BoundaryCondition_RealMax_92) {

    double realMaxValue = std::numeric_limits<double>::max();

    Object obj(realMaxValue);

    EXPECT_TRUE(obj.isReal());

    EXPECT_DOUBLE_EQ(obj.getReal(), realMaxValue);

}
