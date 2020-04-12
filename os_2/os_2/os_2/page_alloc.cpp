
#include <cstdint>
#include <iostream>


class BudLocator {
    static const uint8_t maxlevel = 10;
    static const uint8_t minlevel = 4;

    static const int size = 1 << maxlevel;
    uintptr_t memory_base;

    typedef void* ptr_t;
    typedef struct Container {
        uint8_t memory[size];
        ptr_t free_ptrs[maxlevel + 2];
    };

    typedef struct Info {
        uint8_t level;

        Info(uint8_t level) : level(level) {}
    };

private:
    Container* container = nullptr;

    ptr_t getbuddy(ptr_t block, int i) {
        uintptr_t offset = (uintptr_t)block - memory_base;
        uintptr_t buddy = offset ^ blocksize(i);
        return (ptr_t)(buddy + memory_base);
    }

    uintptr_t blocksize(int i) {
        return 1 << (i);
    }

    void setinfo(ptr_t& block, Info info) {
        *(((Info*)block) - sizeof(Info)) = info;
    }

    Info getinfo(ptr_t& block) {
        return *(((Info*)block) - sizeof(Info));
    }

    ptr_t hideinfo(Info* block) {
        return (void*)(block + 1);
    }

    Info* showinfo(ptr_t block) {
        return ((Info*)block) - 1;
    }

    int free_space() {
        int bytes = 0;
        for (int i = 0; i <= maxlevel; i++) {
            int count = 0;
            ptr_t* p = &(container->free_ptrs[i]);
            while (*p != NULL) {
                count++;
                p = (ptr_t*)*p;
            }
            bytes += count * blocksize(i);
        }
        return bytes;
    }

    void show_buddies(int i) {
        ptr_t* link = &container->free_ptrs[i];
        int buddies = 0;
        // std::cout << "Level " << i << std::endl;
        while (*link != NULL) {
            buddies++;
            link = (ptr_t*)*link;
        }

        for (int j = 0; j < buddies; ++j) {
            for (int k = 0; k < i; ++k) {
                // std::cout << "-";
            }
            //std::cout << " ";
        }
       // std::cout << std::endl;
    }

    ptr_t* tofreelist(ptr_t buddy, int level) {
        ptr_t* list = &(container->free_ptrs[level]);

        while (true) {
            if (*list == buddy)
                return list;
            if (*list == nullptr)
                return nullptr;
            list = (ptr_t*)*list;
        }
    }

    ptr_t getleftbuddy(ptr_t b1, ptr_t b2) {
        if (b1 < b2)
            return b1;
        return b2;
    }

    int findfreelevel(int min) {
        for (int i = min; i <= maxlevel; i++) {
            if (container->free_ptrs[i])
                return i;
        }
        return NULL;
    }

public:
    BudLocator() {
        container = new Container();
        container->free_ptrs[maxlevel] = container->memory;
        memory_base = (uintptr_t)container->memory;
    }

    ~BudLocator() {
        free(container);
    }

    ptr_t my_alloc(int bytes) {
        std::cout << "Allocate request " << bytes << " bytes" << std::endl;

        int i = 0;
        while (blocksize(i) < bytes + sizeof(Info))
            i++;


        if (i < minlevel) {
            i = minlevel;
        }
        int order = i;
        std::cout << "Minimal fit size level " << i << " (" << blocksize(i) << " bytes)" << std::endl;

        int level = findfreelevel(i);
        // std::cout << "Free level " << level << std::endl;

        ptr_t block = container->free_ptrs[level];
        container->free_ptrs[level] = nullptr;

        std::cout << "Block: " << block << std::endl;
        while (level-- > order) {
            ptr_t buddy = getbuddy(block, level);
            container->free_ptrs[level] = buddy;
            // std::cout << "Level " << level << " buddy:" << buddy << std::endl;
        }

        auto info = Info(order);
        setinfo(block, info);
        return block;
    }

    void free(ptr_t block) {
        std::cout << "Delete request for " << block << std::endl;

        Info info = getinfo(block);

        for (int i = info.level; ; i++) {
            ptr_t buddy = getbuddy(block, i);

            ptr_t* list = tofreelist(buddy, i);

            if (list == nullptr) {
                std::cout << "Container for " << block << " is occupied" << std::endl;
                *((ptr_t*)block) = container->free_ptrs[i];
                container->free_ptrs[i] = block;
                return;
            }
            else {
                std::cout << "Container found " << block << " and " << buddy << " merged" << std::endl;
                block = getleftbuddy(block, buddy);
                *list = *((ptr_t*)*list);
            }
        }
    }

    void to_string() {
        std::cout << "Space : " << free_space() << "/" << size << std::endl;
        for (int i = 0; i <= maxlevel; i++) {
            show_buddies(i);
        }
    }
};