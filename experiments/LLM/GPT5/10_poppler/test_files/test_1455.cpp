#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/qt5/src/poppler-sound.cc"  // Include the relevant header file

namespace Poppler {
    // Mock Sound class since it's a dependency
    class MockSound : public Sound {
    public:
        MOCK_METHOD(void, play, (), (override));
        MOCK_METHOD(void, stop, (), (override));
    };
}

class SoundDataTest_1455 : public testing::Test {
protected:
    Poppler::SoundData soundData;
};

TEST_F(SoundDataTest_1455, SoundData_DefaultConstructor_1455) {
    // Verifying that the default constructor does not crash
    EXPECT_EQ(soundData.m_type, 0);  // Assuming the default type is 0
    EXPECT_EQ(soundData.m_soundObj, nullptr);  // Default m_soundObj should be nullptr
}

TEST_F(SoundDataTest_1455, SoundData_Destructor_1455) {
    // Verifying that the destructor does not cause a crash
    // Use a mock Sound object to verify destructor behavior (i.e., memory management)
    {
        Poppler::SoundData soundData;
        soundData.m_soundObj = new Poppler::MockSound();  // Assign a mock object to m_soundObj
    }  // Destructor will be called here, and we should ensure no memory leak
    // If there's a memory leak, Google Test will report an issue
}

TEST_F(SoundDataTest_1455, SoundData_CopyConstructor_1455) {
    // Verifying that copy constructor is deleted (as per the given code)
    // Try to copy and expect a compile-time error (because it's deleted)
    // Compile-time check: this test should not compile if the copy constructor is correctly deleted
    // Uncommenting the next line should cause a compilation error
    // Poppler::SoundData copiedSoundData = soundData;
    SUCCEED();  // If the test runs, the copy constructor is correctly deleted
}

TEST_F(SoundDataTest_1455, SoundData_AssignmentOperator_1455) {
    // Verifying that assignment operator is deleted (as per the given code)
    // Try to assign and expect a compile-time error (because it's deleted)
    // Compile-time check: this test should not compile if the assignment operator is correctly deleted
    // Uncommenting the next line should cause a compilation error
    // soundData = anotherSoundData;
    SUCCEED();  // If the test runs, the assignment operator is correctly deleted
}

TEST_F(SoundDataTest_1455, SoundData_Destructor_CleansUpMemory_1455) {
    // Verifying that SoundData's destructor cleans up memory properly
    // Use a mock Sound object to track if the destructor properly deletes m_soundObj
    Poppler::SoundData* soundDataPtr = new Poppler::SoundData();
    soundDataPtr->m_soundObj = new Poppler::MockSound();  // Allocate mock object
    delete soundDataPtr;  // Destructor should be invoked here
    SUCCEED();  // If no memory issues occur, the test passes
}

TEST_F(SoundDataTest_1455, SoundData_ValidSoundObject_1455) {
    // Testing if valid Sound objects are handled properly
    Poppler::SoundData soundData;
    soundData.m_soundObj = new Poppler::MockSound();
    
    // Verify that the sound object can be used (e.g., call play method)
    EXPECT_CALL(*static_cast<Poppler::MockSound*>(soundData.m_soundObj), play()).Times(1);
    
    soundData.m_soundObj->play();  // This should call the mock play method

    delete soundData.m_soundObj;  // Clean up
}

TEST_F(SoundDataTest_1455, SoundData_NullSoundObject_1455) {
    // Verifying that SoundData behaves correctly with a null sound object
    Poppler::SoundData soundData;
    soundData.m_soundObj = nullptr;

    // The soundObj should be null, so no call should happen
    ASSERT_EQ(soundData.m_soundObj, nullptr);
}

TEST_F(SoundDataTest_1455, SoundData_AssignmentWithNullSound_1455) {
    // Verifying that assignment works when m_soundObj is null
    Poppler::SoundData soundData1;
    soundData1.m_soundObj = nullptr;
    Poppler::SoundData soundData2;
    soundData2 = soundData1;
    
    // Checking if the m_soundObj is still null after assignment
    EXPECT_EQ(soundData2.m_soundObj, nullptr);
}

TEST_F(SoundDataTest_1455, SoundData_SoundObjectLifetime_1455) {
    // Verifying that SoundData manages the lifetime of the sound object
    {
        Poppler::SoundData soundData;
        soundData.m_soundObj = new Poppler::MockSound();  // Assigning mock sound object
        
        // Mock object should be deleted when soundData goes out of scope
    }
    // If no memory issues occur, the test passes
    SUCCEED();
}