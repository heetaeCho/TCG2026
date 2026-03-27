#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/properties.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class XmpPropertiesTest_1244 : public ::testing::Test {

protected:

    XmpProperties xmpProperties;

};



TEST_F(XmpPropertiesTest_1244, RegisterNs_NormalOperation_1244) {

    std::string ns = "http://example.com/";

    std::string prefix = "ex";

    EXPECT_NO_THROW(xmpProperties.registerNs(ns, prefix));

}



TEST_F(XmpPropertiesTest_1244, RegisterNs_BoundaryNoTrailingSlash_1244) {

    std::string ns = "http://example.com";

    std::string prefix = "ex";

    EXPECT_NO_THROW(xmpProperties.registerNs(ns, prefix));

}



TEST_F(XmpPropertiesTest_1244, RegisterNs_UpdateNamespaceUri_1244) {

    std::string ns1 = "http://example.com/";

    std::string ns2 = "http://new-example.com/";

    std::string prefix = "ex";

    

    EXPECT_NO_THROW(xmpProperties.registerNs(ns1, prefix));

    EXPECT_NO_THROW(xmpProperties.registerNs(ns2, prefix));

}



TEST_F(XmpPropertiesTest_1244, RegisterNs_EmptyNamespace_1244) {

    std::string ns = "";

    std::string prefix = "ex";

    EXPECT_THROW(xmpProperties.registerNs(ns, prefix), Exiv2::Error);

}



TEST_F(XmpPropertiesTest_1244, RegisterNs_EmptyPrefix_1244) {

    std::string ns = "http://example.com/";

    std::string prefix = "";

    EXPECT_THROW(xmpProperties.registerNs(ns, prefix), Exiv2::Error);

}



TEST_F(XmpPropertiesTest_1244, RegisterNs_LogWarningOnUpdate_1244) {

    std::string ns1 = "http://example.com/";

    std::string ns2 = "http://new-example.com/";

    std::string prefix = "ex";



    testing::StrictMock<testing::MockFunction<void(int, const char*)>> mockHandler;

    LogMsg::setHandler([&mockHandler](int level, const char* msg) {

        mockHandler.Call(level, msg);

    });



    EXPECT_CALL(mockHandler, Call(LogMsg::warn, testing::_)).Times(1);



    xmpProperties.registerNs(ns1, prefix);

    xmpProperties.registerNs(ns2, prefix);

}
