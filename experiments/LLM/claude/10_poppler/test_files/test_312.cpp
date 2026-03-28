#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"

// Helper to create a Dict and Object for LinkRendition construction
// We need to construct LinkRendition objects through valid Object parameters

class LinkRenditionTest_312 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a LinkRendition constructed with a null/empty object reports not ok
TEST_F(LinkRenditionTest_312, ConstructWithNullObject_IsNotOk_312) {
    Object obj;
    LinkRendition rendition(&obj);
    // An empty/null object should likely result in an invalid LinkRendition
    // We test isOk() to see if it returns false
    EXPECT_FALSE(rendition.isOk());
}

// Test that getKind returns actionRendition
TEST_F(LinkRenditionTest_312, GetKindReturnsRendition_312) {
    Object obj;
    LinkRendition rendition(&obj);
    EXPECT_EQ(rendition.getKind(), actionRendition);
}

// Test getOperation on a default/invalid rendition
TEST_F(LinkRenditionTest_312, GetOperationOnInvalidRendition_312) {
    Object obj;
    LinkRendition rendition(&obj);
    // Just verify it returns a valid RenditionOperation enum value without crashing
    RenditionOperation op = rendition.getOperation();
    (void)op; // No crash is the success criterion
}

// Test hasScreenAnnot on invalid rendition
TEST_F(LinkRenditionTest_312, HasScreenAnnotOnInvalidRendition_312) {
    Object obj;
    LinkRendition rendition(&obj);
    // Invalid rendition should not have a screen annotation
    EXPECT_FALSE(rendition.hasScreenAnnot());
}

// Test getMedia on invalid rendition returns nullptr
TEST_F(LinkRenditionTest_312, GetMediaOnInvalidRendition_312) {
    Object obj;
    LinkRendition rendition(&obj);
    const MediaRendition *media = rendition.getMedia();
    EXPECT_EQ(media, nullptr);
}

// Test getScript on invalid rendition returns empty string
TEST_F(LinkRenditionTest_312, GetScriptOnInvalidRendition_312) {
    Object obj;
    LinkRendition rendition(&obj);
    const std::string &script = rendition.getScript();
    EXPECT_TRUE(script.empty());
}

// Test construction with a dictionary containing rendition info
TEST_F(LinkRenditionTest_312, ConstructWithDictContainingOP_312) {
    // Build an Object dict that has "OP" key for operation
    Object obj = Object(new Dict(nullptr));
    
    // Add OP entry (operation code)
    // RenditionOperation values: 0=Play, 1=Stop, 2=Pause, 3=Resume
    obj.dictAdd("OP", Object(0));
    
    LinkRendition rendition(&obj);
    
    // The operation should reflect what was set
    RenditionOperation op = rendition.getOperation();
    // We just verify it doesn't crash and returns a value
    (void)op;
}

// Test construction with a dictionary containing JS entry
TEST_F(LinkRenditionTest_312, ConstructWithDictContainingJS_312) {
    Object obj = Object(new Dict(nullptr));
    
    // Add a JS string entry
    obj.dictAdd("JS", Object(new GooString("alert('hello');")));
    
    LinkRendition rendition(&obj);
    
    const std::string &script = rendition.getScript();
    // If JS was properly parsed, script should contain the javascript
    if (rendition.isOk()) {
        EXPECT_FALSE(script.empty());
    }
}

// Test construction with AN (screen annotation reference)
TEST_F(LinkRenditionTest_312, ConstructWithScreenAnnotRef_312) {
    Object obj = Object(new Dict(nullptr));
    
    // Add AN as a reference - screen annotation
    obj.dictAdd("AN", Object(42, 0)); // ref with num=42, gen=0
    obj.dictAdd("OP", Object(0));
    
    LinkRendition rendition(&obj);
    
    if (rendition.isOk()) {
        EXPECT_TRUE(rendition.hasScreenAnnot());
        Ref ref = rendition.getScreenAnnot();
        EXPECT_EQ(ref.num, 42);
        EXPECT_EQ(ref.gen, 0);
    }
}

// Test multiple operation values
TEST_F(LinkRenditionTest_312, OperationValues_312) {
    for (int opVal = 0; opVal <= 4; opVal++) {
        Object obj = Object(new Dict(nullptr));
        obj.dictAdd("OP", Object(opVal));
        obj.dictAdd("AN", Object(1, 0));
        
        LinkRendition rendition(&obj);
        RenditionOperation op = rendition.getOperation();
        // Just ensure no crash for each operation value
        (void)op;
    }
}
