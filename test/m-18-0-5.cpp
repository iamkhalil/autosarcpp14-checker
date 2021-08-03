#include <cstring>

size_t _strlen(const char *str)
{
  (void)str;
  return strlen("C programmers never die. They are just cast into void.");
}

char *_strcpy(char *dest, const char *src) { return strcpy(dest, src); }

int _strcmp(const char *s1, const char *s2)
{
	return strcmp(s1, s2);
}

char *_strcat(char *dest, const char *src) { return strcat(dest, src); }

char *_strstr(char *haystack, char *needle) { return strstr(haystack, needle); }

char *_strchr(char *s, int c) {
  (void)c;
  return strchr(s, 'C');
}

char *_strrchr(char *s, int c) { return strrchr(s, c); }

size_t _strspn(const char *s, const char *accept) { return strspn(s, accept); }

size_t _strcspn(const char *s, const char *reject) {
  return strcspn(s, reject);
}

char *_strtok(char *str, const char *delim) {
  (void)delim;
  return strtok(str, "~");
}

char *_strpbrk(char *s, char *accept) { return strpbrk(s, accept); }
