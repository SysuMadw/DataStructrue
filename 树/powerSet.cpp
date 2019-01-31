/*************************************************************************
    > File Name: powerSet.cpp
    > Author: 马定伟
    > Mail: 1981409833@qq.com 
    > Created Time: 2019年01月26日 星期六 18时58分33秒
 ************************************************************************/

# include <iostream>
# include <vector>

using namespace std;

void powerSet(vector<vector<int>>& sets, vector<int>& arr, int i){
	if (i >= arr.size())
		return;
	int num = sets.size();
	for (int j=0; j<num; j++){
		vector<int> array(sets[j]);
		array.push_back(arr[i]);
		sets.push_back(array);
	}
	powerSet(sets,arr,i+1);
}

int main(void){
	vector<int> ans = {1,2,3,4,5,6,7,8,9,10};
	vector<vector<int>> arr(1,vector<int>());
	powerSet(arr,ans,0);
	for (int i=0; i<arr.size(); i++){
		for (int j=0; j<arr[i].size(); j++)
			cout << arr[i][j] << ' ';
		cout << endl;
	}
	return 0;
}

//递归解
class Solution {
public:
    vector<vector<int>> ans;
    vector<int> arr;
    
    vector<vector<int>> subsets(vector<int>& nums) {
        powerSet(nums,0);
        return ans;
    }
    
    void powerSet(vector<int>& nums, int i){
        if (i >= nums.size()){
            ans.push_back(arr);
            return;
        }
        arr.push_back(nums[i]);
        powerSet(nums,i+1);
        arr.pop_back();
        powerSet(nums,i+1);
    }
};
