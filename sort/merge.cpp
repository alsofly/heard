#include <iostream>

void mergesort(int *num, int *tmp, int l, int r)
{
   if ( l >= r ) return;
   int mid = (l + r)/2;
   mergesort(num, tmp, l, mid);
   mergesort(num, tmp, mid+1, r);

   int p1(l), p2(mid+1), pt(l);
   while ( p1 <= mid && p2 <= r )
   {
      if ( num[p1] < num[p2] ) tmp[pt++] = num[p1++];
      else tmp[pt++] = num[p2++];
   }

   int p_left = p1 > mid ? p2 : p1;
   while ( pt <= r ) tmp[pt++] = num[p_left++];
   for ( int i = l; i <= r; ++i ) num[i] = tmp[i];
}

int main()
{
   int num[] = {12, 2, 33, -2, 23, 1, 1, -2, 11};
   int len = sizeof(num)/sizeof(int);
   int tmp[len];
   mergesort(num, tmp, 0, len - 1);
   for ( int i = 0; i < len; ++i )
   {
      std::cout << num[i] << std::endl;
   }
   return 0;
}
