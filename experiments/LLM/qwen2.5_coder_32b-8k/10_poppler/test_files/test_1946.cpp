#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming fromCharPtr is in a namespace or header file that we include

// For this example, I'll assume it's in a namespace called GPGMECryptoSignBackend



namespace GPGMECryptoSignBackend {

    static std::string fromCharPtr(const char *data) { if (data) { return std::string { data }; } return {}; }

}



using ::testing::Eq;



TEST(fromCharPtrTest_1946, NormalOperationWithNonNullPointer_1946) {

    const char* testData = "Hello, World!";

    EXPECT_EQ(GPGMECryptoSignBackend::fromCharPtr(testData), "Hello, World!");

}



TEST(fromCharPtrTest_1946, NormalOperationWithEmptyString_1946) {

    const char* testData = "";

    EXPECT_EQ(GPGMECryptoSignBackend::fromCharPtr(testData), "");

}



TEST(fromCharPtrTest_1946, BoundaryConditionWithNullPointer_1946) {

    const char* testData = nullptr;

    EXPECT_EQ(GPGMECryptoSignBackend::fromCharPtr(testData), "");

}
