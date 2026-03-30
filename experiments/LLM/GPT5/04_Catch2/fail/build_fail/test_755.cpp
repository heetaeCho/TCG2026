// File: tests/table_printer_columnInfos_755.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <type_traits>
#include <vector>

// Include the production header(s) that declare Catch::TablePrinter and Catch::ColumnInfo.
// If your build exposes the class only via catch_reporter_console.cpp, include the
// appropriate umbrella header for reporters instead.
#include "catch2/reporters/catch_reporter_console.hpp"

namespace {

using Catch::TablePrinter;
using Catch::ColumnInfo;

class TablePrinterTest_755 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Verifies that columnInfos() returns a const reference, and that repeated calls
// alias the same underlying container (observable via address equality).
TEST_F(TablePrinterTest_755, ColumnInfosReturnsConstRef_755) {
    std::vector<ColumnInfo> infos; // empty set of columns (boundary: 0 columns)
    TablePrinter tp(oss, infos);

    // Type-level property: returned type is const reference
    static_assert(std::is_same_v<decltype(tp.columnInfos()), std::vector<ColumnInfo> const&>,
                  "columnInfos() must return const std::vector<ColumnInfo>&");

    auto const& ref1 = tp.columnInfos();
    auto const& ref2 = tp.columnInfos();

    // Same address -> same underlying container
    EXPECT_EQ(&ref1, &ref2);
    // For empty input, observable size should be 0
    EXPECT_EQ(ref1.size(), 0u);
}

// Normal operation: Non-empty columns -> size matches what we provided at construction.
// We do not depend on ColumnInfo internals; size is an observable property.
TEST_F(TablePrinterTest_755, ColumnInfosSizeMatchesCtorInput_Single_755) {
    std::vector<ColumnInfo> infos(1); // 1 default-constructed column
    TablePrinter tp(oss, infos);

    auto const& cols = tp.columnInfos();
    EXPECT_EQ(cols.size(), infos.size());
}

// Normal operation: multiple entries.
TEST_F(TablePrinterTest_755, ColumnInfosSizeMatchesCtorInput_Multiple_755) {
    std::vector<ColumnInfo> infos(3); // 3 default-constructed columns
    TablePrinter tp(oss, infos);

    auto const& cols = tp.columnInfos();
    EXPECT_EQ(cols.size(), infos.size());
}

// Boundary/exceptional-style observability: mutating the original vector after construction
// must not affect the already-constructed TablePrinter’s column list (constructor took by value).
TEST_F(TablePrinterTest_755, ColumnInfosUnaffectedByExternalMutationsAfterCtor_755) {
    std::vector<ColumnInfo> infos(2);
    TablePrinter tp(oss, infos);

    // Mutate the original vector *after* constructing tp.
    infos.push_back(ColumnInfo{});
    infos.push_back(ColumnInfo{});

    // Observable behavior: tp’s columns remain what they were at construction time.
    auto const& cols = tp.columnInfos();
    EXPECT_EQ(cols.size(), 2u);
}

// Stability across other public interactions: calling open()/close() should not invalidate
// the reference or change the observable size (no reliance on internals).
TEST_F(TablePrinterTest_755, ColumnInfosStableAcrossOpenClose_755) {
    std::vector<ColumnInfo> infos(4);
    TablePrinter tp(oss, infos);

    auto const& before = tp.columnInfos();
    ASSERT_EQ(before.size(), 4u);

    // Exercise other public methods; we do not assert their internal effects.
    tp.open();
    tp.close();

    auto const& after = tp.columnInfos();

    // Still aliases the same container
    EXPECT_EQ(&before, &after);
    // Size remains the same (observable property)
    EXPECT_EQ(after.size(), 4u);
}

} // namespace
