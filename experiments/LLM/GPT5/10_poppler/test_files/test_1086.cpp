#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "OutputDev.h" // Include the header file containing the class

// Mocking PopplerCache if needed
class MockPopplerCache : public PopplerCache<Ref, GfxICCBasedColorSpace> {
public:
    MOCK_METHOD(GfxICCBasedColorSpace*, get, (const Ref&), (override));
};

// Unit tests for OutputDev class
TEST_F(OutputDevTest_1086, GetIccColorSpaceCache_1086) {
    OutputDev outputDev;

    // Act: Call the method to retrieve the cache
    PopplerCache<Ref, GfxICCBasedColorSpace>* cache = outputDev.getIccColorSpaceCache();

    // Assert: Ensure the returned cache pointer is not null
    ASSERT_NE(cache, nullptr);
}

TEST_F(OutputDevTest_1086, GetIccColorSpaceCache_NormalOperation_1086) {
    OutputDev outputDev;
    MockPopplerCache mockCache;

    // Set up expectations for the mock cache
    Ref ref;
    GfxICCBasedColorSpace* colorSpace = new GfxICCBasedColorSpace();
    EXPECT_CALL(mockCache, get(ref)).WillOnce(testing::Return(colorSpace));

    // Act: Call the method to retrieve the cache
    PopplerCache<Ref, GfxICCBasedColorSpace>* cache = outputDev.getIccColorSpaceCache();
    GfxICCBasedColorSpace* result = cache->get(ref);

    // Assert: Ensure the returned color space is what we expect
    ASSERT_EQ(result, colorSpace);
}

TEST_F(OutputDevTest_1086, GetIccColorSpaceCache_EmptyCache_1086) {
    OutputDev outputDev;
    
    // Act: Call the method to retrieve the cache
    PopplerCache<Ref, GfxICCBasedColorSpace>* cache = outputDev.getIccColorSpaceCache();

    // Assert: Ensure the cache is empty
    ASSERT_EQ(cache->size(), 0); // Assumes that the cache starts empty
}

TEST_F(OutputDevTest_1086, GetIccColorSpaceCache_ErrorCase_1086) {
    OutputDev outputDev;
    MockPopplerCache mockCache;

    // Set up the mock to return nullptr in case of error
    Ref ref;
    EXPECT_CALL(mockCache, get(ref)).WillOnce(testing::Return(nullptr));

    // Act: Call the method to retrieve the cache
    PopplerCache<Ref, GfxICCBasedColorSpace>* cache = outputDev.getIccColorSpaceCache();
    GfxICCBasedColorSpace* result = cache->get(ref);

    // Assert: Ensure the result is nullptr
    ASSERT_EQ(result, nullptr);
}