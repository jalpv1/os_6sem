#include "alloc.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	size_t MALLOC_SIZE = (4 * 1024 * 1024);
	Allocator* my_block = new Allocator(MALLOC_SIZE);


	printf("Allocated a block on the host, pointer: %p, size %d\n", my_block, MALLOC_SIZE);

	BlockStorage::Node* t1 = my_block->mem_alloc(1000 * 1000)->blocks;
	BlockStorage::Node* t2 = my_block->mem_alloc(3 * 1000 * 1000)->blocks;
	BlockStorage::Node* t3 = my_block->mem_alloc(100)->blocks;
	BlockStorage::Node* t4 = my_block->mem_alloc(200)->blocks;
	BlockStorage::Node* t5 = my_block->mem_alloc(300)->blocks;
	BlockStorage::Node* t6 = my_block->mem_alloc(400)->blocks;
	BlockStorage::Node* t7 = my_block->mem_alloc(400 * 1000)->blocks;

	my_block->mem_free(t3);
	my_block->mem_free(t1);
	my_block->mem_free(t1);
	t7 = my_block->mem_alloc(400 * 1000)->blocks;

	my_block->mem_realloc(MALLOC_SIZE, 2 * MALLOC_SIZE);
	my_block->show_free_blocks();
	my_block->show_busy_blocks();
	getchar(); getchar();


}