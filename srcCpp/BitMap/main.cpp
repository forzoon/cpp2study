/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2024.
 ******************************************************************************************/

#pragma warning(disable : 4996 4800)
#include "_share/util.h"
//#include "Bitmap_O1_init.h"
#include "Bitmap.h"

/******************************************************************************************
 * ����λͼ
 ******************************************************************************************/
int testBitmap( int n, int t ) {
   bool* B = new bool[n]; //����λͼ
   Bitmap M ( n ); //��Чλͼ
   while ( t-- > 0 ) { //�ظ�ʹ��λͼ���
      memset ( B, 0, n * sizeof ( bool ) ); //��λ���㣬O(n)
      M.reset(); //�߼����㣬O(1)
      for ( int i = 0; i < 3 * n; i++ ) { //������
         Rank k = dice ( n ); //�����λ����
         if ( dice ( 2 ) ) { //��50%�ĸ��ʲ���
            B[k] = true; M.set ( k );
         } else { //��50%�ĸ������
            B[k] = false; M.clear ( k );
         }
      }
      //M.set( 29 ); //��ʱ�������������Է�����Ա����Գ���
      int sz = 0; for ( int j = 0; j < n; j++ ) sz += B[j];
      printf( "\nM[] x %d %s %d\n", M.size(), ( M.size() == sz ? "==" : "<>" ), sz );
      for ( int j = 0; j < n; j++ ) printf ( "%c", M.test ( j ) ? 'x' : '.' );
      int k = 0;
      while ( k++ < n ) //��λ�ضԱ�
         if ( B[k] != M.test ( k ) ) //һ�����ֲ���
            break; //�漴�˳�
      if ( k < n ) { //�����棨assert:: k == n+1��
         printf ( "\n B[]\n" );
         for ( int j = 0; j <= k; j++ ) printf ( "%c", B[j] ? 'x' : '.' );
         printf ( "\n M[] x %d\n", M.size() );
         for ( int j = 0; j <= k; j++ ) printf ( "%c", M.test ( j ) ? 'x' : '.' );
         printf ( "\n" );
      } else
         printf( "\nTest %4d OK\n", t );
   }
   delete [] B;
   return 0;
}

/******************************************************************************************
 * ����λͼ
 ******************************************************************************************/
int main( int argc, char* argv[] ) {
   if ( 3 > argc ) { printf ( "Usage: %s <bitmap size> <#Test>\a\a\n", argv[0] ); return 1; }
   srand((unsigned int)time(NULL)); //�������
   //srand( 31415926 ); //�̶����ӣ������ӣ������ã�
   return testBitmap( max(0, atoi(argv[1])), max(0, atoi(argv[2]))); //��������
}