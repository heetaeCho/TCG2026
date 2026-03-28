// File: tests/parser_write_to_stream_670_tests.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Include only public headers/interfaces used by the tests.
#include "catch2/internal/catch_clara.hpp"

using Catch::Clara::Parser;
using Catch::Clara::ExeName;
using Catch::Clara::Detail::HelpColumns;

class ParserWriteToStreamTest_670 : public ::testing::Test {
protected:
    // Utility to produce output from writeToStream
    static std::string render(const Parser& p) {
        std::ostringstream os;
        p.writeToStream(os);
        return os.str();
    }
};

// Normal operation: by default, ExeName is non-empty ("<executable>"),
// so "usage:" and "where options are:" should be present, and the exe name
// should appear in the usage line.
TEST_F(ParserWriteToStreamTest_670, DefaultPrintsUsageAndWhereOptions_670) {
    Parser p; // default-constructed

    const std::string out = render(p);

    // Observable behavior from the provided code path:
    // - When exe name is non-empty, it prints:
    //   "usage:\n <name> ..." and then "\n\nwhere options are:\n"
    EXPECT_NE(out.find("usage:\n"), std::string::npos);
    EXPECT_NE(out.find("<executable>"), std::string::npos);
    EXPECT_NE(out.find("where options are:"), std::string::npos);
}

// Boundary condition: if exe name is set to empty string, the "usage:" header
// (and the trailing "where options are:" line) are *not* printed.
// We do this only via the public interface: ExeName + operator|=.
TEST_F(ParserWriteToStreamTest_670, EmptyExeNameSuppressesUsageSection_670) {
    Parser p;

    ExeName ex;
    // Set to empty via public API; then attach to the parser via operator|=.
    // We do not assert how operator|= stores it; we only observe writeToStream.
    (void)ex.set(std::string{""});
    p |= ex;

    const std::string out = render(p);

    EXPECT_EQ(out.find("usage:"), std::string::npos);
    EXPECT_EQ(out.find("where options are:"), std::string::npos);
    // No further assumptions about remaining content.
}

// Normal operation: If we set a custom executable name via ExeName and combine it
// with the Parser (public operator|=), the name should be reflected in the output.
TEST_F(ParserWriteToStreamTest_670, CustomExeNameIsReflectedInUsage_670) {
    Parser p;

    ExeName ex;
    (void)ex.set(std::string{"mytool"});
    p |= ex;

    const std::string out = render(p);

    EXPECT_NE(out.find("usage:\n"), std::string::npos);
    EXPECT_NE(out.find("mytool"), std::string::npos);
    EXPECT_NE(out.find("where options are:"), std::string::npos);
}

// Verification of external interactions (indirect):
// writeToStream() takes the rows from getHelpColumns() and renders them
// using TextFlow columns. Without assuming exact formatting, we can still
// assert that each row's "left" and at least the beginning of its
// "descriptions" text appear in the output.
TEST_F(ParserWriteToStreamTest_670, HelpColumnsAreRendered_670) {
    Parser p;

    // Obtain the same data writeToStream() will use, through the public API.
    const std::vector<HelpColumns> rows = p.getHelpColumns();

    const std::string out = render(p);

    for (const auto& r : rows) {
        // "left" content should be present somewhere in the output if non-empty.
        if (!r.left.empty()) {
            EXPECT_NE(out.find(r.left), std::string::npos)
                << "Expected left column content to appear in output: '" << r.left << "'";
        }

        // Descriptions are exposed as StringRef; only rely on observable string content.
        const std::string desc = static_cast<std::string>(r.descriptions);
        if (!desc.empty()) {
            // We avoid depending on exact wrapping; check presence of a prefix.
            const std::string probe = desc.substr(0, std::min<size_t>(desc.size(), 10));
            EXPECT_NE(out.find(probe), std::string::npos)
                << "Expected description prefix to appear in output: '" << probe << "'";
        }
    }
}
