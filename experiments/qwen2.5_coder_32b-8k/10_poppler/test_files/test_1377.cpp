#include <gtest/gtest.h>

#include "poppler-form.h"



using namespace Poppler;



TEST(hasGPGBackendFeatureTest_1377, BackendAsksPassphrase_ReturnsTrue_1377) {

    EXPECT_TRUE(hasGPGBackendFeature(CryptoSignBackendFeature::BackendAsksPassphrase));

}



TEST(hasGPGBackendFeatureTest_1377, InvalidFeature_ReturnsFalse_1377) {

    EXPECT_FALSE(hasGPGBackendFeature(static_cast<CryptoSignBackendFeature>(-1)));

    EXPECT_FALSE(hasGPGBackendFeature(static_cast<CryptoSignBackendFeature>(1)));

}
