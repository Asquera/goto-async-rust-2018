
struct server_t {
    unsigned int port;
};

struct rvalue_t {
    void         *ignore_me;
    unsigned int code;
};

unsigned int initialise(struct server_t **, unsigned int);

const char *reverse(const char*);

struct rvalue_t myfunction();