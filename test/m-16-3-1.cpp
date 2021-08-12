// Non-compliant
#define NonCompliant(a, b)  # a ## b
// Compliant
#define Stringfy(a) #a
#define Compliant(a, b)  Stringfy(a##b)
