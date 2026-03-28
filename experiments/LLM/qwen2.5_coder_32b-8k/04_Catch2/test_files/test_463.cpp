#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_debugger.hpp"



namespace Catch {



class ErrnoGuard {

public:

    ErrnoGuard() {}

};



TEST(isDebuggerActiveTest_463, DebuggerNotActive_463) {

    // Arrange

    std::ifstream in("/proc/self/status");

    std::string content = "TracerPid:\t0";

    testing::internal::CaptureStdout();

    std::ofstream ofs("/proc/self/status");

    ofs << content;

    ofs.close();



    // Act

    bool result = isDebuggerActive();



    // Assert

    EXPECT_FALSE(result);

}



TEST(isDebuggerActiveTest_463, DebuggerActive_463) {

    // Arrange

    std::ifstream in("/proc/self/status");

    std::string content = "TracerPid:\t1";

    testing::internal::CaptureStdout();

    std::ofstream ofs("/proc/self/status");

    ofs << content;

    ofs.close();



    // Act

    bool result = isDebuggerActive();



    // Assert

    EXPECT_TRUE(result);

}



TEST(isDebuggerActiveTest_463, FileNotFound_463) {

    // Arrange

    remove("/proc/self/status");



    // Act & Assert

    EXPECT_FALSE(isDebuggerActive());

}



TEST(isDebuggerActiveTest_463, InvalidFormat_463) {

    // Arrange

    std::string content = "InvalidLine:\t1";

    testing::internal::CaptureStdout();

    std::ofstream ofs("/proc/self/status");

    ofs << content;

    ofs.close();



    // Act

    bool result = isDebuggerActive();



    // Assert

    EXPECT_FALSE(result);

}



TEST(isDebuggerActiveTest_463, MultipleLines_463) {

    // Arrange

    std::string content = "Name:\tcatch_test\nTracerPid:\t1";

    testing::internal::CaptureStdout();

    std::ofstream ofs("/proc/self/status");

    ofs << content;

    ofs.close();



    // Act

    bool result = isDebuggerActive();



    // Assert

    EXPECT_TRUE(result);

}



}  // namespace Catch
