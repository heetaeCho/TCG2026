#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_stdstreams.hpp"



class CatchStdStreamsTest_549 : public ::testing::Test {

protected:

    // No additional setup or teardown required for this simple interface

};



TEST_F(CatchStdStreamsTest_549, ClogReturnsClogStream_549) {

    std::ostream& result = Catch::clog();

    EXPECT_EQ(&result, &std::clog);

}



// Since the function is just a wrapper around std::clog, there are no boundary conditions,

// exceptional cases, or external interactions to test.
