#include <stdio.h>
#include <math.h>
#include <time.h>            // include the necessary libraries
#include <stdlib.h>

typedef struct     // struct representing each site in the lattice
{
int state;
}site;

const long int Num_of_sites = 1000;          // Number of sites in the 1D lattice

int random_num_interval(const int Num_of_sites);         // random number generator function prototype
int MCS_updater(int MCS_step);                            // Monte Carlo Step updating function prototype
void zero_array(site func_array[Num_of_sites], int counter);    // prototype for the function which initializes all sites to zero.
void A_is_normal(int start_site2, int right_neighbor, int left_neighbor, int rand_site_num);
void zero_mcscount_num_up_num_down(int *Number_up, int *Number_down, int *MCS_count);

int main()                                 // main function
{
double p = 0.00;              // probability of updating a long-range neighbor
double PofX = 0.00;           // Exit probability (more commonly labeled E(x))
int c=0,k=0,f=0,g=0,v=0;        // counting integers
double mcs = 0;                 // average number of updates per x-value. In my case, 1 site-pair selection = 1 update = 1 Monte Carlo Step
double kprime = 0;              // x-value, percent initially in the up-state
int Number_up = 0;              // number of up sites in the lattice at any given time
int Number_down = 0;            // number of down sites in the lattice at any given time
int rand_site_num = 0;          // site "A"
int start_site2 = 0;            // site "B"
int left_neighbor = 0;          // the neighbor to the left of A (if we imagine it this way [l_n] [A] [B]  [r_n]
int right_neighbor = 0;         // the neighbor to the right of B
int number_up_sum = 0;          // total amount of times a lattice has ended unanimously "up"
const int u = 1;                // represents an "up" opinion
const int d = 0;                // represents a "down" opinion
int MCS_count = 0;              // Total number of MCS (while loop iterations) in bringing system from initial conditions to unanimity (up OR down)
const long int num_of_runs = 1000;    // number of times to go through the while (updating) loop, this is nested inside the x-value loop
const double deltaX = 0.01;           // how much X is incremented by in the outer for loop
const int Num_of_slots = 1.000/deltaX;    // gives an integer amount which lets the outer for loop (x-value loop) know when to quit
int random_long = 0;                     // random long-range site to be updated by "A"
int random_long2 = 0;                     // random long-range site to be updated by "B"
double rand_probability = 0;              // probability of LR update for site "A"
double rand_probability2 = 0;              // probability of LR update for site "B"


srand(time(NULL));    // seed the random number generator

FILE * output=0;                // pointer to file which gives the PofX for every x-value, and the corresponding x-values
FILE * output_MCS =0;           // pointer to the file which gives the mcs for every x-value, and the corresponding x-values
output_MCS = fopen("SM1_Data/1000_0_1000_MCS.dat", "a");      // open and name the files
output = fopen("SM1_Data/1000_0_1000.dat", "a");       // KEY:   <Num_of_sites>  <p>  <Num_of_runs>

clock_t start;               // initialize clock time variables
clock_t finish;

site sitestruct[Num_of_sites];       // create a 1D array (lattice) of the sites
int MCS_info[num_of_runs];           // create a 1D array (size: Num_of_runs) which stores the MCS upon the completion of every while loop at a particular
                                     // completion of every while loop at a particular x-value. This is then averaged to find the
start = clock();                     // average amount of MCS per x-value. It does not matter if all sites end up "up" or "down"

for (k =0; k < (Num_of_slots + 1); k++)     // Begin For Loop 1
{
	kprime = k*deltaX;              // create an initial up-spin percentage  (e.g. x = 0.04 (4%))
	number_up_sum = 0;              // amount of times the lattice has ended unanimously up is reset
	MCS_count = 0;                  // amount of while loop iterations (Monte Carlo Steps) is reset for every x-value
	if((kprime !=0) && (kprime !=1))    // IF_1 Begin
	{                                   // No sense going through the Num_of_runs loop if we are at x = 0 or x = 1
	for(f = 0; f < num_of_runs; f++)     // Begin For Loop 2
	{
		zero_array(sitestruct,g);      // zero the array of sites
		zero_mcscount_num_up_num_down(&Number_up, &Number_down, &MCS_count);
		c = kprime*Num_of_sites;       // create percentage of sites which are initially up (also called the x-value)
		while(c>0)         // WHILE_Loop_1 Begin
		{
			rand_site_num = random_num_interval(Num_of_sites);   // select random site within the lattice
			if(sitestruct[rand_site_num].state == u)      // if it's already up, don't update it
			{
				//do nothing
			}
			else if (sitestruct[rand_site_num].state == d)  // if the randomly selected site is down, it is changed to "up"
			{
				sitestruct[rand_site_num].state = u;     // the actual reassignment of site status
				c = c - 1;                              // decrement the number of sites to still update
				Number_up = Number_up + 1;            //update the number of "up" sites in the lattice
				Number_down = Num_of_sites - Number_up;  // Update the number of "down" sites in the lattice
			}
		}              // WHILE_Loop_1 End

	while((Number_up < Num_of_sites) && (Number_down < Num_of_sites))      // WHILE_LOOP_2 Begin
	{
        rand_site_num = Num_of_sites * ((double) rand ()) * (1.000000/((double) RAND_MAX + 1));  // Pick the "A" site
		if(rand_site_num == Num_of_sites - 1)   // Say that there are 100 sites in the lattice. if array index 99 is picked, I must loop back to
			{                                   // the beginning of the array to find a neighbor, otherwise I would get a memory access error
				start_site2 = 0;                // "B" is the site at array index 0
				left_neighbor = rand_site_num - 1;    // l_n = 99-1 = 98
				right_neighbor = 1;                   // r_n = array index 1
			}
		if(rand_site_num == Num_of_sites - 2)           // Site "A" = 98
			{
				start_site2 = Num_of_sites - 1;           // "B" = index 99
				left_neighbor = rand_site_num - 1;        // l_n = index 97
				right_neighbor = 0;                       // r_n = index 0
			}
		if(rand_site_num == 0)                           // "A" = index 0
			{
				start_site2 = 1;                         // "B" = index 1
				left_neighbor = Num_of_sites - 1;        // l_n = index 99
				right_neighbor = 2;                      // r_n = index 2
			}
		else {                                          // Any other scenario
                A_is_normal(start_site2, right_neighbor, left_neighbor, rand_site_num);
		     }

		MCS_count = MCS_updater(MCS_count);     // A pair of sites has been picked, this counts as 1 Monte Carlo Step

		if(sitestruct[rand_site_num].state == sitestruct[start_site2].state)    // Two parent sites "A" and "B" are both up, or both down
	{               // SITES_AGREE_BEGIN
				random_long = Num_of_sites * (((double) rand()) * (1.000000/((double) RAND_MAX + 1)));   // random long range site to be updated by A
				random_long2 = Num_of_sites * (((double) rand()) * (1.000000/((double) RAND_MAX + 1)));  // random long range site to be updated by B
				rand_probability = ((double) rand()) * (1.000000/((double) RAND_MAX));                 // probability of "A" updating a LR neighbor
				rand_probability2 = ((double) rand()) * (1.000000/((double) RAND_MAX));               // probability of "B" updating a LR neighbor

				if(rand_probability <=p)          // "A" updates a LR neighbor.
				{
					if((sitestruct[random_long].state != sitestruct[rand_site_num].state) && (sitestruct[rand_site_num].state == u))        //  random_long is not the same status as "A"
					{
						sitestruct[random_long].state = sitestruct[rand_site_num].state;    // update that site's status
                        Number_up = Number_up + 1;                // update the number_up
                        Number_down = Num_of_sites - Number_up;     // update the number_down
                    }
                    if((sitestruct[random_long].state != sitestruct[rand_site_num].state) && (sitestruct[rand_site_num].state == d))
                    {
                        sitestruct[random_long].state = sitestruct[rand_site_num].state;    // update that site's status
                        Number_down = Number_down + 1;                  // update the number_up
                        Number_up = Num_of_sites - Number_down;          // update the number_down
                    }
				}

				if(rand_probability >p)             // "A" updates a short-range neighbor, namely l_n
				{
					if((sitestruct[left_neighbor].state != sitestruct[rand_site_num].state) && (sitestruct[rand_site_num].state == u))//  random_long is not the same status as "A"
					{
						sitestruct[left_neighbor].state = sitestruct[rand_site_num].state; // update l_n's status
                        Number_up = Number_up + 1;                       // update the number_up
                        Number_down = Num_of_sites - Number_up;            // update the number_down
                    }
                    if((sitestruct[left_neighbor].state != sitestruct[rand_site_num].state) && (sitestruct[rand_site_num].state == u))
                    {
                        sitestruct[left_neighbor].state = sitestruct[rand_site_num].state; // update l_n's status
                        Number_down = Number_down + 1;                   // update the Number_down
                        Number_up = Num_of_sites - Number_down;         // update the number_up
                    }
				}

				if(rand_probability2 <=p)                      // "B" updates a long-range neighbor (random_long2)
				{
					if((sitestruct[random_long2].state != sitestruct[start_site2].state) &&  (sitestruct[start_site2].state == u))  // random_long2 is not the same status as "B"
					{
					    sitestruct[random_long2].state = sitestruct[start_site2].state;   // update random_long2 status
                        Number_up = Number_up + 1;                    // update the number_up
                        Number_down = Num_of_sites - Number_up;     // update the number_down
					}
					if((sitestruct[random_long2].state != sitestruct[start_site2].state) &&  (sitestruct[start_site2].state == d))
                    {
                        sitestruct[random_long2].state = sitestruct[start_site2].state;
                        Number_down = Number_down + 1;                      // update the number_down
                        Number_up = Num_of_sites - Number_down;                // update the number_up
                    }
				}

				if(rand_probability2 > p)             // "B" updates a short-range neighbor (r_n)
				{
					if((sitestruct[right_neighbor].state != sitestruct[start_site2].state) && (sitestruct[rand_site_num].state == u))   // r_n is not the same status as "B"
					{
					    sitestruct[right_neighbor].state = sitestruct[start_site2].state;
                        Number_up = Number_up + 1;                  // update the number_up
                        Number_down = Num_of_sites - Number_up;     // update the number_down
					}
                    if((sitestruct[right_neighbor].state != sitestruct[start_site2].state) && (sitestruct[rand_site_num].state == d))
                    {
                        sitestruct[right_neighbor].state = sitestruct[start_site2].state;
                        Number_down = Number_down + 1;            // update the number_down
                        Number_up = Num_of_sites - Number_down;      // update the number_up
                    }
				}
	    }                     // SITES_AGREE_END
		else if (sitestruct[rand_site_num].state != sitestruct[start_site2].state) { /*do nothing*/ } // A.state != B.state, no updates happening
	}                 // WHILE_LOOP_2 End
		if(Number_up == Num_of_sites)
		{
			number_up_sum = number_up_sum + 1;
		}

		PofX = (((double) number_up_sum) * (1.0/(double) num_of_runs));    // PofX = number of times lattice is unanimously up/num_of_runs
		MCS_info[f] = MCS_count;               // each time Lattice reached unanimity, the total number of MCS is stored into array of size num_of_runs
		}            // End For Loop 2 (num_of_runs loop)
		}            // IF_1 End

	if(kprime == 0){PofX = 0.00;}
	if(kprime == 1){PofX = 1.00;}   // PofX = E(x), also known as E(x,L), where L is the system size
                                     // Here, L = Num_of_sites
	if(kprime !=1 && kprime !=0)            // remembering that we are now back in For Loop 1, the x-value loop
	{
		for(v = 0; v < num_of_runs; v++)
		{
			mcs = mcs + MCS_info[v];              // sum all members in the MCS_info array
		}
		mcs = mcs*(1.000000/(double)num_of_runs);            // average all members in the array to find out average MCS for a particular x-value (initial "up" percentage)
		fprintf(output_MCS, "%3f %3f\n", kprime, mcs);
		printf("%3f  ",mcs);  //display MCS on screen for particular x-value
		mcs = 0;             // reinitialize mcs for the next x-value
	}
	if(kprime ==0 || kprime ==1)    // remember that kprime = x-value (e.g. 0.15, or 15%)
	{
		fprintf(output_MCS, "%3f 0.000000\n", kprime);     // write to the MCS file
		printf("0.000000  ");
	}

	fprintf(output, "%3f %3f\n", kprime, PofX);        // write to the PofX file
	printf("%3f %3f %ld\n", kprime, PofX, Num_of_sites);    //more printing statements

}   // End For Loop 1

finish = clock();  // record simulation end time
fclose(output);
fclose(output_MCS);            // close the files that were opened and to which data was written

double sim_time = (((double) (finish - start)) / (CLOCKS_PER_SEC));
printf("\nTime elapsed was: %3f s = %3f minutes\n", sim_time, sim_time * 0.016667);   // print to the screen how long the simulation took

return 0;     // return 0, for good form
}

int random_num_interval (const int Num_of_sites)           // finds a random number from 0 to Num_of_sites -1 (corresponding to array indexes
{
	int t = 0;
	t = Num_of_sites * (((double) rand()) / ((double) RAND_MAX + 1));              /*return r*Num_of_sites*/
	return t;
}

int MCS_updater(int MCS_step)               // updates the number of MCS taken. This is called once for every WHILE_LOOP_2 iteration
{
	MCS_step = MCS_step + 1;
	return MCS_step;
}

void zero_array(site func_array[Num_of_sites], int counter)             // zeros the array (Lattice) of sites
{
	counter = 0;
	for(counter =0; counter < Num_of_sites; counter++)
	{
		func_array[counter].state = 0;
	}
}

//if(rand_site_num == Num_of_sites - 1)   // Say that there are 100 sites in the lattice. if array index 99 is picked, I must loop back to
//			{                                   // the beginning of the array to find a neighbor, otherwise I would get a memory access error
//				start_site2 = 0;                // "B" is the site at array index 0
//				left_neighbor = rand_site_num - 1;    // l_n = 99-1 = 98                 A_is_N_minus_1
//				right_neighbor = 1;                   // r_n = array index 1
//			}
//		if(rand_site_num == Num_of_sites - 2)           // Site "A" = 98
//			{
//				start_site2 = Num_of_sites - 1;           // "B" = index 99
//				left_neighbor = rand_site_num - 1;        // l_n = index 97                A_is_N_minus_2
//				right_neighbor = 0;                       // r_n = index 0
//			}
//		if(rand_site_num == 0)                           // "A" = index 0
//			{
//				start_site2 = 1;                         // "B" = index 1
//				left_neighbor = Num_of_sites - 1;        // l_n = index 99                   FUNC A_is_0
//				right_neighbor = 2;                      // r_n = index 2
//			}
//void A_is_N_minus_1(const int Num_of_sites, int right_neighbor, int left_neighbor, int rand_site_num, int start_site2)
//{
//
//}
//
//void A_is_N_minus_2(const int Num_of_sites, int right_neighbor, int left_neighbor, int rand_site_num)
//{
//
//}
//
//void A_is_0(const int Num_of_sites, int right_neighbor, int left_neighbor, int rand_site_num)
//{
//
//}

void A_is_normal(int start_site2, int right_neighbor, int left_neighbor, int rand_site_num)
{
    start_site2 = rand_site_num + 1;              // B = A + 1
    left_neighbor = rand_site_num - 1;             // l_n = A-1                       A_is_normal
    right_neighbor = rand_site_num + 2;            // r_n = A+2 or B+1
}

void zero_mcscount_num_up_num_down(int *Number_up, int *Number_down, int *MCS_count)
{
        *Number_up = 0;                 // Reinitialize Number_up to zero
		*Number_down = 0;               // Reinitialize Number_down to zero
		*MCS_count = 0;                 // Reinitialize MCS_count, the number of while loop iterations to bring a system to unanimity
}














//#include <stdio.h>
//#include <math.h>
//#include <time.h>
//#include <stdlib.h>
//
//typedef struct
//{
//int state;
//}site;
//
//const int Num_of_sites = 1000;
//const int num_of_runs = 10000;
//const double deltaX = 0.01;
//const int Num_of_slots = 1/deltaX;
//
//int random_num_interval(const int Num_of_sites);
//int MCS_updater(int MCS_step);
//void zero_array(site func_array[Num_of_sites], int counter);
//double SUM_MCS_AVG(int MCS_array[][num_of_runs], int k_index, int counter1);
//
//int main()
//{
//
//double p = 1.00;
//double PofX = 0.00;
//int c=0,k=0,f=0,g=0,v =0;
//double kprime = 0;
//int Number_up = 0;
//int Number_down = 0;
//int selected_site = 0;
//int start_site2 = 0;
//int left_neighbor = 0;
//int right_neighbor = 0;
//int number_up_sum = 0;
//const int u = 1;
//const int d = 0;
//int MCS_count;
//
//srand(time(NULL));
//
//char filename[25];
//FILE * output =0;
//FILE * output_MCS =0;
//output_MCS = fopen("SM1_ALPS_MCS.dat", "a");        // create file pointer for MCS information file
//output = fopen("SM1_ALPS.dat", "a");                // create file pointer for PofX information file
//
//clock_t start;
//clock_t finish;
//
//site sitestruct[Num_of_sites];
//int MCS_info[Num_of_slots][num_of_runs];
//
//start = clock();
//
//for (k =0; k < (Num_of_slots + 1); k++)      // begin of loop alpha, the delta x loop
//{
//        kprime = k*deltaX;
//        number_up_sum = 0, MCS_count = 0;         // reinitialize MCS_count,MCS_fail and MCS_pass for each x-value.
//        if((kprime !=0) && (kprime !=1))       // begin pofx condition
//        {
//        /*beginning of initialization sequence, seq 1*/
//        for(f = 0; f < num_of_runs; f++)        // begin of loop beta, the num of runs per x value loop
//        {
//                zero_array(sitestruct, g);
//                Number_up =0, Number_down = 0, MCS_count = 0;
//                c = kprime*Num_of_sites;
//                while(c>0)
//                {
//                        selected_site = random_num_interval(Num_of_sites);
//                        if(sitestruct[selected_site].state == u)
//                        {
//                                //do nothing
//                        }
//                        else if (sitestruct[selected_site].state == d)
//                        {
//                                sitestruct[selected_site].state = u;
//                                c = c - 1;
//                                Number_up = Number_up + 1;
//                                Number_down = Num_of_sites - Number_up;
//                        }
//                }
//            /*end of initialization sequence, seq 1*/
//            /*beginning of update sequence, seq 2*/
//        while((Number_up < Num_of_sites) && (Number_down < Num_of_sites))
//        {
//                    /*book-end conditions begin*/
//                int rand_site_num = Num_of_sites * (((double) rand ()) / ((double) RAND_MAX + 1));
//                if(rand_site_num == Num_of_sites - 1)
//                        {
//                                start_site2 = 0;
//                                left_neighbor = rand_site_num - 1;
//                                right_neighbor = 1;
//                        }
//                if(rand_site_num == Num_of_sites - 2)
//                        {
//                                start_site2 = Num_of_sites - 1;
//                                left_neighbor = rand_site_num - 1;
//                                right_neighbor = 0;
//                        }
//                if(rand_site_num == 0)
//                        {
//                                start_site2 = 1;
//                                left_neighbor = Num_of_sites - 1;
//                                right_neighbor = 2;
//                        }
//                else {
//                        start_site2 = rand_site_num + 1;
//                        left_neighbor = rand_site_num - 1;
//                        right_neighbor = rand_site_num + 2;
//                     }
//                    /*book-end conditions end*/
//                if(sitestruct[rand_site_num].state == sitestruct[start_site2].state)  // two sites are in agreement
//                {
//                                int random_long = Num_of_sites * (((double) rand()) / ((double) RAND_MAX + 1));
//                                int random_long2 = Num_of_sites * (((double) rand()) / ((double) RAND_MAX + 1));
//                                double rand_probability = (((double) rand()) / ((double) RAND_MAX));
//                                double rand_probability2 = (((double) rand()) / ((double) RAND_MAX));
//
//                                if(rand_probability <=p)
//                                {
//                                        if(sitestruct[random_long].state != sitestruct[rand_site_num].state)
//                                        {
//                                                sitestruct[random_long].state = sitestruct[rand_site_num].state;
//                                                MCS_count = MCS_updater(MCS_count);
//                                                        if(sitestruct[rand_site_num].state == u)
//                                                        {
//                                                                Number_up = Number_up + 1;
//                                                                Number_down = Num_of_sites - Number_up;
//                                                        }
//                                                        if(sitestruct[rand_site_num].state == d)
//                                                        {
//                                                        Number_down = Number_down + 1;
//
//
//                                                        Number_up = Num_of_sites - Number_down;
//                                                        }
//                                        }
//                                }
//
//                                if(rand_probability >p)
//                                {
//                                        if(sitestruct[left_neighbor].state != sitestruct[rand_site_num].state)
//                                        {
//                                                sitestruct[left_neighbor].state = sitestruct[rand_site_num].state;
//                                                MCS_count = MCS_updater(MCS_count);
//                                                if(sitestruct[rand_site_num].state == u)
//                                                   {
//                                                        Number_up = Number_up + 1;
//                                                        Number_down = Num_of_sites - Number_up;
//                                                   }
//                                                if(sitestruct[rand_site_num].state == d)
//                                                   {
//                                                        Number_down = Number_down + 1;
//                                                        Number_up = Num_of_sites - Number_down;
//                                                   }
//                                        }
//                                }
//
//                                if(rand_probability2 <=p)
//                                {
//                                        if(sitestruct[random_long2].state != sitestruct[start_site2].state)
//                                        {
//                                                sitestruct[random_long2].state = sitestruct[start_site2].state;
//                                                MCS_count = MCS_updater(MCS_count);
//                                                if(sitestruct[start_site2].state == u)   /*I put rand_site_num here in my working algorithm, doesn't make a diff.*/
//                                                {
//                                                        Number_up = Number_up + 1;
//                                                        Number_down = Num_of_sites - Number_up;
//                                                }
//                                                if(sitestruct[start_site2].state == d)
//                                                {
//                                                        Number_down = Number_down + 1;
//                                                        Number_up = Num_of_sites - Number_down;
//                                                }
//                                        }
//                                }
//
//                                if(rand_probability2 > p)
//                                {
//                                        if(sitestruct[right_neighbor].state != sitestruct[start_site2].state)
//                                        {
//                                                sitestruct[right_neighbor].state = sitestruct[start_site2].state;
//                                                MCS_count = MCS_updater(MCS_count);
//                                                if(sitestruct[rand_site_num].state == u)
//                                                   {
//                                                        Number_up = Number_up + 1;
//                                                        Number_down = Num_of_sites - Number_up;
//                                                   }
//
//                                                if(sitestruct[rand_site_num].state == d)
//                                                   {
//                                                        Number_down = Number_down + 1;
//                                                        Number_up = Num_of_sites - Number_down;
//                                                   }
//                                        }
//                                }
//                }
//                else if (sitestruct[rand_site_num].state != sitestruct[start_site2].state)
//                        {
//                              MCS_count = MCS_updater(MCS_count);   //update the MCS count
//                        }
//        }
//            /*end of update sequence, sequence 2*/
//                if(Number_up == Num_of_sites)
//                {
//                        number_up_sum = number_up_sum + 1;
//                }
//
//                PofX = (((double) number_up_sum) / ((double) num_of_runs));    // find PofX for a particular x-value.
//               MCS_info[k][f] = MCS_count;          // store the MCS into a 2D array MCS_info
//               // fprintf(output_MCS, "%d %d %d\n", MCS_count, k, f);         // store the MCS into a file
//                }       // end of loop beta, the num of runs loop
//        }
//        if(kprime == 0){PofX = 0.00;}
//        if(kprime == 1){PofX = 1.00;}
//
//if(kprime != 1 && kprime != 0)
//{
//    double q = SUM_MCS_AVG(MCS_info, k, v);                  // compute the average MCS per x-value
//    fprintf(output_MCS, "%3f\n", q);                         // print the information to a file
//}
//if(kprime == 0 || kprime ==1)
//{
//    fprintf(output_MCS, "0\n");
//}
//
//printf(" %3f %3f\n",kprime,PofX);    // this is printed out 1.000/deltaX times
//fprintf(output, "\n%3f %3f", kprime, PofX);
//
//}        // end of loop alpha, the delta x loop,
//
//finish = clock();
//fclose(output);          // close POfX information file
//fclose(output_MCS);       // close MCS information file
//
//double sim_time = (((double) (finish - start)) / (CLOCKS_PER_SEC));
//printf("\nTime elapsed was: %3f s = %3f minutes\n", sim_time, sim_time / (60));
//
//return 0;
//}
//
//int random_num_interval(const int Num_of_sites)
//{
//        int t = 0;
//        t = Num_of_sites * (((double) rand()) / ((double) RAND_MAX + 1));              /*return r*Num_of_sites*/
//        return t;
//}
//
//int MCS_updater(int MCS_step)
//{
//        MCS_step = MCS_step + 1;
//        return MCS_step;
//}
//
//void zero_array(site func_array[Num_of_sites], int counter)
//{
//        counter = 0;
//        for(counter =0; counter < Num_of_sites; counter++)
//        {
//            func_array[counter].state = 0;
//        }
//}
//
//double SUM_MCS_AVG(int MCS_array[][num_of_runs], int k_index, int counter1)
//{
//    counter1 = 0;
//    int MCS_sum = 0;
//    for(counter1 =0; counter1 < num_of_runs; counter1++)
//    {
//        MCS_sum = MCS_sum + MCS_array[k_index][counter1];
//    }
//    return MCS_sum/num_of_runs;
//}

//What I will do then (not necessarily in this order), is:
    //1. P =0, N = 100,500,1000 with as large run sizes as possible for each. I will see how quickly those run on the server.
    //2. P = 1.00, and I will redo N =100, 500; with 100,000 -> 1,000,000 runs
    //3. Add code to count MCS.  DONE
    //4. I will grab all of that information once the runs are done and plot it in MATLAB.
    // I need to make a correction in my code (that includes this one, the one in Code::Blocks). Since I noticed that the MCS is dependent on the
    // num_of_runs parameter, I will need to get rid of that and print out the MCS for each
    // one of my num_of_runs trials. So with 1000 num_of_runs and deltaX = 0.01, that means I will have
    // 1000 * 100 + 1 MCS values. (The +1 comes from x = 0).

//We can cogunt 1 MCS as N update attempts (whether or not those updates are successfull or not).  So every time you pick 1 pair of sites, that is 1/N MCS.  
//This is a pretty typical way to count MCS, and is the one used by Slanina et al. in EPL 82 18006 (2008).


