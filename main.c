#include <stdio.h>
#include <stdlib.h>
#include "memoryAllocator.h"

void TestMemoryAllocatorInit()
{
   void * allocaition = malloc(40);
   MemoryAllocator * memory = MemoryAllocator_init(allocaition, 40);
   if (memory->m_size != 40)
   {
       printf("%s", "Test MemoryAllocatorInit Fail\n");
   }
   else
       printf("%s", "Test MemoryAllocatorInit succeed\n");

}

void TestMemoryAllocatorAllocate()
{
   size_t s = 40;
   void * allocaition = malloc(s);
   MemoryAllocator * memory = MemoryAllocator_init(allocaition, 40);
   MemoryAllocator_allocate(memory, 4);
   if (memory->m_size == 32)
   {
       printf("%s", "Test MemoryAllocatorAllocate succeed\n");
   }
   else
   {
       printf("%s", "Test MemoryAllocatorAllocate faill\n");
   }
}

void TestMemoryAllocatorFree()
{
   size_t s = 40;
   void * allocaition = malloc(s);
   MemoryAllocator * memory = MemoryAllocator_init(allocaition, 40);
   void * ptr = MemoryAllocator_allocate(memory, 4);
   size_t size = MemoryAllocator_free(memory, ptr);
   if (size == 40)
   {
       printf("%s", "Test MemoryAllocatorFree succeed\n");
   }
   else
   {
       printf("%s", "Test MemoryAllocatorFree faill\n");
   }


}

void TestMemoryAllocatorOptimize()
{

   size_t size = 64;
   void * ptr;
   int * intArr;
   char *  charArr;
   MemoryAllocator * mem;

   ptr = malloc(size);
   mem = MemoryAllocator_init(ptr, size);

   intArr = (int *)MemoryAllocator_allocate(mem,1);
   charArr = (char *)MemoryAllocator_allocate(mem,1);
   (long *)MemoryAllocator_allocate(mem,1);
   MemoryAllocator_free(mem, intArr);
   MemoryAllocator_free(mem, charArr);
   if (!(MemoryAllocator_optimize(mem) == 40))
   {
       printf("Test MemoryAllocatorOptimize failed\n");

   }
   else
   {
       printf("Test MemoryAllocatorOptimize succeed\n");
   }
}

int main()
{
   TestMemoryAllocatorInit();
   TestMemoryAllocatorAllocate();
   TestMemoryAllocatorFree();
   TestMemoryAllocatorOptimize();

}
