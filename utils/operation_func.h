/***************************************************
  Filename: operation_func.h
  Purpose:  Header file for operation function
  Product:  operation function
  Version:  1
 ***************************************************/
#ifndef __OPERATION_FUNC__
#define __OPERATION_FUNC__

/*****************************************************************************
** description:  operation function provided by the user.
** arguments:    param - user's data.
** return value: 1 - continue operation, 0 - operation finished.
** notes:
******************************************************************************/
typedef int (*operation_func)(void *param);

#endif /* __OPERATION_FUNC__ */
