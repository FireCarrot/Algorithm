// code for foo starts at memory address 0x002717f0
int foo() { return 5; }

int main() {
    // jump to address 0x002717f0
    foo();

    return 0;
}
/* ********************* */

/* Pointers to functions */
// fcnPtr is a pointer to a function that takes no arguments and returns an integer
int (*fcnPtr)();

// To make a const function pointer
int (*const fcnPtr)();

int foo() { return 5; }
int goo() { return 6; }
int main() {
    // fcnPtr points to function foo
    int (*fcnPtr)() = foo;
    // fcnPtr now points to function goo
    fcnPtr = goo;

    // one common mistake is to do this:
    // fcnPtr = goo();

    return 0;
}
/* ********************* */


/* Assigning a function to a function pointer */
// function prototypes
int foo();
double goo();
int hoo(int x);

// function pointer assignments
int (*fcnPtr1)() = foo;
double (*fcnPtr2)() = goo;
int (*fcnPtr3)(int) = hoo;
/* ********************* */


/* Calling a function using a function pointer */
int foo(int x) { return x; }
int main() {
    // assign fcnPtr to function foo
    int (*fcnPtr)(int) = foo;
    // call function foo(5) through fcnPtr.
    (*fcnPtr)(5);
    // via implicit dereference :
    fcnPtr(5);
}
/* ********************* */
