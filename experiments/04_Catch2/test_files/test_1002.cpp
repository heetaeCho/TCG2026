#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/catch_test_spec.hpp"



using namespace Catch;



class TestSpecPatternTest_1002 : public ::testing::Test {

protected:

    TestSpec::Pattern pattern;

    

    TestSpecPatternTest_1002() : pattern("test_pattern") {}

};



TEST_F(TestSpecPatternTest_1002, NameReturnsCorrectValue_1002) {

    EXPECT_EQ(pattern.name(), "test_pattern");

}



// Assuming matches function can be tested with a mock or by providing known test cases

// Since we do not have the implementation of TestCaseInfo, we cannot directly invoke matches.

// However, if there are predefined patterns and test cases, we could simulate that.



// Mocking external collaborators (if any) is not applicable here as we don't have dependencies.

// No exceptional or error cases observable through the interface based on provided information.



// Boundary conditions would be more relevant if there were constraints on input size or type,

// which are not present in this simple getter function.



// Since the class does not interact with external systems, verification of external interactions is not applicable here.
