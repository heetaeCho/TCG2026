// File: catch_stdstreams_test_547.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

// The header/decl for Catch::cout() would normally be included.
// For the purpose of testing based on the provided interface:
namespace Catch { std::ostream& cout(); }

// Simple RAII redirector to avoid cross-test interference.
class CoutRedirector {
public:
    explicit CoutRedirector(std::ostream& replacement)
        : old_buf_(std::cout.rdbuf(replacement.rdbuf())),
          old_flags_(std::cout.flags()),
          old_fill_(std::cout.fill()) {}

    ~CoutRedirector() {
        std::cout.rdbuf(old_buf_);
        std::cout.flags(old_flags_);
        std::cout.fill(old_fill_);
        std::cout.flush();
    }

private:
    std::streambuf*         old_buf_;
    std::ios::fmtflags      old_flags_;
    char                    old_fill_;
};

// ---------- Tests ----------

TEST(StdStreamsTest_547, ReturnsStdCoutReference_547) {
    // Verifies that Catch::cout() returns a reference to std::cout
    std::ostream* catch_cout_ptr = &Catch::cout();
    std::ostream* std_cout_ptr   = &std::cout;
    EXPECT_EQ(catch_cout_ptr, std_cout_ptr);
}

TEST(StdStreamsTest_547, WritesGoToStdCoutBuffer_547) {
    // Redirect std::cout to capture output, then write via Catch::cout()
    std::ostringstream sink;
    CoutRedirector redirect(sink);

    Catch::cout() << "hello, world";
    // Ensure content written through Catch::cout() reached std::cout's buffer
    EXPECT_EQ(sink.str(), "hello, world");
}

TEST(StdStreamsTest_547, ManipulatorsBehaveConsistently_547) {
    // std::endl should insert a newline and flush the stream
    std::ostringstream sink;
    CoutRedirector redirect(sink);

    Catch::cout() << "line1" << std::endl << "line2";
    EXPECT_EQ(sink.str(), std::string("line1\nline2"));
}

TEST(StdStreamsTest_547, SharesFormattingStateWithStdCout_547) {
    // Changes to std::cout's formatting should affect Catch::cout(), since they are the same stream
    std::ostringstream sink;
    CoutRedirector redirect(sink);

    // Set formatting on std::cout (hex base)
    std::cout.setf(std::ios::hex, std::ios::basefield);

    // Write using Catch::cout() and observe formatted output
    Catch::cout() << 255;  // 255 in hex is "ff"
    EXPECT_EQ(sink.str(), "ff");
}
