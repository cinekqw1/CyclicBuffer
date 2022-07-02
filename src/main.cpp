#include <iostream>
#include <iterator>

template<typename T, size_t SIZE>
class CyclicBuffer
{
public:
    using Reference = T&;
    
    explicit CyclicBuffer()
    {
        m_begin = (T*) malloc(SIZE * sizeof(T));
        m_read = m_begin;
        m_write = m_begin;
    }
    
    Reference push(T const& obj)
    {
        return push_impl(obj);
    }   
    
    Reference push(T&& obj)
    {
        return push_impl(std::move(obj));
    }
    
    
    Reference push(std::initializer_list<T> args)
    {
        for (auto i = std::begin(args); i < std::end(args)-1; ++i)
        {
            push_impl(*i);
        }
    
        return push_impl(*(std::end(args)-1));
    }
    
    [[nodiscard]] Reference get()
    {
        if( m_read == (m_begin+SIZE))
        {
            m_read = m_begin;
        }
        return *(m_read)++;
    }
    
    void dump(std::string msg)
    {
        std::cout << msg << "-> ";
        for (auto i = m_begin; i < (m_begin +SIZE) ; ++i)
        {
            std::cout <<  *i << " ";
        }
        
        std::cout << "\n";
    }
    
    ~CyclicBuffer()
    {
        free(m_begin);
    }
    
private:
    T* m_begin;
    T* m_read;
    T* m_write;
    
    template<typename... Args>
    Reference push_impl(Args&&... args)
    {
        if(m_write == (m_begin+SIZE))
        {
            m_write = m_begin;
        }

        return *new (m_write++) T(std::forward<Args>(args)...);
    }
};

int main() {
  std::cout << "Hello World!\n";

  CyclicBuffer<int, 10> cb;
  cb.dump("1");
    
  cb.push({1,2,3,4,5,6,7});
  cb.dump("2");
  cb.push({11,12,13,14,15,16,17});
  cb.push(1);
  cb.dump("3");

  std::cout << cb.get() << "\n";
  cb.dump("4");
  std::cout << cb.get() << "\n";
  cb.dump("5");
  
}