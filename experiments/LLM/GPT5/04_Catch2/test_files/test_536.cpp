// File: json_value_writer_writeArray_rvalue_tests_536.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <sstream>

// Include the header that declares JsonValueWriter / JsonArrayWriter
#include "catch2/internal/catch_jsonwriter.hpp"

namespace {

using Catch::JsonValueWriter;
using Catch::JsonArrayWriter;

// ---------- Compile-time interface checks ----------

// Ensures that calling writeArray() on an rvalue returns a JsonArrayWriter.
static_assert(std::is_same<
                  decltype(std::declval<JsonValueWriter&&>().writeArray()),
                  JsonArrayWriter
              >::value,
              "writeArray() called on an rvalue JsonValueWriter must return JsonArrayWriter");

// ---------- Runtime smoke tests relying only on observable behavior ----------

struct JsonValueWriterWriteArrayTest_536 : ::testing::Test {};

TEST_F(JsonValueWriterWriteArrayTest_536, RvalueCallCompilesAndRuns_536) {
    std::ostringstream os;
    // Create a temporary (rvalue) and call writeArray(); we don't assert on
    // side-effects, only that the call is valid and does not throw.
    EXPECT_NO_THROW({
        (void)JsonValueWriter{os}.writeArray();
    });
}

TEST_F(JsonValueWriterWriteArrayTest_536, RvalueCallWithExplicitIndentCompilesAndRuns_536) {
    std::ostringstream os;
    // If the interface provides a ctor with an explicit indent level,
    // this verifies the overload can still be used with rvalue-qualified writeArray().
    EXPECT_NO_THROW({
        JsonValueWriter w{os, static_cast<std::uint64_t>(2)};
        (void)std::move(w).writeArray();
    });
}

} // namespace
