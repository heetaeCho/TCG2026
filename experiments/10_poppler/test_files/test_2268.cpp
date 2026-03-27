#include <gtest/gtest.h>

#include "poppler-attachment.h"



// Assuming PopplerAttachmentClass is a GObject-derived class and we can create instances of it for testing.

class PopplerAttachmentTest_2268 : public ::testing::Test {

protected:

    // Setup code here if needed, though there's not much setup required given the current interface

};



TEST_F(PopplerAttachmentTest_2268, FinalizeFunctionIsSet_2268) {

    PopplerAttachmentClass klass;

    poppler_attachment_class_init(&klass);

    

    EXPECT_EQ(klass.finalize, &poppler_attachment_finalize);

}



// Additional test cases are not possible with the current provided interface and constraints.

```


