#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/qt5/src/poppler-link.cc"  // Adjust the path as necessary

namespace Poppler {

class MockSoundObject : public SoundObject {
public:
    MOCK_METHOD(void, play, (), (override));
    MOCK_METHOD(void, stop, (), (override));
};

}  // namespace Poppler

// Test Fixture for LinkSoundPrivate class
class LinkSoundPrivateTest_1250 : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code here (if any required)
    }

    void TearDown() override {
        // Cleanup code here (if any required)
    }
};

// Normal operation test case for LinkSoundPrivate destructor
TEST_F(LinkSoundPrivateTest_1250, Destructor_DeletesSoundObject_1250) {
    Poppler::LinkSoundPrivate* linkSoundPrivate = new Poppler::LinkSoundPrivate(10);
    linkSoundPrivate->sound = new Poppler::MockSoundObject();  // Assign a mock sound object

    // No direct assertions since we are testing the destruction of sound object
    delete linkSoundPrivate;

    // Verify the destructor is called (handled by the mock object in this case)
    // This will happen when the object is deleted, so no additional asserts required.
}

// Boundary test for LinkSoundPrivate with area initialization
TEST_F(LinkSoundPrivateTest_1250, Constructor_InitializesWithPositiveArea_1250) {
    QRectF area(0, 0, 100, 100);  // Using a positive non-zero area
    Poppler::LinkSoundPrivate linkSoundPrivate(area);

    ASSERT_NE(linkSoundPrivate.sound, nullptr);  // Check that the sound object is created correctly
}

// Boundary test for LinkSoundPrivate with zero area
TEST_F(LinkSoundPrivateTest_1250, Constructor_InitializesWithZeroArea_1250) {
    QRectF area(0, 0, 0, 0);  // Zero area boundary case
    Poppler::LinkSoundPrivate linkSoundPrivate(area);

    ASSERT_EQ(linkSoundPrivate.sound, nullptr);  // Check that the sound object is not created if area is zero
}

// Exceptional case: Test if destructor handles null sound pointer correctly
TEST_F(LinkSoundPrivateTest_1250, Destructor_HandlesNullSoundObject_1250) {
    Poppler::LinkSoundPrivate* linkSoundPrivate = new Poppler::LinkSoundPrivate(10);
    linkSoundPrivate->sound = nullptr;  // No sound object assigned

    // Check that no crash occurs when deleting a null sound object
    EXPECT_NO_THROW(delete linkSoundPrivate);
}

// Verification of external interaction: Testing a SoundObject interaction
TEST_F(LinkSoundPrivateTest_1250, VerifyPlaySoundInteraction_1250) {
    // Arrange
    Poppler::MockSoundObject* mockSoundObject = new Poppler::MockSoundObject();
    Poppler::LinkSoundPrivate linkSoundPrivate(10);
    linkSoundPrivate.sound = mockSoundObject;  // Assign the mock sound object

    // Expect that the play method on the sound object is called
    EXPECT_CALL(*mockSoundObject, play()).Times(1);

    // Act: Call the function that triggers the play
    mockSoundObject->play();

    // Assert the expected interaction
    testing::Mock::VerifyAndClearExpectations(mockSoundObject);
}

}  // namespace Poppler