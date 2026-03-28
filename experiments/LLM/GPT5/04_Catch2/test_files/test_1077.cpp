// File: tests/json_array_writer_constructor_with_indent_1077_tests.cpp

#include <gtest/gtest.h>
#include <sstream>

// Use the real header from your codebase.
// Path based on the prompt; adjust include path as needed in your build system.
#include "catch2/internal/catch_jsonwriter.hpp"

using namespace Catch;

//
// TEST_ID: 1077
// Suite: JsonArrayWriter constructor (ostream&, uint64_t)
// Notes:
//  - We only assert observable effects on the provided std::ostream.
//  - We do NOT assume or re-implement any internal logic beyond what is visible
//    through the interface & observable side effects.
//

// Normal operation: constructing with indent_level = 0 should write an opening bracket.
TEST(JsonArrayWriterTest_1077, WritesOpeningBracketOnConstruction_ZeroIndent_1077) {
    std::ostringstream os;

    // Act: Construct writer with zero indent.
    JsonArrayWriter writer{ os, static_cast<std::uint64_t>(0) };

    // Assert: Stream now begins with '[' (observable side effect).
    EXPECT_EQ(os.str(), "[");
}

// Boundary condition: constructing with a large indent_level should still write an opening bracket.
// We do not assert anything about spacing/indentation (black-box); only that '[' appears immediately.
TEST(JsonArrayWriterTest_1077, WritesOpeningBracketOnConstruction_LargeIndent_1077) {
    std::ostringstream os;
    const std::uint64_t hugeIndent = std::numeric_limits<std::uint64_t>::max();

    // Act
    JsonArrayWriter writer{ os, hugeIndent };

    // Assert
    EXPECT_EQ(os.str(), "[");
}

// Interaction on the same stream: constructing two writers sequentially on the same ostream
// should result in two observable writes (two '[' characters appended).
TEST(JsonArrayWriterTest_1077, MultipleWritersAppendOpeningBracketsToSameStream_1077) {
    std::ostringstream os;

    {
        JsonArrayWriter first{ os, 0 };
        // Destruction behavior is not asserted (black-box). We only check what was written so far.
        EXPECT_EQ(os.str(), "[");
    }

    {
        JsonArrayWriter second{ os, 4 };
        // Now there should be two opening brackets in sequence due to two constructions.
        EXPECT_EQ(os.str(), "[[");
    }
}
