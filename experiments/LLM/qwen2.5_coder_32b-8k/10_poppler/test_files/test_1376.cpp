#include <gtest/gtest.h>

#include "./TestProjects/poppler/qt5/src/poppler-form.h"

#include "./TestProjects/poppler/qt5/src/poppler-form.cc"



using namespace Poppler;



TEST(hasNSSBackendFeatureTest_1376, BackendAsksPassphrase_ReturnsFalse_1376) {

    EXPECT_FALSE(hasNSSBackendFeature(CryptoSignBackendFeature::BackendAsksPassphrase));

}



TEST(hasNSSBackendFeatureTest_1376, DefaultCase_ReturnsFalse_1376) {

    EXPECT_FALSE(hasNSSBackendFeature(static_cast<CryptoSignBackendFeature>(-1)));

}
