#ifdef GEOFRAME_EXPORT
#define GEOFRAME_API __declspec(dllexport)
#else
#define GEOFRAME_API __declspec(dllimport)
#endif

#ifdef GEOFRAME_INLINE
#define GEOFRAME_API GEOFRAME_API inline
#endif
