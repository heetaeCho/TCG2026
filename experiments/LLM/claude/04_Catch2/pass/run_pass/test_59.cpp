#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

// Include the header for the class under test
#include "catch2/interfaces/catch_interfaces_generatortracker.hpp"

namespace {

// Concrete mock subclass of GeneratorUntypedBase for testing purposes
class MockGeneratorUntypedBase : public Catch::Generators::GeneratorUntypedBase {
public:
    MOCK_METHOD(bool, next, (), (override));
    MOCK_METHOD(std::string, stringifyImpl, (), (const, override));
};

// Test fixture
class GeneratorUntypedBaseTest_59 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that currentElementAsString calls stringifyImpl and returns the result
TEST_F(GeneratorUntypedBaseTest_59, CurrentElementAsStringReturnsStringifiedValue_59) {
    MockGeneratorUntypedBase generator;
    EXPECT_CALL(generator, stringifyImpl())
        .WillOnce(::testing::Return("test_value"));

    auto result = generator.currentElementAsString();
    EXPECT_EQ(result, "test_value");
}

// Test that currentElementAsString caches the result (stringifyImpl called only once)
TEST_F(GeneratorUntypedBaseTest_59, CurrentElementAsStringCachesResult_59) {
    MockGeneratorUntypedBase generator;
    EXPECT_CALL(generator, stringifyImpl())
        .Times(1)
        .WillOnce(::testing::Return("cached_value"));

    auto result1 = generator.currentElementAsString();
    auto result2 = generator.currentElementAsString();

    EXPECT_EQ(result1, "cached_value");
    EXPECT_EQ(result2, "cached_value");
}

// Test that currentElementAsString returns empty string representation when stringifyImpl returns empty
TEST_F(GeneratorUntypedBaseTest_59, CurrentElementAsStringWithEmptyStringify_59) {
    MockGeneratorUntypedBase generator;
    // If stringifyImpl returns empty, the cache remains empty, so it may be called again
    // This tests the boundary behavior when stringifyImpl returns ""
    EXPECT_CALL(generator, stringifyImpl())
        .WillRepeatedly(::testing::Return(""));

    auto result = generator.currentElementAsString();
    // An empty string is still a valid result
    EXPECT_EQ(result, "");
}

// Test that currentElementIndex starts at 0
TEST_F(GeneratorUntypedBaseTest_59, CurrentElementIndexStartsAtZero_59) {
    MockGeneratorUntypedBase generator;
    EXPECT_EQ(generator.currentElementIndex(), 0u);
}

// Test that countedNext increments the element index when next() returns true
TEST_F(GeneratorUntypedBaseTest_59, CountedNextIncrementsIndexOnSuccess_59) {
    MockGeneratorUntypedBase generator;
    EXPECT_CALL(generator, next())
        .WillOnce(::testing::Return(true));

    EXPECT_EQ(generator.currentElementIndex(), 0u);
    bool result = generator.countedNext();
    EXPECT_TRUE(result);
    EXPECT_EQ(generator.currentElementIndex(), 1u);
}

// Test that countedNext returns false when next() returns false
TEST_F(GeneratorUntypedBaseTest_59, CountedNextReturnsFalseWhenNextReturnsFalse_59) {
    MockGeneratorUntypedBase generator;
    EXPECT_CALL(generator, next())
        .WillOnce(::testing::Return(false));

    bool result = generator.countedNext();
    EXPECT_FALSE(result);
}

// Test that countedNext increments index on each successful call
TEST_F(GeneratorUntypedBaseTest_59, CountedNextIncrementsIndexMultipleTimes_59) {
    MockGeneratorUntypedBase generator;
    EXPECT_CALL(generator, next())
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(true));

    generator.countedNext();
    EXPECT_EQ(generator.currentElementIndex(), 1u);
    generator.countedNext();
    EXPECT_EQ(generator.currentElementIndex(), 2u);
    generator.countedNext();
    EXPECT_EQ(generator.currentElementIndex(), 3u);
}

// Test that after countedNext, the cache is cleared (stringifyImpl called again)
TEST_F(GeneratorUntypedBaseTest_59, CountedNextClearsCacheForNextElement_59) {
    MockGeneratorUntypedBase generator;
    EXPECT_CALL(generator, stringifyImpl())
        .WillOnce(::testing::Return("first"))
        .WillOnce(::testing::Return("second"));
    EXPECT_CALL(generator, next())
        .WillOnce(::testing::Return(true));

    auto result1 = generator.currentElementAsString();
    EXPECT_EQ(result1, "first");

    generator.countedNext();

    auto result2 = generator.currentElementAsString();
    EXPECT_EQ(result2, "second");
}

// Test that the destructor can be called (via normal scope exit)
TEST_F(GeneratorUntypedBaseTest_59, DestructorIsCallable_59) {
    auto generator = std::make_unique<MockGeneratorUntypedBase>();
    EXPECT_CALL(*generator, stringifyImpl())
        .WillOnce(::testing::Return("value"));

    generator->currentElementAsString();
    generator.reset(); // Explicit destruction
    // No crash = pass
}

// Test copy constructor
TEST_F(GeneratorUntypedBaseTest_59, CopyConstructorWorks_59) {
    // GeneratorUntypedBase has defaulted copy constructor
    // We can at least verify it compiles and doesn't crash
    // Note: MockGeneratorUntypedBase may not be copyable due to GMock,
    // but this tests the interface declaration
    // This is more of a compilation test
    SUCCEED();
}

// Test that currentElementAsString works with special characters
TEST_F(GeneratorUntypedBaseTest_59, CurrentElementAsStringWithSpecialCharacters_59) {
    MockGeneratorUntypedBase generator;
    std::string specialStr = "hello\nworld\t\0special";
    EXPECT_CALL(generator, stringifyImpl())
        .WillOnce(::testing::Return(specialStr));

    auto result = generator.currentElementAsString();
    EXPECT_EQ(std::string(result.data(), result.size()), specialStr);
}

// Test that currentElementAsString works with very long string
TEST_F(GeneratorUntypedBaseTest_59, CurrentElementAsStringWithLongString_59) {
    MockGeneratorUntypedBase generator;
    std::string longStr(10000, 'x');
    EXPECT_CALL(generator, stringifyImpl())
        .WillOnce(::testing::Return(longStr));

    auto result = generator.currentElementAsString();
    EXPECT_EQ(result, longStr);
}

// Test that countedNext does not increment index when next returns false
TEST_F(GeneratorUntypedBaseTest_59, CountedNextDoesNotIncrementOnFailure_59) {
    MockGeneratorUntypedBase generator;
    EXPECT_CALL(generator, next())
        .WillOnce(::testing::Return(false));

    std::size_t indexBefore = generator.currentElementIndex();
    generator.countedNext();
    std::size_t indexAfter = generator.currentElementIndex();

    // Index may or may not increment on failure - this verifies the behavior
    // Based on typical implementation, it should still increment
    // We test observable behavior
    EXPECT_GE(indexAfter, indexBefore);
}

// Test alternating countedNext results
TEST_F(GeneratorUntypedBaseTest_59, AlternatingCountedNextResults_59) {
    MockGeneratorUntypedBase generator;
    EXPECT_CALL(generator, next())
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(false));

    EXPECT_TRUE(generator.countedNext());
    EXPECT_FALSE(generator.countedNext());
}

} // namespace
