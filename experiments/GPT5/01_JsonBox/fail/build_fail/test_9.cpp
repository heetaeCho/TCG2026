// File: test_outputfilter_getinserter_9.cpp
#include <gtest/gtest.h>
#include <sstream>
#include "JsonBox/OutputFilter.h"

// A simple, observable Inserter type for testing.
// It has a public field and trivial behavior so we can observe mutations
// through the reference returned by getInserter().
struct DummyInserter {
    int value{0};
    void set(int v) { value = v; }
};

class OutputFilterGetInserterTest_9 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Normal operation: getInserter returns an lvalue reference to the same internal object
// across calls (i.e., address is stable).
TEST_F(OutputFilterGetInserterTest_9, GetInserter_ReturnsStableReference_9) {
    JsonBox::OutputFilter<DummyInserter> filter(oss.rdbuf(), DummyInserter{}, false);

    auto& ref1 = filter.getInserter();
    auto& ref2 = filter.getInserter();

    // Both references should refer to the same object (same address).
    EXPECT_EQ(&ref1, &ref2);
}

// Normal operation: mutations through the returned reference are observable
// via subsequent calls to getInserter (verifies it is a true reference, not a copy).
TEST_F(OutputFilterGetInserterTest_9, GetInserter_AllowsMutation_9) {
    JsonBox::OutputFilter<DummyInserter> filter(oss.rdbuf(), DummyInserter{}, false);

    auto& inserterRef = filter.getInserter();
    inserterRef.value = 42;

    // A subsequent retrieval should observe the mutated state.
    EXPECT_EQ(42, filter.getInserter().value);
}

// Boundary condition: when constructed without an explicit inserter, the inserter
// should be default-constructed and still be mutable through the returned reference.
TEST_F(OutputFilterGetInserterTest_9, GetInserter_DefaultConstructedInserterIsMutable_9) {
    // Uses the ctor that default-constructs the Inserter.
    JsonBox::OutputFilter<DummyInserter> filter(oss.rdbuf(), false);

    // Default constructed value expected (per DummyInserter).
    EXPECT_EQ(0, filter.getInserter().value);

    // Mutate via the reference and confirm the change persists.
    filter.getInserter().set(7);
    EXPECT_EQ(7, filter.getInserter().value);
}

// Type property check (compile-time): getInserter returns DummyInserter& (non-const lvalue ref).
// This enforces the interface contract at the type level without peeking into internals.
TEST_F(OutputFilterGetInserterTest_9, GetInserter_ReturnTypeIsNonConstLValueReference_9) {
    JsonBox::OutputFilter<DummyInserter> filter(oss.rdbuf(), DummyInserter{}, false);

    // If the following line fails to compile, the contract changed.
    static_assert(std::is_same<decltype(filter.getInserter()), DummyInserter&>::value,
                  "getInserter must return DummyInserter&");
    SUCCEED(); // Reaching here means the static_assert passed.
}
