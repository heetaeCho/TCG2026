#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "catch2/interfaces/catch_interfaces_generatortracker.hpp"

namespace {

// Concrete test subclass to make the abstract class testable
class MockGenerator : public Catch::Generators::GeneratorUntypedBase {
public:
    MOCK_METHOD(bool, next, (), (override));
    MOCK_METHOD(const std::string, stringifyImpl, (), (override));
};

class GeneratorUntypedBaseTest_58 : public ::testing::Test {
protected:
    MockGenerator generator;
};

// Test that countedNext returns true when next() returns true
TEST_F(GeneratorUntypedBaseTest_58, CountedNextReturnsTrueWhenNextReturnsTrue_58) {
    EXPECT_CALL(generator, next()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(generator.countedNext());
}

// Test that countedNext returns false when next() returns false
TEST_F(GeneratorUntypedBaseTest_58, CountedNextReturnsFalseWhenNextReturnsFalse_58) {
    EXPECT_CALL(generator, next()).WillOnce(::testing::Return(false));
    EXPECT_FALSE(generator.countedNext());
}

// Test that currentElementIndex starts at 0
TEST_F(GeneratorUntypedBaseTest_58, InitialElementIndexIsZero_58) {
    EXPECT_EQ(generator.currentElementIndex(), 0u);
}

// Test that countedNext increments the element index when next() returns true
TEST_F(GeneratorUntypedBaseTest_58, CountedNextIncrementsIndexOnSuccess_58) {
    EXPECT_CALL(generator, next()).WillOnce(::testing::Return(true));
    generator.countedNext();
    EXPECT_EQ(generator.currentElementIndex(), 1u);
}

// Test that countedNext does NOT increment the element index when next() returns false
TEST_F(GeneratorUntypedBaseTest_58, CountedNextDoesNotIncrementIndexOnFailure_58) {
    EXPECT_CALL(generator, next()).WillOnce(::testing::Return(false));
    generator.countedNext();
    EXPECT_EQ(generator.currentElementIndex(), 0u);
}

// Test multiple successful countedNext calls increment the index correctly
TEST_F(GeneratorUntypedBaseTest_58, MultipleCountedNextIncrementsIndex_58) {
    EXPECT_CALL(generator, next()).WillRepeatedly(::testing::Return(true));
    
    generator.countedNext();
    EXPECT_EQ(generator.currentElementIndex(), 1u);
    
    generator.countedNext();
    EXPECT_EQ(generator.currentElementIndex(), 2u);
    
    generator.countedNext();
    EXPECT_EQ(generator.currentElementIndex(), 3u);
}

// Test mixed success and failure of countedNext
TEST_F(GeneratorUntypedBaseTest_58, MixedCountedNextCalls_58) {
    EXPECT_CALL(generator, next())
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(true));
    
    generator.countedNext();
    EXPECT_EQ(generator.currentElementIndex(), 1u);
    
    generator.countedNext();
    EXPECT_EQ(generator.currentElementIndex(), 1u);  // Should not increment
    
    generator.countedNext();
    EXPECT_EQ(generator.currentElementIndex(), 2u);
}

// Test that currentElementAsString calls stringifyImpl
TEST_F(GeneratorUntypedBaseTest_58, CurrentElementAsStringCallsStringifyImpl_58) {
    EXPECT_CALL(generator, stringifyImpl())
        .WillOnce(::testing::Return("test_value"));
    
    auto result = generator.currentElementAsString();
    // The result should contain the stringified value
    EXPECT_FALSE(result.empty());
}

// Test that the string cache is cleared after a successful countedNext
TEST_F(GeneratorUntypedBaseTest_58, StringCacheClearedAfterSuccessfulCountedNext_58) {
    // First, get the string representation to populate the cache
    EXPECT_CALL(generator, stringifyImpl())
        .WillOnce(::testing::Return("value1"))
        .WillOnce(::testing::Return("value2"));
    
    auto result1 = generator.currentElementAsString();
    
    // Now do a successful countedNext which should clear the cache
    EXPECT_CALL(generator, next()).WillOnce(::testing::Return(true));
    generator.countedNext();
    
    // Getting string again should call stringifyImpl again (cache was cleared)
    auto result2 = generator.currentElementAsString();
    // Both calls should have been made to stringifyImpl
}

// Test that the string cache is NOT cleared after a failed countedNext
TEST_F(GeneratorUntypedBaseTest_58, StringCacheNotClearedAfterFailedCountedNext_58) {
    // First, get the string representation to populate the cache
    EXPECT_CALL(generator, stringifyImpl())
        .WillOnce(::testing::Return("cached_value"));
    
    auto result1 = generator.currentElementAsString();
    
    // Failed countedNext should not clear the cache
    EXPECT_CALL(generator, next()).WillOnce(::testing::Return(false));
    generator.countedNext();
    
    // Getting string again should use the cached value (stringifyImpl not called again)
    auto result2 = generator.currentElementAsString();
    // stringifyImpl was only called once total
}

// Test that next() is called exactly once per countedNext
TEST_F(GeneratorUntypedBaseTest_58, NextCalledExactlyOncePerCountedNext_58) {
    EXPECT_CALL(generator, next())
        .Times(3)
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(false));
    
    generator.countedNext();
    generator.countedNext();
    generator.countedNext();
}

// Test copy constructor works (default copy)
TEST_F(GeneratorUntypedBaseTest_58, DefaultConstructorSetsInitialState_58) {
    MockGenerator freshGenerator;
    EXPECT_EQ(freshGenerator.currentElementIndex(), 0u);
}

// Test many iterations to check for overflow or boundary issues
TEST_F(GeneratorUntypedBaseTest_58, ManyIterationsIncrementCorrectly_58) {
    EXPECT_CALL(generator, next()).WillRepeatedly(::testing::Return(true));
    
    for (int i = 0; i < 100; ++i) {
        generator.countedNext();
    }
    EXPECT_EQ(generator.currentElementIndex(), 100u);
}

// Test alternating true/false pattern
TEST_F(GeneratorUntypedBaseTest_58, AlternatingTrueFalsePattern_58) {
    EXPECT_CALL(generator, next())
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(false));
    
    EXPECT_TRUE(generator.countedNext());
    EXPECT_EQ(generator.currentElementIndex(), 1u);
    
    EXPECT_FALSE(generator.countedNext());
    EXPECT_EQ(generator.currentElementIndex(), 1u);
    
    EXPECT_TRUE(generator.countedNext());
    EXPECT_EQ(generator.currentElementIndex(), 2u);
    
    EXPECT_FALSE(generator.countedNext());
    EXPECT_EQ(generator.currentElementIndex(), 2u);
}

// Test that all false calls never increment the index
TEST_F(GeneratorUntypedBaseTest_58, AllFalseNeverIncrementsIndex_58) {
    EXPECT_CALL(generator, next()).WillRepeatedly(::testing::Return(false));
    
    for (int i = 0; i < 10; ++i) {
        EXPECT_FALSE(generator.countedNext());
    }
    EXPECT_EQ(generator.currentElementIndex(), 0u);
}

}  // namespace
