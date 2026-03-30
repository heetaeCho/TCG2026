#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "stream.h"



namespace YAML {

    class StreamTest_174 : public ::testing::Test {

    protected:

        std::istringstream input;

        Stream stream;



        StreamTest_174() : stream(input) {}

    };



    TEST_F(StreamTest_174, BoolOperator_ReturnsTrueForGoodInputStream_174) {

        input.str("test");

        EXPECT_TRUE(static_cast<bool>(stream));

    }



    TEST_F(StreamTest_174, BoolOperator_ReturnsFalseForEmptyStreamAtEof_174) {

        input.str("");

        input.seekg(0, std::ios::end);

        EXPECT_FALSE(static_cast<bool>(stream));

    }



    TEST_F(StreamTest_174, BoolOperator_ReturnsTrueForNonEmptyReadaheadAfterEof_174) {

        stream.m_readahead.push_back('a');

        input.str("");

        input.seekg(0, std::ios::end);

        EXPECT_TRUE(static_cast<bool>(stream));

    }



    TEST_F(StreamTest_174, BoolOperator_ReturnsFalseForEmptyReadaheadAtEof_174) {

        stream.m_readahead.clear();

        input.str("");

        input.seekg(0, std::ios::end);

        EXPECT_FALSE(static_cast<bool>(stream));

    }



    TEST_F(StreamTest_174, BoolOperator_ReturnsTrueAfterReadingToEndOfStreamWithReadahead_174) {

        input.str("test");

        stream.get(4); // Exhaust the stream

        stream.m_readahead.push_back('a');

        EXPECT_TRUE(static_cast<bool>(stream));

    }



    TEST_F(StreamTest_174, BoolOperator_ReturnsFalseAfterReadingToEndOfStreamWithoutReadahead_174) {

        input.str("test");

        stream.get(4); // Exhaust the stream

        stream.m_readahead.clear();

        EXPECT_FALSE(static_cast<bool>(stream));

    }



}  // namespace YAML
