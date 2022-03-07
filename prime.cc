///////////////////////////////////////////////////////////////////////////////
//
//  This implements a brute force method of determining the prime numbers
//  in a given range 1..n.
//
///////////////////////////////////////////////////////////////////////////////


/*

	This is all an example on how to do the prime function, but I can and should prob
	just implement this into my utilities module??

*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>

bool TestForPrime( int val )
{
    int limit, factor = 2;

    limit = (long)( sqrtf( (float) val ) + 0.5f );
    while( (factor <= limit) && (val % factor) )
        factor++;

    return( factor > limit );
}
/*		Commented out implementation so i only have one main function in project

int main()
{
	int i, n, p;

	printf( "Enter number n of numbers to test as primes.\n" );
	scanf( "%d", &n );
	printf( "Now enter %d numbers to test as prime.\n", n );
	fflush( stdout );

	for( i = 0; i < n; i++ ){
		printf( "Enter number:\n" );
		scanf( "%d", &p );

		if( TestForPrime( p ) )
			printf( "%d is a prime.\n", p );
		else
			printf( "%d is not a prime.\n", p );
	}
}

*/
