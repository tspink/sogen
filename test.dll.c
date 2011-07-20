/*
 * test.dll.c
 * 
 * Copyright (C) Tom Spink 2011 <tspink@gmail.com>
 * All Rights Reserved
 */
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/image.h>
#include <mono/metadata/debug-helpers.h>
#include "support.h"

static void (*FnTest_TestClass_TestStaticMethod)(MonoException **exception);
__stub void Test_TestClass_TestStaticMethod(void)
{
	MonoException *exception;
	
slow_path:
	sp_ensure_runtime();
	FnTest_TestClass_TestStaticMethod = sp_get_method_thunk("Test.TestClass:TestStaticMethod()");
	sp_rewrite_me(&&slow_path, &&fast_path);
	
fast_path:
	FnTest_TestClass_TestStaticMethod(&exception);
	if (exception != NULL) {
		mono_raise_exception(exception);
	}
}

static int (*FnTest_TestClass_TestStaticMethod2)(MonoException **exception);
__stub int Test_TestClass_TestStaticMethod2(void)
{
	int result;
	MonoException *exception;
	
slow_path:
	sp_ensure_runtime();
	FnTest_TestClass_TestStaticMethod2 = sp_get_method_thunk("Test.TestClass:TestStaticMethod2()");
	sp_rewrite_me(&&slow_path, &&fast_path);

fast_path:
	result = FnTest_TestClass_TestStaticMethod2(&exception);
	if (exception != NULL) {
		mono_raise_exception(exception);
		return 0;
	}
	
	return result;
}

static int (*Fnnew_Test_TestClass)(MonoObject *this, MonoException **exception);
static MonoClass *Test_TestClass;
__stub void *new_Test_TestClass(void)
{
	MonoException *exception;
	MonoObject *obj;
	
slow_path:
	sp_ensure_runtime();
	Test_TestClass = mono_class_from_name(m_image, "Test", "TestClass");
	Fnnew_Test_TestClass = sp_get_method_thunk("Test.TestClass:.ctor()");
	sp_rewrite_me(&&slow_path, &&fast_path);
	
fast_path:
	obj = mono_object_new(m_domain, Test_TestClass);
	Fnnew_Test_TestClass(obj, &exception);
	if (exception != NULL) {
		mono_raise_exception(exception);
		return NULL;
	}
	
	return obj;
}

static int (*Fnnew_Test_TestClass2)(MonoObject *this, int start, MonoException **exception);
__stub void *new_Test_TestClass2(int start)
{
	MonoException *exception;
	MonoObject *obj;
	
slow_path:
	sp_ensure_runtime();
	Test_TestClass = mono_class_from_name(m_image, "Test", "TestClass");
	Fnnew_Test_TestClass2 = sp_get_method_thunk("Test.TestClass:.ctor(int)");
	sp_rewrite_me(&&slow_path, &&fast_path);

fast_path:		
	obj = mono_object_new(m_domain, Test_TestClass);
	Fnnew_Test_TestClass2(obj, start, &exception);
	if (exception != NULL) {
		mono_raise_exception(exception);
		return NULL;
	}
	
	return obj;
}

static int (*FnTest_TestClass_TestMethod)(MonoObject *this, MonoException **exception);
__stub void Test_TestClass_TestMethod(void *this)
{
	MonoException *exception;
	
slow_path:
	sp_ensure_runtime();
	FnTest_TestClass_TestMethod = sp_get_method_thunk("Test.TestClass:TestMethod()");
	sp_rewrite_me(&&slow_path, &&fast_path);
	
fast_path:
	FnTest_TestClass_TestMethod((MonoObject *)this, &exception);
	if (exception != NULL) {
		mono_raise_exception(exception);
	}
}

static int (*FnTest_TestClass_TestMethod2)(MonoObject *this, MonoString *name, MonoException **exception);
__stub void Test_TestClass_TestMethod2(void *this, char *name)
{
	MonoException *exception;
	
slow_path:
	sp_ensure_runtime();
	FnTest_TestClass_TestMethod2 = sp_get_method_thunk("Test.TestClass:TestMethod2(string)");
	sp_rewrite_me(&&slow_path, &&fast_path);
	
fast_path:
	FnTest_TestClass_TestMethod2((MonoObject *)this, mono_string_new(m_domain, name), &exception);
	if (exception != NULL) {
		mono_raise_exception(exception);
	}
}

static int (*FnTest_TestClass_TestMethod3)(MonoObject *this, MonoException **exception);
__stub void Test_TestClass_TestMethod3(void *this)
{
	MonoException *exception;
	
slow_path:
	sp_ensure_runtime();
	FnTest_TestClass_TestMethod3 = sp_get_method_thunk("Test.TestClass:TestMethod3()");
	sp_rewrite_me(&&slow_path, &&fast_path);
	
fast_path:
	FnTest_TestClass_TestMethod3((MonoObject *)this, &exception);
	if (exception != NULL) {
		mono_raise_exception(exception);
	}
}
