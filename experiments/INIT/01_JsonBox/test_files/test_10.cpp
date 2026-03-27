// File: test_outputfilter_getdestination_10.cpp

#include <gtest/gtest.h>
#include <sstream>
#include "JsonBox/OutputFilter.h"

// A minimal dummy inserter type for template instantiation.
// We don't rely on any behavior—just the type.
struct DummyInserter {
    // must be copyable
    DummyInserter() = default;
};

using JsonBoxOutputFilter = JsonBox::OutputFilter<DummyInserter>;

class OutputFilterTest_10 : public ::testing::Test {
protected:
    std::stringbuf buf1_;
    std::stringbuf buf2_;
};

// Normal operation: constructed with (destination, inserter)
TEST_F(OutputFilterTest_10, GetDestination_WithInserter_ReturnsSamePointer_10) {
    DummyInserter ins;
    JsonBoxOutputFilter f(&buf1_, ins, /*deleteWhenFinished=*/false);

    EXPECT_EQ(f.getDestination(), &buf1_);
}

// Normal operation (overload): constructed with (destination) only
TEST_F(OutputFilterTest_10, GetDestination_WithoutInserter_ReturnsSamePointer_10) {
    JsonBoxOutputFilter f(&buf2_, /*deleteWhenFinished=*/true);

    EXPECT_EQ(f.getDestination(), &buf2_);
}

// Boundary: constructed with nullptr destination (if allowed by interface)
TEST_F(OutputFilterTest_10, GetDestination_NullDestination_ReturnsNullptr_10) {
    DummyInserter ins;
    JsonBoxOutputFilter f(nullptr, ins, /*deleteWhenFinished=*/false);

    EXPECT_EQ(f.getDestination(), nullptr);
}

// API property: method is const—call on const object
TEST_F(OutputFilterTest_10, GetDestination_CallOnConstObject_10) {
    DummyInserter ins;
    JsonBoxOutputFilter f(&buf1_, ins, /*deleteWhenFinished=*/false);

    const JsonBoxOutputFilter& cref = f;
    std::streambuf* dest_from_const = cref.getDestination();

    EXPECT_EQ(dest_from_const, &buf1_);
}
