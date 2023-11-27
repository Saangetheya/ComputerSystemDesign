#ifndef INTERNAL_HEAP 
#define INTERNAL_HEAP

int proc_last = 1, free_last = 1; // tag id's
int last_address = 0; // this is address size that free blocks are using 
// remember to use this address with the base address of the heap

enum StatusCode {
    SUCCESS = 0,
    FAILURE = 1,
    NULL_POINTER = 2,
    INVALID_TAG = 3,
    INVALID_SIZE = 4,
    INVALID_ADDRESS = 5,
    NOT_ENOUGH_SPACE = 6,
    NOT_FOUND = 7,
};

struct free_block {
    int address; // initial location of the address of the block
    int size_free; // size left free in the block
    int capactity; // capactity of the  block
    int tag; // tag id of the block
    int num_procs; // number of processes using the block
    struct free_block* next;
} *free_head = 0, *free_prev = 0;

enum StatusCode free_block_init(struct free_block*, int);
int free_block_insert(struct free_block*, int);
void free_block_delete(struct free_block*, int);
struct free_block* _free_block_finder(struct free_block*, int);
int free_block_alloc(struct free_block*, int);
int free_block_dealloc(struct free_block*, int, int);

struct proc_block {
    int address; // initial location of the  address of the  block
    int size; // size taken by the process
    int tag; // tag of the block
    int block_id;
    struct proc_block* next;
}*proc_head = nullptr, *proc_prev= nullptr;

#endif 