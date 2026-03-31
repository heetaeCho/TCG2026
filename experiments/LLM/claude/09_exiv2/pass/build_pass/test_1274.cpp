#include <gtest/gtest.h>

// Minimal type definitions needed for XMP_Error
typedef const char* XMP_StringPtr;
typedef int XMP_Int32;

class XMP_Error {
private:
    XMP_Int32 id;
    XMP_StringPtr errMsg;
public:
    XMP_Error(XMP_Int32 _id, XMP_StringPtr _errMsg) : id(_id), errMsg(_errMsg) {}
    inline XMP_Int32 GetID() const { return id; }
    inline XMP_StringPtr GetErrMsg() const { return errMsg; }
};

// Test fixture
class XMP_ErrorTest_1274 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Normal operation tests

TEST_F(XMP_ErrorTest_1274, GetErrMsg_ReturnsCorrectMessage_1274) {
    XMP_Error error(1, "Test error message");
    EXPECT_STREQ(error.GetErrMsg(), "Test error message");
}

TEST_F(XMP_ErrorTest_1274, GetID_ReturnsCorrectID_1274) {
    XMP_Error error(42, "Some error");
    EXPECT_EQ(error.GetID(), 42);
}

TEST_F(XMP_ErrorTest_1274, GetErrMsg_WithDifferentMessages_1274) {
    XMP_Error error1(1, "First error");
    XMP_Error error2(2, "Second error");
    EXPECT_STREQ(error1.GetErrMsg(), "First error");
    EXPECT_STREQ(error2.GetErrMsg(), "Second error");
}

TEST_F(XMP_ErrorTest_1274, GetID_WithDifferentIDs_1274) {
    XMP_Error error1(100, "Error A");
    XMP_Error error2(200, "Error B");
    EXPECT_EQ(error1.GetID(), 100);
    EXPECT_EQ(error2.GetID(), 200);
}

TEST_F(XMP_ErrorTest_1274, ConstructorPreservesIDAndMessage_1274) {
    XMP_Int32 expectedId = 99;
    XMP_StringPtr expectedMsg = "Expected error message";
    XMP_Error error(expectedId, expectedMsg);
    EXPECT_EQ(error.GetID(), expectedId);
    EXPECT_STREQ(error.GetErrMsg(), expectedMsg);
}

// Boundary condition tests

TEST_F(XMP_ErrorTest_1274, GetErrMsg_EmptyString_1274) {
    XMP_Error error(0, "");
    EXPECT_STREQ(error.GetErrMsg(), "");
}

TEST_F(XMP_ErrorTest_1274, GetID_ZeroID_1274) {
    XMP_Error error(0, "Zero ID error");
    EXPECT_EQ(error.GetID(), 0);
}

TEST_F(XMP_ErrorTest_1274, GetID_NegativeID_1274) {
    XMP_Error error(-1, "Negative ID error");
    EXPECT_EQ(error.GetID(), -1);
}

TEST_F(XMP_ErrorTest_1274, GetID_MaxIntID_1274) {
    XMP_Error error(2147483647, "Max int ID error");
    EXPECT_EQ(error.GetID(), 2147483647);
}

TEST_F(XMP_ErrorTest_1274, GetID_MinIntID_1274) {
    XMP_Error error(-2147483648, "Min int ID error");
    EXPECT_EQ(error.GetID(), -2147483648);
}

TEST_F(XMP_ErrorTest_1274, GetErrMsg_LongMessage_1274) {
    const char* longMsg = "This is a very long error message that contains many characters to test whether the XMP_Error class can handle long strings properly without any issues whatsoever.";
    XMP_Error error(1, longMsg);
    EXPECT_STREQ(error.GetErrMsg(), longMsg);
}

// Exceptional/edge case tests

TEST_F(XMP_ErrorTest_1274, GetErrMsg_NullMessage_1274) {
    XMP_Error error(1, nullptr);
    EXPECT_EQ(error.GetErrMsg(), nullptr);
}

TEST_F(XMP_ErrorTest_1274, GetErrMsg_CalledMultipleTimes_ReturnsSameValue_1274) {
    XMP_Error error(5, "Consistent message");
    EXPECT_STREQ(error.GetErrMsg(), "Consistent message");
    EXPECT_STREQ(error.GetErrMsg(), "Consistent message");
    EXPECT_STREQ(error.GetErrMsg(), "Consistent message");
}

TEST_F(XMP_ErrorTest_1274, GetID_CalledMultipleTimes_ReturnsSameValue_1274) {
    XMP_Error error(77, "Repeated ID check");
    EXPECT_EQ(error.GetID(), 77);
    EXPECT_EQ(error.GetID(), 77);
    EXPECT_EQ(error.GetID(), 77);
}

TEST_F(XMP_ErrorTest_1274, GetErrMsg_SpecialCharacters_1274) {
    XMP_Error error(10, "Error with special chars: !@#$%^&*()_+\n\t\\\"");
    EXPECT_STREQ(error.GetErrMsg(), "Error with special chars: !@#$%^&*()_+\n\t\\\"");
}

TEST_F(XMP_ErrorTest_1274, MultipleErrorObjectsIndependent_1274) {
    XMP_Error error1(1, "Error 1");
    XMP_Error error2(2, "Error 2");
    XMP_Error error3(3, "Error 3");

    EXPECT_EQ(error1.GetID(), 1);
    EXPECT_EQ(error2.GetID(), 2);
    EXPECT_EQ(error3.GetID(), 3);

    EXPECT_STREQ(error1.GetErrMsg(), "Error 1");
    EXPECT_STREQ(error2.GetErrMsg(), "Error 2");
    EXPECT_STREQ(error3.GetErrMsg(), "Error 3");
}

TEST_F(XMP_ErrorTest_1274, CopyConstruction_PreservesValues_1274) {
    XMP_Error original(55, "Original error");
    XMP_Error copy(original);
    EXPECT_EQ(copy.GetID(), 55);
    EXPECT_STREQ(copy.GetErrMsg(), "Original error");
}

TEST_F(XMP_ErrorTest_1274, GetErrMsg_PointsToSameStringLiteral_1274) {
    const char* msg = "Shared message";
    XMP_Error error(1, msg);
    EXPECT_EQ(error.GetErrMsg(), msg);
}
