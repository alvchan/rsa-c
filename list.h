struct list {
	void *val;
	struct list *next;
	struct list *prev;
};

struct list *list_init(void *val);
void list_free(struct list *l);
void list_free_all(struct list *l);
void list_append(struct list *l, void *val);
struct list *list_prepend(struct list *l, void *val);
