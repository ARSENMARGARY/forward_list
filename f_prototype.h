#include <iostream>

namespace ATL
{
    template <typename T>
    struct Node
    {
        T m_data{};
        Node<T>* m_next{};
        Node(const T& data = T(), Node<T>* ptr = nullptr);
    };

    template <typename T>
    class F_List
    {
    public:
        F_List() = default;
        ~F_List();
        F_List(const T&);
        F_List(const F_List<T>&);
        F_List(F_List<T>&&);

    public:
        F_List<T>& operator= (const F_List<T>&);
        F_List<T>& operator= (F_List<T>&&);

    public:
        T& front()const;
	    T& back()const;
        void push_front(const T&);
        void pop_front();
	    bool empty()const;
	    size_t max_size()const;
	    void clear();
        void swap(F_List<T>&);
        void traverse(void(*p)(const T&));
        bool is_cycle(F_List<T>*);
        T& merge(F_List<T>&,F_List<T>&);

    private:
        Node<T>* head{};
        size_t size{};
    };
}
