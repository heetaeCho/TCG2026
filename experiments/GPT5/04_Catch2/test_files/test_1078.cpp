// File: tests/json_array_writer_move_1078.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <sstream>

// Include the real header from your tree
#include "catch2/internal/catch_jsonwriter.hpp"

// ---- Compile-time interface checks (do not depend on internals) ----
static_assert(std::is_move_constructible<Catch::JsonArrayWriter>::value,
              "JsonArrayWriter must be move-constructible");
static_assert(!std::is_move_assignable<Catch::JsonArrayWriter>::value,
              "JsonArrayWriter move assignment should be deleted");
static_assert(noexcept(Catch::JsonArrayWriter(std::declval<Catch::JsonArrayWriter&&>())),
              "JsonArrayWriter move constructor should be noexcept");

// --------------------------------- Tests ---------------------------------

// Verifies: After move-constructing, writing via the moved-to writer
// produces observable output into the original stream.
// Does not assume any particular formatting, only that the substring "true" appears.
TEST(JsonArrayWriterMove_1078, MoveTransfersWritingToSameStream_1078) {
    using Catch::JsonArrayWriter;

    std::ostringstream os;
    {
        JsonArrayWriter w1{os};
        JsonArrayWriter w2{std::move(w1)}; // move-construct

        // Write something simple & unambiguous
        w2.write(true);
    }
    const std::string out = os.str();
    // Only assert observable effect — "true" appeared in the stream.
    EXPECT_NE(out.find("true"), std::string::npos);
}

// Verifies: After being moved-from, using the source writer to write does NOT
// add new observable output. We do not assert on exceptions or internal flags;
// we only check that writing via moved-from does not append "false" to the stream.
// If the class intentionally no-ops after move (as the interface allows), this should pass.
TEST(JsonArrayWriterMove_1078, MovedFromWriterDoesNotProduceFurtherOutput_1078) {
    using Catch::JsonArrayWriter;

    std::ostringstream os;
    std::string before, after;
    {
        JsonArrayWriter w1{os};
        JsonArrayWriter w2{std::move(w1)}; // w1 is now moved-from

        w2.write(true);
        before = os.str();

        // Attempt to use the moved-from writer; treat behavior as black box
        // and only observe the stream for any new "false" content.
        w1.write(false);
        after = os.str();
    }

    // Ensure initial write happened
    EXPECT_NE(before.find("true"), std::string::npos);

    // Writing via moved-from should not introduce "false" (observable no-op).
    // We accept either identical output or output that at least does not contain "false".
    EXPECT_EQ(before, after) << "Moved-from writer should not change the stream";
    EXPECT_EQ(after.find("false"), std::string::npos);
}

// Verifies: Moving an already-populated writer preserves its ability to continue writing
// (normal operation case). We do not validate exact JSON, only that both tokens appear.
TEST(JsonArrayWriterMove_1078, WriteBeforeAndAfterMoveAreBothObserved_1078) {
    using Catch::JsonArrayWriter;

    std::ostringstream os;
    {
        JsonArrayWriter w1{os};
        w1.write(false);               // write before move (observable token "false")

        JsonArrayWriter w2{std::move(w1)};
        w2.write(true);                // write after move (observable token "true")
    }
    const std::string out = os.str();
    EXPECT_NE(out.find("false"), std::string::npos);
    EXPECT_NE(out.find("true"), std::string::npos);
}
