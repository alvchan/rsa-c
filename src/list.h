#include <stdint.h>

struct list {
	uint8_t val;
	struct list *next;
	struct list *prev;
};

struct list *list_init(void);
void list_free(struct list *l);
void list_append(struct list *l, uint8_t x);
struct list *list_prepend(struct list *l, uint8_t x);
struct list *list_get(const struct list *src, int index);
