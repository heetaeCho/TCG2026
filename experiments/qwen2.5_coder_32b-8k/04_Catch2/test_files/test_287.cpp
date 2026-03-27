#include <gtest/gtest.h>

#include "catch2/catch_registry_hub.hpp"

#include "catch2/internal/catch_singletons.hpp"



namespace Catch {

    class IMutableRegistryHubMock : public IMutableRegistryHub {

    public:

        MOCK_METHOD(void, someMethod, (), (override));

    };

}



class RegistryHubSingletonTest_287 : public ::testing::Test {

protected:

    using SingletonImplT = RegistryHub;

    using InterfaceT = IRegistryHub const&;

    using MutableInterfaceT = IMutableRegistryHubMock&;



    void SetUp() override {

        // Reset the singleton instance if needed

    }



    void TearDown() override {

        // Clean up if necessary

    }

};



TEST_F(RegistryHubSingletonTest_287, GetMutableRegistryHub_ReturnsMutableInstance_287) {

    auto& mutableHub = Catch::getMutableRegistryHub();

    EXPECT_TRUE(dynamic_cast<Catch::IMutableRegistryHub*>(&mutableHub) != nullptr);

}



TEST_F(RegistryHubSingletonTest_287, GetMutableRegistryHub_ConsistentAcrossCalls_287) {

    auto& mutableHub1 = Catch::getMutableRegistryHub();

    auto& mutableHub2 = Catch::getMutableRegistryHub();

    EXPECT_EQ(&mutableHub1, &mutableHub2);

}



TEST_F(RegistryHubSingletonTest_287, GetMutableRegistryHub_NotSameAsImmutable_287) {

    auto& immutableHub = Catch::getRegistryHub(); // Assuming getRegistryHub() for comparison

    auto& mutableHub = Catch::getMutableRegistryHub();

    EXPECT_NE(&immutableHub, &mutableHub);

}



// Additional test cases if there are more methods in IMutableRegistryHub to verify

// For example, if there is a method like `void someMethod()` in IMutableRegistryHub



TEST_F(RegistryHubSingletonTest_287, MutableRegistryHub_SomeMethod_DoesNotThrow_287) {

    auto& mutableHub = Catch::getMutableRegistryHub();

    EXPECT_NO_THROW(mutableHub.someMethod());

}



// Assuming there are no other observable methods or behaviors to test based on the given interface
