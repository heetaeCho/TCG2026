#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_stdstreams.cpp"

#include <sstream>



using namespace Catch;



class CatchStdStreamsTest : public ::testing::Test {

protected:

    std::stringstream ss;

};



TEST_F(CatchStdStreamsTest_548, CerrReturnsStandardCerr_548) {

    EXPECT_EQ(&cerr(), &std::cerr);

}



// No other observable behavior or interactions are present in the provided code,

// so we do not need additional test cases.
