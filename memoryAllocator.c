#include <stdio.h>
#include <stdlib.h>
#include "memoryAllocator.h"

size_t Aligment(size_t size)
{
   if (!size % sizeof(size_t))
       return size;

   return size + (sizeof(size_t) - (size % sizeof(size_t)));
}

MemoryAllocator* MemoryAllocator_init(void* memoryPool, size_t size)
{

   MemoryAllocator * memory = (MemoryAllocator *)malloc(sizeof(memoryPool));
   memory->m_memoryPool = memoryPool;

   if (size % sizeof(size_t))
   {
       memory->m_size = Aligment(size) - sizeof(size_t);
   }

   else
   {
       memory->m_size = size;
   }

   (*(char* )memory->m_memoryPool) = memory->m_size + 1;
   return memory;
}

void* MemoryAllocator_allocate(MemoryAllocator* allocator, size_t size)
{
   char * ptr;
   size_t  i = 0;
   size_t newSize = Aligment(size + 1);
   ptr = allocator->m_memoryPool;

   if (allocator->m_size < newSize)
   {
       printf("%s", "ERROR IN ALLOCAITION");
   }

   while (i < allocator->m_size)
   {

       if ( *ptr % sizeof(size_t))
       {

           if (*ptr - 1 >= newSize)
           {
               allocator->m_size -= newSize;
               *(ptr + newSize) = *(ptr) - newSize;
               *(ptr) = newSize;
               return ptr + 1;
           }

           else
           {
               i += *ptr - 1;
               ptr += *ptr -1;
           }
       }
       i += *ptr;
       ptr += *ptr;
   }

}

size_t MemoryAllocator_free(MemoryAllocator* allocator, void* ptr)
{
   allocator->m_size += *((char* )ptr -1);
   *((char* )ptr -1) += 1;
   return allocator->m_size;

}

size_t MemoryAllocator_optimize(MemoryAllocator* allocator)
{
   size_t maxSize = 0;
   size_t s2 = allocator->m_size;
   char * ptr = allocator->m_memoryPool;

   while (s2 != 0)
   {

       if (*ptr % sizeof(size_t))
       {

           if (*(ptr + *(ptr) - 1) % sizeof(size_t))
           {
               *ptr += *(ptr + *(ptr) - 1) - 1;

               if (*ptr - 1 > maxSize)
               {
                   maxSize += *ptr - 1;
               }

           }

           else
           {
               if (*ptr - 1 > maxSize)
               {
                   maxSize = *ptr - 1;
               }
               s2 -= *ptr - 1;
               ptr += *ptr - 1 + *(ptr + *(ptr) - 1);
           }
       }

       else
       {
           ptr += *ptr -1 ;
       }
   }

   return maxSize;
}
