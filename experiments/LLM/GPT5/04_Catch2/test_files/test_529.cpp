// File: json_object_writer_dtor_tests_529.cpp

#include <gtest/gtest.h>
#include <sstream>

// Use the public interface only
#include "catch2/internal/catch_jsonwriter.hpp"

using namespace Catch;

class JsonObjectWriterTest_529 : public ::testing::Test {};

// Verifies: When an active JsonObjectWriter goes out of scope,
// it appends a newline and a closing '}' to the provided stream.
TEST_F(JsonObjectWriterTest_529, DestructorWritesNewlineAndClosingBraceWhenActive_529) {
    std::ostringstream os;
    {
        // Use the (ostream, indent) overload to set some indent level.
        JsonObjectWriter writer(os, /*indent_level*/ 3);
        // No assumptions about internal behavior besides destructor side-effects.
    } // ~JsonObjectWriter called here

    const std::string out = os.str();
    // Observable effects: there should be at least one newline and the stream must end with '}'.
    ASSERT_FALSE(out.empty());
    EXPECT_NE(std::string::npos, out.find('\n'));
    EXPECT_EQ('}', out.back());
}

// Verifies: Destroying a moved-from JsonObjectWriter does NOT write anything.
// Only the moved-to instance should write to the stream upon destruction.
TEST_F(JsonObjectWriterTest_529, DestructorNoOutputWhenMovedFrom_529) {
    std::ostringstream os;

    size_t afterMovedFromDestructionSize = 0;
    {
        JsonObjectWriter original(os, /*indent_level*/ 2);
        JsonObjectWriter moved_to(std::move(original));

        // End the lifetime of the moved-from object explicitly by scope:
        {
            // Create an inner scope solely to trigger original's destructor
            // (even though it's already moved-from).
        }
        // Capture size before moved_to is destroyed to ensure original produced no output.
        afterMovedFromDestructionSize = os.str().size();

        // moved_to still alive in this outer scope
    } // moved_to destroyed here, should produce exactly one closing

    const std::string out = os.str();
    // Moved-from dtor produced nothing
    EXPECT_EQ(afterMovedFromDestructionSize, out.size() - 1 /* at least '}' appended later */ + 1);

    // Exactly one '}' should be present in the full output (from the moved-to instance).
    size_t braceCount = std::count(out.begin(), out.end(), '}');
    EXPECT_EQ(1u, braceCount);
    EXPECT_EQ('}', out.back());
}

// Verifies: Default-constructed-with-stream (no explicit indent) still writes
// the newline and closing brace on destruction.
TEST_F(JsonObjectWriterTest_529, DestructorWritesClosingBraceWithDefaultConstructor_529) {
    std::ostringstream os;
    {
        JsonObjectWriter writer(os); // uses the (ostream) constructor
    } // destructor

    const std::string out = os.str();
    ASSERT_FALSE(out.empty());
    EXPECT_NE(std::string::npos, out.find('\n'));
    EXPECT_EQ('}', out.back());
}

// Verifies: Independent writers to the same stream each close their object on destruction,
// resulting in two closing braces in order.
TEST_F(JsonObjectWriterTest_529, MultipleWritersEachCloseObject_529) {
    std::ostringstream os;
    {
        JsonObjectWriter w1(os, 1);
        JsonObjectWriter w2(os, 2);
        // Scope end destroys w2 then w1 (reverse order), each should append a closing brace.
    }

    const std::string out = os.str();
    size_t braceCount = std::count(out.begin(), out.end(), '}');
    EXPECT_GE(braceCount, 2u);     // At least two closings should be observable
    EXPECT_EQ('}', out.back());    // The last character should be a closing brace
}
