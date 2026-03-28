// File: tests/TablePrinter_OutputFlush_761.cpp
#include <gtest/gtest.h>
#include <ostream>
#include <streambuf>
#include <string>

// Adjust this include to your project layout as needed:
#include <catch2/reporters/catch_reporter_console.hpp>

using namespace Catch;

namespace {

// A tracking streambuf to observe flushes (sync calls) without peeking into TablePrinter internals.
class TrackingBuf : public std::stringbuf {
public:
    int sync() override {
        ++flushCount_;
        return std::stringbuf::sync();
    }
    int flushCount() const noexcept { return flushCount_; }
private:
    int flushCount_ = 0;
};

// Minimal fixture to host a custom ostream using TrackingBuf.
class TablePrinterOutputFlushTest_761 : public ::testing::Test {
protected:
    TrackingBuf buf_;
    std::ostream os_{ &buf_ };
};

} // namespace

// --- Tests ---

// [TEST_ID = 761]
// Ensures that streaming OutputFlush into TablePrinter flushes the underlying stream (one sync).
TEST_F(TablePrinterOutputFlushTest_761, FlushesUnderlyingStream_761) {
    // Construct TablePrinter with the observable ostream.
    // If your TablePrinter requires different args, adapt here (but keep the observable ostream).
    TablePrinter tp{ os_ };

    EXPECT_EQ(buf_.flushCount(), 0) << "Precondition: no flush before operator<<";

    // Act: invoke the operator under test
    tp << OutputFlush{};

    EXPECT_EQ(buf_.flushCount(), 1) << "OutputFlush should flush the underlying stream exactly once";
}

// [TEST_ID = 761]
// Ensures that the operator returns the same TablePrinter reference, enabling chaining.
TEST_F(TablePrinterOutputFlushTest_761, ReturnsSameReferenceForChaining_761) {
    TablePrinter tp{ os_ };

    TablePrinter* before = &tp;
    TablePrinter* after  = &(tp << OutputFlush{});

    EXPECT_EQ(before, after) << "operator<< (OutputFlush) must return the same TablePrinter reference";
}

// [TEST_ID = 761]
// Ensures the flush manipulator does not emit extra characters into the stream buffer.
TEST_F(TablePrinterOutputFlushTest_761, ProducesNoAdditionalOutput_761) {
    TablePrinter tp{ os_ };

    // Prime the buffer with some content to ensure flush doesn't alter it
    os_ << "payload";
    ASSERT_EQ(buf_.str(), "payload");

    tp << OutputFlush{};

    // Flush should not change existing content or append new characters
    EXPECT_EQ(buf_.str(), "payload") << "OutputFlush must not write additional characters";
}
