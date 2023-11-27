#include "heap.h"

/**
 * \brief initializes a free block with given tag
 *
 * \param free_head the head of the free list
 * \param tag the tag of the block to be initialized
 *
 * \returns INVALID_TAG if tag is invalid, 0 else (SUCCESS)
 *
 * \note initialize only the last free block with given tag
*/
enum StatusCode free_block_init(struct free_block* free_head, int tag) {
    struct free_block* pre = free_head;

    while (pre != 0 && pre->tag != tag) {
        pre = pre->next;
    }

    if (pre == 0) return INVALID_TAG;

    pre->address = last_address;
    pre->capactity = 0;
    pre->num_procs = 0;
    pre->size_free = 0;
    pre->next = 0;

    return SUCCESS;
}

/**
 * \brief inserts a new block at the end of the free list with given size
 *
 * \param free_head the head of the free list
 * \param size the size of the block to be inserted
 *
 * \returns tag id (>=1) if successful, -1 else
 *
 * \note the address of the block is set to last_address
 * \note the tag of the block is set to free_last
 * \note the capactity of the block is set to size
*/
int free_block_insert(struct free_block* free_head, int size) {
    if (size == 0) return -1;

    struct free_block* new_blk = (struct free_block*)malloc(sizeof(struct free_block));
    new_blk->tag = free_last; // tag is set to free_last
    free_block_init(free_head, new_blk->tag);

    new_blk->size_free = size; // size blocks got alloted
    new_blk->address = last_address;
    new_blk->capactity = size;

    last_address += size; // last address got updated for next allocation
    free_last++; // free_last got updated for next allocation

    if (free_head == 0) {
        free_head = new_blk;
        return SUCCESS;
    }

    struct free_block* pre = free_head;

    while (pre->next != 0) {
        pre = pre->next;
    }

    pre->next = new_blk;

    return new_blk->tag;
}

/**
 * \brief deletes a block with given tag
 *
 * \param free_head the head of the free list
 * \param tag the tag of the block to be deleted
 *
 * \returns NULL_POINTER if free_head is null, NOT_FOUND if tag is not found, SUCCESS else
 * \note remember to free the process block tha used this block using the block_id
*/
void free_block_delete(struct free_block* free_head, int tag) {
    if (free_head == 0) return NULL_POINTER;

    struct free_block* pre = free_head;
    struct free_block* pre_pre = 0;

    while (pre != 0 && pre->tag != tag) {
        pre_pre = pre;
        pre = pre->next;
    }

    if (pre == 0) return NOT_FOUND;

    if (pre_pre == 0) {
        free_head = pre->next;
        free(pre);
        return SUCCESS;
    }

    pre_pre->next = pre->next;
    pre_pre->capactity += pre->capactity;

    free(pre);
    return SUCCESS;
}

/**
 * \brief finds the best fit block for a process with given size
 *
 * \param free_head the head of the free list
 * \param size the size of the block to be allocated
 *
 * \returns the free block if successful, 0 else
 *
 * \note best fit algorithm is used. we can limitate the allocation of free blocks based
 * on number of parameters like size, number of processes using the block, etc. here.
*/
struct free_block* _free_block_finder(struct free_block* free_head, int size) {
    struct free_block* pre = free_head;

    int best_size = __INT32_MAX__;
    struct free_block* best_block = 0;

    while (pre != 0) {
        if (pre->size_free >= size) {
            int diff = pre->size_free - size;
            if (diff < best_size) {
                best_size = diff;
                best_block = pre;
            }
        }

        pre = pre->next;
    }

    return best_block;
}


/**
 * \brief allocates size in free block for a process
 * \param free_head the head of the free list
 * \param size the size of the block to be allocated
 *
 * \returns the tag of the block if successful, else 1
 * \note best fit algorithm is used
*/
int free_block_alloc(struct free_block* free_head, int size) {
    struct free_block* _alloted_block = _free_block_finder(free_head, size);

    if (size == 0) return -1;
    if (_alloted_block == 0) return -1;

    int used = _alloted_block->capactity - _alloted_block->size_free;
    int address = _alloted_block->address + used;

    _alloted_block->address += size; // size blocks got alloted 
    _alloted_block->size_free -= size;
    _alloted_block->num_procs++;

    return _alloted_block->tag;
}

/**
 * \brief deallocates size in free block by a process
 *
 * \param free_head the head of the free list
 * \param tag the tag of the block to be deallocated
 * \param size the amount of size to be deallocated
 *
 * \returns 0 if successful, NOT_FOUND if tag is not found, INVALID_SIZE if size is invalid, else 1
*/
int free_block_dealloc(struct free_block* free_head, int tag, int size) {
    if (free_head == 0) return NULL_POINTER;

    struct free_block* pre = free_head;

    while (pre != 0 && pre->tag != tag) {
        pre = pre->next;
    }

    if (pre == 0) return NOT_FOUND;
    if (pre->size_free + size > pre->capactity) return INVALID_SIZE;

    pre->size_free += size;
    pre->num_procs--;

    return SUCCESS;
}

/**
 * \brief returns the free block with given tag
 *
 * \param free_head the head of the free list
 * \param tag the tag of the block to be returned
 *
 * \returns the free block if successful, NOT_FOUND , else NULL_POINTER
*/
struct free_block* free_block_at(struct free_block* free_head, int tag) {
    if (free_head == 0) return NULL_POINTER;

    struct free_block* pre = free_head;

    while (pre != 0 && pre->tag != tag) {
        pre = pre->next;
    }

    if (pre == 0) return NOT_FOUND;
    return pre;
}

/**
 * \brief returns the number of free blocks
 *
 * \param free_head the head of the free list
 * \returns the number of free blocks
*/
int free_block_length(struct free_block* free_head) {
    if (free_head == 0) return NULL_POINTER;

    int c = 0;
    struct free_block* pre = free_head;
    while (pre != 0) {
        c++;
        pre = pre->next;
    }

    return c;
}

int free_block_get_free_space(struct free_block* free_head) {
    if (free_head == 0) return NULL_POINTER;

    int c = 0;
    struct free_block* pre = free_head;
    while (pre != 0) {
        c += pre->size_free;
        pre = pre->next;
    }

    return c;
}

int free_block_get_used_space(struct free_block* free_head) {
    if (free_head == 0) return 0;
    int c = 0;
    struct free_block* pre = free_head;
    while (pre != 0) {
        c += pre->capactity - pre->size_free;
        pre = pre->next;
    }

    return c;
}

/**
 * \brief initializes a process block with given tag
 *
 * \param proc_head the head of the process list
 * \param tag the tag of the block to be initialized
 *
 * \returns INVALID_TAG if tag is invalid, 0 else (SUCCESS)
*/
int proc_block_init(struct proc_block* proc_head, int tag) {
    if (proc_head == 0) return NULL_POINTER;

    struct proc_block* pre = proc_head;

    while (pre != 0 && pre->tag != tag) {
        pre = pre->next;
    }

    if (pre == 0) return INVALID_TAG;

    pre->address = 0;
    pre->size = 0;
    pre->block_id = -1;
    pre->next = 0;

    return SUCCESS;
}

/**
 * \brief inserts a new block at the end of the process list
 *
 * \param proc_head the head of the process list
 *
 * \returns tag id (>=1) if successful, -1 else
*/
int proc_block_insert(struct proc_block* proc_head) {
    if (proc_head == 0) return -1;

    struct proc_block* new_blk = (struct proc_block*)malloc(sizeof(struct proc_block));
    new_blk->tag = proc_last;
    proc_block_init(proc_head, new_blk->tag);
    proc_last++;

    if (proc_head == 0) {
        proc_head = new_blk;
        return new_blk->tag;
    }

    struct proc_block* pre = proc_head;

    while (pre->next != 0) {
        pre = pre->next;
    }

    pre->next = new_blk;
    return new_blk->tag;
}

/**
 * \brief deletes a block with given tag and deallocates the memory used by the block
 *
 * \param proc_head the head of the process list
 * \param tag the tag of the block to be deleted
 *
 * \returns 0 if successful, NOT_FOUND if tag is not found, INVALID_SIZE if size is invalid, else -1
*/
int proc_block_delete(struct proc_block* proc_head, int tag) {
    if (proc_head == 0) return NULL_POINTER;

    struct proc_block* pre = proc_head;
    struct proc_block* pre_pre = 0;

    while (pre != 0 && pre->tag != tag) {
        pre_pre = pre;
        pre = pre->next;
    }

    if (pre == 0) return NOT_FOUND;

    int code = free_block_dealloc(free_head, pre->block_id, pre->size);
    if (code == NOT_FOUND) return NOT_FOUND;
    if (code == INVALID_SIZE) return -1;

    if (pre_pre == 0) {
        proc_head = pre->next;
        free(pre);
        return SUCCESS;
    }

    pre_pre->next = pre->next;
    free(pre);
    return SUCCESS;
}

struct proc_block* proc_block_at(struct proc_block* proc_head, int tag) {
    if (proc_head == 0) return 0;

    struct proc_block* pre = proc_head;

    while (pre != 0 && pre->tag != tag) {
        pre = pre->next;
    }

    return pre;
}


/**
 * \brief allocates size in free block for a process
 *
 * \param proc_head the head of the process list
 * \param size the size of the block to be allocated
 *
 * \returns the address of the block if successful,-1 else
*/
enum StatusCode proc_block_alloc(struct proc_block* proc_head, int size) {
    if (proc_head == 0) return -1;

    struct proc_block* pre = proc_head;
    int new_tag = proc_block_insert(proc_head);

    if (new_tag == -1) return -1;

    struct proc_block* new_blk = proc_block_at(proc_head, new_tag);

    int free_tag = free_block_alloc(free_head, size);
    if (free_tag == -1) return -1;

    new_blk->block_id = free_tag;
    new_blk->size = size;
    new_blk->address = free_block_at(free_head, free_tag)->address - size; // we need to do this 
    // because values are updated for next allocation

    return new_blk->address;
}

// update is disabled to make more use of this small individual components