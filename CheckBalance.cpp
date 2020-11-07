#include<iostream>
#include<fstream>

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
    if (!isFull(*st))
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
    if(!isEmpty(*st))
    {
        takePoppedItem = st->baseArray[st->top];
        st->top--;
        return true;
    }
    else
        return false;
}

template<class T>
bool pop(stack<T> *st)
{
    if(!isEmpty(*st))
    {
        st->top--;
        return true;
    }
    else
        return false;
}

template<class T>
T peekTop(stack<T> st)
{
    return st.baseArray[st.top];
}

template<class T>
bool resize(stack<T>* st, int capacity)
{
    T* temp;
    int tempCapacity = st->capacity;
    temp = new(nothrow)T[st->capacity];
    if (!temp)
    {
        for(int i=0;i<st->capacity;i++)
            temp[i] = st->baseArray[i];

        delete [] st->baseArray;

        createStack(*&st, capacity);

        for(int i=0;i<tempCapacity;i++)
        {
            st->baseArray[i] = temp[i];
            st->count++;
            st->top++;
        }

        return true;
    }

    return false;

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

// template<class T>
// void displayStack(stack<T> st)
// {
//     for(int i=0; i<=st.top;i++)
//         cout<< st.baseArray[i]<<" ";
// }

template<class T>
void displayStack(stack<T> st)
{
    for(int i=st.top; i>=0;i--)
        cout<< st.baseArray[i]<<" ";
}

int main()
{
    stack<char> st;
    createStack(&st, 300);
    ifstream fin {"sourceCode.txt", ios::in};

    string readLine {};
    char chOne, chTwo;

    bool foundAtNext;
    while (fin.peek() != EOF)
    {
        fin.get(chOne);
        if(chOne == '/')
        {
            fin.get(chTwo);
            if(chTwo == '/')
                getline(fin, readLine);
            else if(chTwo == '*')
            {
                do
                {
                    fin.get(chTwo);
                    foundAtNext = fin.peek() == '/';
                } while (chTwo != '*' || !foundAtNext);
                fin.get(chTwo);
            }
        }
        else if(chOne == '"')
        {
            do
            {
                fin.get(chTwo);
                // foundAtNext = fin.peek() == '/';
            } while (chTwo != '"');
            // fin.get(chTwo);
        }
        else if(chOne == '\'')
        {
            do
            {
                fin.get(chTwo);
            } while (chTwo != '\'');
            if(fin.peek() == '\'')
                fin.get(chTwo);
        }
        else if(chOne == '{' || chOne == '(' || chOne == '[' || chOne == '}' || chOne == ')' || chOne == ']')
        {
            push(&st, chOne);
        }
    }
    displayStack(st);
    cout<<endl;

    char symbol;
    int curlyOpen=0,parenthOpen=0,bracketOpen=0,curlyClose=0,parenthClose=0,bracketClose=0;
    cout<<endl<<st.top<<endl;
    while (st.top >= 0)
    {
        pop(&st, symbol);
        switch (symbol)
        {
        case '}':
            curlyClose++;
            break;
        case ')':
            parenthClose++;
            break;
        case ']':
            bracketClose++;
            break;
        case '{':
            curlyOpen++;
            break;
        case '(':
            parenthOpen++;
            break;
        case '[':
            bracketOpen++;
            break;
        case '"':
        {
            do
            {
                pop(&st, chTwo);
            } while (chTwo != '"');
        }
            break;
        case '\'':
        {
            do
            {
                pop(&st, chTwo);
            } while (chTwo != '\'');
        }
            break;
        default:
            break;
        }
    }

        if(curlyOpen == curlyClose)
        {
            cout<<"C_ok"<<endl;
            cout<<"Copen = "<<curlyOpen<<endl;
            cout<<"Cclose = "<<curlyClose<<endl;
        }
        else
        {
            cout<<"Copen = "<<curlyOpen<<endl;
            cout<<"Cclose = "<<curlyClose<<endl;
        }
        if(bracketOpen == bracketClose)
        {
            cout<<"B_ok"<<endl;
            cout<<"Bopen = "<<bracketOpen<<endl;
            cout<<"Bclose = "<<bracketClose<<endl;
        }
        else
        {
            cout<<"Bopen = "<<bracketOpen<<endl;
            cout<<"Bclose = "<<bracketClose<<endl;
        }

        if(parenthOpen == parenthClose)
        {
            cout<<"P_ok"<<endl;
            cout<<"Popen = "<<parenthOpen<<endl;
            cout<<"Pclose = "<<parenthClose<<endl;
        }
        else
        {
            cout<<"Popen = "<<parenthOpen<<endl;
            cout<<"Pclose = "<<parenthClose<<endl;
        }

    fin.close();
}
