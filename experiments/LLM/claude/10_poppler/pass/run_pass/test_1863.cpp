#include <gtest/gtest.h>
#include <csetjmp>
#include <cstring>
#include <jpeglib.h>

// Since jpegExitErrorHandler is static in the .cc file, we need to include it
// to access the static function. This is a common testing pattern for static functions.
#include "ImageEmbeddingUtils.cc"

namespace {

static bool g_outputMessageCalled = false;

static void mockOutputMessage(j_common_ptr /*info*/)
{
    g_outputMessageCalled = true;
}

class JpegExitErrorHandlerTest_1863 : public ::testing::Test {
protected:
    void SetUp() override
    {
        g_outputMessageCalled = false;
    }
};

TEST_F(JpegExitErrorHandlerTest_1863, LongjmpIsPerformed_1863)
{
    // Setup a JpegErrorManager with a setjmp point
    ImageEmbeddingUtils::JpegErrorManager errorManager;
    memset(&errorManager, 0, sizeof(errorManager));

    // Set up the output_message callback
    errorManager.pub.output_message = mockOutputMessage;

    // Create a fake j_common_struct that points to our error manager
    struct jpeg_common_struct commonInfo;
    memset(&commonInfo, 0, sizeof(commonInfo));
    commonInfo.err = &errorManager.pub;

    // Use setjmp to establish the jump point
    bool longjmpOccurred = false;
    if (setjmp(errorManager.setjmpBuffer) == 0) {
        // First return from setjmp - call the error handler
        ImageEmbeddingUtils::jpegExitErrorHandler(&commonInfo);
        // Should NOT reach here
        FAIL() << "longjmp should have been called, execution should not continue here";
    } else {
        // Returned via longjmp
        longjmpOccurred = true;
    }

    EXPECT_TRUE(longjmpOccurred);
}

TEST_F(JpegExitErrorHandlerTest_1863, OutputMessageIsCalled_1863)
{
    ImageEmbeddingUtils::JpegErrorManager errorManager;
    memset(&errorManager, 0, sizeof(errorManager));

    errorManager.pub.output_message = mockOutputMessage;

    struct jpeg_common_struct commonInfo;
    memset(&commonInfo, 0, sizeof(commonInfo));
    commonInfo.err = &errorManager.pub;

    if (setjmp(errorManager.setjmpBuffer) == 0) {
        ImageEmbeddingUtils::jpegExitErrorHandler(&commonInfo);
        FAIL() << "Should not reach here after longjmp";
    }

    EXPECT_TRUE(g_outputMessageCalled);
}

TEST_F(JpegExitErrorHandlerTest_1863, JpegErrorManagerStructLayout_1863)
{
    // Verify that JpegErrorManager has the expected members
    ImageEmbeddingUtils::JpegErrorManager errorManager;
    memset(&errorManager, 0, sizeof(errorManager));

    // Verify pub is a jpeg_error_mgr (can assign standard error)
    jpeg_std_error(&errorManager.pub);

    // Verify that pub.output_message is set by jpeg_std_error
    EXPECT_NE(errorManager.pub.output_message, nullptr);
}

TEST_F(JpegExitErrorHandlerTest_1863, LongjmpReturnsNonZero_1863)
{
    ImageEmbeddingUtils::JpegErrorManager errorManager;
    memset(&errorManager, 0, sizeof(errorManager));
    errorManager.pub.output_message = mockOutputMessage;

    struct jpeg_common_struct commonInfo;
    memset(&commonInfo, 0, sizeof(commonInfo));
    commonInfo.err = &errorManager.pub;

    int setjmpReturnValue = setjmp(errorManager.setjmpBuffer);
    if (setjmpReturnValue == 0) {
        ImageEmbeddingUtils::jpegExitErrorHandler(&commonInfo);
        FAIL() << "Should not reach here";
    } else {
        // longjmp was called with value 1
        EXPECT_EQ(setjmpReturnValue, 1);
    }
}

} // namespace
