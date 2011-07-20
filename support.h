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

extern MonoAssembly *m_assembly;
extern MonoImage *m_image;
extern MonoDomain *m_domain;

struct assembly_info
{
	const char *name;
};

#define DEFINE_ASSEMBLY(_name) const struct assembly_info __assembly_info = { \
		.name = _name, \
	}

#endif
