#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/properties.hpp"

#include <TXMPMeta.hpp>



using namespace Exiv2;



class XmpParserTest : public ::testing::Test {

protected:

    XmpParser parser;

};



TEST_F(XmpParserTest_1316, TerminateCallsUnregisterNs_1316) {

    EXPECT_CALL(*(static_cast<XmpProperties*>(&XmpProperties())), unregisterNs()).Times(1);

    parser.terminate();

}



#ifdef EXV_HAVE_XMP_TOOLKIT

TEST_F(XmpParserTest_1316, TerminateCallsTerminateOnSxmpMetaWhenDefined_1316) {

    EXPECT_CALL(::testing::Mock::NiceMock<SXMPMeta>(), Terminate()).Times(1);

    parser.terminate();

}

#endif



TEST_F(XmpParserTest_1316, InitializeWithFunctionAndDataSetsInitializedTrue_1316) {

    XmpParser::XmpLockFct xmpLockFct = nullptr;

    void* pLockData = nullptr;

    bool result = parser.initialize(xmpLockFct, pLockData);

    EXPECT_TRUE(result);

}



TEST_F(XmpParserTest_1316, DecodeReturnsZeroOnSuccess_1316) {

    XmpData xmpData;

    std::string xmpPacket = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\"> <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"></rdf:RDF> </x:xmpmeta>";

    int result = parser.decode(xmpData, xmpPacket);

    EXPECT_EQ(result, 0);

}



TEST_F(XmpParserTest_1316, EncodeReturnsZeroOnSuccess_1316) {

    XmpData xmpData;

    std::string xmpPacket;

    uint16_t formatFlags = 0;

    uint32_t padding = 4;

    int result = parser.encode(xmpPacket, xmpData, formatFlags, padding);

    EXPECT_EQ(result, 0);

}



TEST_F(XmpParserTest_1316, RegisterNsRegistersNamespace_1316) {

    std::string ns = "http://example.com/ns";

    std::string prefix = "ex";

    parser.registerNs(ns, prefix);

    // No observable effect to verify other than the call itself

}



TEST_F(XmpParserTest_1316, UnregisterNsUnregistersNamespace_1316) {

    std::string ns = "http://example.com/ns";

    parser.unregisterNs(ns);

    // No observable effect to verify other than the call itself

}
