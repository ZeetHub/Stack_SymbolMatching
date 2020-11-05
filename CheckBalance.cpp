#include<iostream>

using namespace std;

const int NIL{-1};
template<class T>
struct stack
{
    T* baseArray;
    int top;
    int capacity;
    int count;
};

template<class T>
bool createStack(stack<T> *st, int capacity = 50)
{
    st->baseArray = new(nothrow)T[capacity];
    st->top = NIL;
    st->capacity = capacity;
    st->count = 0;
    return true;
}

template<class T>
bool isFull(stack<T> st)
{
    return st.top == st.capacity-1;
}

template<class T>
bool isEmpty(stack<T> st)
{
    return st.top == NIL;
}

template<class T>
bool push(stack<T> *st, T item)
{
    if (!isFull(st))
        {
            st->baseArray[++st->top] = item;
            st->count++;
            return true;
        }
    else
        return false;
}

template<class T>
bool pop(stack<T> *st, T& takePoppedItem = NIL)
{
    if(!isEmpty(st))
    {
        takePoppedItem = st->baseArray[st->top];
        st->top--;
        return true;
    }
    else
        return false;
}

template<class T>
T peekTop(stack<T> st)
{
    return st->baseArray[st->top];
}

template<class T>
bool resize(stack<T>* st, int capacity)
{
    T* temp;
    int tempCapacity = st->capacity;
    temp = new(nothrow)T[st->capacity];//may throw NULL, but rare.
    for(int i=0;i<st->capacity;i++)
        temp[i] = st->baseArray[i];
    
    delete [] st->baseArray;
    
    createStack(&st, capacity);

    for(int i=0;i<tempCapacity;i++)
    {
        st->baseArray[i] = temp[i];
        count++;
        st->top++;
    }
}

template<class T>
void clear(stack<T> *st)
{
    st->top = NIL;
}

template<class T>
void destroy(stack<T> *st)
{
    clear(st);
    delete [] st->baseArray;

}


int main()
{

}