#include <gtest/gtest.h>

// Include the header for BoundRef
#include "catch2/internal/catch_clara.hpp"

namespace {

// Since BoundRef has pure virtual methods (isFlag), we need a concrete derived class for testing
class ConcreteBoundRef : public Catch::Clara::Detail::BoundRef {
public:
    bool isFlag() const override { return false; }
};

// Test fixture
class BoundRefTest_658 : public ::testing::Test {
protected:
    void SetUp() override {
        boundRef = std::make_unique<ConcreteBoundRef>();
    }

    std::unique_ptr<ConcreteBoundRef> boundRef;
};

// Test that isContainer returns false by default
TEST_F(BoundRefTest_658, IsContainerReturnsFalse_658) {
    EXPECT_FALSE(boundRef->isContainer());
}

// Test that isContainer consistently returns false on multiple calls
TEST_F(BoundRefTest_658, IsContainerConsistentlyReturnsFalse_658) {
    EXPECT_FALSE(boundRef->isContainer());
    EXPECT_FALSE(boundRef->isContainer());
    EXPECT_FALSE(boundRef->isContainer());
}

// Test that BoundRef can be referenced through base pointer and isContainer still works
TEST_F(BoundRefTest_658, IsContainerViaBasePointerReturnsFalse_658) {
    Catch::Clara::Detail::BoundRef* basePtr = boundRef.get();
    EXPECT_FALSE(basePtr->isContainer());
}

// Test that the destructor can be called through base pointer (virtual destructor)
TEST_F(BoundRefTest_658, VirtualDestructorWorksCorrectly_658) {
    Catch::Clara::Detail::BoundRef* basePtr = new ConcreteBoundRef();
    EXPECT_NO_THROW(delete basePtr);
}

// Test isFlag on the concrete derived class returns false
TEST_F(BoundRefTest_658, DerivedIsFlagReturnsFalse_658) {
    EXPECT_FALSE(boundRef->isFlag());
}

// Test with a derived class that overrides isContainer
class ContainerBoundRef : public Catch::Clara::Detail::BoundRef {
public:
    bool isContainer() const override { return true; }
    bool isFlag() const override { return false; }
};

TEST_F(BoundRefTest_658, DerivedCanOverrideIsContainer_658) {
    ContainerBoundRef containerRef;
    EXPECT_TRUE(containerRef.isContainer());
}

// Test with a derived class that overrides isFlag
class FlagBoundRef : public Catch::Clara::Detail::BoundRef {
public:
    bool isFlag() const override { return true; }
};

TEST_F(BoundRefTest_658, DerivedCanOverrideIsFlag_658) {
    FlagBoundRef flagRef;
    EXPECT_TRUE(flagRef.isFlag());
    // Base isContainer should still return false
    EXPECT_FALSE(flagRef.isContainer());
}

// Test polymorphic behavior - base pointer to derived with overridden isContainer
TEST_F(BoundRefTest_658, PolymorphicIsContainerBehavior_658) {
    std::unique_ptr<Catch::Clara::Detail::BoundRef> base = std::make_unique<ConcreteBoundRef>();
    EXPECT_FALSE(base->isContainer());

    std::unique_ptr<Catch::Clara::Detail::BoundRef> container = std::make_unique<ContainerBoundRef>();
    EXPECT_TRUE(container->isContainer());
}

} // namespace
