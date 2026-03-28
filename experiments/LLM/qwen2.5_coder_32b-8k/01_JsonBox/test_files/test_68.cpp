#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "JsonBox/Value.h"

#include "JsonBox/Grammar.h"



using namespace JsonBox;

using namespace std;



class ArrayOutputTest_68 : public ::testing::Test {

protected:

    Array array;

    stringstream output;



    void SetUp() override {

        // Initialize the test environment

    }



    void TearDown() override {

        // Clean up after tests

    }

};



TEST_F(ArrayOutputTest_68, EmptyArrayOutput_68) {

    output << array;

    EXPECT_EQ(output.str(), "[]");

}



TEST_F(ArrayOutputTest_68, SingleElementArrayOutput_68) {

    array.push_back("element1");

    output << array;

    EXPECT_EQ(output.str(), "[\nelement1\n]");

}



TEST_F(ArrayOutputTest_68, MultipleElementsArrayOutput_68) {

    array.push_back("element1");

    array.push_back("element2");

    output << array;

    EXPECT_EQ(output.str(), "[\nelement1,\nelement2\n]");

}



TEST_F(ArrayOutputTest_68, ArrayWithSpecialCharactersOutput_68) {

    array.push_back("\"element1\"");

    array.push_back("\"element2\"");

    output << array;

    EXPECT_EQ(output.str(), "[\n\"element1\",\n\"element2\"\n]");

}
