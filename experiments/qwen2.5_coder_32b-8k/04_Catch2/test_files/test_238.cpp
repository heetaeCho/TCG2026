#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_container_properties.hpp"



using namespace Catch::Matchers;



TEST(IsEmptyMatcherTest_238, EmptyContainer_ReturnsTrue_238) {

    std::vector<int> emptyVector;

    EXPECT_TRUE(IsEmpty().match(emptyVector));

}



TEST(IsEmptyMatcherTest_238, NonEmptyContainer_ReturnsFalse_238) {

    std::vector<int> nonEmptyVector = {1, 2, 3};

    EXPECT_FALSE(IsEmpty().match(nonEmptyVector));

}



TEST(IsEmptyMatcherTest_238, EmptyString_ReturnsTrue_238) {

    std::string emptyString;

    EXPECT_TRUE(IsEmpty().match(emptyString));

}



TEST(IsEmptyMatcherTest_238, NonEmptyString_ReturnsFalse_238) {

    std::string nonEmptyString = "Hello";

    EXPECT_FALSE(IsEmpty().match(nonEmptyString));

}



TEST(IsEmptyMatcherTest_238, EmptyMap_ReturnsTrue_238) {

    std::map<int, int> emptyMap;

    EXPECT_TRUE(IsEmpty().match(emptyMap));

}



TEST(IsEmptyMatcherTest_238, NonEmptyMap_ReturnsFalse_238) {

    std::map<int, int> nonEmptyMap = {{1, 2}, {3, 4}};

    EXPECT_FALSE(IsEmpty().match(nonEmptyMap));

}
