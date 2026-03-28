// File: ./TestProjects/re2/util/pcre_dtor_test.cc

#include "gtest/gtest.h"
#include "TestProjects/re2/util/pcre.h"

using re2::PCRE;

//
// The goal is to exercise ~PCRE(), which (per the provided snippet) frees
// internal compiled regex pointers and conditionally deletes an error string.
// Treat the class as a black box and only verify behavior visible via the
// public interface: successful construction within a scope and safe teardown.
//

// Creates and destroys via const char* constructor.
TEST(PCREDestructorTest_188, Destroy_WithCStringCtor_188) {
  // Scope ensures ~PCRE is invoked when leaving.
  {
    PCRE re("a");  // simple literal; we don't assert internal state
    // No further observable effects required; success == no crash / UB.
  }
  SUCCEED();  // Explicitly marks the test as passed if no failure occurs.
}

// Creates and destroys via std::string constructor.
TEST(PCREDestructorTest_188, Destroy_WithStdStringCtor_188) {
  {
    std::string pattern = "abc";
    PCRE re(pattern);
  }
  SUCCEED();
}

// Creates and destroys multiple instances in sequence to exercise repeated cleanup.
TEST(PCREDestructorTest_188, Destroy_MultipleInstancesSequentially_188) {
  {
    PCRE re1("x");
    PCRE re2("y");
    PCRE re3("z");
    // All three go out of scope together; destructor runs for each.
  }
  SUCCEED();
}

// Creates and destroys within nested scopes to mimic varied lifetimes.
TEST(PCREDestructorTest_188, Destroy_NestedScopes_188) {
  {
    PCRE outer("outer");
    {
      PCRE inner("inner");
      // inner destroyed first
    }
    // outer destroyed next
  }
  SUCCEED();
}

// Ensures destruction via dynamic allocation path also safely invokes ~PCRE.
TEST(PCREDestructorTest_188, Destroy_ViaDelete_188) {
  PCRE* re = new PCRE("dyn");
  // No observable effects to assert; just ensure delete is safe.
  delete re;
  SUCCEED();
}
