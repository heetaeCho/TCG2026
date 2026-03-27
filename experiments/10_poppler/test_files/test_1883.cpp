#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming GfxLCMSProfilePtr is a smart pointer like std::shared_ptr or std::unique_ptr

template<typename T>

class GfxLCMSProfilePtr {

public:

    GfxLCMSProfilePtr() : ptr(nullptr) {}

    GfxLCMSProfilePtr(T* p, void(*deleter)(T*)) : ptr(p), deleter(deleter) {}

    ~GfxLCMSProfilePtr() { if (ptr && deleter) deleter(ptr); }

private:

    T* ptr;

    void(*deleter)(void*);

};



extern "C" {

    void lcmsprofiledeleter(void *profile);

}



// Mock the lcmsprofiledeleter function

class MockLCMSProfileDeleter {

public:

    MOCK_METHOD1(Call, void(void*));

};



MockLCMSProfileDeleter* mock_deleter = nullptr;



extern "C" {

    void lcmsprofiledeleter(void *profile) {

        if (mock_deleter) {

            mock_deleter->Call(profile);

        }

    }

}



void* create_mock_profile() {

    return new int(42); // Just a placeholder for the profile

}



class GfxLCMSProfilePtrTest_1883 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_deleter = new MockLCMSProfileDeleter();

    }



    void TearDown() override {

        delete mock_deleter;

        mock_deleter = nullptr;

    }

};



TEST_F(GfxLCMSProfilePtrTest_1883, CreateWithNullptr_1883) {

    GfxLCMSProfilePtr<void> profilePtr = make_GfxLCMSProfilePtr(nullptr);

    EXPECT_EQ(profilePtr, GfxLCMSProfilePtr<void>());

}



TEST_F(GfxLCMSProfilePtrTest_1883, CreateWithValidProfile_1883) {

    void* mock_profile = create_mock_profile();

    EXPECT_CALL(*mock_deleter, Call(mock_profile)).Times(1);

    GfxLCMSProfilePtr<void> profilePtr = make_GfxLCMSProfilePtr(mock_profile);

}



TEST_F(GfxLCMSProfilePtrTest_1883, DeleterCalledOnceOnDestruction_1883) {

    void* mock_profile = create_mock_profile();

    EXPECT_CALL(*mock_deleter, Call(mock_profile)).Times(1);

    {

        GfxLCMSProfilePtr<void> profilePtr = make_GfxLCMSProfilePtr(mock_profile);

    } // Destructor should be called here

}
