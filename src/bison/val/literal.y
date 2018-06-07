ast_literal* literal_node;
ast_int_val* int_node;
ast_real_val* real_node;
ast_array_val* array_node;

#union

%type <literal_node> literal
%type <int_node> int
%type <real_node> real
%type <array_node> array

%%

literal:
    int {
        $$ = $1;
    }
    | real {
        $$ = $1;
    }
    | CHAR {
        $$ = new ast_char_val($1);
        YY_SET_LOCATION($$);
    }
    | BOOL_TRUE {
        $$ = new ast_bool_val(true);
        YY_SET_LOCATION($$);
    }
    | BOOL_FALSE {
        $$ = new ast_bool_val(false);
        YY_SET_LOCATION($$);
    }
;

int:
    INT {
        $$ = new ast_int_val($1);
        YY_SET_LOCATION($$);
    }
    | SYM_ADD INT {
        $$ = new ast_int_val($1);
        YY_SET_LOCATION($$);
    }
    | SYM_SUB INT {
        $$ = new ast_int_val(-$1);
        YY_SET_LOCATION($$);
    }
;

real:
    REAL {
        $$ = new ast_real_val($1);
        YY_SET_LOCATION($$);
    }
    | SYM_ADD REAL {
        $$ = new ast_real_val($1);
        YY_SET_LOCATION($$);
    }
    | SYM_SUB REAL {
        $$ = new ast_real_val(-$1);
        YY_SET_LOCATION($$);
    }
;

array:
    SYM_LPAREN exp_seq_with_array_at_least_2 SYM_RPAREN {
        $$ = new ast_array_val($2);
        YY_SET_LOCATION($$);
    }
;
