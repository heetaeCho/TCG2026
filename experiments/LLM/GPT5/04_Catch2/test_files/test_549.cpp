// File: catch_stdstreams_tests_549.cpp

#include <gtest/gtest.h>
#include <ostream>
#include <sstream>
#include <iomanip>  // for std::endl, std::flush, manipulators
#include <type_traits>

// Forward declaration of the function under test.
namespace Catch {
    std::ostream& clog();
}

// A tiny RAII helper to temporarily redirect an ostream's rdbuf.
class StreamRedirect {
public:
    explicit StreamRedirect(std::ostream& os, std::streambuf* newBuf)
        : os_(os), oldBuf_(os.rdbuf(newBuf)) {}
    ~StreamRedirect() { os_.rdbuf(oldBuf_); }
    StreamRedirect(const StreamRedirect&) = delete;
    StreamRedirect& operator=(const StreamRedirect&) = delete;
private:
    std::ostream&   os_;
    std::streambuf* oldBuf_;
};

class CatchStdStreamsTest_549 : public ::testing::Test {};

// Verifies that Catch::clog() returns a reference to the same object as std::clog.
TEST_F(CatchStdStreamsTest_549, ReturnsStdClogReference_549) {
    std::ostream* catch_clog_ptr = std::addressof(Catch::clog());
    std::ostream* std_clog_ptr   = std::addressof(std::clog);

    // They should refer to the exact same stream object.
    EXPECT_EQ(catch_clog_ptr, std_clog_ptr);
}

// Writing via Catch::clog() should go to std::clog's buffer (observable via redirection).
TEST_F(CatchStdStreamsTest_549, WritesAreCapturedViaStdClogRedirection_549) {
    std::ostringstream capture;
    StreamRedirect redirect(std::clog, capture.rdbuf());

    Catch::clog() << "hello clog" << std::endl;

    EXPECT_EQ(capture.str(), std::string("hello clog\n"));
}

// Standard manipulators (like std::endl / std::flush) should be supported and affect output.
TEST_F(CatchStdStreamsTest_549, SupportsStandardManipulatorsAndFlush_549) {
    std::ostringstream capture;
    StreamRedirect redirect(std::clog, capture.rdbuf());

    Catch::clog() << "line1" << std::endl;
    Catch::clog() << "line2";
    Catch::clog() << std::flush;

    EXPECT_EQ(capture.str(), std::string("line1\nline2"));
}

// Boundary case: writing an empty string should not change the buffer contents beyond a flush.
TEST_F(CatchStdStreamsTest_549, WritingEmptyStringHasNoEffectBeyondFlush_549) {
    std::ostringstream capture;
    StreamRedirect redirect(std::clog, capture.rdbuf());

    Catch::clog() << "" << std::flush;

    EXPECT_TRUE(capture.str().empty());
}
