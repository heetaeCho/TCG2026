#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/traits.h"

#include <string>



// Mock class to simulate Key type for testing

class MockKey {

public:

    MOCK_METHOD0(ToString, std::string());

};



// Specialization of streamable_to_string for MockKey

namespace YAML {

template <>

struct streamable_to_string<MockKey, true> {

public:

    static std::string impl(const MockKey& key) {

        return key.ToString();

    }

};

}



class StreamableToStringTest_79 : public ::testing::Test {};



TEST_F(StreamableToStringTest_79, NormalOperation_79) {

    MockKey mockKey;

    EXPECT_CALL(mockKey, ToString()).WillOnce(::testing::Return("expected_value"));



    std::string result = YAML::streamable_to_string<MockKey, true>::impl(mockKey);

    ASSERT_EQ(result, "expected_value");

}



TEST_F(StreamableToStringTest_79, BoundaryConditions_EmptyString_79) {

    MockKey mockKey;

    EXPECT_CALL(mockKey, ToString()).WillOnce(::testing::Return(""));



    std::string result = YAML::streamable_to_string<MockKey, true>::impl(mockKey);

    ASSERT_EQ(result, "");

}



TEST_F(StreamableToStringTest_79, ExceptionalCase_ThrowException_79) {

    MockKey mockKey;

    EXPECT_CALL(mockKey, ToString()).WillOnce(::testing::Throw(std::runtime_error("error")));



    EXPECT_THROW(YAML::streamable_to_string<MockKey, true>::impl(mockKey), std::runtime_error);

}
