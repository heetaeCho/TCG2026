#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <QString>

#include <GooString.h>

#include "NSSCryptoSignBackend.h"



namespace Poppler {

    void setNSSDir(const QString &path);

}



using namespace testing;



class NSSSignatureConfigurationMock : public ::testing::Test {

protected:

    NiceMock<MockFunction<void(const GooString&)>> mockSetNSSDir;



    NSSSignatureConfigurationMock() {

        EXPECT_CALL(mockSetNSSDir, Call(_)).Times(AnyNumber());

    }



    virtual void SetUp() override {

        ON_CALL(*this->mockSetNSSDir, Call(_))

            .WillByDefault([](const GooString& nssDir) {

                NSSSignatureConfiguration::setNSSDir(nssDir);

            });

    }

};



TEST_F(NSSSignatureConfigurationMock_1379, SetNSSDirWithValidPath_1379) {

    QString validPath = "/path/to/nssdir";

    EXPECT_CALL(*this->mockSetNSSDir, Call(_)).Times(1);



    Poppler::setNSSDir(validPath);

}



TEST_F(NSSSignatureConfigurationMock_1379, SetNSSDirWithEmptyPath_1379) {

    QString emptyPath = "";

    EXPECT_CALL(*this->mockSetNSSDir, Call(_)).Times(0);



    Poppler::setNSSDir(emptyPath);

}



TEST_F(NSSSignatureConfigurationMock_1379, SetNSSDirWithNullPath_1379) {

    QString nullPath;

    EXPECT_CALL(*this->mockSetNSSDir, Call(_)).Times(0);



    Poppler::setNSSDir(nullPath);

}
