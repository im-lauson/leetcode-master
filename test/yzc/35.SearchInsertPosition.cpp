#include "iostream"
#include "vector"
#include <unordered_map>

using namespace std;

class Solution {
public:
    // Solution 1：暴力解法 一次遍历 比较直观的做法 O(n)
    // 遍历数组 处理各种特殊的情况，最后即推出答案
    static int searchInsertIntuitive(vector<int>& nums,int target){
        int ans = 0;
        int length = nums.size();

        // 思路是处理每一种情况，该题一共有如下 4 种情况
        // - case1: 目标在等于数组中的某一个元素
        // - case2: 目标在所有元素之前
        // - case3: 目标需要插入到数组中某个位置
        // - case4: 目标在所有元素之后

        // handle all cases.
        for (int i = 0; i < length; ++i) {
            if (nums[i] == target){ // case 1. 直接找到该目标
                ans = i;
                break;
            } else if (nums[length-1] < target){ // case 4. 若该有序数组最后一个元素都小于目标，可以断定目标将插入到数组末尾
                ans = length;
                break;
            } else if (nums[0] > target){ // case 2. 若该有序数组的第一个元素都大于目标，可以断定目标将插入数值最前面
                ans = 0;
            } else if (nums[i] > target){ // case 3. 若该位置元素大于目标，则先假设目标将插入此地
                ans = i;
                break;
            }
            // 优化思考：第 3，4步可以放入第一步中
            // 将第1步改为： if(nums[i] >= length)...
        }
        return ans;
    }
    // Concise version of solution 1.
    static int searchInsertIntuitiveConcise(vector<int> &nums,int target){
        for (int i = 0; i <nums.size(); ++i) {
            // handle case 1,2,3
            if (nums[i] >= target){
                return i;
            }
        }
        // case 4.
        return nums.size(); // (这里同时也可以处理 nums 为空的情况)
    }
    // Solution 2: Binary search
    // the 'zero' method
    static int searchInsertBS0(vector<int>& nums, int target) {
        int length = nums.size();
        int left = 0, right = length - 1, ans = length;
        while (left <= right) {
            int mid = ((right - left) >> 1) + left;
            if (target <= nums[mid]) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }
    // Binary search
    // the first method.
    static int searchInsertBS1(vector<int>& nums, int target) {
        int length = nums.size();
        int left = 0;
        int right = length - 1; // 定义目标在左闭右闭的区间里，[left,right]
        while (left <= right) { // 当 left == right 时，区间[left,right] 仍然有效
            // int middle = (left + right)/2; // 取中值。该方法可能会造成溢出 //TODO: 何时会溢出
            int middle = left + ((right - left)/2); // 取中值。该写法可以防止溢出
            if (nums[middle] > target){
                right = middle -1; // 往左移动 right（中值都大于目标，说明目标在中值左边，因此去除右边无用元素）
            } else if (nums[middle] < target){
                left = middle + 1;
            } else{ // nums[target] == target 中值就是目标
                return middle;
            }
        }
        // - 目标在所有元素中。直接返回 return middle
        // 在如上的 binary search 算法中都没找到该元素 说明不在数组中
        // 分别处理如下 3 种情况：
        // - 目标在所有元素之前 [0,-1]。 这种情况下，right 会一直向左移动，直到 right == left == 0
        //      此时 right = middle-1 = (left + ((right-left)/2)) -1 = (0+0)-1 = -1, 此时返回 right +1 ;
        // - 目标在所有元素之后 [left,right]。这种情况下 left 会一直向右移动，一直到 left == right == length -1
        //      此时要将目标放在最后面 即 right+1
        // - 目标不在所有元素中，但是需要混入其中。
        //      此时以 right 为基准
        return right + 1;
    }
};

int main(){
    vector<int> nums1 = {1,3,5,6};
    int target1 = 5;
    int target2 = 2;
    int target3 = 7;

    int resultIntuitive = Solution::searchInsertIntuitive(nums1,target1);
    cout << "[Solution]: "<< resultIntuitive << endl;
    int result = Solution::searchInsertBS1(nums1, target1);
    cout << "[Solution]: "<< result << endl;

    return 0;
}