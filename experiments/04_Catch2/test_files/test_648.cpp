#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_reusable_string_stream.hpp"

#include "catch2/internal/catch_singletons.hpp"



using namespace Catch;



class ReusableStringStreamTest : public ::testing::Test {

protected:

    void SetUp() override {

        // No setup needed as we treat the class as a black box

    }



    void TearDown() override {

        // No teardown needed as we treat the class as a black box

    }

};



TEST_F(ReusableStringStreamTest_648, DefaultConstructorInitializesEmptyString_648) {

    ReusableStringStream rss;

    EXPECT_EQ(rss.str(), "");

}



TEST_F(ReusableStringStreamTest_648, StrSetsAndGetsStringCorrectly_648) {

    ReusableStringStream rss;

    rss.str("Hello, World!");

    EXPECT_EQ(rss.str(), "Hello, World!");

}



TEST_F(ReusableStringStreamTest_648, OperatorLeftShiftAddsToString_648) {

    ReusableStringStream rss;

    rss << "Hello" << ", " << "World!";

    EXPECT_EQ(rss.str(), "Hello, World!");

}



TEST_F(ReusableStringStreamTest_648, GetReturnsOstreamReference_648) {

    ReusableStringStream rss;

    std::ostream& os = rss.get();

    os << "Test";

    EXPECT_EQ(rss.str(), "Test");

}



TEST_F(ReusableStringStreamTest_648, StrWithEmptyStringResetsContent_648) {

    ReusableStringStream rss;

    rss << "Initial content";

    rss.str("");

    EXPECT_EQ(rss.str(), "");

}
