/*
 * support.c
 * 
 * Copyright (C) Tom Spink 2011 <tspink@gmail.com>
 * All Rights Reserved
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/image.h>
#include <mono/metadata/debug-helpers.h>
#include "support.h"

/* The assembly information structure. */
extern struct assembly_info __assembly_info;

/* HACK: need to make this generic, so we can provide ONE version of
 * support.o that works for all. */
extern char _binary_test_dll_start;	/* The beginning of the assembly data. */
extern char _binary_test_dll_end;	/* The end of the assembly data. */

static int runtime_started;	/* Whether or not the runtime has been started. */

MonoDomain *m_domain;		/* The execution domain. */
MonoAssembly *m_assembly;	/* The encapsulated assembly. */
MonoImage *m_image;		/* The encapsulated assembly image. */

/**
 * Rewrites the function stub after first run to be very
 * efficient.  Basically, NOPs everything out between two labels.
 */
void sp_rewrite_me(void *slow, void *fast)
{
	unsigned char *code = (unsigned char *)slow;
	while (code < (unsigned char *)fast)
		*code++ = 0x90;
}

/**
 * Starts the mono runtime, and loads the encapsulated assembly, unless
 * it's already been loaded.
 */
void sp_ensure_runtime()
{
	/* Check that the runtime hasn't already been started. */
	if (runtime_started) {
		return;
	}
	
	/* Initialise the JIT. */
	m_domain = mono_jit_init_version(__assembly_info.name, __assembly_info.version);
	if (!m_domain) {
		printf("error: unable to create mono domain\n");
		_exit(0);
	}
	
	/* Open the assembly image, from the data inside the object
	 * file.  This data is accessed via the special symbols created
	 * when the PE is linked in as a binary object.
	 */
	m_image = mono_image_open_from_data(&_binary_test_dll_start, &_binary_test_dll_end - &_binary_test_dll_start, 0, NULL);
	if (!m_image) {
		printf("error: unable to open assembly image\n");
		_exit(0);
	}
	
	/* Now, load the assembly. */
	m_assembly = mono_assembly_load_from_full(m_image, __assembly_info.name, NULL, 0);
	if (!m_assembly) {
		printf("error: unable to load assembly\n");
		_exit(0);
	}
	
	/* Mark the runtime as started, just in case we neglected to
	 * rewrite some function stubs. */
	runtime_started = 1;
}

/**
 * Returns the unmanaged thunk for the given @method_name method
 * descriptor.
 */
void *sp_get_method_thunk(const char *method_name)
{
	MonoMethodDesc *method_desc;
	MonoMethod *method;
	
	/* Create a MonoMethodDesc for the supplied method_name. */
	method_desc = mono_method_desc_new(method_name, 1);
	if (method_desc == NULL) {
		printf("error: unable to create method desc\n");
		_exit(0);
	}
	
	/* Try and find the method in the loaded assembly image. */
	method = mono_method_desc_search_in_image(method_desc, m_image);
	if (method == NULL) {
		printf("error: unable to find method\n");
		_exit(0);
	}

	/* Return the unmanaged thunk for the method. */
	return mono_method_get_unmanaged_thunk(method);
}
