#include <gtest/gtest.h>
#include <cstring>

// Type definitions matching the XMP SDK types
typedef int XMP_Status;
typedef const char * XMP_StringPtr;
typedef unsigned int XMP_StringLen;
typedef XMP_Status (* XMP_TextOutputProc)(void * refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize);

// TOPW_Info class based on the known/inferred dependencies
class TOPW_Info {
public:
    XMP_TextOutputProc clientProc;
    void * clientRefCon;
    TOPW_Info(XMP_TextOutputProc proc, void * refCon) : clientProc(proc), clientRefCon(refCon) {}
private:
    TOPW_Info();
};

// The function under test
static XMP_Status TextOutputProcWrapper(void * refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    try {
        TOPW_Info * info = (TOPW_Info*)refCon;
        return info->clientProc(info->clientRefCon, buffer, bufferSize);
    } catch (...) {
        return -1;
    }
}

// ============================================================================
// Test Helpers
// ============================================================================

// A simple callback that records what was passed to it
struct CallbackRecord {
    void * receivedRefCon;
    XMP_StringPtr receivedBuffer;
    XMP_StringLen receivedBufferSize;
    int callCount;
    XMP_Status returnValue;
};

static XMP_Status RecordingCallback(void * refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    CallbackRecord * record = static_cast<CallbackRecord*>(refCon);
    record->receivedRefCon = refCon;
    record->receivedBuffer = buffer;
    record->receivedBufferSize = bufferSize;
    record->callCount++;
    return record->returnValue;
}

// A callback that always returns success (0)
static XMP_Status SuccessCallback(void * refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    (void)refCon;
    (void)buffer;
    (void)bufferSize;
    return 0;
}

// A callback that returns a specific error code
static XMP_Status ErrorCallback(void * refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    (void)refCon;
    (void)buffer;
    (void)bufferSize;
    return -42;
}

// A callback that throws an exception
static XMP_Status ThrowingCallback(void * refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    (void)refCon;
    (void)buffer;
    (void)bufferSize;
    throw std::runtime_error("Test exception");
}

// A callback that throws an integer
static XMP_Status ThrowingIntCallback(void * refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    (void)refCon;
    (void)buffer;
    (void)bufferSize;
    throw 42;
}

// A callback that returns a positive value
static XMP_Status PositiveReturnCallback(void * refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    (void)refCon;
    (void)buffer;
    (void)bufferSize;
    return 100;
}

// ============================================================================
// Test Fixture
// ============================================================================

class TextOutputProcWrapperTest_1275 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================================
// Normal Operation Tests
// ============================================================================

TEST_F(TextOutputProcWrapperTest_1275, CallbackIsInvokedWithCorrectParameters_1275) {
    CallbackRecord record = {};
    record.returnValue = 0;
    record.callCount = 0;

    TOPW_Info info(RecordingCallback, &record);

    const char * testBuffer = "Hello, World!";
    XMP_StringLen testLen = static_cast<XMP_StringLen>(strlen(testBuffer));

    XMP_Status status = TextOutputProcWrapper(&info, testBuffer, testLen);

    EXPECT_EQ(status, 0);
    EXPECT_EQ(record.callCount, 1);
    EXPECT_EQ(record.receivedBuffer, testBuffer);
    EXPECT_EQ(record.receivedBufferSize, testLen);
    EXPECT_EQ(record.receivedRefCon, &record);
}

TEST_F(TextOutputProcWrapperTest_1275, SuccessCallbackReturnsZero_1275) {
    int dummyRefCon = 0;
    TOPW_Info info(SuccessCallback, &dummyRefCon);

    XMP_Status status = TextOutputProcWrapper(&info, "test", 4);

    EXPECT_EQ(status, 0);
}

TEST_F(TextOutputProcWrapperTest_1275, ErrorCallbackPropagatesReturnValue_1275) {
    int dummyRefCon = 0;
    TOPW_Info info(ErrorCallback, &dummyRefCon);

    XMP_Status status = TextOutputProcWrapper(&info, "test", 4);

    EXPECT_EQ(status, -42);
}

TEST_F(TextOutputProcWrapperTest_1275, PositiveReturnValueIsPropagated_1275) {
    int dummyRefCon = 0;
    TOPW_Info info(PositiveReturnCallback, &dummyRefCon);

    XMP_Status status = TextOutputProcWrapper(&info, "test", 4);

    EXPECT_EQ(status, 100);
}

TEST_F(TextOutputProcWrapperTest_1275, ClientRefConIsPassedThrough_1275) {
    CallbackRecord record = {};
    record.returnValue = 0;
    record.callCount = 0;

    TOPW_Info info(RecordingCallback, &record);

    TextOutputProcWrapper(&info, "data", 4);

    // The callback should have received the clientRefCon (which is &record)
    EXPECT_EQ(record.receivedRefCon, static_cast<void*>(&record));
}

// ============================================================================
// Exception Handling Tests
// ============================================================================

TEST_F(TextOutputProcWrapperTest_1275, StdExceptionReturnsMinus1_1275) {
    int dummyRefCon = 0;
    TOPW_Info info(ThrowingCallback, &dummyRefCon);

    XMP_Status status = TextOutputProcWrapper(&info, "test", 4);

    EXPECT_EQ(status, -1);
}

TEST_F(TextOutputProcWrapperTest_1275, NonStdExceptionReturnsMinus1_1275) {
    int dummyRefCon = 0;
    TOPW_Info info(ThrowingIntCallback, &dummyRefCon);

    XMP_Status status = TextOutputProcWrapper(&info, "test", 4);

    EXPECT_EQ(status, -1);
}

// ============================================================================
// Boundary Condition Tests
// ============================================================================

TEST_F(TextOutputProcWrapperTest_1275, EmptyBufferIsPassedThrough_1275) {
    CallbackRecord record = {};
    record.returnValue = 0;
    record.callCount = 0;

    TOPW_Info info(RecordingCallback, &record);

    XMP_Status status = TextOutputProcWrapper(&info, "", 0);

    EXPECT_EQ(status, 0);
    EXPECT_EQ(record.callCount, 1);
    EXPECT_EQ(record.receivedBufferSize, 0u);
}

TEST_F(TextOutputProcWrapperTest_1275, NullBufferIsPassedThrough_1275) {
    CallbackRecord record = {};
    record.returnValue = 0;
    record.callCount = 0;

    TOPW_Info info(RecordingCallback, &record);

    XMP_Status status = TextOutputProcWrapper(&info, nullptr, 0);

    EXPECT_EQ(status, 0);
    EXPECT_EQ(record.callCount, 1);
    EXPECT_EQ(record.receivedBuffer, nullptr);
    EXPECT_EQ(record.receivedBufferSize, 0u);
}

TEST_F(TextOutputProcWrapperTest_1275, NullClientRefConIsPassedThrough_1275) {
    CallbackRecord record = {};
    record.returnValue = 5;
    record.callCount = 0;

    // Here we use RecordingCallback but the TOPW_Info's clientRefCon is &record
    TOPW_Info info(RecordingCallback, &record);

    XMP_Status status = TextOutputProcWrapper(&info, "abc", 3);

    EXPECT_EQ(status, 5);
    EXPECT_EQ(record.callCount, 1);
}

TEST_F(TextOutputProcWrapperTest_1275, LargeBufferSizeIsPassedThrough_1275) {
    CallbackRecord record = {};
    record.returnValue = 0;
    record.callCount = 0;

    TOPW_Info info(RecordingCallback, &record);

    XMP_StringLen largeSize = 0xFFFFFFFF;
    XMP_Status status = TextOutputProcWrapper(&info, "x", largeSize);

    EXPECT_EQ(status, 0);
    EXPECT_EQ(record.receivedBufferSize, largeSize);
}

TEST_F(TextOutputProcWrapperTest_1275, MultipleCallsWorkCorrectly_1275) {
    CallbackRecord record = {};
    record.returnValue = 0;
    record.callCount = 0;

    TOPW_Info info(RecordingCallback, &record);

    TextOutputProcWrapper(&info, "first", 5);
    TextOutputProcWrapper(&info, "second", 6);
    TextOutputProcWrapper(&info, "third", 5);

    EXPECT_EQ(record.callCount, 3);
    // Last call's parameters should be recorded
    EXPECT_EQ(record.receivedBufferSize, 5u);
}

TEST_F(TextOutputProcWrapperTest_1275, ReturnValueMinInt_1275) {
    static auto minIntCallback = [](void * refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) -> XMP_Status {
        (void)refCon; (void)buffer; (void)bufferSize;
        return std::numeric_limits<int>::min();
    };

    // Use a function pointer compatible callback
    struct Helper {
        static XMP_Status Callback(void * refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
            (void)refCon; (void)buffer; (void)bufferSize;
            return -2147483647 - 1; // INT_MIN
        }
    };

    int dummy = 0;
    TOPW_Info info(Helper::Callback, &dummy);

    XMP_Status status = TextOutputProcWrapper(&info, "test", 4);

    EXPECT_EQ(status, -2147483647 - 1);
}

TEST_F(TextOutputProcWrapperTest_1275, ReturnValueMaxInt_1275) {
    struct Helper {
        static XMP_Status Callback(void * refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
            (void)refCon; (void)buffer; (void)bufferSize;
            return 2147483647; // INT_MAX
        }
    };

    int dummy = 0;
    TOPW_Info info(Helper::Callback, &dummy);

    XMP_Status status = TextOutputProcWrapper(&info, "test", 4);

    EXPECT_EQ(status, 2147483647);
}

// ============================================================================
// Exception Variety Tests
// ============================================================================

TEST_F(TextOutputProcWrapperTest_1275, ThrowStringExceptionReturnsMinus1_1275) {
    struct Helper {
        static XMP_Status Callback(void * refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
            (void)refCon; (void)buffer; (void)bufferSize;
            throw std::string("string exception");
        }
    };

    int dummy = 0;
    TOPW_Info info(Helper::Callback, &dummy);

    XMP_Status status = TextOutputProcWrapper(&info, "test", 4);

    EXPECT_EQ(status, -1);
}

TEST_F(TextOutputProcWrapperTest_1275, ThrowBadAllocReturnsMinus1_1275) {
    struct Helper {
        static XMP_Status Callback(void * refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
            (void)refCon; (void)buffer; (void)bufferSize;
            throw std::bad_alloc();
        }
    };

    int dummy = 0;
    TOPW_Info info(Helper::Callback, &dummy);

    XMP_Status status = TextOutputProcWrapper(&info, "test", 4);

    EXPECT_EQ(status, -1);
}
