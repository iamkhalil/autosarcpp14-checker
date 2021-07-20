// Run: $ clang++ -fsyntax-only -std=c++14 -Wswitch-bool -Werror -ferror-limit=0

void func(void)
{
        int x = 42;

        switch (x == 42) { // Non-compliant

        }
        switch (x != 42) { // Non-compliant

        }
        switch (x < 42) { // Non-compliant

        }
        switch (x) { // Compliant
                // ...
        }
}
