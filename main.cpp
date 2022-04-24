#include <iostream>
#include <thread>

void threadFun(int& x, int& y, int& rec)
{
    x = 1;
    //__asm("DMB ISH"); // Uncomment to fix it!
    rec = y;
}

int main(int argc, const char * argv[])
{
    uint64_t iter = 0;

    int r1 = 0;
    int r2 = 0;

    while(1)
    {
        int a = 0;
        int b = 0;

        std::thread T1(threadFun, std::ref(a), std::ref(b), std::ref(r1));
        std::thread T2(threadFun, std::ref(b), std::ref(a), std::ref(r2));

        T1.join();
        T2.join();

        if ((r1 != 0) || (r2 != 0))
        {
            printf("Iteration %lld: R1 = %d ; R2 = %d\n", iter, r1, r2);
        }
        else // both R1 and R2 are zero
        {
            printf("ERROR!! Iteration %lld: R1 = %d ; R2 = %d\n", iter, r1, r2);
            return 1;
        }
        iter++;
    }

    return 0;
}
