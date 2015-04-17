/* Forward declarations */
struct lval;
struct lenv;
typedef struct lval lval;
typedef struct lenv lenv;

/* Function pointer type */
typedef lval*(*lbuiltin)(lenv*, lval*);

/* Create Enumeration of possible lval Types */
enum { LVAL_NUM, LVAL_ERR, LVAL_SYM, LVAL_FUN, 
       LVAL_SEXPR, LVAL_QEXPR };

/*Declare New lval Struct */
struct lval {
  int type;

  /* Basic */
  long num;
  char* err;
  char* sym;

  //lbuiltin fun;

  /* Function */
  lbuiltin builtin;
  lenv* env;
  lval* formals;
  lval* body;

  /* Expression */
  int count;
  struct lval** cell;
};

/* Variable environment struct */
struct lenv {
    lenv* par;
    int count;
    char** syms;
    lval** vals;
};

/* Create Enumeration of Possible Error Types */
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

/* Function declarations */
lval* eval(mpc_ast_t*);
lval* eval_op(lval*, char*, lval*);
lval* lval_eval_sexpr(lenv*, lval*);
lval* lval_eval(lenv*, lval*);

lval* lval_pop(lval*, int);
lval* lval_take(lval*, int);
lval* lval_join(lval*, lval*);

lval* builtin(lenv*, lval*, char*);
lval* builtin_op(lenv*, lval*, char*);
lval* builtin_head(lenv*, lval*);
lval* builtin_tail(lenv*, lval*);
lval* builtin_list(lenv*, lval*);
lval* builtin_eval(lenv*, lval*);
lval* builtin_join(lenv*, lval*);

/* Math-specific builtins */
lval* builtin_add(lenv* e, lval* a);
lval* builtin_sub(lenv* e, lval* a);
lval* builtin_mul(lenv* e, lval* a);
lval* builtin_div(lenv* e, lval* a);


lval* lval_num(long);
lval* lval_err(char* fmt, ...);
lval* lval_sym(char*);
lval* lval_qexpr(void);
lval* lval_read_num(mpc_ast_t*);
lval* lval_read(mpc_ast_t*);
lval* lval_add(lval*, lval*);
lval* lval_copy(lval* v);
void lval_expr_print(lval*, char, char);
void lval_print(lval*);
void lval_del(lval*);
void lval_print(lval*);
void lval_println(lval*);

/* Variable Environment functions */
lenv* lenv_new(void);
void lenv_del(lenv* e);
lval* lenv_get(lenv* e, lval* k);
void lenv_put(lenv* e, lval* k, lval* v); 

void lenv_add_builtin(lenv* e, char* name, lbuiltin func);
void lenv_add_builtins(lenv* e);

lval* builtin_def(lenv* e, lval* a);
lval* builtin_put(lenv*, lval*, char*);
lval* builtin_var(lenv*, lval*, char*);


char* ltype_name(int);

lval* lval_lambda(lval* formals, lval* body);
lval* builtin_lambda(lenv* e, lval* a);

lenv* lenv_copy(lenv* e);
void lenv_def(lenv* e, lval* k, lval* v);

lval* lval_call(lenv* e, lval* f, lval* a);


lval* builtin_gt(lenv*, lval*);
lval* builtin_lt(lenv*, lval*);
lval* builtin_ge(lenv*, lval*);
lval* builtin_le(lenv*, lval*);
lval* builtin_ord(lenv*, lval*, char*);
int lval_eq(lval*, lval*);
lval* builtin_cmp(lenv*, lval*, char*);
lval* builtin_eq(lenv*, lval*);
lval* builtin_eq(lenv*, lval*);
lval* builtin_ne(lenv*, lval*);
lval* builtin_if(lenv*, lval*);