#ifndef BASE_TL_BASE_H
#define BASE_TL_BASE_H

template<class T>
inline void swap(T &a, T &b)
{
	T c = b;
	b = a;
	a = c;
}

#endif
