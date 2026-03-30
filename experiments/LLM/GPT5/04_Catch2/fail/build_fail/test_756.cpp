// File: tests/table_printer_open_756.cpp
#include <gtest/gtest.h>
#include <sstream>

// Rely on the public interface only.
#include <catch2/reporters/catch_reporter_console.hpp>

namespace {

using Catch::TablePrinter;
using Catch::ColumnInfo;

class TablePrinterOpenTest_756 : public ::testing::Test {
protected:
    std::ostringstream os;
};

} // namespace

// Normal operation: With no columns, open() should still write a header section
// consisting of (potentially empty) header line(s) and a separator line of '-'.
TEST_F(TablePrinterOpenTest_756, OpenPrintsHeaderAndSeparator_756) {
    std::vector<ColumnInfo> columns; // empty on purpose (no assumptions about ColumnInfo::name)
    TablePrinter tp{os, columns};

    tp.open();

    const std::string out = os.str();

    // Must contain at least one newline (header/spacing) and a line of '-' followed by newline.
    // We do not assert the exact width; we only assert presence of a dashed line.
    // Keep this robust to different console widths/formatters.
    ASSERT_FALSE(out.empty()) << "open() should write something to the stream";

    // Look for "\n-----...\n"
    const auto firstDash = out.find('\n');
    ASSERT_NE(firstDash, std::string::npos) << "Expected at least one newline in the output";

    // Find any line made exclusively of '-' characters followed by newline.
    bool hasDashedLine = false;
    {
        std::istringstream in(out);
        std::string line;
        while (std::getline(in, line)) {
            if (!line.empty() && line.find_first_not_of('-') == std::string::npos) {
                hasDashedLine = true;
                break;
            }
        }
    }
    EXPECT_TRUE(hasDashedLine) << "Expected a separator line made of '-' characters";
}

// Idempotence/boundary behavior: Calling open() again should not duplicate the header.
TEST_F(TablePrinterOpenTest_756, OpenIsIdempotent_756) {
    std::vector<ColumnInfo> columns; // empty, so we don't depend on column names
    TablePrinter tp{os, columns};

    tp.open();
    const std::string once = os.str();

    // Call open() again; should not add more output.
    tp.open();
    const std::string twice = os.str();

    EXPECT_EQ(twice, once) << "open() called twice should not duplicate header output";
}

// (Optional) Defensive behavior around repeated calls is already covered above.
// We avoid testing invalid widths because that requires making assumptions
// about ColumnInfo members beyond the provided interface and about
// assert/termination behavior in different build modes.
