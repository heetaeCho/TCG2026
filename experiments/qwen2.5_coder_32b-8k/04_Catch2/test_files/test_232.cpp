#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "catch2/matchers/catch_matchers_container_properties.hpp"



using namespace Catch::Matchers;



// Mock class to simulate a container-like object

class MockContainer {

public:

    MOCK_METHOD(std::size_t, size, (), (const));

};



TEST(HasSizeMatcher_Test_232, Match_ReturnsTrueForEqualSizes_232) {

    MockContainer mock_container;

    EXPECT_CALL(mock_container, size()).WillOnce(::testing::Return(5));



    HasSizeMatcher matcher(5);

    EXPECT_TRUE(matcher.match(mock_container));

}



TEST(HasSizeMatcher_Test_232, Match_ReturnsFalseForDifferentSizes_232) {

    MockContainer mock_container;

    EXPECT_CALL(mock_container, size()).WillOnce(::testing::Return(3));



    HasSizeMatcher matcher(5);

    EXPECT_FALSE(matcher.match(mock_container));

}



TEST(HasSizeMatcher_Test_232, Describe_ReturnsCorrectDescription_232) {

    HasSizeMatcher matcher(10);

    EXPECT_EQ("has size 10", matcher.describe());

}



TEST(HasSizeMatcher_Test_232, Match_BoundaryCondition_ZeroSize_232) {

    MockContainer mock_container;

    EXPECT_CALL(mock_container, size()).WillOnce(::testing::Return(0));



    HasSizeMatcher matcher(0);

    EXPECT_TRUE(matcher.match(mock_container));

}



TEST(HasSizeMatcher_Test_232, Match_ExceptionalCase_LargeSize_232) {

    MockContainer mock_container;

    std::size_t large_size = std::numeric_limits<std::size_t>::max();

    EXPECT_CALL(mock_container, size()).WillOnce(::testing::Return(large_size));



    HasSizeMatcher matcher(large_size);

    EXPECT_TRUE(matcher.match(mock_container));

}
