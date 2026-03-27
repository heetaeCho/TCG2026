#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/FontInfo.h"

// Mock class if needed for external dependencies
class MockGfxFont : public GfxFont {};
class MockXRef : public XRef {};

// TEST_ID: 1001
TEST_F(FontInfoTest_1001, GetEncoding_ReturnsCorrectEncoding_1001) {
    MockGfxFont mockFont;
    MockXRef mockXRef;
    
    // Setup FontInfo object
    FontInfo fontInfo(&mockFont, &mockXRef);
    
    // Assuming encoding is "UTF-8" for testing purposes
    EXPECT_EQ(fontInfo.getEncoding(), "UTF-8");
}

// TEST_ID: 1002
TEST_F(FontInfoTest_1002, GetName_ReturnsValidName_1002) {
    MockGfxFont mockFont;
    MockXRef mockXRef;
    
    // Setup FontInfo object with a name
    FontInfo fontInfo(&mockFont, &mockXRef);
    
    // Simulate setting a name, assuming an internal mechanism to do so.
    fontInfo.setName("Arial");
    
    // Test that name is returned correctly
    EXPECT_EQ(*fontInfo.getName(), "Arial");
}

// TEST_ID: 1003
TEST_F(FontInfoTest_1003, GetSubstituteName_ReturnsValidSubstituteName_1003) {
    MockGfxFont mockFont;
    MockXRef mockXRef;
    
    // Setup FontInfo object with a substitute name
    FontInfo fontInfo(&mockFont, &mockXRef);
    
    // Simulate setting a substitute name
    fontInfo.setSubstituteName("Arial-Sub");
    
    // Test that substitute name is returned correctly
    EXPECT_EQ(*fontInfo.getSubstituteName(), "Arial-Sub");
}

// TEST_ID: 1004
TEST_F(FontInfoTest_1004, GetFile_ReturnsValidFile_1004) {
    MockGfxFont mockFont;
    MockXRef mockXRef;
    
    // Setup FontInfo object with a file
    FontInfo fontInfo(&mockFont, &mockXRef);
    
    // Simulate setting a file path
    fontInfo.setFile("fontfile.ttf");
    
    // Test that file is returned correctly
    EXPECT_EQ(*fontInfo.getFile(), "fontfile.ttf");
}

// TEST_ID: 1005
TEST_F(FontInfoTest_1005, GetEncoding_WhenEncodingIsNotSet_ReturnsEmpty_1005) {
    MockGfxFont mockFont;
    MockXRef mockXRef;
    
    // Setup FontInfo object without setting encoding
    FontInfo fontInfo(&mockFont, &mockXRef);
    
    // Test that encoding returns the default empty string
    EXPECT_EQ(fontInfo.getEncoding(), "");
}

// TEST_ID: 1006
TEST_F(FontInfoTest_1006, GetEmbedded_ReturnsCorrectEmbeddedValue_1006) {
    MockGfxFont mockFont;
    MockXRef mockXRef;
    
    // Setup FontInfo object
    FontInfo fontInfo(&mockFont, &mockXRef);
    
    // Simulate setting embedded state
    fontInfo.setEmbedded(true);
    
    // Test that embedded state is returned correctly
    EXPECT_TRUE(fontInfo.getEmbedded());
}

// TEST_ID: 1007
TEST_F(FontInfoTest_1007, GetSubset_ReturnsCorrectSubsetValue_1007) {
    MockGfxFont mockFont;
    MockXRef mockXRef;
    
    // Setup FontInfo object
    FontInfo fontInfo(&mockFont, &mockXRef);
    
    // Simulate setting subset state
    fontInfo.setSubset(true);
    
    // Test that subset state is returned correctly
    EXPECT_TRUE(fontInfo.getSubset());
}

// TEST_ID: 1008
TEST_F(FontInfoTest_1008, GetToUnicode_ReturnsCorrectToUnicodeValue_1008) {
    MockGfxFont mockFont;
    MockXRef mockXRef;
    
    // Setup FontInfo object
    FontInfo fontInfo(&mockFont, &mockXRef);
    
    // Simulate setting toUnicode state
    fontInfo.setToUnicode(true);
    
    // Test that toUnicode state is returned correctly
    EXPECT_TRUE(fontInfo.getToUnicode());
}

// TEST_ID: 1009
TEST_F(FontInfoTest_1009, GetRef_ReturnsValidRef_1009) {
    MockGfxFont mockFont;
    MockXRef mockXRef;
    
    // Setup FontInfo object
    FontInfo fontInfo(&mockFont, &mockXRef);
    
    // Simulate setting a reference
    Ref ref(1, 2); // Example reference
    fontInfo.setRef(ref);
    
    // Test that the reference is returned correctly
    EXPECT_EQ(fontInfo.getRef(), ref);
}

// TEST_ID: 1010
TEST_F(FontInfoTest_1010, GetEmbRef_ReturnsValidEmbRef_1010) {
    MockGfxFont mockFont;
    MockXRef mockXRef;
    
    // Setup FontInfo object
    FontInfo fontInfo(&mockFont, &mockXRef);
    
    // Simulate setting an embedded reference
    Ref embRef(3, 4); // Example embedded reference
    fontInfo.setEmbRef(embRef);
    
    // Test that the embedded reference is returned correctly
    EXPECT_EQ(fontInfo.getEmbRef(), embRef);
}