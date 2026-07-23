// Daniel Huynh, Jesse Chaney CS201
// This program analyzes floating-point values and displays their IEEE 754 components.
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define F_EXP_BITS_DEFAULT 8
#define F_FRAC_BITS_DEFAULT 23
#define F_FRAC_ADD_DEFAULT 1.0

int main(int argc, char * argv [])
{
	int e_flag;
	long exp_bits = F_EXP_BITS_DEFAULT;
	long frac_bits = F_FRAC_BITS_DEFAULT;
	double exp_bias = 127;
	double frac_add = F_FRAC_ADD_DEFAULT;
	int type =0;
	char word[100];
	bool verbose;
	char * input_file = NULL;
	FILE * ifile = stdin;

	int opt;
	while((opt = getopt(argc, argv, "i:dhbm :e:E:f:F:v:H")) != -1)
	{
		switch(opt)
		{
			case 'i'://specify input file

				input_file = optarg;
				ifile = fopen(input_file, "r");
				if(ifile == NULL)
				{
					fprintf(stderr, " could not open file: %s\n", input_file);
					exit(EXIT_FAILURE);
				}
				break;

			case 'd': //double precision
				exp_bits = 11;
				frac_bits =52;
				exp_bias = 1023;
				break;

			case 'h': //half precision
				exp_bits= 5;
				frac_bits = 10;
				exp_bias = 15;
				break;
			case 'b': //bfloat
				exp_bits = 8;
				frac_bits = 7;
				exp_bias = 127;
				break;
			case 'm': //minifloat
				exp_bits = 4;
				frac_bits =3;
				exp_bias = -2;
				break;
			case 'e': //exponent bits
				exp_bits = strtol(optarg, NULL, 10);
				e_flag =1;

				break;
			case 'E': // exponent bias
				exp_bias = atoi(optarg);
				break;

			case 'f': //frac bits

				frac_bits = strtol(optarg, NULL, 10);
				break;

			case 'F': //frac value
				frac_add = atoi(optarg);
				break;

			case 'v': //verbose
				verbose = true;
				printf("verbose%d", verbose);
				printf("fracadd:%f", frac_add);
				break;
			case 'H': //help menu
				printf("float-2-hex\n"
						"-i <file>      specify input file\n"
						"-d		double precision\n"
						"-h		half precision\n"
						"-b		bfloat\n"
						"-m		minifloat\n"
						"-e		set exponenet bits\n"
						"-E		set exponenet bias\n"
						"-f		set fraction bits\n"
						"-F		set fraction value\n"
						"-v		verbose statement\n"
						"-H		Help message\n");

				exit(EXIT_SUCCESS);


			case '?': //default

				break;
		}

	}

	//masks
	{
		unsigned long mask = 0x1l << (frac_bits + exp_bits);
		unsigned long exp_mask = 0x1Lu;
		unsigned long frac_mask;

		for(int i =0; i < exp_bits -1; i++)
		{
			exp_mask <<= 1L; //build the mask
			exp_mask |= 0x1Lu; //one bit at a time
		}

		exp_mask <<= frac_bits; //shift into place
		frac_mask = ~(exp_mask | mask);
		//stdin
		while(fgets(word, 100, ifile))
		{

			double sign;
			double ub_exp;
			unsigned long exp;
			unsigned long uv;
			double frac;

			word[strlen(word) - 1] = '\0';
			mask = 0x1l << (frac_bits + exp_bits);
			//unsigned long uv;
			sscanf(word, "%lx", &uv);

			sign = (uv & mask);
			exp = (uv & exp_mask);
			frac = (uv & frac_mask);

			/*
			   unsigned long exp = uv & exp_mask;
			   unsigned long frac=  uv & exp_mask;
			   */

			ub_exp = exp >> frac_bits;


			//determine if normalized denormalized etc
			if(ub_exp == 0)//denormalized, exponent is all zeros
			{
				type =1;
			}
			else if(exp == exp_mask)//special values, exp is all ones
			{
				if(frac ==0)//+/-infinity frac is zero then +/- infinity
				{
					type = 2;
				}
				else//frac not zero then NaN
					type = 3;
			}
			else
			{
				type =4; //normalized, exp is neither all zero or ones
			}
			printf("%s\n", word);
			printf("\t%d ", (uv & mask) ? 1 : 0);
			for(int i = exp_bits; i > 0; --i)
			{
				mask >>= 1;
				printf("%d", (uv & mask) ? 1 : 0);
			}
			printf(" ");
			for(int i = frac_bits; i > 0; --i)
			{
				mask >>=1;
				printf("%d", (uv & mask) ? 1 :0 );
			}
			for(int i =0; i<1; ++i)
			{
				printf("\n\ts ");
				for(int b=0; b< exp_bits; ++b)
				{
					printf("e");
				}
				printf(" ");
				for(int b=0; b < frac_bits; ++b)
				{
					printf("f");
				}
				printf("\n");
			}
			if(type ==1) ///denormalized
			{
				double value=0.0;
				double E;
				double frac_d = (uv & frac_mask) / pow (2.0, frac_bits);
				double M= (uv & frac_mask) / pow (2.0, frac_bits);
				double sign_value =0.0;
				if(e_flag ==1)
				{
					exp_bias = pow(2, exp_bits-1)-1;
				}
				E = 1.0 - exp_bias;
				printf("\tdenormalized value\n"); 
				if(sign == 0)
				{
					printf("\tsign:\t\tpositive\n");
					sign_value =2;
				}
				else
				{
					printf("\tsign:\t\tnegative\n");
					sign_value = 1;
				}
				printf("\tbias:\t\t%-10.0lf\n", exp_bias);
				printf("\tunbiased exp:\t%-10.0lf\n", ub_exp); 
				printf("\tE:\t\t%-10.0lf\n", E);
				printf("\tfrac:\t\t%-.20lf\n", frac_d);
				printf("\tM:\t\t%-.20lf\n", M);
				value = pow(-1, sign_value)* M * pow(2.0, E);
				printf("\tvalue:\t\t%-.20lf\n", value);
				printf("\tvalue:\t\t%-.20le\n\n", value);

			}
			if(type ==2) //+/- infinity
			{
				printf("\tspecial value\n");
				if(sign == 0)
				{
					printf("\tpositive infinity\n\n");
				}
				else
				{
					printf("\tnegative infinity\n\n");
				}
			}
			if(type ==3)//NaN
			{
				printf("\tspecial value\n");
				printf("\tNaN\n\n");

			}
			if(type ==4) // normalized
			{
				double frac_n;
				double E;
				double sign_value=0;
				double value = 0.0;
				double M = 0.0;
				if(e_flag ==1)
				{
					exp_bias = pow(2, exp_bits-1)-1;
				}
				E = ub_exp - exp_bias;
				printf("\tnormalized value\n");
				if(sign ==0)
				{
					printf("\tsign:\t\tpositive\n");
					sign_value =2;
				}
				else
				{
					printf("\tsign:\t\tnegative\n");
					sign_value =1;
				}
				printf("\tbias:\t\t%-10.0lf\n", exp_bias);
				printf("\tunbiased exp:\t%-10.0lf\n", ub_exp); 
				printf("\tE:\t\t%-10.0lf\n", E);

				frac_n = (uv & frac_mask) / pow (2.0, frac_bits);
				M = frac_n + 1;
				printf("\tfrac:\t\t%-.20lf\n", frac_n);
				printf("\tM:\t\t%-.20lf\n", M);
				value = pow(-1, sign_value)* M * pow(2.0, E);
				printf("\tvalue:\t\t%-.20lf\n", value);
				printf("\tvalue:\t\t%-.20le\n\n", value);
			}

		}

	}
	if(input_file != NULL)
	{
		fclose(ifile);
	}
	return EXIT_SUCCESS;
}
