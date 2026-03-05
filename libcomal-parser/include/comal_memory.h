#ifndef COMAL_MEMORY_H
#define COMAL_MEMORY_H

#define NR_FIXED_POOLS 4

#define PARSE_POOL 0
#define RUN_POOL 1
#define MISC_POOL 2

#define NRCPOOLS 2
#define INT_CPOOL 0
#define FLOAT_CPOOL 1

#define GETCORE(p, a) (a *)mem_alloc((p), sizeof(a))

struct mem_block {
	struct mem_block *next;
	struct mem_block *prev;
	int marker;
	long size;
	struct mem_pool *pool;
};

struct mem_pool {
	long size;
	struct mem_block *root;
	int id;
};

void mem_init(void);
void mem_tini(void);
void *cell_alloc(unsigned int pool);
void *mem_alloc_private(struct mem_pool *pool, long size);
void *mem_alloc(unsigned int pool, long size);
void *mem_realloc(void *block, long newsize);
void cell_free(void *m);
void *mem_free(void *m);
void cell_freepool(unsigned int pool);
void mem_freepool(unsigned int pool);
void mem_freepool_private(struct mem_pool *pool);
void mem_shiftmem(unsigned int frompool, struct mem_pool *topool);
void mem_debug(int level);
struct mem_pool *pool_new(void);
void pool_free(struct mem_pool *pool);

#endif
