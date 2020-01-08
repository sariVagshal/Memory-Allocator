#ifndef __MEMORYALLOCATOR_H__
#define __MEMORYALLOCATOR_H__

#include <stddef.h>
#include <stdio.h>

typedef struct MemoryAllocator MemoryAllocator;
struct MemoryAllocator
{
	size_t m_size;
    void* m_memoryPool;
};

struct MemoryAllocator* MemoryAllocator_init(void* memoryPool, size_t size);

void* MemoryAllocator_allocate(struct MemoryAllocator* allocator, size_t size);

/* Return number of still allocated blocks */
size_t MemoryAllocator_free(struct MemoryAllocator* allocator, void* ptr);

/* Return the size of largest free block */
size_t MemoryAllocator_optimize(struct MemoryAllocator* allocator);

#endif /*__MEMORYALLOCATOR_H__*/
