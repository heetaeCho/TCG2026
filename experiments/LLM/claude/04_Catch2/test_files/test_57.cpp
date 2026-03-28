#include <gtest/gtest.h>
#include "catch2/interfaces/catch_interfaces_generatortracker.hpp"

// Since GeneratorUntypedBase has pure virtual methods, we need a concrete subclass for testing
class ConcreteGenerator : public Catch::Generators::GeneratorUntypedBase {
public:
    ConcreteGenerator() : Catch::Generators::GeneratorUntypedBase() {}
    
    // Track how many times next() is called
    int nextCallCount = 0;
    bool nextReturnValue = true;
    std::string stringifyValue = "test_value";

private:
    bool next() override {
        nextCallCount++;
        return nextReturnValue;
    }
    
    std::string stringifyImpl() const override {
        return stringifyValue;
    }
};

class GeneratorUntypedBaseTest_57 : public ::testing::Test {
protected:
    ConcreteGenerator generator;
};

// Test that initial element index is 0
TEST_F(GeneratorUntypedBaseTest_57, InitialElementIndexIsZero_57) {
    EXPECT_EQ(generator.currentElementIndex(), 0u);
}

// Test that countedNext increments the element index
TEST_F(GeneratorUntypedBaseTest_57, CountedNextIncrementsElementIndex_57) {
    generator.nextReturnValue = true;
    bool result = generator.countedNext();
    EXPECT_TRUE(result);
    EXPECT_EQ(generator.currentElementIndex(), 1u);
}

// Test that multiple countedNext calls increment the index correctly
TEST_F(GeneratorUntypedBaseTest_57, MultipleCountedNextIncrementsIndex_57) {
    generator.nextReturnValue = true;
    generator.countedNext();
    generator.countedNext();
    generator.countedNext();
    EXPECT_EQ(generator.currentElementIndex(), 3u);
}

// Test that countedNext returns false when next() returns false
TEST_F(GeneratorUntypedBaseTest_57, CountedNextReturnsFalseWhenExhausted_57) {
    generator.nextReturnValue = false;
    bool result = generator.countedNext();
    EXPECT_FALSE(result);
}

// Test that countedNext still increments index even when next returns false
TEST_F(GeneratorUntypedBaseTest_57, CountedNextIncrementsIndexEvenWhenFalse_57) {
    generator.nextReturnValue = false;
    generator.countedNext();
    // The index should have been incremented regardless of next()'s return value
    EXPECT_EQ(generator.currentElementIndex(), 1u);
}

// Test that currentElementAsString returns a non-empty value
TEST_F(GeneratorUntypedBaseTest_57, CurrentElementAsStringReturnsValue_57) {
    generator.stringifyValue = "hello_world";
    auto result = generator.currentElementAsString();
    // The result should contain the stringified value
    EXPECT_FALSE(result.empty());
}

// Test copy construction preserves element index
TEST_F(GeneratorUntypedBaseTest_57, CopyConstructionPreservesIndex_57) {
    generator.nextReturnValue = true;
    generator.countedNext();
    generator.countedNext();
    
    ConcreteGenerator copied(generator);
    EXPECT_EQ(copied.currentElementIndex(), generator.currentElementIndex());
}

// Test that default constructed generator has index 0
TEST_F(GeneratorUntypedBaseTest_57, DefaultConstructedHasZeroIndex_57) {
    ConcreteGenerator fresh;
    EXPECT_EQ(fresh.currentElementIndex(), 0u);
}

// Test copy assignment preserves element index
TEST_F(GeneratorUntypedBaseTest_57, CopyAssignmentPreservesIndex_57) {
    generator.nextReturnValue = true;
    generator.countedNext();
    generator.countedNext();
    generator.countedNext();
    
    ConcreteGenerator other;
    other = generator;
    EXPECT_EQ(other.currentElementIndex(), 3u);
}

// Test sequential countedNext with alternating return values
TEST_F(GeneratorUntypedBaseTest_57, SequentialCountedNextAlternating_57) {
    generator.nextReturnValue = true;
    EXPECT_TRUE(generator.countedNext());
    EXPECT_EQ(generator.currentElementIndex(), 1u);
    
    generator.nextReturnValue = true;
    EXPECT_TRUE(generator.countedNext());
    EXPECT_EQ(generator.currentElementIndex(), 2u);
    
    generator.nextReturnValue = false;
    EXPECT_FALSE(generator.countedNext());
    EXPECT_EQ(generator.currentElementIndex(), 3u);
}

// Test destruction does not crash (virtual destructor)
TEST_F(GeneratorUntypedBaseTest_57, DestructionDoesNotCrash_57) {
    auto* gen = new ConcreteGenerator();
    gen->nextReturnValue = true;
    gen->countedNext();
    Catch::Generators::GeneratorUntypedBase* basePtr = gen;
    EXPECT_NO_THROW(delete basePtr);
}

// Test currentElementAsString caching behavior - calling it multiple times
TEST_F(GeneratorUntypedBaseTest_57, CurrentElementAsStringMultipleCalls_57) {
    generator.stringifyValue = "cached_value";
    auto result1 = generator.currentElementAsString();
    auto result2 = generator.currentElementAsString();
    // Both calls should return the same value
    EXPECT_EQ(std::string(result1.data(), result1.size()), 
              std::string(result2.data(), result2.size()));
}
