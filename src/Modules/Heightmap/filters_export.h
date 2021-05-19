
#ifndef FILTERS_EXPORT_H
#define FILTERS_EXPORT_H

#ifdef FILTERS_STATIC_DEFINE
#  define FILTERS_EXPORT
#  define FILTERS_NO_EXPORT
#else
#  ifndef FILTERS_EXPORT
#    ifdef filters_EXPORTS
        /* We are building this library */
#      define FILTERS_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define FILTERS_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef FILTERS_NO_EXPORT
#    define FILTERS_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef FILTERS_DEPRECATED
#  define FILTERS_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef FILTERS_DEPRECATED_EXPORT
#  define FILTERS_DEPRECATED_EXPORT FILTERS_EXPORT FILTERS_DEPRECATED
#endif

#ifndef FILTERS_DEPRECATED_NO_EXPORT
#  define FILTERS_DEPRECATED_NO_EXPORT FILTERS_NO_EXPORT FILTERS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef FILTERS_NO_DEPRECATED
#    define FILTERS_NO_DEPRECATED
#  endif
#endif

#endif /* FILTERS_EXPORT_H */
