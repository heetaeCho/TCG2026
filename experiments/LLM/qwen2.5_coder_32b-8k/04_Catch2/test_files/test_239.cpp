#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_container_properties.hpp"



using namespace Catch::Matchers;



class HasSizeMatcherTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(HasSizeMatcherTest_239, SizeIs_ReturnsCorrectMatcher_239) {

    std::size_t expected_size = 5;

    HasSizeMatcher matcher = SizeIs(expected_size);

    

    EXPECT_EQ(matcher.m_expectedSize, expected_size);

}



TEST_F(HasSizeMatcherTest_239, SizeIs_ZeroSize_239) {

    std::size_t zero_size = 0;

    HasSizeMatcher matcher = SizeIs(zero_size);

    

    EXPECT_EQ(matcher.m_expectedSize, zero_size);

}



TEST_F(HasSizeMatcherTest_239, SizeIs_LargeNumber_239) {

    std::size_t large_number = 1000000;

    HasSizeMatcher matcher = SizeIs(large_number);

    

    EXPECT_EQ(matcher.m_expectedSize, large_number);

}
