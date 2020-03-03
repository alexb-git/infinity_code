/* Author: Alex B
** Last update: 18.09.17 21:20
** Program: Testing Circular Buffer
*/

#include <string.h> /* memcpy */
#include <stdio.h>  /* printf */
#include "cbuffer.h" /* vector DS */

#define GREEN   "\x1b[32m"
#define RED     "\x1b[31m"
#define YELLOW  "\x1b[93m"
#define RESET   "\x1b[0m"
#define BLUE    "\x1B[34m"
#define WHITE   "\x1B[37m"

#define YellowSysMessage(X) printf("%-15s\t", X )
#define OKmessage			printf(GREEN "%-7s" RESET, "->OK")
#define ERRORmessage		printf(RED   "%-7s" RESET, "->ERR")

/* the main test function */
void TestCBuffer();

/* prints and compares: 1). CBufferCapacity 
						2). CBufferFreeSpace
						3). CBufferIsEmpty  */
void PrintInfo(	cbuffer_t *test, size_t buffer,
				size_t ex_free_cap, int ex_is_empty );

/* prints and compares: Actually read  */
void PrintReadAction(	cbuffer_t *test, void* src,
						size_t bytes_to_read, size_t ex_read_bytes );

/* prints and compares: Actually written  */
void PrintWriteAction(	cbuffer_t *test, void* src,
						size_t bytes_to_write, size_t ex_written_bytes );

/* prints the addresses of read and write pointer */
extern void PrintAddresses(const cbuffer_t *cbuffer);



int main(int argc, char const *argv[])
{
	TestCBuffer();



	return 0;
}


void TestCBuffer()
{
	size_t buffer = 3;

	char src[] = "Hello Word";
	char des[15]={0};

	cbuffer_t *test = CBufferCreate(buffer);


	printf(YELLOW "%-15s%-7s%-7s%-7s%-7s%-7s%-7s%-7s%-7s%-7s%-7s\n" RESET
            ,"|Acti|"
            ,"|Actu|"  , "|Comp|"
            ,"|Cap|"   , "|Comp|"
            ,"|FreS|"  , "|Comp|"
            ,"|IsEm|"  , "|Comp|"
            ,"|read|"  , "|write|");


	YellowSysMessage("Initial stats:");
	 /* PrintInfo( handler, ex_capacity, ex_free_cap, ex_is_empty) */
	printf("%-7c", '-');
	printf("%-7c", '-');
	PrintInfo(test, buffer, buffer, 1);
	PrintAddresses(test);
	printf("\n");

	YellowSysMessage("Write 5 bytes:");
	PrintWriteAction(test, src, 5, buffer);
	PrintInfo(test, buffer, 0, 0);
	PrintAddresses(test);
	printf("\n");

	YellowSysMessage("Write 1 bytes:");
	PrintWriteAction(test, src, 5, 0);
	PrintInfo(test, buffer, 0, 0);
	PrintAddresses(test);
	printf("\n");	

	YellowSysMessage("Read 5 bytes:");
	PrintReadAction(test, des, 5, buffer);
	PrintInfo(test, buffer, buffer, 1);
	PrintAddresses(test);
	printf("\n");

	YellowSysMessage("Write 1 bytes:");
	PrintWriteAction(test, src, 1, 1);
	PrintInfo(test, buffer, 2, 0);
	PrintAddresses(test);
	printf("\n");

	YellowSysMessage("Read 1 bytes:");
	PrintReadAction(test, des, 1, 1);
	PrintInfo(test, buffer, buffer, 1);
	PrintAddresses(test);
	printf("\n");

	YellowSysMessage("Write 1 bytes:");
	PrintWriteAction(test, src, 1, 1);
	PrintInfo(test, buffer, 2, 0);
	PrintAddresses(test);
	printf("\n");

	YellowSysMessage("Read 1 bytes:");
	PrintReadAction(test, des, 1, 1);
	PrintInfo(test, buffer, buffer, 1);
	PrintAddresses(test);
	printf("\n");

	YellowSysMessage("Write 1 bytes:");
	PrintWriteAction(test, src, 1, 1);
	PrintInfo(test, buffer, 2, 0);
	PrintAddresses(test);
	printf("\n");

	YellowSysMessage("Read 1 bytes:");
	PrintReadAction(test, des, 1, 1);
	PrintInfo(test, buffer, buffer, 1);
	PrintAddresses(test);
	printf("\n");

	YellowSysMessage("Write 1 bytes:");
	PrintWriteAction(test, src, 1, 1);
	PrintInfo(test, buffer, 2, 0);
	PrintAddresses(test);
	printf("\n");

	YellowSysMessage("Read 1 bytes:");
	PrintReadAction(test, des, 1, 1);
	PrintInfo(test, buffer, buffer, 1);
	PrintAddresses(test);
	printf("\n");

	YellowSysMessage("Read 1 bytes:");
	PrintReadAction(test, des, 1, 0);
	PrintInfo(test, buffer, buffer, 1);
	PrintAddresses(test);
	printf("\n");

	CBufferDestroy(test);


}


/****************************************************************************/
void PrintInfo(	cbuffer_t *test, size_t buffer,
				size_t ex_free_cap, int ex_is_empty )
{
	int    is_empty = CBufferIsEmpty(test);
	size_t capacity = CBufferCapacity(test);
	size_t free_cap = CBufferFreeSpace(test);

	printf("%-7lu", capacity);
	(capacity == buffer) ? (OKmessage) : (ERRORmessage);

	printf("%-7lu", free_cap);
	(free_cap == ex_free_cap) ? (OKmessage) : (ERRORmessage);

	printf("%-7d", is_empty);
	(is_empty == ex_is_empty) ? (OKmessage) : (ERRORmessage);
}
/****************************************************************************/
void PrintWriteAction(	cbuffer_t *test, void* src,
						size_t bytes_to_write, size_t ex_written_bytes )
{
	size_t actually_writen = CBufferWrite(test, src, bytes_to_write);

	printf("%-7lu", actually_writen);
	(actually_writen == ex_written_bytes) ? (OKmessage) : (ERRORmessage);
}
/****************************************************************************/
void PrintReadAction(	cbuffer_t *test, void* des,
						size_t bytes_to_read, size_t ex_read_bytes )
{
	size_t	actually_read   = CBufferRead(test, des, bytes_to_read);
	
	printf("%-7lu", actually_read);
	(actually_read == ex_read_bytes) ? (OKmessage) : (ERRORmessage);
}
/****************************************************************************/
