#include "comal_base.h"
#include "comal_misc.h"
#include "comal_string_utils.h"
#include "comal_id.h"
#include "comal_program.h"

#include <stdarg.h>
#include <string.h>

struct pool_node {
	void *ptr;
	struct pool_node *next;
};

static struct pool_node *pool_lists[NR_FIXED_POOLS];

static void pool_add(unsigned int pool, void *ptr)
{
	struct pool_node *node;

	if (pool >= NR_FIXED_POOLS || ptr == NULL) {
		return;
	}

	node = (struct pool_node *)malloc(sizeof(struct pool_node));
	if (node == NULL) {
		return;
	}

	node->ptr = ptr;
	node->next = pool_lists[pool];
	pool_lists[pool] = node;
}

static void pool_remove(void *ptr)
{
	unsigned int i;

	if (ptr == NULL) {
		return;
	}

	for (i = 0; i < NR_FIXED_POOLS; i++) {
		struct pool_node *prev = NULL;
		struct pool_node *cur = pool_lists[i];

		while (cur != NULL) {
			if (cur->ptr == ptr) {
				if (prev == NULL) {
					pool_lists[i] = cur->next;
				} else {
					prev->next = cur->next;
				}
				free(cur);
				return;
			}
			prev = cur;
			cur = cur->next;
		}
	}
}

void mem_init(void)
{
}

void mem_tini(void)
{
}

void *cell_alloc(unsigned int pool)
{
	return mem_alloc(pool, 1);
}

void *mem_alloc_private(struct mem_pool *pool, long size)
{
	(void)pool;
	if (size <= 0) {
		return NULL;
	}
	return malloc((size_t)size);
}

void *mem_alloc(unsigned int pool, long size)
{
	void *ptr;

	if (size <= 0) {
		return NULL;
	}

	ptr = calloc(1, (size_t)size);
	pool_add(pool, ptr);
	return ptr;
}

void *mem_realloc(void *block, long newsize)
{
	void *ptr;

	if (newsize <= 0) {
		return NULL;
	}

	ptr = realloc(block, (size_t)newsize);
	if (ptr != block) {
		pool_remove(block);
		pool_add(PARSE_POOL, ptr);
	}

	return ptr;
}

void cell_free(void *m)
{
	mem_free(m);
}

void *mem_free(void *m)
{
	if (m == NULL) {
		return NULL;
	}
	pool_remove(m);
	free(m);
	return NULL;
}

void cell_freepool(unsigned int pool)
{
	mem_freepool(pool);
}

void mem_freepool(unsigned int pool)
{
	struct pool_node *cur;

	if (pool >= NR_FIXED_POOLS) {
		return;
	}

	cur = pool_lists[pool];
	pool_lists[pool] = NULL;

	while (cur != NULL) {
		struct pool_node *next = cur->next;
		free(cur->ptr);
		free(cur);
		cur = next;
	}
}

void mem_freepool_private(struct mem_pool *pool)
{
	(void)pool;
}

void mem_shiftmem(unsigned int frompool, struct mem_pool *topool)
{
	(void)frompool;
	(void)topool;
}

void mem_debug(int level)
{
	(void)level;
}

struct mem_pool *pool_new(void)
{
	struct mem_pool *pool = (struct mem_pool *)malloc(sizeof(struct mem_pool));

	if (pool == NULL) {
		return NULL;
	}

	pool->size = 0;
	pool->root = NULL;
	pool->id = -1;

	return pool;
}

void pool_free(struct mem_pool *pool)
{
	free(pool);
}

void *my_reverse(void *root)
{
	struct my_list *prev = NULL;
	struct my_list *cur = (struct my_list *)root;

	while (cur != NULL) {
		struct my_list *next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}

	return prev;
}

int exp_list_of_nums(struct exp_list *root)
{
	struct exp_list *cur = root;

	while (cur != NULL) {
		if (cur->exp == NULL) {
			return 0;
		}
		switch (cur->exp->optype) {
		case T_INTNUM:
		case T_FLOAT:
		case T_EXP_IS_NUM:
			break;
		default:
			return 0;
		}
		cur = cur->next;
	}

	return 1;
}

char *exp_cmd(struct expression *exp)
{
	(void)exp;
	return "";
}

struct comal_line *stat_dup(struct comal_line *stat)
{
	struct comal_line *copy;

	if (stat == NULL) {
		return NULL;
	}

	copy = (struct comal_line *)mem_alloc(PARSE_POOL, (long)sizeof(struct comal_line));
	if (copy == NULL) {
		return NULL;
	}

	memcpy(copy, stat, sizeof(struct comal_line));
	return copy;
}

void my_printf(int stream, int newline, char *s, ...)
{
	FILE *out = stdout;
	va_list ap;

	if (stream == MSG_ERROR || stream == MSG_DEBUG || stream == MSG_TRACE) {
		out = stderr;
	}

	va_start(ap, s);
	vfprintf(out, s, ap);
	va_end(ap);

	if (newline) {
		fputc('\n', out);
	}
}

void fatal(char *s, ...)
{
	va_list ap;

	va_start(ap, s);
	vfprintf(stderr, s, ap);
	va_end(ap);
	fputc('\n', stderr);
	exit(1);
}

char *my_strdup(int pool, char *s)
{
	size_t len;
	char *dest;

	if (s == NULL) {
		return NULL;
	}

	len = strlen(s);
	dest = (char *)mem_alloc((unsigned int)pool, (long)(len + 1));
	if (dest == NULL) {
		return NULL;
	}

	memcpy(dest, s, len + 1);
	return dest;
}

char *my_strcpy(char *to, char *from)
{
	if (to == NULL || from == NULL) {
		return to;
	}

	return strcpy(to, from);
}

void strupr(char *s)
{
	if (s == NULL) {
		return;
	}

	while (*s) {
		if (*s >= 'a' && *s <= 'z') {
			*s = (char)(*s - ('a' - 'A'));
		}
		s++;
	}
}

void strlwr(char *s)
{
	if (s == NULL) {
		return;
	}

	while (*s) {
		if (*s >= 'A' && *s <= 'Z') {
			*s = (char)(*s + ('a' - 'A'));
		}
		s++;
	}
}

void remove_trailing(char *s, char *trailing, char *subst)
{
	size_t slen;
	size_t tlen;

	if (s == NULL || trailing == NULL || subst == NULL) {
		return;
	}

	slen = strlen(s);
	tlen = strlen(trailing);

	if (tlen == 0 || slen < tlen) {
		return;
	}

	if (strcmp(s + slen - tlen, trailing) == 0) {
		s[slen - tlen] = '\0';
		strcat(s, subst);
	}
}

struct string *str_make(int pool, char *s)
{
	struct string *str;
	size_t len;

	if (s == NULL) {
		return NULL;
	}

	len = strlen(s);
	str = (struct string *)STR_ALLOC(pool, (long)(len + 1));
	if (str == NULL) {
		return NULL;
	}

	str->len = (long)len;
	memcpy(str->s, s, len + 1);
	return str;
}

struct string *str_make2(int pool, long len)
{
	struct string *str;

	if (len < 0) {
		return NULL;
	}

	str = (struct string *)STR_ALLOC(pool, len + 1);
	if (str == NULL) {
		return NULL;
	}

	str->len = len;
	str->s[0] = '\0';
	return str;
}

int id_eql(struct id_rec *id1, struct id_rec *id2)
{
	if (id1 == id2) {
		return 1;
	}

	if (id1 == NULL || id2 == NULL) {
		return 0;
	}

	return strcmp(id1->name, id2->name) == 0;
}

static struct id_rec *id_root = NULL;

void id_reset(void)
{
	id_root = NULL;
}

struct id_rec *id_search(char *id)
{
	struct id_rec **cur = &id_root;
	int cmp;
	size_t len;

	if (id == NULL) {
		return NULL;
	}

	while (*cur != NULL) {
		cmp = strcmp(id, (*cur)->name);
		if (cmp == 0) {
			return *cur;
		}
		if (cmp < 0) {
			cur = &(*cur)->left;
		} else {
			cur = &(*cur)->right;
		}
	}

	len = strlen(id);
	*cur = (struct id_rec *)mem_alloc(PARSE_POOL, (long)(sizeof(struct id_rec) + len));
	if (*cur == NULL) {
		return NULL;
	}

	(*cur)->left = NULL;
	(*cur)->right = NULL;
	(*cur)->type = V_ERROR;
	memcpy((*cur)->name, id, len + 1);

	return *cur;
}

void prog_addline(struct comal_line *line)
{
	(void)line;
}

int prog_del(struct comal_line **root, long from, long to, int mainprog)
{
	(void)root;
	(void)from;
	(void)to;
	(void)mainprog;
	return 0;
}

long prog_highest_line(void)
{
	return 0;
}

void prog_total_scan(void)
{
}

void prog_new(void)
{
}

void prog_load(char *fn)
{
	(void)fn;
}

void prog_run(void)
{
}
