// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "elevatortest.h"

// testnum is set in main.cc
int testnum = 1;

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

/***********
new code begins
***********/
void
SimpleThread()
{
    int num;
    for (num = 0; num < 5; num++) {
	printf("*** thread %d userid %d looped %d times\n", currentThread->tid, currentThread->uid, num);
        currentThread->Yield();
    }
}
/***********
new code ends
***********/

//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1");

    Thread *t = new Thread("forked thread");

    t->Fork(SimpleThread);
    SimpleThread();
}

//----------------------------------------------------------------------
// ThreadTest2
// 	Iteratively create 128 threads, and system will abort due to max
//	thread number limitation eventually.
//----------------------------------------------------------------------

void
ThreadTest2()
{
	DEBUG('t', "Entering ThreadTest2");
	
	for (int i = 1; i <= 128; i++) {
		Thread *t = new Thread("forked thread");
		printf("***thread %d user id %d created.\n", t->getTid(), t->getUserID());
	}
}

//----------------------------------------------------------------------
// ThreadTest3
// 	Print information of running threads.
//----------------------------------------------------------------------

void
ThreadTest3()
{
	DEBUG('t', "Printing threads");
	
}

//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    switch (testnum) {
    case 1:
	ThreadTest1();
	break;
	case 2:
	ThreadTest2();
	break;
	case 3:
	ThreadTest3();
	break;
    default:
	printf("No test specified.\n");
	break;
    }
}

