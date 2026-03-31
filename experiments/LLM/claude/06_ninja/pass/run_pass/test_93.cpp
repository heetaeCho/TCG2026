#include "gtest/gtest.h"
#include "subprocess.h"
#include <string>
#include <signal.h>

// Test fixture for SubprocessSet tests
class SubprocessSetTest_93 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Reset interrupted state before each test if possible
  }
  
  void TearDown() override {
  }
};

// Test that IsInterrupted returns false initially (before any signal)
TEST_F(SubprocessSetTest_93, IsInterruptedInitiallyFalse_93) {
  // Before any interruption signal, IsInterrupted should return false
  // Note: This assumes no prior test has set the interrupted flag
  // In a fresh process, interrupted_ should be 0
  EXPECT_FALSE(SubprocessSet::IsInterrupted());
}

// Test that SetInterruptedFlag causes IsInterrupted to return true
TEST_F(SubprocessSetTest_93, SetInterruptedFlagMakesIsInterruptedTrue_93) {
  SubprocessSet::SetInterruptedFlag(SIGINT);
  EXPECT_TRUE(SubprocessSet::IsInterrupted());
}

// Test that SetInterruptedFlag with SIGTERM also sets interrupted
TEST_F(SubprocessSetTest_93, SetInterruptedFlagWithSIGTERM_93) {
  SubprocessSet::SetInterruptedFlag(SIGTERM);
  EXPECT_TRUE(SubprocessSet::IsInterrupted());
}

// Test that SetInterruptedFlag with SIGHUP also sets interrupted
TEST_F(SubprocessSetTest_93, SetInterruptedFlagWithSIGHUP_93) {
  SubprocessSet::SetInterruptedFlag(SIGHUP);
  EXPECT_TRUE(SubprocessSet::IsInterrupted());
}

// Test SubprocessSet construction and destruction
TEST_F(SubprocessSetTest_93, ConstructAndDestruct_93) {
  SubprocessSet* subprocs = new SubprocessSet();
  ASSERT_NE(nullptr, subprocs);
  delete subprocs;
}

// Test NextFinished returns NULL when nothing has been run
TEST_F(SubprocessSetTest_93, NextFinishedReturnsNullWhenEmpty_93) {
  SubprocessSet subprocs;
  Subprocess* result = subprocs.NextFinished();
  EXPECT_EQ(nullptr, result);
}

// Test Add creates a subprocess for a simple command
TEST_F(SubprocessSetTest_93, AddSimpleCommand_93) {
  SubprocessSet subprocs;
  Subprocess* subproc = subprocs.Add("echo hello", false);
  ASSERT_NE(nullptr, subproc);
  subprocs.Clear();
}

// Test Add with use_console = true
TEST_F(SubprocessSetTest_93, AddWithConsole_93) {
  SubprocessSet subprocs;
  Subprocess* subproc = subprocs.Add("echo hello", true);
  ASSERT_NE(nullptr, subproc);
  subprocs.Clear();
}

// Test that DoWork completes a simple command
TEST_F(SubprocessSetTest_93, DoWorkCompletesSimpleCommand_93) {
  SubprocessSet subprocs;
  Subprocess* subproc = subprocs.Add("/bin/echo hello", false);
  ASSERT_NE(nullptr, subproc);
  
  while (!subprocs.DoWork()) {
    // Keep doing work until all subprocesses finish
  }
  
  Subprocess* finished = subprocs.NextFinished();
  EXPECT_NE(nullptr, finished);
  subprocs.Clear();
}

// Test that a successful command has ExitSuccess status
TEST_F(SubprocessSetTest_93, SuccessfulCommandExitStatus_93) {
  SubprocessSet subprocs;
  Subprocess* subproc = subprocs.Add("/bin/echo hello", false);
  ASSERT_NE(nullptr, subproc);
  
  while (!subprocs.DoWork()) {
  }
  
  Subprocess* finished = subprocs.NextFinished();
  ASSERT_NE(nullptr, finished);
  EXPECT_EQ(ExitSuccess, finished->Finish());
  subprocs.Clear();
}

// Test that a failed command has ExitFailure status
TEST_F(SubprocessSetTest_93, FailedCommandExitStatus_93) {
  SubprocessSet subprocs;
  Subprocess* subproc = subprocs.Add("/bin/false", false);
  ASSERT_NE(nullptr, subproc);
  
  while (!subprocs.DoWork()) {
  }
  
  Subprocess* finished = subprocs.NextFinished();
  ASSERT_NE(nullptr, finished);
  EXPECT_EQ(ExitFailure, finished->Finish());
  subprocs.Clear();
}

// Test that output from a command is captured
TEST_F(SubprocessSetTest_93, CommandOutputCaptured_93) {
  SubprocessSet subprocs;
  Subprocess* subproc = subprocs.Add("/bin/echo hello", false);
  ASSERT_NE(nullptr, subproc);
  
  while (!subprocs.DoWork()) {
  }
  
  Subprocess* finished = subprocs.NextFinished();
  ASSERT_NE(nullptr, finished);
  EXPECT_EQ("hello\n", finished->GetOutput());
  subprocs.Clear();
}

// Test multiple subprocesses
TEST_F(SubprocessSetTest_93, MultipleSubprocesses_93) {
  SubprocessSet subprocs;
  Subprocess* subproc1 = subprocs.Add("/bin/echo one", false);
  Subprocess* subproc2 = subprocs.Add("/bin/echo two", false);
  ASSERT_NE(nullptr, subproc1);
  ASSERT_NE(nullptr, subproc2);
  
  while (!subprocs.DoWork()) {
  }
  
  Subprocess* finished1 = subprocs.NextFinished();
  ASSERT_NE(nullptr, finished1);
  Subprocess* finished2 = subprocs.NextFinished();
  ASSERT_NE(nullptr, finished2);
  
  // After two finishes, there should be no more
  Subprocess* finished3 = subprocs.NextFinished();
  EXPECT_EQ(nullptr, finished3);
  
  subprocs.Clear();
}

// Test Clear empties running and finished queues
TEST_F(SubprocessSetTest_93, ClearEmptiesQueues_93) {
  SubprocessSet subprocs;
  subprocs.Add("/bin/echo test", false);
  subprocs.Clear();
  
  Subprocess* finished = subprocs.NextFinished();
  EXPECT_EQ(nullptr, finished);
}

// Test that an empty command can be added
TEST_F(SubprocessSetTest_93, EmptyCommand_93) {
  SubprocessSet subprocs;
  // An empty command might still create a subprocess (shell will handle it)
  Subprocess* subproc = subprocs.Add("", false);
  ASSERT_NE(nullptr, subproc);
  subprocs.Clear();
}

// Test command with no output
TEST_F(SubprocessSetTest_93, CommandWithNoOutput_93) {
  SubprocessSet subprocs;
  Subprocess* subproc = subprocs.Add("/bin/true", false);
  ASSERT_NE(nullptr, subproc);
  
  while (!subprocs.DoWork()) {
  }
  
  Subprocess* finished = subprocs.NextFinished();
  ASSERT_NE(nullptr, finished);
  EXPECT_EQ("", finished->GetOutput());
  EXPECT_EQ(ExitSuccess, finished->Finish());
  subprocs.Clear();
}
