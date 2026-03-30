// File: tests/json_array_writer_writeArray_533_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>

// Include the real headers from your project
#include "catch2/internal/catch_jsonwriter.hpp"

using ::testing::HasSubstr;
using ::testing::Not;

// Test fixture to share a stream across tests where needed
class JsonArrayWriterWriteArrayTest_533 : public ::testing::Test {
protected:
    std::ostringstream os_;
};

// [Normal] writeArray returns a writer that writes into the SAME ostream.
// Verification via observable stream content after writing a simple value.
TEST_F(JsonArrayWriterWriteArrayTest_533, WriteArray_ReturnsWriterThatWritesToSameStream_533) {
    Catch::JsonArrayWriter root(os_, /*indent*/ 0);

    // Act: create a child array writer and write a bool
    auto child = root.writeArray();
    child.write(true);

    // Assert: the underlying stream now contains something reflecting the write.
    // We don't assume exact formatting or delimiters — only that "true" appears.
    EXPECT_THAT(os_.str(), HasSubstr("true"));
}

// [Behavior] Two sibling arrays created sequentially write in creation order.
// We only assert relative ordering of observable tokens, not exact formatting.
TEST_F(JsonArrayWriterWriteArrayTest_533, WriteArray_TwoSiblings_PreservesWriteOrder_533) {
    Catch::JsonArrayWriter root(os_, /*indent*/ 0);

    auto first  = root.writeArray();
    first.write(true);

    auto second = root.writeArray();
    second.write(false);

    const std::string out = os_.str();

    // Find tokens; we assert they exist and "true" appears before "false".
    auto posTrue  = out.find("true");
    auto posFalse = out.find("false");

    ASSERT_NE(posTrue,  std::string::npos) << "Expected to observe 'true' written by first child writer";
    ASSERT_NE(posFalse, std::string::npos) << "Expected to observe 'false' written by second child writer";
    EXPECT_LT(posTrue, posFalse) << "Writes from first child should precede writes from second child in the same stream";
}

// [Nested] A nested child writer created from a child still writes into the root stream.
// We validate presence and relative ordering of tokens from different depths.
TEST_F(JsonArrayWriterWriteArrayTest_533, WriteArray_NestedChild_WritesIntoRootStream_533) {
    Catch::JsonArrayWriter root(os_, /*indent*/ 0);

    auto level1 = root.writeArray();
    level1.write(false);

    // Create a nested array from level1 and write a value
    auto level2 = level1.writeArray();
    level2.write(true);

    const std::string out = os_.str();

    // Observable tokens for both writes must appear in the single shared stream
    auto posFalse = out.find("false");
    auto posTrue  = out.find("true");

    ASSERT_NE(posFalse, std::string::npos) << "Expected to observe 'false' from level1";
    ASSERT_NE(posTrue,  std::string::npos) << "Expected to observe 'true'  from level2";
    // Do not assume exact formatting/indentation — only relative ordering from actions taken.
    EXPECT_LT(posFalse, posTrue);
}

// [Boundary] Calling writeArray() without writing any values should be safe and not
// accidentally inject unrelated tokens (e.g., "true"/"false") into the stream.
// We don't assert on specific structural characters (like '[' or commas) to avoid internal assumptions.
TEST_F(JsonArrayWriterWriteArrayTest_533, WriteArray_EmptyChild_NoSpuriousBooleanTokens_533) {
    Catch::JsonArrayWriter root(os_, /*indent*/ 0);

    // Create a child writer and immediately let it go out of scope
    {
        auto child = root.writeArray();
        // No writes performed with the child
    }

    const std::string out = os_.str();
    // Verify that no boolean literals appear due to the empty child usage
    EXPECT_THAT(out, Not(HasSubstr("true")));
    EXPECT_THAT(out, Not(HasSubstr("false")));
}

// [Chaining] Multiple chained writeArray() calls return distinct writers that all write to the same stream.
// We check that both observable tokens are present; no formatting assumptions.
TEST_F(JsonArrayWriterWriteArrayTest_533, WriteArray_ChainedCalls_ProduceWritableChildren_533) {
    Catch::JsonArrayWriter root(os_, /*indent*/ 0);

    auto a = root.writeArray().writeArray(); // chain to produce a deeper child
    a.write(true);

    // Create another child (sibling of the first top-level child) and write
    auto b = root.writeArray();
    b.write(false);

    const std::string out = os_.str();

    ASSERT_NE(out.find("true"),  std::string::npos);
    ASSERT_NE(out.find("false"), std::string::npos);
}

// [Robustness] Interleaving writes between parent and child remains coherent in the shared stream.
// We assert relative ordering only.
TEST_F(JsonArrayWriterWriteArrayTest_533, WriteArray_InterleaveParentAndChildWrites_OrderIsCoherent_533) {
    Catch::JsonArrayWriter root(os_, /*indent*/ 0);

    root.write(false);              // Parent write #1
    auto child = root.writeArray(); // Create child
    child.write(true);              // Child write
    root.write(false);              // Parent write #2

    const std::string out = os_.str();

    auto posP1 = out.find("false");                 // First 'false'
    ASSERT_NE(posP1, std::string::npos);

    // Find 'true' after first 'false'
    auto posC  = out.find("true", posP1 + 1);
    ASSERT_NE(posC, std::string::npos);

    // Find a subsequent 'false' after the 'true'
    auto posP2 = out.find("false", posC + 1);
    ASSERT_NE(posP2, std::string::npos);

    EXPECT_LT(posP1, posC);
    EXPECT_LT(posC,  posP2);
}
