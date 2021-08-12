/*
**  IMDb_sorting_lib.c
**  IMDbデータ用ソートライブラリ
**  
*/

#include "IMDb_IO.h"



/* 関数名: swap
 * 機能：配列Aの要素A[a]とA[b]の中身を入れ替える
 * 引数: A:データidの配列, a,b: 入れ替える要素が格納されているindex                                            */
void swap(int *A, int a, int b)
{
  int temp=A[a];
  A[a]=A[b];
  A[b]=temp;
}

/* 関数名: bubblesort
 * 機能：配列Aに格納されたn個のデータidをset_val_functionで設定したデータ属性値でバブルソートする
 * 引数: A:データidの配列, n:配列に格納されている数                                            */
void bubblesort(int *A, int n) {
  /* begin p 課題 1                                                                              */
  for (int i = 1; i < n - 1; i++) {
    for (int j = n - 1; j >= i; j--) {
      if (!ORelation( val(A[j - 1]), val(A[j]))) {
        swap(A, j - 1, j);
      }
    }
  }
  /* end   p 課題 1                                                                              */
}

/* 関数名: partition
 * 機能：配列Aに格納されたn個のデータidを、set_val_functionで設定したデータ属性値がa以下のものがA[0]〜A[*right]，
 *      a以上のものがA[*left]〜A[n-1]となるように並べ替える。
 * 引数: A:データidの配列, n:配列に格納されている数, a:軸要素(実数), left, right:整数へのポインタ(出力用)   */
void partition(int *A, int n, double a, int *left, int *right)
{
  /* begin p 課題 2                                                                              */
  int l = 0;
  int r = n - 1;

  while (l <= r) {
    while (!ORelation(a, val(A[l]))) {
      l++;
    }
    while (!ORelation(val(A[r]), a)) {
      r--;
    }
    if (l <= r) {
      swap(A, l, r);
      l++;
      r--;
    }
  }
  *left = l;
  *right = r;
  /* end   p 課題 2                                                                              */
}

/* 関数名: quicksort
 * 機能：配列Aに格納されたn個のデータidをset_val_functionで設定したデータ属性値でクイックソートする
 * 引数: A:データidの配列, n:配列に格納されている数                                          */
void quicksort(int *A, int n) {
  if(n>1) {
    double a=val(A[0]);
    int left,right;
    partition(A,n,a,&left,&right);
    quicksort(A,right+1);
    quicksort(&A[left],n-left);
  }
}

/* 関数名: quicksort_topN
 * 機能: 配列Aに格納されたn個のデータidに対し、set_val_functionで設定したデータ属性値でN番目までの値を
 *       partition関数を用いてA[0]〜A[N-1]にセットする
 * 引数: A:データidの配列, n:配列に格納されている数, N:1〜numの自然数                         */
void quicksort_topN(int *A, int n, int N) {
  /* begin p 課題 3                                                                              */
  if (n > 1) {
    double a = val(A[0]);
    int left, right;
    partition(A, n, a, &left, &right);
    // Step4
    int k = right + 1;
    if (k > 1) {
      quicksort_topN(A, k, N);
    }
    if (N - 1 >= k) {
      quicksort_topN(&A[left], n - left, N - k);
    }
  }
  /* end   p 課題 3                                                                              */
}

/* 関数名: quicksort_pth
 * 機能: 配列Aに格納されたn個のデータidに対し、set_val_functionで設定したデータ属性値でp番目のidをA[p-1]に格納する
 * 引数: A:データidの配列, n:配列に格納されている数, p:1〜numの自然数                       */
void quicksort_pth(int *A, int n, int p) {
  /* begin p 課題 4                                                                              */
  if (n > 1) {
    double a = val(A[0]);
    int left, right;
    partition(A, n, a, &left, &right);
    int k = right + 1;
    if (p <= k) {
      quicksort_pth(A, right + 1, p);
    } else {
      quicksort_pth(&A[left], n - left, p - k);
    }
  }
  /* end   p 課題 4                                                                              */
}

/* 関数名: partition_into_3
 * 機能：配列Aに格納されたn個のデータidを、set_val_functionで設定したデータ属性値がa未満のものがA[0]〜A[*right]，
 *      aのものがA[*right+1]〜A[*left-1], aより大きいものがA[*left]〜A[n-1]となるように並べ替える。
 * 引数: A:データidの配列, n:配列に格納されている数, a:軸要素(実数), left, right:整数へのポインタ(出力用)   */
void partition_into_3(int *A, int n, double a, int *left,int *right)
{
  /* begin p 課題 5                                                                              */
  // Step1
  int l1 = 0, l2 = 0;
  int r1 = n - 1, r2 = n - 1;

  // Step2
  // 軸要素と同じ属性値のデータのidを格納しておく配列
  int A_save[n+1];
  int saved_num = 0;
  while (l1 <= r1) {
    // (1)
    while (!ORelation(a, val(A[l1]))) {
      A[l2] = A[l1];
      l1++;
      l2++;
    }
    // (2)
    while (!ORelation(val(A[r1]), a)) {
      A[r2] = A[r1];
      r1--;
      r2--;
    }
    // (3)
    if (l1 <= r1) {
      // [ⅰ]
      swap(A, l1, r1);
      // [ⅱ]
      if (val(A[l1]) != a) {
        A[l2] = A[l1];
        l2++;
      } else {
        A_save[saved_num] = A[l1];
        saved_num++;
      }
      // [ⅲ]
      if (val(A[r1]) != a) {
        A[r2] = A[r1];
        r2--;
      } else {
        A_save[saved_num] = A[r1];
        saved_num++;
      }
      // [ⅳ]
      l1++;
      r1--;
    }
  }

  // Step3
  int j = 0;
  for (int i = l2; i <= r2; i++) {
    A[i] = A_save[j];
    j++;
  }

  // Step4
  *right = l2 - 1;
  *left = r2 + 1;
  
  /* end   p 課題 5                                                                              */
}

/* 関数名: select_pth
 * 機能：配列Aに格納されたn個のデータidに対し、set_val_functionで設定したデータ属性値でp番目のidを，最悪ケースでもO(n)時間で計算しA[p-1]に格納する
 * 引数: A:データidの配列, n:配列に格納されている数, p:1〜nの自然数                         */
void select_pth(int *A, int n, int p)
{
  /* begin p 課題 6                                                                              */
  // Step1
  if (n < 35) {
    quicksort(A, n);
    return;
  }

  // Step2
  int m = n / 5;
  
  // Step3
  for (int i = 0; i < m; i++) {
    // (1)
    quicksort(&A[5*i], 5);
    // (2)
    swap(A, i, 5*i + 2);
  }

  // Step4
  select_pth(A, m, (m + 1) / 2);
  
  // Step5
  double a = val(A[((m + 1) / 2) - 1]);

  // Step6
  int l, r;
  partition_into_3(A, n, a, &l, &r);

  // Step7
  if (p <= r + 1) {
    select_pth(A, r + 1, p);
  }
  if (p >= l + 1) {
    select_pth(&A[l], n - l, p - l);
  }
  /* end   p 課題 6                                                                              */
}

/* 関数名: quicksort_wc
 * 機能：配列Aに格納されたn個のデータidをset_val_functionで設定したデータ属性値で，最悪時間計算量O(n log n)でクイックソートする
 * 引数: A:データidの配列, n:配列に格納されている数                                          */
void quicksort_wc(int *A, int n) {
  if(n>1) {
    select_pth(A,n,(n+1)/2);
    int right=(n+1)/2-2;
    int left=(n+1)/2;
    quicksort_wc(A,right+1);
    quicksort_wc(&A[left],n-left);
  }
}

/* 関数名: quicksort_wc_topN
 * 機能: 配列Aに格納されたn個のデータidに対し、set_val_functionで設定したデータ属性値でN番目までの値を
 *       最悪計算時間O(n log N)でA[0]〜A[N-1]にセットする
 * 引数: A:データidの配列, n:配列に格納されている数, N:1〜numの自然数                         */
void quicksort_wc_topN(int *A, int n, int N) {
  if(n>1) {
    select_pth(A,n,(n+1)/2);
    int right=(n+1)/2-2;
    int left=(n+1)/2;
    quicksort_wc_topN(A,right+1,N);
    if(N>=left+1) quicksort_wc_topN(&A[left],n-left,N-left);
  }
}


