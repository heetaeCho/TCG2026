#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/ninja/src/jobserver.h"



using ::testing::_;

using ::testing::Return;

using ::testing::Invoke;



class JobserverClientMock : public Jobserver::Client {

public:

    MOCK_METHOD(Slot, TryAcquire, (), (override));

    MOCK_METHOD(void, Release, (Slot slot), (override));

};



class JobserverTest_29 : public ::testing::Test {

protected:

    std::unique_ptr<Jobserver::Client> client;



    void SetUp() override {

        Config config;

        std::string error;

        client = Jobserver::Client::Create(config, &error);

    }

};



TEST_F(JobserverTest_29, TryAcquireReturnsValidSlot_29) {

    Slot slot;

    EXPECT_CALL(*client, TryAcquire()).WillOnce(Return(slot));

    ASSERT_EQ(client->TryAcquire(), slot);

}



TEST_F(JobserverTest_29, ReleaseDoesNotThrowOnValidSlot_29) {

    Slot slot;

    EXPECT_CALL(*client, Release(slot)).Times(1);

    client->Release(slot);

}



TEST_F(JobserverTest_29, TryAcquireConsistentBehavior_29) {

    Slot slot1 = client->TryAcquire();

    Slot slot2 = client->TryAcquire();

    ASSERT_NE(slot1, slot2);  // Assuming slots are unique

}



TEST_F(JobserverTest_29, ReleaseCalledWithSameSlotTwice_29) {

    Slot slot = client->TryAcquire();

    EXPECT_CALL(*client, Release(slot)).Times(2);

    client->Release(slot);

    client->Release(slot);

}
