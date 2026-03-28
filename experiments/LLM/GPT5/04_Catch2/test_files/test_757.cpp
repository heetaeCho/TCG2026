// File: tests/TablePrinter_close_757_tests.cpp

#include <gtest/gtest.h>
#include <ostream>
#include <streambuf>
#include <string>
#include <vector>
#include <sstream>

// Include the real TablePrinter declaration if available.
// If your project exposes a public header, prefer including it instead.
// #include <catch2/reporters/catch_reporter_console.hpp>

namespace Catch {
// Forward-declare ColumnInfo so we can construct an empty vector for TablePrinter.
// (We are NOT re-implementing TablePrinter; just satisfying the constructor arg type.)
struct ColumnInfo;

// Forward-declare TablePrinter interface we use in tests.
// Prefer including the real header if present.
class TablePrinter {
public:
    TablePrinter(std::ostream& os, std::vector<ColumnInfo> columnInfos);
    auto columnInfos() const -> std::vector<ColumnInfo> const&;
    void open();
    void close();
};
} // namespace Catch

// A streambuf that counts how many times flush/sync is requested.
// This is a collaborator we control (the ostream provided to TablePrinter),
// so using it is allowed by the constraints.
class SyncCountingStringBuf : public std::stringbuf {
public:
    int sync() override {
        ++sync_calls;
        return std::stringbuf::sync();
    }
    int sync_calls = 0;
};

class ConsoleTablePrinterTest_757 : public ::testing::Test {
protected:
    // Test harness owns a counting buffer and an ostream that uses it.
    SyncCountingStringBuf buf_;
    std::ostream os_{&buf_};

    // Helper to build a TablePrinter with an empty ColumnInfo set.
    Catch::TablePrinter makePrinter() {
        std::vector<Catch::ColumnInfo> cols; // empty is fine; we don't assert on layout
        return Catch::TablePrinter(os_, std::move(cols));
    }

    // Convenience: current output string
    std::string str() const { return buf_.str(); }
};

// [Normal/No-op] close() when not open: no output, no flush.
TEST_F(ConsoleTablePrinterTest_757, CloseWhenNotOpen_NoOutputAndNoFlush_757) {
    auto printer = makePrinter();

    // Act
    printer.close();

    // Assert: nothing written and no flush requested
    EXPECT_TRUE(str().empty());
    EXPECT_EQ(buf_.sync_calls, 0);
}

// [Normal] close() after open(): should write a trailing newline and flush exactly once.
TEST_F(ConsoleTablePrinterTest_757, CloseAfterOpen_WritesNewlineAndFlushesOnce_757) {
    auto printer = makePrinter();

    // Arrange
    printer.open();
    const auto before = str();

    // Act
    printer.close();

    // Assert: output increased and ends with '\n'
    const auto after = str();
    ASSERT_GE(after.size(), before.size());
    ASSERT_FALSE(after.empty());
    EXPECT_EQ(after.back(), '\n');

    // Assert: exactly one flush from close() path
    EXPECT_EQ(buf_.sync_calls, 1);
}

// [Idempotency] calling close() twice after open() should not add extra output or extra flushes.
TEST_F(ConsoleTablePrinterTest_757, DoubleClose_Idempotent_NoExtraOutputOrFlush_757) {
    auto printer = makePrinter();
    printer.open();

    // First close
    printer.close();
    const auto size_after_first = str().size();
    const auto flush_after_first = buf_.sync_calls;

    // Second close
    printer.close();

    // Assert: no more bytes, no more flush
    EXPECT_EQ(str().size(), size_after_first);
    EXPECT_EQ(buf_.sync_calls, flush_after_first);
}

// [Boundary] multiple close() calls without ever opening remain no-ops.
TEST_F(ConsoleTablePrinterTest_757, MultipleCloseWithoutOpen_StillNoOutputOrFlush_757) {
    auto printer = makePrinter();

    printer.close();
    printer.close();
    printer.close();

    EXPECT_TRUE(str().empty());
    EXPECT_EQ(buf_.sync_calls, 0);
}
