#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_stdstreams.hpp"



class CatchStdStreamsTest : public ::testing::Test {

protected:

    // No additional setup required for these tests

};



TEST_F(CatchStdStreamsTest_547, CoutReturnsStandardOutput_547) {

    std::ostream& result = Catch::cout();

    EXPECT_EQ(&result, &std::cout);

}
