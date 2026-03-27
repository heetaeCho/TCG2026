#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_registrars.hpp"

#include <string>



using namespace Catch;



// Mocking the Detail namespace to capture calls to registerReporterImpl

namespace Detail {

    class MockDetail {

    public:

        MOCK_STATIC(void, registerReporterImpl(const std::string&, std::unique_ptr<ReporterFactoryBase>));

    };

}



TEST(ReporterRegistrarTest_1083, ConstructorRegistersReporter_1083) {

    // Arrange

    EXPECT_CALL(Detail::MockDetail::registerReporterImpl, 

                testing::_(testing::_, testing::_));



    // Act

    ReporterRegistrar<ReporterFactoryBase> registrar("test_reporter");



    // Assert is handled by the mock expectation

}



TEST(ReporterRegistrarTest_1083, ConstructorHandlesEmptyName_1083) {

    // Arrange

    EXPECT_CALL(Detail::MockDetail::registerReporterImpl, 

                testing::(_, testing::_));



    // Act

    ReporterRegistrar<ReporterFactoryBase> registrar("");



    // Assert is handled by the mock expectation

}



TEST(ReporterRegistrarTest_1083, ConstructorHandlesLongName_1083) {

    // Arrange

    std::string long_name(1024, 'a'); // Example of a long name

    EXPECT_CALL(Detail::MockDetail::registerReporterImpl, 

                testing::(_, testing::_));



    // Act

    ReporterRegistrar<ReporterFactoryBase> registrar(long_name);



    // Assert is handled by the mock expectation

}

```


