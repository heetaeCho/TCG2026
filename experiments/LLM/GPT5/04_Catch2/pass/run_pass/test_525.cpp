// File: json_value_writer_tests_525.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <limits>

// Include the interface under test
#include "catch2/internal/catch_jsonwriter.hpp"

using Catch::JsonValueWriter;

// Simple helper: create a writer bound to an ostream and return both.
struct WriterWithStream {
    std::ostringstream os;
    JsonValueWriter writer;
    WriterWithStream() : os(), writer(os) {}
};

// A trivial type with operator<< to verify generic T handling
struct CustomType525 {
    int x{7};
};
inline std::ostream& operator<<(std::ostream& os, const CustomType525& v) {
    os << "CustomType525:" << v.x;
    return os;
}

class JsonValueWriterTest_525 : public ::testing::Test {};

// Normal operation: arithmetic value should be written (no assumption on quoting)
TEST_F(JsonValueWriterTest_525, Write_Int_WritesDigits_525) {
    WriterWithStream w;
    std::move(w.writer).write(123);
    const std::string out = w.os.str();
    // Only assert that "123" appears in the output (observable substring)
    EXPECT_NE(out.find("123"), std::string::npos);
}

// Normal operation: double should be written (no assumption on formatting details)
TEST_F(JsonValueWriterTest_525, Write_Double_WritesNumber_525) {
    WriterWithStream w;
    std::move(w.writer).write(3.5);
    const std::string out = w.os.str();
    // Check that at least "3.5" appears (common observable content)
    EXPECT_NE(out.find("3.5"), std::string::npos);
}

// Specific overload: bool should be written using bool overload (observable as true/false or 1/0)
TEST_F(JsonValueWriterTest_525, Write_Bool_WritesBooleanToken_525) {
    WriterWithStream w;
    std::move(w.writer).write(true);
    const std::string out = w.os.str();
    // Accept either textual or numeric boolean representation
    bool looks_bool = (out.find("true") != std::string::npos) ||
                      (out.find("false") != std::string::npos) ||
                      (out.find("1") != std::string::npos) ||
                      (out.find("0") != std::string::npos);
    EXPECT_TRUE(looks_bool);
}

// String-like input: ensure the payload text appears (without assuming exact quoting/escaping)
TEST_F(JsonValueWriterTest_525, Write_CString_ContainsPayload_525) {
    WriterWithStream w;
    const char* msg = "hello_525";
    std::move(w.writer).write(msg);
    const std::string out = w.os.str();
    EXPECT_NE(out.find("hello_525"), std::string::npos);
}

// Generic T path: user-defined type with operator<< should produce its text
TEST_F(JsonValueWriterTest_525, Write_CustomType_ContainsStreamedRepresentation_525) {
    WriterWithStream w;
    CustomType525 c;
    std::move(w.writer).write(c);
    const std::string out = w.os.str();
    EXPECT_NE(out.find("CustomType525:7"), std::string::npos);
}

// Boundary: very large integer should be written completely
TEST_F(JsonValueWriterTest_525, Write_Int64Max_WritesAllDigits_525) {
    WriterWithStream w;
    auto v = std::numeric_limits<long long>::max();
    std::move(w.writer).write(v);
    const std::string out = w.os.str();
    // Convert the expected digits and verify they appear
    std::string expected = std::to_string(v);
    EXPECT_NE(out.find(expected), std::string::npos);
}

// Boundary: empty string should not drop content (presence of serialization around it is fine)
TEST_F(JsonValueWriterTest_525, Write_EmptyCString_EmitsSomethingAndContainsEmptyPayload_525) {
    WriterWithStream w;
    const char* empty = "";
    std::move(w.writer).write(empty);
    const std::string out = w.os.str();
    // Should produce some output (e.g., quotes, etc.). At minimum, not remain empty.
    EXPECT_FALSE(out.empty());
    // And the empty payload is trivially contained at any position; still check writer touched stream
    // (already ensured by not-empty).
}
