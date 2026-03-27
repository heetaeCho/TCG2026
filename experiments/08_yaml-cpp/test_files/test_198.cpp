#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/iterator.h"



using namespace YAML::detail;



class IteratorBaseProxyTest_198 : public ::testing::Test {

protected:

    using V = int; // Assuming a simple type for V, as it's not specified in the interface.

    proxy p;



    IteratorBaseProxyTest_198() : p(V(42)) {}

};



TEST_F(IteratorBaseProxyTest_198, OperatorArrowReturnsAddressOfMRef_198) {

    EXPECT_EQ(p.operator->(), &p.m_ref);

}



TEST_F(IteratorBaseProxyTest_198, OperatorVPtrReturnsAddressOfMRef_198) {

    EXPECT_EQ(static_cast<V*>(p), &p.m_ref);

}



TEST_F(IteratorBaseProxyTest_198, ConstructorInitializesMRef_198) {

    EXPECT_EQ(p.m_ref, V(42));

}
