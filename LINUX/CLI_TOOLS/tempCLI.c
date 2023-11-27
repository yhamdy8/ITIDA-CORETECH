#include<stdio.h>

#include<stdlib.h>

#include<getopt.h>



void print_usage()

{

	printf("Usage: temp -c <temp> | temp -f <temp> \n");

	exit(2);

}



void print_farenheit(float temp)

{



	float f = ( ((temp * 9) / 5) + 32) ;

	

	printf("%.2f centigrade is %.2f farenheit\n",temp,f);



}



void print_centigrade(float temp)

{



	float c = ( ((temp -32) * 5) / 32);

	

	printf("%.2f farenheit is %.2f centigrade\n",temp,c);



}



int main( int argc, char* argv[])

{

  if(argc < 2)

  {

    print_usage();

  }

  int options;

  int cflag=0;

  int fflag=0;

  

  while( (options = getopt(argc, argv ,"c:f:") ) != -1) // ':' means that we need to have an arg after the option,,, '::' means that its an optional argument

  {

  	switch(options)

  	{

  		case 'c' :

  			if(cflag)

  				{

  				  /*

  				  printf("Only one option\n");

  				  exit(1); // to make sure that we dont process anything

  				  */

  				  print_usage(); // used instead

  				}

  				else

  				{

  				  cflag++;

  				  fflag++; // to make sure that we take only 1 option

  				}

  				

  			//printf("You want centigrade\n");

  			print_farenheit( atof(optarg) );

  			break;

  				

  		case 'f' :

  			if(fflag)

  				{

  				  /*

  				  printf("Only one option\n");

  				  exit(1); // to make sure that we dont process anything

  				  */

  				  print_usage(); // used instead

  				}

  			else

  				{

  				  cflag++; // to make sure that we take only 1 option

  				  fflag++; 

  				}

  			//printf("You want farenheit\n");

  			print_centigrade( atof(optarg) );

  			break;

  			

  	}

  

  

  }











return 0;

}