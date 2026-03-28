// File: test/OutputFilterTest_6.cpp
#include <gtest/gtest.h>
#include <streambuf>
#include <sstream>
#include <memory>

#include "JsonBox/OutputFilter.h"  // class under test

using namespace JsonBox;

namespace {

// A tiny streambuf that flips a flag when destroyed, so we can observe deletion.
struct TrackedBuf : public std::stringbuf {
    explicit TrackedBuf(bool* destroyed_flag) : flag(destroyed_flag) {
        if (flag) *flag = false;
    }
    ~TrackedBuf() override {
        if (flag) *flag = true;
    }
    bool* flag;
};

// Minimal inserter type to instantiate the template. We don't assume internal use.
struct DummyInserter {
    int tag = 0;
    void operator()(int /*unused*/) { /* no-op for tests */ }
};

using DUT = OutputFilter<DummyInserter>;

} // namespace

class OutputFilterTest_6 : public ::testing::Test {};

// Destructor deletes destination when deleteWhenFinished == true.
TEST_F(OutputFilterTest_6, DtorDeletesDestination_WhenFlagTrue_6) {
    bool destroyed = false;
    auto* buf = new TrackedBuf(&destroyed);
    {
        // Construct with (destination, inserter, deleteWhenFinished=true)
        DummyInserter ins;
        auto* dut = new DUT(buf, ins, /*deleteWhenFinished=*/true);
        // Deleting DUT should delete 'buf' internally.
        delete dut;
    }
    EXPECT_TRUE(destroyed);
}

// Destructor
