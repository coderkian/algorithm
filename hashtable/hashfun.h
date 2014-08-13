
template <typename T> struct  hash { };

inline size_t
stringkey(const char* s)
{
	unsigned long h = 0;
	for ( ; *s; ++s)
		h = 5*h + *s;
	return size_t(h);
}

template <> struct hash<const char*>
{
  size_t operator()(const char* x) const { return stringkey(x); }
};

template <> struct hash<char*>
{
  size_t operator()(char* x) const { return stringkey(x); }
};
template <> struct hash<int>
{
  size_t operator()(int x) const { return x; }
};
