/*
**  IMDb_heap_lib.c
**  IMDbデータ用ヒープライブラリ
**  
*/

#include <stdio.h>
#include <stdlib.h>
#include "IMDb_IO.h"

/* 関数名: heap_insert
 * 機能：サイズがnのヒープ配列Aにデータid xを追加する．
 * 引数: A: データidの配列, n:現在のヒープのサイズ, id: データのid                                                                      */
void heap_insert(int *A, int n, int x)
{
  /* begin p 課題 7 (1)                                                                           */
  int i, j;
  // Step1
  i = n;

  // Step2
  while (i > 0) {
    j = (i - 1) / 2;
    if (ORelation(val(A[j]), val(x))) {
      break;
    }
    A[i] = A[j];
    i = j;
  }

  // Step3
  A[i] = x;
  /* end   p 課題 7 (1)                                                                          */
}

/* 関数名: heap_heapify
 * 機能：サイズがnのヒープ配列Aの位置iを開けて位置i以降の適切な位置にxを格納する
 * 引数: A: データidの配列, n:現在のヒープのサイズ, i:0〜n-1の整数, x: 格納するデータid                                                   */
void heap_heapify(int *A, int n, int i, int x)
{
  /* begin p 課題 7 (2)                                                                           */
  // Step1
  int j = 2*i + 1;

  // Step2
  while (j < n) {
    // (1)
    if (j + 1 < n) {
      if (!ORelation(val(A[j]), val(A[j + 1]))) {
        j++;
      }
    }
    // (2)
    if (ORelation(val(x), val(A[j]))) {
      break;
    }
    // (3)
    A[i] = A[j];
    i = j;
    j = 2*i + 1;
  }

  // Step3
  A[i] = x;
  /* end   p 課題 7 (2)                                                                          */
}

/* 関数名: heap_deletemin
 * 機能：サイズがnのヒープ配列Aの先頭のデータid A[0]を削除し，関数値として返す．
 * 引数: A: データidの配列, n:現在のヒープのサイズ                                                                                     */
int heap_deletemin(int *A, int n)
{
  /* begin p 課題 7 (3)                                                                           */
  // Step1
  int y = A[0];

  // Step2
  if (n > 1) {
    heap_heapify(A, n - 1, 0, A[n - 1]);
  }

  // Step3
  return y;
  /* end   p 課題 7 (3)                                                                          */
}

/* 関数名: heap_sort
 * 機能：配列Aに格納されたn個のデータidをset_val_functionで設定したデータ属性値でヒープソートする
 * 引数: A:データidの配列, n:配列に格納されている数                                          */
void heap_sort(int *A,int n)
{
  /* begin p 課題 8                                                                               */
  // Step1

  for (int i = (n - 2) / 2; i >= 0; i--) {
    heap_heapify(A, n, i, A[i]);
  }

  // Step2
  for (int i = n; i > 1; i--) {
    A[i - 1] = heap_deletemin(A, i);
  }
  
  /* end   p 課題 8                                                                              */
}

/* 関数名: heap_topN
 * 機能：配列Aに格納されたn個のデータidに対し、set_val_functionで設定したデータ属性値でN番目までの値をA[0]〜A[N-1]にセットする
 * 引数: A:データidの配列, n:配列に格納されている数, N:1〜numの自然数                         */
void heap_topN(int *A, int n, int N)
{
  /* begin p 課題 8                                                                               */
  // Step1
  for (int i = (N - 2) / 2; i >= 0; i--) {
    heap_heapify(A, N, i, A[i]);
  }

  // Step1.5
  for (int i = N; i < n; i++) {
    if (ORelation(val(A[0]), val(A[i]))) {
      A[0] = A[i];
      heap_heapify(A, N, 0, A[0]);
    }
  }

  // Step2
  for (int i = N; i > 1; i--) {
    A[i - 1] = heap_deletemin(A, i);
  }
  /* end   p 課題 8                                                                              */
}
