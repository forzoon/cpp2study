/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2024.
 ******************************************************************************************/

#include "binTree_test.h"

int testID = 0; //���Ա��

// ������������߶�Ϊh�Ķ�����
template <typename T> bool randomBinTree ( BinTree<T> & btA, BinNodePosi<T> x, int h ) {
   if ( 0 >= h ) return false; //����h��
   if ( 0 < dice ( h ) ) //��1/h�ĸ�����ֹ��ǰ��֧������
      randomBinTree ( btA, btA.insert ( x, dice ( ( T ) h * h * h ) ), h - 1 );
   if ( 0 < dice ( h ) ) //��1/h�ĸ�����ֹ��ǰ��֧������
      randomBinTree ( btA, btA.insert ( dice ( ( T ) h * h * h ), x ), h - 1 );
   return true;
}

// �ڶ����������ȷ��һ���ڵ�λ��
template <typename T> BinNodePosi<T> randomPosiInBinTree ( BinNodePosi<T> root ) {
   if ( IsLeaf ( root ) ) return root;
   if ( !root->lc )
      return dice ( 6 ) ? randomPosiInBinTree ( root->rc ) : root;
   if ( !root->rc )
      return dice ( 6 ) ? randomPosiInBinTree ( root->lc ) : root;
   return dice ( 2 ) ?
          randomPosiInBinTree ( root->lc ) :
          randomPosiInBinTree ( root->rc ) ;
}

template <typename T> void testBinTree ( int h ) { //���Զ�����
   printf ( "\n  ==== Test %2d. Generate a binTree of height <= %d \n", testID++, h );
   BinTree<T> btA; print ( btA );
   btA.insert ( dice ( ( T ) h * h * h ) ); print ( btA );
   randomBinTree<T> ( btA, btA.root(), h ); print ( btA );

   printf ( "\n  ==== Test %2d. Double and increase all nodes by traversal\n", testID++ );
   btA.travPre ( Double<T>() ); btA.travPre ( Increase<T>() ); print ( btA );
   btA.travIn ( Double<T>() ); btA.travIn ( Increase<T>() ); print ( btA );
   btA.travPost ( Double<T>() ); btA.travPost ( Increase<T>() ); print ( btA );
   btA.travLevel ( Double<T>() ); btA.travLevel ( Increase<T>() ); print ( btA );
   Hailstone<T> hs; btA.travIn ( hs ); print ( btA );

   printf ( "\n  ==== Test %2d. Create a shadow by copying\n", testID++ );
   BinTree<T> btB( btA ); //��Ч��BinTree<T> btB = btA;
   print( btB );

   printf ( "\n  ==== Test %2d. Create a HART by attaching\n", testID++ );
   BinNodePosi<T> p;
   p = btB.root(); while (p->lc) p = p->lc; btB.attach( btA, p );
   p = btB.root(); while (p->lc) p = p->lc; btB.attach( btA, p );
   BinNodePosi<T> q;
   q = btB.root(); while (q->rc) q = q->rc; btB.attach( q, btA );
   q = btB.root(); while (q->rc) q = q->rc; btB.attach( q, btA );
   print( btB );

   printf ( "\n  ==== Test %2d. Remove subtrees\n", testID++ );
   while ( !btB.empty() ) {
      BinNodePosi<T> p = randomPosiInBinTree ( btB.root() ); //���ѡ��һ���ڵ�
      if ( dice ( 2 ) ) {
         printf ( "removing " ); print ( p->data ); printf ( " ...\n" );
         printf ( "%d node(s) removed\n", btB.remove ( p ) ); print ( btB );
      } else {
         printf ( "releasing " ); print ( p->data ); printf ( " ...\n" );
         BinTree<T>* S = btB.secede ( p ); print ( S );
         printf ( "%d node(s) released\n", S->size() ); S->remove(S->root()); print ( btB );
      }
   }
}

int main ( int argc, char* argv[] ) { //���Զ�����
   if ( 2 > argc ) { printf ( "Usage: %s <size of Test>\a\a\n", argv[0] ); return 1; }
   srand ( ( unsigned int ) time ( NULL ) );
   //srand( 31415926 ); //�̶����ӣ������ӣ������ã�
   testBinTree<int> ( atoi ( argv[1] ) ); //Ԫ�����Ϳ�������������ѡ��
   return 0;
}