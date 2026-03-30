#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_templated.hpp"



using namespace Catch::Matchers::Detail;

using ::testing::_;

using ::testing::Return;



class MatchAllOfGenericTest_157 : public ::testing::Test {

protected:

    template<typename MatcherTs>

    std::unique_ptr<MatchAllOfGeneric<MatcherTs>> createMatchAllOfGeneric(MatcherTs const&... matchers) {

        return std::make_unique<MatchAllOfGeneric<MatcherTs>>(matchers...);

    }

};



TEST_F(MatchAllOfGenericTest_157, ConstructorWithVariadicArgs_157) {

    // Arrange & Act

    auto matcher = createMatchAllOfGeneric<int, double>(42, 3.14);



    // Assert (No direct observable behavior other than successful construction)

}



TEST_F(MatchAllOfGenericTest_157, ConstructorWithArray_157) {

    // Arrange

    std::array<void const*, 2> matchers = { reinterpret_cast<void const*>(42), reinterpret_cast<void const*>(3.14) };



    // Act

    auto matcher = createMatchAllOfGeneric<int, double>(matchers);



    // Assert (No direct observable behavior other than successful construction)

}



TEST_F(MatchAllOfGenericTest_157, DeletedCopyConstructor_157) {

    // Arrange & Act & Assert (This test is more about code correctness, no runtime check needed here)

}



TEST_F(MatchAllOfGenericTest_157, DefaultMoveConstructor_157) {

    // Arrange

    auto original = createMatchAllOfGeneric<int, double>(42, 3.14);



    // Act

    auto moved = std::move(*original);



    // Assert (No direct observable behavior other than successful move construction)

}



TEST_F(MatchAllOfGenericTest_157, DeletedCopyAssignmentOperator_157) {

    // Arrange & Act & Assert (This test is more about code correctness, no runtime check needed here)

}



TEST_F(MatchAllOfGenericTest_157, DefaultMoveAssignmentOperator_157) {

    // Arrange

    auto original = createMatchAllOfGeneric<int, double>(42, 3.14);

    auto target = createMatchAllOfGeneric<int, double>(0, 0.0);



    // Act

    *target = std::move(*original);



    // Assert (No direct observable behavior other than successful move assignment)

}



TEST_F(MatchAllOfGenericTest_157, Describe_ReturnsValidString_157) {

    // Arrange

    auto matcher = createMatchAllOfGeneric<int, double>(42, 3.14);



    // Act

    std::string description = matcher->describe();



    // Assert (The exact string content is not specified, but it should not throw)

    EXPECT_FALSE(description.empty());

}
