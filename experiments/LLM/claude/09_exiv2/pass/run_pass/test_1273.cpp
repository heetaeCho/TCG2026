#include <gtest/gtest.h>

// Minimal type definitions needed for XMP_Error
typedef int32_t XMP_Int32;
typedef const char* XMP_StringPtr;

// Reconstruct the XMP_Error class based on the known/inferred dependencies
class XMP_Error {
public:
    XMP_Error(XMP_Int32 _id, XMP_StringPtr _errMsg) : id(_id), errMsg(_errMsg) {}
    inline XMP_Int32 GetID() const { return id; }
    inline XMP_StringPtr GetErrMsg() const { return errMsg; }
private:
    XMP_Int32 id;
    XMP_StringPtr errMsg;
};

// Test fixture
class XMPErrorTest_1273 : public ::testing::Test {
protected:
    // Helper to create XMP_Error objects
};

// Normal operation tests

TEST_F(XMPErrorTest_1273, GetID_ReturnsCorrectPositiveID_1273) {
    XMP_Error error(42, "Some error");
    EXPECT_EQ(42, error.GetID());
}

TEST_F(XMPErrorTest_1273, GetID_ReturnsCorrectNegativeID_1273) {
    XMP_Error error(-1, "Negative ID error");
    EXPECT_EQ(-1, error.GetID());
}

TEST_F(XMPErrorTest_1273, GetID_ReturnsZeroID_1273) {
    XMP_Error error(0, "Zero ID error");
    EXPECT_EQ(0, error.GetID());
}

TEST_F(XMPErrorTest_1273, GetErrMsg_ReturnsCorrectMessage_1273) {
    const char* msg = "Test error message";
    XMP_Error error(1, msg);
    EXPECT_STREQ("Test error message", error.GetErrMsg());
}

TEST_F(XMPErrorTest_1273, GetErrMsg_ReturnsEmptyString_1273) {
    XMP_Error error(1, "");
    EXPECT_STREQ("", error.GetErrMsg());
}

TEST_F(XMPErrorTest_1273, GetID_CalledMultipleTimes_ReturnsSameValue_1273) {
    XMP_Error error(100, "Consistent");
    EXPECT_EQ(100, error.GetID());
    EXPECT_EQ(100, error.GetID());
    EXPECT_EQ(100, error.GetID());
}

TEST_F(XMPErrorTest_1273, GetErrMsg_CalledMultipleTimes_ReturnsSameValue_1273) {
    const char* msg = "Consistent message";
    XMP_Error error(1, msg);
    EXPECT_STREQ(msg, error.GetErrMsg());
    EXPECT_STREQ(msg, error.GetErrMsg());
    EXPECT_STREQ(msg, error.GetErrMsg());
}

// Boundary condition tests

TEST_F(XMPErrorTest_1273, GetID_MaxInt32Value_1273) {
    XMP_Error error(INT32_MAX, "Max int error");
    EXPECT_EQ(INT32_MAX, error.GetID());
}

TEST_F(XMPErrorTest_1273, GetID_MinInt32Value_1273) {
    XMP_Error error(INT32_MIN, "Min int error");
    EXPECT_EQ(INT32_MIN, error.GetID());
}

TEST_F(XMPErrorTest_1273, GetErrMsg_NullPointer_1273) {
    XMP_Error error(1, nullptr);
    EXPECT_EQ(nullptr, error.GetErrMsg());
}

// Const correctness test

TEST_F(XMPErrorTest_1273, ConstObject_GetID_Works_1273) {
    const XMP_Error error(55, "Const error");
    EXPECT_EQ(55, error.GetID());
}

TEST_F(XMPErrorTest_1273, ConstObject_GetErrMsg_Works_1273) {
    const XMP_Error error(55, "Const error message");
    EXPECT_STREQ("Const error message", error.GetErrMsg());
}

// Multiple distinct errors

TEST_F(XMPErrorTest_1273, MultipleErrors_HaveDistinctIDs_1273) {
    XMP_Error error1(1, "Error 1");
    XMP_Error error2(2, "Error 2");
    XMP_Error error3(3, "Error 3");
    EXPECT_EQ(1, error1.GetID());
    EXPECT_EQ(2, error2.GetID());
    EXPECT_EQ(3, error3.GetID());
}

TEST_F(XMPErrorTest_1273, MultipleErrors_HaveDistinctMessages_1273) {
    XMP_Error error1(1, "First");
    XMP_Error error2(2, "Second");
    EXPECT_STREQ("First", error1.GetErrMsg());
    EXPECT_STREQ("Second", error2.GetErrMsg());
}

TEST_F(XMPErrorTest_1273, SameID_DifferentMessages_1273) {
    XMP_Error error1(5, "Message A");
    XMP_Error error2(5, "Message B");
    EXPECT_EQ(error1.GetID(), error2.GetID());
    EXPECT_STRNE(error1.GetErrMsg(), error2.GetErrMsg());
}

TEST_F(XMPErrorTest_1273, GetErrMsg_PointerIdentity_1273) {
    const char* msg = "Exact pointer";
    XMP_Error error(1, msg);
    EXPECT_EQ(msg, error.GetErrMsg());
}

TEST_F(XMPErrorTest_1273, LongErrorMessage_1273) {
    const char* longMsg = "This is a very long error message that spans many characters to test whether the error class properly stores and returns longer strings without any truncation or corruption issues.";
    XMP_Error error(99, longMsg);
    EXPECT_STREQ(longMsg, error.GetErrMsg());
    EXPECT_EQ(99, error.GetID());
}
