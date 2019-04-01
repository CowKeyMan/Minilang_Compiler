// a method to get size of an array
template <typename T,unsigned S>
inline unsigned arraysize(const T (&v)[S]) { return S; }

void cleanup(); // method to be called at exit (example: free up pointers)