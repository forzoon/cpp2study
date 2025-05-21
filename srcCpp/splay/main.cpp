/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2024.
 ******************************************************************************************/

#include "Splay_test.h"

template <typename T> void testSplayPeriod( int n ) { //�����Է��ʲ���
   Splay<T> splay;
   for ( int i = 0; i < n; i++ ) splay.insert ( ( T ) i ); print ( splay );
   for ( int i = 0; i < n; i++ ) { splay.search ( ( T ) i ); print ( splay ); }
}

template <typename T> void testSplayRandom( Rank n ) { //������ʲ���
   Splay<T> splay;
   while ( splay.size() < n ) {
      T e = dice ( ( T ) n * 3 ); //[0, 3n)��Χ�ڵ�e
      switch ( dice ( 3 ) ) {
         case 0: { //���ң��ɹ��� <= 33.3%
            printf ( "Searching for " ); print ( e ); printf ( " ...\n" );
            splay.search ( e ) ?
            printf ( "Found with" ), print ( splay.root() ), printf ( "\n" ) :
            printf ( "Not found\n" );
            break;
         }
         case 1: { //ɾ�����ɹ��� <= 33.3%
            printf ( "Removing " ); print ( e ); printf ( " ...\n" );
            splay.remove ( e ) ?
            printf ( "Removal done\n" ) :
            print ( e ), printf ( " not exists\n" );
            break;
         }
         default: {//���룬�ɹ��� == 100%
            printf ( "Inserting " ); print ( e ); printf ( " ...\n" );
            splay.insert ( e );
            ( e == splay.root()->data ) ?
            printf ( "Insertion done with" ), print ( splay.root() ), printf ( "\n" ) :
            print ( e ), "duplicated";
            break;
         }
      } //switch
      print ( splay ); //���۵����ĸ��ӿڣ�Splay�������ҵ�����̬������ͳһ���
   } //while
   while ( splay.size() > 0 ) {
      T e = dice ( ( T ) n * 3 ); //[0, 3n)��Χ�ڵ�e
      printf ( "Removing " ); print ( e ); printf ( " ...\n" );
      splay.remove ( e ) ? printf ( "Removal done\n" ), print ( splay ) : print ( e ), printf ( " not exists\n" );
   }
} //�κ�������һ�ӿڣ���Բ�ͬ�ֲ��ķ��ʣ���֤���϶�Splay��̯�����Ľ���

int main( int argc, char* argv[] ) { //���������
   if ( 2 > argc ) { printf ( "Usage: %s <size of Test>\a\a\n", argv[0] ); return 1; }
   //srand((unsigned int)time(NULL)); //�������
   srand( 31415926 ); //�̶����ӣ������ӣ������ã�
   testSplayRandom<int> ( atoi ( argv[1] ) ); //Ԫ�����Ϳ�������������ѡ��
   testSplayPeriod<int> ( atoi ( argv[1] ) ); //Ԫ�����Ϳ�������������ѡ��
   return 0;
}