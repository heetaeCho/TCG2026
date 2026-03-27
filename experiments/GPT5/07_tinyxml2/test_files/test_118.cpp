#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "tinyxml2.h"

using namespace tinyxml2;
using ::testing::AtLeast;
using ::testing::Exactly;

// Mock class to verify PopDepth is called
class MockXMLDocument : public XMLDocument {
public:
    MOCK_METHOD(void, PopDepth, (), ());  // Mock the method called by DepthTracker
};

TEST(DepthTrackerTest_118, DestructorCallsPopDepth_118) {
    // Arrange
    MockXMLDocument mockDoc;

    // Expect PopDepth to be called exactly once when DepthTracker is destroyed
    EXPECT_CALL(mockDoc, PopDepth())
        .Times(Exactly(1));

    // Act
    {
        DepthTracker tracker(&mockDoc);
        // tracker goes out of scope at end of block -> destructor called
    }

    // Assert
    // Expectations are automatically verified at the end of the test
}

TEST(DepthTrackerTest_118, ConstructorStoresDocumentPointer_118) {
    // Arrange
    MockXMLDocument mockDoc;

    // Act
    DepthTracker* tracker = new DepthTracker(&mockDoc);

    // Assert
    // Since we cannot access private members, just verify no crash occurs
    SUCCEED() << "Constructor executed without crashing.";

    delete tracker; // Cleanup, also triggers PopDepth
}

TEST(DepthTrackerTest_118, MultipleDepthTrackersCallPopDepth_118) {
    // Arrange
    MockXMLDocument mockDoc;

    // Expect PopDepth to be called twice for two DepthTracker instances
    EXPECT_CALL(mockDoc, PopDepth())
        .Times(Exactly(2));

    // Act
    {
        DepthTracker tracker1(&mockDoc);
        DepthTracker tracker2(&mockDoc);
    } // Both destructors called here

    // Assert
    // Verified by EXPECT_CALL
}
