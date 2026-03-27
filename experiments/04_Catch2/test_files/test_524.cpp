#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_getenv.cpp"



using namespace Catch::Detail;



class GetEnvTest_524 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be used to set environment variables if needed

    }



    void TearDown() override {

        // Teardown can be used to clean up environment variables if needed

    }

};



TEST_F(GetEnvTest_524, ValidEnvironmentVariable_524) {

    // Assuming there is an environment variable named "PATH" which is usually set in most systems

    char const* result = getEnv("PATH");

    EXPECT_NE(result, nullptr);

}



TEST_F(GetEnvTest_524, NonexistentEnvironmentVariable_524) {

    char const* result = getEnv("NONEXISTENT_VARIABLE_524");

    EXPECT_EQ(result, nullptr);

}



TEST_F(GetEnvTest_524, EmptyStringAsVariableName_524) {

    char const* result = getEnv("");

    EXPECT_EQ(result, nullptr);

}



TEST_F(GetEnvTest_524, NullptrAsVariableName_524) {

    char const* result = getEnv(nullptr);

    EXPECT_EQ(result, nullptr);

}

```


