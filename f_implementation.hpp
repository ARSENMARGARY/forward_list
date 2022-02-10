#include "f_prototype.h"

template <typename T>
ATL::Node<T>::Node(const T& data, Node<T>* ptr)
{
	this->data = data;
	this->next = ptr;
}

template<typename T>
ATL::F_List<T>::F_List()
{
    this->head = nullptr;
}

template<typename T>
ATL::F_List<T>::~F_List()
{
    if(head != nullptr)
    {
        clear();
    }
}

template<typename T>
ATL::F_List<T>::F_List(const T& val)
{
    this->head = new Node(val);
}

template<typename T>
ATL::F_List<T>::F_List(const F_List<T>& ls)
{
    if(ls.head == nullptr){return;}
    Node<T>* tmp = ls.head;
    this->head = new Node(tmp->m_data);
    Node<T>* m_tmp = this->head->m_next;
    tmp = tmp->m_next;

    while(tmp)
    {
        m_tmp->m_next = new Node (tmp->m_data);
        m_tmp = m_tmp->m_next;
        tmp = tmp->m_next;
    }
}

template<typename T>
ATL::F_List<T>::F_List(F_List<T>&& ls)
{
    this->head = ls.head;
    ls.head = nullptr;
}

template<typename T>
ATL::F_List<T>& ATL::F_List<T>::operator=(const F_List<T>& ls)
{
      if(ls.head == nullptr){return *this;}
      F_List<T> tmp(ls);
      this->swap(tmp);
      return *this;
}

template<typename T>
ATL::F_List<T>& ATL::F_List<T>::operator=(F_List<T>&& ls)
{
      clear();
      head = ls.head;
      ls.head = nullptr;
}

template<typename T>
T& ATL::F_List<T>::front()const
{
    return head->m_data;
}

template<typename T>
T& ATL::F_List<T>::back()const
{
    Node<T>* tmp = head;
    while(tmp->m_next)
    {
        tmp = tmp -> m_next;
    }
    return tmp -> m_data;
}

template<typename T>
bool ATL::F_List<T>::empty() const
{
    return head == nullptr;
}

template<typename T>
size_t ATL::F_List<T>::max_size() const
{
    Node<T>* tmp = head ;
    size_t size = 0 ;
    while(tmp != nullptr)
    {
        tmp = tmp -> m_next ;
        size++;
    }
    return size;
}

template<typename T>
void ATL::F_List<T>::push_front(const T& elem)
{
    Node<T>* tmp = head;
    head = new Node(elem,head);
}

template<typename T>
void ATL::F_List<T>::pop_front()
{
    if(head == nullptr){return;}
    Node<T>* tmp = head;
    head = head -> m_next;
    delete tmp;
}

template<typename T>
void ATL::F_List<T>::clear()
{
    while(head)
    {
        this->pop_front();
    }
    return;
}

template<typename T>
void ATL::F_List<T>::swap(F_List<T>& other)
{
    if(this->head == other.head)
    {
        return this->head;
    }
    std::swap(this->head,other->head);
}

template<typename T>
void ATL::F_List<T>::traverse(void(*visit)(const T&))
{
	Node<T>* current = head;
	while (current != nullptr)
	{
		visit(current->data);
		current = current->next;
	}
}

template<typename T>
bool ATL::F_List<T>::is_cycle(F_List<T>* oth)
{
    if(oth->head == nullptr || oth->head->next == nullptr)
    {
        return false;
    } 
    else 
    {
        F_List<T>*slow = oth->head, *fast = oth->head->next;   
        while (slow != fast)
        {
            if(fast == nullptr || fast->next == nullptr)
            {
                return false;
            }
            else
            {
                slow = slow->next;
                fast = fast->next->next;
            }
        }
        return true;
    }
}

template<typename T>
T& ATL::F_List<T>::merge(F_List<T>& first,F_List<T>& second)
{
    if(!first.head){return second}
    if(!second.head){return first}

    F_List<T>* tmp = new Node();
    while (first && second)
    {
        if(first.head->m_data <= second.head->m_data)
        {
            tmp.head->m_next = first.head;
            first.head = first.head->m_next;
        }
        else
        {
            tmp.head = second.head;
            second->head = second.head->m_next;
        }
        tmp->head = tmp->head->m_next; 
    }
    tmp->head = first.head ? first.head : second.head;

    return tmp->head;
}




