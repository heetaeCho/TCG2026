#include <gtest/gtest.h>

#include "JBIG2Stream.h"

#include <memory>



class JBIG2StreamTest_1482 : public ::testing::Test {

protected:

    std::unique_ptr<Object> globalsStream;

    Ref globalsStreamRef;



    void SetUp() override {

        globalsStream = std::make_unique<Object>();

        // Initialize other necessary members if needed

    }



    JBIG2Stream* createJBIG2Stream() {

        return new JBIG2Stream(0, std::move(*globalsStream), &globalsStreamRef);

    }

};



TEST_F(JBIG2StreamTest_1482, GetGlobalsStream_ReturnsNonNullPointer_1482) {

    auto stream = createJBIG2Stream();

    EXPECT_NE(stream->getGlobalsStream(), nullptr);

    delete stream;

}



TEST_F(JBIG2StreamTest_1482, GetGlobalsStream_ReturnsSameObject_1482) {

    auto stream = createJBIG2Stream();

    Object* globalsStreamPtr1 = stream->getGlobalsStream();

    Object* globalsStreamPtr2 = stream->getGlobalsStream();

    EXPECT_EQ(globalsStreamPtr1, globalsStreamPtr2);

    delete stream;

}



TEST_F(JBIG2StreamTest_1482, GetGlobalsStreamRef_ReturnsNonNullPointer_1482) {

    auto stream = createJBIG2Stream();

    EXPECT_NE(stream->getGlobalsStreamRef(), nullptr);

    delete stream;

}



// Additional tests can be added based on observable behavior and interface

```


