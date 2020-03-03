/****************************************************************************
** Filename:    - stackcalc.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - implementations of Stack Calculator
** Date:        - 8/1/2017
** Version:     - 34
*****************************************************************************/
#include <stdlib.h>     /* malloc, free */
#include <assert.h>     /* assert */
#include <float.h>		/* DBL_MAX */
#include <ctype.h>      /* isspace */

#include "stackcalc.h"  /* Sorting Algorithms */
#include "stack.h"      /* stack header file */

/****************************************************************************
    Macros for this program
*****************************************************************************/
#define OP_CAPACITY  (40)
#define NUM_CAPACITY (40)
#define No_OF_STATES (4)
#define No_OF_EVENTS (8)

#define PromoteEquation(X)  (++X->equation)
#define GetChar(X)          (*X->equation)
#define GetEvent(X)         ((int)*X->equation)
#define GetNumber(X)        (*(double*)StackPeek(X->numbers_stack))
#define GetOperation(X)     (*(char*)StackPeek(X->operation_stack))
#define IsOPStackEmpty(X)   (StackCount(X->operation_stack) == 0)
#define CheckPush(X)        if(X==0){return error;}

/****************************************************************************
    enumes for this program
*****************************************************************************/
typedef enum state
{
    error,         /* == 0 */
    start,         /* == 1 */
    recieved_num,  /* == 2 */
    recieved_op    /* == 3 */

} state_e;

typedef enum event
{
    illegal_input, /* == 0 */

    number, /* == 1 */
    op_bra, /* == 2 */
    cl_bra, /* == 3 */

    addi,   /* == 4 */
    subs,   /* == 5 */

    mult,   /* == 6 */
    divi = mult

} event_e;

/****************************************************************************
    the Stack Calculator handler
*****************************************************************************/
typedef struct FSMHandler
{
    stack_t *numbers_stack;     /* stack of doubles */
    stack_t *operation_stack;   /* stack of operations - represented as char */
    char    *equation;          /* pointer to what's left to calculate */

} FSMHandler_t;

/*****************************************************************************
    perform the corresponding function and return the current state
******************************************************************************/
typedef state_e (*func)(FSMHandler_t *handler);

/****************************************************************************
    function declarations
*****************************************************************************/
static FSMHandler_t* CreateCalcHandler(char *equation);
static void DestroyCalcHandler(FSMHandler_t*handler);

static state_e CalcTillEmpty  (FSMHandler_t *handler);
static state_e CalcAndPush    (FSMHandler_t *handler);
static state_e InsertNumber   (FSMHandler_t *handler);
static state_e InsertOperators(FSMHandler_t *handler);
static state_e CalcBrackets   (FSMHandler_t *handler);
static state_e ErrFunc        (FSMHandler_t *handler);

static void InitTransTable(func transition_func[][No_OF_EVENTS]);
static void InitCharLUT(size_t arr[]);

static int IsCurrHigherPrec(char curr_operator, char last_in_stack);
static int PoweOfOperator(char operator);

/****************************************************************************
    simulate Finite State Machine for calculation, solve the equation
*****************************************************************************/
double StackCalculator(char *equation)
{
    static size_t char_LUT[256] = {0};

    state_e  state         = start;
    double   result        = 0;

    FSMHandler_t *handler  = NULL;

    func transition_funcs[No_OF_STATES][No_OF_EVENTS];
    func func2do;

    assert( equation != NULL );

    handler = CreateCalcHandler(equation);
    if ( NULL == handler )
    {
        return error;
    }

    InitCharLUT(char_LUT);
    InitTransTable(transition_funcs);

    /**********************************************************
        the core functionality of this program is this loop
    ***********************************************************/
    /* while (1) not end of string (EOF)
             (2) state != error */
    while ( GetChar(handler) && state )
    {
        if ( !isspace(GetChar(handler)) ) /* if not white space */
        {
            func2do = transition_funcs[state][char_LUT[GetEvent(handler)]];
            state   = func2do(handler);
        }
        else /* ignore white spaces */
        {
            PromoteEquation(handler);
        }
    }

    if ( error != state )
    {
        state = CalcTillEmpty(handler);
    }

    if ( error == state ) /* case: '(' was found with no matching ')' */
    {
        DestroyCalcHandler(handler);
        return DBL_MAX;
    }

    result = GetNumber(handler);
    DestroyCalcHandler(handler);
    handler = NULL;

    return result;
}

/****************************************************************************
   dealing with numbers that start with '-' (minus / substract)
*****************************************************************************/
state_e InsertNegativeNumber(FSMHandler_t *handler)
{
    /*  '-' ==(translates to)=> '(-1)*':
        '-1' pushed to numbers stack,
        '*' pushed to operations stack  */

    double minus_one = -1;
    char   multiplication = '*';

    assert( handler != NULL );

    CheckPush(StackPush(handler->numbers_stack  , &minus_one));
    CheckPush(StackPush(handler->operation_stack, &multiplication));

    PromoteEquation(handler);

    return recieved_op;
}

/****************************************************************************
   dealing with numbers that start with '+' (plus / addition)
*****************************************************************************/
state_e InsertWithPlusNumber(FSMHandler_t *handler)
{
    /*  '+' ==(translates to)=> '(+1)*':
        '1' pushed to numbers stack,
        '*' pushed to operations stack  */

    double plus_one = 1;
    char   multiplication = '*';

    assert( handler != NULL );

    CheckPush(StackPush(handler->numbers_stack  , &plus_one));
    CheckPush(StackPush(handler->operation_stack, &multiplication));

    PromoteEquation(handler);

    return recieved_op;
}

/****************************************************************************
   push number to the operands stack
*****************************************************************************/
static state_e InsertNumber(FSMHandler_t *handler)
{
    double num;

    assert( handler != NULL );

    num = strtod(handler->equation, &handler->equation);

    CheckPush(StackPush(handler->numbers_stack, &num));

    return recieved_num;
}

/****************************************************************************
   push operator to the operators stack
*****************************************************************************/
static state_e InsertOperators(FSMHandler_t *handler)
{
    state_e state = recieved_op;

    assert( handler != NULL );

    /* while (1) operations stack is not empty
             (2) previous operation is not '('
             (3) current operation has lower precedence
             (4) push was successful (!= error) */
    while(    !IsOPStackEmpty(handler)
           &&  GetOperation(handler) != '('
           && !IsCurrHigherPrec(GetChar(handler), GetOperation(handler))
           &&  state    )
    {
        state = CalcAndPush(handler);
    }

    /* push new operation onto the operation stack and promote the equation */
    CheckPush(StackPush(handler->operation_stack, handler->equation));
    PromoteEquation(handler);

    return (state) ? (recieved_op) : (error);
}

/****************************************************************************
   calculate expression till open bracket
*****************************************************************************/
static state_e CalcBrackets(FSMHandler_t *handler)
{
    state_e state = recieved_op;

    assert( handler != NULL );

    /* while (1) operations stack is not empty
             (2) previous operation is not '('
             (3) push was successful (!= error) */
    while (   !IsOPStackEmpty(handler)
            && GetOperation(handler) != '('
            && state )
    {
        state = CalcAndPush(handler);
    }

    /* case: opening bracket '(' was not found */
    if ( IsOPStackEmpty(handler) || (error == state) )
    {
        return error;
    }

    StackPop(handler->operation_stack); /* pop out '(' */
    PromoteEquation(handler);

    return recieved_num;
}

/****************************************************************************
    calculate till stack is empty
*****************************************************************************/
static state_e CalcTillEmpty(FSMHandler_t *handler)
{
    state_e state = recieved_num;

    assert( handler != NULL );

    /* while (1) there are operation to perform
             (2) push was successful (!= error) */
    while ( !IsOPStackEmpty(handler) && state )
    {
        if ( GetOperation(handler) == '(' )
        {
            /* case: '(' was found with no matching ')' */
            return error;
        }

        state = CalcAndPush(handler);
    }

    return (state) ? (recieved_op) : (error);
}
/****************************************************************************
   calculate one expression
*****************************************************************************/
static state_e CalcAndPush(FSMHandler_t *handler)
{
    double num1;
    double num2;
    double result;
    char   operation;

    assert( handler != NULL );

    num1 = GetNumber(handler);
    StackPop(handler->numbers_stack);

    num2 = GetNumber(handler);
    StackPop(handler->numbers_stack);

    operation = GetOperation(handler);
    StackPop(handler->operation_stack);

    switch ( operation )
    {
        case '+': result = num2 + num1; break;
        case '-': result = num2 - num1; break;
        case '*': result = num2 * num1; break;
        case '/': result = num2 / num1; break;
    }

    CheckPush(StackPush(handler->numbers_stack, &result));

    return recieved_num;
}

/****************************************************************************
   calculate expression till stuck is empty
*****************************************************************************/
static state_e ErrFunc(FSMHandler_t *handler)
{
    return error;
}

/****************************************************************************
    CheckPrecedence
*****************************************************************************/
static int IsCurrHigherPrec(char curr_operator, char last_in_stack)
{
    return PoweOfOperator(curr_operator) > PoweOfOperator(last_in_stack);
}

/*==========================  PoweOfOperator  ==========================*/
static int PoweOfOperator(char operation)
{
    switch ( operation )
    {
        case '+': return 0;
        case '-': return 0;
        case '*': return 1;
        case '/': return 1;
        case '(': return 2;

        default : return -1; /* reaches end of non-void function */
    }
}

/*==========================  CreateCalcHandler  ==========================*/
static FSMHandler_t* CreateCalcHandler(char *equation)
{
    FSMHandler_t *handler = (FSMHandler_t*)malloc(sizeof(FSMHandler_t));
    if (NULL == handler)
    {
        return NULL;
    }

    /* allocate and create stack for numbers */
    handler->numbers_stack = StackCreate(sizeof(double), NUM_CAPACITY);
    if (NULL == handler->numbers_stack)
    {
        free(handler);
        handler = NULL;
        return NULL;
    }

    /* allocate and create stack for operations */
    handler->operation_stack = StackCreate(sizeof(char), OP_CAPACITY);
    if (NULL == handler->operation_stack)
    {
        free(handler->numbers_stack);
        handler->numbers_stack = NULL;

        free(handler);
        handler = NULL;

        return NULL;
    }

    /* copy equation string into the handler */
    handler->equation = equation;

    return handler;
}

/*==========================  DestroyCalcHandler  ==========================*/
static void DestroyCalcHandler(FSMHandler_t *handler)
{
    assert( handler != NULL );

    StackDestroy(handler->numbers_stack);
    handler->numbers_stack = NULL;

    StackDestroy(handler->operation_stack);
    handler->operation_stack = NULL;

    free(handler);
    handler = NULL;
}

/*==========================  InitTransTable  ==========================*/
static void InitTransTable(func transition_func[][No_OF_EVENTS])
{
    size_t i;

    for ( i = 0 ; i < No_OF_STATES ; ++i )
    {
        size_t j;

        for ( j = 0 ; j < No_OF_EVENTS ; ++j )
        {
            transition_func[i][j] = ErrFunc;
        }
    }

    transition_func[start       ][number] = InsertNumber;
    transition_func[start       ][op_bra] = InsertOperators;
    transition_func[start       ][subs  ] = InsertNegativeNumber;

    transition_func[recieved_num][cl_bra] = CalcBrackets;
    transition_func[recieved_num][mult  ] = InsertOperators;
    transition_func[recieved_num][addi  ] = InsertOperators;
    transition_func[recieved_num][subs  ] = InsertOperators;
    transition_func[recieved_num][divi  ] = InsertOperators;

    transition_func[recieved_op][number ] = InsertNumber;
    transition_func[recieved_op][op_bra ] = InsertOperators;
    transition_func[recieved_op][subs   ] = InsertNegativeNumber;
    transition_func[recieved_op][addi   ] = InsertWithPlusNumber;
}

/*==========================  InitCharLUT  ==========================*/
static void InitCharLUT(size_t look_up_table[])
{
    int i;

    /* init numbers */
    for ( i = '0' ; i <= '9' ; ++i )
    {
        look_up_table[i] = number;
    }

    look_up_table[illegal_input] = 0;

    look_up_table['('] = op_bra;
    look_up_table[')'] = cl_bra;
    look_up_table['+'] = addi;
    look_up_table['-'] = subs;
    look_up_table['*'] = mult;
    look_up_table['/'] = divi;
}
