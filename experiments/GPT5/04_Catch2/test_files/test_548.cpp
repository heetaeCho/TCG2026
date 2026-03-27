// File: catch_stdstreams_test_548.cpp
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

// Declaration under test (normally you'd include the real header)
namespace Catch { std::ostream& cerr(); }

// Test fixture that safely redirects std::cerr for the duration of a test.
class CerrStreamTest_548 : public ::testing::Test {
protected:
    std::ostringstream capture_;
    std::streambuf* oldBuf_ = nullptr;

    // Also save & restore formatting flags to avoid cross-test leakage
    std::ios_base::fmtflags oldFlags_{};
    std::streamsize oldPrecision_{};
    char oldFill_{};

    void SetUp() override {
        oldBuf_ = std::cerr.rdbuf(capture_.rdbuf());
        oldFlags_ = std::cerr.flags();
        oldPrecision_ = std::cerr.precision();
        oldFill_ = std::cerr.fill();
    }

    void TearDown() override {
        std::cerr.flags(oldFlags_);
        std::cerr.precision(oldPrecision_);
        std::cerr.fill(oldFill_);
        std::cerr.rdbuf(oldBuf_);
    }
};

// Verifies that Catch::cerr() returns the same stream object as std::cerr.
TEST(CerrStreamTest_548, ReturnsStdCerrReference_548) {
    // Compare addresses of the stream objects (references) to ensure identity.
    std::ostream* catchCerrPtr = &Catch::cerr();
    std::ostream* stdCerrPtr   = &std::cerr;
    EXPECT_EQ(catchCerrPtr, stdCerrPtr);
}

// Writing via Catch::cerr() must be observable on std::cerr.
TEST_F(CerrStreamTest_548, WritesGoToStdCerr_548) {
    Catch::cerr() << "hello, cerr";
    EXPECT_EQ(capture_.str(), "hello, cerr");
}

// The stream should support standard manipulators (e.g., std::endl).
TEST_F(CerrStreamTest_548, SupportsStreamManipulators_548) {
    Catch::cerr() << 42 << std::endl; // std::endl inserts '\n' and flushes
    EXPECT_EQ(capture_.str(), "42\n");
}

// Formatting flags applied through the returned stream should affect output.
TEST_F(CerrStreamTest_548, FormattingFlagsAffectOutput_548) {
    // Change basefield to hex and verify formatted output.
    Catch::cerr().setf(std::ios::hex, std::ios::basefield);
    Catch::cerr() << 255;

    // Lowercase hex is the default for iostreams unless std::uppercase is set.
    EXPECT_EQ(capture_.str(), "ff");
}

// Writing an empty string should not change the stream content.
TEST_F(CerrStreamTest_548, WritingEmptyStringProducesNoOutput_548) {
    Catch::cerr() << "";
    EXPECT_TRUE(capture_.str().empty());
}

// Multiple calls to Catch::cerr() should consistently return the same object.
TEST_F(CerrStreamTest_548, ReturnsStableReferenceAcrossCalls_548) {
    std::ostream* p1 = &Catch::cerr();
    std::ostream* p2 = &Catch::cerr();
    EXPECT_EQ(p1, p2);
}

