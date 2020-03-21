#include <stdio.h>
#include <stdlib.h>

class BlockStorage {

public:
    BlockStorage()
    {
        head = NULL;
        tail = NULL;
    };

    struct Node {
        size_t size;
        Node* previous;
        Node* next;
        bool is_free;
        int links;
        void* data;
        Node() :
            size(0),
            previous(nullptr),
            next(nullptr),
            is_free(false),
            links(0),
            data(NULL) {}
    };


    Node* tail, * head;

    Node* newNode(Node* tmp, size_t size, void* data, Node* previous, Node* next, bool is_free, int links) {
        //		tmp = (Node*)addr;
        tmp->data = data;
        tmp->size = size;
        tmp->is_free = is_free;
        tmp->links = links;
        tmp->previous = previous;
        if (tmp->previous != nullptr) {
            tmp->previous->next = tmp;
        }
        tmp->next = next;
        if (tmp->next != nullptr) {
            tmp->next->previous = tmp;
        }
        return tmp;
    }

    void remove(Node* deleteNode) {
        if (deleteNode->previous == nullptr) {
            if (deleteNode->next == nullptr) {
                head = nullptr;
            }
            else {
                head = deleteNode->next;
                head->previous = nullptr;
            }
        }
        else {
            if (deleteNode->next == nullptr) {
                deleteNode->previous->next = nullptr;
            }
            else {
                deleteNode->previous->next = deleteNode->next;
                deleteNode->next->previous = deleteNode->previous;
            }
        }
    };
    void* find_last(void* mem) {
        size_t MALLOC_SIZE = (4 * 1024 * 1024);
        Node* tmp;
        tmp = head;
        void* min_addr = (char*)mem + MALLOC_SIZE;
        while (tmp != NULL)
        {
            if (tmp <= min_addr)
            {
                min_addr = tmp;
            }
            tmp = tmp->next;
        }
        return min_addr;
    }
private:
    BlockStorage(BlockStorage& doublyLinkedList);
};



