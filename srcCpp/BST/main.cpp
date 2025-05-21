/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2024.
 ******************************************************************************************/

/******************************************************************************************
 * Test of Binary Search Tree
 ******************************************************************************************/
#include "BST_test.h"

/******************************************************************************************
 * Test a BST
 ******************************************************************************************/
template <typename T> void testBST ( Rank n ) {
   if ( n < 1 ) return;
   BST<T> bst;
//
   while ( bst.size() < n ) bst.insert ( dice ( ( T ) n * 3 ) ); print ( bst ); //�������
   bst.stretchToLPath(); print ( bst ); //��ֱ��Ʋ
   while ( !bst.empty() ) bst.remove ( bst.root()->data ); //���
//
   while ( bst.size() < n ) bst.insert ( dice ( ( T ) n * 3 ) ); print ( bst ); //�������
   bst.stretchToRPath(); print ( bst ); //��ֱ����
   while ( !bst.empty() ) bst.remove ( bst.root()->data ); //���
//
   while ( bst.size() < n ) bst.insert ( dice ( ( T ) n * 3 ) ); print ( bst ); //�������
   stretchByZig( bst.root()->lc ); //��������ֱ����
   stretchByZag( bst.root()->rc ); //��������ֱ��Ʋ
   print ( bst );
   while ( !bst.empty() ) bst.remove ( bst.root()->data ); //���
//
   while ( bst.size() < n ) bst.insert ( dice ( ( T ) n * 3 ) ); print ( bst ); //�������
   stretchByZag( bst.root()->lc ); //��������ֱ��Ʋ
   stretchByZig( bst.root()->rc ); //��������ֱ����
   print ( bst );
   while ( !bst.empty() ) bst.remove ( bst.root()->data ); //���
//
   while ( bst.size() < n ) { //������롢��ѯ��ɾ��
      T e = dice ( ( T ) n * 3 ); //[0, 3n)��Χ�ڵ�e
      switch ( dice ( 3 ) ) {
         case 0: { //���ң��ɹ��� <= 33.3%
            printf ( "Searching for " ); print ( e ); printf ( " ... " );
            BinNodePosi<T> & p = bst.search ( e );
            p ?
            printf ( "Found with" ), print ( p->data ), printf ( "\n" ) :
            printf ( "not found\n" );
            break;
         }
         case 1: { //ɾ�����ɹ��� <= 33.3%
            printf ( "Removing " ); print ( e ); printf ( " ... " );
            bst.remove ( e ) ?
            printf ( "Done\n" ), print ( bst ) :
            printf ( "not exists\n" );
            break;
         }
         default: {//���룬�ɹ��� == 100%
            printf ( "Inserting " ); print ( e ); printf ( " ... " );
            printf ( "Done with" ), print ( bst.insert ( e )->data ), printf ( "\n" ), print ( bst );
            break;
         }
      }
   }
   while ( bst.size() > 0 ) { //���
      T e = dice ( ( T ) n * 3 ); //[0, 3n)��Χ�ڵ�e
      printf ( "Removing " ); print ( e ); printf ( " ... " );
      bst.remove ( e ) ? printf ( "Done\n" ), print ( bst ) : printf ( "not exists\n" );
   }
}

/******************************************************************************************
 * ���������
 ******************************************************************************************/
int main ( int argc, char* argv[] ) {
   if ( 2 > argc ) { printf ( "Usage: %s <size of Test>\a\a\n", argv[0] ); return 1; }
   srand((unsigned int)time(NULL)); //�������
   //srand( 31415926 ); //�̶����ӣ������ӣ������ã�
   testBST<int> ( atoi ( argv[1] ) ); //Ԫ�����Ϳ�������������ѡ��
   return 0;
}