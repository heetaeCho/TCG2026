#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#include "browse.h"
#include "state.h"

// Since RunBrowsePython forks and execs, direct testing is dangerous.
// We test it in a forked child so the exec/exit doesn't kill our test process.

class RunBrowsePythonTest_167 : public ::testing::Test {
 protected:
  State state_;

  void SetUp() override {
    // Set up a minimal state
  }
};

// Test that RunBrowsePython can be called with a valid State and doesn't crash
// before fork (we run it in a child process to protect the test runner).
TEST_F(RunBrowsePythonTest_167, DoesNotCrashWithValidArgs_167) {
  // We fork here so that the internal fork+exec in RunBrowsePython
  // doesn't affect our test process.
  pid_t test_pid = fork();
  if (test_pid == 0) {
    // In child: call RunBrowsePython
    // It will fork again internally, and the parent side will try to execvp python.
    // Since python may or may not be available, we just want no crash/segfault.
    // We redirect stderr/stdout to /dev/null to keep test output clean.
    freopen("/dev/null", "w", stdout);
    freopen("/dev/null", "w", stderr);
    
    char* argv[] = { nullptr };
    RunBrowsePython(&state_, "ninja", "build.ninja", 0, argv);
    // If execvp fails, the function calls _exit(1), which is fine.
    _exit(0);
  }
  ASSERT_GT(test_pid, 0) << "Test fork failed";
  
  int status;
  waitpid(test_pid, &status, 0);
  // The child should have exited (either via _exit or exit)
  EXPECT_TRUE(WIFEXITED(status));
}

// Test that RunBrowsePython can be called with additional arguments
TEST_F(RunBrowsePythonTest_167, HandlesAdditionalArguments_167) {
  pid_t test_pid = fork();
  if (test_pid == 0) {
    freopen("/dev/null", "w", stdout);
    freopen("/dev/null", "w", stderr);
    
    char arg1[] = "target1";
    char arg2[] = "target2";
    char* argv[] = { arg1, arg2, nullptr };
    RunBrowsePython(&state_, "ninja", "build.ninja", 2, argv);
    _exit(0);
  }
  ASSERT_GT(test_pid, 0) << "Test fork failed";
  
  int status;
  waitpid(test_pid, &status, 0);
  EXPECT_TRUE(WIFEXITED(status));
}

// Test with empty ninja_command string
TEST_F(RunBrowsePythonTest_167, HandlesEmptyNinjaCommand_167) {
  pid_t test_pid = fork();
  if (test_pid == 0) {
    freopen("/dev/null", "w", stdout);
    freopen("/dev/null", "w", stderr);
    
    char* argv[] = { nullptr };
    RunBrowsePython(&state_, "", "build.ninja", 0, argv);
    _exit(0);
  }
  ASSERT_GT(test_pid, 0) << "Test fork failed";
  
  int status;
  waitpid(test_pid, &status, 0);
  EXPECT_TRUE(WIFEXITED(status));
}

// Test with empty input_file string
TEST_F(RunBrowsePythonTest_167, HandlesEmptyInputFile_167) {
  pid_t test_pid = fork();
  if (test_pid == 0) {
    freopen("/dev/null", "w", stdout);
    freopen("/dev/null", "w", stderr);
    
    char* argv[] = { nullptr };
    RunBrowsePython(&state_, "ninja", "", 0, argv);
    _exit(0);
  }
  ASSERT_GT(test_pid, 0) << "Test fork failed";
  
  int status;
  waitpid(test_pid, &status, 0);
  EXPECT_TRUE(WIFEXITED(status));
}

// Test with zero argc and empty argv
TEST_F(RunBrowsePythonTest_167, HandlesZeroArgc_167) {
  pid_t test_pid = fork();
  if (test_pid == 0) {
    freopen("/dev/null", "w", stdout);
    freopen("/dev/null", "w", stderr);
    
    char* argv[] = { nullptr };
    RunBrowsePython(&state_, "ninja", "build.ninja", 0, argv);
    _exit(0);
  }
  ASSERT_GT(test_pid, 0) << "Test fork failed";
  
  int status;
  waitpid(test_pid, &status, 0);
  EXPECT_TRUE(WIFEXITED(status));
}

// Test with a State that has some nodes
TEST_F(RunBrowsePythonTest_167, HandlesStateWithNodes_167) {
  state_.GetNode("foo.o", 0);
  state_.GetNode("bar.o", 0);
  
  pid_t test_pid = fork();
  if (test_pid == 0) {
    freopen("/dev/null", "w", stdout);
    freopen("/dev/null", "w", stderr);
    
    char arg1[] = "foo.o";
    char* argv[] = { arg1, nullptr };
    RunBrowsePython(&state_, "ninja", "build.ninja", 1, argv);
    _exit(0);
  }
  ASSERT_GT(test_pid, 0) << "Test fork failed";
  
  int status;
  waitpid(test_pid, &status, 0);
  EXPECT_TRUE(WIFEXITED(status));
}

// Test with many arguments
TEST_F(RunBrowsePythonTest_167, HandlesManyArguments_167) {
  pid_t test_pid = fork();
  if (test_pid == 0) {
    freopen("/dev/null", "w", stdout);
    freopen("/dev/null", "w", stderr);
    
    const int kNumArgs = 100;
    std::vector<std::string> arg_strings(kNumArgs);
    std::vector<char*> argv_vec(kNumArgs + 1);
    for (int i = 0; i < kNumArgs; i++) {
      arg_strings[i] = "arg" + std::to_string(i);
      argv_vec[i] = const_cast<char*>(arg_strings[i].c_str());
    }
    argv_vec[kNumArgs] = nullptr;
    
    RunBrowsePython(&state_, "ninja", "build.ninja", kNumArgs, argv_vec.data());
    _exit(0);
  }
  ASSERT_GT(test_pid, 0) << "Test fork failed";
  
  int status;
  waitpid(test_pid, &status, 0);
  EXPECT_TRUE(WIFEXITED(status));
}
