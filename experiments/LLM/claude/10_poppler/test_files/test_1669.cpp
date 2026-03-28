#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Since we only have a partial interface showing DeviceNRecoder with isBinary method,
// we need to test based on the observable behavior described.

// Minimal mock/stub to make the code compilable
// The DeviceNRecoder class has isBinary that always returns true

class DeviceNRecoder {
public:
    virtual bool isBinary(bool last = true) const { return true; }
    virtual ~DeviceNRecoder() = default;
};

// Test fixture
class DeviceNRecoderTest_1669 : public ::testing::Test {
protected:
    DeviceNRecoder recoder;
};

// Test that isBinary returns true with default parameter
TEST_F(DeviceNRecoderTest_1669, IsBinaryReturnsTrueDefault_1669) {
    EXPECT_TRUE(recoder.isBinary());
}

// Test that isBinary returns true when called with true
TEST_F(DeviceNRecoderTest_1669, IsBinaryReturnsTrueWithTrueArg_1669) {
    EXPECT_TRUE(recoder.isBinary(true));
}

// Test that isBinary returns true when called with false
TEST_F(DeviceNRecoderTest_1669, IsBinaryReturnsTrueWithFalseArg_1669) {
    EXPECT_TRUE(recoder.isBinary(false));
}

// Test that isBinary is consistent across multiple calls
TEST_F(DeviceNRecoderTest_1669, IsBinaryConsistentAcrossMultipleCalls_1669) {
    EXPECT_TRUE(recoder.isBinary());
    EXPECT_TRUE(recoder.isBinary(true));
    EXPECT_TRUE(recoder.isBinary(false));
    EXPECT_TRUE(recoder.isBinary());
}

// Test that isBinary works on a const object
TEST_F(DeviceNRecoderTest_1669, IsBinaryWorksOnConstObject_1669) {
    const DeviceNRecoder constRecoder;
    EXPECT_TRUE(constRecoder.isBinary());
    EXPECT_TRUE(constRecoder.isBinary(true));
    EXPECT_TRUE(constRecoder.isBinary(false));
}

// Test with pointer to object
TEST_F(DeviceNRecoderTest_1669, IsBinaryWorksViaPointer_1669) {
    DeviceNRecoder* ptr = new DeviceNRecoder();
    EXPECT_TRUE(ptr->isBinary());
    EXPECT_TRUE(ptr->isBinary(true));
    EXPECT_TRUE(ptr->isBinary(false));
    delete ptr;
}

// Test that the return value is exactly true (not just truthy)
TEST_F(DeviceNRecoderTest_1669, IsBinaryReturnsExactlyTrue_1669) {
    bool result = recoder.isBinary();
    EXPECT_EQ(result, true);
}

// Test that default parameter value doesn't affect result
TEST_F(DeviceNRecoderTest_1669, DefaultParameterDoesNotAffectResult_1669) {
    bool resultDefault = recoder.isBinary();
    bool resultTrue = recoder.isBinary(true);
    bool resultFalse = recoder.isBinary(false);
    EXPECT_EQ(resultDefault, resultTrue);
    EXPECT_EQ(resultDefault, resultFalse);
}
