#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/impl.h"



using namespace YAML::detail;



class NodeTest_667 : public ::testing::Test {

protected:

    shared_memory_holder pMemory;

    node testNode;



    void SetUp() override {

        // Initialize any necessary setup for the tests

    }

};



TEST_F(NodeTest_667, EqualsWithMatchingValues_667) {

    int value = 42;

    testNode.set_scalar(std::to_string(value));

    EXPECT_TRUE(testNode.equals(value, pMemory));

}



TEST_F(NodeTest_667, EqualsWithNonMatchingValues_667) {

    int value = 42;

    testNode.set_scalar("100");

    EXPECT_FALSE(testNode.equals(value, pMemory));

}



TEST_F(NodeTest_667, EqualsWithStringLiteral_667) {

    const char* expected = "Hello";

    testNode.set_scalar(expected);

    EXPECT_TRUE(testNode.equals(expected, pMemory));

}



TEST_F(NodeTest_667, EqualsWithDifferentStringLiteral_667) {

    const char* expected = "World";

    testNode.set_scalar("Hello");

    EXPECT_FALSE(testNode.equals(expected, pMemory));

}



TEST_F(NodeTest_667, EqualsWithEmptyString_667) {

    testNode.set_scalar("");

    EXPECT_TRUE(testNode.equals("", pMemory));

}



TEST_F(NodeTest_667, EqualsWithNullNode_667) {

    testNode.set_null();

    EXPECT_FALSE(testNode.equals(0, pMemory)); // Assuming null node cannot equal an integer 0

}



TEST_F(NodeTest_667, EqualsWithInvalidConversion_667) {

    testNode.set_scalar("not_a_number");

    EXPECT_FALSE(testNode.equals(42, pMemory));

}
