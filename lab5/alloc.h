#include <vector>
#include <algorithm>

struct Chunk {
    unsigned char * memory;
    int size;
    bool is_free;
};

template <typename T>
class Allocator {
public: // for work with STL
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = T const&;
    using value_type = T;

    explicit Allocator(size_t chunkSize_ = 10000000, size_t chunkCount_ = 50) : chunkSize(chunkSize_), chunkCount(chunkCount_) {
        chunks = std::vector<Chunk>(chunkCount);
        for (int i = 0; i < chunkCount; i++) {
            chunks[i].size = chunkSize;
            chunks[i].is_free = true;
            chunks[i].memory = new uint8_t[chunkSize];
        }
    }

    template<typename other_T>
    Allocator(const Allocator<other_T> & other) : chunks(other.getChunks()){}

    ~Allocator() = default;

    T* allocate(size_t wantedSize) {
        for (auto & item : chunks) {
            if (item.size >= wantedSize * sizeof(T) and item.is_free) {
                item.is_free = false;
                return reinterpret_cast<T*>(item.memory);
            }
        }
        throw std::bad_alloc();
    }

    void deallocate(T * ptr, size_t n) noexcept {
        for (auto item : chunks) {
            if (reinterpret_cast<T*>(item.memory) == ptr){
                item.is_free = true;
                return;
            }
        }
        // out of free sheets
    }

    [[nodiscard]] std::vector<Chunk> const& getChunks() const { return chunks; }
private:
    std::vector<Chunk> chunks;
    int chunkCount;
    int chunkSize;
};