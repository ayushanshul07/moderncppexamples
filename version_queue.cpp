#include <iostream>
#include <vector>
#include <cstddef>

template<typename T>
struct Node{
    T m_data;
    Node<T>* m_next;

    Node(const T& data, Node* next = nullptr) : m_data(data), m_next(next){}
};

template<typename T>
struct Version{
    Node<T>* m_head;
    Node<T>* m_tail;

    Version(Node<T>* head, Node<T>* tail): m_head(head), m_tail(tail){}
};

template<typename T>
class Queue{

    public:

    Queue(): m_head(nullptr), m_tail(nullptr){
        version_history.emplace_back(m_head, m_tail);
    }

    ~Queue(){
        
        if(version_history.size() <= 1) return;

        Node<T>* curr = version_history[1].m_head;

        while(curr){
            Node<T>* next = curr->m_next;
            delete(curr);
            curr = next;
        }

    }

    void enqueue(T data){
        if(!m_head){
            m_head = new Node<T>(data);
            m_tail = m_head;
        }
        else{
            Node<T>* tmp = new Node<T>(data);
            m_tail->m_next = tmp;
            m_tail = tmp;
        }
        version_history.emplace_back(m_head, m_tail);
    }

    T& dequeue(){
        Node<T>* tmp = m_head;
        m_head = m_head->m_next;
        version_history.emplace_back(m_head, m_tail);
        return tmp->m_data;
    }

    void print(size_t vno){

        std::cout << "Data for queue version " << vno << " is: \n";
        Node<T>* running = version_history[vno].m_head;
        while(running){
            std::cout << running->m_data << " ";
            if(running == version_history[vno].m_tail) break;
            running = running->m_next;
        }
        std::cout << "\n";
    }

    bool isEmpty() const noexcept {
        return m_head == nullptr;
    }

    private:
    Node<T>* m_head;
    Node<T>* m_tail;
    std::vector<Version<T>> version_history;
};

int main(){

    Queue<int> Q;

    Q.enqueue(1);
    Q.enqueue(2);
    Q.enqueue(3);
    Q.dequeue();
    Q.dequeue();
    Q.dequeue();

    Q.print(0);
    Q.print(1);
    Q.print(2);
    Q.print(3);
    Q.print(4);
    Q.print(5);
    Q.print(6);

    return 0;
}