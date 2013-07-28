#include <iostream>

void swap(int &a, int &b)
{
   if ( a != b )
   {
      a = a^b;
      b = a^b;
      a = a^b;
   }
}

int rearrange(int *num, int l, int r)
{
   // pick the first as the pivot
   int pivot_num = num[r];
   int p(l);
   for ( int i = l; i <= r-1; ++i )
   {
      if ( num[i] <= pivot_num ) swap(num[i], num[p++]);
   }
   swap(num[p], num[r]);
   return p;
}

void quicksort(int *num, int l, int r)
{
   if ( l >= r ) return;
   int pivot = rearrange(num, l, r);
   quicksort(num, l, pivot - 1);
   quicksort(num, pivot + 1, r);
}

int main()
{
   int num[] = {12, 2, 33, -2, 23, 1, 1, -2, 11};
   int len = sizeof(num)/sizeof(int);
   quicksort(num, 0, len - 1);
   for ( int i = 0; i < len; ++i )
   {
      std::cout << num[i] << std::endl;
   }
   return 0;
}
