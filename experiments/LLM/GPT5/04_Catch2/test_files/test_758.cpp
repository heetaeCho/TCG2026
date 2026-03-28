// File: tests/TablePrinter_StreamOperator_758.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <vector>

// Include the real Catch2 headers that declare TablePrinter/ColumnInfo.
// Adjust include paths to your repo layout as needed.
#include "catch2/reporters/catch_reporter_console.hpp"  // or the header that exposes TablePrinter

// NOTE: We treat TablePrinter as a black box and only use its public interface.
// We do not assume anything about internal buffers beyond effects observable
// via the provided std::ostream after open()/close().

using Catch::TablePrinter;
using Catch::ColumnInfo;

class TablePrinterStreamOpTest_758 : public ::testing::Test {
protected:
    std::ostringstream os;                       // observable sink
    std::vector<ColumnInfo> noColumns;           // minimal column set (empty)
};

// Verifies that the templated operator<< returns a TablePrinter& (enabling chaining)
TEST_F(TablePrinterStreamOpTest_758, OperatorReturnsSelfReference_758) {
    TablePrinter tp(os, noColumns);

    // Exercise: stream a value and capture the address of the returned reference.
    TablePrinter* ret = &(tp << "hello");

    // Expect: returned reference is the same object (allows chaining).
    EXPECT_EQ(ret, &tp);
}

// Verifies chaining across heterogeneous types compiles and still returns self reference
TEST_F(TablePrinterStreamOpTest_758, ChainedInsertionAcrossTypesReturnsSelf_758) {
    TablePrinter tp(os, noColumns);

    // Exercise: chain various streamable types
    TablePrinter* ret = &(tp << "str" << ' ' << 123 << ' ' << 3.14159);

    // Expect: chaining preserves self reference
    EXPECT_EQ(ret, &tp);
}

// Verifies operator<< works with user-defined types that are streamable to std::ostream
// (observable only through successful chaining & no-throw; content visibility is verified in next test)
namespace {
struct Printable {
    int v{7};
};
std::ostream& operator<<(std::ostream& o, const Printable& p) {
    return o << "[Printable:" << p.v << "]";
}
} // namespace

TEST_F(TablePrinterStreamOpTest_758, StreamsUserDefinedType_CompilesAndChains_758) {
    TablePrinter tp(os, noColumns);
    Printable p{42};

    // Exercise: stream user-defined type; should compile and allow chaining
    EXPECT_NO_THROW({
        TablePrinter* ret = &(tp << p);
        EXPECT_EQ(ret, &tp);
    });
}

// Best-effort observable-behavior test:
// Many TablePrinter implementations flush buffered cell text to the provided ostream
// during lifecycle events such as open()/close(). Without relying on internals,
// we assert that text we streamed becomes observable in the output after a plausible
// lifecycle (open -> stream -> close). If the real implementation prints at a different
// point, this test may need adjusting to that public behavior (still black-box).
TEST_F(TablePrinterStreamOpTest_758, BufferedContentBecomesObservableAfterLifecycle_758) {
    TablePrinter tp(os, noColumns);

    // Exercise: typical lifecycle
    EXPECT_NO_THROW(tp.open());
    tp << "alpha" << ' ' << 99;
    EXPECT_NO_THROW(tp.close());

    // Assert (best-effort): the provided ostream eventually sees what we streamed.
    // We only check substrings to remain resilient to any table formatting.
    const std::string out = os.str();
    // These expectations are intentionally soft (substring) to avoid coupling to formatting.
    EXPECT_NE(out.find("alpha"), std::string::npos);
    EXPECT_NE(out.find("99"), std::string::npos);
}

// Safety: streaming nothing should not crash and should not produce output unless the
// TablePrinter's public lifecycle dictates so. We only assert that the lifecycle is no-throw.
TEST_F(TablePrinterStreamOpTest_758, NoContent_NoCrash_758) {
    TablePrinter tp(os, noColumns);
    EXPECT_NO_THROW(tp.open());
    EXPECT_NO_THROW(tp.close());
    // No strict assertion on os.str() content to avoid assuming formatting.
}
