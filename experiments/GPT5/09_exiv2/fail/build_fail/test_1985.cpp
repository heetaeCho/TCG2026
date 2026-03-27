#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMPMeta.hpp"
#include "XMPUtils.hpp"

// Mocking the XMP_Node class since it's used in the function CreateEstimatedSizeMap
class MockXMP_Node : public XMP_Node {
public:
    MockXMP_Node(XMP_Node* parent, const XMP_VarString& name, XMP_OptionBits options)
        : XMP_Node(parent, name, options) {}

    MOCK_METHOD(size_t, getChildrenSize, (), (const, override));
    MOCK_METHOD(XMP_Node*, getChildAt, (size_t index), (const, override));
};

class XMPUtilsTest : public ::testing::Test {
protected:
    XMPMeta stdXMP;
    PropSizeMap propSizes;

    void SetUp() override {
        // Setup XMPMeta and other initializations as necessary
    }

    void TearDown() override {
        // Clean up after each test
    }
};

// TEST_ID: 1985
TEST_F(XMPUtilsTest, CreateEstimatedSizeMap_NormalOperation_1985) {
    // Test case for normal operation
    MockXMP_Node* mockNode = new MockXMP_Node(nullptr, "testSchema", 0);
    EXPECT_CALL(*mockNode, getChildrenSize()).WillOnce(testing::Return(2));

    // Simulate normal behavior
    XMP_Node* mockChild = new MockXMP_Node(mockNode, "testProperty", 0);
    EXPECT_CALL(*mockNode, getChildAt(0)).WillOnce(testing::Return(mockChild));

    // Call CreateEstimatedSizeMap
    CreateEstimatedSizeMap(stdXMP, &propSizes);
    EXPECT_FALSE(propSizes.empty());
}

// TEST_ID: 1986
TEST_F(XMPUtilsTest, CreateEstimatedSizeMap_EmptyTree_1986) {
    // Test case where the XMP tree is empty
    EXPECT_CALL(*mockNode, getChildrenSize()).WillOnce(testing::Return(0));

    // Call CreateEstimatedSizeMap with empty tree
    CreateEstimatedSizeMap(stdXMP, &propSizes);
    EXPECT_TRUE(propSizes.empty());
}

// TEST_ID: 1987
TEST_F(XMPUtilsTest, CreateEstimatedSizeMap_OneProperty_1987) {
    // Test case for a single property
    MockXMP_Node* mockNode = new MockXMP_Node(nullptr, "testSchema", 0);
    EXPECT_CALL(*mockNode, getChildrenSize()).WillOnce(testing::Return(1));

    XMP_Node* mockChild = new MockXMP_Node(mockNode, "testProperty", 0);
    EXPECT_CALL(*mockNode, getChildAt(0)).WillOnce(testing::Return(mockChild));

    // Call CreateEstimatedSizeMap with one property
    CreateEstimatedSizeMap(stdXMP, &propSizes);
    EXPECT_EQ(propSizes.size(), 1);
}

// TEST_ID: 1988
TEST_F(XMPUtilsTest, CreateEstimatedSizeMap_IgnoreExtendedXMP_1988) {
    // Test case where xmpNote:HasExtendedXMP should be ignored
    MockXMP_Node* mockNode = new MockXMP_Node(nullptr, "xmpNote", 0);
    XMP_Node* mockChild = new MockXMP_Node(mockNode, "xmpNote:HasExtendedXMP", 0);

    EXPECT_CALL(*mockNode, getChildrenSize()).WillOnce(testing::Return(1));
    EXPECT_CALL(*mockNode, getChildAt(0)).WillOnce(testing::Return(mockChild));

    // Call CreateEstimatedSizeMap and ensure "xmpNote:HasExtendedXMP" is ignored
    CreateEstimatedSizeMap(stdXMP, &propSizes);
    EXPECT_TRUE(propSizes.empty());
}

// TEST_ID: 1989
TEST_F(XMPUtilsTest, CreateEstimatedSizeMap_InvalidProperty_1989) {
    // Test case for an invalid property that might cause an error or unexpected behavior
    MockXMP_Node* mockNode = new MockXMP_Node(nullptr, "testSchema", 0);
    EXPECT_CALL(*mockNode, getChildrenSize()).WillOnce(testing::Return(1));

    XMP_Node* mockChild = new MockXMP_Node(mockNode, "invalidProperty", 0);
    EXPECT_CALL(*mockNode, getChildAt(0)).WillOnce(testing::Return(mockChild));

    // Simulate error while estimating size for JPEG
    EXPECT_CALL(*mockChild, EstimateSizeForJPEG()).WillOnce(testing::Return(-1));  // Invalid size

    // Call CreateEstimatedSizeMap
    CreateEstimatedSizeMap(stdXMP, &propSizes);
    EXPECT_TRUE(propSizes.empty());
}