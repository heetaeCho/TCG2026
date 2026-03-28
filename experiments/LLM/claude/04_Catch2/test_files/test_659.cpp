#include <gtest/gtest.h>

// Include the header for the class under test
#include "catch2/internal/catch_clara.hpp"

namespace {

// Since BoundRef has pure virtual methods and is NonCopyable, we need a concrete
// derived class to instantiate it for testing
class ConcreteBoundRef : public Catch::Clara::Detail::BoundRef {
public:
    bool isContainer() const override { return false; }
    // We do NOT override isFlag() so the base class implementation is used
};

// A derived class that does override isFlag to verify base behavior separately
class FlagBoundRef : public Catch::Clara::Detail::BoundRef {
public:
    bool isContainer() const override { return false; }
    bool isFlag() const override { return true; }
};

// Test fixture
class BoundRefTest_659 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that the base BoundRef::isFlag() returns false
TEST_F(BoundRefTest_659, IsFlagReturnsFalse_659) {
    ConcreteBoundRef ref;
    EXPECT_FALSE(ref.isFlag());
}

// Test that isFlag consistently returns false on multiple calls
TEST_F(BoundRefTest_659, IsFlagConsistentlyReturnsFalse_659) {
    ConcreteBoundRef ref;
    EXPECT_FALSE(ref.isFlag());
    EXPECT_FALSE(ref.isFlag());
    EXPECT_FALSE(ref.isFlag());
}

// Test that a derived class can override isFlag to return true
TEST_F(BoundRefTest_659, DerivedCanOverrideIsFlagToTrue_659) {
    FlagBoundRef ref;
    EXPECT_TRUE(ref.isFlag());
}

// Test polymorphic behavior through base pointer - base implementation returns false
TEST_F(BoundRefTest_659, PolymorphicIsFlagReturnsFalseForBase_659) {
    ConcreteBoundRef concreteRef;
    Catch::Clara::Detail::BoundRef* basePtr = &concreteRef;
    EXPECT_FALSE(basePtr->isFlag());
}

// Test polymorphic behavior through base pointer - derived override returns true
TEST_F(BoundRefTest_659, PolymorphicIsFlagReturnsTrueForDerived_659) {
    FlagBoundRef flagRef;
    Catch::Clara::Detail::BoundRef* basePtr = &flagRef;
    EXPECT_TRUE(basePtr->isFlag());
}

// Test that isContainer returns false for the concrete implementation
TEST_F(BoundRefTest_659, IsContainerReturnsFalse_659) {
    ConcreteBoundRef ref;
    EXPECT_FALSE(ref.isContainer());
}

// Test that the destructor can be called without issues (via unique_ptr)
TEST_F(BoundRefTest_659, DestructorDoesNotThrow_659) {
    EXPECT_NO_THROW({
        auto ref = std::make_unique<ConcreteBoundRef>();
        // unique_ptr will call destructor when going out of scope
    });
}

// Test destruction through base class pointer
TEST_F(BoundRefTest_659, VirtualDestructorWorksCorrectly_659) {
    EXPECT_NO_THROW({
        std::unique_ptr<Catch::Clara::Detail::BoundRef> ref =
            std::make_unique<ConcreteBoundRef>();
    });
}

// Test that multiple instances each independently return false for isFlag
TEST_F(BoundRefTest_659, MultipleInstancesAllReturnFalseForIsFlag_659) {
    ConcreteBoundRef ref1;
    ConcreteBoundRef ref2;
    ConcreteBoundRef ref3;
    
    EXPECT_FALSE(ref1.isFlag());
    EXPECT_FALSE(ref2.isFlag());
    EXPECT_FALSE(ref3.isFlag());
}

} // anonymous namespace
