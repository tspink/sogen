/*
 * so-gen-test.c
 * 
 * Copyright (C) Tom Spink 2011 <tspink@gmail.com>
 * All Rights Reserved
 */
#include <stdio.h>

extern void Test_TestClass_TestStaticMethod(void);
extern int Test_TestClass_TestStaticMethod2(void);
extern void *new_Test_TestClass(void);
extern void *new_Test_TestClass2(int start);
extern void Test_TestClass_TestMethod(void *this);
extern void Test_TestClass_TestMethod2(void *this, char *name);
extern void Test_TestClass_TestMethod3(void *this);

int main(int argc, char **argv)
{
	void *c, *d;
	int r;
	
	printf("calling Test.TestClass.TestStaticMethod...\n");
	for (r = 0; r < 10; r++)
		Test_TestClass_TestStaticMethod();
	
	printf("calling Test.TestClass.TestStaticMethod2...\n");
	r = Test_TestClass_TestStaticMethod2();
	printf("return value: %d\n", r);
	
	printf("constructing Test.TestClass()...\n");
	c = new_Test_TestClass();
	
	printf("calling Test.TestClass.TestMethod...\n");
	for (r = 0; r < 10; r++)
		Test_TestClass_TestMethod(c);

	printf("calling Test.TestClass.TestMethod2...\n");
	Test_TestClass_TestMethod2(c, "Tom");
	
	printf("constructing Test.TestClass(int)...\n");
	d = new_Test_TestClass2(50);
	
	printf("calling Test.TestClass.TestMethod...\n");
	for (r = 0; r < 10; r++)
		Test_TestClass_TestMethod(d);

	printf("calling Test.TestClass.TestMethod3...\n");
	Test_TestClass_TestMethod3(c);
	printf("done.\n");
	return 0;
}
