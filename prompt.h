/*Declare New lval Struct */
typedef struct lval {
  int type;
  long num;
  /* Error and Symbol types have some string data */
  char* err;
  char* sym;
  /* Count and Pointer to a list of "lval*" */
  int count;
  struct lval** cell;
} lval;

/* Create Enumeration of possible lval Types */
enum { LVAL_NUM, LVAL_ERR, LVAL_SYM, LVAL_SEXPR, LVAL_QEXPR };

/* Create Enumeration of Possible Error Types */
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

/* Function declarations */
lval* eval(mpc_ast_t*);
lval* eval_op(lval*, char*, lval*);
lval* lval_eval_sexpr(lval*);
lval* lval_eval(lval* v);
lval* lval_pop(lval*, int);
lval* lval_take(lval*, int);
lval* builtin_op(lval*, char*);
lval* lval_num(long);
lval* lval_err(char*);
lval* lval_sym(char*);
lval* lval_qexpr(void);
lval* lval_read_num(mpc_ast_t*);
lval* lval_read(mpc_ast_t*);
lval* lval_add(lval*, lval*);
void lval_expr_print(lval*, char, char);
void lval_print(lval*);
void lval_del(lval*);
void lval_print(lval*);
void lval_println(lval*);