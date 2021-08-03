// Non-compliant
union u1 {
  int i;
  float f;
};

// Compliant
struct Tagged {
  enum class TYPE { UINT, FLOAT };
  union {
    long l;
    double d;
  };
  TYPE which;
};

// Non-compliant
static union {
  // ..
};

// Compliant
enum class Tag { Integer, Float, String };
struct Variant {
  Tag tag;
  union Value {
    int i;
    float f;
    char *str;
  } value;
};
