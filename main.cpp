#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <random>
#include <algorithm>
#include <thread>
#include <mutex>
// void compute(std::vector <int> *array,int slicemax);
// int sum(std::vector <int> a);
// std::vector<int> *result=NULL;
// int slices=0;
// int main(void)
// {
//     std::vector <int> *array=new std::vector<int>;
//     int slicemax, types;
//     std::cin>>slicemax;
//     std::cin>>types;
//     int pizza;
//     while(1)
//     {
//         pizza=-1;
//         std::cin>>pizza;
//         if(pizza==-1)
//             break;
//         array->push_back(pizza);
//     }
//     std::cout<<"Max slices: "<<slicemax<<std::endl;
//     std::cout<<"Pizza types: "<<types<<std::endl;
//     std::cout<<std::endl<<"Slices of pizzas: "<<std::endl;
//     for(int i=0;i<array->size();i++)
//         std::cout<<array->at(i)<<" ";
//     std::cout<<std::endl<<std::endl;
//     compute(array,slicemax);
//     if(result!=NULL)
//     {
//         for(int i=0;i<result->size();i++)
//         {
//             std::cout<<result->at(i)<<" ";
//         }
//         std::cout<<" ("<<slices<<")"<<std::endl;
//     }
// }
// int sum(std::vector <int> a)
// {
//     int s=0;
//     for(int i=0;i<a.size();i++)
//     {
//         s+=a.at(i);
//     }
//     return s;
// }
// void compute(std::vector <int> *array,int slicemax)
// {
//     int s=sum(*array);
//     if(s>slices&&s<slicemax)
//     {
//         slices=s;
//         if(result!=NULL)
//             delete result;
//         result=new std::vector<int>(*array);
//     }
//     // std::vector<int> *backup=new std::vector<int>(*array);
//     for(int i=0;i<array->size();i++)
//     {
//         // std::cout<<i<<std::endl;
//         std::vector <int> *newvec=new std::vector<int>(*array);
//         newvec->erase(newvec->begin()+i);
//         compute(newvec,slicemax);
//         delete newvec;
//         //delete backup;
//         // backup=newvec;
//         // std::cout<<i<<std::endl;

//     }
// }
using namespace std; 
  
int max(int a, int b) { return (a > b)? a : b; } 
  
void knapSack(int W, int* wt, int* val, int n) 
{ 
   int i, w; 
   int** K=new int*[n+1];
   for(i=0;i<n+1;i++)
    K[i]=new int[W+1];
//    int K[n+1][W+1]; 
   for (i = 0; i <= n; i++) 
   { 
       char ch=getchar();
       for (w = 0; w <= W; w++) 
       { 
           if (i==0 || w==0) 
               K[i][w] = 0; 
           else if (wt[i-1] <= w) 
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]); 
           else
                 K[i][w] = K[i-1][w]; 
       } 
   } 
   int j=W;
   i=n;
   int counter=0;
    while(1)
   {
       if(K[i][j]==0)
            break;
       if(K[i][j]==K[i-1][j])
       {
           i--;
       }
       else
       {
           j-=wt[i-1];
           counter++;
       }
   }
   std::cout<<counter<<std::endl;
   i=n;
   j=W;
   while(1)
   {
       if(K[i][j]==0)
            break;
       if(K[i][j]==K[i-1][j])
       {
           i--;
       }
       else
       {
           j-=wt[i-1];
           std::cout<<wt[i-1]<<" ";
       }
   }
   std::cout<<std::endl;
//    std::cout<<"("<<K[n][W]<<")"<<std::endl;
} 

std::mutex m;
std::vector<int> bestarray;
int best=0;
void randomm(int slicemax,int* array,int types,bool flag)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,types);
    generator.seed( /* your seed for the RNG goes here */ );

    while(best<slicemax)
    {
        if(flag)
        {
            std::cout<<"\r"<<best;
            fflush(stdout);
        }
        int sum=0;
        std::vector<int> used;
        while(1)
        {
            int next=distribution(generator);
            if(std::find(used.begin(),used.end(),next)!=used.end())
                continue;
            if(sum+array[next]>slicemax)
            {
                if(sum>best)
                {
                    m.lock();
                    best=sum;
                    bestarray.clear();
                    for(int i=0;i<used.size();i++)
                    {
                        bestarray.push_back(array[used.at(i)]);
                    }
                    m.unlock();
                }
                break;
            }
            used.push_back(next);
            sum+=array[next];
        }

    }

    if(flag)
    {
        // std::cout<<"\rBest for now: "<<std::endl;
        // for(int i=0;i<bestarray.size();i++)
        // {
        //     std::cout<<bestarray.at(i)<<" ";
        // }
        // std::cout<<"("<<best<<")"<<std::endl;
        std::cout<<"\r              \r";
        std::cout<<bestarray.size()<<std::endl;
        for(int i=0;i<bestarray.size();i++)
        {
            std::cout<<bestarray.at(i)<<" ";
        }
        std::cout<<std::endl<<std::endl;
    }

}
int main() 
{ 
    int slicemax, types;
    std::cin>>slicemax;
    std::cin>>types;
    int pizza;
    int* array=new int[types];
    for(int i=0;i<types;i++)
    {
        std::cin>>pizza;
        array[i]=pizza;
    }
    // std::cout<<"Max slices: "<<slicemax<<std::endl;
    // std::cout<<"Pizza types: "<<types<<std::endl;
    // std::cout<<std::endl<<"Slices of pizzas: "<<std::endl;
    // for(int i=0;i<types;i++)
    //     std::cout<<array[i]<<" ";
    // std::cout<<std::endl<<std::endl;
    std::thread** tarray=new std::thread*[16];
    for(int i=0;i<8;i++)
    {
        tarray[i]=new std::thread(randomm,slicemax,array,types,(i==0?true:false));
    }
    for(int i=0;i<8;i++)
    {
        tarray[i]->join();
    }
    // knapSack(slicemax,array,array,types);
    return 0; 
} 
