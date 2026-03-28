#include <gtest/gtest.h>

// Include the header that declares BoundFlagRefBase
#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara::Detail;

// Since BoundFlagRefBase may be abstract (it inherits from BoundRef and has virtual methods),
// we need a concrete derived class for testing purposes.
// We create a minimal concrete implementation that just satisfies the interface.
namespace {

class ConcreteBoundFlagRef : public BoundFlagRefBase {
public:
    // Implement any pure virtual methods from BoundRef or BoundFlagRefBase
    // that are needed to make the class instantiable.
    
    ParserResult setValue(std::string const& arg) override {
        // Minimal implementation for testing
        return ParserResult::ok(ParseResultType::Matched);
    }
    
    ParserResult setFlag(bool flag) override {
        m_flag = flag;
        return ParserResult::ok(ParseResultType::Matched);
    }
    
    bool m_flag = false;
};

} // anonymous namespace

class BoundFlagRefBaseTest_660 : public ::testing::Test {
protected:
    ConcreteBoundFlagRef flagRef;
};

// Test that isFlag() returns true for BoundFlagRefBase
TEST_F(BoundFlagRefBaseTest_660, IsFlagReturnsTrue_660) {
    EXPECT_TRUE(flagRef.isFlag());
}

// Test that isFlag() consistently returns true on multiple calls
TEST_F(BoundFlagRefBaseTest_660, IsFlagReturnsTrueConsistently_660) {
    EXPECT_TRUE(flagRef.isFlag());
    EXPECT_TRUE(flagRef.isFlag());
    EXPECT_TRUE(flagRef.isFlag());
}

// Test isFlag via pointer to base (polymorphic behavior)
TEST_F(BoundFlagRefBaseTest_660, IsFlagReturnsTrueViaBasePointer_660) {
    BoundFlagRefBase* basePtr = &flagRef;
    EXPECT_TRUE(basePtr->isFlag());
}

// Test that isFlag returns true even after setFlag has been called
TEST_F(BoundFlagRefBaseTest_660, IsFlagReturnsTrueAfterSetFlag_660) {
    flagRef.setFlag(true);
    EXPECT_TRUE(flagRef.isFlag());
    
    flagRef.setFlag(false);
    EXPECT_TRUE(flagRef.isFlag());
}

// Test that a different instance also returns true for isFlag
TEST_F(BoundFlagRefBaseTest_660, DifferentInstanceIsFlagReturnsTrue_660) {
    ConcreteBoundFlagRef anotherFlagRef;
    EXPECT_TRUE(anotherFlagRef.isFlag());
}

// Test const correctness - isFlag is const
TEST_F(BoundFlagRefBaseTest_660, IsFlagWorksOnConstObject_660) {
    const ConcreteBoundFlagRef constFlagRef;
    EXPECT_TRUE(constFlagRef.isFlag());
}

// Test const pointer to base
TEST_F(BoundFlagRefBaseTest_660, IsFlagWorksOnConstBasePointer_660) {
    const BoundFlagRefBase* constBasePtr = &flagRef;
    EXPECT_TRUE(constBasePtr->isFlag());
}
