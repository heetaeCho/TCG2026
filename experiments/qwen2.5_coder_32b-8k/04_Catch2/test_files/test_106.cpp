#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_message.hpp"



using namespace Catch;



TEST(MessageStreamTest_106, InsertionOperatorIncreasesLength_106) {

    MessageStream stream;

    size_t initial_length = stream.m_stream.str().length();

    stream << "test";

    size_t final_length = stream.m_stream.str().length();

    EXPECT_GT(final_length, initial_length);

}



TEST(MessageStreamTest_106, InsertionOperatorHandlesMultipleInsertions_106) {

    MessageStream stream;

    stream << "Hello" << " " << "World";

    EXPECT_EQ(stream.m_stream.str(), "Hello World");

}



TEST(MessageStreamTest_106, InsertionOperatorHandlesIntegers_106) {

    MessageStream stream;

    int number = 42;

    stream << number;

    EXPECT_EQ(stream.m_stream.str(), "42");

}



TEST(MessageStreamTest_106, InsertionOperatorHandlesFloatingPointNumbers_106) {

    MessageStream stream;

    double pi = 3.14159;

    stream << pi;

    EXPECT_EQ(stream.m_stream.str(), "3.14159");

}



TEST(MessageStreamTest_106, InsertionOperatorHandlesBooleans_106) {

    MessageStream stream;

    bool flag = true;

    stream << flag;

    EXPECT_EQ(stream.m_stream.str(), "1");



    stream.m_stream.clear();

    stream.m_stream.str("");

    flag = false;

    stream << flag;

    EXPECT_EQ(stream.m_stream.str(), "0");

}



TEST(MessageStreamTest_106, InsertionOperatorHandlesEmptyString_106) {

    MessageStream stream;

    stream << "";

    EXPECT_EQ(stream.m_stream.str(), "");

}
