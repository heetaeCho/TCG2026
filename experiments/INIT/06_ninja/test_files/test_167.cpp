// File: ./TestProjects/ninja/tests/browse_test_167.cc

#include <gtest/gtest.h>
#include <errno.h>
#include <string>
#include <vector>

// We are going to intercept the OS calls used by RunBrowsePython by
// redefining them *only* for the translation unit that includes browse.cc.

// Forward declarations of mock syscall implementations.
int     mock_pipe(int pipefd[2]);
pid_t   mock_fork();
int     mock_dup2(int oldfd, int newfd);
int     mock_execvp(const char* file, char* const* argv);
ssize_t mock_write(int fd, const void* buf, size_t count);
int     mock_close(int fd);
void    mock_perror(const char* s);
void    mock__exit(int status);
void    mock_exit(int status);

// Redirect system calls inside browse.cc to our mocks.
#define pipe   mock_pipe
#define fork   mock_fork
#define dup2   mock_dup2
#define execvp mock_execvp
#define write  mock_write
#define close  mock_close
#define perror mock_perror
#define _exit  mock__exit
#define exit   mock_exit

// Include the implementation under test so that it uses the mocked
// functions above.
#include "../src/browse.cc"

// Stop redirecting for the rest of this file.
#undef pipe
#undef fork
#undef dup2
#undef execvp
#undef write
#undef close
#undef perror
#undef _exit
#undef exit

// ---------------------------------------------------------------------
// Global recording of calls made by RunBrowsePython via our mocks.
// ---------------------------------------------------------------------

namespace {

struct SyscallRecorder {
  // Configuration for next calls.
  int   pipe_return          = 0;
  pid_t fork_return          = 1;   // >0 -> parent branch by default
  int   dup2_return          = 0;
  int   execvp_return        = -1;
  int   execvp_errno         = ENOENT;
  ssize_t write_return       = -1;  // default "error" -> triggers perror
  int   close_return         = 0;

  // Call counts.
  int pipe_called   = 0;
  int fork_called   = 0;
  int dup2_called   = 0;
  int execvp_called = 0;
  int write_called  = 0;
  int close_called  = 0;
  int perror_called = 0;
  int exit_called   = 0;
  int _exit_called  = 0;

  // Last / collected arguments.
  int pipefd_last[2] = {-1, -1};

  int dup2_oldfd = -1;
  int dup2_newfd = -1;

  std::string last_perror_msg;

  int last_exit_code  = -1;
  int last__exit_code = -1;

  std::vector<int>        closed_fds;
  std::string             execvp_program;
  std::vector<std::string> execvp_argv;

  int    last_write_fd   = -1;
  size_t last_write_size = 0;
  const void* last_write_buf = nullptr;

  void Reset() {
    pipe_return    = 0;
    fork_return    = 1;
    dup2_return    = 0;
    execvp_return  = -1;
    execvp_errno   = ENOENT;
    write_return   = -1;
    close_return   = 0;

    pipe_called   = 0;
    fork_called   = 0;
    dup2_called   = 0;
    execvp_called = 0;
    write_called  = 0;
    close_called  = 0;
    perror_called = 0;
    exit_called   = 0;
    _exit_called  = 0;

    pipefd_last[0] = pipefd_last[1] = -1;
    dup2_oldfd = dup2_newfd = -1;

    last_perror_msg.clear();

    last_exit_code  = -1;
    last__exit_code = -1;

    closed_fds.clear();
    execvp_program.clear();
    execvp_argv.clear();

    last_write_fd   = -1;
    last_write_size = 0;
    last_write_buf  = nullptr;
  }
};

SyscallRecorder g_sys;

}  // namespace

// ---------------------------------------------------------------------
// Mock implementations used by the included browse.cc
// ---------------------------------------------------------------------

int mock_pipe(int pipefd[2]) {
  ++g_sys.pipe_called;
  // Use deterministic fds so tests can assert on them.
  pipefd[0] = 10;
  pipefd[1] = 11;
  g_sys.pipefd_last[0] = pipefd[0];
  g_sys.pipefd_last[1] = pipefd[1];
  return g_sys.pipe_return;
}

pid_t mock_fork() {
  ++g_sys.fork_called;
  return g_sys.fork_return;
}

int mock_dup2(int oldfd, int newfd) {
  ++g_sys.dup2_called;
  g_sys.dup2_oldfd = oldfd;
  g_sys.dup2_newfd = newfd;
  return g_sys.dup2_return;
}

int mock_execvp(const char* file, char* const* argv) {
  ++g_sys.execvp_called;
  g_sys.execvp_program = file ? file : "";

  g_sys.execvp_argv.clear();
  if (argv) {
    for (int i = 0; argv[i] != nullptr; ++i) {
      g_sys.execvp_argv.emplace_back(argv[i]);
    }
  }

  errno = g_sys.execvp_errno;
  return g_sys.execvp_return;
}

ssize_t mock_write(int fd, const void* buf, size_t count) {
  ++g_sys.write_called;
  g_sys.last_write_fd   = fd;
  g_sys.last_write_buf  = buf;
  g_sys.last_write_size = count;
  return g_sys.write_return;
}

int mock_close(int fd) {
  ++g_sys.close_called;
  g_sys.closed_fds.push_back(fd);
  return g_sys.close_return;
}

void mock_perror(const char* s) {
  ++g_sys.perror_called;
  g_sys.last_perror_msg = s ? s : "";
}

void mock__exit(int status) {
  ++g_sys._exit_called;
  g_sys.last__exit_code = status;
  // Do NOT terminate the process; just return so tests can continue.
}

void mock_exit(int status) {
  ++g_sys.exit_called;
  g_sys.last_exit_code = status;
  // Do NOT terminate the process; just return so tests can continue.
}

// ---------------------------------------------------------------------
// Test fixture
// ---------------------------------------------------------------------

class RunBrowsePythonTest_167 : public ::testing::Test {
 protected:
  void SetUp() override { g_sys.Reset(); }
};

// ---------------------------------------------------------------------
// Tests
// ---------------------------------------------------------------------

// pipe() failure should call perror("ninja: pipe") and return without
// calling fork or other syscalls.
TEST_F(RunBrowsePythonTest_167, PipeFailureCallsPerrorAndReturns_167) {
  g_sys.pipe_return = -1;  // simulate pipe() error

  RunBrowsePython(nullptr, "ninja_cmd", "build.ninja", 0, nullptr);

  EXPECT_EQ(1, g_sys.pipe_called);
  EXPECT_EQ(0, g_sys.fork_called);
  EXPECT_EQ(1, g_sys.perror_called);
  EXPECT_EQ("ninja: pipe", g_sys.last_perror_msg);
  EXPECT_EQ(0, g_sys._exit_called);
  EXPECT_EQ(0, g_sys.exit_called);
}

// fork() failure should call perror("ninja: fork") and return without
// trying dup2/execvp/write.
TEST_F(RunBrowsePythonTest_167, ForkFailureCallsPerrorAndReturns_167) {
  g_sys.pipe_return = 0;   // success
  g_sys.fork_return = -1;  // simulate fork() failure

  RunBrowsePython(nullptr, "ninja_cmd", "build.ninja", 0, nullptr);

  EXPECT_EQ(1, g_sys.pipe_called);
  EXPECT_EQ(1, g_sys.fork_called);
  EXPECT_EQ(1, g_sys.perror_called);
  EXPECT_EQ("ninja: fork", g_sys.last_perror_msg);
  EXPECT_EQ(0, g_sys.dup2_called);
  EXPECT_EQ(0, g_sys.execvp_called);
  EXPECT_EQ(0, g_sys.write_called);
  EXPECT_EQ(0, g_sys.exit_called);
  EXPECT_EQ(0, g_sys._exit_called);
}

// In the parent branch, dup2() failure should call perror("ninja: dup2")
// and then _exit(1) without calling execvp.
TEST_F(RunBrowsePythonTest_167, ParentDup2FailureCallsPerrorAndExits_167) {
  g_sys.pipe_return = 0;
  g_sys.fork_return = 1234;   // parent branch
  g_sys.dup2_return = -1;     // fail dup2

  RunBrowsePython(nullptr, "ninja_cmd", "build.ninja", 0, nullptr);

  ASSERT_EQ(1, g_sys.pipe_called);
  ASSERT_EQ(1, g_sys.fork_called);
  EXPECT_EQ(1, g_sys.close_called);          // close write end
  ASSERT_FALSE(g_sys.closed_fds.empty());
  EXPECT_EQ(11, g_sys.closed_fds[0]);        // write-end from mock_pipe

  EXPECT_EQ(1, g_sys.dup2_called);
  EXPECT_EQ(10, g_sys.dup2_oldfd);           // read-end
  EXPECT_EQ(0,  g_sys.dup2_newfd);           // stdin

  EXPECT_EQ(1, g_sys.perror_called);
  EXPECT_EQ("ninja: dup2", g_sys.last_perror_msg);

  EXPECT_EQ(0, g_sys.execvp_called);
  EXPECT_EQ(1, g_sys._exit_called);
  EXPECT_EQ(1, g_sys.last__exit_code);
}

// In the parent branch, on successful dup2() and execvp() failure with
// errno == ENOENT, RunBrowsePython should NOT call perror("ninja: execvp")
// (it prints a message via printf instead) and should still call _exit(1).
TEST_F(RunBrowsePythonTest_167, ParentExecvpEnoentDoesNotUsePerror_167) {
  g_sys.pipe_return   = 0;
  g_sys.fork_return   = 1234;     // parent
  g_sys.dup2_return   = 0;        // success
  g_sys.execvp_return = -1;       // fail
  g_sys.execvp_errno  = ENOENT;   // specific errno

  const char* ninja_cmd = "ninja_binary";
  const char* input     = "build.ninja";
  char* argv[] = { const_cast<char*>("-t"),
                   const_cast<char*>("targets") };

  RunBrowsePython(nullptr, ninja_cmd, input, 2, argv);

  EXPECT_EQ(1, g_sys.execvp_called);
  EXPECT_EQ(1, g_sys._exit_called);

  // No perror at all in this scenario: not pipe/fork/dup2 and execvp uses printf.
  EXPECT_EQ(0, g_sys.perror_called);

  // Check that the command vector is built with the expected trailing arguments.
  // We don't assert argv[0] because it depends on NINJA_PYTHON's value,
  // which is internal to the implementation.
  ASSERT_GE(g_sys.execvp_argv.size(), static_cast<size_t>(6));
  ASSERT_EQ("-",                g_sys.execvp_argv[1]);
  ASSERT_EQ("--ninja-command",  g_sys.execvp_argv[2]);
  ASSERT_EQ(ninja_cmd,          g_sys.execvp_argv[3]);
  ASSERT_EQ("-f",               g_sys.execvp_argv[4]);
  ASSERT_EQ(input,              g_sys.execvp_argv[5]);
  ASSERT_EQ("-t",               g_sys.execvp_argv[6]);
  ASSERT_EQ("targets",          g_sys.execvp_argv[7]);
}

// In the parent branch, on execvp() failure with a non-ENOENT errno,
// RunBrowsePython should call perror("ninja: execvp").
TEST_F(RunBrowsePythonTest_167, ParentExecvpOtherErrorCallsPerror_167) {
  g_sys.pipe_return   = 0;
  g_sys.fork_return   = 1234;     // parent
  g_sys.dup2_return   = 0;        // success
  g_sys.execvp_return = -1;
  g_sys.execvp_errno  = EACCES;   // some error other than ENOENT

  RunBrowsePython(nullptr, "ninja_cmd", "build.ninja", 0, nullptr);

  EXPECT_EQ(1, g_sys.execvp_called);
  EXPECT_EQ(1, g_sys._exit_called);

  // Only one perror call for "ninja: execvp".
  EXPECT_EQ(1, g_sys.perror_called);
  EXPECT_EQ("ninja: execvp", g_sys.last_perror_msg);
}

// In the child branch, a successful write() should NOT call perror("ninja: write")
// and should call exit(0), closing both ends of the pipe appropriately.
TEST_F(RunBrowsePythonTest_167, ChildWriteSuccessClosesFdsAndExits_167) {
  g_sys.pipe_return = 0;
  g_sys.fork_return = 0;     // child branch
  g_sys.write_return = 1;    // some non-negative value

  RunBrowsePython(nullptr, "ninja_cmd", "build.ninja", 0, nullptr);

  EXPECT_EQ(1, g_sys.pipe_called);
  EXPECT_EQ(1, g_sys.fork_called);
  EXPECT_EQ(1, g_sys.write_called);

  // Child closes read end then write end.
  ASSERT_EQ(2u, g_sys.closed_fds.size());
  EXPECT_EQ(10, g_sys.closed_fds[0]);  // read end
  EXPECT_EQ(11, g_sys.closed_fds[1]);  // write end

  EXPECT_EQ(0, g_sys.perror_called);   // no write error
  EXPECT_EQ(1, g_sys.exit_called);
  EXPECT_EQ(0, g_sys.last_exit_code);
  EXPECT_EQ(0, g_sys._exit_called);    // parent-only path
}

// In the child branch, a short write (simulated by negative return value)
// should trigger perror("ninja: write") before exiting.
TEST_F(RunBrowsePythonTest_167, ChildWriteShortCallsPerror_167) {
  g_sys.pipe_return  = 0;
  g_sys.fork_return  = 0;     // child
  g_sys.write_return = -1;    // definitely < kBrowsePyLength

  RunBrowsePython(nullptr, "ninja_cmd", "build.ninja", 0, nullptr);

  EXPECT_EQ(1, g_sys.write_called);
  EXPECT_EQ(1, g_sys.perror_called);
  EXPECT_EQ("ninja: write", g_sys.last_perror_msg);

  EXPECT_EQ(1, g_sys.exit_called);
  EXPECT_EQ(0, g_sys.last_exit_code);
}
