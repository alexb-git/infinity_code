/***************************************************
  Filename: wdduncs.h
  Purpose:  Header file for watch dog functions
  Product:  more complex WD
  Version:  42
 ***************************************************/
#ifndef __WD_H__
#define __WD_H__

/*****************************************************************************
**  description: Start wd service, will restart current app on crush after
**               this method was invoked.
**  arguments:   argv - the app argv array.
**  return value: SUCCSESS on succsess, on failure return error num.
**  notes: creates another thread for wd communicaion, uses SIGUSR1 SIGUSR2
**         and SIGCHLD. to end this service call StopWd(). may take some time
**         depending on system load.
******************************************************************************/
int StartWD(char* const *argv);

/*****************************************************************************
**  description: end wd service.
**  arguments:
**  return value: SUCCSESS on succsess, on failure return error num.
**  notes:  stopes the additional thread.
******************************************************************************/
int StopWD();

/*****************************************************************************
**  description: set current app as the watch dog side, USED ONLY BY WD
**  arguments:    none
**  return value: none
******************************************************************************/
void SetIsWD();


#endif /* __WD_H__ */
