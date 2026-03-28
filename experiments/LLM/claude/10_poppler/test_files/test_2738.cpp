#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <string>
#include "parseargs.h"

// Helper to capture stderr output
class StderrCapture {
public:
    void start() {
        fflush(stderr);
        old_stderr_ = dup(fileno(stderr));
        tmpfile_ = std::tmpfile();
        dup2(fileno(tmpfile_), fileno(stderr));
    }
    std::string stop() {
        fflush(stderr);
        dup2(old_stderr_, fileno(stderr));
        close(old_stderr_);
        rewind(tmpfile_);
        std::string result;
        char buf[1024];
        while (fgets(buf, sizeof(buf), tmpfile_)) {
            result += buf;
        }
        fclose(tmpfile_);
        return result;
    }
private:
    int old_stderr_;
    FILE* tmpfile_;
};

class PrintUsageTest_2738 : public ::testing::Test {
protected:
    StderrCapture capture;
};

TEST_F(PrintUsageTest_2738, EmptyArgsNoOtherArgs_2738) {
    ArgDesc args[] = {
        { nullptr, argFlag, nullptr, nullptr }
    };
    capture.start();
    printUsage("myprogram", nullptr, args);
    std::string output = capture.stop();
    
    EXPECT_NE(output.find("Usage: myprogram [options]"), std::string::npos);
    // Should NOT contain extra otherArgs
    EXPECT_EQ(output.find("Usage: myprogram [options] "), std::string::npos);
}

TEST_F(PrintUsageTest_2738, EmptyArgsWithOtherArgs_2738) {
    ArgDesc args[] = {
        { nullptr, argFlag, nullptr, nullptr }
    };
    capture.start();
    printUsage("myprogram", "<input-file>", args);
    std::string output = capture.stop();
    
    EXPECT_NE(output.find("Usage: myprogram [options] <input-file>"), std::string::npos);
}

TEST_F(PrintUsageTest_2738, SingleFlagArg_2738) {
    bool flagVal = false;
    ArgDesc args[] = {
        { "-verbose", argFlag, &flagVal, "enable verbose mode" },
        { nullptr, argFlag, nullptr, nullptr }
    };
    capture.start();
    printUsage("tool", nullptr, args);
    std::string output = capture.stop();
    
    EXPECT_NE(output.find("-verbose"), std::string::npos);
    EXPECT_NE(output.find("enable verbose mode"), std::string::npos);
    // argFlag should not have a type annotation like <int>
    EXPECT_EQ(output.find("<int>"), std::string::npos);
    EXPECT_EQ(output.find("<fp>"), std::string::npos);
    EXPECT_EQ(output.find("<string>"), std::string::npos);
}

TEST_F(PrintUsageTest_2738, IntArgShowsIntType_2738) {
    int intVal = 0;
    ArgDesc args[] = {
        { "-count", argInt, &intVal, "number of items" },
        { nullptr, argFlag, nullptr, nullptr }
    };
    capture.start();
    printUsage("tool", nullptr, args);
    std::string output = capture.stop();
    
    EXPECT_NE(output.find("-count"), std::string::npos);
    EXPECT_NE(output.find("<int>"), std::string::npos);
    EXPECT_NE(output.find("number of items"), std::string::npos);
}

TEST_F(PrintUsageTest_2738, FPArgShowsFpType_2738) {
    double fpVal = 0.0;
    ArgDesc args[] = {
        { "-scale", argFP, &fpVal, "scale factor" },
        { nullptr, argFlag, nullptr, nullptr }
    };
    capture.start();
    printUsage("tool", nullptr, args);
    std::string output = capture.stop();
    
    EXPECT_NE(output.find("-scale"), std::string::npos);
    EXPECT_NE(output.find("<fp>"), std::string::npos);
    EXPECT_NE(output.find("scale factor"), std::string::npos);
}

TEST_F(PrintUsageTest_2738, StringArgShowsStringType_2738) {
    char strVal[256] = "";
    ArgDesc args[] = {
        { "-output", argString, strVal, "output file" },
        { nullptr, argFlag, nullptr, nullptr }
    };
    capture.start();
    printUsage("tool", nullptr, args);
    std::string output = capture.stop();
    
    EXPECT_NE(output.find("-output"), std::string::npos);
    EXPECT_NE(output.find("<string>"), std::string::npos);
    EXPECT_NE(output.find("output file"), std::string::npos);
}

TEST_F(PrintUsageTest_2738, GooStringArgShowsStringType_2738) {
    ArgDesc args[] = {
        { "-name", argGooString, nullptr, "a name" },
        { nullptr, argFlag, nullptr, nullptr }
    };
    capture.start();
    printUsage("tool", nullptr, args);
    std::string output = capture.stop();
    
    EXPECT_NE(output.find("-name"), std::string::npos);
    EXPECT_NE(output.find("<string>"), std::string::npos);
}

TEST_F(PrintUsageTest_2738, MultipleArgs_2738) {
    int intVal = 0;
    double fpVal = 0.0;
    bool flagVal = false;
    char strVal[256] = "";
    ArgDesc args[] = {
        { "-n", argInt, &intVal, "count" },
        { "-scale", argFP, &fpVal, "scale" },
        { "-v", argFlag, &flagVal, "verbose" },
        { "-out", argString, strVal, "output" },
        { nullptr, argFlag, nullptr, nullptr }
    };
    capture.start();
    printUsage("multi", "file1 file2", args);
    std::string output = capture.stop();
    
    EXPECT_NE(output.find("Usage: multi [options] file1 file2"), std::string::npos);
    EXPECT_NE(output.find("-n"), std::string::npos);
    EXPECT_NE(output.find("-scale"), std::string::npos);
    EXPECT_NE(output.find("-v"), std::string::npos);
    EXPECT_NE(output.find("-out"), std::string::npos);
}

TEST_F(PrintUsageTest_2738, NullUsageString_2738) {
    bool flagVal = false;
    ArgDesc args[] = {
        { "-q", argFlag, &flagVal, nullptr },
        { nullptr, argFlag, nullptr, nullptr }
    };
    capture.start();
    printUsage("tool", nullptr, args);
    std::string output = capture.stop();
    
    EXPECT_NE(output.find("-q"), std::string::npos);
    // No colon should appear since usage is null
    // The line for -q should not contain ": "
    auto pos = output.find("-q");
    auto lineEnd = output.find('\n', pos);
    std::string line = output.substr(pos, lineEnd - pos);
    EXPECT_EQ(line.find(": "), std::string::npos);
}

TEST_F(PrintUsageTest_2738, IntDummyShowsIntType_2738) {
    ArgDesc args[] = {
        { "-dummy", argIntDummy, nullptr, "dummy int" },
        { nullptr, argFlag, nullptr, nullptr }
    };
    capture.start();
    printUsage("tool", nullptr, args);
    std::string output = capture.stop();
    
    EXPECT_NE(output.find("<int>"), std::string::npos);
}

TEST_F(PrintUsageTest_2738, FPDummyShowsFpType_2738) {
    ArgDesc args[] = {
        { "-dummy", argFPDummy, nullptr, "dummy fp" },
        { nullptr, argFlag, nullptr, nullptr }
    };
    capture.start();
    printUsage("tool", nullptr, args);
    std::string output = capture.stop();
    
    EXPECT_NE(output.find("<fp>"), std::string::npos);
}

TEST_F(PrintUsageTest_2738, StringDummyShowsStringType_2738) {
    ArgDesc args[] = {
        { "-dummy", argStringDummy, nullptr, "dummy string" },
        { nullptr, argFlag, nullptr, nullptr }
    };
    capture.start();
    printUsage("tool", nullptr, args);
    std::string output = capture.stop();
    
    EXPECT_NE(output.find("<string>"), std::string::npos);
}

TEST_F(PrintUsageTest_2738, FlagDummyShowsNoType_2738) {
    ArgDesc args[] = {
        { "-dummy", argFlagDummy, nullptr, "dummy flag" },
        { nullptr, argFlag, nullptr, nullptr }
    };
    capture.start();
    printUsage("tool", nullptr, args);
    std::string output = capture.stop();
    
    EXPECT_EQ(output.find("<int>"), std::string::npos);
    EXPECT_EQ(output.find("<fp>"), std::string::npos);
    EXPECT_EQ(output.find("<string>"), std::string::npos);
    EXPECT_NE(output.find("dummy flag"), std::string::npos);
}

TEST_F(PrintUsageTest_2738, ProgramNameAppearsInUsageLine_2738) {
    ArgDesc args[] = {
        { nullptr, argFlag, nullptr, nullptr }
    };
    capture.start();
    printUsage("my-special-program", nullptr, args);
    std::string output = capture.stop();
    
    EXPECT_NE(output.find("my-special-program"), std::string::npos);
}

TEST_F(PrintUsageTest_2738, LongArgNameAlignment_2738) {
    bool f1 = false, f2 = false;
    ArgDesc args[] = {
        { "-a", argFlag, &f1, "short" },
        { "-very-long-argument-name", argFlag, &f2, "long" },
        { nullptr, argFlag, nullptr, nullptr }
    };
    capture.start();
    printUsage("tool", nullptr, args);
    std::string output = capture.stop();
    
    // Both args should be present
    EXPECT_NE(output.find("-a"), std::string::npos);
    EXPECT_NE(output.find("-very-long-argument-name"), std::string::npos);
    EXPECT_NE(output.find(": short"), std::string::npos);
    EXPECT_NE(output.find(": long"), std::string::npos);
}
