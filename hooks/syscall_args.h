/* This header is meant as a helper to improve readability of the
 * syscall hooks code. It defines macros for the value of each
 * syscall argument. The file should be included twice each time:
 * once to enable the macro definitions for a specific syscall and
 * once to disable them.
 *
 * Make sure you check how each macro is defined before using them.
 * Sometimes, some minimal processing is done for convenience.
 * E.g. pgoffset argument of mmap2() is converted to bytes offset
 * because that is what we use in practice.
 *
 * Usage example:
 *     #define DEF_SYSCALL_X
 *     #include "syscall_args.h"
 *     void pre_X_hook(syscall_ctx_t *ctx) { ... }
 *     void post_X_hook(syscall_ctx_t *ctx) { ... }
 *     #define UNDEF_SYSCALL_X
 *     #include "syscall_args.h"
 *
 * In addition to argument macros, we also define the _CALL_LOG_STR
 * which merges the arguments in a format suitable to be used with 
 * Pin's LOG() function. As a convention, non-imporant arguments can
 * be rendered as "*".
 */


/**** open(2) *****************************************************/
#ifdef DEF_SYSCALL_OPEN
#define _FD				(int)ctx->ret
#define _PATHNAME		(char *)ctx->arg[SYSCALL_ARG0]
#define _FLAGS			(ctx->nr == __NR_open ? ctx->arg[SYSCALL_ARG1] : O_CREAT|O_WRONLY|O_TRUNC)
#define _MODE			(ctx->nr == __NR_creat ? ctx->arg[SYSCALL_ARG1] : ctx->arg[SYSCALL_ARG2])
#define _CALL_LOG_STR	+ std::string(ctx->nr == __NR_creat ? "creat(" : "open(") + _PATHNAME + ", " + decstr(_FLAGS) + ", " + decstr(_MODE) + ") = " + decstr(_FD)
#undef DEF_SYSCALL_OPEN
#endif

#ifdef UNDEF_SYSCALL_OPEN
#undef _FD
#undef _PATHNAME
#undef _FLAGS
#undef _MODE
#undef _CALL_LOG_STR
#undef UNDEF_SYSCALL_OPEN
#endif

/**** close(2) *****************************************************/
#ifdef DEF_SYSCALL_CLOSE
#define _RET_STATUS		(int)ctx->ret
#define _FD				(int)ctx->arg[SYSCALL_ARG0]
#define _CALL_LOG_STR	"close(" + decstr(_FD) + ") = " + decstr(_RET_STATUS)
#undef DEF_SYSCALL_CLOSE
#endif

#ifdef UNDEF_SYSCALL_CLOSE
#undef _RET_STATUS
#undef _FD
#undef _CALL_LOG_STR
#undef UNDEF_SYSCALL_CLOSE
#endif

/**** mmap2(2) ****************************************************/
#ifdef DEF_SYSCALL_MMAP2
#define _ADDR			(ADDRINT)ctx->ret
#define _ADDR_HINT		(ADDRINT)ctx->arg[SYSCALL_ARG0]
#define _LENGTH			(size_t)ctx->arg[SYSCALL_ARG1]
#define _PROT			(int)ctx->arg[SYSCALL_ARG2]
#define _FLAGS			(int)ctx->arg[SYSCALL_ARG3]
#define _FD				(int)ctx->arg[SYSCALL_ARG4]
#define _FD_OFFSET		((INT64)ctx->arg[SYSCALL_ARG5]*4096)
#define _CALL_LOG_STR	"mmap2(*, " + decstr(_LENGTH) + ", " + "*, *, " + decstr(_FD) + ", " + std::string(((_FLAGS&(MAP_ANONYMOUS|MAP_ANON)) != 0) ? "*" : hexstr(_FD_OFFSET)) + ") = " + StringFromAddrint(_ADDR)
#undef DEF_SYSCALL_MMAP2
#endif

#ifdef UNDEF_SYSCALL_MMAP2
#undef _ADDR
#undef _ADDR_HINT
#undef _LENGTH
#undef _PROT
#undef _FLAGS
#undef _FD
#undef _FD_OFFSET
#undef _CALL_LOG_STR
#undef UNDEF_SYSCALL_MMAP2
#endif


/**** munmap(2) ***************************************************/
#ifdef DEF_SYSCALL_MUNMAP
#define _RET_STATUS		ctx->ret
#define _ADDR			(ADDRINT)ctx->arg[SYSCALL_ARG0]
#define _LENGTH			(size_t)ctx->arg[SYSCALL_ARG1]
#define _CALL_LOG_STR	"munmap(" + StringFromAddrint(_ADDR) + ", " + decstr(_LENGTH) + ") = " + decstr(_RET_STATUS)
#undef DEF_SYSCALL_MUNMAP
#endif

#ifdef UNDEF_SYSCALL_MUNMAP
#undef _RET_STATUS
#undef _ADDR
#undef _LENGTH
#undef _CALL_LOG_STR
#undef UNDEF_SYSCALL_MUNMAP
#endif


/**** read(2) *****************************************************/
#ifdef DEF_SYSCALL_READ
#define _RET_STATUS		(int)ctx->ret
#define _FD				(int)ctx->arg[SYSCALL_ARG0]
#define _CALL_LOG_STR	"close(" + decstr(_FD) + ") = " + decstr(_RET_STATUS)
#undef DEF_SYSCALL_READ
#endif

#ifdef UNDEF_SYSCALL_READ
#undef _RET_STATUS
#undef _FD
#undef _CALL_LOG_STR
#undef UNDEF_SYSCALL_READ
#endif


/**** write(2) ****************************************************/
#ifdef DEF_SYSCALL_WRITE
#define _N_WRITTEN		(ssize_t)ctx->ret
#define _FD				(int)ctx->arg[SYSCALL_ARG0]
#define _BUF			(ADDRINT)ctx->arg[SYSCALL_ARG1]
#define _COUNT			(size_t)ctx->arg[SYSCALL_ARG2]
#define _CALL_LOG_STR	"write(" + decstr(_FD) + ", " + StringFromAddrint(_BUF) + ", " + decstr(_COUNT) + ") = " + decstr(_N_WRITTEN)
#undef DEF_SYSCALL_WRITE
#endif

#ifdef UNDEF_SYSCALL_WRITE
#undef _N_WRITTEN
#undef _FD
#undef _BUF
#undef _COUNT
#undef _CALL_LOG_STR
#undef UNDEF_SYSCALL_WRITE
#endif
