// File: make_stream_tests_651.cpp

#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <typeinfo>
#include <filesystem>

// Prefer the public/interface header that declares Catch::makeStream.
// If your project exposes a different header for makeStream, include it instead.
#include "catch2/internal/catch_istream.hpp"  // Adjust include path if needed

namespace fs = std::filesystem;

namespace {

// Small helper to create an empty temp file and return its path.
std::string CreateTempFile_651() {
    fs::path dir = fs::temp_directory_path();
    fs::path file = dir / fs::path("catch_make_stream_651.tmp");
    // Ensure uniqueness if the name exists
    int suffix = 0;
    while (fs::exists(file)) {
        file = dir / fs::path("catch_make_stream_651_" + std::to_string(++suffix) + ".tmp");
    }
    std::ofstream ofs(file.string(), std::ios::out | std::ios::trunc);
    ofs << ""; // create the file
    ofs.close();
    return file.string();
}

// Helper to get RTTI name safely
std::string TypeNameOf(const Catch::Detail::unique_ptr<Catch::IStream>& p) {
    return p ? std::string(typeid(*p).name()) : std::string();
}

} // namespace

// Normal: empty filename maps to a cout-backed stream (same type as %stdout)
TEST(MakeStreamTest_651, EmptyMapsToStdoutType_651) {
    auto a = Catch::makeStream("");         // empty
    auto b = Catch::makeStream("%stdout");  // explicit stdout

    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);
    EXPECT_EQ(TypeNameOf(a), TypeNameOf(b));
}

// Boundary: "-" also maps to stdout type
TEST(MakeStreamTest_651, DashMapsToStdoutType_651) {
    auto a = Catch::makeStream("-");        // dash
    auto b = Catch::makeStream("%stdout");  // explicit stdout

    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);
    EXPECT_EQ(TypeNameOf(a), TypeNameOf(b));
}

// Normal: %stderr returns a valid stream and has a different runtime type than %stdout
TEST(MakeStreamTest_651, PercentStderrIsDifferentFromStdout_651) {
    auto stderrStream = Catch::makeStream("%stderr");
    auto stdoutStream = Catch::makeStream("%stdout");

    ASSERT_NE(stderrStream, nullptr);
    ASSERT_NE(stdoutStream, nullptr);
    EXPECT_NE(TypeNameOf(stderrStream), TypeNameOf(stdoutStream));
}

// Normal: %debug returns a valid stream and has a different runtime type than %stdout
TEST(MakeStreamTest_651, PercentDebugIsDifferentFromStdout_651) {
    auto debugStream = Catch::makeStream("%debug");
    auto stdoutStream = Catch::makeStream("%stdout");

    ASSERT_NE(debugStream, nullptr);
    ASSERT_NE(stdoutStream, nullptr);
    EXPECT_NE(TypeNameOf(debugStream), TypeNameOf(stdoutStream));
}

// Error case: unknown %specifier throws (observable via exception)
TEST(MakeStreamTest_651, UnknownPercentSpecifierThrows_651) {
    // The exact exception type is implementation detail; verify that *an* exception is thrown.
    EXPECT_ANY_THROW({
        auto bad = Catch::makeStream("%not_a_real_stream");
        (void)bad;
    });
}

// Normal: regular filename returns a valid stream; its type should differ from %stdout
TEST(MakeStreamTest_651, RegularFilenameReturnsFileBackedStream_651) {
    const std::string path = CreateTempFile_651();
    auto fileStream  = Catch::makeStream(path);
    auto stdoutStream = Catch::makeStream("%stdout");

    ASSERT_NE(fileStream, nullptr);
    ASSERT_NE(stdoutStream, nullptr);

    // File stream should not have the same runtime type as stdout stream
    EXPECT_NE(TypeNameOf(fileStream), TypeNameOf(stdoutStream));

    // Cleanup
    std::error_code ec;
    fs::remove(path, ec); // best-effort cleanup
}

