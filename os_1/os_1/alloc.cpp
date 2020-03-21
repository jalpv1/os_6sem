#include "alloc.h"
#include <stdio.h>
#include <utility> 
#include <string.h>
Ptr* Allocator::mem_alloc(size_t size) {
	printf("Allocating a block of size :%d\n", size);
	if (size <= Allocator::maxblocksize) {
		BlockStorage::Node* tmp = l.head;
		Ptr* cur_d = (Ptr*)(mem);
		cur_d->blocks = nullptr;
		while (tmp != NULL) {
			if (tmp->is_free) {
				if (tmp->size >= size) {

					void* addr = l.find_last(mem);
					BlockStorage::Node* blk = (BlockStorage::Node*)((char*)addr - sizeof(BlockStorage::Node));
					cur_d = Allocator::find(size);
					tmp->size -= size;
					blk = l.newNode(blk, size, (char*)cur_d->blocks->data + size, tmp->previous, tmp, false, 1);
					if (blk->previous == nullptr) {
						l.head = blk;
					}
					if (blk->next == nullptr) {
						l.tail = blk;
					}
					Ptr ret = Ptr::Ptr(blk);
					return &ret;
				}
			}
			tmp = tmp->next;
		}
		printf("\nERROR! Not enough space\n\n");
		return cur_d;
	}
}

void Allocator::mem_free(BlockStorage::Node* blk) {
	printf("Freeing a block...\n");
	if (!(blk->is_free)) {
		if (blk->previous != NULL && blk->previous->is_free)
		{
			if (blk->next != NULL && blk->next->is_free) {
				blk->previous->size += (blk->size + blk->next->size);
				l.remove(blk->next);
				l.remove(blk);
				return;
			}
			blk->previous->size += blk->size;
			l.remove(blk);

			return;
		}
		if (blk->next != NULL && blk->next->is_free)
		{
			blk->next->size += blk->size;
			l.remove(blk);
			return;
		}
		blk->is_free = true;
		return;
	}
	printf("\nERROR! Block is already free\n\n");
}

void Allocator::mem_realloc(size_t size, size_t new_size) {
	printf("Reallocating a block of size :%d\n", new_size);
	void* tmp = mem;

	Allocator::Allocator(new_size);
	memmove(mem, tmp, sizeof(tmp));
	void* addr = l.find_last(mem);
	BlockStorage::Node* block = (BlockStorage::Node*)((char*)addr - sizeof(BlockStorage::Node));
	block = l.newNode(block, new_size - size, mem, l.tail, nullptr, true, 1);
	l.tail = block;
	return;
}

void Allocator::show_busy_blocks() {
	printf("\n Busy blocks:\n");
	BlockStorage::Node* tmp = l.head;
	while (tmp != NULL) {
		if (!tmp->is_free && tmp->links != 0) {
			printf("Address:%p, Size:%d\n", tmp->data, tmp->size);
		}
		tmp = tmp->next;
	}
}

void Allocator::show_free_blocks() {
	printf("\n Free blocks:\n");
	BlockStorage::Node* tmp = l.head;
	while (tmp != NULL) {
		if (tmp->is_free && tmp->links != 0) {
			printf("Address:%p, Size:%d\n", tmp->data, tmp->size);
		}
		tmp = tmp->next;
	}
}
Ptr* Allocator::find(size_t size)
{
	size_t minsize = maxblocksize;
	BlockStorage::Node* tmp = l.head;
	BlockStorage::Node* fit_block = NULL;
	while (tmp != NULL)
	{
		if (tmp->is_free)
			if ((minsize >= tmp->size) && (size <= tmp->size)) {
				minsize = tmp->size;
				fit_block = tmp;
			}
		tmp = tmp->next;
	}
	Ptr ret = Ptr::Ptr(fit_block);
	return &ret;
}