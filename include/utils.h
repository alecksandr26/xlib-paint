#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

#define LOG(msg, ...) do {						\
		char str[1024];						\
		sprintf(str, msg __VA_OPT__(,) __VA_ARGS__);		\
		fprintf(stdout, "[INFO] %s:%i: %s\n", __FILE_NAME__, __LINE__, str); \
		fflush(stdout);						\
	} while (0)

#endif
