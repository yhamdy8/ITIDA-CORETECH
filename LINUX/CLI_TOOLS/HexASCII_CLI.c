#include<stdio.h>

#include<string.h>

#include<stdlib.h>

#include<getopt.h>



//char hex2char(char hex[]);



int Hex2Dec(char hexChar);



char* Hex2ASCII(char hex[]);



int CheckHex(char* hex);



void print_usage(void);



int main(int argc, char* argv[])

{

	if(argc<2)

	{

		print_usage();

	}

	int options;

	

	 while( (options = getopt(argc, argv ,"i:") ) != -1)

	 {

		 switch(options)

		 {

			 case 'i':

				//char hex[399];

				//printf("Enter hex code to be converted to text: ");

				//scanf("%558[^\n]s", hex);

				if(CheckHex(optarg))

				{

					char* text = Hex2ASCII(optarg);

					printf("The hex text is:\n%s\n", text);

					free(text);

				}

				else

				{

					//printf("The input should be a hex number,0...9 | A...F\n");

					print_usage();

				}

				break;

		 }

	 }

	return 0;

}



int Hex2Dec(char hexChar)

{

	switch(hexChar)

	{

		case '1': return 1;

		case '2': return 2;

		case '3': return 3;

		case '4': return 4;

		case '5': return 5;

		case '6': return 6;

		case '7': return 7;

		case '8': return 8;

		case '9': return 9;

		

		case 'A':

		case 'a': return 10;

		case 'B':

		case 'b': return 11;

		case 'C':

		case 'c': return 12;

		case 'D':

		case 'd': return 13;

		case 'E':

		case 'e': return 14;

		case 'F':

		case 'f': return 15;

		

		default:

		{

			printf("Symbol error not found in hex elements: %c\n",hexChar);

			return -1;

		}

	}

}



char* Hex2ASCII(char hex[])

{

	int HexLength = strlen(hex); //length of the Hex code

	char* text=NULL;			 // char ptr to save res in

	int LastIndex = HexLength - 1;

	if(HexLength > 0)				// safety check

	{

		int CharCount;				// number of characters found as a result

		int OddHexCount = ( (HexLength %2) == 1 );	//check if number of Hex string is odd

		if(OddHexCount)								

		{

			CharCount = (HexLength / 2 ) + 1;		// we need to add an element cuz every 2 hex -> 1 char

		}

		else

		{

			CharCount = (HexLength / 2);			

		}

		text=(char*)malloc(CharCount + 1 ); 	// +1 for the '\0' operator

		

		for(int i= LastIndex; i >=0;i--)

		{

			if( ( (LastIndex - i) % 2 !=0) )

			{

				int DecValue = 16* Hex2Dec(hex[i]) + Hex2Dec(hex[i+1]);

				if(OddHexCount)	

					text[i/2+1] = DecValue;

				else 

					text[i/2] = DecValue;

			}

			else if(i == 0)

			{

				int DecValue = Hex2Dec(hex[0]);

				text[0] = DecValue;

			}

		}

		text[CharCount] = '\0';	

		}

		return text;

}



/*char hex2char(char hex[])

{

	char res;

	

	res=16* Hex2Dec(hex[0]) +Hex2Dec(hex[1]);

	

	

	return res;

}*/



int CheckHex(char* hex)

{

	printf("Checking: ");

	while(*hex)

	{

		printf("%c", *hex);

		switch(*hex)

		{

			case '0': 

			case '1': 

			case '2': 

			case '3': 

			case '4': 

			case '5': 

			case '6': 

			case '7': 

			case '8': 

			case '9': 

			case 'A':

			case 'a': 

			case 'B':

			case 'b': 

			case 'C':

			case 'c': 

			case 'D':

			case 'd': 

			case 'E':

			case 'e': 

			case 'F':

			case 'f': break;

			default:

			{

				//printf(" ..Failed.\n");

				//return 0;

				print_usage();

			}

		}

		hex++;

	}

	printf(" ..OK.\n");

	return 1;

}



void print_usage(void)

{

	printf("Usage: HexASCII -i <HEX>\n");

	exit(2);

}