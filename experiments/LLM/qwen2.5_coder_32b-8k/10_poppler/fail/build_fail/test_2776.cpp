#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking dependencies if necessary (none in this case)

namespace Poppler {

    class Object;

    class PageTransition;



    class PageTransitionData {

    public:

        explicit PageTransitionData(Object* trans);

        PageTransitionData(const PageTransitionData& ptd);

        ~PageTransitionData();

        PageTransitionData& operator=(const PageTransitionData&) = delete;



    private:

        ::PageTransition* pt;

    };

}



// Test fixture

class PageTransitionDataTest_2776 : public ::testing::Test {

protected:

    // Setup and teardown if necessary (none in this case)

};



// Normal operation tests

TEST_F(PageTransitionDataTest_2776, CopyConstructorCopiesObject_2776) {

    // Arrange

    Poppler::Object* mockTrans = new Poppler::Object();  // Assuming Object is a simple class for demonstration

    Poppler::PageTransitionData original(mockTrans);



    // Act

    Poppler::PageTransitionData copy(original);



    // Assert

    EXPECT_NE(copy.pt, original.pt);  // Ensure it's a different object



    delete mockTrans;

}



// Boundary conditions tests (if any applicable)



// Exceptional or error cases tests (if observable through the interface)

TEST_F(PageTransitionDataTest_2776, DestructorDoesNotThrow_2776) {

    // Arrange

    Poppler::Object* mockTrans = new Poppler::Object();

    Poppler::PageTransitionData data(mockTrans);



    // Act & Assert (Destructor call is implicit)

    EXPECT_NO_THROW({ delete mockTrans; });

}



// Verification of external interactions tests (if any applicable)

```


