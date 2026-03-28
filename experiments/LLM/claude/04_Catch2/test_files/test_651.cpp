#include <gtest/gtest.h>
#include <string>
#include <memory>
#include <sstream>

// Include the necessary Catch2 headers
#include "catch2/internal/catch_istream.hpp"

namespace {

// Test fixture for makeStream tests
class MakeStreamTest_651 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Empty filename returns a valid stream (CoutStream)
TEST_F(MakeStreamTest_651, EmptyFilenameReturnsCoutStream_651) {
    auto stream = Catch::makeStream("");
    ASSERT_NE(stream, nullptr);
    // The stream should have a valid std::ostream reference
    std::ostream& os = stream->stream();
    EXPECT_TRUE(os.good());
}

// Test: Dash ("-") filename returns a valid stream (CoutStream)
TEST_F(MakeStreamTest_651, DashFilenameReturnsCoutStream_651) {
    auto stream = Catch::makeStream("-");
    ASSERT_NE(stream, nullptr);
    std::ostream& os = stream->stream();
    EXPECT_TRUE(os.good());
}

// Test: "%debug" filename returns a valid DebugOutStream
TEST_F(MakeStreamTest_651, PercentDebugReturnsDebugOutStream_651) {
    auto stream = Catch::makeStream("%debug");
    ASSERT_NE(stream, nullptr);
    std::ostream& os = stream->stream();
    // DebugOutStream should provide a valid ostream
    EXPECT_NE(&os, nullptr);
}

// Test: "%stderr" filename returns a valid CerrStream
TEST_F(MakeStreamTest_651, PercentStderrReturnsCerrStream_651) {
    auto stream = Catch::makeStream("%stderr");
    ASSERT_NE(stream, nullptr);
    std::ostream& os = stream->stream();
    EXPECT_TRUE(os.good());
}

// Test: "%stdout" filename returns a valid CoutStream
TEST_F(MakeStreamTest_651, PercentStdoutReturnsCoutStream_651) {
    auto stream = Catch::makeStream("%stdout");
    ASSERT_NE(stream, nullptr);
    std::ostream& os = stream->stream();
    EXPECT_TRUE(os.good());
}

// Test: Unrecognised stream starting with '%' throws an error
TEST_F(MakeStreamTest_651, UnrecognisedPercentStreamThrows_651) {
    EXPECT_THROW(Catch::makeStream("%unknown"), std::runtime_error);
}

// Test: Another unrecognised percent stream
TEST_F(MakeStreamTest_651, UnrecognisedPercentStreamThrows2_651) {
    EXPECT_THROW(Catch::makeStream("%foo"), std::runtime_error);
}

// Test: Regular filename creates a FileStream (valid file path)
TEST_F(MakeStreamTest_651, RegularFilenameCreatesFileStream_651) {
    // Use a temporary file that can be created
    std::string tempFile = "test_output_651.txt";
    auto stream = Catch::makeStream(tempFile);
    ASSERT_NE(stream, nullptr);
    std::ostream& os = stream->stream();
    // We should be able to write to it
    os << "test data";
    EXPECT_TRUE(os.good());
    // Cleanup
    stream.reset();
    std::remove(tempFile.c_str());
}

// Test: Writing to CoutStream (from empty filename) doesn't crash
TEST_F(MakeStreamTest_651, WritingToCoutStreamDoesNotCrash_651) {
    auto stream = Catch::makeStream("");
    ASSERT_NE(stream, nullptr);
    std::ostream& os = stream->stream();
    os << "Hello from test";
    // Should not crash or set bad bits (cout should be fine)
    EXPECT_FALSE(os.bad());
}

// Test: Writing to CerrStream doesn't crash
TEST_F(MakeStreamTest_651, WritingToCerrStreamDoesNotCrash_651) {
    auto stream = Catch::makeStream("%stderr");
    ASSERT_NE(stream, nullptr);
    std::ostream& os = stream->stream();
    os << "Error test output";
    EXPECT_FALSE(os.bad());
}

// Test: Writing to DebugOutStream doesn't crash
TEST_F(MakeStreamTest_651, WritingToDebugOutStreamDoesNotCrash_651) {
    auto stream = Catch::makeStream("%debug");
    ASSERT_NE(stream, nullptr);
    std::ostream& os = stream->stream();
    os << "Debug test output";
    // Should not crash; we just check the stream isn't null
    EXPECT_NE(&os, nullptr);
}

// Test: Percent sign alone as filename is an unrecognised stream
TEST_F(MakeStreamTest_651, PercentAloneThrows_651) {
    EXPECT_THROW(Catch::makeStream("%"), std::runtime_error);
}

// Test: FileStream with a valid writable path works correctly
TEST_F(MakeStreamTest_651, FileStreamWriteAndVerify_651) {
    std::string tempFile = "test_filestream_verify_651.txt";
    {
        auto stream = Catch::makeStream(tempFile);
        ASSERT_NE(stream, nullptr);
        std::ostream& os = stream->stream();
        os << "verify content";
        EXPECT_TRUE(os.good());
    }
    // Verify the file was written
    std::ifstream inFile(tempFile);
    ASSERT_TRUE(inFile.is_open());
    std::string content;
    std::getline(inFile, content);
    EXPECT_EQ(content, "verify content");
    inFile.close();
    std::remove(tempFile.c_str());
}

// Test: Multiple streams can be created simultaneously
TEST_F(MakeStreamTest_651, MultipleStreamsSimultaneously_651) {
    auto stream1 = Catch::makeStream("");
    auto stream2 = Catch::makeStream("-");
    auto stream3 = Catch::makeStream("%stdout");
    auto stream4 = Catch::makeStream("%stderr");
    
    ASSERT_NE(stream1, nullptr);
    ASSERT_NE(stream2, nullptr);
    ASSERT_NE(stream3, nullptr);
    ASSERT_NE(stream4, nullptr);
}

// Test: Case sensitivity - "%DEBUG" should not be recognized (starts with '%' but not "%debug")
TEST_F(MakeStreamTest_651, CaseSensitivePercentStream_651) {
    EXPECT_THROW(Catch::makeStream("%DEBUG"), std::runtime_error);
}

// Test: Case sensitivity for stderr
TEST_F(MakeStreamTest_651, CaseSensitiveStderr_651) {
    EXPECT_THROW(Catch::makeStream("%STDERR"), std::runtime_error);
}

// Test: Case sensitivity for stdout
TEST_F(MakeStreamTest_651, CaseSensitiveStdout_651) {
    EXPECT_THROW(Catch::makeStream("%STDOUT"), std::runtime_error);
}

} // namespace
