int countWaysUtil(int x, int n, int num)
{
    // Base cases 
    int val = (x - pow(num, n));
    if (val == 0)
        return 1;
    if (val < 0)
        return 0;

    // Consider two possibilities, num is 
    // included and num is not included. 
    return countWaysUtil(val, n, num + 1) +
        countWaysUtil(x, n, num + 1);
}

// Returns number of ways to express 
// x as sum of n-th power of two. 
int countWays(int x, int n)
{
}

int countWaySumOfSquare(int x)
{
    /*
     * STUDENT ANSWER
     */

    return countWaysUtil(x, n, 1);

}