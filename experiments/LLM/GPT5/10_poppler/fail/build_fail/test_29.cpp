// The TEST_ID is 29
//
// Unit tests for ./TestProjects/poppler/goo/JpegWriter.cc (partial)
// Focus: static outputMessage(j_common_ptr)
//
// NOTE: We treat the implementation as a black box. We only verify observable behavior:
// - It calls cinfo->err->format_message(cinfo, buffer)
// - It forwards the formatted buffer to error(errInternal, -1, "{0:s}", buffer)

#include <gtest/gtest.h>

#include <cstring>
#include <string>

// ---- Minimal external dependencies/stubs to compile and observe behavior ----

// From ./TestProjects/poppler/poppler/Error.h (given)
enum ErrorCategory {
  errSyntaxWarning = 0,
  errSyntaxError = 1,
  errConfig = 2,
  errCommandLine = 3,
  errIO = 4,
  errNotAllowed = 5,
  errUnimplemented = 6,
  errInternal = 7
};

// JMSG_LENGTH_MAX is used to size the stack buffer in outputMessage.
// Use a reasonable constant; tests rely only on relative behavior with this value.
#ifndef JMSG_LENGTH_MAX
#define JMSG_LENGTH_MAX 200
#endif

// Forward-declare types referenced by JpegWriter.cc typedefs
struct jpeg_common_struct;
typedef struct jpeg_common_struct* j_common_ptr;

// Minimal error manager containing the callback invoked by outputMessage.
struct jpeg_error_mgr {
  void (*format_message)(j_common_ptr cinfo, char* buffer);
};

// Minimal jpeg_common_struct containing err pointer used by outputMessage.
struct jpeg_common_struct {
  jpeg_error_mgr* err;
};

// Capture calls to poppler::error(...) made by outputMessage.
namespace test_capture {
struct ErrorCall {
  int calls = 0;
  ErrorCategory category = errSyntaxWarning;
  int pos = 0;
  std::string fmt;
  std::string arg;
};

inline ErrorCall g_error_call;

inline void ResetErrorCall() { g_error_call = ErrorCall{}; }

inline void RecordError(ErrorCategory category, int pos, const char* fmt, const char* arg) {
  g_error_call.calls++;
  g_error_call.category = category;
  g_error_call.pos = pos;
  g_error_call.fmt = fmt ? fmt : "";
  g_error_call.arg = arg ? arg : "";
}
}  // namespace test_capture

// Provide a symbol named `error(...)` matching the call site in outputMessage.
// This is the only observable "external interaction" in the snippet.
void error(ErrorCategory category, int pos, const char* fmt, const char* arg) {
  test_capture::RecordError(category, pos, fmt, arg);
}

// ---- Include the unit under test into this translation unit ----
// This allows calling the `static` function outputMessage(...) directly.
#include "./TestProjects/poppler/goo/JpegWriter.cc"

// ---- Tests ----

namespace {
struct FormatMessageCapture {
  int calls = 0;
  j_common_ptr last_cinfo = nullptr;
  const char* text_to_write = nullptr;

  static FormatMessageCapture* instance;

  static void Callback(j_common_ptr cinfo, char* buffer) {
    ASSERT_NE(buffer, nullptr);
    ASSERT_NE(instance, nullptr);
    instance->calls++;
    instance->last_cinfo = cinfo;

    const char* src = instance->text_to_write ? instance->text_to_write : "";
    // Write into provided buffer in a safe way; this simulates an external collaborator.
    std::strncpy(buffer, src, JMSG_LENGTH_MAX - 1);
    buffer[JMSG_LENGTH_MAX - 1] = '\0';
  }
};
FormatMessageCapture* FormatMessageCapture::instance = nullptr;
}  // namespace

class OutputMessageTest_29 : public ::testing::Test {
protected:
  void SetUp() override {
    test_capture::ResetErrorCall();
    capture_ = FormatMessageCapture{};
    FormatMessageCapture::instance = &capture_;
    err_mgr_.format_message = &FormatMessageCapture::Callback;
    cinfo_.err = &err_mgr_;
  }

  void TearDown() override { FormatMessageCapture::instance = nullptr; }

  jpeg_error_mgr err_mgr_{};
  jpeg_common_struct cinfo_{};
  FormatMessageCapture capture_{};
};

TEST_F(OutputMessageTest_29, CallsFormatMessageAndForwardsToError_29) {
  capture_.text_to_write = "hello-from-format_message";

  outputMessage(&cinfo_);

  // Verify external interaction #1: format_message invoked once with same cinfo.
  EXPECT_EQ(capture_.calls, 1);
  EXPECT_EQ(capture_.last_cinfo, &cinfo_);

  // Verify external interaction #2: error called once with expected parameters.
  EXPECT_EQ(test_capture::g_error_call.calls, 1);
  EXPECT_EQ(test_capture::g_error_call.category, errInternal);
  EXPECT_EQ(test_capture::g_error_call.pos, -1);
  EXPECT_EQ(test_capture::g_error_call.fmt, "{0:s}");
  EXPECT_EQ(test_capture::g_error_call.arg, "hello-from-format_message");
}

TEST_F(OutputMessageTest_29, HandlesEmptyFormattedMessage_29) {
  capture_.text_to_write = "";

  outputMessage(&cinfo_);

  EXPECT_EQ(capture_.calls, 1);
  EXPECT_EQ(test_capture::g_error_call.calls, 1);
  EXPECT_EQ(test_capture::g_error_call.category, errInternal);
  EXPECT_EQ(test_capture::g_error_call.pos, -1);
  EXPECT_EQ(test_capture::g_error_call.fmt, "{0:s}");
  EXPECT_EQ(test_capture::g_error_call.arg, "");
}

TEST_F(OutputMessageTest_29, ForwardsLongMessageUpToBufferLimit_29) {
  // Create a message longer than the buffer to exercise boundary conditions.
  std::string long_msg(static_cast<size_t>(JMSG_LENGTH_MAX) * 3u, 'A');
  capture_.text_to_write = long_msg.c_str();

  outputMessage(&cinfo_);

  EXPECT_EQ(capture_.calls, 1);
  EXPECT_EQ(test_capture::g_error_call.calls, 1);

  // Since the collaborator writes into a fixed-size buffer, we expect truncation to (JMSG_LENGTH_MAX-1).
  ASSERT_EQ(test_capture::g_error_call.arg.size(), static_cast<size_t>(JMSG_LENGTH_MAX - 1));
  EXPECT_TRUE(std::all_of(test_capture::g_error_call.arg.begin(),
                          test_capture::g_error_call.arg.end(),
                          [](char ch) { return ch == 'A'; }));
}