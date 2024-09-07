#if !defined(_UTIL_MACROS_H_)
#define _UTIL_MACROS_H_

#if !defined(COUNT_OF)
#define COUNT_OF(a) (sizeof a / sizeof a[0])
#endif // !defined(COUNT_OF)

#define QQQ_PASTE_AB(a,b) a##b
#define QQ_PASTE_AB(a,b) QQQ_PASTE_AB(a,b)
#define PASTE_AB(a,b) QQ_PASTE_AB(a,b)

#endif // !defined(_UTIL_MACROS_H_)
