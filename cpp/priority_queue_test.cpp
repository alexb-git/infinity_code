/****************************************************************************
** Filename:    - pq_test.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - testing
                  thread dafe mutable waitable timeout priority queue
** Date:        - 27/2/2018
** Version:     - 1
*****************************************************************************/
#include <iostream> /* count, cin */

#include "priority_queue.hpp"    /* observer dp */
/****************************************************************************
    Helpful colors
*****************************************************************************/
#define YLL	 "\x1b[93m"
#define GRE	 "\x1b[92m"
#define RED	 "\x1b[91m"
#define WHI	 "\x1B[37m"
#define CYA	 "\x1B[36m"
#define BLU	 "\x1B[34m"
#define YEL	 "\x1b[33m"
#define RES	 "\x1b[0m"
#define BLD  "\x1B[1m"
#define UDL  "\x1b[4m"

/****************************************************************************
    Helpful defines and inline functions
*****************************************************************************/
inline void PrintHeader(const char *str)
{
    std::cout << BLU BLD "\n\t------------  This is a test for: "
              << str << " ------------\n" RES << std::endl;
}

inline void PrintInYellow(const char *str) { std::cout << YLL << str << RES;}
inline void PrintOK()  { std::cout << GRE "-OK" RES; }
inline void PrintERR() { std::cout << RED "-ERR" RES; }

#define Alighl(X)         ( std::left << setw(X) )
#define PrintOKorERR(X)   ( (X)?(PrintOK()):(PrintERR()) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )
/****************************************************************************/

template <typename T>
inline void PrintMes(const char* color, const char* message, T var)
{
    std::cout << color << message << " " << RES << var << std::endl;
}

/*==========================  Myint class  ==========================*/
class Myint
{
public:
    Myint() : m_id(m_runner) {
        ++m_runner;
        // PrintMes<int>(BLD BLU, "Myint Ctor", m_id);
    }

    Myint(const Myint &other) {
        m_id = other.m_id;
        // PrintMes<int>(BLD CYA, "Myint CCtor", m_id);
    }

    ~Myint () {
        // PrintMes<int>(BLD RED, "Myint Dtor", m_id);
    }

    Myint& operator=(const Myint &other)
    {
        m_id = other.m_id;
        // PrintMes<int>(BLD CYA, "Myint op=", m_id);
        return *this;
    }

    bool operator< (const Myint &other) const
    {
        return (m_id < other.m_id);
    }

    operator int() const
    {
        return m_id;
    }

    void swap(Myint &other)
    {
        PrintMes<int>(BLD RED, "Myint swap", m_id);

        int temp = m_id;
            m_id = other.m_id;
      other.m_id = temp;
    }

private:
    int m_id;
    static int m_runner;

}; /* end of Myint */

/* template specialization  */
namespace std
{
template<>
void swap( Myint &a ,
           Myint &b )
{
    a.swap(b);
}

}

int Myint::m_runner = 0;

template <typename T>
void RandomizeArr(T *arr, size_t N_MEM)
{
    srand(time(NULL));

    for (size_t i = 0; i < N_MEM; ++i)
    {
        // make std::swap available in this function
        using std::swap;

        // call the best swap for objects of type T
        swap(arr[i], arr[rand() % N_MEM]);
    }
}



/*=====================  Structs for this program  =====================*/
// struct aux_t
// {
//     size_t location;
// };

/*==========================  global Variables  ==========================*/
const size_t N_MEM     = 8;
const size_t N_THREADS = N_MEM;

ilrd::PQueue<Myint> pqueue;

Myint arr[N_MEM];
Myint elem;


/*==========================  thread functions  ==========================*/
void* LoadToQueue(void *buffer)
{
    size_t index = reinterpret_cast<size_t>(buffer);

    // std::cout << YEL "i = " << i << RES << std::endl;
    std::cout << arr[index] << "\n";
    pqueue.Enqueue(arr[index]);

    return NULL;
}


void* UnLoadFromQueue(void *buffer)
{
    // std::cout << "bool Dequeue: " << pqueue.Dequeue(&elem);
    pqueue.Dequeue(&elem);
    std::cout << "elem = " << elem << "\n";

    return NULL;
}


/*==========================  THE MAIN  ==========================*/
int main(int argc, char const *argv[])
{
    // aux_t info;
    RandomizeArr(arr, N_MEM);

    PrintInYellow("\n-> Array contant\n");
    for (size_t i = 0 ; i < SizeArr(arr) ; ++i )
    {
        std::cout << arr[i] << " ";
    }

    PrintInYellow("\n-> About to Enqueue\n");
    pthread_t enqueue_s[N_THREADS];

    for (size_t i = 0 ; i < N_THREADS ; ++i )
    {
        pthread_create(&enqueue_s[i], NULL, LoadToQueue, (void*)i);
    }

    for (size_t i = 0 ; i < N_THREADS ; ++i )
    {
        pthread_join(enqueue_s[i], NULL);
    }


    PrintInYellow("\n-> About to Dequeue\n");
    for (size_t i = 0 ; i < N_THREADS ; ++i )
    {
        pthread_create(&enqueue_s[i], NULL, UnLoadFromQueue, NULL);
    }

    for (size_t i = 0 ; i < N_THREADS ; ++i )
    {
        pthread_join(enqueue_s[i], NULL);
    }



    PrintInYellow("\n->Just before hitting return\n");
    return 0;
}
