/*
    Given an array of non-negative integers, you are initially positioned 
        at the first index of the array.

    Each element in the array represents your maximum jump length at that 
        position.

    Determine if you are able to reach the last index.

    For example:
        A = [2,3,1,1,4], return true.

        A = [3,2,1,0,4], return false.
*/
class Solution {
public:
    bool canJump(vector<int>& A) 
    {
        if (A.empty()) return true;
        int mx = 0;
        for (int i = 0; i <= mx; ++i)
        {
            mx = max(mx, i + A[i]);
            if (mx >= A.size() - 1) return true;
        }
        return false;
    }
};