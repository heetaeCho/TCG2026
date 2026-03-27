#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/catch_registry_hub.cpp"



using namespace Catch;



class RegistryHubTest_286 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be used to initialize objects if needed.

    }



    void TearDown() override {

        // Cleanup can be done here if necessary.

    }

};



TEST_F(RegistryHubTest_286, GetRegistryHub_ReturnsConsistentInstance_286) {

    auto& hub1 = getRegistryHub();

    auto& hub2 = getRegistryHub();

    EXPECT_EQ(&hub1, &hub2);

}



// Since the interface provided is very limited and it's a singleton,

// there are no boundary conditions or exceptional cases to test directly.

// However, we can still ensure that the function behaves correctly under normal conditions.



TEST_F(RegistryHubTest_286, GetRegistryHub_IsConstReference_286) {

    const IRegistryHub& hub = getRegistryHub();

    EXPECT_TRUE((std::is_same<decltype(hub), const IRegistryHub&>::value));

}
