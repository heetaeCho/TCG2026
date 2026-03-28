#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>

// Include the necessary headers from poppler
#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class AnnotRichMediaContentTest_866 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getAssets returns a reference to the assets vector
// When Content is constructed with a valid dict, getAssets should return accessible vector
TEST_F(AnnotRichMediaContentTest_866, GetAssetsReturnsVector_866) {
    // We need a PDFDoc to create proper Dict objects
    // Since we can't easily construct Content without a proper Dict from a PDF,
    // we test through loading an actual PDF with RichMedia annotations if available.
    // For unit testing purposes, we verify the interface contract.
    
    // Create a minimal Dict - this requires an XRef object
    // Since Content requires a Dict*, and we're testing the interface,
    // we can test with a nullptr or empty dict to check boundary behavior
    // However, Content's constructor may crash with nullptr, so we need a real Dict
    
    // Test with an empty Dict (no RichMedia assets)
    auto xref = std::unique_ptr<XRef>(nullptr);
    Dict dict(static_cast<XRef*>(nullptr));
    
    // Construct Content with an empty dict - should handle gracefully
    AnnotRichMedia::Content content(&dict);
    
    const auto &assets = content.getAssets();
    // With an empty dict, there should be no assets
    EXPECT_TRUE(assets.empty());
}

// Test that getConfigurations returns a reference to the configurations vector
TEST_F(AnnotRichMediaContentTest_866, GetConfigurationsReturnsVector_866) {
    Dict dict(static_cast<XRef*>(nullptr));
    
    AnnotRichMedia::Content content(&dict);
    
    const auto &configurations = content.getConfigurations();
    // With an empty dict, there should be no configurations
    EXPECT_TRUE(configurations.empty());
}

// Test that getAssets returns consistent results on multiple calls
TEST_F(AnnotRichMediaContentTest_866, GetAssetsConsistentResults_866) {
    Dict dict(static_cast<XRef*>(nullptr));
    
    AnnotRichMedia::Content content(&dict);
    
    const auto &assets1 = content.getAssets();
    const auto &assets2 = content.getAssets();
    
    // Should return the same reference
    EXPECT_EQ(&assets1, &assets2);
}

// Test that getConfigurations returns consistent results on multiple calls
TEST_F(AnnotRichMediaContentTest_866, GetConfigurationsConsistentResults_866) {
    Dict dict(static_cast<XRef*>(nullptr));
    
    AnnotRichMedia::Content content(&dict);
    
    const auto &configs1 = content.getConfigurations();
    const auto &configs2 = content.getConfigurations();
    
    // Should return the same reference
    EXPECT_EQ(&configs1, &configs2);
}

// Test that Content with empty dict produces empty assets and configurations
TEST_F(AnnotRichMediaContentTest_866, EmptyDictProducesEmptyCollections_866) {
    Dict dict(static_cast<XRef*>(nullptr));
    
    AnnotRichMedia::Content content(&dict);
    
    EXPECT_EQ(content.getAssets().size(), 0u);
    EXPECT_EQ(content.getConfigurations().size(), 0u);
}

// Test that the returned vectors contain unique_ptr elements (type check via compilation)
TEST_F(AnnotRichMediaContentTest_866, ReturnTypeIsCorrect_866) {
    Dict dict(static_cast<XRef*>(nullptr));
    
    AnnotRichMedia::Content content(&dict);
    
    // Verify that the return types are correct by assigning to typed references
    const std::vector<std::unique_ptr<AnnotRichMedia::Content::Asset>> &assets = content.getAssets();
    const std::vector<std::unique_ptr<AnnotRichMedia::Content::Configuration>> &configs = content.getConfigurations();
    
    // If this compiles, the types are correct
    EXPECT_GE(assets.size(), 0u);
    EXPECT_GE(configs.size(), 0u);
}
