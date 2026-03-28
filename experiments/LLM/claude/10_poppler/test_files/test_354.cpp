#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"

// A concrete subclass for testing since Function has a virtual method
class ConcreteFunction : public Function {
public:
    ~ConcreteFunction() override = default;
};

// A subclass that overrides hasDifferentResultSet to return true
class DifferentResultFunction : public Function {
public:
    ~DifferentResultFunction() override = default;
    bool hasDifferentResultSet(const Function * /*func*/) const override { return true; }
};

// Test that default implementation returns false
TEST(FunctionTest_354, HasDifferentResultSetReturnsFalseByDefault_354) {
    ConcreteFunction func1;
    ConcreteFunction func2;
    EXPECT_FALSE(func1.hasDifferentResultSet(&func2));
}

// Test with nullptr argument
TEST(FunctionTest_354, HasDifferentResultSetWithNullptr_354) {
    ConcreteFunction func;
    EXPECT_FALSE(func.hasDifferentResultSet(nullptr));
}

// Test with self as argument
TEST(FunctionTest_354, HasDifferentResultSetWithSelf_354) {
    ConcreteFunction func;
    EXPECT_FALSE(func.hasDifferentResultSet(&func));
}

// Test that a derived class can override the behavior
TEST(FunctionTest_354, OverriddenHasDifferentResultSetReturnsTrue_354) {
    DifferentResultFunction func1;
    ConcreteFunction func2;
    EXPECT_TRUE(func1.hasDifferentResultSet(&func2));
}

// Test polymorphic call through base pointer - default implementation
TEST(FunctionTest_354, PolymorphicCallDefaultReturnsFalse_354) {
    ConcreteFunction concreteFunc;
    Function* basePtr = &concreteFunc;
    ConcreteFunction other;
    EXPECT_FALSE(basePtr->hasDifferentResultSet(&other));
}

// Test polymorphic call through base pointer - overridden implementation
TEST(FunctionTest_354, PolymorphicCallOverriddenReturnsTrue_354) {
    DifferentResultFunction diffFunc;
    Function* basePtr = &diffFunc;
    ConcreteFunction other;
    EXPECT_TRUE(basePtr->hasDifferentResultSet(&other));
}

// Test with different derived types as argument
TEST(FunctionTest_354, HasDifferentResultSetWithDifferentDerivedType_354) {
    ConcreteFunction func;
    DifferentResultFunction diffFunc;
    // ConcreteFunction uses default impl which returns false regardless of argument type
    EXPECT_FALSE(func.hasDifferentResultSet(&diffFunc));
}

// Test overridden version with nullptr
TEST(FunctionTest_354, OverriddenHasDifferentResultSetWithNullptr_354) {
    DifferentResultFunction func;
    EXPECT_TRUE(func.hasDifferentResultSet(nullptr));
}

// Test overridden version with self
TEST(FunctionTest_354, OverriddenHasDifferentResultSetWithSelf_354) {
    DifferentResultFunction func;
    EXPECT_TRUE(func.hasDifferentResultSet(&func));
}
