/*
 * Author: Spencer Peters
 * Date: 9/23/18
 * Class: CSC-2710
 * File Location: ~/CSC2710/Proj2
 *
 * This program uses both brute force and divide and conquer to decide
 * whether to buy or sell a stock by funding the maximum sub-array
 */

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

//Function Prototypes
void scan(int pr[], int days, int chnge[]);
int bruteForce(int chnge[], int days, int &lpos, int &rpos);
int maxSub(int chnge[], int low, int high, int &lsub, int &rsub);
int crossMaxSub(int chnge[], int low , int mid, int high, int &lsub , int &rsub);


int main()
{
    //Variables
    int days;
    char algoType;
    cin >> algoType;
    cin >> days;
    int maxSum = 0;
    int price[days];
    int change[days];
    int rpos = 0;
    int lpos = 0;
    int lsub = 0;
    int rsub = 0;
    //Scan Function Call
    scan(price,days,change);
    //Checks to see if it's a divide and conquer or brute force
    if(algoType == 'd' || algoType == 'D')
    {
        maxSum = maxSub(change, 0, days-1, lsub, rsub);
        cout <<"The max sum: " << maxSum << endl;
        cout << "This would be between days: " << (lsub) << "-" << (rsub) << endl;
    }
    else if(algoType == 'b' || algoType == 'B')
    {
        cout << "Brute Force" << endl;
        maxSum = bruteForce(change, days, lpos, rpos);
        cout <<"The max sum: " << maxSum << endl;
        cout << "This would be between days: " << (lpos + 1) << "-" << (rpos +1) << endl;
    }
    return 0;
}

/*Scan Function:
 *      Reads in the price of the stock from the data file and calculates the change
 *
 *precondition:
 *      pr[] is the array where the prices are held the size is
 *      determined by the amount of days that's scanned in at the beginning of
 *      the file in order to not take up more memory then needed. chnge[] is
 *      the array allocated to holding the change between the two
 *
 *post conditon:
 *      pr[] while be loaded with the the prices of the stocks and ready
 *      to be used in the rest of the program. chnge[] will be filled with the
 *      change between each day based off the starting price
 */
void scan(int pr[], int days, int chnge[])
{
    for (int i = 0; i <= days; ++i)
    {
        cin >> pr[i];
    }
    for (int j = 0; j < days; ++j)
    {
        chnge[j] = pr[j+1] - pr[j];
    }
}


/*bruteForce Function:
 *     Finds the max sub array by using brute force instead of divide and conquer
 *
 *precondition:
 *     Takes in the chnge[] and days in order to find the maximum sub array and
 *     compares every possible one to determine the max sub array
 *
 *post conditon:
 *      Returns the total which holds the value of the max sub array and keeps track
 *      of where they fall in the array itself by passing lpos and rpos by reference
 */
int bruteForce(int chnge[], int days, int &lpos, int &rpos)
{
        int total = INT_MIN;
        int contSum;

        for(int i=0;i<days;i++)
        {
            contSum=0;
            for(int j=i;j<days;j++)
            {
                contSum+=chnge[j];
                if(contSum>total)
                {
                    total=contSum;
                    lpos = i;
                    rpos = j;
                }
            }
        }
        return total;
}

/*maxSub Function:
 *      This function finds the max sub array using the divide and conquer method
 *
 *precondition:
 *      The function uses recursion in order to break the array of changes into smaller
 *      and smaller pieces and compares the 3 possibilities being left max, mid max, and
 *      right max then they are compared in the if statements
 *
 *post conditon:
 *      The function will return the the highest max sum, the lsub and rsub are reference
 *      values that hold the left and right postions for the max sub array to print in main
 */
int maxSub(int chnge[], int low, int high, int &lsub, int &rsub)
{

    if (low == high)
    {
        return chnge[low];
    }

    int mid = (low + high)/2;
    int lsub1, lsub2, lsub3;
    int rsub1, rsub2, rsub3;
    int firstMax = maxSub(chnge, low, mid, lsub1, rsub1);
    int secondMax = maxSub(chnge, mid+1, high, lsub2, rsub2);
    int thirdMax = crossMaxSub(chnge, low, mid, high, lsub3, rsub3);
    int maxSum = firstMax;
    lsub = lsub1;
    rsub = rsub1;

    if(firstMax < secondMax)
    {
        maxSum = secondMax;
        lsub = lsub2;
        rsub = rsub2;
    }

    if(firstMax < thirdMax)
    {
        maxSum = thirdMax;
        lsub = lsub3;
        rsub = rsub3;
    }
    return maxSum;
}

/*crossMaxSub Function:
 *      This function is called in maxSub to determine the left and right sub arrays
 *
 *precondition:
 *      It is sent the low, mid, high in order to find out of left or right sum is bigger
 *      than one or the other
 *
 *post conditon:
 *      The function returns the value of both right and left values.
 */
int crossMaxSub(int chnge[], int low , int mid, int high, int &lsub , int &rsub)
{
    int sum = 0;
    int left = INT_MIN;

    for (int i = mid; i >= low; i--)
    {
        sum = sum + chnge[i];
        if(sum > left)
        {
            left = sum;
            lsub = (i+1);
        }
    }

    sum = 0;
    int right = INT_MIN;
    for (int i = mid+1; i <= high; i++)
    {
        sum = sum + chnge[i];
        if(sum > right)
        {
            right = sum;
            rsub = (i+1);
        }
    }
    return left + right;
}