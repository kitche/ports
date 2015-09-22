/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20141006

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 28 "parse.y"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/queue.h>
#include <sys/tree.h>
#include <sys/ioctl.h>
#include <sys/sockio.h>
#include <sys/time.h>

#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <ctype.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <ifaddrs.h>
#include <syslog.h>

#include "httpd.h"
#include "http.h"

#ifdef __FreeBSD__
#include <stdlib.h>
#endif

TAILQ_HEAD(files, file)		 files = TAILQ_HEAD_INITIALIZER(files);
static struct file {
	TAILQ_ENTRY(file)	 entry;
	FILE			*stream;
	char			*name;
	int			 lineno;
	int			 errors;
} *file, *topfile;
struct file	*pushfile(const char *, int);
int		 popfile(void);
int		 check_file_secrecy(int, const char *);
int		 yyparse(void);
int		 yylex(void);
int		 yyerror(const char *, ...)
    __attribute__((__format__ (printf, 1, 2)))
    __attribute__((__nonnull__ (1)));
int		 kw_cmp(const void *, const void *);
int		 lookup(char *);
int		 lgetc(int);
int		 lungetc(int);
int		 findeol(void);

TAILQ_HEAD(symhead, sym)	 symhead = TAILQ_HEAD_INITIALIZER(symhead);
struct sym {
	TAILQ_ENTRY(sym)	 entry;
	int			 used;
	int			 persist;
	char			*nam;
	char			*val;
};
int		 symset(const char *, const char *, int);
char		*symget(const char *);

struct httpd		*conf = NULL;
static int		 errors = 0;
static int		 loadcfg = 0;
uint32_t		 last_server_id = 0;
uint32_t		 last_auth_id = 0;

static struct server	*srv = NULL, *parentsrv = NULL;
static struct server_config *srv_conf = NULL;
struct serverlist	 servers;
struct media_type	 media;

struct address	*host_v4(const char *);
struct address	*host_v6(const char *);
int		 host_dns(const char *, struct addresslist *,
		    int, struct portrange *, const char *, int);
int		 host_if(const char *, struct addresslist *,
		    int, struct portrange *, const char *, int);
int		 host(const char *, struct addresslist *,
		    int, struct portrange *, const char *, int);
void		 host_free(struct addresslist *);
struct server	*server_inherit(struct server *, const char *,
		    struct server_config *);
int		 getservice(char *);
int		 is_if_in_group(const char *, const char *);

typedef struct {
	union {
		int64_t			 number;
		char			*string;
		struct timeval		 tv;
		struct portrange	 port;
		struct auth		 auth;
		struct {
			struct sockaddr_storage	 ss;
			char			 name[HOST_NAME_MAX+1];
		}			 addr;
	} v;
	int lineno;
} YYSTYPE;

#line 128 "parse.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define ACCESS 257
#define ALIAS 258
#define AUTO 259
#define BACKLOG 260
#define BODY 261
#define BUFFER 262
#define CERTIFICATE 263
#define CHROOT 264
#define CIPHERS 265
#define COMMON 266
#define COMBINED 267
#define CONNECTION 268
#define DHE 269
#define DIRECTORY 270
#define ECDHE 271
#define ERR 272
#define FCGI 273
#define INDEX 274
#define IP 275
#define KEY 276
#define LISTEN 277
#define LOCATION 278
#define LOG 279
#define LOGDIR 280
#define MAXIMUM 281
#define NO 282
#define NODELAY 283
#define ON 284
#define PORT 285
#define PREFORK 286
#define PROTOCOLS 287
#define REQUEST 288
#define REQUESTS 289
#define ROOT 290
#define SACK 291
#define SERVER 292
#define SOCKET 293
#define STRIP 294
#define STYLE 295
#define SYSLOG 296
#define TCP 297
#define TIMEOUT 298
#define TLS 299
#define TYPES 300
#define ERROR 301
#define INCLUDE 302
#define AUTHENTICATE 303
#define WITH 304
#define BLOCK 305
#define DROP 306
#define RETURN 307
#define PASS 308
#define STRING 309
#define NUMBER 310
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    0,    0,    0,    0,    0,    0,    7,    8,
    2,    2,    9,    9,    9,   12,   10,   14,   14,   15,
   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,
   26,   15,   15,   23,   23,   27,   23,   30,   23,   28,
   28,   29,   18,   18,   32,   32,   33,   33,   33,   19,
   19,   34,   34,   35,   35,   35,   35,   35,   35,   20,
   20,   37,   37,   36,   36,   24,   24,    6,    6,   21,
   21,   39,   39,   38,   38,   38,   38,   22,   22,   22,
   41,   41,   40,   40,   40,   40,   40,   42,   42,   42,
   25,   25,   25,   25,   43,    5,    5,   17,   17,   44,
   44,   45,   45,   45,   45,   45,   45,   45,   11,   46,
   46,   49,   47,   47,   48,   48,   51,    1,    1,    3,
    4,    4,   50,   50,   13,   13,   31,   31,   16,
};
static const YYINT yylen[] = {                            2,
    0,    3,    2,    3,    3,    3,    3,    3,    2,    3,
    0,    1,    2,    2,    2,    0,    7,    3,    2,    5,
    2,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    0,    7,    1,    2,    1,    0,    6,    0,    3,    3,
    2,    2,    5,    2,    3,    2,    2,    3,    4,    5,
    2,    3,    2,    2,    2,    2,    2,    2,    2,    2,
    5,    3,    2,    1,    2,    2,    2,    3,    2,    2,
    5,    3,    2,    2,    2,    2,    3,    2,    5,    2,
    3,    2,    2,    1,    2,    2,    2,    1,    1,    1,
    4,    2,    1,    1,    1,    0,    1,    5,    2,    3,
    2,    1,    2,    1,    2,    2,    3,    3,    5,    3,
    2,    0,    6,    1,    2,    1,    1,    2,    2,    1,
    1,    1,    1,    0,    2,    0,    2,    1,    2,
};
static const YYINT yydefred[] = {                         1,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    3,
    0,    0,    0,    0,    0,    8,   14,   15,   13,   16,
    0,    9,    0,    2,    4,    5,    6,    7,    0,    0,
    0,   10,    0,  125,    0,  114,    0,    0,    0,    0,
  109,    0,    0,  111,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   95,   94,   33,    0,
    0,   22,   23,   24,   25,   26,   27,   28,   29,   30,
    0,  112,  110,  129,   21,    0,    0,    0,   44,    0,
    0,    0,    0,   70,    0,    0,    0,   31,    0,    0,
    0,    0,   84,    0,   78,   34,   80,   66,    0,   64,
    0,   60,    0,    0,    0,  104,  102,    0,    0,   99,
    0,    0,    0,    0,    0,    0,    0,   51,    0,    0,
   67,   17,    0,   19,   92,    0,    0,    0,    0,  120,
   47,    0,   76,   74,    0,   75,    0,    0,    0,   39,
    0,    0,   86,   87,   85,   88,   89,   90,   83,    0,
   65,    0,  106,    0,  105,  103,    0,    0,   54,   56,
   57,   58,   55,   59,    0,   69,    0,   18,    0,  122,
  121,  117,    0,  116,    0,   48,    0,    0,   77,    0,
    0,    0,   42,   12,    0,    0,    0,    0,    0,    0,
  108,  107,    0,    0,    0,    0,   68,   97,   91,  123,
  113,  115,   49,   43,    0,    0,   46,  128,    0,   73,
    0,   71,    0,    0,    0,   20,    0,   82,    0,   79,
   63,    0,   61,   98,  101,    0,   50,   53,    0,    0,
  127,   45,   72,   37,   41,    0,  119,  118,    0,   81,
   62,  100,   52,   40,   32,
};
static const YYINT yydgoto[] = {                          1,
  216,  185,  131,  172,  199,  121,   59,   12,   13,   14,
   15,   29,   31,   60,   61,  208,   62,   63,   64,   65,
   66,   67,   68,   69,   70,  142,   85,  213,  214,   86,
  209,  177,  178,  195,  196,  189,  190,  180,  181,  187,
  188,  149,   71,  193,  194,   37,   38,  173,  127,  201,
  174,
};
static const YYINT yysindex[] = {                         0,
  -10,   13, -281, -252, -270, -241,  -47, -230,   24,    0,
   77,   86,   92,   99,  104,    0,    0,    0,    0,    0,
  109,    0, -186,    0,    0,    0,    0,    0,   -1,  109,
 -288,    0,  109,    0,   78,    0,  -93,  127, -187, -166,
    0,  127,  109,    0, -165, -118, -113,    0, -139, -158,
 -105, -260, -121,  -25, -116, -282,    0,    0,    0,  297,
  109,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -273,    0,    0,    0,    0, -189, -156,  109,    0, -117,
 -153, -244,  109,    0,   35, -134, -145,    0, -144, -141,
 -130, -133,    0,  109,    0,    0,    0,    0, -140,    0,
  109,    0, -138, -135, -266,    0,    0,  -87,  109,    0,
 -123, -101,  -99,  -97,  -96,  -85,  109,    0,  -81, -128,
    0,    0,  127,    0,    0, -131, -180,  -57,  -80,    0,
    0, -272,    0,    0,  -43,    0, -218,  109,  -75,    0,
  -62,  116,    0,    0,    0,    0,    0,    0,    0, -237,
    0, -229,    0,  -70,    0,    0,  -69, -155,    0,    0,
    0,    0,    0,    0,  -27,    0,  -66,    0,  -64,    0,
    0,    0,  -58,    0,  -63,    0,  123,   -7,    0,   -7,
  128, -134,    0,    0,  -30,  109,   -7,  131,   -7,  136,
    0,    0,  137,   -7,  138,   -7,    0,    0,    0,    0,
    0,    0,    0,    0,  109,  109,    0,    0, -272,    0,
 -218,    0,  139,   -7, -168,    0, -187,    0, -237,    0,
    0, -229,    0,    0,    0, -155,    0,    0,  -27,    0,
    0,    0,    0,    0,    0, -134,    0,    0,  333,    0,
    0,    0,    0,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -278,    0,    0,    0,    0,    0,    0,    0,    0,  -76,
    0,    0,  220,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  204,    0,    0,    0,    0,    1,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  375,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   37,    0,    0,    0,    0,    0,    0, -269,    0,    0,
    0,    0, -181,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -188,    0,    0,    0,    0,    0,    0,
 -227,    0,    0,    0,    0,    0,    0,    0, -143,    0,
    0,    0,    0,    0,    0,    0,  178,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -28,    0,    0,
  -13,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   53,    0,
    0,    0,  263,    0,    0,    0,    0,  150,    0,  150,
    0,    0,    0,    0,    0,  220,  150,    0,  150,    0,
    0,    0,    0,  150,    0,  150,    0,    0,    0,    0,
    0,    0,    0,    0,  100, -221,    0,    0,    0,    0,
    0,    0,    0,  150,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  142,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
    0,    0,    0,    0,    0,    0,   15,    0,    0,    0,
    0,    0,  367,   60,  -54,  -34,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   45,  198,    0,
  -83,   76,  240,   58,  233,  236,   71,  249,   90,  246,
   83,    0,    0,   82,  258,    0,  276,    0,    0,    0,
  144,
};
#define YYTABLESIZE 683
static const YYINT yytable[] = {                         10,
  200,  101,  205,   44,   78,  123,  117,   73,   76,   83,
   35,  126,   96,    8,  135,   11,  155,   94,   97,   89,
   35,  119,   16,  126,  156,   77,  120,   17,  126,  136,
  126,   41,  125,  126,   90,  126,  206,  126,  126,   19,
   80,  126,   98,  126,   91,   36,   93,  126,  126,  126,
  126,   36,  126,  126,  126,   81,   18,   92,   93,  126,
  126,  126,   96,   82,   99,  126,  126,   20,  126,  126,
   45,  126,  126,  126,  126,   21,  126,  126,   22,  100,
   46,  126,   47,  126,   23,   48,   24,  126,  168,   49,
   50,   51,  126,  126,   52,   25,  211,  109,  128,  129,
  126,   26,   53,  219,  103,  222,  126,  126,   27,   54,
  226,   55,  229,   28,    8,   56,  126,   57,   30,  104,
   58,   33,   32,   36,   40,   35,  105,  106,  170,  171,
  236,  126,  146,  147,  148,  107,   43,  108,  126,  126,
  237,  238,   72,   75,   87,   80,  111,  126,  112,  126,
   88,   89,  113,  130,  114,  134,  133,  138,  139,  115,
   81,   93,   76,  141,  143,  145,   90,  144,   82,  151,
  116,  153,   99,  154,  157,  167,   91,   96,  169,   77,
  126,  126,  126,  126,  123,  159,  126,  100,  126,   92,
   93,  126,  126,  126,  126,  126,  126,  126,  126,  126,
  126,  126,  126,  175,  126,  126,  126,  160,    8,  161,
  126,  162,  163,  126,  126,   35,  126,  126,  126,  126,
  126,  126,  126,  164,  126,  126,  126,  166,  126,  176,
  179,  126,  126,  183,  103,  111,  184,  112,  186,  191,
  192,  113,  197,  114,  198,    2,  203,  204,  115,  104,
  170,  171,  212,    3,  215,  220,  105,  106,   35,  116,
  223,  224,  227,  234,  126,  107,  125,  108,   35,    4,
   35,   11,  124,   35,  126,    5,  239,   35,   35,   35,
  244,    6,   35,  140,  232,   79,  243,  118,  102,    7,
   35,    8,  241,   38,   93,   84,   95,   35,    9,   35,
  233,  240,   35,   35,   93,   35,   93,  242,   35,   93,
   96,  110,   42,   93,   93,   93,  202,    0,   93,    0,
   96,    0,   96,    0,    0,   96,   93,    0,  126,   96,
   96,   96,    0,   93,   96,   93,    0,    0,   93,   93,
    0,   93,   96,    0,   93,    0,    0,    0,    0,   96,
    0,   96,    0,    0,   96,   96,  126,   96,  126,  126,
   96,    0,  126,    0,  126,    0,    0,    0,  126,    0,
  126,  126,    0,  126,  126,  126,    0,    0,    0,    0,
  126,  126,  126,    0,    0,    0,  126,    0,    0,    0,
  126,    0,  126,  126,  126,  126,   34,  126,  129,   39,
  129,  129,    0,    0,  129,    0,  129,    0,  126,   74,
  129,    0,  129,  129,    0,  129,  129,  129,    0,    0,
    0,  122,  129,  129,  129,    0,    0,  124,  129,    0,
    0,    0,  129,    0,  129,  129,  129,  129,    0,  129,
  126,    0,  126,    0,  132,    0,  126,    0,  126,  137,
  129,    0,    0,  126,    0,    0,    0,  245,    0,    0,
  150,  126,    0,    0,  126,    0,    0,  152,    0,    0,
    0,  126,    0,  126,    0,  158,  126,  126,    0,    0,
  126,  126,  126,  165,    0,  126,    0,  126,    0,  126,
    0,    0,  126,  126,    0,    0,  126,  126,  126,  126,
  126,  126,  126,    0,  182,  126,  126,    0,  126,  126,
    0,  126,  126,    0,    0,    0,  126,    0,  126,    0,
    0,  126,  126,    0,  126,    0,    0,  126,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  207,    0,  210,    0,    0,    0,
    0,    0,  217,  218,   45,  221,    0,    0,    0,    0,
  225,    0,  228,    0,   46,    0,   47,    0,    0,   48,
    0,  230,  231,   49,   50,   51,    0,    0,   52,    0,
  235,    0,    0,    0,    0,    0,   53,    0,    0,    0,
   45,    0,    0,   54,    0,   55,    0,    0,    8,   56,
   46,   57,   47,    0,   58,   48,    0,    0,    0,   49,
   50,   51,    0,    0,   52,    0,    0,    0,    0,    0,
    0,    0,   53,    0,    0,    0,    0,    0,    0,   54,
    0,   55,  126,    0,    8,   56,    0,   57,    0,    0,
   58,    0,  126,    0,  126,    0,    0,  126,    0,    0,
    0,  126,  126,  126,    0,    0,  126,    0,    0,    0,
    0,    0,    0,    0,  126,    0,    0,    0,    0,    0,
    0,  126,    0,  126,    0,    0,  126,  126,    0,  126,
    0,    0,  126,
};
static const YYINT yycheck[] = {                         10,
   59,  123,   10,   38,  123,   60,  123,   42,  281,  123,
   10,  281,  273,  302,  259,    1,  283,  123,  279,  257,
  309,  304,   10,  302,  291,  298,  309,  309,  298,  274,
  309,  125,  306,  307,  272,  257,   44,  259,  260,  310,
  259,  263,  303,  265,  282,   31,   10,  269,  125,  271,
  272,   37,  274,  275,  276,  274,  309,  295,  296,  281,
  282,  283,   10,  282,  294,  287,  294,  309,  257,  291,
  258,  293,  294,  295,  296,  123,  298,  259,  309,  309,
  268,  309,  270,  272,   61,  273,   10,  309,  123,  277,
  278,  279,  274,  282,  282,   10,  180,  123,  288,  289,
  282,   10,  290,  187,  260,  189,  295,  296,   10,  297,
  194,  299,  196,   10,  302,  303,  260,  305,   10,  275,
  308,  123,  309,  123,   47,  125,  282,  283,  309,  310,
  214,  275,  266,  267,  268,  291,   10,  293,  282,  283,
  309,  310,  309,  309,  284,  259,  263,  291,  265,  293,
  309,  257,  269,  310,  271,  309,  274,  123,  293,  276,
  274,  125,  281,  309,  309,  296,  272,  309,  282,  310,
  287,  310,  294,  309,  262,  304,  282,  125,  310,  298,
  257,  258,  259,  260,  239,  309,  263,  309,  265,  295,
  296,  268,  269,  270,  271,  272,  273,  274,  275,  276,
  277,  278,  279,  261,  281,  282,  283,  309,  302,  309,
  287,  309,  309,  290,  291,  309,  293,  294,  295,  296,
  297,  298,  299,  309,  125,  302,  303,  309,  305,  310,
  274,  308,  309,  309,  260,  263,  299,  265,  123,  310,
  310,  269,  309,  271,  309,  256,  310,  125,  276,  275,
  309,  310,  125,  264,  285,  125,  282,  283,  258,  287,
  125,  125,  125,  125,  293,  291,  125,  293,  268,  280,
  270,  285,   10,  273,  125,  286,  217,  277,  278,  279,
  236,  292,  282,   86,  209,   46,  229,   55,   53,  300,
  290,  302,  222,  293,  258,   47,   51,  297,  309,  299,
  211,  219,  302,  303,  268,  305,  270,  226,  308,  273,
  258,   54,   37,  277,  278,  279,  173,   -1,  282,   -1,
  268,   -1,  270,   -1,   -1,  273,  290,   -1,  125,  277,
  278,  279,   -1,  297,  282,  299,   -1,   -1,  302,  303,
   -1,  305,  290,   -1,  308,   -1,   -1,   -1,   -1,  297,
   -1,  299,   -1,   -1,  302,  303,  257,  305,  259,  260,
  308,   -1,  263,   -1,  265,   -1,   -1,   -1,  269,   -1,
  271,  272,   -1,  274,  275,  276,   -1,   -1,   -1,   -1,
  281,  282,  283,   -1,   -1,   -1,  287,   -1,   -1,   -1,
  291,   -1,  293,  294,  295,  296,   30,  298,  257,   33,
  259,  260,   -1,   -1,  263,   -1,  265,   -1,  309,   43,
  269,   -1,  271,  272,   -1,  274,  275,  276,   -1,   -1,
   -1,  125,  281,  282,  283,   -1,   -1,   61,  287,   -1,
   -1,   -1,  291,   -1,  293,  294,  295,  296,   -1,  298,
  263,   -1,  265,   -1,   78,   -1,  269,   -1,  271,   83,
  309,   -1,   -1,  276,   -1,   -1,   -1,  125,   -1,   -1,
   94,  258,   -1,   -1,  287,   -1,   -1,  101,   -1,   -1,
   -1,  268,   -1,  270,   -1,  109,  273,  258,   -1,   -1,
  277,  278,  279,  117,   -1,  282,   -1,  268,   -1,  270,
   -1,   -1,  273,  290,   -1,   -1,  277,  278,  279,  125,
  297,  282,  299,   -1,  138,  302,  303,   -1,  305,  290,
   -1,  308,  309,   -1,   -1,   -1,  297,   -1,  299,   -1,
   -1,  302,  303,   -1,  305,   -1,   -1,  308,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  178,   -1,  180,   -1,   -1,   -1,
   -1,   -1,  186,  187,  258,  189,   -1,   -1,   -1,   -1,
  194,   -1,  196,   -1,  268,   -1,  270,   -1,   -1,  273,
   -1,  205,  206,  277,  278,  279,   -1,   -1,  282,   -1,
  214,   -1,   -1,   -1,   -1,   -1,  290,   -1,   -1,   -1,
  258,   -1,   -1,  297,   -1,  299,   -1,   -1,  302,  303,
  268,  305,  270,   -1,  308,  273,   -1,   -1,   -1,  277,
  278,  279,   -1,   -1,  282,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  290,   -1,   -1,   -1,   -1,   -1,   -1,  297,
   -1,  299,  258,   -1,  302,  303,   -1,  305,   -1,   -1,
  308,   -1,  268,   -1,  270,   -1,   -1,  273,   -1,   -1,
   -1,  277,  278,  279,   -1,   -1,  282,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  290,   -1,   -1,   -1,   -1,   -1,
   -1,  297,   -1,  299,   -1,   -1,  302,  303,   -1,  305,
   -1,   -1,  308,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 310
#define YYUNDFTOKEN 364
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,"'\\n'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,"','",0,0,"'/'",0,0,0,0,0,0,0,0,0,0,0,"';'",0,"'='",0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"ACCESS","ALIAS","AUTO","BACKLOG","BODY","BUFFER","CERTIFICATE","CHROOT",
"CIPHERS","COMMON","COMBINED","CONNECTION","DHE","DIRECTORY","ECDHE","ERR",
"FCGI","INDEX","IP","KEY","LISTEN","LOCATION","LOG","LOGDIR","MAXIMUM","NO",
"NODELAY","ON","PORT","PREFORK","PROTOCOLS","REQUEST","REQUESTS","ROOT","SACK",
"SERVER","SOCKET","STRIP","STYLE","SYSLOG","TCP","TIMEOUT","TLS","TYPES",
"ERROR","INCLUDE","AUTHENTICATE","WITH","BLOCK","DROP","RETURN","PASS","STRING",
"NUMBER",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : grammar",
"grammar :",
"grammar : grammar include '\\n'",
"grammar : grammar '\\n'",
"grammar : grammar varset '\\n'",
"grammar : grammar main '\\n'",
"grammar : grammar server '\\n'",
"grammar : grammar types '\\n'",
"grammar : grammar error '\\n'",
"include : INCLUDE STRING",
"varset : STRING '=' STRING",
"opttls :",
"opttls : TLS",
"main : PREFORK NUMBER",
"main : CHROOT STRING",
"main : LOGDIR STRING",
"$$1 :",
"server : SERVER STRING $$1 '{' optnl serveropts_l '}'",
"serveropts_l : serveropts_l serveroptsl nl",
"serveropts_l : serveroptsl optnl",
"serveroptsl : LISTEN ON STRING opttls port",
"serveroptsl : ALIAS STRING",
"serveroptsl : tcpip",
"serveroptsl : connection",
"serveroptsl : tls",
"serveroptsl : root",
"serveroptsl : directory",
"serveroptsl : logformat",
"serveroptsl : fastcgi",
"serveroptsl : authenticate",
"serveroptsl : filter",
"$$2 :",
"serveroptsl : LOCATION STRING $$2 '{' optnl serveropts_l '}'",
"serveroptsl : include",
"fastcgi : NO FCGI",
"fastcgi : FCGI",
"$$3 :",
"fastcgi : FCGI $$3 '{' optnl fcgiflags_l '}'",
"$$4 :",
"fastcgi : FCGI $$4 fcgiflags",
"fcgiflags_l : fcgiflags optcommanl fcgiflags_l",
"fcgiflags_l : fcgiflags optnl",
"fcgiflags : SOCKET STRING",
"connection : CONNECTION '{' optnl conflags_l '}'",
"connection : CONNECTION conflags",
"conflags_l : conflags optcommanl conflags_l",
"conflags_l : conflags optnl",
"conflags : TIMEOUT timeout",
"conflags : MAXIMUM REQUESTS NUMBER",
"conflags : MAXIMUM REQUEST BODY NUMBER",
"tls : TLS '{' optnl tlsopts_l '}'",
"tls : TLS tlsopts",
"tlsopts_l : tlsopts optcommanl tlsopts_l",
"tlsopts_l : tlsopts optnl",
"tlsopts : CERTIFICATE STRING",
"tlsopts : KEY STRING",
"tlsopts : CIPHERS STRING",
"tlsopts : DHE STRING",
"tlsopts : ECDHE STRING",
"tlsopts : PROTOCOLS STRING",
"root : ROOT rootflags",
"root : ROOT '{' optnl rootflags_l '}'",
"rootflags_l : rootflags optcommanl rootflags_l",
"rootflags_l : rootflags optnl",
"rootflags : STRING",
"rootflags : STRIP NUMBER",
"authenticate : NO AUTHENTICATE",
"authenticate : AUTHENTICATE authopts",
"authopts : STRING WITH STRING",
"authopts : WITH STRING",
"directory : DIRECTORY dirflags",
"directory : DIRECTORY '{' optnl dirflags_l '}'",
"dirflags_l : dirflags optcommanl dirflags_l",
"dirflags_l : dirflags optnl",
"dirflags : INDEX STRING",
"dirflags : NO INDEX",
"dirflags : AUTO INDEX",
"dirflags : NO AUTO INDEX",
"logformat : LOG logflags",
"logformat : LOG '{' optnl logflags_l '}'",
"logformat : NO LOG",
"logflags_l : logflags optcommanl logflags_l",
"logflags_l : logflags optnl",
"logflags : STYLE logstyle",
"logflags : SYSLOG",
"logflags : NO SYSLOG",
"logflags : ACCESS STRING",
"logflags : ERR STRING",
"logstyle : COMMON",
"logstyle : COMBINED",
"logstyle : CONNECTION",
"filter : block RETURN NUMBER optstring",
"filter : block DROP",
"filter : block",
"filter : PASS",
"block : BLOCK",
"optstring :",
"optstring : STRING",
"tcpip : TCP '{' optnl tcpflags_l '}'",
"tcpip : TCP tcpflags",
"tcpflags_l : tcpflags optcommanl tcpflags_l",
"tcpflags_l : tcpflags optnl",
"tcpflags : SACK",
"tcpflags : NO SACK",
"tcpflags : NODELAY",
"tcpflags : NO NODELAY",
"tcpflags : BACKLOG NUMBER",
"tcpflags : SOCKET BUFFER NUMBER",
"tcpflags : IP STRING NUMBER",
"types : TYPES '{' optnl mediaopts_l '}'",
"mediaopts_l : mediaopts_l mediaoptsl nl",
"mediaopts_l : mediaoptsl nl",
"$$5 :",
"mediaoptsl : STRING '/' STRING $$5 medianames_l optsemicolon",
"mediaoptsl : include",
"medianames_l : medianames_l medianamesl",
"medianames_l : medianamesl",
"medianamesl : numberstring",
"port : PORT NUMBER",
"port : PORT STRING",
"timeout : NUMBER",
"numberstring : NUMBER",
"numberstring : STRING",
"optsemicolon : ';'",
"optsemicolon :",
"optnl : '\\n' optnl",
"optnl :",
"optcommanl : ',' optnl",
"optcommanl : nl",
"nl : '\\n' optnl",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 1054 "parse.y"

struct keywords {
	const char	*k_name;
	int		 k_val;
};

int
yyerror(const char *fmt, ...)
{
	va_list		 ap;
	char		*msg;

	file->errors++;
	va_start(ap, fmt);
	if (vasprintf(&msg, fmt, ap) == -1)
		fatalx("yyerror vasprintf");
	va_end(ap);
	logit(LOG_CRIT, "%s:%d: %s", file->name, yylval.lineno, msg);
	free(msg);
	return (0);
}

int
kw_cmp(const void *k, const void *e)
{
	return (strcmp(k, ((const struct keywords *)e)->k_name));
}

int
lookup(char *s)
{
	/* this has to be sorted always */
	static const struct keywords keywords[] = {
		{ "access",		ACCESS },
		{ "alias",		ALIAS },
		{ "authenticate",	AUTHENTICATE},
		{ "auto",		AUTO },
		{ "backlog",		BACKLOG },
		{ "block",		BLOCK },
		{ "body",		BODY },
		{ "buffer",		BUFFER },
		{ "certificate",	CERTIFICATE },
		{ "chroot",		CHROOT },
		{ "ciphers",		CIPHERS },
		{ "combined",		COMBINED },
		{ "common",		COMMON },
		{ "connection",		CONNECTION },
		{ "dhe",		DHE },
		{ "directory",		DIRECTORY },
		{ "drop",		DROP },
		{ "ecdhe",		ECDHE },
		{ "error",		ERR },
		{ "fastcgi",		FCGI },
		{ "include",		INCLUDE },
		{ "index",		INDEX },
		{ "ip",			IP },
		{ "key",		KEY },
		{ "listen",		LISTEN },
		{ "location",		LOCATION },
		{ "log",		LOG },
		{ "logdir",		LOGDIR },
		{ "max",		MAXIMUM },
		{ "no",			NO },
		{ "nodelay",		NODELAY },
		{ "on",			ON },
		{ "pass",		PASS },
		{ "port",		PORT },
		{ "prefork",		PREFORK },
		{ "protocols",		PROTOCOLS },
		{ "request",		REQUEST },
		{ "requests",		REQUESTS },
		{ "return",		RETURN },
		{ "root",		ROOT },
		{ "sack",		SACK },
		{ "server",		SERVER },
		{ "socket",		SOCKET },
		{ "strip",		STRIP },
		{ "style",		STYLE },
		{ "syslog",		SYSLOG },
		{ "tcp",		TCP },
		{ "timeout",		TIMEOUT },
		{ "tls",		TLS },
		{ "types",		TYPES },
		{ "with",		WITH }
	};
	const struct keywords	*p;

	p = bsearch(s, keywords, sizeof(keywords)/sizeof(keywords[0]),
	    sizeof(keywords[0]), kw_cmp);

	if (p)
		return (p->k_val);
	else
		return (STRING);
}

#define MAXPUSHBACK	128

u_char	*parsebuf;
int	 parseindex;
u_char	 pushback_buffer[MAXPUSHBACK];
int	 pushback_index = 0;

int
lgetc(int quotec)
{
	int		c, next;

	if (parsebuf) {
		/* Read character from the parsebuffer instead of input. */
		if (parseindex >= 0) {
			c = parsebuf[parseindex++];
			if (c != '\0')
				return (c);
			parsebuf = NULL;
		} else
			parseindex++;
	}

	if (pushback_index)
		return (pushback_buffer[--pushback_index]);

	if (quotec) {
		if ((c = getc(file->stream)) == EOF) {
			yyerror("reached end of file while parsing "
			    "quoted string");
			if (file == topfile || popfile() == EOF)
				return (EOF);
			return (quotec);
		}
		return (c);
	}

	while ((c = getc(file->stream)) == '\\') {
		next = getc(file->stream);
		if (next != '\n') {
			c = next;
			break;
		}
		yylval.lineno = file->lineno;
		file->lineno++;
	}

	while (c == EOF) {
		if (file == topfile || popfile() == EOF)
			return (EOF);
		c = getc(file->stream);
	}
	return (c);
}

int
lungetc(int c)
{
	if (c == EOF)
		return (EOF);
	if (parsebuf) {
		parseindex--;
		if (parseindex >= 0)
			return (c);
	}
	if (pushback_index < MAXPUSHBACK-1)
		return (pushback_buffer[pushback_index++] = c);
	else
		return (EOF);
}

int
findeol(void)
{
	int	c;

	parsebuf = NULL;

	/* skip to either EOF or the first real EOL */
	while (1) {
		if (pushback_index)
			c = pushback_buffer[--pushback_index];
		else
			c = lgetc(0);
		if (c == '\n') {
			file->lineno++;
			break;
		}
		if (c == EOF)
			break;
	}
	return (ERROR);
}

int
yylex(void)
{
	u_char	 buf[8096];
	u_char	*p, *val;
	int	 quotec, next, c;
	int	 token;

top:
	p = buf;
	while ((c = lgetc(0)) == ' ' || c == '\t')
		; /* nothing */

	yylval.lineno = file->lineno;
	if (c == '#')
		while ((c = lgetc(0)) != '\n' && c != EOF)
			; /* nothing */
	if (c == '$' && parsebuf == NULL) {
		while (1) {
			if ((c = lgetc(0)) == EOF)
				return (0);

			if (p + 1 >= buf + sizeof(buf) - 1) {
				yyerror("string too long");
				return (findeol());
			}
			if (isalnum(c) || c == '_') {
				*p++ = c;
				continue;
			}
			*p = '\0';
			lungetc(c);
			break;
		}
		val = symget(buf);
		if (val == NULL) {
			yyerror("macro '%s' not defined", buf);
			return (findeol());
		}
		parsebuf = val;
		parseindex = 0;
		goto top;
	}

	switch (c) {
	case '\'':
	case '"':
		quotec = c;
		while (1) {
			if ((c = lgetc(quotec)) == EOF)
				return (0);
			if (c == '\n') {
				file->lineno++;
				continue;
			} else if (c == '\\') {
				if ((next = lgetc(quotec)) == EOF)
					return (0);
				if (next == quotec || c == ' ' || c == '\t')
					c = next;
				else if (next == '\n') {
					file->lineno++;
					continue;
				} else
					lungetc(next);
			} else if (c == quotec) {
				*p = '\0';
				break;
			} else if (c == '\0') {
				yyerror("syntax error");
				return (findeol());
			}
			if (p + 1 >= buf + sizeof(buf) - 1) {
				yyerror("string too long");
				return (findeol());
			}
			*p++ = c;
		}
		yylval.v.string = strdup(buf);
		if (yylval.v.string == NULL)
			err(1, "yylex: strdup");
		return (STRING);
	}

#define allowed_to_end_number(x) \
	(isspace(x) || x == ')' || x ==',' || x == '/' || x == '}' || x == '=')

	if (c == '-' || isdigit(c)) {
		do {
			*p++ = c;
			if ((unsigned)(p-buf) >= sizeof(buf)) {
				yyerror("string too long");
				return (findeol());
			}
		} while ((c = lgetc(0)) != EOF && isdigit(c));
		lungetc(c);
		if (p == buf + 1 && buf[0] == '-')
			goto nodigits;
		if (c == EOF || allowed_to_end_number(c)) {
			const char *errstr = NULL;

			*p = '\0';
			yylval.v.number = strtonum(buf, LLONG_MIN,
			    LLONG_MAX, &errstr);
			if (errstr) {
				yyerror("\"%s\" invalid number: %s",
				    buf, errstr);
				return (findeol());
			}
			return (NUMBER);
		} else {
nodigits:
			while (p > buf + 1)
				lungetc(*--p);
			c = *--p;
			if (c == '-')
				return (c);
		}
	}

#define allowed_in_string(x) \
	(isalnum(x) || (ispunct(x) && x != '(' && x != ')' && \
	x != '{' && x != '}' && x != '<' && x != '>' && \
	x != '!' && x != '=' && x != '#' && \
	x != ',' && x != ';' && x != '/'))

	if (isalnum(c) || c == ':' || c == '_' || c == '*') {
		do {
			*p++ = c;
			if ((unsigned)(p-buf) >= sizeof(buf)) {
				yyerror("string too long");
				return (findeol());
			}
		} while ((c = lgetc(0)) != EOF && (allowed_in_string(c)));
		lungetc(c);
		*p = '\0';
		if ((token = lookup(buf)) == STRING)
			if ((yylval.v.string = strdup(buf)) == NULL)
				err(1, "yylex: strdup");
		return (token);
	}
	if (c == '\n') {
		yylval.lineno = file->lineno;
		file->lineno++;
	}
	if (c == EOF)
		return (0);
	return (c);
}

int
check_file_secrecy(int fd, const char *fname)
{
	struct stat	st;

	if (fstat(fd, &st)) {
		log_warn("cannot stat %s", fname);
		return (-1);
	}
	if (st.st_uid != 0 && st.st_uid != getuid()) {
		log_warnx("%s: owner not root or current user", fname);
		return (-1);
	}
	if (st.st_mode & (S_IWGRP | S_IXGRP | S_IRWXO)) {
		log_warnx("%s: group writable or world read/writable", fname);
		return (-1);
	}
	return (0);
}

struct file *
pushfile(const char *name, int secret)
{
	struct file	*nfile;

	if ((nfile = calloc(1, sizeof(struct file))) == NULL) {
		log_warn("%s: malloc", __func__);
		return (NULL);
	}
	if ((nfile->name = strdup(name)) == NULL) {
		log_warn("%s: malloc", __func__);
		free(nfile);
		return (NULL);
	}
	if ((nfile->stream = fopen(nfile->name, "r")) == NULL) {
		log_warn("%s: %s", __func__, nfile->name);
		free(nfile->name);
		free(nfile);
		return (NULL);
	} else if (secret &&
	    check_file_secrecy(fileno(nfile->stream), nfile->name)) {
		fclose(nfile->stream);
		free(nfile->name);
		free(nfile);
		return (NULL);
	}
	nfile->lineno = 1;
	TAILQ_INSERT_TAIL(&files, nfile, entry);
	return (nfile);
}

int
popfile(void)
{
	struct file	*prev;

	if ((prev = TAILQ_PREV(file, files, entry)) != NULL)
		prev->errors += file->errors;

	TAILQ_REMOVE(&files, file, entry);
	fclose(file->stream);
	free(file->name);
	free(file);
	file = prev;
	return (file ? 0 : EOF);
}

int
parse_config(const char *filename, struct httpd *x_conf)
{
	struct sym	*sym, *next;

	conf = x_conf;
	if (config_init(conf) == -1) {
		log_warn("%s: cannot initialize configuration", __func__);
		return (-1);
	}

	errors = 0;

	if ((file = pushfile(filename, 0)) == NULL)
		return (-1);

	topfile = file;
	setservent(1);

	yyparse();
	errors = file->errors;
	popfile();

	endservent();
	endprotoent();

	/* Free macros */
	for (sym = TAILQ_FIRST(&symhead); sym != NULL; sym = next) {
		next = TAILQ_NEXT(sym, entry);
		if (!sym->persist) {
			free(sym->nam);
			free(sym->val);
			TAILQ_REMOVE(&symhead, sym, entry);
			free(sym);
		}
	}

	return (errors ? -1 : 0);
}

int
load_config(const char *filename, struct httpd *x_conf)
{
	struct sym		*sym, *next;
	struct http_mediatype	 mediatypes[] = MEDIA_TYPES;
	struct media_type	 m;
	int			 i;

	conf = x_conf;
	conf->sc_flags = 0;

	loadcfg = 1;
	errors = 0;
	last_server_id = 0;
	last_auth_id = 0;

	srv = NULL;

	if ((file = pushfile(filename, 0)) == NULL)
		return (-1);

	topfile = file;
	setservent(1);

	yyparse();
	errors = file->errors;
	popfile();

	endservent();
	endprotoent();

	/* Free macros and check which have not been used. */
	for (sym = TAILQ_FIRST(&symhead); sym != NULL; sym = next) {
		next = TAILQ_NEXT(sym, entry);
		if ((conf->sc_opts & HTTPD_OPT_VERBOSE) && !sym->used)
			fprintf(stderr, "warning: macro '%s' not "
			    "used\n", sym->nam);
		if (!sym->persist) {
			free(sym->nam);
			free(sym->val);
			TAILQ_REMOVE(&symhead, sym, entry);
			free(sym);
		}
	}

	if (TAILQ_EMPTY(conf->sc_servers)) {
		log_warnx("no actions, nothing to do");
		errors++;
	}

	if (RB_EMPTY(conf->sc_mediatypes)) {
		/* Add default media types */
		for (i = 0; mediatypes[i].media_name != NULL; i++) {
			(void)strlcpy(m.media_name, mediatypes[i].media_name,
			    sizeof(m.media_name));
			(void)strlcpy(m.media_type, mediatypes[i].media_type,
			    sizeof(m.media_type));
			(void)strlcpy(m.media_subtype,
			    mediatypes[i].media_subtype,
			    sizeof(m.media_subtype));
			m.media_encoding = NULL;

			if (media_add(conf->sc_mediatypes, &m) == NULL) {
				log_warnx("failed to add default media \"%s\"",
				    m.media_name);
				errors++;
			}
		}
	}

	return (errors ? -1 : 0);
}

int
symset(const char *nam, const char *val, int persist)
{
	struct sym	*sym;

	for (sym = TAILQ_FIRST(&symhead); sym && strcmp(nam, sym->nam);
	    sym = TAILQ_NEXT(sym, entry))
		;	/* nothing */

	if (sym != NULL) {
		if (sym->persist == 1)
			return (0);
		else {
			free(sym->nam);
			free(sym->val);
			TAILQ_REMOVE(&symhead, sym, entry);
			free(sym);
		}
	}
	if ((sym = calloc(1, sizeof(*sym))) == NULL)
		return (-1);

	sym->nam = strdup(nam);
	if (sym->nam == NULL) {
		free(sym);
		return (-1);
	}
	sym->val = strdup(val);
	if (sym->val == NULL) {
		free(sym->nam);
		free(sym);
		return (-1);
	}
	sym->used = 0;
	sym->persist = persist;
	TAILQ_INSERT_TAIL(&symhead, sym, entry);
	return (0);
}

int
cmdline_symset(char *s)
{
	char	*sym, *val;
	int	ret;
	size_t	len;

	if ((val = strrchr(s, '=')) == NULL)
		return (-1);

	len = strlen(s) - strlen(val) + 1;
	if ((sym = malloc(len)) == NULL)
		errx(1, "cmdline_symset: malloc");

	(void)strlcpy(sym, s, len);

	ret = symset(sym, val + 1, 1);
	free(sym);

	return (ret);
}

char *
symget(const char *nam)
{
	struct sym	*sym;

	TAILQ_FOREACH(sym, &symhead, entry)
		if (strcmp(nam, sym->nam) == 0) {
			sym->used = 1;
			return (sym->val);
		}
	return (NULL);
}

struct address *
host_v4(const char *s)
{
	struct in_addr		 ina;
	struct sockaddr_in	*sain;
	struct address		*h;

	memset(&ina, 0, sizeof(ina));
	if (inet_pton(AF_INET, s, &ina) != 1)
		return (NULL);

	if ((h = calloc(1, sizeof(*h))) == NULL)
		fatal(NULL);
	sain = (struct sockaddr_in *)&h->ss;
	sain->sin_len = sizeof(struct sockaddr_in);
	sain->sin_family = AF_INET;
	sain->sin_addr.s_addr = ina.s_addr;
	if (sain->sin_addr.s_addr == INADDR_ANY)
		h->prefixlen = 0; /* 0.0.0.0 address */
	else
		h->prefixlen = -1; /* host address */
	return (h);
}

struct address *
host_v6(const char *s)
{
	struct addrinfo		 hints, *res;
	struct sockaddr_in6	*sa_in6;
	struct address		*h = NULL;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_DGRAM; /* dummy */
	hints.ai_flags = AI_NUMERICHOST;
	if (getaddrinfo(s, "0", &hints, &res) == 0) {
		if ((h = calloc(1, sizeof(*h))) == NULL)
			fatal(NULL);
		sa_in6 = (struct sockaddr_in6 *)&h->ss;
		sa_in6->sin6_len = sizeof(struct sockaddr_in6);
		sa_in6->sin6_family = AF_INET6;
		memcpy(&sa_in6->sin6_addr,
		    &((struct sockaddr_in6 *)res->ai_addr)->sin6_addr,
		    sizeof(sa_in6->sin6_addr));
		sa_in6->sin6_scope_id =
		    ((struct sockaddr_in6 *)res->ai_addr)->sin6_scope_id;
		if (memcmp(&sa_in6->sin6_addr, &in6addr_any,
		    sizeof(sa_in6->sin6_addr)) == 0)
			h->prefixlen = 0; /* any address */
		else
			h->prefixlen = -1; /* host address */
		freeaddrinfo(res);
	}

	return (h);
}

int
host_dns(const char *s, struct addresslist *al, int max,
    struct portrange *port, const char *ifname, int ipproto)
{
	struct addrinfo		 hints, *res0, *res;
	int			 error, cnt = 0;
	struct sockaddr_in	*sain;
	struct sockaddr_in6	*sin6;
	struct address		*h;

	if ((cnt = host_if(s, al, max, port, ifname, ipproto)) != 0)
		return (cnt);

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM; /* DUMMY */
	hints.ai_flags = AI_ADDRCONFIG;
	error = getaddrinfo(s, NULL, &hints, &res0);
#ifdef __FreeBSD__
	if (error == EAI_AGAIN || error == EAI_NONAME)
#else
	if (error == EAI_AGAIN || error == EAI_NODATA || error == EAI_NONAME)
#endif
		return (0);
	if (error) {
		log_warnx("%s: could not parse \"%s\": %s", __func__, s,
		    gai_strerror(error));
		return (-1);
	}

	for (res = res0; res && cnt < max; res = res->ai_next) {
		if (res->ai_family != AF_INET &&
		    res->ai_family != AF_INET6)
			continue;
		if ((h = calloc(1, sizeof(*h))) == NULL)
			fatal(NULL);

		if (port != NULL)
			memcpy(&h->port, port, sizeof(h->port));
		if (ifname != NULL) {
			if (strlcpy(h->ifname, ifname, sizeof(h->ifname)) >=
			    sizeof(h->ifname))
				log_warnx("%s: interface name truncated",
				    __func__);
			freeaddrinfo(res0);
			free(h);
			return (-1);
		}
		if (ipproto != -1)
			h->ipproto = ipproto;
		h->ss.ss_family = res->ai_family;
		h->prefixlen = -1; /* host address */

		if (res->ai_family == AF_INET) {
			sain = (struct sockaddr_in *)&h->ss;
			sain->sin_len = sizeof(struct sockaddr_in);
			sain->sin_addr.s_addr = ((struct sockaddr_in *)
			    res->ai_addr)->sin_addr.s_addr;
		} else {
			sin6 = (struct sockaddr_in6 *)&h->ss;
			sin6->sin6_len = sizeof(struct sockaddr_in6);
			memcpy(&sin6->sin6_addr, &((struct sockaddr_in6 *)
			    res->ai_addr)->sin6_addr, sizeof(struct in6_addr));
		}

		TAILQ_INSERT_HEAD(al, h, entry);
		cnt++;
	}
	if (cnt == max && res) {
		log_warnx("%s: %s resolves to more than %d hosts", __func__,
		    s, max);
	}
	freeaddrinfo(res0);
	return (cnt);
}

int
host_if(const char *s, struct addresslist *al, int max,
    struct portrange *port, const char *ifname, int ipproto)
{
	struct ifaddrs		*ifap, *p;
	struct sockaddr_in	*sain;
	struct sockaddr_in6	*sin6;
	struct address		*h;
	int			 cnt = 0, af;

	if (getifaddrs(&ifap) == -1)
		fatal("getifaddrs");

	/* First search for IPv4 addresses */
	af = AF_INET;

 nextaf:
	for (p = ifap; p != NULL && cnt < max; p = p->ifa_next) {
		if (p->ifa_addr->sa_family != af ||
		    (strcmp(s, p->ifa_name) != 0 &&
		    !is_if_in_group(p->ifa_name, s)))
			continue;
		if ((h = calloc(1, sizeof(*h))) == NULL)
			fatal("calloc");

		if (port != NULL)
			memcpy(&h->port, port, sizeof(h->port));
		if (ifname != NULL) {
			if (strlcpy(h->ifname, ifname, sizeof(h->ifname)) >=
			    sizeof(h->ifname))
				log_warnx("%s: interface name truncated",
				    __func__);
			freeifaddrs(ifap);
			return (-1);
		}
		if (ipproto != -1)
			h->ipproto = ipproto;
		h->ss.ss_family = af;
		h->prefixlen = -1; /* host address */

		if (af == AF_INET) {
			sain = (struct sockaddr_in *)&h->ss;
			sain->sin_len = sizeof(struct sockaddr_in);
			sain->sin_addr.s_addr = ((struct sockaddr_in *)
			    p->ifa_addr)->sin_addr.s_addr;
		} else {
			sin6 = (struct sockaddr_in6 *)&h->ss;
			sin6->sin6_len = sizeof(struct sockaddr_in6);
			memcpy(&sin6->sin6_addr, &((struct sockaddr_in6 *)
			    p->ifa_addr)->sin6_addr, sizeof(struct in6_addr));
			sin6->sin6_scope_id = ((struct sockaddr_in6 *)
			    p->ifa_addr)->sin6_scope_id;
		}

		TAILQ_INSERT_HEAD(al, h, entry);
		cnt++;
	}
	if (af == AF_INET) {
		/* Next search for IPv6 addresses */
		af = AF_INET6;
		goto nextaf;
	}

	if (cnt > max) {
		log_warnx("%s: %s resolves to more than %d hosts", __func__,
		    s, max);
	}
	freeifaddrs(ifap);
	return (cnt);
}

int
host(const char *s, struct addresslist *al, int max,
    struct portrange *port, const char *ifname, int ipproto)
{
	struct address *h;

	if (strcmp("*", s) == 0)
		s = "0.0.0.0";

	h = host_v4(s);

	/* IPv6 address? */
	if (h == NULL)
		h = host_v6(s);

	if (h != NULL) {
		if (port != NULL)
			memcpy(&h->port, port, sizeof(h->port));
		if (ifname != NULL) {
			if (strlcpy(h->ifname, ifname, sizeof(h->ifname)) >=
			    sizeof(h->ifname)) {
				log_warnx("%s: interface name truncated",
				    __func__);
				free(h);
				return (-1);
			}
		}
		if (ipproto != -1)
			h->ipproto = ipproto;

		TAILQ_INSERT_HEAD(al, h, entry);
		return (1);
	}

	return (host_dns(s, al, max, port, ifname, ipproto));
}

void
host_free(struct addresslist *al)
{
	struct address	 *h;

	while ((h = TAILQ_FIRST(al)) != NULL) {
		TAILQ_REMOVE(al, h, entry);
		free(h);
	}
}

struct server *
server_inherit(struct server *src, const char *name,
    struct server_config *addr)
{
	struct server	*dst, *s, *dstl;

	if ((dst = calloc(1, sizeof(*dst))) == NULL)
		fatal("out of memory");

	/* Copy the source server and assign a new Id */
	memcpy(&dst->srv_conf, &src->srv_conf, sizeof(dst->srv_conf));
	if ((dst->srv_conf.tls_cert_file =
	    strdup(src->srv_conf.tls_cert_file)) == NULL)
		fatal("out of memory");
	if ((dst->srv_conf.tls_key_file =
	    strdup(src->srv_conf.tls_key_file)) == NULL)
		fatal("out of memory");
	dst->srv_conf.tls_cert = NULL;
	dst->srv_conf.tls_key = NULL;
	dst->srv_conf.tls_cert_len = 0;
	dst->srv_conf.tls_key_len = 0;

	if (src->srv_conf.return_uri != NULL &&
	    (dst->srv_conf.return_uri =
	    strdup(src->srv_conf.return_uri)) == NULL)
		fatal("out of memory");

	dst->srv_conf.id = ++last_server_id;
	dst->srv_conf.parent_id = dst->srv_conf.id;
	dst->srv_s = -1;

	if (last_server_id == INT_MAX) {
		yyerror("too many servers defined");
		serverconfig_free(&dst->srv_conf);
		free(dst);
		return (NULL);
	}

	/* Now set alias and listen address */
	strlcpy(dst->srv_conf.name, name, sizeof(dst->srv_conf.name));
	memcpy(&dst->srv_conf.ss, &addr->ss, sizeof(dst->srv_conf.ss));
	dst->srv_conf.port = addr->port;
	dst->srv_conf.prefixlen = addr->prefixlen;
	if (addr->flags & SRVFLAG_TLS)
		dst->srv_conf.flags |= SRVFLAG_TLS;
	else
		dst->srv_conf.flags &= ~SRVFLAG_TLS;

	if (server_tls_load_keypair(dst) == -1) {
		yyerror("failed to load public/private keys "
		    "for server %s", dst->srv_conf.name);
		serverconfig_free(&dst->srv_conf);
		free(dst);
		return (NULL);
	}

	/* Check if the new server already exists */
	TAILQ_FOREACH(s, conf->sc_servers, srv_entry) {
		if ((s->srv_conf.flags &
		    SRVFLAG_LOCATION) == 0 &&
		    strcmp(s->srv_conf.name,
		    dst->srv_conf.name) == 0 &&
		    s->srv_conf.port == dst->srv_conf.port &&
		    sockaddr_cmp(
		    (struct sockaddr *)&s->srv_conf.ss,
		    (struct sockaddr *)&dst->srv_conf.ss,
		    s->srv_conf.prefixlen) == 0)
			break;
	}
	if (s != NULL) {
		yyerror("server \"%s\" defined twice",
		    dst->srv_conf.name);
		serverconfig_free(&dst->srv_conf);
		free(dst);
		return (NULL);
	}

	/* Copy all the locations of the source server */
	TAILQ_FOREACH(s, conf->sc_servers, srv_entry) {
		if (!(s->srv_conf.flags & SRVFLAG_LOCATION &&
		    s->srv_conf.parent_id == src->srv_conf.parent_id))
			continue;

		if ((dstl = calloc(1, sizeof(*dstl))) == NULL)
			fatal("out of memory");

		memcpy(&dstl->srv_conf, &s->srv_conf, sizeof(dstl->srv_conf));
		strlcpy(dstl->srv_conf.name, name, sizeof(dstl->srv_conf.name));

		/* Copy the new Id and listen address */
		dstl->srv_conf.id = ++last_server_id;
		dstl->srv_conf.parent_id = dst->srv_conf.id;
		memcpy(&dstl->srv_conf.ss, &addr->ss,
		    sizeof(dstl->srv_conf.ss));
		dstl->srv_conf.port = addr->port;
		dstl->srv_conf.prefixlen = addr->prefixlen;
		dstl->srv_s = -1;

		DPRINTF("adding location \"%s\" for \"%s[%u]\"",
		    dstl->srv_conf.location,
		    dstl->srv_conf.name, dstl->srv_conf.id);

		TAILQ_INSERT_TAIL(conf->sc_servers, dstl, srv_entry);
	}

	return (dst);
}

int
getservice(char *n)
{
	struct servent	*s;
	const char	*errstr;
	long long	 llval;

	llval = strtonum(n, 0, UINT16_MAX, &errstr);
	if (errstr) {
		s = getservbyname(n, "tcp");
		if (s == NULL)
			s = getservbyname(n, "udp");
		if (s == NULL) {
			yyerror("unknown port %s", n);
			return (-1);
		}
		return (s->s_port);
	}

	return (htons((u_short)llval));
}

int
is_if_in_group(const char *ifname, const char *groupname)
{
	unsigned int		 len;
	struct ifgroupreq	 ifgr;
	struct ifg_req		*ifg;
	int			 s;
	int			 ret = 0;

	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		err(1, "socket");

	memset(&ifgr, 0, sizeof(ifgr));
	if (strlcpy(ifgr.ifgr_name, ifname, IFNAMSIZ) >= IFNAMSIZ)
		err(1, "IFNAMSIZ");
	if (ioctl(s, SIOCGIFGROUP, (caddr_t)&ifgr) == -1) {
		if (errno == EINVAL || errno == ENOTTY)
			goto end;
		err(1, "SIOCGIFGROUP");
	}

	len = ifgr.ifgr_len;
	ifgr.ifgr_groups =
	    (struct ifg_req *)calloc(len / sizeof(struct ifg_req),
		sizeof(struct ifg_req));
	if (ifgr.ifgr_groups == NULL)
		err(1, "getifgroups");
	if (ioctl(s, SIOCGIFGROUP, (caddr_t)&ifgr) == -1)
		err(1, "SIOCGIFGROUP");

	ifg = ifgr.ifgr_groups;
	for (; ifg && len >= sizeof(struct ifg_req); ifg++) {
		len -= sizeof(struct ifg_req);
		if (strcmp(ifg->ifgrq_group, groupname) == 0) {
			ret = 1;
			break;
		}
	}
	free(ifgr.ifgr_groups);

end:
	close(s);
	return (ret);
}
#line 1701 "parse.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 8:
#line 159 "parse.y"
	{ file->errors++; }
break;
case 9:
#line 162 "parse.y"
	{
			struct file	*nfile;

			if ((nfile = pushfile(yystack.l_mark[0].v.string, 0)) == NULL) {
				yyerror("failed to include file %s", yystack.l_mark[0].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);

			file = nfile;
			lungetc('\n');
		}
break;
case 10:
#line 177 "parse.y"
	{
			if (symset(yystack.l_mark[-2].v.string, yystack.l_mark[0].v.string, 0) == -1)
				fatal("cannot store variable");
			free(yystack.l_mark[-2].v.string);
			free(yystack.l_mark[0].v.string);
		}
break;
case 11:
#line 185 "parse.y"
	{ yyval.v.number = 0; }
break;
case 12:
#line 186 "parse.y"
	{ yyval.v.number = 1; }
break;
case 13:
#line 189 "parse.y"
	{
			if (loadcfg)
				break;
			if (yystack.l_mark[0].v.number <= 0 || yystack.l_mark[0].v.number > SERVER_MAXPROC) {
				yyerror("invalid number of preforked "
				    "servers: %lld", yystack.l_mark[0].v.number);
				YYERROR;
			}
			conf->sc_prefork_server = yystack.l_mark[0].v.number;
		}
break;
case 14:
#line 199 "parse.y"
	{
			conf->sc_chroot = yystack.l_mark[0].v.string;
		}
break;
case 15:
#line 202 "parse.y"
	{
			conf->sc_logdir = yystack.l_mark[0].v.string;
		}
break;
case 16:
#line 207 "parse.y"
	{
			struct server	*s;

			if (!loadcfg) {
				free(yystack.l_mark[0].v.string);
				YYACCEPT;
			}

			if ((s = calloc(1, sizeof (*s))) == NULL)
				fatal("out of memory");

			if (strlcpy(s->srv_conf.name, yystack.l_mark[0].v.string,
			    sizeof(s->srv_conf.name)) >=
			    sizeof(s->srv_conf.name)) {
				yyerror("server name truncated");
				free(yystack.l_mark[0].v.string);
				free(s);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);

			strlcpy(s->srv_conf.root, HTTPD_DOCROOT,
			    sizeof(s->srv_conf.root));
			strlcpy(s->srv_conf.index, HTTPD_INDEX,
			    sizeof(s->srv_conf.index));
			strlcpy(s->srv_conf.accesslog, HTTPD_ACCESS_LOG,
			    sizeof(s->srv_conf.accesslog));
			strlcpy(s->srv_conf.errorlog, HTTPD_ERROR_LOG,
			    sizeof(s->srv_conf.errorlog));
			s->srv_conf.id = ++last_server_id;
			s->srv_conf.parent_id = s->srv_conf.id;
			s->srv_s = -1;
			s->srv_conf.timeout.tv_sec = SERVER_TIMEOUT;
			s->srv_conf.maxrequests = SERVER_MAXREQUESTS;
			s->srv_conf.maxrequestbody = SERVER_MAXREQUESTBODY;
			s->srv_conf.flags |= SRVFLAG_LOG;
			s->srv_conf.logformat = LOG_FORMAT_COMMON;
			s->srv_conf.tls_protocols = TLS_PROTOCOLS_DEFAULT;
			if ((s->srv_conf.tls_cert_file =
			    strdup(HTTPD_TLS_CERT)) == NULL)
				fatal("out of memory");
			if ((s->srv_conf.tls_key_file =
			    strdup(HTTPD_TLS_KEY)) == NULL)
				fatal("out of memory");
			strlcpy(s->srv_conf.tls_ciphers,
			    HTTPD_TLS_CIPHERS,
			    sizeof(s->srv_conf.tls_ciphers));
			strlcpy(s->srv_conf.tls_dhe_params,
			    HTTPD_TLS_DHE_PARAMS,
			    sizeof(s->srv_conf.tls_dhe_params));
			strlcpy(s->srv_conf.tls_ecdhe_curve,
			    HTTPD_TLS_ECDHE_CURVE,
			    sizeof(s->srv_conf.tls_ecdhe_curve));

			if (last_server_id == INT_MAX) {
				yyerror("too many servers defined");
				free(s);
				YYERROR;
			}
			srv = s;
			srv_conf = &srv->srv_conf;

			SPLAY_INIT(&srv->srv_clients);
			TAILQ_INIT(&srv->srv_hosts);

			TAILQ_INSERT_TAIL(&srv->srv_hosts, srv_conf, entry);
		}
break;
case 17:
#line 273 "parse.y"
	{
			struct server		*s = NULL, *sn;
			struct server_config	*a, *b;

			srv_conf = &srv->srv_conf;

			TAILQ_FOREACH(s, conf->sc_servers, srv_entry) {
				if ((s->srv_conf.flags &
				    SRVFLAG_LOCATION) == 0 &&
				    strcmp(s->srv_conf.name,
				    srv->srv_conf.name) == 0 &&
				    s->srv_conf.port == srv->srv_conf.port &&
				    sockaddr_cmp(
				    (struct sockaddr *)&s->srv_conf.ss,
				    (struct sockaddr *)&srv->srv_conf.ss,
				    s->srv_conf.prefixlen) == 0)
					break;
			}
			if (s != NULL) {
				yyerror("server \"%s\" defined twice",
				    srv->srv_conf.name);
				serverconfig_free(srv_conf);
				free(srv);
				YYABORT;
			}

			if (srv->srv_conf.ss.ss_family == AF_UNSPEC) {
				yyerror("listen address not specified");
				serverconfig_free(srv_conf);
				free(srv);
				YYERROR;
			}

			if ((srv->srv_conf.flags & SRVFLAG_TLS) &&
			    srv->srv_conf.tls_protocols == 0) {
				yyerror("no TLS protocols");
				free(srv);
				YYERROR;
			}

			if (server_tls_load_keypair(srv) == -1) {
				yyerror("failed to load public/private keys "
				    "for server %s", srv->srv_conf.name);
				serverconfig_free(srv_conf);
				free(srv);
				YYERROR;
			}

			DPRINTF("adding server \"%s[%u]\"",
			    srv->srv_conf.name, srv->srv_conf.id);

			TAILQ_INSERT_TAIL(conf->sc_servers, srv, srv_entry);

			/*
			 * Add aliases and additional listen addresses as
			 * individual servers.
			 */
			TAILQ_FOREACH(a, &srv->srv_hosts, entry) {
				/* listen address */
				if (a->ss.ss_family == AF_UNSPEC)
					continue;
				TAILQ_FOREACH(b, &srv->srv_hosts, entry) {
					/* alias name */
					if (*b->name == '\0' ||
					    (b == &srv->srv_conf && b == a))
						continue;

					if ((sn = server_inherit(srv,
					    b->name, a)) == NULL) {
						serverconfig_free(srv_conf);
						free(srv);
						YYABORT;
					}

					DPRINTF("adding server \"%s[%u]\"",
					    sn->srv_conf.name, sn->srv_conf.id);

					TAILQ_INSERT_TAIL(conf->sc_servers,
					    sn, srv_entry);
				}
			}

			/* Remove temporary aliases */
			TAILQ_FOREACH_SAFE(a, &srv->srv_hosts, entry, b) {
				TAILQ_REMOVE(&srv->srv_hosts, a, entry);
				if (a == &srv->srv_conf)
					continue;
				serverconfig_free(a);
				free(a);
			}

			srv = NULL;
			srv_conf = NULL;
		}
break;
case 20:
#line 373 "parse.y"
	{
			struct addresslist	 al;
			struct address		*h;
			struct server_config	*s_conf, *alias = NULL;

			if (parentsrv != NULL) {
				yyerror("listen %s inside location", yystack.l_mark[-2].v.string);
				free(yystack.l_mark[-2].v.string);
				YYERROR;
			}

			if (srv->srv_conf.ss.ss_family != AF_UNSPEC) {
				if ((alias = calloc(1,
				    sizeof(*alias))) == NULL)
					fatal("out of memory");

				/* Add as an alias */
				s_conf = alias;
			} else
				s_conf = &srv->srv_conf;

			TAILQ_INIT(&al);
			if (host(yystack.l_mark[-2].v.string, &al, 1, &yystack.l_mark[0].v.port, NULL, -1) <= 0) {
				yyerror("invalid listen ip: %s", yystack.l_mark[-2].v.string);
				free(yystack.l_mark[-2].v.string);
				YYERROR;
			}
			free(yystack.l_mark[-2].v.string);
			h = TAILQ_FIRST(&al);
			memcpy(&s_conf->ss, &h->ss, sizeof(s_conf->ss));
			s_conf->port = h->port.val[0];
			s_conf->prefixlen = h->prefixlen;
			host_free(&al);

			if (yystack.l_mark[-1].v.number) {
				s_conf->flags |= SRVFLAG_TLS;
			}

			if (alias != NULL) {
				TAILQ_INSERT_TAIL(&srv->srv_hosts,
				    alias, entry);
			}
		}
break;
case 21:
#line 416 "parse.y"
	{
			struct server_config	*alias;

			if (parentsrv != NULL) {
				yyerror("alias inside location");
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}

			if ((alias = calloc(1, sizeof(*alias))) == NULL)
				fatal("out of memory");

			if (strlcpy(alias->name, yystack.l_mark[0].v.string, sizeof(alias->name)) >=
			    sizeof(alias->name)) {
				yyerror("server alias truncated");
				free(yystack.l_mark[0].v.string);
				free(alias);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);

			TAILQ_INSERT_TAIL(&srv->srv_hosts, alias, entry);
		}
break;
case 22:
#line 439 "parse.y"
	{
			if (parentsrv != NULL) {
				yyerror("tcp flags inside location");
				YYERROR;
			}
		}
break;
case 23:
#line 445 "parse.y"
	{
			if (parentsrv != NULL) {
				yyerror("connection options inside location");
				YYERROR;
			}
		}
break;
case 24:
#line 451 "parse.y"
	{
			if (parentsrv != NULL) {
				yyerror("tls configuration inside location");
				YYERROR;
			}
		}
break;
case 31:
#line 463 "parse.y"
	{
			struct server	*s;

			if (srv->srv_conf.ss.ss_family == AF_UNSPEC) {
				yyerror("listen address not specified");
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}

			if (parentsrv != NULL) {
				yyerror("location %s inside location", yystack.l_mark[0].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}

			if (!loadcfg) {
				free(yystack.l_mark[0].v.string);
				YYACCEPT;
			}

			if ((s = calloc(1, sizeof (*s))) == NULL)
				fatal("out of memory");

			if (strlcpy(s->srv_conf.location, yystack.l_mark[0].v.string,
			    sizeof(s->srv_conf.location)) >=
			    sizeof(s->srv_conf.location)) {
				yyerror("server location truncated");
				free(yystack.l_mark[0].v.string);
				free(s);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);

			if (strlcpy(s->srv_conf.name, srv->srv_conf.name,
			    sizeof(s->srv_conf.name)) >=
			    sizeof(s->srv_conf.name)) {
				yyerror("server name truncated");
				free(s);
				YYERROR;
			}

			s->srv_conf.id = ++last_server_id;
			/* A location entry uses the parent id */
			s->srv_conf.parent_id = srv->srv_conf.id;
			s->srv_conf.flags = SRVFLAG_LOCATION;
			s->srv_s = -1;
			memcpy(&s->srv_conf.ss, &srv->srv_conf.ss,
			    sizeof(s->srv_conf.ss));
			s->srv_conf.port = srv->srv_conf.port;
			s->srv_conf.prefixlen = srv->srv_conf.prefixlen;

			if (last_server_id == INT_MAX) {
				yyerror("too many servers/locations defined");
				free(s);
				YYERROR;
			}
			parentsrv = srv;
			srv = s;
			srv_conf = &srv->srv_conf;
			SPLAY_INIT(&srv->srv_clients);
		}
break;
case 32:
#line 523 "parse.y"
	{
			struct server	*s = NULL;

			TAILQ_FOREACH(s, conf->sc_servers, srv_entry) {
				if ((s->srv_conf.flags & SRVFLAG_LOCATION) &&
				    s->srv_conf.id == srv_conf->id &&
				    strcmp(s->srv_conf.location,
				    srv_conf->location) == 0)
					break;
			}
			if (s != NULL) {
				yyerror("location \"%s\" defined twice",
				    srv->srv_conf.location);
				serverconfig_free(srv_conf);
				free(srv);
				YYABORT;
			}

			DPRINTF("adding location \"%s\" for \"%s[%u]\"",
			    srv->srv_conf.location,
			    srv->srv_conf.name, srv->srv_conf.id);

			TAILQ_INSERT_TAIL(conf->sc_servers, srv, srv_entry);

			srv = parentsrv;
			srv_conf = &parentsrv->srv_conf;
			parentsrv = NULL;
		}
break;
case 34:
#line 554 "parse.y"
	{
			srv_conf->flags &= ~SRVFLAG_FCGI;
			srv_conf->flags |= SRVFLAG_NO_FCGI;
		}
break;
case 35:
#line 558 "parse.y"
	{
			srv_conf->flags &= ~SRVFLAG_NO_FCGI;
			srv_conf->flags |= SRVFLAG_FCGI;
		}
break;
case 36:
#line 562 "parse.y"
	{
			srv_conf->flags &= ~SRVFLAG_NO_FCGI;
			srv_conf->flags |= SRVFLAG_FCGI;
		}
break;
case 38:
#line 566 "parse.y"
	{
			srv_conf->flags &= ~SRVFLAG_NO_FCGI;
			srv_conf->flags |= SRVFLAG_FCGI;
		}
break;
case 42:
#line 576 "parse.y"
	{
			if (strlcpy(srv_conf->socket, yystack.l_mark[0].v.string,
			    sizeof(srv_conf->socket)) >=
			    sizeof(srv_conf->socket)) {
				yyerror("fastcgi socket too long");
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);
			srv_conf->flags |= SRVFLAG_SOCKET;
		}
break;
case 47:
#line 597 "parse.y"
	{
			memcpy(&srv_conf->timeout, &yystack.l_mark[0].v.tv,
			    sizeof(struct timeval));
		}
break;
case 48:
#line 601 "parse.y"
	{
			srv_conf->maxrequests = yystack.l_mark[0].v.number;
		}
break;
case 49:
#line 604 "parse.y"
	{
			srv_conf->maxrequestbody = yystack.l_mark[0].v.number;
		}
break;
case 54:
#line 617 "parse.y"
	{
			free(srv_conf->tls_cert_file);
			if ((srv_conf->tls_cert_file = strdup(yystack.l_mark[0].v.string)) == NULL)
				fatal("out of memory");
			free(yystack.l_mark[0].v.string);
		}
break;
case 55:
#line 623 "parse.y"
	{
			free(srv_conf->tls_key_file);
			if ((srv_conf->tls_key_file = strdup(yystack.l_mark[0].v.string)) == NULL)
				fatal("out of memory");
			free(yystack.l_mark[0].v.string);
		}
break;
case 56:
#line 629 "parse.y"
	{
			if (strlcpy(srv_conf->tls_ciphers, yystack.l_mark[0].v.string,
			    sizeof(srv_conf->tls_ciphers)) >=
			    sizeof(srv_conf->tls_ciphers)) {
				yyerror("ciphers too long");
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);
		}
break;
case 57:
#line 639 "parse.y"
	{
			if (strlcpy(srv_conf->tls_dhe_params, yystack.l_mark[0].v.string,
			    sizeof(srv_conf->tls_dhe_params)) >=
			    sizeof(srv_conf->tls_dhe_params)) {
				yyerror("dhe too long");
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);
		}
break;
case 58:
#line 649 "parse.y"
	{
			if (strlcpy(srv_conf->tls_ecdhe_curve, yystack.l_mark[0].v.string,
			    sizeof(srv_conf->tls_ecdhe_curve)) >=
			    sizeof(srv_conf->tls_ecdhe_curve)) {
				yyerror("ecdhe too long");
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);
		}
break;
case 59:
#line 659 "parse.y"
	{
			if (tls_config_parse_protocols(
			    &srv_conf->tls_protocols, yystack.l_mark[0].v.string) != 0) {
				yyerror("invalid TLS protocols");
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);
		}
break;
case 64:
#line 678 "parse.y"
	{
			if (strlcpy(srv->srv_conf.root, yystack.l_mark[0].v.string,
			    sizeof(srv->srv_conf.root)) >=
			    sizeof(srv->srv_conf.root)) {
				yyerror("document root too long");
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);
			srv->srv_conf.flags |= SRVFLAG_ROOT;
		}
break;
case 65:
#line 689 "parse.y"
	{
			if (yystack.l_mark[0].v.number < 0 || yystack.l_mark[0].v.number > INT_MAX) {
				yyerror("invalid strip number");
				YYERROR;
			}
			srv->srv_conf.strip = yystack.l_mark[0].v.number;
		}
break;
case 66:
#line 698 "parse.y"
	{
			srv->srv_conf.flags |= SRVFLAG_NO_AUTH;
		}
break;
case 67:
#line 701 "parse.y"
	{
			struct auth	*auth;

			if ((auth = auth_add(conf->sc_auth, &yystack.l_mark[0].v.auth)) == NULL) {
				yyerror("failed to add auth");
				YYERROR;
			}

			if (auth->auth_id == 0) {
				/* New htpasswd, get new Id */
				auth->auth_id = ++last_auth_id;
				if (last_auth_id == INT_MAX) {
					yyerror("too many auth ids defined");
					auth_free(conf->sc_auth, auth);
					YYERROR;
				}
			}

			srv->srv_conf.auth_id = auth->auth_id;
			srv->srv_conf.flags |= SRVFLAG_AUTH;
		}
break;
case 68:
#line 724 "parse.y"
	{
			if (strlcpy(srv->srv_conf.auth_realm, yystack.l_mark[-2].v.string,
			    sizeof(srv->srv_conf.auth_realm)) >=
			    sizeof(srv->srv_conf.auth_realm)) {
				yyerror("basic auth realm name too long");
				free(yystack.l_mark[-2].v.string);
				YYERROR;
			}
			free(yystack.l_mark[-2].v.string);
			if (strlcpy(yyval.v.auth.auth_htpasswd, yystack.l_mark[0].v.string,
			    sizeof(yyval.v.auth.auth_htpasswd)) >=
			    sizeof(yyval.v.auth.auth_htpasswd)) {
				yyerror("password file name too long");
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);

		}
break;
case 69:
#line 743 "parse.y"
	{
			if (strlcpy(yyval.v.auth.auth_htpasswd, yystack.l_mark[0].v.string,
			    sizeof(yyval.v.auth.auth_htpasswd)) >=
			    sizeof(yyval.v.auth.auth_htpasswd)) {
				yyerror("password file name too long");
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);
		}
break;
case 74:
#line 762 "parse.y"
	{
			if (strlcpy(srv_conf->index, yystack.l_mark[0].v.string,
			    sizeof(srv_conf->index)) >=
			    sizeof(srv_conf->index)) {
				yyerror("index file too long");
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			srv_conf->flags &= ~SRVFLAG_NO_INDEX;
			srv_conf->flags |= SRVFLAG_INDEX;
			free(yystack.l_mark[0].v.string);
		}
break;
case 75:
#line 774 "parse.y"
	{
			srv_conf->flags &= ~SRVFLAG_INDEX;
			srv_conf->flags |= SRVFLAG_NO_INDEX;
		}
break;
case 76:
#line 778 "parse.y"
	{
			srv_conf->flags &= ~SRVFLAG_NO_AUTO_INDEX;
			srv_conf->flags |= SRVFLAG_AUTO_INDEX;
		}
break;
case 77:
#line 782 "parse.y"
	{
			srv_conf->flags &= ~SRVFLAG_AUTO_INDEX;
			srv_conf->flags |= SRVFLAG_NO_AUTO_INDEX;
		}
break;
case 80:
#line 791 "parse.y"
	{
			srv_conf->flags &= ~SRVFLAG_LOG;
			srv_conf->flags |= SRVFLAG_NO_LOG;
		}
break;
case 84:
#line 802 "parse.y"
	{
			srv_conf->flags &= ~SRVFLAG_NO_SYSLOG;
			srv_conf->flags |= SRVFLAG_SYSLOG;
		}
break;
case 85:
#line 806 "parse.y"
	{
			srv_conf->flags &= ~SRVFLAG_SYSLOG;
			srv_conf->flags |= SRVFLAG_NO_SYSLOG;
		}
break;
case 86:
#line 810 "parse.y"
	{
			if (strlcpy(srv_conf->accesslog, yystack.l_mark[0].v.string,
			    sizeof(srv_conf->accesslog)) >=
			    sizeof(srv_conf->accesslog)) {
				yyerror("access log name too long");
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);
			srv_conf->flags |= SRVFLAG_ACCESS_LOG;
		}
break;
case 87:
#line 821 "parse.y"
	{
			if (strlcpy(srv_conf->errorlog, yystack.l_mark[0].v.string,
			    sizeof(srv_conf->errorlog)) >=
			    sizeof(srv_conf->errorlog)) {
				yyerror("error log name too long");
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);
			srv_conf->flags |= SRVFLAG_ERROR_LOG;
		}
break;
case 88:
#line 834 "parse.y"
	{
			srv_conf->flags &= ~SRVFLAG_NO_LOG;
			srv_conf->flags |= SRVFLAG_LOG;
			srv_conf->logformat = LOG_FORMAT_COMMON;
		}
break;
case 89:
#line 839 "parse.y"
	{
			srv_conf->flags &= ~SRVFLAG_NO_LOG;
			srv_conf->flags |= SRVFLAG_LOG;
			srv_conf->logformat = LOG_FORMAT_COMBINED;
		}
break;
case 90:
#line 844 "parse.y"
	{
			srv_conf->flags &= ~SRVFLAG_NO_LOG;
			srv_conf->flags |= SRVFLAG_LOG;
			srv_conf->logformat = LOG_FORMAT_CONNECTION;
		}
break;
case 91:
#line 851 "parse.y"
	{
			if (yystack.l_mark[-1].v.number <= 0 || server_httperror_byid(yystack.l_mark[-1].v.number) == NULL) {
				yyerror("invalid return code: %lld", yystack.l_mark[-1].v.number);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			srv_conf->return_code = yystack.l_mark[-1].v.number;

			if (yystack.l_mark[0].v.string != NULL) {
				/* Only for 3xx redirection headers */
				if (yystack.l_mark[-1].v.number < 300 || yystack.l_mark[-1].v.number > 399) {
					yyerror("invalid return code for "
					    "location URI");
					free(yystack.l_mark[0].v.string);
					YYERROR;
				}
				srv_conf->return_uri = yystack.l_mark[0].v.string;
				srv_conf->return_uri_len = strlen(yystack.l_mark[0].v.string) + 1;
			}
		}
break;
case 92:
#line 871 "parse.y"
	{
			/* No return code, silently drop the connection */
			srv_conf->return_code = 0;
		}
break;
case 93:
#line 875 "parse.y"
	{
			/* Forbidden */
			srv_conf->return_code = 403;
		}
break;
case 94:
#line 879 "parse.y"
	{
			srv_conf->flags &= ~SRVFLAG_BLOCK;
			srv_conf->flags |= SRVFLAG_NO_BLOCK;
		}
break;
case 95:
#line 885 "parse.y"
	{
			srv_conf->flags &= ~SRVFLAG_NO_BLOCK;
			srv_conf->flags |= SRVFLAG_BLOCK;
		}
break;
case 96:
#line 891 "parse.y"
	{ yyval.v.string = NULL; }
break;
case 97:
#line 892 "parse.y"
	{ yyval.v.string = yystack.l_mark[0].v.string; }
break;
case 102:
#line 903 "parse.y"
	{ srv_conf->tcpflags |= TCPFLAG_SACK; }
break;
case 103:
#line 904 "parse.y"
	{ srv_conf->tcpflags |= TCPFLAG_NSACK; }
break;
case 104:
#line 905 "parse.y"
	{
			srv_conf->tcpflags |= TCPFLAG_NODELAY;
		}
break;
case 105:
#line 908 "parse.y"
	{
			srv_conf->tcpflags |= TCPFLAG_NNODELAY;
		}
break;
case 106:
#line 911 "parse.y"
	{
			if (yystack.l_mark[0].v.number < 0 || yystack.l_mark[0].v.number > SERVER_MAX_CLIENTS) {
				yyerror("invalid backlog: %lld", yystack.l_mark[0].v.number);
				YYERROR;
			}
			srv_conf->tcpbacklog = yystack.l_mark[0].v.number;
		}
break;
case 107:
#line 918 "parse.y"
	{
			srv_conf->tcpflags |= TCPFLAG_BUFSIZ;
			if ((srv_conf->tcpbufsiz = yystack.l_mark[0].v.number) < 0) {
				yyerror("invalid socket buffer size: %lld", yystack.l_mark[0].v.number);
				YYERROR;
			}
		}
break;
case 108:
#line 925 "parse.y"
	{
			if (yystack.l_mark[0].v.number < 0) {
				yyerror("invalid ttl: %lld", yystack.l_mark[0].v.number);
				free(yystack.l_mark[-1].v.string);
				YYERROR;
			}
			if (strcasecmp("ttl", yystack.l_mark[-1].v.string) == 0) {
				srv_conf->tcpflags |= TCPFLAG_IPTTL;
				srv_conf->tcpipttl = yystack.l_mark[0].v.number;
			} else if (strcasecmp("minttl", yystack.l_mark[-1].v.string) == 0) {
				srv_conf->tcpflags |= TCPFLAG_IPMINTTL;
				srv_conf->tcpipminttl = yystack.l_mark[0].v.number;
			} else {
				yyerror("invalid TCP/IP flag: %s", yystack.l_mark[-1].v.string);
				free(yystack.l_mark[-1].v.string);
				YYERROR;
			}
			free(yystack.l_mark[-1].v.string);
		}
break;
case 112:
#line 953 "parse.y"
	{
			if (strlcpy(media.media_type, yystack.l_mark[-2].v.string,
			    sizeof(media.media_type)) >=
			    sizeof(media.media_type) ||
			    strlcpy(media.media_subtype, yystack.l_mark[0].v.string,
			    sizeof(media.media_subtype)) >=
			    sizeof(media.media_subtype)) {
				yyerror("media type too long");
				free(yystack.l_mark[-2].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[-2].v.string);
			free(yystack.l_mark[0].v.string);
		}
break;
case 117:
#line 975 "parse.y"
	{
			if (strlcpy(media.media_name, yystack.l_mark[0].v.string,
			    sizeof(media.media_name)) >=
			    sizeof(media.media_name)) {
				yyerror("media name too long");
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);

			if (!loadcfg)
				break;

			if (media_add(conf->sc_mediatypes, &media) == NULL) {
				yyerror("failed to add media type");
				YYERROR;
			}
		}
break;
case 118:
#line 995 "parse.y"
	{
			if (yystack.l_mark[0].v.number <= 0 || yystack.l_mark[0].v.number >= (int)USHRT_MAX) {
				yyerror("invalid port: %lld", yystack.l_mark[0].v.number);
				YYERROR;
			}
			yyval.v.port.val[0] = htons(yystack.l_mark[0].v.number);
		}
break;
case 119:
#line 1002 "parse.y"
	{
			int	 val;

			if ((val = getservice(yystack.l_mark[0].v.string)) == -1) {
				yyerror("invalid port: %s", yystack.l_mark[0].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);

			yyval.v.port.val[0] = val;
		}
break;
case 120:
#line 1017 "parse.y"
	{
			if (yystack.l_mark[0].v.number < 0) {
				yyerror("invalid timeout: %lld", yystack.l_mark[0].v.number);
				YYERROR;
			}
			yyval.v.tv.tv_sec = yystack.l_mark[0].v.number;
			yyval.v.tv.tv_usec = 0;
		}
break;
case 121:
#line 1027 "parse.y"
	{
			char *s;
			if (asprintf(&s, "%lld", yystack.l_mark[0].v.number) == -1) {
				yyerror("asprintf: number");
				YYERROR;
			}
			yyval.v.string = s;
		}
break;
#line 2861 "parse.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
