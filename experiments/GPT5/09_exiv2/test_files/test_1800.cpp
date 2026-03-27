#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include <cstdlib>
#include <string>

// Mocking the standard getenv functionality for testing purposes
class EnvMock {
public:
    MOCK_METHOD(const char*, getenv, (const char* name), ());
};

// The function to be tested (as provided)
namespace Exiv2 {
    std::string getEnv(int env_var) {
        if (env_var < envHTTPPOST || env_var > envTIMEOUT) 
            throw std::out_of_range("Unexpected env variable");

        #ifdef _WIN32
            char* buf = nullptr;
            size_t len;
            if (_dupenv_s(&buf, &len, ENVARKEY[env_var]) == 0 && buf) {
                auto ret = std::string(buf);
                free(buf);
                return ret;
            }
        #else
            if (auto val = std::getenv(ENVARKEY[env_var]))
                return val;
        #endif
        return ENVARDEF[env_var];
    }
}

// Test case class
class FutilsTest : public ::testing::Test {
protected:
    EnvMock env_mock;

    void SetUp() override {
        // Setup any common mock expectations or initialization if needed
    }

    void TearDown() override {
        // Cleanup if needed
    }
};

// TEST_ID: 1800
TEST_F(FutilsTest, GetEnv_ValidEnvHTTPPOST_1800) {
    // Normal operation for envHTTPPOST
    EXPECT_CALL(env_mock, getenv("EXIV2_HTTP_POST"))
        .WillOnce(testing::Return("/exiv2.php"));

    EXPECT_EQ(Exiv2::getEnv(Exiv2::envHTTPPOST), "/exiv2.php");
}

// TEST_ID: 1801
TEST_F(FutilsTest, GetEnv_ValidEnvTimeout_1801) {
    // Normal operation for envTIMEOUT
    EXPECT_CALL(env_mock, getenv("EXIV2_TIMEOUT"))
        .WillOnce(testing::Return("40"));

    EXPECT_EQ(Exiv2::getEnv(Exiv2::envTIMEOUT), "40");
}

// TEST_ID: 1802
TEST_F(FutilsTest, GetEnv_OutOfRange_1802) {
    // Boundary test for out-of-range env variable
    EXPECT_THROW(Exiv2::getEnv(2), std::out_of_range);
}

// TEST_ID: 1803
TEST_F(FutilsTest, GetEnv_NoEnvVarSet_1803) {
    // Test case for when the environment variable is not set
    EXPECT_CALL(env_mock, getenv("EXIV2_HTTP_POST"))
        .WillOnce(testing::Return(nullptr));

    EXPECT_EQ(Exiv2::getEnv(Exiv2::envHTTPPOST), "/exiv2.php"); // Defaults to "/exiv2.php"
}

// TEST_ID: 1804
TEST_F(FutilsTest, GetEnv_InvalidEnvVar_1804) {
    // Test case for invalid env_var value
    EXPECT_THROW(Exiv2::getEnv(-1), std::out_of_range);
}

// TEST_ID: 1805
TEST_F(FutilsTest, GetEnv_DefaultForMissingEnvVar_1805) {
    // Test for default behavior when environment variable is missing
    EXPECT_CALL(env_mock, getenv("EXIV2_TIMEOUT"))
        .WillOnce(testing::Return(nullptr));

    EXPECT_EQ(Exiv2::getEnv(Exiv2::envTIMEOUT), "40"); // Defaults to "40"
}