#include "gtest/gtest.h"
#include "catch2/internal/catch_clara.hpp"

// We need to test BoundManyLambda's isContainer() method.
// Based on the interface, BoundManyLambda inherits from BoundLambda<L>
// and overrides isContainer() to return true.

namespace {

// A simple lambda type for testing
auto dummyLambda = [](const std::string&) { return Catch::Clara::Detail::ParserResult::ok(Catch::Clara::Detail::ParseResultType::Matched); };

using DummyLambdaType = decltype(dummyLambda);

} // anonymous namespace

class BoundManyLambdaTest_383 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that isContainer returns true for BoundManyLambda
TEST_F(BoundManyLambdaTest_383, IsContainerReturnsTrue_383) {
    Catch::Clara::Detail::BoundManyLambda<DummyLambdaType> boundMany(dummyLambda);
    EXPECT_TRUE(boundMany.isContainer());
}

// Test that BoundManyLambda's isContainer consistently returns true on multiple calls
TEST_F(BoundManyLambdaTest_383, IsContainerConsistentlyReturnsTrue_383) {
    Catch::Clara::Detail::BoundManyLambda<DummyLambdaType> boundMany(dummyLambda);
    EXPECT_TRUE(boundMany.isContainer());
    EXPECT_TRUE(boundMany.isContainer());
    EXPECT_TRUE(boundMany.isContainer());
}

// Test that BoundManyLambda differs from BoundLambda in isContainer behavior
// BoundLambda should return false for isContainer (it's not a container),
// while BoundManyLambda should return true
TEST_F(BoundManyLambdaTest_383, IsContainerDiffersFromBoundLambda_383) {
    Catch::Clara::Detail::BoundLambda<DummyLambdaType> boundSingle(dummyLambda);
    Catch::Clara::Detail::BoundManyLambda<DummyLambdaType> boundMany(dummyLambda);
    
    EXPECT_FALSE(boundSingle.isContainer());
    EXPECT_TRUE(boundMany.isContainer());
}

// Test polymorphic behavior through base class pointer
TEST_F(BoundManyLambdaTest_383, IsContainerThroughBasePointer_383) {
    auto boundMany = std::make_unique<Catch::Clara::Detail::BoundManyLambda<DummyLambdaType>>(dummyLambda);
    // Access through a pointer to the base type to verify virtual dispatch
    Catch::Clara::Detail::BoundLambda<DummyLambdaType>* basePtr = boundMany.get();
    EXPECT_TRUE(basePtr->isContainer());
}

// Test with a different lambda type to ensure template works with various callables
TEST_F(BoundManyLambdaTest_383, IsContainerWithDifferentLambdaType_383) {
    auto intLambda = [](const std::string&) { return Catch::Clara::Detail::ParserResult::ok(Catch::Clara::Detail::ParseResultType::Matched); };
    Catch::Clara::Detail::BoundManyLambda<decltype(intLambda)> boundMany(intLambda);
    EXPECT_TRUE(boundMany.isContainer());
}
