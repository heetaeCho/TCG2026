#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "state.h"

#include <unistd.h>

#include <sys/types.h>



using namespace ::testing;



extern void RunBrowsePython(State* state, const char* ninja_command, const char* input_file, int argc, char* argv[]);



class RunBrowsePythonTest_167 : public Test {

protected:

    State state;

};



TEST_F(RunBrowsePythonTest_167, NormalOperationWithArgs_167) {

    const char* ninja_command = "ninja";

    const char* input_file = "build.ninja";

    char* argv[] = {"--arg1", "--arg2"};

    int argc = 2;



    EXPECT_EXIT(RunBrowsePython(&state, ninja_command, input_file, argc, argv),

                ExitedWithCode(0), "");

}



TEST_F(RunBrowsePythonTest_167, NormalOperationWithoutArgs_167) {

    const char* ninja_command = "ninja";

    const char* input_file = "build.ninja";

    char* argv[] = {};

    int argc = 0;



    EXPECT_EXIT(RunBrowsePython(&state, ninja_command, input_file, argc, argv),

                ExitedWithCode(0), "");

}



TEST_F(RunBrowsePythonTest_167, PipeCreationFailure_167) {

    // Mock pipe() to return -1

    testing::internal::CaptureStderr();

    EXPECT_EXIT({

        int (*real_pipe)(int[2]) = pipe;

        *reinterpret_cast<int (**)(int[2])>(dlsym(RTLD_NEXT, "pipe")) = [](int pipefd[2]) -> int {

            return -1;

        };

        RunBrowsePython(&state, "ninja", "build.ninja", 0, nullptr);

    }, ExitedWithCode(1), "ninja: pipe");

}



TEST_F(RunBrowsePythonTest_167, ForkFailure_167) {

    // Mock fork() to return -1

    testing::internal::CaptureStderr();

    EXPECT_EXIT({

        pid_t (*real_fork)() = fork;

        *reinterpret_cast<pid_t (**)(void)>(dlsym(RTLD_NEXT, "fork")) = []() -> pid_t {

            return -1;

        };

        RunBrowsePython(&state, "ninja", "build.ninja", 0, nullptr);

    }, ExitedWithCode(1), "ninja: fork");

}



TEST_F(RunBrowsePythonTest_167, WriteFailure_167) {

    // Mock write() to return less than kBrowsePyLength

    testing::internal::CaptureStderr();

    EXPECT_EXIT({

        ssize_t (*real_write)(int, const void*, size_t) = write;

        *reinterpret_cast<ssize_t (**)(int, const void*, size_t)>(dlsym(RTLD_NEXT, "write")) = [](int fd, const void* buf, size_t count) -> ssize_t {

            return -1;

        };

        RunBrowsePython(&state, "ninja", "build.ninja", 0, nullptr);

    }, ExitedWithCode(1), "ninja: write");

}



TEST_F(RunBrowsePythonTest_167, ExecvpFailure_167) {

    // Mock execvp() to fail with ENOENT

    testing::internal::CaptureStderr();

    EXPECT_EXIT({

        int (*real_execvp)(const char*, char* const[]) = execvp;

        *reinterpret_cast<int (**)(const char*, char* const[])>(dlsym(RTLD_NEXT, "execvp")) = [](const char* file, char* const argv[]) -> int {

            errno = ENOENT;

            return -1;

        };

        RunBrowsePython(&state, "ninja", "build.ninja", 0, nullptr);

    }, ExitedWithCode(1), "ninja: python is required for the browse tool");

}



TEST_F(RunBrowsePythonTest_167, ExecvpGeneralFailure_167) {

    // Mock execvp() to fail with some other error

    testing::internal::CaptureStderr();

    EXPECT_EXIT({

        int (*real_execvp)(const char*, char* const[]) = execvp;

        *reinterpret_cast<int (**)(const char*, char* const[])>(dlsym(RTLD_NEXT, "execvp")) = [](const char* file, char* const argv[]) -> int {

            errno = EACCES;

            return -1;

        };

        RunBrowsePython(&state, "ninja", "build.ninja", 0, nullptr);

    }, ExitedWithCode(1), "ninja: execvp");

}
