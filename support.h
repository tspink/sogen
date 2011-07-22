/*
 * support.h
 * 
 * Copyright (C) Tom Spink 2011 <tspink@gmail.com>
 * All Rights Reserved.
 */
#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#define __stub __attribute__((section(".stubs,\"awx\"#")))

extern void sp_ensure_runtime(void);
extern void *sp_get_method_thunk(const char *method_name);
extern void sp_rewrite_me(void *slow, void *fast);

extern MonoAssembly *m_assembly;
extern MonoImage *m_image;
extern MonoDomain *m_domain;

struct assembly_info
{
	const char *name;
	const char *version;
};

#define DEFINE_ASSEMBLY(__name, __ver) const struct assembly_info __assembly_info = { \
		.name = __name, \
		.version = __ver, \
	}

#endif
