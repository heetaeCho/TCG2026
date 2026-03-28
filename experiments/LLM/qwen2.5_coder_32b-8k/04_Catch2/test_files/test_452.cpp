#include <gtest/gtest.h>

#include "catch2/catch_session.hpp"

#include "catch2/catch_config.hpp"



class CatchSessionTest : public ::testing::Test {

protected:

    Catch::Session session;

    Catch::ConfigData configData;

};



TEST_F(CatchSessionTest_452, UseConfigData_SetsConfigData_452) {

    // Arrange

    configData.listTests = true;



    // Act

    session.useConfigData(configData);



    // Assert

    EXPECT_EQ(session.configData().listTests, true);

}



TEST_F(CatchSessionTest_452, UseConfigData_ResetsConfigPointer_452) {

    // Arrange

    configData.listTests = true;

    session.useConfigData(configData);



    // Act & Assert

    EXPECT_NE(session.m_config.get(), nullptr); // Assuming m_config is initially set to some value

    session.useConfigData(Catch::ConfigData());

    EXPECT_EQ(session.m_config.get(), nullptr);

}



TEST_F(CatchSessionTest_452, UseConfigData_DoesNotThrowOnValidInput_452) {

    // Arrange

    configData.listTests = true;



    // Act & Assert

    EXPECT_NO_THROW(session.useConfigData(configData));

}
